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

#ifndef GRAPENLP_SIMPLE_SEGMENT_ARRAY_X_WEIGHT_H
#define GRAPENLP_SIMPLE_SEGMENT_ARRAY_X_WEIGHT_H

#include <grapenlp/segment_map_x_weight.h>
#include <grapenlp/simple_segment.h>
#include <grapenlp/set_impl_selector.h>

namespace grapenlp
{
	template<typename InputIterator, typename Id, typename Weight>
	struct simple_segment_array_x_weight
	{
		simple_segment_array<InputIterator, Id> ssa;
		Weight w;

		simple_segment_array_x_weight(): ssa(), w()
		{}
	};

    template<typename InputIterator, typename Id, typename Weight, assoc_container_impl_choice acic>
    void reset_simple_segment_array_x_weight(simple_segment_array_x_weight<InputIterator, Id, Weight> &ssaw, InputIterator input_begin, InputIterator input_end, token_iterator<InputIterator> token_begin, token_iterator<InputIterator> token_end, const segment_map_x_weight<token_iterator<InputIterator>, Id, Weight, acic> &smxw)
    {
        reset_simple_segment_array<InputIterator, Id, acic>(ssaw.ssa, input_begin, input_end, token_begin, token_end, smxw.sm);
        ssaw.w = smxw.w;
    }

	template<typename InputIterator, typename Id, typename Weight>
    using simple_segment_array_x_weight_array = array<simple_segment_array_x_weight<InputIterator, Id, Weight> >;

    template<typename InputIterator, typename Id, typename Weight, assoc_container_impl_choice acic>
    void reset_simple_segment_array_x_weight_array(simple_segment_array_x_weight_array<InputIterator, Id, Weight> &ssawa, InputIterator input_begin, InputIterator input_end, token_iterator<InputIterator> token_begin, token_iterator<InputIterator> token_end, const typename set_impl_selector<acic, segment_map_x_weight<token_iterator<InputIterator>, Id, Weight, acic> >::type &smws)
    {
        std::unique_ptr<simple_segment_array_x_weight<InputIterator, Id, Weight>[]> ref(new simple_segment_array_x_weight<InputIterator, Id, Weight>[smws.size()]);
        typename set_impl_selector<acic, segment_map_x_weight<token_iterator<InputIterator>, Id, Weight, acic> >::type::const_iterator i(smws.begin());
        simple_segment_array_x_weight<InputIterator, Id, Weight> *j = ref.get();
        for (;i != smws.end(); ++i, ++j)
            reset_simple_segment_array_x_weight<InputIterator, Id, Weight, acic>(*j, input_begin, input_end, token_begin, token_end, *i);
        ssawa.reset(ref.release(), smws.size());
    }
}

#endif /*GRAPENLP_SIMPLE_SEGMENT_ARRAY_X_WEIGHT_H*/
