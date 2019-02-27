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
    /**
     * A conversation context given by a sort of key/value map. The map is optimized for evaluating whether a key is
     * present and associated to a given value. Internally, keys and values are transformed into pointers to trie
     * strings so that string comparisons are reduced to comparing 2 pointers instead of sequences of characters of
     * arbitrary length. This data structure maintains a trie of keys (the key dictionary) and another of values (the
     * value dictionary), and provides methods for obtaining the pointers to the trie strings corresponding to the
     * desired keys and values. Upon loading a grammar, all the referred keys and values in the grammar are transformed
     * once into the trie string pointers, thus this transformation can be reused for the analysis of multiple
     * sentences. Upon loading the current conversation context, the corresponding keys and values must also be
     * transformed into pointers to trie strings, though as long as the context is not modified it can be reused in
     * further analysis, and as long as the context evolves by modifying a few mappings each time the conversion of the
     * constant part of the context is reused as well in further analyses.
     * @tparam Char the character type of the context keys and values (e.g. unichar)
     */
    template<typename KeyIterator, typename ValueIterator>
    class context
    {
    public:
        typedef KeyIterator key_iterator;
        typedef ValueIterator value_iterator;
        typedef typename std::iterator_traits<KeyIterator>::value_type key_char;
        typedef typename std::iterator_traits<ValueIterator>::value_type value_char;
        typedef trie<key_char> key_dictionary;
        typedef trie<value_char> value_dictionary;
        typedef typename key_dictionary::string::const_ref optimized_key;
        typedef typename value_dictionary::string::const_ref optimized_value;
        typedef std::map<optimized_key, optimized_value> map;
        typedef typename map::const_iterator map_const_iterator;
        typedef typename map::size_type size_type;

    private:
        key_dictionary keys;
        value_dictionary values;
        map the_map;

    public:
        context(): keys(), values(), the_map()
        {}

        size_type size() const
        {
            return the_map.size();
        }

        optimized_key get_optimized_key(key_iterator k_begin, key_iterator k_end)
        {
            return &keys.epsilon().concat(k_begin, k_end);
        }

        optimized_value get_optimized_value(value_iterator v_begin, value_iterator v_end)
        {
            return &values.epsilon().concat(v_begin, v_end);
        }

        void set(optimized_key k, optimized_value v)
        {
            the_map[k] = v;
        }

        bool equals(optimized_key k, optimized_value v) const
        {
            map_const_iterator it(the_map.find(k));
            return it != the_map.end() && it->second == v;
        }

        bool not_equals(optimized_key k, optimized_value v) const
        {
            map_const_iterator it(the_map.find(k));
            return it == the_map.end() || it->second != v;
        }

        void clear_map()
        {
            the_map.clear();
        }

        void clear()
        {
            clear_map();
            keys.clear();
            values.clear();
        }

        ~context()
        {}
    };
} //namespace grapenlp

#endif /*GRAPENLP_CONTEXT_H*/