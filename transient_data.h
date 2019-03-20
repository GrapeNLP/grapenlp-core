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

#ifndef GRAPENLP_TRANSIENT_DATA_H
#define GRAPENLP_TRANSIENT_DATA_H

namespace grapenlp
{
    template<typename InputIterator>
    struct transient_data
    {
        typename token<InputIterator>::ref_list the_token_list;
        bool hasnt_white_at_begin;
        bool hasnt_white_at_end;
        assoc_container_impl_choice the_output_set_impl_choice;
        void *output_set_ref;
    #if SIMPLIFIED_OUTPUT
        simple_segment_array_x_weight_array<InputIterator, unichar, weight> simplified_weighted_output;
    #endif
    #if defined(SERIALIZED_OUTPUT)
        u_array ua;
    #endif

        transient_data()
        {
            the_token_list(),
            hasnt_white_at_begin(true),
            hasnt_white_at_end(true),
            the_output_set_impl_choice(LRB_TREE_3W),
            output_set_ref(NULL),
#ifdef SIMPLIFIED_OUTPUT
            simplified_weighted_output(),
#endif
#if defined(SERIALIZED_OUTPUT)
            ua(),
#endif
            the_parse_func_ref(NULL),
            the_parse_and_get_fprtn_stats_func_ref(NULL)
        }

        ~transient_data() {
            if (output_set_ref)
                delete_output_set();
        }
    };
} //namespace grapenlp
#endif //GRAPENLP_TRANSIENT_DATA_H
