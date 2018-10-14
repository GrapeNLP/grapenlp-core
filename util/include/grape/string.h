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

#ifndef GRAPE_STRING_H
#define GRAPE_STRING_H

#include <iterator>
#include <string>

#include <grape/algorithm.h>

namespace grape
{
	template<typename CharT, typename Traits = std::char_traits<CharT> >
	struct basic_string: public std::basic_string<CharT, Traits>
	{
		typedef std::basic_string<CharT, Traits> base_type;

		explicit basic_string (): base_type()
		{}

		basic_string (const std::basic_string<CharT, Traits>& str): base_type(str)
		{}

		basic_string (const std::basic_string<CharT, Traits>& str, std::size_t pos, std::size_t n = base_type::npos): base_type(str, pos, n)
		{}

		basic_string (const CharT *s, std::size_t n): base_type(s, n)
		{}

		basic_string (const CharT *s): base_type(s)
		{}

		basic_string (std::size_t n, CharT c): base_type(n, c)
		{}

		CharT front() const
		{ return *this->begin(); }

		CharT back() const
		{ return *this->rbegin(); }

		template<std::size_t N>
		bool starts_with(const CharT s[N]) const
		{ return grape::starts_with(this->begin(), this->end(), s); }

		bool starts_with(const CharT c) const
		{ return !this->empty() && this->front() == c; }

		bool starts_with(const base_type &str) const
		{ return grape::starts_with(this->begin(), this->end(), str.begin(), str.end()); }

		template<typename CharIterator>
		bool starts_with(CharIterator begin, CharIterator end) const
		{ return grape::starts_with(begin(), end(), begin, end); }

		template<std::size_t N>
		bool ends_with(const CharT s[N]) const
		{ return grape::ends_with(this->begin(), this->end(), s); }

		bool ends_with(const CharT c) const
		{ return !this->empty() && this->back() == c; }

		bool ends_with(const base_type &str) const
		{ return grape::ends_with(this->begin(), this->end(), str.begin(), str.end()); }

		template<typename CharIterator>
		bool ends_with(CharIterator begin, CharIterator end) const
		{ return grape::ends_with(begin(), end(), begin, end); }
	};

	typedef basic_string<char, std::char_traits<char> > string;
	typedef basic_string<wchar_t, std::char_traits<wchar_t> > wstring;
} //namespace grape

#endif /*GRAPE_STRING_H*/
