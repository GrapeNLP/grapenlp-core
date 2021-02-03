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

#ifndef GRAPENLP_U_TRIE_H
#define GRAPENLP_U_TRIE_H

#include <grapenlp/unicode.h>
#include <grapenlp/trie.h>

namespace grapenlp
{
	typedef trie<unichar> u_trie;
	typedef u_trie::string u_trie_string;
	typedef u_trie_string::ref u_trie_string_ref;
	typedef u_trie_string::const_ref u_trie_string_const_ref;

	template<typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const trie<unichar>::string &s)
	{ return s.serialize(out); }
} //namespace grapenlp

#endif /*GRAPENLP_U_TRIE_H*/
