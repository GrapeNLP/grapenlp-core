/*
 * GRAPENLP
 *
 * Copyright (C) 2011-2012 Universidad de Alicante <javier.sastre@gmail.com>
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

#ifndef GRAPENLP_ULTW_FST2_READER_H
#define GRAPENLP_ULTW_FST2_READER_H

#include <grapenlp/weight_transformer_traits.h>
#include <grapenlp/lutw_rtno.h>
#include <grapenlp/tw_fst2_tag_output_reader.h>
#include <grapenlp/ul_fst2_reader.h>

namespace grapenlp
{
	template<typename InputIterator, typename WeightTransformer, typename CaseNormalizer=u_tolower>
	struct ultw_fst2_reader: public ul_fst2_reader<InputIterator, tw_fst2_tag_output_reader<WeightTransformer>, CaseNormalizer>
	{
		typedef ul_fst2_reader<InputIterator, tw_fst2_tag_output_reader<WeightTransformer>, CaseNormalizer> base_type;
		typedef typename base_type::machine machine;

		int operator() (FILE *f, machine &grammar, ul_tag_input_trie<unichar, InputIterator> &ult, u_trie &ut, u_text_delaf<CaseNormalizer> &dico, u_context_key_value_hasher &c_hasher)
		{
			tw_fst2_tag_output_reader<WeightTransformer> tor(ut);
			return base_type::operator() (f, grammar, ult, tor, dico, c_hasher);
		}

		int operator() (FILE *f, machine &grammar, ul_tag_input_trie<unichar, InputIterator> &ult, u_trie &ut, compressed_delaf &dico, u_context_key_value_hasher &c_hasher)
		{
			tw_fst2_tag_output_reader<WeightTransformer> tor(ut);
			return base_type::operator() (f, grammar, ult, tor, dico, c_hasher);
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_ULTW_FST2_READER*/
