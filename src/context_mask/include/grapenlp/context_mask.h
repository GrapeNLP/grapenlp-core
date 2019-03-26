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

#ifdef TRACE
#include <grapenlp/context_key_value_hasher.h>
#endif

#include <grapenlp/context.h>
#include <grapenlp/u_context_mask_constants.h>

namespace grapenlp
{
    template<typename Char>
    class context_mask
    {
    public:
        typedef context<Char> context_type;
        typedef typename context_type::hash_type hash_type;

    private:
        const hash_type key_hash;
        const hash_type value_hash;
#ifdef TRACE
        array<Char> key;
        array<Char> value;
#endif

    public:
#ifdef TRACE
        template<typename CharIterator>
        context_mask(const hash_type key_hash_, const hash_type value_hash_, CharIterator key_begin, CharIterator key_end, CharIterator value_begin, CharIterator value_end): key_hash(key_hash_), value_hash(value_hash_), key(key_begin, key_end), value(value_begin, value_end)
#else
        context_mask(const hash_type key_hash_, const hash_type value_hash_): key_hash(key_hash_), value_hash(value_hash_)
#endif
        {}

    public:
        bool match(const context<Char> &c) const
        {
            return c.equals(key_hash, value_hash);
        }

#ifdef TRACE
        std::ostream& serialize(std::ostream& out) const
        { return serialize_context_expression(out << "%"); }

        std::wostream& wserialize(std::wostream& out) const
        { return wserialize_context_expression(out << L"%"); }

        std::ostream& serialize_context_expression(std::ostream& out) const
        { return out << "<@" << key << "=" << *value << ">"; }

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
#endif

        bool operator<(const context_mask &other) const
        {
            if (key_hash < other.key_hash)
                return true;
            if (other.key_hash < key_hash)
                return false;
            return (value_hash < other.value_hash);
        }

        bool operator==(const context_mask &other) const
        {
            return key_hash == other.key_hash && value_hash == other.value_hash;
        }

        ~context_mask(){}
    };
} //namespace grapenlp

#endif /*GRAPENLP_CONTEXT_MASK_H*/
