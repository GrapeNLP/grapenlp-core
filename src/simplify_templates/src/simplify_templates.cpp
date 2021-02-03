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

/*
 *  This tool is intended to simplify the output of C++ compilers for the case of
 *  C++ code making an intensive use of templates.
 *  It indiscriminately replaces every string of the form "class_name<···<···>···>"
 *  by "class_name<>", that is, it removes the arguments of templates and leaves "<>"
 *  in order to mark removed template arguments.
 *  It takes into account that chars '<' and '>' in "<<" and ">>" are not start or end
 *  chars of template argument declarations but there should be at least one space or
 *  any other char in between. This avoids chars '<' and '>' of "operator<<" and
 *  "operator>>" to be interpreted as start and end chars of a template argument
 *  declarations. As well, chars '>' are not interpreted as end of template argument
 *  declarations if no unclosed '<' was found before in order to correctly process
 *  sequences such as "pointer->field".
 */

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	//We use "cin.get()" instead of "cin >>" since the second option skips newline chars
	char c1(cin.get());
	if (cin.eof())
		return 0;
	char c2(cin.get());
	if (cin.eof())
	{
		cout << c1;
		return 0;
	}
	size_t template_level(0);
	//While there are chars left
	while (!cin.eof())
	{
		//If reached start of template argument declaration: reached char '<' of "class_name<....>", but not of "operator<<"
		if (c1 == '<')
		{
			//If second consecutive '<', print every consecutive '<' if at top template level and skip all of them
			if (c2 == '<')
			{
				do
				{
					if (!template_level)
						cout << c1;
					c1 = c2;
					c2 = cin.get();
				} while (!cin.eof() && c1 == '<');
				if (cin.eof())
				{
					cout << '<';
					return 0;
				}
			}
			//Else print '<' only for the top level template declaration (level 0)
			else
			{
				if (!template_level)
					cout << '<';
				++template_level;
				c1 = c2;
				c2 = cin.get();
			}
		}
		//If reached end of template argument declaration: reached char '>' of "class_name<....>", but not of "operator>>" or "pointer->field"
		else if (template_level > 0 && c1 == '>')
		{
			//If second consecutive '>', print every consecutive '>' if at top template level and skip all of them
			if (c2 == '>')
			{
				do
				{
					if (!template_level)
						cout << c1;
					c1 = c2;
					c2 = cin.get();
				} while (!cin.eof() && c1 == '>');
				if (cin.eof())
				{
					cout << '>';
					return 0;
				}
			}
			//Else print '>' only for the top level template declaration (level 0)
			else
			{
				--template_level;
				if (!template_level)
					cout << '>';
				c1 = c2;
				c2 = cin.get();
			}
		}
		//If not reached start or end of template argument declaration, just print the char if at top template level
		else
		{
			if (!template_level)
				cout << c1;
			c1 = c2;
			c2 = cin.get();
		}
	}
	//Print last char
	cout << c1;
	return 0;
}
