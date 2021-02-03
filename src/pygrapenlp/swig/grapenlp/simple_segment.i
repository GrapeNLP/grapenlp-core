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

/* simple_segment.i */
%module simple_segment
%include u_array.i
%include u_out_bound.i
%{
#include <grapenlp/simple_segment.h>

namespace grapenlp
{
    typedef ::grapenlp::simple_segment<::grapenlp::array<unichar>::const_iterator, unichar> uau_simple_segment;
    typedef ::grapenlp::array<::grapenlp::simple_segment<::grapenlp::array<unichar>::const_iterator, unichar> > uau_simple_segment_array;
}
%}

namespace grapenlp
{
    %nodefaultctor simple_segment;
    %nodefaultdtor simple_segment;
	template<typename InputIterator, typename Id>
	class simple_segment
	{
    public:
		typedef typename out_bound<Id>::name_string_const_ref name_string_const_ref;

        name_string_const_ref name;
		std::size_t begin;
		std::size_t end;

		simple_segment();
        ~simple_segment();
	};

    typedef ::grapenlp::simple_segment<::grapenlp::array<unichar>::const_iterator, unichar> uau_simple_segment;
    %template(uau_simple_segment) ::grapenlp::simple_segment<::grapenlp::array<unichar>::const_iterator, unichar>;

    typedef ::grapenlp::array<::grapenlp::simple_segment<::grapenlp::array<unichar>::const_iterator, unichar> > uau_simple_segment_array;
    %template(uau_simple_segment_array) ::grapenlp::array<::grapenlp::simple_segment<::grapenlp::array<unichar>::const_iterator, unichar> >;
}
