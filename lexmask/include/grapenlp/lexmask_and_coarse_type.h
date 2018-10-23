/*
 * GRAPENLP
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

#ifndef GRAPENLP_LEXMASK_AND_COARSE_TYPE
#define GRAPENLP_LEXMASK_AND_COARSE_TYPE

#include <grapenlp/error.h>
#include <grapenlp/lexmask.h>
#include <grapenlp/trie.h>

namespace grapenlp
{
	enum coarse_lexmask_type {EPSILON, NO_BLANK_EPSILON, BLANK_EPSILON, CONSUMING};

	template<typename InputIterator>
	struct lexmask_and_coarse_type
	{
		lexmask<InputIterator>* lexmask_ref;
		coarse_lexmask_type type;

		lexmask_and_coarse_type(lexmask<InputIterator>* lexmask_ref_, coarse_lexmask_type type_): lexmask_ref(lexmask_ref_), type(type_)
		{}

		std::ostream& serialize(std::ostream& out)
		{
			switch (type)
			{
				case EPSILON: return out << "<E>";
				case NO_BLANK_EPSILON: return out << "#";
				case BLANK_EPSILON: return out << "\\ ";
				case CONSUMING: return lexmask_ref->serialize(out);
				default: fatal_error("Unknown lexmask coarse type: %d\n", type);
			}
			return out;
		}

		~lexmask_and_coarse_type()
		{
			if (lexmask_ref)
				delete lexmask_ref;
		}
	};

	template<typename Id, typename InputIterator>
	class l_trie: public trie_with_ptr_data<Id, lexmask_and_coarse_type<InputIterator> >
	{
	public:
		typedef trie_with_ptr_data<Id, lexmask_and_coarse_type<InputIterator> > base_type;

	protected:
		//Constructor used by derived classes in order to provide a specialized epsilon string
		l_trie(typename base_type::string::ref s): base_type(s)
		{}

	public:
		l_trie(): base_type()
		{}
	};
}//namespace grapenlp

#endif /*GRAPENLP_LEXMASK_AND_COARSE_TYPE*/
