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

#ifndef GRAPENLP_U_COMPRESSED_DICO_WORD_META_MASK_FACTORY_H
#define GRAPENLP_U_COMPRESSED_DICO_WORD_META_MASK_FACTORY_H


#include <grapenlp/normalizer_iterator.h>
#include <grapenlp/u_dico_word_meta_mask_factory.h>
#include <grapenlp/compressed_delaf_entry_filter_factory.h>

namespace grapenlp
{
	template<typename InputIterator, typename CaseNormalizer=u_tolower>
	struct u_compressed_dico_word_meta_mask_factory: public u_dico_word_meta_mask_factory<InputIterator>
	{
		compressed_delaf &dico;

		u_compressed_dico_word_meta_mask_factory(compressed_delaf &dico_): dico(dico_)
		{}

		lexmask_and_coarse_type<InputIterator>* operator() (u_array::const_iterator meta_code_begin, u_array::const_iterator meta_code_end) const
		{ return new lexmask_and_coarse_type<InputIterator>(new constrained_compressed_dico_word_meta_mask<InputIterator, CaseNormalizer>(dico, make_compressed_delaf_entry_filter<CaseNormalizer, u_array::const_iterator, normalizer_iterator<CaseNormalizer, InputIterator> >(meta_code_begin, meta_code_end, dico)), CONSUMING); }
	};
} //namespace grapenlp

#endif /*GRAPENLP_U_COMPRESSED_DICO_WORD_META_MASK_FACTORY_H*/
