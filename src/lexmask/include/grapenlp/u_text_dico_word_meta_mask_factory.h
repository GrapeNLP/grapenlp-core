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

#ifndef GRAPENLP_U_TEXT_DICO_WORD_META_MASK_FACTORY_H
#define GRAPENLP_U_TEXT_DICO_WORD_META_MASK_FACTORY_H

#include <grapenlp/u_dico_word_meta_mask_factory.h>
#include <grapenlp/u_text_delaf_entry_filter_factory.h>

namespace grapenlp
{
	template<typename InputIterator, typename CaseNormalizer=u_tolower>
	struct u_text_dico_word_meta_mask_factory: public u_dico_word_meta_mask_factory<InputIterator>
	{
		u_text_delaf<CaseNormalizer> &dico;

		u_text_dico_word_meta_mask_factory(u_text_delaf<CaseNormalizer> &dico_): dico(dico_)
		{}

		lexmask<InputIterator>* operator()(u_array::const_iterator meta_code_begin, u_array::const_iterator meta_code_end) const
		{ return new constrained_text_dico_word_meta_mask<InputIterator, CaseNormalizer>(dico, make_u_text_delaf_entry_filter<CaseNormalizer, u_array::const_iterator>(meta_code_begin, meta_code_end, dico)); }
	};
} //namespace grapenlp

#endif /*GRAPENLP_U_TEXT_DICO_WORD_META_MASK_FACTORY_H*/
