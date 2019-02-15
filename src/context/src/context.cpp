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

#include <grapenlp/context.h>

namespace grapenlp
{
    context::context(): keys(), values(), the_map()
    {}

    std::size_t size()
    {
        return the_map.size();
    }

    ua_trie_string_const_ref context::get_key_const_ref(const u_array &key)
    {

    }

    ua_trie_string_const_ref context::get_value_const_ref(const u_array &value)
    {}

    void context::set(ua_trie_string_const_ref key_const_ref, ua_trie_string_const_ref value_const_ref)
    {
        the_map[key_const_ref] = value_const_ref;
    }

    bool context::equals(ua_trie_string_const_ref key_const_ref, ua_trie_string_const_ref value_const_ref)
    {
        map_const_iterator it(the_map.find(key_const_ref));
        return it != the_map.end() && *it == value_const_ref;
    }

    bool context::not_equals(ua_trie_string_const_ref key_const_ref, ua_trie_string_const_ref value_const_ref)
    {
        map_const_iterator it(the_map.find(key_const_ref));
        return it == the_map.end() || *it != value_const_ref;
    }

    context::~context()
    {}
} //namespace grapenlp
