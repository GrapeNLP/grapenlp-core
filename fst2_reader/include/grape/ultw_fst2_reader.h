/*
 * GRAPE
 *
 * Copyright (C) 2011-2012 Universidad de Alicante <javier.sastre@telefonica.net>
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

#ifndef GRAPE_ULTW_FST2_READER_H
#define GRAPE_ULTW_FST2_READER_H

#include <grape/weight_transformer_traits.h>
#include <grape/lutw_rtno.h>
#include <grape/tw_fst2_tag_output_reader.h>
#include <grape/ul_fst2_reader.h>

namespace grape
{
	template<typename InputIterator, typename WeightTransformer, typename CaseNormalizer=u_tolower>
	struct ultw_fst2_reader: public ul_fst2_reader<InputIterator, tw_fst2_tag_output_reader<WeightTransformer>, CaseNormalizer>
	{
		typedef ul_fst2_reader<InputIterator, tw_fst2_tag_output_reader<WeightTransformer>, CaseNormalizer> base_type;
		typedef typename base_type::machine machine;

		int operator() (FILE *f, machine &grammar, l_trie<unichar, InputIterator> &ult, u_trie &ut, u_text_delaf<CaseNormalizer> &dico)
		{
			tw_fst2_tag_output_reader<WeightTransformer> tor(ut);
			return base_type::operator() (f, grammar, ult, tor, dico);
		}

		int operator() (FILE *f, machine &grammar, l_trie<unichar, InputIterator> &ult, u_trie &ut, compressed_delaf &dico)
		{
			tw_fst2_tag_output_reader<WeightTransformer> tor(ut);
			return base_type::operator() (f, grammar, ult, tor, dico);
		}
	};
} //namespace grape

#endif /*GRAPE_ULTW_FST2_READER*/
