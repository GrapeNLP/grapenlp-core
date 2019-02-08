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

/* simple_segment_array_x_weight.i */
%module simple_segment_array_x_weight
%include simple_segment.i
%{
#include <grapenlp/simple_segment_array_x_weight.h>

namespace grapenlp
{
    typedef ::grapenlp::simple_segment_array_x_weight<::grapenlp::array<unichar>::const_iterator, unichar, int> uaui_simple_segment_array_x_weight;
    typedef ::grapenlp::array<::grapenlp::simple_segment_array_x_weight<::grapenlp::array<unichar>::const_iterator, unichar, int> > uaui_simple_segment_array_x_weight_array;
}
%}

namespace grapenlp
{
    %nodefaultctor simple_segment_array_x_weight;
    %nodefaultdtor simple_segment_array_x_weight;
	template<typename InputIterator, typename Id, typename Weight>
	class simple_segment_array_x_weight
    {
    public:
		::grapenlp::uau_simple_segment_array ssa;
		Weight w;

        simple_segment_array_x_weight();
        ~simple_segment_array_x_weight();
    };

    typedef ::grapenlp::simple_segment_array_x_weight<::grapenlp::array<unichar>::const_iterator, unichar, int> uaui_simple_segment_array_x_weight;
    %template(uaui_simple_segment_array_x_weight) ::grapenlp::simple_segment_array_x_weight<::grapenlp::array<unichar>::const_iterator, unichar, int>;

    typedef ::grapenlp::array<::grapenlp::simple_segment_array_x_weight<::grapenlp::array<unichar>::const_iterator, unichar, int> > uaui_simple_segment_array_x_weight_array;
    %template(uaui_simple_segment_array_x_weight_array) ::grapenlp::array<::grapenlp::simple_segment_array_x_weight<::grapenlp::array<unichar>::const_iterator, unichar, int> >;
}
