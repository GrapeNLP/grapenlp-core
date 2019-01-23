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

/* set_trie.i */
%module set_trie
%include trie_with_def_data.i
%{
#include <grapenlp/set_trie.h>

namespace grapenlp
{
    template<typename T>
    using set_trie_const_iterator = typename ::grapenlp::set_trie<T>::const_iterator;
}
%}

namespace grapenlp
{
    template<typename T>
    class set_trie_const_iterator
    {
    public:
        const_iterator();
        const_iterator(const trie_with_def_data_string<T, ::grapenlp::false_func> &root): base_iterator(root);

        const T& operator*();
        const_iterator& operator++();
    };

    %define SET_TRIE_CONST_ITERATOR_EXTEND(name, T)
    %extend name<T>
    {
        bool has_next() const
        { return !base_iterator::base_iterator::base_iterator::call_back_trace.empty(); }
    }

    %pythoncode %{
    def name(self):
        if self.has_next():
            elem = self.__deref__()
            self.__preinc__()
            return elem
        raise StopIteration()

    name.next = name
    %}
    %enddef

	template<typename T>
	class set_trie: public trie_with_def_data<T, ::grapenlp::false_func, ::grapenlp::false_func::result_type>
	{
	public:
		typedef set_trie<T> this_type;
		typedef trie_with_def_data<T, ::grapenlp::false_func> base_trie_with_def_data;
		typedef trie_with_def_data_string<T, ::grapenlp::false_func> string;
		typedef T value_type;

	public:
		set_trie();

        size_type size();

        bool empty();

		string& add(const T& elem);

        %rename(const_begin) ::grapenlp::set_trie::begin() const;
        set_trie_const_iterator<T> begin() const;

        %rename(const_end) ::grapenlp::set_trie::end() const;
        set_trie_const_iterator<T> end() const;

		template<typename Iterator>
		string& add(Iterator begin, Iterator end);

		template<typename Iterator>
		bool includes(const T &elem) const;

		template<typename Iterator>
		bool includes(Iterator begin, Iterator end) const;

		template<typename Iterator>
		inline typename string::ref get_longest_match(Iterator begin, Iterator end);

		template<typename Iterator>
		inline typename string::const_ref get_longest_match(Iterator begin, Iterator end) const;

        ~set_trie();
	};

    %define SET_TRIE_EXTEND(name, T)
    %extend name<T>
    {
        set_trie_const_iterator<T> __iter__() const
        { return begin(); }
    }
    %enddef
}
