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

#ifndef GRAPENLP_POOL_SEQUENCE_X_WEIGHT_H
#define GRAPENLP_POOL_SEQUENCE_X_WEIGHT_H

#ifdef TRACE
#include <grapenlp/iostream.h>
#endif
#include <grapenlp/pool.h>
#include <grapenlp/array_const_ref_x_weight.h>

namespace grapenlp
{
	template<typename SequencePool, typename Weight>
	struct pool_sequence_x_weight
	{
		typedef SequencePool sequence_pool;
		typedef Weight weight;
		typedef typename pool_traits<sequence_pool>::base_type ps_base_type;
		typedef typename pool_traits<sequence_pool>::value_type ps_value_type;
		typedef pool_sequence_x_weight<sequence_pool, weight> value_type;

		ps_value_type ps;
		Weight w;

		pool_sequence_x_weight(): ps(), w()
		{}
		pool_sequence_x_weight(Weight w_): ps(), w(w_)
		{}
		pool_sequence_x_weight(const ps_value_type &ps_, Weight w_): ps(ps_), w(w_)
		{}
		pool_sequence_x_weight(const value_type &psxw): ps(psxw.ps), w(psxw.w)
		{}

		bool operator<(const value_type &psxw) const
		{
			if (w < psxw.w)
				return true;
			if (psxw.w < w)
				return false;
			return ps < psxw.ps;
		}

		std::ptrdiff_t compare_3w(const value_type &psxw) const
		{
			std::ptrdiff_t result(static_cast<std::ptrdiff_t>(this->w) - static_cast<std::ptrdiff_t>(psxw.w));
			if (result)
				return result;
			return grapenlp::compare_3w<ps_value_type>()(ps, psxw.ps);
		}
	};

#ifdef TRACE
	template<typename SequencePool, typename Weight, typename PoolSequenceSerializer = serializer<typename pool_traits<SequencePool>::value_type> >
	struct pool_sequence_x_weight_serializer
	{
		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& operator()(std::basic_ostream<CharT, Traits> &out, const pool_sequence_x_weight<SequencePool, Weight> &psxw)
		{ return PoolSequenceSerializer()(out << '(', psxw.ps) << ", " << psxw.w << ')'; }
	};
#endif

	template<typename SequencePool, typename WeightTransformer, typename PoolSequenceConcatenator = typename pool_traits<SequencePool>::concatenator>
	struct pool_sequence_x_weight_and_array_const_ref_x_weight_concatenator
	{
		typedef SequencePool sequence_pool;
		typedef typename sequence_pool::value_type sequence_type;
		typedef typename sequence_pool::base_type::value_type char_type;
		typedef WeightTransformer weight_transformer;
		typedef typename weight_transformer::result_type weight;
		typedef PoolSequenceConcatenator pool_sequence_concatenator;

		inline pool_sequence_x_weight<SequencePool, weight>& operator()(pool_sequence_x_weight<SequencePool, weight> &psxw, const array_const_ref_x_weight<char_type, weight> &acrxw)
		{
			if (acrxw.a_cref)
				pool_sequence_concatenator()(psxw.ps, acrxw.a_cref);
			psxw.w = weight_transformer()(psxw.w, acrxw.w);
			return psxw;
		}

    	template<typename SourceRef>
		inline pool_sequence_x_weight<SequencePool, weight>& operator()(pool_sequence_x_weight<SequencePool, weight> &psxw, SourceRef s_ref, const array_const_ref_x_weight<char_type, weight> &acrxw)
		{
			if (acrxw.a_cref)
				pool_sequence_concatenator()(psxw.ps, s_ref, acrxw.a_cref);
			psxw.w = weight_transformer()(psxw.w, acrxw.w);
			return psxw;
		}
	};

	template<typename SequencePool, typename Weight, typename PoolSequenceReverseConcatenator = typename pool_traits<SequencePool>::converse_concatenator>
	struct pool_sequence_x_weight_and_array_const_ref_x_weight_unweighted_converse_concatenator
	{
		typedef SequencePool sequence_pool;
		typedef typename sequence_pool::value_type sequence_type;
		typedef typename sequence_pool::base_type::value_type char_type;
		typedef Weight weight;
		typedef PoolSequenceReverseConcatenator pool_sequence_converse_concatenator;

		inline pool_sequence_x_weight<SequencePool, weight>& operator()(pool_sequence_x_weight<SequencePool, weight> &psxw, const array<char_type> *a_cref)
		{
			if (a_cref)
				pool_sequence_converse_concatenator()(psxw.ps, a_cref);
			return psxw;
		}

    	template<typename SourceRef>
		inline pool_sequence_x_weight<SequencePool, weight>& operator()(pool_sequence_x_weight<SequencePool, weight> &psxw, SourceRef s_ref, const array<char_type> *a_cref)
		{
			if (a_cref)
				pool_sequence_converse_concatenator()(psxw.ps, s_ref, a_cref);
			return psxw;
		}
	};

	template<typename SequencePool, typename WeightTransformer, typename PoolSequenceConcatenator2 = typename pool_traits<SequencePool>::concatenator2>
	struct pool_sequence_x_weight_and_array_const_ref_x_weight_concatenator2
	{
		typedef SequencePool sequence_pool;
		typedef typename sequence_pool::value_type sequence_type;
		typedef typename sequence_pool::base_type::value_type char_type;
		typedef WeightTransformer weight_transformer;
		typedef typename weight_transformer::result_type weight;
		typedef PoolSequenceConcatenator2 pool_sequence_concatenator2;

		inline pool_sequence_x_weight<SequencePool, weight>& operator()(pool_sequence_x_weight<SequencePool, weight> &psxw1, const pool_sequence_x_weight<SequencePool, weight> &psxw2)
		{
			pool_sequence_concatenator2()(psxw1.ps, psxw2.ps);
			psxw1.w = weight_transformer()(psxw1.w, psxw2.w);
			return psxw1;
		}

    	template<typename SourceRef>
		inline pool_sequence_x_weight<SequencePool, weight>& operator()(pool_sequence_x_weight<SequencePool, weight> &psxw1, SourceRef s_ref, const pool_sequence_x_weight<SequencePool, weight> &psxw2)
		{
			pool_sequence_concatenator2()(psxw1.ps, psxw2.ps);
			psxw1.w = weight_transformer()(psxw1.w, psxw2.w);
			return psxw1;
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_POOL_SEQUENCE_X_WEIGHT_H*/
