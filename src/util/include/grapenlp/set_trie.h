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

#ifndef GRAPENLP_SET_TRIE_H
#define GRAPENLP_SET_TRIE_H

#include <grapenlp/trie_with_def_data.h>

namespace grapenlp
{
	/*
	 * Trie with a bool at each node, defaulting to false,
	 * which is used to indicate whether the corresponding string belongs to the set or not
	 */

	template<typename T>
	class set_trie: public trie_with_def_data<T, false_func>
	{
	public:
		typedef set_trie<T> this_type;
		typedef trie_with_def_data<T, false_func> base_trie_with_def_data;
		typedef typename base_trie_with_def_data::string string;
		typedef T value_type;
        typedef std::size_t size_type;

        class const_iterator: public base_trie_with_def_data::const_iterator
        {
            friend class set_trie<T>;
        public:
            typedef typename base_trie_with_def_data::const_iterator base_iterator;
        public:
            const_iterator(): base_iterator()
            {
                while (!base_iterator::base_iterator::base_iterator::call_back_trace.empty() && !(*this)->data)
                    base_iterator::operator++();
            }

            const_iterator(const string &root): base_iterator(root)
            {
                while (!base_iterator::base_iterator::base_iterator::call_back_trace.empty() && !(*this)->data)
                    base_iterator::operator++();
            }

            const_iterator& operator++()
            {
                do base_iterator::operator++();
                while (!base_iterator::base_iterator::base_iterator::call_back_trace.empty() && !(*this)->data);
                return *this;
            }
        };

    protected:
        size_type elem_count;

		//Constructor used by derived classes in order to provide a specialized epsilon string
		set_trie(typename string::ref s): base_trie_with_def_data(s), elem_count((size_type)s->data)
        {}

	public:
		set_trie(): base_trie_with_def_data(new string()), elem_count(0)
		{}

        size_type size()
        { return elem_count; }

        bool empty()
        { return (bool)elem_count; }

        const_iterator begin() const
        { return const_iterator(base_trie_with_def_data::epsilon()); }

        const_iterator end() const
        { return const_iterator(); }

		string& add(const T& elem)
		{
			string &s = base_trie_with_def_data::epsilon().concat(elem);
			s.data = true;
            ++elem_count;
			return s;
		}

		template<typename Iterator>
		string& add(Iterator begin, Iterator end)
		{
			string &s(base_trie_with_def_data::epsilon().concat(begin, end));
			s.data = true;
            ++elem_count;
			return s;
		}

		template<typename Iterator>
		bool includes(const T &elem) const
		{
			typename string::const_ref s(base_trie_with_def_data::get(elem));
			return s && s->data;
		}

		template<typename Iterator>
		bool includes(Iterator begin, Iterator end) const
		{
			typename string::const_ref s(base_trie_with_def_data::get(begin, end));
			return s && s->data;
		}

		template<typename Iterator>
		typename string::ref get_longest_match(Iterator begin, Iterator end)
		{
			typename string::ref s(&base_trie_with_def_data::epsilon());
			typename string::ref s2(&base_trie_with_def_data::epsilon());
			while (begin != end)
			{
				s2 = s2->get(*begin);
				if (!s2)
					break;
				if (s2->data)
					s = s2;
				++begin;
			}
			return s;
		}

		template<typename Iterator>
		typename string::const_ref get_longest_match(Iterator begin, Iterator end) const
		{
			typename string::const_ref s(&base_trie_with_def_data::epsilon());
			typename string::const_ref s2(&base_trie_with_def_data::epsilon());
			while (begin != end)
			{
				s2 = s2->get(*begin);
				if (!s2)
					break;
				if (s2->data)
					s = s2;
				++begin;
			}
			return s;
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_SET_TRIE_H*/
