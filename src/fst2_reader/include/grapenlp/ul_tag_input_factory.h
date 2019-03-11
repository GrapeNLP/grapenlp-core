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

#ifndef GRAPENLP_UL_TAG_INPUT_FACTORY_H
#define GRAPENLP_UL_TAG_INPUT_FACTORY_H

#include <grapenlp/u_context_mask_factory.h>
#include <grapenlp/ul_tag_input_constants.h>
#include <grapenlp/ul_tag_input.h>
#include <grapenlp/u_lexmask_factory.h>

namespace grapenlp
{
	template<typename InputIterator, typename CaseNormalizer>
	ul_tag_input<InputIterator>* make_ul_tag_input(typename ul_tag_input_trie<unichar, InputIterator>::string &uls, u_dico_word_meta_mask_factory<InputIterator> &dico_lexmask_factory, u_context &c)
	{
		u_array tag_input_code(uls.size());
		uls.to_array(tag_input_code);

		//If epsilon code, make epsilon input tag
		if (equal(tag_input_code.begin(), tag_input_code.end(), epsilon_transition_code.begin(), epsilon_transition_code.end()))
		{
#ifdef TRACE
			std::wcout << L"Creating epsilon input tag\n";
#endif
			return new ul_tag_input<InputIterator>(EPSILON);
		}

		//If blank epsilon code, make blank epsilon input tag
		if (equal(tag_input_code.begin(), tag_input_code.end(), blank_epsilon_transition_code.begin(), blank_epsilon_transition_code.end()))
		{
#ifdef TRACE
			std::wcout << L"Creating blank epsilon input tag\n";
#endif
			return new ul_tag_input<InputIterator>(BLANK_EPSILON);
		}

		//If no-blank epsilon code, make no-blank epsilon input tag
		if (equal(tag_input_code.begin(), tag_input_code.end(), no_blank_epsilon_transition_code.begin(), no_blank_epsilon_transition_code.end()))
		{
#ifdef TRACE
			std::wcout << L"Creating no-blank epsilon input tag\n";
#endif
			return new ul_tag_input<InputIterator>(NO_BLANK_EPSILON);
		}

		//If context mask delimiters, make context mask
		if (starts_with(tag_input_code.begin() + 1, tag_input_code.end(), context_left_delimiter.begin(), context_left_delimiter.end()) && tag_input_code[0] == case_insensitive_char && tag_input_code.size() > (context_left_delimiter.size() + 1) && tag_input_code[context_left_delimiter.size() + 1] != in_out_separator_char)
		{
#ifdef TRACE
			std::wcout << L"Creating context mask\n";
#endif
			return new ul_tag_input<InputIterator>(make_u_context_mask(tag_input_code.begin() + context_left_delimiter.size(), tag_input_code.end() - context_right_delimiter.size(), c));
		}

		//Otherwise make a lexical mask (there are no other kind of masks)
		return new ul_tag_input<InputIterator>(make_u_lexmask<InputIterator, CaseNormalizer>(tag_input_code, dico_lexmask_factory));
	}
} //namespace grapenlp

#endif /*GRAPENLP_UL_TAG_INPUT_FACTORY_H*/
