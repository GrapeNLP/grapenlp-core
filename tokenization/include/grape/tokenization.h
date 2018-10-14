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

#ifndef GRAPE_TOKENIZATION_H
#define GRAPE_TOKENIZATION_H

#ifdef TRACE
#include <iostream>
#endif

#include <grape/unicode.h>
#include <grape/token.h>

namespace grape
{
	//The purpose of this constant is to estimate the size of the vector of tokens, once computed the size of the char sequence
	const unsigned char average_chars_per_token = 6;

	template<typename InputIterator>
	typename token<InputIterator>::ref_list& tokenize(InputIterator begin, InputIterator end, typename token<InputIterator>::ref_list& the_token_list)
	{
#ifdef TRACE
		std::size_t token_count(0);
#endif
		the_token_list.reserve((end - begin)/average_chars_per_token);
		token<InputIterator> *t;
		InputIterator c = begin;
		token_type t_type;

		while (c != end)
		{
			//Word token
#ifdef TRACE
			std::wcout << L"*** TOKEN START ***\n";
			std::wcout << L"Evaluating '" << *c << L"'\n";
#endif
			if (u_is_letter(*c))
			{
#ifdef TRACE
				std::wcout << L"Starting new word\n";
#endif
				//Starting by lowercase letter
				if (u_is_lower(*c))
				{
#ifdef TRACE
					std::wcout << L"Starts by lowercase\n";
#endif
					do
					{
						++c;
#ifdef TRACE
						if (c != end)
							std::wcout << L"Evaluating '" << *c << L"'\n";
#endif
					}
					while (c != end && u_is_letter(*c) && u_is_lower(*c));
					//But not all lowercase . . . get the remaining letters
					if (c != end && u_is_letter(*c))
					{
#ifdef TRACE
						std::wcout << L"Detected word (not lowercase, uppercase or first-uppercase)\n";
#endif
						do
						{
							++c;
#ifdef TRACE
							if (c != end)
								std::wcout << L"Evaluating '" << *c << L"'\n";
#endif
						}
						while (c != end && u_is_letter(*c));
						t_type = WORD_TOKEN;
					}
					//All lowercase
					else
					{
						t_type = LOWER_WORD_TOKEN;
#ifdef TRACE
						std::wcout << L"Detected lowercase word\n";
#endif
					}
				}
				//Starting by uppercase letter
				else
				{
					++c;
#ifdef TRACE
					if (c != end)
						std::wcout << L"Evaluating '" << *c << L"'\n";
#endif
					//Single uppercase letter word
					if (c == end || !u_is_letter(*c))
					{
						t_type = UPPER_WORD_TOKEN;
#ifdef TRACE
						std::wcout << L"Detected single uppercase letter word\n";
#endif
					}
					else
					{
						//And following a lowercase letter
						if (u_is_lower(*c))
						{
							//Read the following of the lowercase letters
							do
							{
								++c;
#ifdef TRACE
								if (c != end)
									std::wcout << L"Evaluating '" << *c << L"'\n";
#endif
							}
							while (c != end && u_is_letter(*c) && u_is_lower(*c));
							//But not all are lowercase . . . get the remaining letters
							if (c != end && u_is_letter(*c))
							{
								do
								{
									++c;
#ifdef TRACE
									if (c != end)
										std::wcout << L"Evaluating '" << *c << L"'\n";
#endif
								}
								while (c != end && u_is_letter(*c));
								t_type = WORD_TOKEN;
#ifdef TRACE
								std::wcout << L"Detected word (not lowercase, uppercase or first-uppercase)\n";
#endif
							}
							//All lowercase letters except the first one
							else
							{
								t_type = FIRST_UPPER_WORD_TOKEN;
#ifdef TRACE
								std::wcout << L"Detected first-uppercase word\n";
#endif
							}
						}
						//And following an uppercase letter
						else
						{
							//Read the following of the uppercase letters
							do
							{
								++c;
#ifdef TRACE
								if (c != end)
									std::wcout << L"Evaluating '" << *c << L"'\n";
#endif
							}
							while (c != end && u_is_letter(*c) && u_is_upper(*c));
							//But not all are uppercase . . . get the remaining letters
							if (c != end && u_is_letter(*c))
							{
								do
								{
									++c;
#ifdef TRACE
									if (c != end)
										std::wcout << L"Evaluating '" << *c << L"'\n";
#endif
								}
								while (c != end && u_is_letter(*c));
								t_type = WORD_TOKEN;
#ifdef TRACE
								std::wcout << L"Detected word (not lowercase, uppercase or first-uppercase)\n";
#endif
							}
							//All uppercase letters
							else
							{
								t_type = UPPER_WORD_TOKEN;
#ifdef TRACE
								std::wcout << L"Detected uppercase word\n";
#endif
							}
						}
					}
				}
			}
			else if (u_is_white(*c))
			{
				t_type = WHITE_TOKEN;
				do
				{
					++c;
#ifdef TRACE
					if (c != end)
						std::wcout << L"Evaluating '" << *c << L"'\n";
#endif
				}
				while (c != end && u_is_white(*c));
#ifdef TRACE
				std::wcout << L"Detected white\n";
#endif
			}
			else
			{
				if (u_is_digit(*c))
				{
					t_type = DIGIT_TOKEN;
#ifdef TRACE
					std::wcout << L"Detected digit\n";
#endif
				}
				else
				{
					t_type = SYMBOL_TOKEN;
#ifdef TRACE
					std::wcout << L"Detected symbol\n";
#endif
				}
				++c;
			}
#ifndef WHITE
			if (t_type != WHITE_TOKEN)
#endif
			{
				t = new token<InputIterator>(begin, c, t_type);
#ifdef TRACE
				std::wcout << "Token " << token_count << L": " << *t << std::endl;
				token_count++;
#endif
				the_token_list.push_back(t);
			}
			begin = c;
		}
#ifdef TRACE
		std::wcout << L"Token count: " << token_count << std::endl;
#endif
		return the_token_list;
	}
}//namespace grape

#endif /*GRAPE_TOKENIZATION_H*/
