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

#ifndef GRAPE_ULW_FST2_READER_H
#define GRAPE_ULW_FST2_READER_H

#include <array>

#include <grape/lw_rtno.h>
#include <grape/w_fst2_tag_output_reader.h>
#include <grape/ul_fst2_reader.h>

namespace grape
{
	template<typename InputIterator, typename Weight, typename CaseNormalizer=u_tolower>
	struct ulw_fst2_reader: public ul_fst2_reader<InputIterator, w_fst2_tag_output_reader<Weight>, CaseNormalizer>
	{
		typedef ul_fst2_reader<InputIterator, w_fst2_tag_output_reader<Weight>, CaseNormalizer> base_type;
		typedef w_fst2_tag_output_reader<Weight> my_w_fst2_tag_output_reader;
		typedef typename base_type::machine machine;

		static const std::array<unichar, 1> tag_output_stop_chars;

		int operator() (FILE *f, machine &grammar, l_trie<unichar, InputIterator> &ult, u_text_delaf<CaseNormalizer> &dico)
		{
			my_w_fst2_tag_output_reader tor;
			return base_type::operator() (f, grammar, ult, tor, dico);
		}

		int operator() (FILE *f, machine &grammar, l_trie<unichar, InputIterator> &ult, compressed_delaf &dico)
		{
			my_w_fst2_tag_output_reader tor;
			return base_type::operator() (f, grammar, ult, tor, dico);
		}
	};
} //namespace grape

#endif /*GRAPE_ULW_FST2_READER*/
