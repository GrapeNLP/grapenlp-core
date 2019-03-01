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

#ifndef GRAPENLP_LT_RTNO_H
#define GRAPENLP_LT_RTNO_H

#include <grapenlp/l_rtno.h>

namespace grapenlp
{
	/**
	 * Recursive transition network with output (RTNO) having lexical masks as input tags and pointers to trie strings
	 * as output. These pointers allow for a more efficient representation and concatenation of strings, using a single
	 * integer to represent a potentially long string, and allowing for the concatenation of characters to strings in
	 * constant time: the original string is not copied with the appended character but a single node is added under the
	 * trie node that represents the last character of the string (see chapter 9 of
	 * http://monge.univ-mlv.fr/~sastre/publications/sastre11t.zip).
	 * @tparam InputIterator the type of the iterator over the RTNO input (e.g. an unichar array iterator)
	 * @tparam Id the character type of the output strings (e.g. unichar)
	 */
	template<typename InputIterator, typename Id, typename ContextKey, typename ContextValue>
	struct lt_rtno
	{
		typedef typename l_rtno<InputIterator, typename trie<Id>::string::const_ref, ContextKey, ContextValue>::type type;
	private:
		lt_rtno(){}
	};

	/**
	 * Partial instantiation of the recursive transition network with output and numbered states for lexical mask input
	 * tags and pointers to trie strings as output. This struct is not to be instantiated but it just serves for
	 * encapsulating the generic data type.
	 * @tparam InputIterator the type of the iterator over the RTNO input (e.g. an unichar array iterator)
	 * @tparam Id the character type of the output strings (e.g. unichar)
	 */
	template<typename InputIterator, typename Id, typename ContextKey, typename ContextValue>
	struct ltns_rtno
	{
		typedef typename lns_rtno<InputIterator, typename trie<Id>::string::const_ref, ContextKey, ContextValue>::type type;
	private:
		ltns_rtno(){}
	};
} //namespace grapenlp

#endif /*GRAPENLP_LT_RTNO_H*/
