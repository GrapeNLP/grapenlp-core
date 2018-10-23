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

#ifndef GRAPENLP_TRIE_STRING_CONST_REF_X_WEIGHT_H
#define GRAPENLP_TRIE_STRING_CONST_REF_X_WEIGHT_H

#include <grapenlp/trie.h>

namespace grapenlp
{
	template<typename T, typename Weight>
	struct trie_string_const_ref_x_weight
	{
		typedef trie_string_const_ref_x_weight<T, Weight> this_type;
		typedef typename trie<T>::string::const_ref trie_string_const_ref;
		trie_string_const_ref ts_cref;
		Weight w;

		trie_string_const_ref_x_weight(): ts_cref(), w()
		{}
		trie_string_const_ref_x_weight(Weight w_): ts_cref(), w(w_)
		{}
		trie_string_const_ref_x_weight(trie_string_const_ref ts_cref_, Weight w_): ts_cref(ts_cref_), w(w_)
		{}
		trie_string_const_ref_x_weight(const this_type &ts_crefxw): ts_cref(ts_crefxw.ts_cref), w(ts_crefxw.w)
		{}

		//Return true if there is an output trie_string_const_ref defined and/or a non-zero weight
//		operator bool() const
//		{ return ts_cref || w; }

		bool operator<(const trie_string_const_ref_x_weight &ts_crefxw) const
		{
			if (ts_cref < ts_crefxw.ts_cref)
				return true;
			if (ts_crefxw.ts_cref < ts_cref)
				return false;
			return w < ts_crefxw.w;
		}
	};

	template<typename T, typename Weight, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const trie_string_const_ref_x_weight<T, Weight> &ts_crefxw)
	{
		//If the trie string is defined, serialize it
		if (ts_crefxw.ts_cref)
			out << *ts_crefxw.ts_cref;
		//Serialize weight (it is always defined, default weight is 0)
		if (ts_crefxw.w >= static_cast<Weight>(0))
			out << '+';
		return out << ts_crefxw.w;
	}
} //namespace grapenlp

#endif /*GRAPENLP_TRIE_STRING_CONST_REF_X_WEIGHT_H*/
