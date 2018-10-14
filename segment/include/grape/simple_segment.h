/*
 * GRAPE
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

#ifndef GRAPE_SIMPLE_SEGMENT_H
#define GRAPE_SIMPLE_SEGMENT_H

#include <memory>

#include <grape/array.h>
#include <grape/segment.h>

namespace grape
{
    template<typename InputIterator>
    using token_iterator = typename token<InputIterator>::ref_list::const_iterator;

    template<typename Id>
    using name_string_const_ref = typename out_bound<Id>::name_string_const_ref;

	template<typename InputIterator, typename Id>
	struct simple_segment
	{
		typedef typename out_bound<Id>::name_string_const_ref name_string_const_ref;

        name_string_const_ref name;
		std::size_t begin;
		std::size_t end;

		simple_segment(): name(), begin(), end()
		{}
	};

    template<typename InputIterator, typename Id>
    void reset_simple_segment(simple_segment<InputIterator, Id> &ss, InputIterator input_begin, InputIterator input_end, token_iterator<InputIterator> token_begin, token_iterator<InputIterator> token_end, name_string_const_ref<Id> _name, const segment<token_iterator<InputIterator> > &s)
    {
        ss.name = _name;
        ss.begin = std::distance(input_begin, input_end);
        ss.end = 0;

        if (s.get_begin() != token_end)
            ss.begin = std::distance(input_begin, (*s.get_begin())->begin);
        if (s.get_end() != token_begin)
        {
            token_iterator<InputIterator> before_token_end(s.get_end());
            --before_token_end;
            ss.end = std::distance(input_begin, (*before_token_end)->end);
        }
    }

    template<typename InputIterator, typename Id>
    using simple_segment_array = array<simple_segment<InputIterator, Id> >;

    template<typename InputIterator, typename Id, assoc_container_impl_choice acic>
    void reset_simple_segment_array(simple_segment_array<InputIterator, Id> &ssa, InputIterator input_begin, InputIterator input_end, token_iterator<InputIterator> token_begin, token_iterator<InputIterator> token_end, const segment_map<token_iterator<InputIterator>, Id, acic> &sm)
    {
        std::unique_ptr<simple_segment<InputIterator, Id>[]> ref(new simple_segment<InputIterator, Id>[sm.size()]);
        typename segment_map<token_iterator<InputIterator>, Id, acic>::const_iterator i(sm.begin());
        simple_segment<InputIterator, Id> *j = ref.get();
        for (;i != sm.end(); ++i, ++j)
            reset_simple_segment<InputIterator, Id>(*j, input_begin, input_end, token_begin, token_end, i->first, i->second);
        ssa.reset(ref.release(), sm.size());
    }
} //namespace grape

#endif /*GRAPE_SIMPLE_SEGMENT_H*/
