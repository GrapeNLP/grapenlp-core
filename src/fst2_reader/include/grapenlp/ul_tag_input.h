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

#ifndef GRAPENLP_UL_TAG_INPUT
#define GRAPENLP_UL_TAG_INPUT

#include <grapenlp/error.h>
#include <grapenlp/lexmask.h>
#include <grapenlp/u_context_mask.h>
#include <grapenlp/trie.h>

namespace grapenlp
{
	enum ul_tag_input_type {EPSILON, CONTEXT, NO_BLANK_EPSILON, BLANK_EPSILON, CONSUMING};

	template<typename InputIterator>
	struct ul_tag_input
	{
		ul_tag_input_type type;
		u_context_mask* context_mask_ref;
		lexmask<InputIterator>* lexmask_ref;

		explicit ul_tag_input(ul_tag_input_type type_): type(type_), context_mask_ref(nullptr), lexmask_ref(nullptr)
		{}

		explicit ul_tag_input(u_context_mask* context_mask_ref_): type(CONTEXT), context_mask_ref(context_mask_ref_), lexmask_ref(nullptr)
		{}

		explicit ul_tag_input(lexmask<InputIterator>* lexmask_ref_): type(CONSUMING), context_mask_ref(nullptr), lexmask_ref(lexmask_ref_)
		{}

#ifdef TRACE
		std::ostream& serialize(std::ostream& out)
		{
			switch (type)
			{
				case EPSILON: return out << "<E>";
				case CONTEXT: return context_mask_ref->serialize(out);
				case NO_BLANK_EPSILON: return out << "#";
				case BLANK_EPSILON: return out << "\\ ";
				case CONSUMING: return lexmask_ref->serialize(out);
				default: fatal_error("Unknown tag input type: %d\n", type);
			}
			return out;
		}
#endif

		~ul_tag_input()
		{
			if (lexmask_ref)
				delete lexmask_ref;
			if (context_mask_ref)
				delete context_mask_ref;
		}
	};

	template<typename Id, typename InputIterator>
	using ul_tag_input_trie = trie_with_ptr_data<Id, ul_tag_input<InputIterator> >;
}//namespace grapenlp

#endif /*GRAPENLP_UL_TAG_INPUT*/
