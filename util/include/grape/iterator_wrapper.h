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

#ifndef GRAPE_ITERATOR_WRAPPER_H
#define GRAPE_ITERATOR_WRAPPER_H

#include <iterator>
#include <cstddef>

namespace grape
{
	template<typename Iterator>
	struct iterator_wrapper
	{
		typedef iterator_wrapper<Iterator> this_type;

		typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename std::iterator_traits<Iterator>::value_type value_type;
		typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename std::iterator_traits<Iterator>::pointer pointer;
		typedef typename std::iterator_traits<Iterator>::reference reference;

		Iterator the_iterator;

		iterator_wrapper(Iterator the_iterator_): the_iterator(the_iterator_)
		{};

		iterator_wrapper(const iterator_wrapper<Iterator> &iw): the_iterator(iw.the_iterator)
		{};

		inline value_type& operator* ()
		{ return *the_iterator; } 

		inline Iterator& operator-> ()
		{ return the_iterator; } 

		inline bool operator== (const Iterator &i) const
		{ return the_iterator == i; }

		inline bool operator== (const this_type &iw) const
		{ return the_iterator == iw.the_iterator; }

		inline bool operator!= (const Iterator &i) const
		{ return the_iterator != i; }

		inline bool operator!= (const this_type &iw) const
		{ return the_iterator != iw.the_iterator; }

		inline bool operator< (const Iterator &i) const
		{ return the_iterator < i; }

		inline bool operator< (const this_type &iw) const
		{ return the_iterator < iw.the_iterator; }

		inline bool operator> (const Iterator &i) const
		{ return the_iterator > i; }

		inline bool operator> (const this_type &iw) const
		{ return the_iterator > iw.the_iterator; }

		inline bool operator<= (const Iterator &i) const
		{ return the_iterator <= i; }

		inline bool operator<= (const this_type &iw) const
		{ return the_iterator <= iw.the_iterator; }

		inline bool operator>= (const Iterator &i) const
		{ return the_iterator >= i; }

		inline bool operator>= (const this_type &iw) const
		{ return the_iterator >= iw.the_iterator; }

		inline void operator++ ()
		{ ++the_iterator; }

		inline void operator++ (int i)
		{ the_iterator++; }

		inline void operator-- ()
		{ --the_iterator; }

		inline void operator-- (int i)
		{ the_iterator--; }

		inline std::size_t operator- (const this_type &iw) const
		{ return the_iterator - iw.the_iterator; }

		inline std::size_t operator- (const Iterator &i) const
		{ return the_iterator - i; }
	};
} //namespace grape

#endif /*GRAPE_ITERATOR_WRAPPER_H*/
