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

#ifndef GRAPENLP_EMPTY_CLASS_H
#define GRAPENLP_EMPTY_CLASS_H

namespace grapenlp
{
	//The empty class is used for defining template a class A having an optional member
	//om depending on template parameter:
	//template<typename OptionalMember=empty_class>
	//om must not be declared inside A but A must inherit OptionalMember
	//in order to take advantage of the empty class optimization:
	//the former results in extra space being reserved for the representation of om, while
	//the latter omits om representation (seach for "C++ empty class optimization")
	class empty_class
	{};
} //namespace grapenlp

#endif /*GRAPENLP_EMPTY_CLASS_H*/
