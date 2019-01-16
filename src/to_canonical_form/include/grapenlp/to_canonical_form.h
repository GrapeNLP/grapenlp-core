/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2018 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

/*
 *  @author Javier Sastre
 */

#ifndef GRAPENLP_TO_CANONICAL_FORM_H
#define GRAPENLP_TO_CANONICAL_FORM_H

#include <grapenlp/error.h>
#include <grapenlp/array.h>
#include <grapenlp/text_delaf.h>
#include <grapenlp/text_delaf_entry_filter.h>
#include <algorithm>
#include <list>
#include <memory>

namespace grapenlp
{
	template<typename Char, typename InputIterator, typename TokenIterator, typename CaseNormalizer>
	std::size_t compute_to_canonical_form_translations_and_length(InputIterator input_begin, InputIterator input_end, TokenIterator token_begin, TokenIterator token_end, const text_delaf<Char, CaseNormalizer> &dico, const text_delaf_entry_filter<Char, CaseNormalizer> &translation_filter, std::list<std::pair<TokenIterator, typename text_delaf<Char, CaseNormalizer>::lemma_string::const_ref> > &translations)
	{
		//Initialize result length as 0
		std::size_t length(0);
		typename text_delaf<Char, CaseNormalizer>::entry_list::const_iterator current_dico_entry;
		typename text_delaf<Char, CaseNormalizer>::lemma_string::const_ref lsr;

		//For every token
		for (; token_begin != token_end; ++token_begin)
		{
			lsr = dico.get((*token_begin)->begin, (*token_begin)->end);
			//If current token is a known word
			if (lsr && lsr->data)
			{
				current_dico_entry = lsr->data->begin();
				//Search verb interpretation
				while (current_dico_entry != lsr->data->end() && !translation_filter.match(**current_dico_entry))
					++current_dico_entry;
				//If found verb interpretation
				if (current_dico_entry != lsr->data->end())
				{
					translations.push_back(std::pair<TokenIterator, typename text_delaf<Char, CaseNormalizer>::lemma_string::const_ref>(token_begin, &(*current_dico_entry)->canonical_form));
					//Add the number of characters of the canonical form of the current token +
					//the number of characters from the last added character up to the begining of this token
					//and position the input iterator after the token
					length += std::distance(input_begin, (*token_begin)->begin) + (*current_dico_entry)->canonical_form.size();
					input_begin = (*token_begin)->end;
				}
			}
		}
		//Return the current length plus the number of characters left from the last counted character up to the input end
		return length + std::distance(input_begin, input_end);
	}

	template<typename Char, typename InputIterator, typename TokenIterator, typename TranslationIterator, typename ResultIterator>
	void serialize_to_canonical_form_translations(InputIterator input_begin, InputIterator input_end, TokenIterator token_begin, TokenIterator token_end, TranslationIterator translation_begin, TranslationIterator translation_end, ResultIterator result_begin)
	{
		//For every token to be translated
		for (; translation_begin != translation_end; ++translation_begin)
		{
			//Copy the characters between the last copied character and the begining of the current translation
			result_begin = std::copy(input_begin, (*translation_begin->first)->begin, result_begin);
			//Copy the characters of the current translation
			result_begin = std::copy(translation_begin->second->begin(), translation_begin->second->end(), result_begin);
			//Position the input iterator after the current translated token
			input_begin = (*translation_begin->first)->end;
		}
		//Copy the characters left from the last copied character up to the input end
		std::copy(input_begin, input_end, result_begin);
	}

	/* Generates and returns an array of characters from a token list,
	 * where the tokens corresponding to known verbs are replaced by their infinitive form*/
	template<typename Char, typename InputIterator, typename TokenIterator, typename CaseNormalizer>
	void to_canonical_form(InputIterator input_begin, InputIterator input_end, TokenIterator token_begin, TokenIterator token_end, const text_delaf<Char, CaseNormalizer> &dico, const text_delaf_entry_filter<Char, CaseNormalizer> &translation_filter, array<Char> &result)
	{
		//No tokens in the input, just copy the possible no-token characters (whites) and return them
		if (token_begin == token_end)
		{
			std::unique_ptr<array<Char> > result(new array<Char>(std::distance(input_begin, input_end)));
			std::copy(input_begin, input_end, result->begin());
			return;
		}

		//There are tokens in the input
		//Compute the translations to canonical form of the tokens who pass the filter
		//and the length in characters of the resulting translated sentence
		std::list<std::pair<TokenIterator, typename text_delaf<Char, CaseNormalizer>::lemma_string::const_ref> > translations;
		std::size_t length(compute_to_canonical_form_translations_and_length(input_begin, input_end, token_begin, token_end, dico, translation_filter, translations));

		//Initialize the buffer which will contain the result of the translation
		result.reset(length);
		//Fill the buffer with the result
		typename array<Char>::iterator current_result(result->begin());
		serialize_to_canonical_form_translations<Char, InputIterator, TokenIterator, typename std::list<std::pair<TokenIterator, typename text_delaf<Char, CaseNormalizer>::lemma_string::const_ref> >::const_iterator, typename array<Char>::iterator>(input_begin, input_end, token_begin, token_end, translations.begin(), translations.end(), current_result);
		return;
	}

	/* Generates and returns an array of characters from a token list,
	 * where the tokens corresponding to known verbs are replaced by their infinitive form*/
	template<typename Char, typename InputIterator, typename TokenIterator, typename CaseNormalizer, typename MarkIterator>
	void to_canonical_form(InputIterator input_begin, InputIterator input_end, TokenIterator token_begin, TokenIterator token_end, const text_delaf<Char, CaseNormalizer> &dico, const text_delaf_entry_filter<Char, CaseNormalizer> &translation_filter, MarkIterator mark_begin, MarkIterator mark_end, array<Char> &result)
	{
		//No tokens in the input: just copy the possible no-token characters (whites) and return them
		if (token_begin == token_end)
		{
			//Initialize the buffer which will contain the result of the translation
			result.reset(std::distance(input_begin, input_end) + std::distance(mark_begin, mark_end));
			//Copy the mark to the result
			typename array<Char>::iterator current_result(std::copy(mark_begin, mark_end, result.begin()));
			//Copy whites to the result
			std::copy(input_begin, input_end, current_result);
			return;
		}

		//There are tokens in the input
		//Compute the translations to canonical form of the tokens who pass the filter
		//and the length in characters of the resulting translated sentence + the mark + one space
		std::list<std::pair<TokenIterator, typename text_delaf<Char, CaseNormalizer>::lemma_string::const_ref> > translations;
		std::size_t length(std::distance(mark_begin, mark_end) + compute_to_canonical_form_translations_and_length(input_begin, input_end, token_begin, token_end, dico, translation_filter, translations));

		//Initialize the buffer which will contain the result of the translation
		result.reset(length);

		//Copy the mark to the result
		typename array<Char>::iterator current_result(std::copy(mark_begin, mark_end, result.begin()));
		//Fill the buffer with the result
		serialize_to_canonical_form_translations<Char, InputIterator, TokenIterator, typename std::list<std::pair<TokenIterator, typename text_delaf<Char, CaseNormalizer>::lemma_string::const_ref> >::const_iterator, typename array<Char>::iterator>(input_begin, input_end, token_begin, token_end, translations.begin(), translations.end(), current_result);
	}
} //namespace grapenlp


#endif /*GRAPENLP_TO_CANONICAL_FORM_H*/
