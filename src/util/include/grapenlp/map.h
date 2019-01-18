/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2018 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
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

#ifndef GRAPENLP_MAP_H
#define GRAPENLP_MAP_H

#include <map>

namespace grapenlp
{
	template<typename Key, typename Data, typename Compare = std::less<Key>, typename Allocator = std::allocator<std::pair<const Key, Data*> > >
	class ptr_map: public std::map<Key, Data*, Compare, Allocator>
	{
	public:
		typedef std::map<Key, Data*, Compare, Allocator> base_type;
		typedef typename base_type::key_type key_type;
		typedef typename base_type::mapped_type mapped_type;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::key_compare key_compare;
		typedef typename base_type::value_compare value_compare;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
		typedef typename base_type::const_reference const_reference;
		typedef typename base_type::size_type size_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::iterator iterator;
		typedef typename base_type::const_iterator const_iterator;
		typedef typename base_type::reverse_iterator reverse_iterator;
		typedef typename base_type::const_reverse_iterator const_reverse_iterator;

		explicit ptr_map(const Compare &comp = Compare(), const Allocator &alloc= Allocator()): base_type(comp, alloc)
		{}

		template<typename InputIterator>
		ptr_map(InputIterator f, InputIterator l, const Compare &comp = Compare(), const Allocator &alloc= Allocator()): base_type(comp, alloc)
		{
			if (f == l)
				return;
			insert(new Data(f->second)).first;
			iterator i(base_type::begin());
			for (; f != l; ++f, ++i)
				insert(i, new Data(f->second));
		}

		ptr_map(const ptr_map &m): base_type(m)
		{
			iterator i(base_type::begin());
			for (; i != base_type::end(); ++i)
				i->second = new Data(*i->second);
		}

		//Unsafe random insertion
		inline std::pair<iterator,bool> unsafe_insert (const value_type x)
		{ return base_type::insert(x); }

		//Unsafe efficient insertion
		inline iterator unsafe_insert (iterator position, const value_type x)
		{ return base_type::insert(position, x); }

		//Safe efficient range insertion
		template <class InputIterator>
		void unsafe_insert (InputIterator first, InputIterator last)
		{ return base_type::insert(first, last); }

		//Safe random insertion: if the element was already present, its memory is freed
		std::pair<iterator,bool> insert (const value_type x)
		{
			std::pair<iterator,bool> result(unsafe_insert(x));
			if (!result.second)
				delete x.second;
			return result;
		}

		//Safe efficient insertion
		iterator insert (iterator position, const value_type x)
		{
			iterator result(unsafe_insert(position, x));
			if (result->second != x.second)
				delete x.second;
			return result;
		}

		//Safe efficient range insertion
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			//If empty range, return
			if (first == last)
				return;
			//Get first insertion point
			iterator i(base_type::lower_bound(first->first));
			//While insertion point has not reached the end of the map
			while (i != base_type::end())
			{
				//Do safe insertion
				insert(i, first);
				//Advance to next insertion element
				++first;
				//If no more elements to insert, return
				if (first == last)
					return;
				//Get next insertion point
				i = base_type::lower_bound(first->first);
			}
			//Remaining inserts will surely be new: do unsafe insertion
			for (; first != last; ++first)
				unsafe_insert(*first);
		}

		void erase(iterator pos)
		{
			delete pos->second;
			base_type::erase(pos);
		}

		size_type erase(const key_type& x)
		{
			iterator i = find(x);
			if (i == base_type::end())
				return 0;
			delete i->second;
			return 1;
		}

		inline Data* const operator[] (const key_type &x)
		{ return (*(this->insert(std::make_pair(x,new Data)).first)).second; }

		void erase(iterator first, iterator last)
		{
			for (; first != last; ++first)
				erase(first);
		}

		void clear()
		{
			iterator i(base_type::begin());
			for (; i != base_type::end(); ++i)
				delete i->second;
			base_type::clear();
		}

		~ptr_map()
		{
			for (iterator i(base_type::begin()); i != base_type::end(); ++i)
				delete i->second;
		}
	};
} //namespace grapenlp


#endif /*GRAPENLP_MAP_H*/
