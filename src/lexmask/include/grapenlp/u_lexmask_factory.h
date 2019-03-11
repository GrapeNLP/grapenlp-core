/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2019 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
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

#include <grapenlp/u_lexmask_constants.h>
#include <grapenlp/lexmask.h>
#include <grapenlp/meta_code_dico.h>
#include <grapenlp/u_dico_word_meta_mask_factory.h>

namespace grapenlp
{
	template<typename InputIterator, typename CaseNormalizer>
	lexmask<InputIterator>* make_u_lexmask(const u_array &lexmask_code, u_dico_word_meta_mask_factory<InputIterator> &dico_lexmask_factory)
	{
		//Word mask
		if (u_is_letter(lexmask_code[1]))
		{
			if (lexmask_code[0] == case_sensitive_char)
			{
#ifdef TRACE
				std::wcout << L"Creating case sensitive mask\n";
#endif
				return new case_sensitive_word_mask<InputIterator>(lexmask_code.begin() + 1, lexmask_code.end() - 1);
			}
#ifdef TRACE
			std::wcout << L"Creating case insensitive mask\n";
#endif
			return new case_insensitive_word_mask<InputIterator, CaseNormalizer>(lexmask_code.begin() + 1, lexmask_code.end() - 1);
		}

		//Meta mask
		if (lexmask_code.size() > 2 && lexmask_code[0] == case_insensitive_char && lexmask_code[1] == meta_left_delimiter_char)
		{
			if (lexmask_code.back() != meta_right_delimiter_char)
				fatal_error("Unterminated meta mask\n");
			if (lexmask_code.size() == 3)
				fatal_error("Empty meta mask\n");
			u_array::const_iterator meta_code_begin = lexmask_code.begin() + 2;
			u_array::const_iterator meta_code_end = lexmask_code.end() - 1;

			u_trie_string::ref meta_code(the_meta_code_dico.get(meta_code_begin, meta_code_end));
			//Token meta mask
			if (meta_code == the_meta_code_dico.token_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating token meta mask\n";
#endif
				return new token_meta_mask<InputIterator>();
			}
			//Word meta mask
			if (meta_code == the_meta_code_dico.word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating word meta mask\n";
#endif
				return new word_meta_mask<InputIterator>();
			}
			//No word meta mask
			if (meta_code == the_meta_code_dico.no_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating not a word meta mask\n";
#endif
				return new no_word_meta_mask<InputIterator>();
			}
			//Upper word meta mask
			if (meta_code == the_meta_code_dico.upper_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating upper word meta mask\n";
#endif
				return new upper_word_meta_mask<InputIterator>();
			}
			//Not an upper word meta mask
			if (meta_code == the_meta_code_dico.no_upper_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating not an upper word meta mask\n";
#endif
				return new no_upper_word_meta_mask<InputIterator>();
			}
			//Lower word meta mask
			if (meta_code == the_meta_code_dico.lower_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating Lower word meta\n";
#endif
				return new lower_word_meta_mask<InputIterator>();
			}
			//Not a lower word meta mask
			if (meta_code == the_meta_code_dico.no_lower_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating Not a lower word meta\n";
#endif
				return new no_lower_word_meta_mask<InputIterator>();
			}
			//First upper word meta mask
			if (meta_code == the_meta_code_dico.first_upper_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating first upper word meta\n";
#endif
				return new first_upper_word_meta_mask<InputIterator>();
			}
			//Not a first upper word meta mask
			if (meta_code == the_meta_code_dico.no_first_upper_word_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating not a first upper word meta\n";
#endif
				return new no_first_upper_word_meta_mask<InputIterator>();
			}
			//Digit meta mask
			if (meta_code == the_meta_code_dico.digit_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating digit meta\n";
#endif
				return new digit_meta_mask<InputIterator>();
			}
			//Not a digit meta mask
			if (meta_code == the_meta_code_dico.no_digit_meta_code)
			{
#ifdef TRACE
				std::wcout << L"Creating not a digit meta\n";
#endif
				return new no_digit_meta_mask<InputIterator>();
			}
			//Constrained dictionary word meta mask (last possibility)
#ifdef TRACE
			std::wcout << L"Creating constrained dico word meta mask: ";
#endif
			return dico_lexmask_factory(meta_code_begin, meta_code_end);
		}
		//Symbol mask
		if (lexmask_code.size() > 2)
			fatal_error("Symbol mask containing more than 1 symbol\n");
#ifdef TRACE
		std::wcout << L"Creating symbol mask\n";
#endif
		return new symbol_mask<InputIterator>(lexmask_code[1]);
	}
} //namespace grapenlp

#endif /*GRAPENLP_U_LEXMASK_FACTORY_H*/
