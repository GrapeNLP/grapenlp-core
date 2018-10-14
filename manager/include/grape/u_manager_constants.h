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

#ifndef GRAPE_U_MANAGER_CONSTANTS_H
#define GRAPE_U_MANAGER_CONSTANTS_H

#include <array>

#include <grape/unicode.h>

namespace grape
{
	const std::array<unichar, 4> ua_true = { {'t', 'r', 'u', 'e'} };
	const std::array<unichar, 5> ua_false = { {'f', 'a', 'l', 's', 'e'} };
	const std::array<unichar, 18> to_canonical_form_mark = { {'t', 'o', '_', 'c', 'a', 'n', 'o', 'n', 'i', 'c', 'a', 'l', '_', 'f', 'o', 'r', 'm', ' '} };
	const std::array<unichar, 8> unknown_mark = { {'u', 'n', 'k', 'n', 'o', 'w', 'n', ' '} };
} //namespace grape

#endif /*GRAPE_U_DELAF_CONSTANTS_H*/
