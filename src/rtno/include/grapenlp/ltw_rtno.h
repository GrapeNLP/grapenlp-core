/*
 * GRAPENLP
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

#ifndef GRAPENLP_LTW_RTNO_H
#define GRAPENLP_LTW_RTNO_H

#include <grapenlp/l_rtno.h>
#include <grapenlp/trie_string_const_ref_x_weight.h>

namespace grapenlp
{
	/**
	 * Recursive transition network with output (RTNO) having lexical masks as input tags and weighted pointers to trie
	 * strings as output. The weights represent either scores or probabilities which can be used to rank the different
	 * outputs generated. The trie string pointesr allow for a more efficient representation and concatenation of
	 * strings, using a single integer to represent a potentially long string, and allowing for the concatenation of
	 * characters to strings in constant time: the original string is not copied with the appended character but a
	 * single node is added under the trie node that represents the last character of the string (see chapter 9 of
	 * http://monge.univ-mlv.fr/~sastre/publications/sastre11t.zip).
	 * @tparam InputIterator the type of the iterator over the RTNO input (e.g. an unichar array iterator)
	 * @tparam Id the character type of the output strings (e.g. unichar)
	 * @tparam Weight the type of the output score (e.g. int) or probability (e.g. float)
	 */
	template<typename InputIterator, typename Id, typename Weight, typename ContextKey, typename ContextValue>
	struct ltw_rtno
	{
		typedef typename l_rtno<InputIterator, trie_string_const_ref_x_weight<Id, Weight>, ContextKey, ContextValue>::type type;
	private:
		ltw_rtno(){}
	};

	/**
	 * Partial instantiation of the recursive transition network with output and numbered states for lexical mask input
	 * tags and weighted pointers to trie strings as output. This struct is not to be instantiated but it just serves
	 * for encapsulating the generic data type.
	 * @tparam InputIterator the type of the iterator over the RTNO input (e.g. an unichar array iterator)
	 * @tparam Id the character type of the output strings (e.g. unichar)
	 * @tparam Weight the type of the output score (e.g. int) or probability (e.g. float)
	 */
	template<typename InputIterator, typename Id, typename Weight, typename ContextKey, typename ContextValue>
	struct ltwns_rtno
	{
		typedef typename lns_rtno<InputIterator, trie_string_const_ref_x_weight<Id, Weight>, ContextKey, ContextValue>::type type;
	private:
		ltwns_rtno(){}
	};
} //namespace grapenlp

#endif /*GRAPENLP_LTW_RTNO_H*/
