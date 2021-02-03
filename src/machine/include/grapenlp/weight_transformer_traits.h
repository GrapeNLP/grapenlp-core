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

#ifndef GRAPENLP_WEIGHT_TRANSFORMER_TRAITS_H
#define GRAPENLP_WEIGHT_TRANSFORMER_TRAITS_H

#include <grapenlp/functional.h>

namespace grapenlp
{
	template<typename WeightTransformer>
	struct weight_transformer_traits
	{};

	template<>
	struct weight_transformer_traits<std::plus<char> >
	{
		typedef std::plus<char> Transformer;
		static char identity() { return static_cast<char>(0); }
	};

	template<>
	struct weight_transformer_traits<std::plus<wchar_t> >
	{
		typedef std::plus<wchar_t> Transformer;
		static wchar_t identity() { return 0; }
	};

	template<>
	struct weight_transformer_traits<std::plus<short> >
	{
		typedef std::plus<short> Transformer;
		static short identity() { return 0; }
	};

	template<>
	struct weight_transformer_traits<std::plus<int> >
	{
		typedef std::plus<int> Transformer;
		static int identity() { return 0; }
	};

	template<>
	struct weight_transformer_traits<std::plus<long> >
	{
		typedef std::plus<long> Transformer;
		static long identity() { return 0l; }
	};

	template<>
	struct weight_transformer_traits<std::multiplies<float> >
	{
		typedef std::multiplies<float> Transformer;
		static float identity() { return 1.0f; }
	};

	template<>
	struct weight_transformer_traits<std::multiplies<double> >
	{
		typedef std::multiplies<double> Transformer;
		static double identity() { return 1.0; }
	};

	template<>
	struct weight_transformer_traits<std::multiplies<long double> >
	{
		typedef std::multiplies<long double> Transformer;
		static long double identity() { return 1.0L; }
	};
} //namespace grapenlp

#endif /*GRAPENLP_WEIGHT_TRANSFORMER_TRAITS_H*/
