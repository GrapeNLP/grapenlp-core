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

#ifndef GRAPENLP_TRIE_H
#define GRAPENLP_TRIE_H

#include <array>
#include <set>
#include <stack>
#include <vector>
#include <iterator>
#include <grapenlp/array.h>
#include <grapenlp/map.h>
//#include <grapenlp/functional.h>

namespace grapenlp
{
	/*
	 * Base trie class
	 */

	template<typename T>
	class trie
	{
	public:
		typedef trie<T> this_type;
		typedef T value_type;
		typedef std::size_t size_type;

		class iterator;
		class const_iterator;

		class string
		{
			friend class trie<T>;
			friend class trie<T>::iterator;
			friend class trie<T>::const_iterator;

		public:
			typedef T value_type;
			typedef string* ref;
			typedef const string* const_ref;
			//We want here to use string object addresses as order criterion for performance reasons
			typedef std::set<ref> ref_set;
			typedef ptr_map<T, string> suffix_table;

			class iterator: public std::iterator<std::forward_iterator_tag, T, std::size_t, T*, T&>
			{
				friend class string;

			protected:
				ref my_string_ref;
				std::vector<ref> string_trace;

				iterator(ref s_ref): my_string_ref(s_ref), string_trace()
				{ string_trace.reserve(s_ref->size()); }

			public:
				iterator(const iterator &i): my_string_ref(i.my_string_ref), string_trace()
				{
					string_trace.reserve(i.my_string_ref->size());
					for (typename std::vector<ref>::const_iterator j(i.string_trace.begin()); j != i.string_trace.end(); ++j)
						string_trace.push_back(*j);
				}

				iterator& rewind()
				{
					if (my_string_ref->empty())
						return *this;
					if (string_trace.empty())
						string_trace.push_back(my_string_ref);
					while (!string_trace.back()->prefix_ref->empty())
						string_trace.push_back(string_trace.back()->prefix_ref);
					return *this;
				}

				T operator*()
				{ return string_trace.back()->back(); }

				//This only makes sense if T is a pointer type
				T operator->()
				{ return &string_trace.back()->back(); }

				bool operator==(const iterator &i) const
				{ return (string_trace.empty() && i.string_trace.empty()) || (!string_trace.empty() && !i.string_trace.empty() && string_trace.back() == i.string_trace.back()); }

				bool operator!=(const iterator &i) const
				{ return (!string_trace.empty() || !i.string_trace.empty()) && (string_trace.empty() || i.string_trace.empty() || string_trace.back() != i.string_trace.back()); }

				bool operator==(const const_iterator &i) const
				{ return (string_trace.empty() && i.string_trace.empty()) || (!string_trace.empty() && !i.string_trace.empty() && string_trace.back() == i.string_trace.back()); }

				bool operator!=(const const_iterator &i) const
				{ return (!string_trace.empty() || !i.string_trace.empty()) && (string_trace.empty() || i.string_trace.empty() || string_trace.back() != i.string_trace.back()); }

				iterator& operator++()
				{
					string_trace.pop_back();
					return *this;
				}

				iterator& operator--()
				{ string_trace.push_back(string_trace.back()->prefix()); }

				~iterator()
				{}
			};

			class const_iterator: public std::iterator<std::forward_iterator_tag, const T, std::size_t, const T*, const T&>
			{
				friend class string;

			protected:
				const_ref my_string_ref;
				std::vector<const_ref> string_trace;

				const_iterator(const_ref s_ref): my_string_ref(s_ref), string_trace()
				{ string_trace.reserve(s_ref->size()); }

			public:
				const_iterator(const const_iterator &i): my_string_ref(i.my_string_ref), string_trace()
				{
					string_trace.reserve(i.my_string_ref->size());
					for (typename std::vector<const_ref>::const_iterator j(i.string_trace.begin()); j != i.string_trace.end(); ++j)
						string_trace.push_back(*j);
				}

				const_iterator(const iterator &i): my_string_ref(i.my_string_ref), string_trace()
				{
					string_trace.reserve(i.my_string_ref->size());
					for (typename std::vector<ref>::const_iterator j(i.string_trace.begin()); j != i.string_trace.end(); ++j)
						string_trace.push_back(*j);
				}

				const_iterator& rewind()
				{
					if (my_string_ref->empty())
						return *this;
					if (string_trace.empty())
						string_trace.push_back(my_string_ref);
					while (!string_trace.back()->prefix_ref->empty())
						string_trace.push_back(string_trace.back()->prefix_ref);
					return *this;
				}

				const T operator*() const
				{ return string_trace.back()->back(); }

				//This only makes sense if T is a pointer type
				const T operator->() const
				{ return &string_trace.back()->back(); }

				bool operator==(const const_iterator &i) const
				{ return (string_trace.empty() && i.string_trace.empty()) || (!string_trace.empty() && !i.string_trace.empty() && string_trace.back() == i.string_trace.back()); }

				bool operator!=(const const_iterator &i) const
				{ return (!string_trace.empty() || !i.string_trace.empty()) && (string_trace.empty() || i.string_trace.empty() || string_trace.back() != i.string_trace.back()); }

				bool operator==(const iterator &i) const
				{ return (string_trace.empty() && i.string_trace.empty()) || (!string_trace.empty() && !i.string_trace.empty() && string_trace.back() == i.string_trace.back()); }

				bool operator!=(const iterator &i) const
				{ return (!string_trace.empty() || !i.string_trace.empty()) && (string_trace.empty() || i.string_trace.empty() || string_trace.back() != i.string_trace.back()); }

				const_iterator& operator++()
				{
					string_trace.pop_back();
					return *this;
				}

				const_iterator& operator--()
				{ string_trace.push_back(string_trace.back()->prefix()); }

				~const_iterator()
				{}
			};

		protected:
			T elem;
			string* prefix_ref;
			size_type depth;
			suffix_table suffixes;

		public:
			//Construcs the root of a trie: the epsilon (empty word) reference
			string(): elem(), prefix_ref(NULL), depth(0), suffixes()
			{
//				std::wcout << L"created epsilon with depth = " << depth << std::endl;
			}

			//Constructs a trie string as the concatenation of a prefix string with a string element
			string(const T& elem_, ref prefix_ref_): elem(elem_), prefix_ref(prefix_ref_), depth(prefix_ref_->depth + 1), suffixes()
			{
//				std::wcout << L"created other with depth = " << depth << L" and prefix->depth = " << prefix_ref->depth << std::endl;
			}
			//Copy constructor is not furnished since for every trie string x and y, if x == y then &x == &y (they are the same object)
		private:
			string(const string &s)
			{}
		public:
            void prune_suffixes()
            {
			    suffixes.clear();
            }

			//Destructor of base string is virtual since derived string classes use their own destructor instead of this one
			virtual ~string()
			{}
		public:
			bool empty() const
			{ return !prefix_ref; }

			size_type size() const
			{ return depth;	}

			string& prefix()
			{ return *prefix_ref; }

			const string& prefix() const
			{ return *prefix_ref; }

			T back() const
			{ return elem; }

			iterator begin()
			{
				iterator i(this);
				i.rewind();
				return i;
			}

			const_iterator begin() const
			{
				const_iterator i(this);
				i.rewind();
				return i;
			}

			iterator end()
			{ return iterator(this); }

			const_iterator end() const
			{ return const_iterator(this); }

			bool starts_with(const T &elem) const
			{
				if (!depth)
					return false;
				const_ref prefix_ref(this);
				while (prefix_ref->depth > 1)
					prefix_ref = &prefix_ref->prefix();
				return prefix_ref->elem == elem;
			}

			bool starts_with(const string &prefix) const
			{
				if (prefix.depth > depth)
					return false;
				const_ref current_prefix_ref(this);
				while (current_prefix_ref->depth > prefix.depth)
					current_prefix_ref = current_prefix_ref->prefix_ref;
				return current_prefix_ref == &prefix;
			}

			template<typename Iterator>
			bool starts_with(Iterator begin, Iterator end) const
			{
				//Empty prefix
				std::size_t prefix_size(std::distance(begin, end));
				if (prefix_size > depth)
					return false;
				const_ref current_prefix_ref(this);
				while (current_prefix_ref->depth > prefix().depth)
					current_prefix_ref = current_prefix_ref->prefix_ref;
				while (begin != end)
				{
					--end;
					if (*end != current_prefix_ref->elem)
						return false;
					current_prefix_ref = current_prefix_ref->prefix_ref;
				}
				return true;
			}

			bool ends_with(const T &elem) const
			{ return this->elem == elem; }

			bool ends_with(const string &suffix) const
			{
				//The suffix cannot be longer than the string
				if (suffix.depth > depth)
					return false;
				//From now on, we do not require to check that
				//we have run out of elems of the string since
				//we will run out before of elems of the suffix
				const_ref current_suffix_ref(&suffix);
				const_ref current_string_ref(this);
				do
				{
					//Check if we have run out of suffix elems:
					//epsilon is a suffix of every string
					if (current_suffix_ref->empty())
						return true;
					//xa.suffix(yb) == false if a != b
					if (current_suffix_ref->elem != current_string_ref->elem)
						return false;
					//xa.suffix(yb) == x.suffix(y) if a == b
					current_suffix_ref = current_suffix_ref->prefix_ref;
					current_string_ref = current_string_ref->prefix_ref;
				} while (true);
			}

			template<typename Iterator>
			bool ends_with(Iterator begin, Iterator end) const
			{
				//epsilon is a suffix of every string
				if (begin == end)
					return true;
				//We do not check here if the suffix is longer than
				//the string since to compute end - begin may be expensive
				//depending on the Iterator type
				ref current_string_ref(this);
				--end;
				do
				{
					//Check if we have run out of string elems:
					//epsilon has only epsilon as prefix
					if (current_string_ref->empty())
						return begin == end;
					//Check if we have run out of suffix elems:
					//epsilon is a suffix of every string
					if (begin == end)
						return true;
					//xa.suffix(yb) == false if a != b
					if (*end != current_string_ref->elem)
						return false;
					//xa.suffix(yb) == x.suffix(y) if a == b
					current_string_ref = current_string_ref->prefix_ref;
					--end;
				} while (true);
			}

			array<T>& to_array(array<T>& a)
			{
				ref s(this);
				while (s->size() > a.size())
				{ s = s->prefix_ref; }
				while (!s->empty())
				{
					a[s->size() - 1] = s->back();
					s = &s->prefix();
				}
				return a;
			}

			array<T>& to_reverse_array(array<T>& a)
			{
				ref s(this);
				if (size() < a.size())
					for (typename array<T>::iterator a_it(a.begin()); a_it != a.end(); ++a_it, s = s->prefix_ref)
						*a_it = s->back();
				else for (typename array<T>::iterator a_it(a.begin()); s->size(); ++a_it, s = s->prefix_ref)
					*a_it = s->back();
				return a;
			}

			template<typename Iterator>
			Iterator copy(Iterator i)
			{
				if (empty())
					return i;
				i = prefix().copy(i);
				*i = back();
				++i;
				return i;
			}

			//Returns the pointer to the string = (this + elem) if the trie includes it, NULL otherwise
			ref get(const T& elem)
			{
				typename suffix_table::iterator i(suffixes.find(elem));
				if (i == suffixes.end())
					return NULL;
				return i->second;
			}

			const_ref get(const T& elem) const
			{
				typename suffix_table::const_iterator i(suffixes.find(elem));
				if (i == suffixes.end())
					return NULL;
				return i->second;
			}

			//Returns the pointer to the string = (this + elem) if the trie includes it, NULL otherwise
			template<typename Normalizer>
			ref get(const T& elem, Normalizer normalizer)
			{
				typename suffix_table::iterator i(suffixes.find(normalizer(elem)));
				if (i == suffixes.end())
					return NULL;
				return *i;
			}

			template<typename Normalizer>
			const_ref get(const T& elem, Normalizer normalizer) const
			{ return static_cast<const_ref>(get(elem, normalizer)); }

			//Returns the string = (*this + elem)
			//If the trie did not contain it before, it is created and added
			string& concat(const T& elem)
			{ return *suffixes.insert(std::make_pair(elem, new string(elem, this))).first->second; }

			//Returns the string = (*this + elem)
			//If the trie did not contain it before, it is created and added
			//The flag is_new is initialized consequently
			string& concat(const T& elem, bool &is_new)
			{
				std::pair<typename suffix_table::iterator, bool> result(suffixes.insert(std::make_pair(elem, new string(elem, this))));
				is_new = result.second;
				return *result.first->second;
			}

			//Operator version of concat(const T& elem)
			string& operator+(const T& elem)
			{ return concat(elem); }

			//Returns the pointer to the string = (this + s) if the trie includes it, NULL otherwise
			ref get(string &s)
			{
				//x + epsilon = x
				if (s.empty())
					return this;
				//x + ya = (x + y) + a
				ref result(get(s.prefix()));
				if (!result)
					return NULL;
				return result->get(s.back());
			}

			const_ref get(const string &s) const
			{ return static_cast<const_ref>(get(s)); }

			//Returns the pointer to the string = (this + s) if the trie includes it, NULL otherwise
			template<typename Normalizer>
			ref get(string &s, Normalizer normalizer)
			{
				//x + epsilon = x
				if (s.empty())
					return this;
				//x + ya = (x + y) + a
				ref result(get(normalizer(s.prefix())));
				if (!result)
					return NULL;
				return result->get(normalizer(s.back()));
			}

			template<typename Normalizer>
			const_ref get(const string &s, Normalizer normalizer) const
			{ return static_cast<const_ref>(get(s, normalizer)); }

			//Returns the string = (*this + s)
			//If the trie did not contain it before, it is created and added
			string& concat(string &s)
			{
				//x + epsilon = x
				if (s.empty())
					return *this;
				//x + ya = (x + y) + a
				return concat(s.prefix()).concat(s.back());
			}

			//Returns the string = (*this + s)
			//If the trie did not contain it before, it is created and added
			//The flag is_new is initialized consequently
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

			//Operator version of concat(string &s)
			string& operator+(string &s)
			{ return concat(s); }

			//Returns the pointer to the string = (*this + i1 + ... + in) where i1 == *begin and in == *(end - 1)
			//if the trie includes it, NULL otherwise
			template<typename Iterator>
			ref get(Iterator begin, Iterator end)
			{
				ref s(this);
				typename suffix_table::iterator i;
				for (; begin != end; ++begin)
				{
					i = s->suffixes.find(*begin);
					if (i == s->suffixes.end())
						return NULL;
					s = i->second;
				}
				return s;
			}

			template<typename Iterator>
			const_ref get(Iterator begin, Iterator end) const
			{
				const_ref s(this);
				typename suffix_table::const_iterator i;
				for (; begin != end; ++begin)
				{
					i = s->suffixes.find(*begin);
					if (i == s->suffixes.end())
						return NULL;
					s = i->second;
				}
				return s;
			}

			//Returns the pointer to the string = (*this + i1 + ... + in) where i1 == *begin and in == *(end - 1)
			//if the trie includes it, NULL otherwise
			template<typename Iterator, typename Normalizer>
			ref get(Iterator begin, Iterator end, Normalizer normalizer)
			{
				ref s(this);
				typename suffix_table::iterator i;
				for (; begin != end; ++begin)
				{
					i = s->suffixes.find(normalizer(*begin));
					if (i == s->suffixes.end())
						return NULL;
					s = i->second;
				}
				return s;
			}

			template<typename Iterator, typename Normalizer>
			const_ref get(Iterator begin, Iterator end, Normalizer normalizer) const
			{
				const_ref s(this);
				typename suffix_table::const_iterator i;
				for (; begin != end; ++begin)
				{
					i = s->suffixes.find(normalizer(*begin));
					if (i == s->suffixes.end())
						return NULL;
					s = i->second;
				}
				return s;
			}

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

			//Returns the string = (*this + i1 + ... + in) where i1 == *begin and in == *(end - 1)
			//if the trie did not contain it before, it is created and added
			//The flag is_new is initialized consequently
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

			bool operator== (const string& s) const
			{ return this == &s; }

			bool operator!= (const string& s) const
			{ return this != &s; }

			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
			{
				//Empty string: nothing to be printed
				if (empty())
					return out;
				//Strings of the form prefix + elem: print prefix followed by elem;
				return prefix().serialize(out) << back();
			}

		private:
			//Assign operator is hidden in order to avoid its use
			//Strings are nodes of a trie and they are built internally
			string &operator= (const string &s)
			{}
		};

		class iterator: public std::iterator<std::forward_iterator_tag, string, std::size_t, string*, string&>
		{
			friend class trie<T>;

		public:
			typedef std::pair<typename string::ref, typename string::suffix_table::iterator> node_pos;

		protected:
			std::stack<node_pos> call_back_trace;

		public:
			iterator(): call_back_trace()
			{}

			string& operator*()
			{ return *call_back_trace.top().first; }

			typename string::ref operator->()
			{ return call_back_trace.top().first; }

			iterator(string &root): call_back_trace()
			{ call_back_trace.push(node_pos(&root, root.suffixes.begin()));	}

			bool operator==(const iterator &i) const
			{ return call_back_trace == i.call_back_trace; }

			bool operator!=(const iterator &i) const
			{ return call_back_trace != i.call_back_trace; }

			iterator& operator++()
			{
				//While there are strings left on the stack and the heap string suffixes are already processed, pop
				while (!call_back_trace.empty() && call_back_trace.top().second == call_back_trace.top().first->suffixes.end())
					call_back_trace.pop();

				//If we have reached the end, do nothing
				if (call_back_trace.empty())
					return *this;

				//Go into the next suffix
				typename string::ref next_string_ref(call_back_trace.top().second->second);
				++call_back_trace.top().second;
				call_back_trace.push(node_pos(next_string_ref, next_string_ref->suffixes.begin()));
				return *this;
			}

			~iterator()
			{}
		};

		class const_iterator: public std::iterator<std::forward_iterator_tag, const string, std::size_t, const string*, const string&>
		{
			friend class trie<T>;

		public:
			typedef std::pair<typename string::const_ref, typename string::suffix_table::const_iterator> node_pos;

		protected:
			std::stack<node_pos> call_back_trace;

		public:
			const_iterator(): call_back_trace()
			{}

			const_iterator(const string &root): call_back_trace()
			{ call_back_trace.push(node_pos(&root, root.suffixes.begin()));	}

			const string& operator*()
			{ return *call_back_trace.top().first; }

			typename string::const_ref operator->()
			{ return call_back_trace.top().first; }

			bool operator==(const const_iterator &i) const
			{ return call_back_trace == i.call_back_trace; }

			bool operator!=(const const_iterator &i) const
			{ return call_back_trace != i.call_back_trace; }

			const_iterator& operator++()
			{
				//While there are strings left on the stack and the heap string suffixes are already processed, pop
				while (!call_back_trace.empty() && call_back_trace.top().second == call_back_trace.top().first->suffixes.end())
					call_back_trace.pop();

				//If we have reached the end, do nothing
				if (call_back_trace.empty())
					return *this;

				//Go into the next suffix
				typename string::const_ref next_string_ref(call_back_trace.top().second->second);
				++call_back_trace.top().second;
				call_back_trace.push(node_pos(next_string_ref, next_string_ref->suffixes.begin()));
				return *this;
			}

			~const_iterator()
			{}
		};

	protected:
		typename string::ref epsilon_;

		//Constructor used by derived classes in order to provide a specialized epsilon string
		trie(typename string::ref epsilon__)
		{ epsilon_ = epsilon__; }

	public:
		trie(): epsilon_(new string())
		{}

		string& epsilon()
		{ return *epsilon_; }

		const string& epsilon() const
		{ return static_cast<const string&>(*epsilon_); }

		iterator begin()
		{ return iterator(epsilon()); }

		const_iterator begin() const
		{ return const_iterator(epsilon()); }

		iterator end()
		{ return iterator(); }

		const_iterator end() const
		{ return const_iterator(); }

		typename string::ref get(const T& elem)
		{ return epsilon_->get(elem); }

		typename string::const_ref get(const T& elem) const
		{ return epsilon_->get(elem); }

		template<typename Normalizer>
		typename string::ref get(const T& elem, Normalizer normalizer)
		{ return epsilon_->get(normalizer(elem)); }

		template<typename Normalizer>
		typename string::const_ref get(const T& elem, Normalizer normalizer) const
		{ return epsilon_->get(normalizer(elem)); }

		template<typename Iterator>
		typename string::ref get(Iterator begin, Iterator end)
		{ return epsilon_->get(begin, end); }

		template<typename Iterator>
		typename string::const_ref get(Iterator begin, Iterator end) const
		{ return epsilon_->get(begin, end); }

		template<typename Iterator, typename Normalizer>
		typename string::ref get(Iterator begin, Iterator end, Normalizer normalizer)
		{ return epsilon_->get(begin, end, normalizer); }

		template<typename Iterator, typename Normalizer>
		typename string::const_ref get(Iterator begin, Iterator end, Normalizer normalizer) const
		{ return epsilon_->get(begin, end, normalizer); }

		template<typename Iterator>
		typename string::ref get_longest_prefix(Iterator begin, Iterator end)
		{
			typename string::ref s(epsilon_);
			typename string::ref s2;
			while (begin != end)
			{
				s2 = s->get(*begin);
				if (!s2)
					break;
				s = s2;
				++begin;
			}
			return s;
		}

		template<typename Iterator>
		typename string::const_ref get_longest_prefix(Iterator begin, Iterator end) const
		{
			typename string::const_ref s(epsilon_);
			typename string::const_ref s2;
			while (begin != end)
			{
				s2 = s->get(*begin);
				if (!s2)
					break;
				s = s2;
				++begin;
			}
			return s;
		}

		void clear()
		{
            epsilon_->prune_suffixes();
		}

		~trie()
		{ delete(epsilon_); }
	};

    template<typename T, typename Sequence>
    struct trie_string_and_deref_sequence_concatenator
    {
    	typename trie<T>::string& operator() (typename trie<T>::string &ts, const Sequence *seq) const
    	{ return ts.concat(seq->begin(), seq->end()); }

    	template<typename SourceRef>
    	typename trie<T>::string& operator() (typename trie<T>::string &ts, SourceRef src_ref, const Sequence *seq) const
    	{ return ts.concat(seq->begin(), seq->end()); }
    };

    template<typename T, typename Sequence>
    struct deref_trie_string_and_deref_sequence_concatenator
    {
    	typename trie<T>::string* &operator() (typename trie<T>::string* &ts, const Sequence *seq) const
    	{ return ts = &(ts->concat(seq->begin(), seq->end())); }

    	template<typename SourceRef>
    	typename trie<T>::string* &operator() (typename trie<T>::string* &ts, SourceRef src_ref, const Sequence *seq) const
    	{ return ts = &(ts->concat(seq->begin(), seq->end())); }
    };

    template<typename T, typename Sequence>
    struct trie_string_and_deref_reverse_sequence_concatenator
    {
    	typedef typename Sequence::const_iterator const_iterator;
    	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;

    	typename trie<T>::string& operator() (typename trie<T>::string &ts, const Sequence *seq) const
    	{ return ts.concat(reverse_const_iterator(seq->end()), reverse_const_iterator(seq->begin())); }

    	template<typename SourceRef>
    	typename trie<T>::string& operator() (typename trie<T>::string &ts, SourceRef src_ref, const Sequence *seq) const
    	{ return ts.concat(reverse_const_iterator(seq->end()), reverse_const_iterator(seq->begin())); }
    };

    template<typename T, typename Sequence>
    struct deref_trie_string_and_deref_reverse_sequence_concatenator
    {
    	typedef typename Sequence::const_iterator const_iterator;
    	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;

    	typename trie<T>::string* &operator() (typename trie<T>::string* &ts, const Sequence *seq) const
    	{ return ts = &(ts->concat(reverse_const_iterator(seq->end()), reverse_const_iterator(seq->begin()))); }

    	template<typename SourceRef>
    	typename trie<T>::string* &operator() (typename trie<T>::string* &ts, SourceRef src_ref, const Sequence *seq) const
    	{ return ts = &(ts->concat(reverse_const_iterator(seq->end()), reverse_const_iterator(seq->begin()))); }
    };

    template<typename T>
    struct trie_string_and_trie_string_concatenator
    {
    	typename trie<T>::string& operator() (typename trie<T>::string &ts1, const typename trie<T>::string &ts2) const
    	{ return ts1.concat(ts2); }

    	template<typename SourceRef>
    	typename trie<T>::string& operator() (typename trie<T>::string &ts1, SourceRef src_ref, const typename trie<T>::string &ts2) const
    	{ return ts1.concat(ts2); }
    };

    template<typename T>
    struct deref_trie_string_and_deref_trie_string_concatenator
    {
    	typename trie<T>::string* &operator() (typename trie<T>::string * &ts1, typename trie<T>::string *ts2) const
    	{ return ts1 = &(ts1->concat(*ts2)); }

    	template<typename SourceRef>
    	typename trie<T>::string* &operator() (typename trie<T>::string * &ts1, SourceRef src_ref, typename trie<T>::string *ts2) const
    	{ return ts1 = &(ts1->concat(*ts2)); }
    };

    template<typename T, typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const typename trie<T>::string &s)
    { return s.serialize(out); }

    template<typename T>
    struct trie_string_deref_reverse_serializer
    {
    	template<typename CharT, typename Traits>
    	std::basic_ostream<CharT, Traits>& operator() (std::basic_ostream<CharT, Traits>& out, const typename trie<T>::string *s)
    	{
    		while (!s->empty())
    		{
    			out << s->back();
    			s = &(s->prefix());
    		}
    		return out;
    	}
    };
} //namespace grapenlp

#endif /*GRAPENLP_TRIE_H*/
