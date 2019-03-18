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

#ifndef GRAPENLP_TRIE_PERFECT_HASHER_H
#define GRAPENLP_TRIE_PERFECT_HASHER_H

#include<grapenlp/trie_with_def_data.h>

namespace grapenlp
{
    /**
     * This class implements a perfect hasher based on a prefix trie where final nodes are annotated with unique indexes.
     * The first inserted sequence is given index 1, the second one is given index 2, and so on. Upon requesting the
     * index of a sequence, index 0 indicates that the sequence has not been indexed. Note that indexes greater than 0
     * are returned only for whole indexed sequences, prefixes of indexed sequences that are not whole indexed sequences
     * themselves are associated to index 0 until they are explicitly inserted in the hasher.
     * @tparam T the type of the items in the sequences to index
     */
    template<typename T>
    class trie_perfect_hasher
    {
    public:
        typedef std::size_t size_type;
        typedef trie_with_def_data<T, zero_func<size_type> > hash_trie;
        typedef typename hash_trie::string hash_trie_string;
        typedef typename hash_trie_string::const_ref hash_trie_string_const_ref;

    private:
        size_type elem_count;
        hash_trie the_hash_trie;

    public:
        trie_perfect_hasher(): elem_count(0), the_hash_trie()
        {}

        /**
         * Insert a sequence in the hasher and associate it the next index if the sequence is not already indexed.
         * Reinserting the same sequence twice does not modify its index or the hasher size.
         * @tparam Iterator the type of the range iterator
         * @param begin iterator to the first element of the range
         * @param end iterator to the element after the range
         * @return the index associated to sequence [begin, end); if the sequence was not previously indexed, it returns
         * the previous size + 1, otherwise it returns the previous size.
         */
        template<typename Iterator>
        size_type insert(Iterator begin, Iterator end)
        {
            hash_trie_string &s(the_hash_trie.epsilon().concat(begin, end));
            if (!s.data)
            {
                ++elem_count;
                s.data = elem_count;
            }
            return elem_count;
        }

        /**
         * Retrieve the index associated to the given range by this hasher
         * @tparam Iterator the type of the range iterator
         * @param begin iterator to the first element of the range
         * @param end iterator to the element after the range
         * @return 0 if the sequence has not been indexed by this hasher, otherwise it returns 1 if [begin, end) is the
         * first indexed sequence, 2 if it is the second one, and so on.
         */
        template<typename Iterator>
        size_type index_of(Iterator begin, Iterator end) const
        {
            hash_trie_string_const_ref s(the_hash_trie.get(begin, end));
            return s ? s->data : 0;
        }

        /**
         * @return the amount of sequences indexed by this hasher
         */
        size_type size() const
        { return elem_count; }
    };
}

#endif //GRAPENLP_TRIE_PERFECT_HASHER_H
