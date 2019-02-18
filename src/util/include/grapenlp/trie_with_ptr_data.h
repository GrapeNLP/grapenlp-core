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

#ifndef GRAPENLP_TRIE_WITH_PTR_DATA_H
#define GRAPENLP_TRIE_WITH_PTR_DATA_H

#include <grapenlp/trie_with_data.h>

namespace grapenlp
{
    /*
	 * Trie with a pointer to data field at each node
	 */

    template<typename T, typename Data>
	class trie_with_ptr_data: public trie_with_data<T, Data*>
	{
	public:
		typedef trie_with_ptr_data<T, Data> this_type;
		typedef trie_with_data<T, Data*> base_trie_with_data;
		typedef T value_type;

		class string: public base_trie_with_data::string
		{
			friend class trie_with_ptr_data<T, Data>;

		public:
			typedef T value_type;
			typedef string* ref;
			typedef const string* const_ref;
			//We want here to use string object addresses as order criterion for performance reasons
			typedef std::set<ref> ref_set;
			typedef typename base_trie_with_data::string base_string;

		public:
			//Construcs the root of a trie: the epsilon (empty word) reference
			string(): base_string::string()
			{}

			//Construcs the root of a trie: the epsilon (empty word) reference
			string(Data *data_): base_string::string(data_)
			{}

			//Constructs a trie string as the concatenation of a prefix string with a string element
			string(const T& elem_, string::ref prefix_ref_): base_string::string(elem_, prefix_ref_)
			{}

			//Constructs a trie string as the concatenation of a prefix string with a string element
			string(const T& elem_, string::ref prefix_ref_, Data *data_): base_string::string(elem_, prefix_ref_, data_)
			{}

			//Copy constructor is not furnished since for every trie string x and y, if x == y then &x == &y (they are the same object)
		private:
			string(const string &s)
			{}
		public:

		public:
			string& prefix()
			{ return static_cast<string&>(*base_string::base_string::prefix_ref); }

			const string& prefix() const
			{ return static_cast<const string&>(*base_string::base_string::prefix_ref); }

			//Returns the pointer to the string = (this + elem) if the trie includes it, NULL otherwise
			ref get(const T& elem)
			{ return static_cast<ref>(base_string::base_string::get(elem)); }

			const_ref get(const T& elem) const
			{ return static_cast<const_ref>(base_string::base_string::get(elem)); }

			//Returns the pointer to the string = (this + elem) if the trie includes it, NULL otherwise
			template<typename Normalizer>
			ref get(const T& elem, Normalizer normalizer)
			{ return static_cast<ref>(base_string::base_string::get(elem, normalizer)); }

			template<typename Normalizer>
			const_ref get(const T& elem, Normalizer normalizer) const
			{ return static_cast<const_ref>(base_string::base_string::get(elem, normalizer)); }

			//Returns the string = (*this + elem)
			//If the trie did not contain it before, it is created and added and
			//its data field initialized with the specified def_value
			string& concat(const T& elem)
			{
				std::pair<typename base_string::base_string::suffix_table::iterator, bool> result(base_string::base_string::suffixes.insert(std::make_pair(elem, new string(elem, this))));
				return static_cast<string&>(*result.first->second);
			}

			//As before but returning as well whether the resulting string is new or not
			string& concat(const T& elem, bool &is_new)
			{
				std::pair<typename base_string::base_string::suffix_table::iterator, bool> result(base_string::base_string::suffixes.insert(std::make_pair(elem, new string(elem, this))));
				is_new = result.second;
				return static_cast<string&>(*result.first->second);
			}

			//As before but specifying the value to be assigned to the data field
			//If the string was already present, the old data is kept (same behaviour than class std::map)
			string& concat(const T& elem, Data* data)
			{
				std::pair<typename base_string::base_string::suffix_table::iterator, bool> result(base_string::base_string::suffixes.insert(std::make_pair(elem, new string(elem, this, data))));
				return static_cast<string&>(*result.first->second);
			}

			//Operator version of concat(const T& elem)
			string& operator+(const T& elem)
			{ return concat(elem); }

			//Returns the pointer to the string = (this + s) if the trie includes it, NULL otherwise
			ref get(string &s)
			{ return static_cast<ref>(base_string::base_string::get(s)); }

			const_ref get(string &s) const
			{ return static_cast<const_ref>(base_string::base_string::get(s)); }

			//Returns the pointer to the string = (this + s) if the trie includes it, NULL otherwise
			template<typename Normalizer>
			ref get(string &s, Normalizer normalizer)
			{ return static_cast<ref>(base_string::base_string::get(s, normalizer)); }

			template<typename Normalizer>
			const_ref get(string &s, Normalizer normalizer) const
			{ return static_cast<const_ref>(base_string::base_string::get(s, normalizer)); }

			//Returns the string = (*this + s)
			//If the trie did not contain it before, it is created and added and
			//its data field initialized with the default constructor of its class
			string& concat(string &s)
			{
				//x + epsilon = x
				if (s.empty())
					return *this;
				//x + ya = (x + y) + a
				return concat(s.prefix()).concat(s.back());
			}

			//As before but returning as well whether the resulting string is new or not
			string& concat(string &s, bool &is_new)
			{
				//x + epsilon = x -> x is not new
				if (s.empty())
				{
					is_new = false;
					return *this;
				}
				//x + ya = (x + y) + a
				//We concatenate all the string except its last elem without checking if the result is new
				ref result = &concat(s.prefix());
				//We concatenate the last elem checking if its new
				return result->concat(s.back(), is_new);
			}

			//As before but specifying the value to be assigned to the data field
			//If the string was already present, the old data is kept (same behaviour than class std::map)
			string& concat(string &s, Data *data)
			{
				bool is_new;
				string &result = concat(s, is_new);
				if (is_new)
					result.data = data;
				return result;
			}

			//As before but returning as well whether the resulting string is new or not
			string& concat(string &s, Data *data, bool &is_new)
			{
				string &result = concat(s, is_new);
				if (is_new)
					result.data = data;
				return result;
			}

			//Operator version of concat(string &s)
			string& operator+(string& s)
			{ return concat(s); }

			//Returns the pointer to the string = (*this + i1 + ... + in) where i1 == *begin and in == *(end - 1)
			//if the trie includes it, NULL otherwise
			template<typename Iterator>
			ref get(Iterator begin, Iterator end)
			{ return static_cast<ref>(base_string::base_string::get(begin, end)); }

			template<typename Iterator>
			const_ref get(Iterator begin, Iterator end) const
			{ return static_cast<const_ref>(base_string::base_string::get(begin, end)); }

			//Returns the pointer to the string = (*this + i1 + ... + in) where i1 == *begin and in == *(end - 1)
			//if the trie includes it, NULL otherwise
			template<typename Iterator, typename Normalizer>
			ref get(Iterator begin, Iterator end, Normalizer normalizer)
			{ return static_cast<ref>(base_string::base_string::get(begin, end, normalizer)); }

			template<typename Iterator, typename Normalizer>
			const_ref get(Iterator begin, Iterator end, Normalizer normalizer) const
			{ return static_cast<const_ref>(base_string::base_string::get(begin, end, normalizer)); }

			//Returns the string = (*this + i1 + ... + in) where i1 == *begin and in == *(end - 1)
			//if the trie did not contain it before, it is created and added
			template<typename Iterator>
			string& concat(Iterator begin, Iterator end)
			{
				ref s(this);
				for (; begin != end; ++begin)
					s = &s->concat(*begin);
				return *s;
			}

			//As before but returning as well whether the resulting string is new or not
			//If new, the data field of the resulting string is initialized with the default constructor of its class
			template<typename Iterator>
			string& concat(Iterator begin, Iterator end, bool &is_new)
			{
				//Concatenation with epsilon
				if (begin == end)
				{
					is_new = false;
					return *this;
				}
				--end;
				//Concatenation with element
				if (begin == end)
					return concat(*begin, is_new);
				//Concatenation with string longer than 1
				//We only check if the resulting string is new when
				//concatenating the last element
				return this->concat(begin, end).concat(*end, is_new);
			}

			//As before but specifying the value to be assigned to the data field
			//If the string was already present, the old data is kept (same behaviour than class std::map)
			template<typename Iterator>
			string& concat(Iterator begin, Iterator end, Data *data)
			{
				bool is_new;
				ref s(&concat(begin, end, is_new));
				if (is_new)
					s->data = data;
				return *s;
			}

			//As before but returning as well whether the resulting string is new or not
			template<typename Iterator>
			string& concat(Iterator begin, Iterator end, Data *data, bool &is_new)
			{
				ref s(&concat(begin, end, is_new));
				if (is_new)
					s->data = data;
				return *s;
			}

			virtual ~string()
			{ delete base_string::data; }
		};

		class iterator: public base_trie_with_data::iterator
		{
			friend class trie_with_ptr_data<T, Data>;
		public:
			typedef typename base_trie_with_data::iterator base_iterator;
		public:
			iterator(): base_iterator()
			{}

			string& operator*()
			{ return static_cast<string&>(*base_iterator::base_iterator::call_back_trace.top().first); }

			string* operator->()
			{ return static_cast<typename string::ref>(base_iterator::base_iterator::call_back_trace.top().first); }

			iterator(string &root): base_iterator(root)
			{}
		};

		class const_iterator: public base_trie_with_data::const_iterator
		{
			friend class trie_with_ptr_data<T, Data>;
		public:
			typedef typename base_trie_with_data::const_iterator base_iterator;
		public:
			const_iterator(): base_iterator()
			{}

			const string& operator*()
			{ return static_cast<const string&>(*base_iterator::base_iterator::call_back_trace.top().first); }

			typename string::const_ref operator->()
			{ return static_cast<typename string::const_ref>(base_iterator::base_iterator::call_back_trace.top().first); }

			const_iterator(const string &root): base_iterator(root)
			{}
		};

	protected:
		//Constructor used by derived classes in order to provide a specialized epsilon string
		trie_with_ptr_data(typename string::ref s): base_trie_with_data(s)
		{}

	public:
		trie_with_ptr_data(): base_trie_with_data(new string())
		{}

		string& epsilon()
		{ return static_cast<string&>(*base_trie_with_data::base_trie::epsilon_); }

		const string& epsilon() const
		{ return static_cast<const string&>(*base_trie_with_data::base_trie::epsilon_); }

		iterator begin()
		{ return iterator(epsilon()); }

		const_iterator begin() const
		{ return const_iterator(epsilon()); }

		iterator end()
		{ return iterator(); }

		const_iterator end() const
		{ return const_iterator(); }

		typename string::ref get(const T& elem)
		{ return static_cast<typename string::ref>(base_trie_with_data::base_trie::get(elem)); }

		typename string::const_ref get(const T& elem) const
		{ return static_cast<typename string::const_ref>(base_trie_with_data::base_trie::get(elem)); }

		template<typename Normalizer>
		typename string::ref get(const T& elem, Normalizer normalizer)
		{ return static_cast<typename string::ref>(base_trie_with_data::base_trie::get(elem, normalizer)); }

		template<typename Normalizer>
		typename string::const_ref get(const T& elem, Normalizer normalizer) const
		{ return static_cast<typename string::const_ref>(base_trie_with_data::base_trie::get(elem, normalizer)); }

		template<typename Iterator>
		typename string::ref get(Iterator begin, Iterator end)
		{ return static_cast<typename string::ref>(base_trie_with_data::base_trie::get(begin, end)); }

		template<typename Iterator>
		typename string::const_ref get(Iterator begin, Iterator end) const
		{ return static_cast<typename string::const_ref>(base_trie_with_data::base_trie::get(begin, end)); }

		template<typename Iterator, typename Normalizer>
		typename string::ref get(Iterator begin, Iterator end, Normalizer normalizer)
		{ return static_cast<typename string::ref>(base_trie_with_data::base_trie::get(begin, end, normalizer)); }

		template<typename Iterator, typename Normalizer>
		typename string::const_ref get(Iterator begin, Iterator end, Normalizer normalizer) const
		{ return static_cast<typename string::const_ref>(base_trie_with_data::base_trie::get(begin, end, normalizer)); }

		template<typename Iterator>
		typename string::ref get_longest_prefix(Iterator begin, Iterator end)
		{ return static_cast<typename string::ref>(base_trie_with_data::get_longest_prefix(begin, end)); }

		template<typename Iterator>
		typename string::const_ref get_longest_prefix(Iterator begin, Iterator end) const
		{ return static_cast<typename string::const_ref>(base_trie_with_data::get_longest_prefix(begin, end)); }
	};

    template<typename T, typename Data, typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const typename trie_with_ptr_data<T, Data>::string &s)
    { return s.serialize(out); }
} //namespace grapenlp

#endif /*GRAPENLP_TRIE_WITH_PTR_DATA_H*/
