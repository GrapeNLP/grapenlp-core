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

#ifndef GRAPENLP_ARRAY_CONST_REF_X_WEIGHT_H
#define GRAPENLP_ARRAY_CONST_REF_X_WEIGHT_H

#include <grapenlp/array.h>

namespace grapenlp
{
	template<typename T, typename Weight>
	struct array_const_ref_x_weight_weight_getter;

	template<typename T, typename Weight>
	struct array_const_ref_x_weight_non_weight_getter;

	template<typename T, typename Weight>
	struct array_const_ref_x_weight
	{
		typedef Weight weight;
		typedef const array<T>* non_weight;
		typedef array_const_ref_x_weight_weight_getter<T, Weight> weight_getter;
		typedef array_const_ref_x_weight_non_weight_getter<T, Weight> non_weight_getter;

		const array<T>* a_cref;
		Weight w;

		array_const_ref_x_weight(): a_cref(), w()
		{}
		array_const_ref_x_weight(Weight w_): a_cref(), w(w_)
		{}
		array_const_ref_x_weight(const array<T>* a_cref_, Weight w_): a_cref(a_cref_), w(w_)
		{}
		array_const_ref_x_weight(const array_const_ref_x_weight &acrxw): a_cref(acrxw.a_cref), w(acrxw.w)
		{}

		//Return true if there is an output array defined and/or a non-zero weight
//		operator bool() const
//		{ return a_cref || w; }

		bool operator<(const array_const_ref_x_weight &acrxw) const
		{
			if (a_cref < acrxw.a_cref)
				return true;
			if (acrxw.a_cref < a_cref)
				return false;
			return w < acrxw.w;
		}
	};

	template<typename T, typename Weight, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const array_const_ref_x_weight<T, Weight> &acrxw)
	{
		//If the out bound is defined, serialize it
		if (acrxw.a_cref)
			out << *acrxw.a_cref;
		//Serialize weight (it is always defined, default weight is 0)
		if (acrxw.w >= static_cast<Weight>(0))
			out << '+';
		return out << acrxw.w;
	}

	template<typename T, typename Weight>
	struct array_const_ref_x_weight_weight_getter
	{
		Weight operator() (const array_const_ref_x_weight<T, Weight> &acrxw) const
		{ return acrxw.w; }
	};

	template<typename T, typename Weight>
	struct array_const_ref_x_weight_non_weight_getter
	{
		const array<T>* operator() (const array_const_ref_x_weight<T, Weight> &acrxw) const
		{ return acrxw.a_cref; }
	};
} //namespace grapenlp

#endif /*GRAPENLP_ARRAY_CONST_REF_X_WEIGHT_H*/
