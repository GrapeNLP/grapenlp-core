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

#ifndef GRAPENLP_SET_H
#define GRAPENLP_SET_H

#include <set>
#include <grapenlp/functional.h>

namespace grapenlp
{
	template<typename T, typename Comparator=deref_less<T*>, typename Allocator=std::allocator<T*> >
	class ptr_set: public std::set<T*, Comparator, Allocator>
	{
	public:
		typedef std::set<T*, Comparator, Allocator> base_type;
		typedef typename base_type::size_type size_type;
		typedef typename base_type::iterator iterator;
		typedef typename base_type::const_iterator const_iterator;

		ptr_set(): base_type() {};
		explicit ptr_set(const Comparator& comparator): base_type(comparator) {};
		explicit ptr_set(const Comparator& comparator, const Allocator& a): base_type(comparator, a) {};

		//Unsafe random insertion
		inline std::pair<iterator,bool> unsafe_insert (T *x)
		{ return base_type::insert(x); }

		//Unsafe efficient insertion
		inline iterator unsafe_insert (iterator position, T *x)
		{ return base_type::insert(position, x); }

		//Safe efficient range insertion
		template <class InputIterator>
		void unsafe_insert (InputIterator first, InputIterator last)
		{ return base_type::insert(first, last); }

		//Safe random insertion: if the element was already present, its memory is freed
		std::pair<iterator,bool> insert (T *x)
		{
			std::pair<iterator,bool> result(unsafe_insert(x));
			if (!result.second)
				delete x;
			return result;
		}

		//Safe efficient insertion
		iterator insert (iterator position, T *x)
		{
			iterator result(unsafe_insert(position, x));
			if (*result != x)
				delete x;
			return result;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			//If empty range, return
			if (first == last)
				return;
			//Get first insertion point
			iterator i(base_type::lower_bound(*first));
			//While insertion point has not reached the end of the map
			while (i != base_type::end())
			{
				//Do safe insertion
				insert(i, *first);
				//Advance to next insertion element
				++first;
				//If no more elements to insert, return
				if (first == last)
					return;
				//Get next insertion point
				i = base_type::lower_bound(*first);
			}
			//Remaining inserts will surely be new: do unsafe insertion
			for (; first != last; ++first)
				unsafe_insert(*first);
		}

		void erase(iterator pos)
		{
			delete *pos;
			base_type::erase(pos);
		}

		void erase(iterator from, iterator to)
		{
			iterator i;
			for (i = from; i != to; ++i)
				delete *i;
			base_type::erase(from, to);
		}

		size_type erase(const T *elem)
		{
			iterator i = find(elem);
			if (i != this->end())
			{
				delete *i;
				erase(i);
				return 1;
			}
			else return 0;
		}

		void clear()
		{
			iterator i;
			for (i = this->begin(); i != this->end(); ++i)
				delete *i;
			base_type::clear();
		}

		~ptr_set()
		{
			iterator i;
			for (i = this->begin(); i != this->end(); ++i)
				delete *i;
		}
	};

	template<typename T, typename Comparator=deref_less<T*>, typename Allocator=std::allocator<T*> >
	class ptr_multiset: public std::multiset<T*, Comparator, Allocator>
	{
	public:
		typedef typename std::multiset<T*, Comparator, Allocator>::size_type size_type;
		typedef typename std::multiset<T*, Comparator, Allocator>::iterator iterator;
		typedef typename std::multiset<T*, Comparator, Allocator>::const_iterator const_iterator;

		ptr_multiset(): std::multiset<T*, Comparator, Allocator>() {};
		explicit ptr_multiset(const Comparator& comparator): std::multiset<T*, Comparator, Allocator>(comparator) {};
		explicit ptr_multiset(const Comparator& comparator, const Allocator& a): std::multiset<T*, Comparator, Allocator>(comparator, a) {};

		iterator erase(iterator pos)
		{
			delete *pos;
			return std::multiset<T*, Comparator, Allocator>::erase(pos);
		}

		iterator erase(iterator from, iterator to)
		{
			iterator i;
			for (i = from; i != to; ++i)
				delete *i;
			return std::multiset<T*, Comparator, Allocator>::erase(from, to);
		}

		size_type erase(const T *elem)
		{
			iterator i = find(elem);
			if (i == this->end())
				return 0;
			size_type count = 0;
			do
			{
				delete *i;
				erase(i);
				++count;
				++i;
			}
			while (i != this->end && *i == elem);
			return count;
		}

		void clear()
		{
			iterator i;
			for (i = this->begin(); i != this->end(); ++i)
				delete *i;
			std::multiset<T*, Comparator, Allocator>::clear();
		}

		~ptr_multiset()
		{
			iterator i;
			for (i = this->begin(); i != this->end(); ++i)
				delete *i;
		}
	};
} //namespace set

#endif /*GRAPENLP_NAMESPACE_SET*/
