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

#ifndef GRAPE_COUNTER_H
#define GRAPE_COUNTER_H

#include <cstring>

namespace grape
{
	template<typename SizeType = std::size_t>
	struct counter
	{
		typedef SizeType size_type;

		size_type count;

		counter(): count()
		{}

		counter(size_type init): count(init)
		{}

		counter(const counter &c): count(c.count)
		{}

		counter& operator= (const counter &c)
		{
			count = c.count;
			return *this;
		}

		size_type value()
		{ return count; }

		void inc()
		{ ++count; }

		void inc(size_type step)
		{ count += step; }

		void dec()
		{ --count; }

		void dec(size_type step)
		{ count -= step; }
	};
} //namespace grape

#endif /*GRAPE_COUNTER_H*/
