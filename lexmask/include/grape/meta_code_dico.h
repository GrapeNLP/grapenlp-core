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

#ifndef GRAPE_META_CODE_DICO_H
#define GRAPE_META_CODE_DICO_H

#include <array>

#include <grape/u_array.h>
#include <grape/u_trie.h>

namespace grape
{
	const std::array<unichar, 1> epsilon_meta_code = { {'E'} };
	const std::array<unichar, 5> token_meta_code = { {'T', 'O', 'K', 'E', 'N'} };
	const std::array<unichar, 3> word_meta_code = { {'M', 'O', 'T'} };
	const std::array<unichar, 4> no_word_meta_code = { {'!', 'M', 'O', 'T'} };
	const std::array<unichar, 3> upper_word_meta_code = { {'M', 'A', 'J'} };
	const std::array<unichar, 4> no_upper_word_meta_code = { {'!', 'M', 'A', 'J'} };
	const std::array<unichar, 3> lower_word_meta_code = { {'M', 'I', 'N'} };
	const std::array<unichar, 4> no_lower_word_meta_code = { {'!', 'M', 'I', 'N'} };
	const std::array<unichar, 3> first_upper_word_meta_code = { {'P', 'R', 'E'} };
	const std::array<unichar, 4> no_first_upper_word_meta_code = { {'!', 'P', 'R', 'E'} };
	const std::array<unichar, 2> digit_meta_code = { {'N', 'B'} };
	const std::array<unichar, 3> no_digit_meta_code = { {'!', 'N', 'B'} };
	const std::array<unichar, 3> dico_word_meta_code = { {'D', 'I', 'C'} };
	const std::array<unichar, 4> no_dico_word_meta_code = { {'!', 'D', 'I', 'C'} };

	class meta_code_dico: public u_trie
	{
	public:
		//Dictionary of lexical mask meta codes 
		typedef u_trie base_type;

		u_trie::string::ref epsilon_meta_code;
		u_trie::string::ref token_meta_code;
		u_trie::string::ref word_meta_code;
		u_trie::string::ref no_word_meta_code;
		u_trie::string::ref upper_word_meta_code;
		u_trie::string::ref no_upper_word_meta_code;
		u_trie::string::ref lower_word_meta_code;
		u_trie::string::ref no_lower_word_meta_code;
		u_trie::string::ref first_upper_word_meta_code;
		u_trie::string::ref no_first_upper_word_meta_code;
		u_trie::string::ref digit_meta_code;
		u_trie::string::ref no_digit_meta_code;
		u_trie::string::ref dico_word_meta_code;
		u_trie::string::ref no_dico_word_meta_code;

		meta_code_dico(): base_type(),
			epsilon_meta_code(&(base_type::epsilon_->concat(grape::epsilon_meta_code.begin(), grape::epsilon_meta_code.end()))),
			token_meta_code(&(base_type::epsilon_->concat(grape::token_meta_code.begin(), grape::token_meta_code.end()))),
			word_meta_code(&(base_type::epsilon_->concat(grape::word_meta_code.begin(), grape::word_meta_code.end()))),
			no_word_meta_code(&(base_type::epsilon_->concat(grape::no_word_meta_code.begin(), grape::no_word_meta_code.end()))),
			upper_word_meta_code(&(base_type::epsilon_->concat(grape::upper_word_meta_code.begin(), grape::upper_word_meta_code.end()))),
			no_upper_word_meta_code(&(base_type::epsilon_->concat(grape::no_upper_word_meta_code.begin(), grape::no_upper_word_meta_code.end()))),
			lower_word_meta_code(&(base_type::epsilon_->concat(grape::lower_word_meta_code.begin(), grape::lower_word_meta_code.end()))),
			no_lower_word_meta_code(&(base_type::epsilon_->concat(grape::no_lower_word_meta_code.begin(), grape::no_lower_word_meta_code.end()))),
			first_upper_word_meta_code(&(base_type::epsilon_->concat(grape::first_upper_word_meta_code.begin(), grape::first_upper_word_meta_code.end()))),
			no_first_upper_word_meta_code(&(base_type::epsilon_->concat(grape::no_first_upper_word_meta_code.begin(), grape::no_first_upper_word_meta_code.end()))),
			digit_meta_code(&(base_type::epsilon_->concat(grape::digit_meta_code.begin(), grape::digit_meta_code.end()))),
			no_digit_meta_code(&(base_type::epsilon_->concat(grape::no_digit_meta_code.begin(), grape::no_digit_meta_code.end()))),
			dico_word_meta_code(&(base_type::epsilon_->concat(grape::dico_word_meta_code.begin(), grape::dico_word_meta_code.end()))),
			no_dico_word_meta_code(&(base_type::epsilon_->concat(grape::no_dico_word_meta_code.begin(), grape::no_dico_word_meta_code.end())))
		{}
	};

	static meta_code_dico the_meta_code_dico = meta_code_dico();
} //namespace grape

#endif /*GRAPE_SRV_DICO_H*/
