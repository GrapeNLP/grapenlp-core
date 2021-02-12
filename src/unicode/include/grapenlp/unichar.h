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

#ifndef GRAPENLP_UNICHAR_H
#define GRAPENLP_UNICHAR_H

//namespace grapenlp
//{
//In Windows, wchar_t is a 16 bit unsigned integer
#if defined(WIN32)
typedef wchar_t unichar;

//In Linux, wchar_t is a 32 bit unsigned integer, but we only need 16 for UTF-16 chars
//We waste memory, but std::wcout << unichar(c) prints a char instead of a number
#elif defined(UNIX) && defined(TRACE)
typedef wchar_t unichar;

//No unichar printing is required, so we define unichars as 16 bit unsigned integers
#elif defined(UNIX) && !defined(TRACE)
#include <grapenlp/unsigned_int_char_traits.h>
typedef unsigned short unichar;

//Other platforms will probably be production servers, so we stick to the 16 bit unsigned integers
#else //compile for default platform
typedef unsigned short unichar;
#endif
//} //namespace grapenlp

#endif /*GRAPENLP_UNICHAR_H*/
