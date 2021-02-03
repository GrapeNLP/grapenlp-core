/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@gmail.com>
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

#ifndef GRAPENLP_ULUA_FST2_READER_H
#define GRAPENLP_ULUA_FST2_READER_H

#include <grapenlp/lua_rtno.h>
#include <grapenlp/ua_fst2_tag_output_reader.h>
#include <grapenlp/ul_fst2_reader.h>

namespace grapenlp
{
	struct ua_stop_char_evaluator
	{
		bool operator() (unichar c) const
		{ return c == U_ENDL; }
	};


	template<typename InputIterator, typename CaseNormalizer=u_tolower>
	struct ulua_fst2_reader: public ul_fst2_reader<InputIterator, ua_fst2_tag_output_reader<ua_stop_char_evaluator>, CaseNormalizer>
	{
		typedef ua_fst2_tag_output_reader<ua_stop_char_evaluator> my_ua_fst2_tag_output_reader;
		typedef ul_fst2_reader<InputIterator, my_ua_fst2_tag_output_reader, CaseNormalizer> base_type;
		typedef typename base_type::machine machine;
		typedef typename my_ua_fst2_tag_output_reader::ua_trie ua_trie;

		ulua_fst2_reader(): base_type()
		{}

		int operator() (FILE *f, machine &grammar, ul_tag_input_trie<unichar, InputIterator> &ult, ua_trie &uat, u_text_delaf<CaseNormalizer> &dico, u_context_key_value_hasher &c_hasher)
		{
			ua_stop_char_evaluator is_stop_char;
			my_ua_fst2_tag_output_reader tor(is_stop_char, uat);
			return base_type::operator() (f, grammar, ult, tor, dico, c_hasher);
		}

		int operator() (FILE *f, machine &grammar, ul_tag_input_trie<unichar, InputIterator> &ult, ua_trie &uat, compressed_delaf &dico, u_context_key_value_hasher &c_hasher)
		{
			ua_stop_char_evaluator is_stop_char;
			my_ua_fst2_tag_output_reader tor(is_stop_char, uat);
			return base_type::operator() (f, grammar, ult, tor, dico, c_hasher);
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_ULUA_FST2_READER*/
