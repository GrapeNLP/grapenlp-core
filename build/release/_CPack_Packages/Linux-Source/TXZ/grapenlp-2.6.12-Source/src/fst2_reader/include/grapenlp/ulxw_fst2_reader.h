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

#ifndef GRAPENLP_ULXW_FST2_READER_H
#define GRAPENLP_ULXW_FST2_READER_H

#include <grapenlp/luxw_rtno.h>
#include <grapenlp/xw_fst2_tag_output_reader.h>
#include <grapenlp/ul_fst2_reader.h>

namespace grapenlp
{
	template<typename InputIterator, typename WeightTransformer, typename CaseNormalizer=u_tolower>
	struct ulxw_fst2_reader: public ul_fst2_reader<InputIterator, xw_fst2_tag_output_reader<WeightTransformer>, CaseNormalizer>
	{
		typedef ul_fst2_reader<InputIterator, xw_fst2_tag_output_reader<WeightTransformer>, CaseNormalizer> base_type;
		typedef typename base_type::machine machine;

		int operator() (FILE *f, machine &grammar, l_trie<unichar, InputIterator> &ult, u_out_bound_trie &uobt, u_text_delaf<CaseNormalizer> &dico)
		{
			xw_fst2_tag_output_reader<WeightTransformer> tor(uobt);
			return base_type::operator() (f, grammar, ult, tor, dico);
		}

		int operator() (FILE *f, machine &grammar, l_trie<unichar, InputIterator> &ult, u_out_bound_trie &uobt, compressed_delaf &dico)
		{
			xw_fst2_tag_output_reader<WeightTransformer> tor(uobt);
			return base_type::operator() (f, grammar, ult, tor, dico);
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_ULXW_FST2_READER*/
