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

#include <grapenlp/context_key_value_hasher.h>

namespace grapenlp
{
    /**
     * A conversation context given by a sort of key/value map. The map is optimized for evaluating whether a key is
     * present and associated to a given value. Internally, keys and values are transformed into indexes and the map
     * is represented by an integer array m where key i is associated to value with index m[i], thus checking that a key
     * is associated to a value is reduced to obtaining the key and value indexes k and v then computing m[k] == v. In
     * order to take advantage of this optimization, the same context object is to be reused during a conversation,
     * modifying the context mappings that are needed after each interaction.
     *
     * @tparam CharT the character type of the context keys and values (e.g. unichar)
     */
    template<typename CharT>
    class context
    {
    public:
        typedef context_key_value_hasher<CharT> hasher;
        typedef typename hasher::hash_type hash_type;
#ifdef TRACE
        typedef typename hasher::hasher::hash_trie_string_const_ref hash_trie_string_const_ref;
        typedef typename hasher::hasher::const_iterator hash_trie_const_iterator;
#endif

    private:
        const context_key_value_hasher<CharT> &the_hasher;
        hash_type *the_map;
#ifdef TRACE
        hash_trie_string_const_ref *reverse_key_map;
        hash_trie_string_const_ref *reverse_value_map;
#endif

    public:
        /**
         * Delete all the key/value mappings. Internally, all the keys are mapped to 0, the index associated to the
         * unknown value, so checking that a grammar key is associated to a grammar value will fail since all grammar
         * values are given indexes greater than 0. For succeeding, the context will have to define an association of
         * a grammar key with a grammar value and such mapping will have to be requested by the grammar.
         */
        void clear()
        {
            hash_type *begin(the_map);
            hash_type *end(the_map + the_hasher.key_hasher.size() + 1);
            while (begin != end)
            {
                *begin = 0;
                ++begin;
            }
        }

        /**
         * Constructor of an empty context for a given context key and value hasher; when building the context the
         * hasher is supposed to contain all the keys and values in the grammar (after loading the grammar) and not to
         * be modified during the application of the grammar to the user sentences and contexts (if the grammar is to be
         * reloaded, so it is the hasher and user contexts).
         * @param the_hasher_ the context key and value hasher built during the grammar loading 
         */
        context(const context_key_value_hasher<CharT> &the_hasher_): the_hasher(the_hasher_), the_map(nullptr)
        {
            if (the_hasher_.key_hasher.size())
            {
                the_map = new hash_type[the_hasher_.key_hasher.size() + 1];
                clear();
#ifdef TRACE
                reverse_key_map = new hash_trie_string_const_ref[the_hasher_.key_hasher.size() + 1];
                hash_trie_const_iterator begin(the_hasher_.key_hasher.begin());
                hash_trie_const_iterator end(the_hasher_.key_hasher.end());
                while (begin != end)
                {
                    reverse_key_map[begin->data] = &(*begin);
                    ++begin;
                }
                reverse_value_map = new hash_trie_string_const_ref[the_hasher_.value_hasher.size() + 1];
                begin = the_hasher_.value_hasher.begin();
                end = the_hasher_.value_hasher.end();
                while (begin != end)
                {
                    reverse_value_map[begin->data] = &(*begin);
                    ++begin;
                }
#endif
            }
        }

#ifdef TRACE
        context(context &&c) noexcept: the_hasher(c.the_hasher), the_map(c.the_map), reverse_key_map(c.reverse_key_map), reverse_value_map(c.reverse_value_map)
#else
        context(context &&c) noexcept: the_hasher(c.the_hasher), the_map(c.the_map)
#endif
        {
            c.the_map = nullptr;
#ifdef TRACE
            c.reverse_key_map = nullptr;
            c.reverse_value_map = nullptr;
#endif
        }

        /**
         * @tparam KeyIterator the type of the key character iterator
         * @param key_begin the first element of the key range
         * @param key_end the element after the key range
         * @return the index associated to the key given by range [begin, end) 
         */
        template<typename KeyIterator>
        hash_type get_key_hash(KeyIterator key_begin, KeyIterator key_end)
        {
            return the_hasher.key_hasher.index_of(key_begin, key_end);
        }

        /**
         * @tparam ValueIterator the type of the value character iterator
         * @param value_begin the first element of the value range
         * @param value_end the element after the value range
         * @return the index associated to the value given by range [begin, end) 
         */
        template<typename ValueIterator>
        hash_type get_value_hash(ValueIterator value_begin, ValueIterator value_end)
        {
            return the_hasher.value_hasher.index_of(value_begin, value_end);
        }

        /**
         * Get the value hash associated to the given key hash. This method does not verify that the passed key hash is
         *
         * @param k
         * @return
         */
        hash_type get(hash_type k)
        {
            return the_map[k];
        }

        /**
         * Map a key to a given value
         * @param k the key index (result of function get_key_hash(key_begin, key_end))
         * @param v the value index (result of function get_value_hash(value_begin, value_end))
         */
        void set(hash_type k, hash_type v)
        {
            the_map[k] = v;
        }

        /**
         * Map a key [key_begin, key_end) to a value [value_begin, value_end)
         * @param key_begin the first element of the key range
         * @param key_end the element after the key range
         * @param value_begin the first element of the value range
         * @param value_end the element after the value range
         */
        template<typename KeyIterator, typename ValueIterator>
        void set(KeyIterator key_begin, KeyIterator key_end, ValueIterator value_begin, ValueIterator value_end)
        {
            hash_type key_hash(get_key_hash(key_begin, key_end));
            hash_type value_hash(get_value_hash(value_begin, value_end));
            the_map[key_hash] = value_hash;
        }

        /**
         * Check that the given key is mapped to the given value
         * @param k the key index (result of function get_key_hash(key_begin, key_end))
         * @param v the value index (result of function get_value_hash(value_begin, value_end))
         * @return true if key with index k is mapped to value with index v; false otherwise
         */
        bool equals(hash_type k, hash_type v) const
        {
            return the_map[k] == v;
        }

        /**
         * Check that the given key is mapped to the given value
         * @param key_begin the first element of the key range
         * @param key_end the element after the key range
         * @param value_begin the first element of the value range
         * @param value_end the element after the value range
         * @return true if key [key_begin, key_end) is mapped to value [value_begin, value_end); false otherwise
         */
        template<typename KeyIterator, typename ValueIterator>
        bool equals(KeyIterator key_begin, KeyIterator key_end, ValueIterator value_begin, ValueIterator value_end)
        {
            return the_map[get_key_hash(key_begin, key_end)] == get_value_hash(value_begin, value_end);
        }

        /**
         * Check that the given key is not mapped to the given value
         * @param k the key index (result of function get_key_hash(key_begin, key_end))
         * @param v the value index (result of function get_value_hash(value_begin, value_end))
         * @return false if key with index k is mapped to value with index v; true otherwise
         */
        template<typename KeyIterator, typename ValueIterator>
        bool not_equals(hash_type k, hash_type v) const
        {
            return the_map[k] != v;
        }

        /**
         * Check that the given key is not mapped to the given value
         * @param key_begin the first element of the key range
         * @param key_end the element after the key range
         * @param value_begin the first element of the value range
         * @param value_end the element after the value range
         * @return false if key [key_begin, key_end) is mapped to value [value_begin, value_end); true otherwise
         */
        template<typename KeyIterator, typename ValueIterator>
        bool not_equals(KeyIterator key_begin, KeyIterator key_end, ValueIterator value_begin, ValueIterator value_end)
        {
            return the_map[get_key_hash(key_begin, key_end)] != get_value_hash(value_begin, value_end);
        }

        ~context()
        {
            if (the_map)
                delete[] the_map;
#ifdef TRACE
            if (reverse_key_map)
                delete[] reverse_key_map;
            if (reverse_value_map)
                delete[] reverse_value_map;
#endif
        }
    };
} //namespace grapenlp

#endif /*GRAPENLP_CONTEXT_H*/
