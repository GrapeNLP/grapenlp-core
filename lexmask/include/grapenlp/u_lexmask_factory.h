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

#ifndef GRAPENLP_U_LEXMASK_FACTORY_H
#define GRAPENLP_U_LEXMASK_FACTORY_H

//#include <grapenlp/error.h>
//#include <grapenlp/u_array.h>
//#include <grapenlp/u_delaf.h>
#include <grapenlp/u_lexmask_constants.h>
//#include <grapenlp/lexmask_and_coarse_type.h>
#include <grapenlp/meta_code_dico.h>
#include <grapenlp/u_text_dico_word_meta_mask_factory.h>
#include <grapenlp/u_compressed_dico_word_meta_mask_factory.h>
//#include <grapenlp/u_delaf_entry_filter_factory.h>

namespace grapenlp
{
/*	template<typename InputIterator, typename CaseNormalizer>
	lexmask_and_coarse_type<InputIterator>* make_u_lexmask(typename l_trie<unichar, InputIterator>::string &uls,u_text_delaf<CaseNormalizer> &dico)
	{
		u_text_dico_word_meta_mask_factory<InputIterator, CaseNormalizer> dico_lexmask_factory(dico);
		return make_u_lexmask<InputIterator, CaseNormalizer>(uls, dico_lexmask_factory);
	}

	template<typename InputIterator, typename CaseNormalizer>
	lexmask_and_coarse_type<InputIterator>* make_u_lexmask(typename l_trie<unichar, InputIterator>::string &uls, compressed_delaf &dico)
	{
		u_compressed_dico_word_meta_mask_factory<InputIterator, CaseNormalizer> dico_lexmask_factory(dico);
		return make_u_lexmask<InputIterator, CaseNormalizer>(uls, dico_lexmask_factory);
	}*/

	template<typename InputIterator, typename CaseNormalizer>
	lexmask_and_coarse_type<InputIterator>* make_u_lexmask(typename l_trie<unichar, InputIterator>::string &uls, u_dico_word_meta_mask_factory<InputIterator> &dico_lexmask_factory)
	{
		u_array lexmask_code(uls.size());
		uls.to_array(lexmask_code);
		//Word mask
		if (u_is_letter(lexmask_code[1]))
		{
			if (lexmask_code[0] == case_sensitive_char)
			{
#ifdef TRACE
				std::wcout << L"Creating case sensitive mask\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new case_sensitive_word_mask<InputIterator>(lexmask_code.begin() + 1, lexmask_code.size() - 1), CONSUMING);
			}
#ifdef TRACE
			std::wcout << L"Creating case insensitive mask\n";
#endif
			return new lexmask_and_coarse_type<InputIterator>(new case_insensitive_word_mask<InputIterator, CaseNormalizer>(lexmask_code.begin() + 1, lexmask_code.size() - 1), CONSUMING);
		}

		//Meta mask
		if (lexmask_code[1] == meta_left_delimiter_char && lexmask_code[0] == case_insensitive_char && lexmask_code.size() > 2 && lexmask_code[2] != in_out_separator_char)
		{
			if (lexmask_code.back() != meta_right_delimiter_char)
				fatal_error("Unterminated meta mask\n");
			u_array::const_iterator meta_code_begin = lexmask_code.begin() + 2;
			u_array::const_iterator meta_code_end = lexmask_code.end() - 1;

			u_trie_string::ref meta_code(the_meta_code_dico.get(meta_code_begin, meta_code_end));
			//Epsilon
			if (meta_code == the_meta_code_dico.epsilon_meta_code)
			{
#ifdef TRACE
					std::wcout << L"Creating epsilon meta mask\n";
#endif
					return new lexmask_and_coarse_type<InputIterator>(NULL, EPSILON);
			}
			//Token meta mask
			if (meta_code == the_meta_code_dico.token_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating token meta mask\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new token_meta_mask<InputIterator>(), CONSUMING);
			}
			//Word meta mask
			if (meta_code == the_meta_code_dico.word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating word meta mask\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new word_meta_mask<InputIterator>(), CONSUMING);
			}
			//No word meta mask
			if (meta_code == the_meta_code_dico.no_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating not a word meta mask\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new no_word_meta_mask<InputIterator>(), CONSUMING);
			}
			//Upper word meta mask
			if (meta_code == the_meta_code_dico.upper_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating upper word meta mask\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new upper_word_meta_mask<InputIterator>(), CONSUMING);
			}
			//Not an upper word meta mask
			if (meta_code == the_meta_code_dico.no_upper_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating not an upper word meta mask\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new no_upper_word_meta_mask<InputIterator>(), CONSUMING);
			}
			//Lower word meta mask
			if (meta_code == the_meta_code_dico.lower_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating Lower word meta\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new lower_word_meta_mask<InputIterator>(), CONSUMING);
			}
			//Not a lower word meta mask
			if (meta_code == the_meta_code_dico.no_lower_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating Not a lower word meta\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new no_lower_word_meta_mask<InputIterator>(), CONSUMING);
			}
			//First upper word meta mask
			if (meta_code == the_meta_code_dico.first_upper_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating first upper word meta\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new first_upper_word_meta_mask<InputIterator>(), CONSUMING);
			}
			//Not a first upper word meta mask
			if (meta_code == the_meta_code_dico.no_first_upper_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating not a first upper word meta\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new no_first_upper_word_meta_mask<InputIterator>(), CONSUMING);
			}
			//Digit meta mask
			if (meta_code == the_meta_code_dico.digit_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating digit meta\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new digit_meta_mask<InputIterator>(), CONSUMING);
			}
			//Not a digit meta mask
			if (meta_code == the_meta_code_dico.no_digit_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating not a digit meta\n";
#endif
				return new lexmask_and_coarse_type<InputIterator>(new no_digit_meta_mask<InputIterator>(), CONSUMING);
			}
			//Constrained dictionary word meta mask (last possibility)
#ifdef TRACE
			std::wcout << L"Creating constrained dico word meta mask: ";
#endif
			return dico_lexmask_factory(meta_code_begin, meta_code_end);
//			return new lexmask_and_coarse_type<InputIterator>(new constrained_dico_word_meta_mask<InputIterator, CaseNormalizer>(d, make_u_delaf_entry_filter<CaseNormalizer, u_array::const_iterator>(meta_code_begin, meta_code_end, d)), CONSUMING);
		}

		//No-blank epsilon transition
		if (lexmask_code[1] == no_blank_char && lexmask_code[0] == case_insensitive_char)
		{
			if (lexmask_code.size() > 2)
				fatal_error("No-blank mask more than 1 symbol\n");
#ifdef TRACE
			std::wcout << L"Creating no-blank epsilon meta mask\n";
#endif
			return new lexmask_and_coarse_type<InputIterator>(NULL, NO_BLANK_EPSILON);
		}

		//Blank epsilon transition
		if (lexmask_code[1] == blank_char && lexmask_code[0] == case_insensitive_char)
		{
			if (lexmask_code.size() > 2)
				fatal_error("Blank mask more than 1 symbol\n");
#ifdef TRACE
			std::wcout << L"Creating blank epsilon meta mask\n";
#endif
			return new lexmask_and_coarse_type<InputIterator>(NULL, BLANK_EPSILON);
		}

		//Symbol mask
		if (lexmask_code.size() > 2)
			fatal_error("Symbol mask containing more than 1 symbol\n");
#ifdef TRACE
		std::wcout << L"Creating symbol mask\n";
#endif
		return new lexmask_and_coarse_type<InputIterator>(new symbol_mask<InputIterator>(lexmask_code[1]), CONSUMING);
	}
} //namespace grapenlp

#endif /*GRAPENLP_U_LEXMASK_FACTORY_H*/
