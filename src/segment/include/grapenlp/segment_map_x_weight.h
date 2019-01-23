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

#ifndef GRAPENLP_SEGMENT_MAP_X_WEIGHT_H
#define GRAPENLP_SEGMENT_MAP_X_WEIGHT_H

#include <grapenlp/segment.h>
#include <grapenlp/out_bound_const_ref_x_weight.h>

namespace grapenlp
{
	template<typename SourceRef, typename Id, typename Weight, assoc_container_impl_choice acic>
	struct segment_map_x_weight
	{
		typedef segment_map_x_weight* ref;

		segment_map<SourceRef, Id, acic> sm;
		Weight w;

		segment_map_x_weight(): sm(), w()
		{}

		segment_map_x_weight(Weight w_): sm(), w(w_)
		{}

		segment_map_x_weight(const segment_map<SourceRef, Id, acic> &sm_, Weight w_): sm(sm_), w(w_)
		{}

		segment_map_x_weight(const segment_map_x_weight &smxw): sm(smxw.sm), w(smxw.w)
		{}

		bool operator< (const segment_map_x_weight &smxw) const
		{
			//Greater instead of less so that top ranked segment maps come first!!
			if (w > smxw.w)
				return true;
			if (w < smxw.w)
				return false;
			return sm < smxw.sm;
		}

		std::ptrdiff_t compare_3w(const segment_map_x_weight &smxw) const
		{
			//Greater instead of less so that top ranked segment maps come first!!
			std::ptrdiff_t result(static_cast<std::ptrdiff_t>(smxw.w) - static_cast<std::ptrdiff_t>(this->w));
			if (result)
				return result;
			return sm.compare_3w(smxw.sm);
		}
	};

	template<typename SourceRef, typename Id, typename Weight, assoc_container_impl_choice acic, typename CharT, typename Traits>
	inline std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const segment_map_x_weight<SourceRef, Id, Weight, acic> &smxw)
	{ return out << '(' << smxw.sm << ", " << smxw.w << ')'; }

	template<typename SourceRef, typename Id, typename WeightTransformer, assoc_container_impl_choice acic>
	struct segment_map_x_weight_transformer: public segment_map_transformer<SourceRef, Id, acic>
	{
		typedef segment_map_transformer<SourceRef, Id, acic> base_type;
		typedef WeightTransformer weight_transformer;
		typedef typename WeightTransformer::result_type weight;

		segment_map_x_weight_transformer(): base_type()
		{}

		segment_map_x_weight_transformer(SourceRef begin_src_ref_, SourceRef end_src_ref_): base_type(begin_src_ref_, end_src_ref_)
		{}

		segment_map_x_weight<SourceRef, Id, weight, acic>& operator() (segment_map_x_weight<SourceRef, Id, weight, acic> &smxw, SourceRef src_ref, const out_bound_const_ref_x_weight<Id, weight> &obcrxw) const
		{
			if (obcrxw.ob_cref)
				base_type::operator()(smxw.sm, src_ref, obcrxw.ob_cref);
			smxw.w = weight_transformer()(smxw.w, obcrxw.w);
			return smxw;
		}
	};

	template<typename SourceRef, typename Id, typename WeightComposer, assoc_container_impl_choice acic>
	struct segment_map_x_weight_composer
	{
		typedef WeightComposer weight_composer;
		typedef typename weight_composer::result_type weight;
		typedef segment_map_x_weight<SourceRef, Id, weight, acic> blackboard;

		segment_map_composer<SourceRef, Id, acic> sm_circ;

		blackboard& operator() (blackboard &smxw1, const blackboard &smxw2) const
		{
			sm_circ(smxw1.sm, smxw2.sm);
			smxw1.w = weight_composer()(smxw1.w, smxw2.w);
			return smxw1;
		}
	};

	template<typename SourceRef, typename Id, typename Weight, assoc_container_impl_choice acic>
	struct segment_map_x_weight_unweighted_converse_transformer: public segment_map_converse_transformer<SourceRef, Id, acic>
	{
		typedef segment_map_converse_transformer<SourceRef, Id, acic> base_type;

		segment_map_x_weight_unweighted_converse_transformer(): base_type()
		{}

		segment_map_x_weight_unweighted_converse_transformer(SourceRef begin_src_ref_, SourceRef end_src_ref_): base_type(begin_src_ref_, end_src_ref_)
		{}

		segment_map_x_weight<SourceRef, Id, Weight, acic>& operator() (segment_map_x_weight<SourceRef, Id, Weight, acic> &smxw, SourceRef src_ref, typename out_bound<Id>::const_ref ob_cref) const
		{
			if (ob_cref)
				base_type::operator()(smxw.sm, src_ref, ob_cref);
			return smxw;
		}
	};
}

#endif /*GRAPENLP_SEGMENT_MAP_WEIGHT_H*/
