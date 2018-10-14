/*
 * GRAPE
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

#ifndef GRAPE_TO_DECOMPRESSED_CANONICAL_FORM_H
#define GRAPE_TO_DECOMPRESSED_CANONICAL_FORM_H

#include <grape/error.h>
#include <grape/array.h>
#include <grape/normalizer_iterator.h>
#include <grape/compressed_delaf.h>
#include <grape/compressed_delaf_entry_filter.h>
#include <algorithm>
#include <list>

namespace grape
{
	//
	template<typename Char, typename InputIterator, typename TokenIterator, typename CaseNormalizer>
	std::size_t compute_to_decompressed_canonical_form_translations_and_length(InputIterator input_begin, InputIterator input_end, TokenIterator token_begin, TokenIterator token_end, const compressed_delaf &dico, const compressed_delaf_entry_filter<normalizer_iterator<CaseNormalizer, InputIterator> > &translation_filter, std::list<std::pair<TokenIterator, const inf_delaf::entry*> > &translations)
	{
		//Initialize result length as 0
		std::size_t length(0);
		const inf_delaf::ambiguous_entry* current_dico_ambiguous_entry_ref;
		inf_delaf::ambiguous_entry::const_iterator current_dico_entry_ref;
		
		//For every token
		for (; token_begin != token_end; ++token_begin)
		{
			current_dico_ambiguous_entry_ref = dico.get_word_properties(normalizer_iterator<CaseNormalizer, InputIterator>((*token_begin)->begin), normalizer_iterator<CaseNormalizer, InputIterator>((*token_begin)->end));
			//If current token is a known word
			if (current_dico_ambiguous_entry_ref)
			{
				current_dico_entry_ref = current_dico_ambiguous_entry_ref->begin();
				//Search verb interpretation
				while (current_dico_entry_ref != current_dico_ambiguous_entry_ref->end() && !translation_filter.match(normalizer_iterator<CaseNormalizer, InputIterator>((*token_begin)->begin), normalizer_iterator<CaseNormalizer, InputIterator>((*token_begin)->end), **current_dico_entry_ref))
					++current_dico_entry_ref;
				//If found verb interpretation
				if (current_dico_entry_ref != current_dico_ambiguous_entry_ref->end())
				{
					translations.push_back(std::pair<TokenIterator, const inf_delaf::entry*>(token_begin, *current_dico_entry_ref));
					//Add the number of characters of the canonical form of the current token +
					//the number of characters from the last added character up to the begining of this token
					//and position the input iterator after the token
					length += std::distance(input_begin, (*token_begin)->begin) + (*current_dico_entry_ref)->get_decompressed_canonical_form_size((*token_begin)->begin, (*token_begin)->end);
					input_begin = (*token_begin)->end;
				}
			}
		}
		//Return the current length plus the number of characters left from the last counted character up to the input end 
		return length + std::distance(input_begin, input_end);
	}

	template<typename Char, typename InputIterator, typename TokenIterator, typename TranslationIterator, typename ResultIterator>
	void serialize_to_decompressed_canonical_form_translations(InputIterator input_begin, InputIterator input_end, TokenIterator token_begin, TokenIterator token_end, TranslationIterator translation_begin, TranslationIterator translation_end, ResultIterator result_begin)
	{
		//For every token to be translated
		for (; translation_begin != translation_end; ++translation_begin)
		{
			//Copy the characters between the last copied character and the begining of the current translation
			result_begin = std::copy(input_begin, (*translation_begin->first)->begin, result_begin);
			//Copy the characters of the current translation steam
			result_begin = std::copy(normalizer_iterator<u_tolower, InputIterator>((*translation_begin->first)->begin), normalizer_iterator<u_tolower, InputIterator>((*translation_begin->first)->end - translation_begin->second->inflected_form_suffix_length), result_begin);
			//Copy the characters of the current translation canonical form suffix
			result_begin = std::copy(translation_begin->second->canonical_form_suffix.begin(), translation_begin->second->canonical_form_suffix.end(), result_begin);
			//Position the input iterator after the current translated token
			input_begin = (*translation_begin->first)->end;
		}
		//Copy the characters left from the last copied character up to the input end 
		std::copy(input_begin, input_end, result_begin);
	}

	/* Generates and returns an array of characters from a token list,
	 * where the tokens corresponding to known verbs are replaced by their infinitive form*/
	template<typename Char, typename InputIterator, typename TokenIterator, typename CaseNormalizer>
	void to_decompressed_canonical_form(InputIterator input_begin, InputIterator input_end, TokenIterator token_begin, TokenIterator token_end, const compressed_delaf &dico, const compressed_delaf_entry_filter<normalizer_iterator<CaseNormalizer, InputIterator> > &translation_filter, array<Char> &result)
	{
		//No tokens in the input, just copy the possible no-token characters (whites) and return them
		if (token_begin == token_end)
		{
			result.reset(std::distance(input_begin, input_end));
			std::copy(input_begin, input_end, result.begin());
			return;
		}

		//There are tokens in the input
		//Compute the translations to canonical form of the tokens who pass the filter
		//and the length in characters of the resulting translated sentence
		std::list<std::pair<TokenIterator, const inf_delaf::entry*> > translations;
		std::size_t length(compute_to_decompressed_canonical_form_translations_and_length<Char, InputIterator, TokenIterator, CaseNormalizer>(input_begin, input_end, token_begin, token_end, dico, translation_filter, translations));

		//Initialize the buffer which will contain the result of the translation
		result.reset(length);
		//Fill the buffer with the result 
		typename array<Char>::iterator current_result(result.begin());
		serialize_to_decompressed_canonical_form_translations<Char, InputIterator, TokenIterator, typename std::list<std::pair<TokenIterator, const inf_delaf::entry*> >::const_iterator, typename array<Char>::iterator>(input_begin, input_end, token_begin, token_end, translations.begin(), translations.end(), current_result);
	}

	/* Generates and returns an array of characters from a token list,
	 * where the tokens corresponding to known verbs are replaced by their infinitive form*/
	template<typename Char, typename InputIterator, typename TokenIterator, typename CaseNormalizer, typename MarkIterator>
	void to_decompressed_canonical_form(InputIterator input_begin, InputIterator input_end, TokenIterator token_begin, TokenIterator token_end, const compressed_delaf &dico, const compressed_delaf_entry_filter<normalizer_iterator<CaseNormalizer, InputIterator> > &translation_filter, MarkIterator mark_begin, MarkIterator mark_end, array<Char> &result)
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
		std::list<std::pair<TokenIterator, const inf_delaf::entry*> > translations;
		std::size_t length(std::distance(mark_begin, mark_end) + compute_to_decompressed_canonical_form_translations_and_length<Char, InputIterator, TokenIterator, CaseNormalizer>(input_begin, input_end, token_begin, token_end, dico, translation_filter, translations));

		//Initialize the buffer which will contain the result of the translation
		result.reset(length);

		//Copy the mark to the result
		typename array<Char>::iterator current_result(std::copy(mark_begin, mark_end, result.begin()));
		//Fill the buffer with the result 
		serialize_to_decompressed_canonical_form_translations<Char, InputIterator, TokenIterator, typename std::list<std::pair<TokenIterator, const inf_delaf::entry*> >::const_iterator, typename array<Char>::iterator>(input_begin, input_end, token_begin, token_end, translations.begin(), translations.end(), current_result);
	}
} //namespace grape


#endif /*GRAPE_TO_DECOMPRESSED_CANONICAL_FORM_H*/
