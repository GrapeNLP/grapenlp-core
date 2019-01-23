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

#ifndef GRAPENLP_OUT_BOUND_CONST_REF_X_WEIGHT_H
#define GRAPENLP_OUT_BOUND_CONST_REF_X_WEIGHT_H

#include <grapenlp/out_bound.h>

namespace grapenlp
{
	template<typename T, typename Weight>
	struct out_bound_const_ref_x_weight_weight_getter;

	template<typename T, typename Weight>
	struct out_bound_const_ref_x_weight_non_weight_getter;

	template<typename T, typename Weight>
	struct out_bound_const_ref_x_weight
	{
		typedef Weight weight;
		typedef typename out_bound<T>::const_ref non_weight;
		typedef out_bound_const_ref_x_weight_weight_getter<T, Weight> weight_getter;
		typedef out_bound_const_ref_x_weight_non_weight_getter<T, Weight> non_weight_getter;

		typename out_bound<T>::const_ref ob_cref;
		weight w;

		out_bound_const_ref_x_weight(): ob_cref(), w()
		{}
		out_bound_const_ref_x_weight(Weight w_): ob_cref(), w(w_)
		{}
		out_bound_const_ref_x_weight(typename out_bound<T>::const_ref ob_cref_, Weight w_): ob_cref(ob_cref_), w(w_)
		{}
		out_bound_const_ref_x_weight(const out_bound_const_ref_x_weight &obcrxw): ob_cref(obcrxw.ob_cref), w(obcrxw.w)
		{}

		bool operator<(const out_bound_const_ref_x_weight &obcrxw) const
		{
			if (ob_cref < obcrxw.ob_cref)
				return true;
			if (obcrxw.ob_cref < ob_cref)
				return false;
			return w < obcrxw.w;
		}

		std::ptrdiff_t compare_3w(const out_bound_const_ref_x_weight &obcrxw) const
		{
			std::ptrdiff_t result(ob_cref.compare_3w(obcrxw.ob_cref));
			if (result)
				return result;
			return (static_cast<std::ptrdiff_t>(this->w) - static_cast<std::ptrdiff_t>(obcrxw.w));
		}
	};

	template<typename T, typename Weight, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const out_bound_const_ref_x_weight<T, Weight> &obcrxw)
	{
		//If the out bound is defined, serialize it
		if (obcrxw.ob_cref)
			out << *obcrxw.ob_cref;
		//Serialize weight (it is always defined)
		if (obcrxw.w >= static_cast<Weight>(0))
			out << '+';
		return out << obcrxw.w;
	}

	template<typename T, typename Weight>
	struct out_bound_const_ref_x_weight_weight_getter
	{
		inline Weight operator() (const out_bound_const_ref_x_weight<T, Weight> &obcrxw) const
		{ return obcrxw.w; }
	};

	template<typename T, typename Weight>
	struct out_bound_const_ref_x_weight_non_weight_getter
	{
		inline typename out_bound<T>::const_ref operator() (const out_bound_const_ref_x_weight<T, Weight> &obcrxw) const
		{ return obcrxw.ob_cref; }
	};
} //namespace grapenlp

#endif /*GRAPENLP_OUT_BOUND_CONST_REF_X_WEIGHT_H*/
