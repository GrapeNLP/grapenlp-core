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

#ifndef GRAPENLP_CONTEXT_H
#define GRAPENLP_CONTEXT_H

#include <map>

#include <grapenlp/u_array.h>
#include <grapenlp/u_trie.h>

namespace grapenlp
{
    class context
    {
    public:
        typedef trie_with_ptr_data<unichar, u_array> ua_trie;
        typedef trie_with_ptr_data<unichar, u_array>::string ua_trie_string;
        typedef trie_with_ptr_data<unichar, u_array>::string::const_ref ua_trie_string_const_ref;
        typedef std::map<ua_trie_string_const_ref, ua_trie_string_const_ref> map;
        typedef map::const_iterator map_const_iterator;

    private:
        ua_trie keys;
        ua_trie values;
        map the_map;

    public:
        context();

        std::size_t size() const;

        ua_trie_string_const_ref get_key_const_ref(const u_array &key);
        ua_trie_string_const_ref get_value_const_ref(const u_array &value);

        bool set_context_value(ua_trie_string_const_ref key_const_ref, ua_trie_const_ref value_const_ref);
        bool equals(ua_trie_string_const_ref key_const_ref, ua_trie_const_ref value_const_ref);
        bool not_equals(ua_trie_string_const_ref key_const_ref, ua_trie_const_ref value_const_ref);

        ~context();
    };
} //namespace grapenlp

#endif /*GRAPENLP_CONTEXT_H*/
