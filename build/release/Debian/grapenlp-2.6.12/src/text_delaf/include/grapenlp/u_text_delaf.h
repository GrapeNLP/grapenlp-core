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

#ifndef GRAPENLP_U_DELAF_H
#define GRAPENLP_U_DELAF_H

#include <grapenlp/u_delaf_constants.h>
#include <grapenlp/u_set_trie.h>
#include <grapenlp/text_delaf.h>

namespace grapenlp
{
	template<typename CaseNormalizer>
	class u_text_delaf: public text_delaf<unichar, CaseNormalizer>
	{
	public:
		typedef text_delaf<unichar, CaseNormalizer> base_type;
		typedef typename base_type::entry u_entry;

		//Types for lemma and canonical form handling
		typedef typename base_type::entry_list u_entry_list;
		typedef typename base_type::lemma_trie_with_entry_data u_lemma_trie_with_entry_data;
		typedef typename base_type::lemma_string u_lemma_string;


		//Types for semantic traits and clitic pronouns handling
		typedef typename base_type::c_set_trie u_set_trie;
		typedef typename base_type::cst_set ust_set;
		typedef typename base_type::cst_string ust_string;

		//Types for possible flexional traits handling
		typedef typename base_type::c_set u_set;
		typedef typename base_type::flexional_traits_list u_flexional_traits_list;

		u_text_delaf(): base_type()
		{}
	};

	typedef u_text_delaf<u_tolower> tolower_u_text_delaf;
} //namespace grapenlp

#endif /*GRAPENLP_U_DELAF_H*/
