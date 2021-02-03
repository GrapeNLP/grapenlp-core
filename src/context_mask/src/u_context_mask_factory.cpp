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

#include <grapenlp/u_context_mask_factory.h>

namespace grapenlp
{
    /**
     * Parses a context expression and returns the corresponding unicode context mask
     * @param context_expression_begin iterator pointing at the first character of the context expression right after
     * the left context expression delimiter
     * @param context_expression_end iterator pointing right after the last character of the context expression, that
     * is, the first character of the right context expression delimiter
     * @param c the context object that will later be used in the grammar application (needed to convert context keys
     * and values to trie strings)
     * @return a pointer to a context mask corresponding to the context expression given by the range
     * [context_expression_begin, context_expression_end)
     */
    u_context_mask* make_u_context_mask(u_array::const_iterator context_expression_begin, u_array::const_iterator context_expression_end, u_context_key_value_hasher &c_hasher)
    {
        u_array::const_iterator context_key_begin(context_expression_begin);
        //Skip whites before context right delimiter
        while (u_is_white(*(context_expression_end - 1)))
            --context_expression_end;
        //Skip whites before key begin
        while (context_key_begin != context_expression_end && u_is_white(*context_key_begin))
            ++context_key_begin;
        if (context_key_begin == context_expression_end)
            fatal_error("Context mask without key or value\n");
        if (!u_is_letter(*context_key_begin))
            fatal_error("Context key doesn't start with a letter\n");
        //Find key end
        u_array::const_iterator context_key_end(context_key_begin + 1);
        //Skip valid key chars
        while (context_key_end != context_expression_end && (u_is_letter(*context_key_end) || u_is_digit(*context_key_end) || *context_key_end == '_'))
            ++context_key_end;
        if (context_key_end == context_expression_end || (!u_is_white(*context_key_end) && *context_key_end != '='))
            fatal_error("Context mask without equal symbol after key\n");
        u_array::const_iterator context_value_begin = context_key_end;
        //Skip whites after key
        while (context_value_begin != context_expression_end && u_is_white(*context_value_begin))
            ++context_value_begin;
        if (context_value_begin == context_expression_end || *context_value_begin != '=')
            fatal_error("Context mask without equal symbol after key\n");
        ++context_value_begin;
        //Skip whites after equal sign
        while (context_value_begin != context_expression_end && u_is_white(*context_value_begin))
            ++context_value_begin;
        if (context_value_begin == context_expression_end)
            fatal_error("Context mask without value\n");
        u_array::const_iterator context_value_end(context_value_begin + 1);
        //Skip valid value chars
        while (context_value_end != context_expression_end && !u_is_white(*context_value_end))
            ++context_value_end;
        if (context_value_end != context_expression_end)
            fatal_error("Context value contains whites");
        u_context_key_value_hasher::hash_type key_hash(c_hasher.key_hasher.insert(context_key_begin, context_key_end).data);
        u_context_key_value_hasher::hash_type value_hash(c_hasher.value_hasher.insert(context_value_begin, context_value_end).data);
#ifdef TRACE
        return new u_context_mask(key_hash, value_hash, context_key_begin, context_key_end, context_value_begin, context_value_end);
#else
        return new u_context_mask(key_hash, value_hash);
#endif
    }
} //namespace grapenlp
