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

#ifndef GRAPE_TOKEN_H
#define GRAPE_TOKEN_H

#include <ostream>

#include <grape/vector.h>

namespace grape
{
	enum token_type
	{
		WORD_TOKEN,
		UPPER_WORD_TOKEN,
		LOWER_WORD_TOKEN,
		FIRST_UPPER_WORD_TOKEN,
		WHITE_TOKEN,
		DIGIT_TOKEN,
		SYMBOL_TOKEN
	};

	template<typename InputIterator>
	struct token
	{
	public:
		typedef token* ref;
		typedef const token* const_ref;
		typedef ptr_vector<token> ref_list;

		InputIterator begin, end;
		const token_type my_type;

		token(InputIterator begin_, InputIterator end_, token_type type_) : begin(begin_), end(end_), my_type(type_)
		{}

		bool is_word() const
		{ return my_type <= FIRST_UPPER_WORD_TOKEN; }

		bool is_upper_word() const
		{ return my_type == UPPER_WORD_TOKEN; }

		bool is_lower_word() const
		{ return my_type == LOWER_WORD_TOKEN; }

		bool is_first_upper_word() const
		{ return my_type == FIRST_UPPER_WORD_TOKEN; }

		bool is_digit() const
		{ return my_type == DIGIT_TOKEN; }

		bool is_white() const
		{ return my_type == WHITE_TOKEN; }

		bool is_symbol() const
		{ return my_type == SYMBOL_TOKEN; }

		std::size_t size()
		{ return std::distance(begin, end);	}
	};

	template<typename InputIterator, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const token<InputIterator> &t)
	{
		InputIterator i(t.begin);
		for (; i != t.end; ++i)
			out << *i;
		return out;
	}
}//namespace grape

#endif /*GRAPE_TOKEN_H*/
