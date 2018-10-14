/*
 * GRAPE
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

#ifndef GRAPE_LIST_H
#define GRAPE_LIST_H

#include <list>

namespace grape
{
	template<typename T, typename Allocator=std::allocator<T*> >
	class ptr_list: public std::list<T*, Allocator>
	{
	public:
		typedef typename std::list<T*, Allocator> base_type;
		typedef typename base_type::size_type size_type;
		typedef typename base_type::iterator iterator;
		typedef typename base_type::const_iterator const_iterator;

		ptr_list(): std::list<T*, Allocator>() {};
		explicit ptr_list(const Allocator& a): std::list<T*, Allocator>(a) {};
		explicit ptr_list(size_type n): std::list<T*, Allocator>(n) {};

		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last )
		{
			clear();
			base_type::assign(first, last);
		}

	private:
		//This assign method is disabled in order to forbid filling the list with several copies of the same pointer,
		//which would produce several deletions of the same object upon destruction
		void assign(size_type n, const T& u)
		{}

	public:
		iterator erase(iterator pos)
		{
			delete *pos;
			return base_type::erase(pos);
		}

		iterator erase(iterator from, iterator to)
		{
			iterator i;
			for (i = from; i != to; ++i)
				delete *i;
			return base_type::erase(from, to);
		}

		void clear()
		{
			iterator i;
			for (i = this->begin(); i != this->end(); ++i)
				delete *i;
			base_type::clear();
		}

	private:
		//Resize is disabled in order to forbid filling the list with several copies of the same pointer,
		//which would produce several deletions of the same object upon destruction
//		void resize(size_type sz, T c = T())
//		{}

	public:
		void transfer(ptr_list &l)
		{
			while (!this->empty())
			{
				l.push_back(this->back());
				this->pop_back();
			}
		}

		~ptr_list()
		{
			iterator i;
			for (i = this->begin(); i != this->end(); ++i)
				delete *i;
		}
	};
} //namespace grape

#endif /*GRAPE_LIST_H*/
