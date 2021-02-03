/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@gmail.com>
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

#ifndef GRAPENLP_ITERATOR_WRAPPER_H
#define GRAPENLP_ITERATOR_WRAPPER_H

#include <iterator>
#include <cstddef>

namespace grapenlp
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

		value_type& operator* ()
		{ return *the_iterator; } 

		Iterator& operator-> ()
		{ return the_iterator; } 

		bool operator== (const Iterator &i) const
		{ return the_iterator == i; }

		bool operator== (const this_type &iw) const
		{ return the_iterator == iw.the_iterator; }

		bool operator!= (const Iterator &i) const
		{ return the_iterator != i; }

		bool operator!= (const this_type &iw) const
		{ return the_iterator != iw.the_iterator; }

		bool operator< (const Iterator &i) const
		{ return the_iterator < i; }

		bool operator< (const this_type &iw) const
		{ return the_iterator < iw.the_iterator; }

		bool operator> (const Iterator &i) const
		{ return the_iterator > i; }

		bool operator> (const this_type &iw) const
		{ return the_iterator > iw.the_iterator; }

		bool operator<= (const Iterator &i) const
		{ return the_iterator <= i; }

		bool operator<= (const this_type &iw) const
		{ return the_iterator <= iw.the_iterator; }

		bool operator>= (const Iterator &i) const
		{ return the_iterator >= i; }

		bool operator>= (const this_type &iw) const
		{ return the_iterator >= iw.the_iterator; }

		void operator++ ()
		{ ++the_iterator; }

		void operator++ (int i)
		{ the_iterator++; }

		void operator-- ()
		{ --the_iterator; }

		void operator-- (int i)
		{ the_iterator--; }

		std::size_t operator- (const this_type &iw) const
		{ return the_iterator - iw.the_iterator; }

		std::size_t operator- (const Iterator &i) const
		{ return the_iterator - i; }
	};
} //namespace grapenlp

#endif /*GRAPENLP_ITERATOR_WRAPPER_H*/
