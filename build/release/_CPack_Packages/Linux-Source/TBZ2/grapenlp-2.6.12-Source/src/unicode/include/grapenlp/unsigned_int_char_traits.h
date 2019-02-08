/*
 * GRAPENLP
 *
 * Copyright (C) 2011-2012 Universidad de Alicante <javier.sastre@telefonica.net>
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

#ifndef GRAPENLP_UNSIGNED_INT_CHAR_TRAITS_H
#define GRAPENLP_UNSIGNED_INT_CHAR_TRAITS_H

#include <string>

namespace std
{
	template<>
	struct char_traits<unsigned int>
	{
		typedef unsigned int char_type;
		typedef unsigned int int_type;
		typedef streamoff off_type;
		typedef streampos pos_type;
		typedef mbstate_t state_type;

		static void assign(char_type& __c1, const char_type& __c2)
		{ __c1 = __c2; }

	    static bool eq(const char_type& __c1, const char_type& __c2)
	    { return __c1 == __c2; }

	    static bool lt(const char_type& __c1, const char_type& __c2)
	    { return __c1 < __c2; }

	    static int compare(const char_type* __s1, const char_type* __s2, size_t __n)
	    {
	    	for (size_t __i = 0; __i < __n; ++__i)
	    		if (lt(__s1[__i], __s2[__i]))
	    			return -1;
	    		else if (lt(__s2[__i], __s1[__i]))
	    			return 1;
	    	return 0;
	    }

	    static size_t length(const char_type* __s)
	    {
	    	size_t __i = 0;
	    	while (!eq(__s[__i], char_type()))
	    		++__i;
	    	return __i;
	    }

	    static const char_type* find(const char_type* __s, size_t __n, const char_type& __a)
	    {
	    	for (size_t __i = 0; __i < __n; ++__i)
				if (eq(__s[__i], __a))
				  return __s + __i;
			return 0;
	    }

	    static char_type* move(char_type* __s1, const char_type* __s2, size_t __n)
	    { return (static_cast<char_type*>(__builtin_memmove(__s1, __s2, __n * sizeof(char_type)))); }

	    static char_type* copy(char_type* __s1, const char_type* __s2, size_t __n)
	    { return (static_cast<char_type*>(__builtin_memcpy(__s1, __s2, __n * sizeof(char_type)))); }

	    static char_type* assign(char_type* __s, size_t __n, char_type __a)
	    {
	    	for (size_t __i = 0; __i < __n; ++__i)
	    		assign(__s[__i], __a);
	    	return __s;
	    }

	    static char_type to_char_type(const int_type& __c)
	    { return char_type(__c); }

	    static int_type to_int_type(const char_type& __c)
	    { return int_type(__c); }

	    static bool eq_int_type(const int_type& __c1, const int_type& __c2)
	    { return __c1 == __c2; }

	    static int_type eof()
	    { return static_cast<int_type>(-1); }

	    static int_type not_eof(const int_type& __c)
	    { return eq_int_type(__c, eof()) ? 0 : __c; }
	};
} //namespace std

#endif /*GRAPENLP_UNSIGNED_INT_CHAR_TRAITS_H*/
