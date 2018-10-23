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

#ifndef GRAPENLP_MEMORY_H
#define GRAPENLP_MEMORY_H

#include <memory>
#include <type_traits>

namespace grapenlp
{
	template<typename Allocator, bool = std::is_empty<Allocator>::value>
	struct allocator_swapper
	{
		void operator() (Allocator& a1, Allocator& a2)
		{}
	};

	template<typename Allocator>
	struct allocator_swapper<Allocator, false>
	{
		void operator()(Allocator& a1, Allocator &a2) const
		{
			if (a1 != a2)
				std::swap(a1, a2);
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_MEMORY_H*/
