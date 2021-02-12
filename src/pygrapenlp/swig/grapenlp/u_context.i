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

/* u_context.i */
%module u_context
%include u_array.i
%include context.i
%{
#include <grapenlp/u_array.h>
#include <grapenlp/u_context.h>
%}

namespace grapenlp
{
    %extend context {
        %template(ua_set) set<::grapenlp::u_array::const_iterator, ::grapenlp::u_array::const_iterator>;
    }

    typedef ::grapenlp::context<unichar> u_context;
    %template(u_context) ::grapenlp::context<unichar>;
}
