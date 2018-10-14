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

#ifndef GRAPE_VECTOR_H
#define GRAPE_VECTOR_H

#include <vector>

namespace grape
{
	template<typename T, typename Allocator=std::allocator<T*> >
	class ptr_vector: public std::vector<T*, Allocator>
	{
	public:
		typedef typename std::vector<T*, Allocator>::size_type size_type;
		typedef typename std::vector<T*, Allocator>::iterator iterator;
		typedef typename std::vector<T*, Allocator>::const_iterator const_iterator;

		ptr_vector(): std::vector<T*, Allocator>() {};
		explicit ptr_vector(const Allocator& a): std::vector<T*, Allocator>(a) {};
		explicit ptr_vector(size_type n): std::vector<T*, Allocator>(n) {};

		iterator erase(iterator pos)
		{
			delete *pos;
			return std::vector<T*, Allocator>::erase(pos);
		}

		iterator erase(iterator from, iterator to)
		{
			iterator i;
			for (i = from; i != to; ++i)
				delete *i;
			return std::vector<T*, Allocator>::erase(from, to);
		}

		void clear()
		{
			iterator i;
			for (i = this->begin(); i != this->end(); ++i)
				delete *i;
			std::vector<T*, Allocator>::clear();
		}

		~ptr_vector()
		{
			iterator i;
			for (i = this->begin(); i != this->end(); ++i)
				delete *i;
		}
	};

	template<typename T, typename Allocator=std::allocator<T*> >
	class array_ptr_vector: public std::vector<T*, Allocator>
	{
	public:
		typedef typename std::vector<T*, Allocator>::size_type size_type;
		typedef typename std::vector<T*, Allocator>::iterator iterator;
		typedef typename std::vector<T*, Allocator>::const_iterator const_iterator;

		array_ptr_vector(): std::vector<T*, Allocator>() {};
		explicit array_ptr_vector(const Allocator& a): std::vector<T*, Allocator>(a) {};
		explicit array_ptr_vector(size_type n): std::vector<T*, Allocator>(n) {};

		iterator erase(iterator pos)
		{
			delete[] *pos;
			return std::vector<T*, Allocator>::erase(pos);
		}

		iterator erase(iterator from, iterator to)
		{
			iterator i;
			for (i = from; i != to; ++i)
				delete[] *i;
			return std::vector<T*, Allocator>::erase(from, to);
		}

		void clear()
		{
			iterator i;
			for (i = this->begin(); i != this->end(); ++i)
				delete[] *i;
			std::vector<T*, Allocator>::clear();
		}

		~array_ptr_vector()
		{
			iterator i;
			for (i = this->begin(); i != this->end(); ++i)
				delete[] *i;
		}
	};
} //namespace grape

#endif /*GRAPE_VECTOR_H*/
