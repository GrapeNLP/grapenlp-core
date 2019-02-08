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

/* array.i */
%module array
%include size_t.i
%include carrays.i
%{
#include <grapenlp/array.h>
%}

namespace grapenlp
{
    %nodefaultctor array;
    %nodefaultdtor array;
    template<typename T>
	class array
	{
    public:
        typedef T*          iterator;
        typedef const T*    const_iterator;
        typedef std::size_t size_type;

        array(size_type count_);
        ~array();
        size_type size() const;
        size_type size_in_bytes() const;
        bool empty() const;
        iterator begin();
        %rename(const_begin) begin() const;
        const_iterator begin() const;
        %rename(const_end) end() const;
        const_iterator end() const;
        const unsigned char* get_bytes() const;
        void set_bytes(unsigned char* bytes);
	};

    %extend array
    {
        const T& get_elem_at(size_type i) const
        { return (*$self)[i]; }
    }
}
