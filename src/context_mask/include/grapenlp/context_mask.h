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

#ifndef GRAPENLP_CONTEXT_MASK_H
#define GRAPENLP_CONTEXT_MASK_H

#include <grapenlp/context.h>
#include <grapenlp/u_context_mask_constants.h>

namespace grapenlp
{
    template<typename Char>
    class context_mask
    {
    public:
        typedef context<Char> context_type;
        typedef typename context_type::optimized_key optimized_context_key;
        typedef typename context_type::optimized_value optimized_context_value;

    private:
        const optimized_context_key key;
        const optimized_context_value value;

    public:
        context_mask(const optimized_context_key key_, const optimized_context_value value_): key(key_), value(value_)
        {}

        template<typename KeyCharIterator, typename ValueCharIterator>
        context_mask(KeyCharIterator key_begin, KeyCharIterator key_end, ValueCharIterator value_begin, ValueCharIterator value_end, context_type &c):
        key(c.get_optimized_key(key_begin, key_end)), value(c.get_optimized_value(value_begin, value_end))
        {}

    public:
        bool match(const context<Char> &c) const
        {
            return c.equals(key, value);
        }

        std::ostream& serialize(std::ostream& out) const
        { return serialize_context_expression(out << "%"); }

        std::wostream& wserialize(std::wostream& out) const
        { return wserialize_context_expression(out << L"%"); }

        std::ostream& serialize_context_expression(std::ostream& out) const
        { return out << "<@" << key << "=" << value << ">"; }

        std::wostream& wserialize_context_expression(std::wostream& out) const
        { return out << L"<@" << key << L"=" << value << L">"; }

        void u_write(FILE *f) const
        {
            ::u_write(f, context_left_delimiter.begin(), context_left_delimiter.end());
            ::u_write(f, key.begin(), key.end());
            u_fputc('=', f);
            ::u_write(f, value.begin(), value.end());
            ::u_write(f, context_right_delimiter.begin(), context_right_delimiter.end());
        }

        bool operator<(const context_mask &other) const
        {
            if (key < other.key)
                return true;
            if (other.key < key)
                return false;
            return (value < other.value);
        }

        bool operator==(const context_mask &other) const
        {
            return key == other.key && value == other.value;
        }

        ~context_mask(){}
    };
} //namespace grapenlp

#endif /*GRAPENLP_CONTEXT_MASK_H*/
