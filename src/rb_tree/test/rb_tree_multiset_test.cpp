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

#include <grapenlp/mtrace.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <queue>

#include <boost/program_options.hpp>

#include <grapenlp/string.h>
#include <grapenlp/functional.h>
#include <grapenlp/rb_tree_multiset.h>
#include <grapenlp/rb_tree_to_dot_serializer.h>

#define CEIL_INT 1000
#define INTS_TO_INSERT 100
#define INTS_TO_DELETE 100
#define BOUNDS 10

using namespace std;
using namespace boost;
using namespace boost::program_options;
using namespace grapenlp;

typedef rb_tree_multiset<int> multiset_type;

inline bool is_digit(char c)
{
	return c >= '0' && c <= '9';
}

int parse_int(std::string::const_iterator &begin, std::string::const_iterator end)
{
	bool negative(false);
	if (*begin == '-' || *begin == '+')
	{
		negative = *begin == '-';
		++begin;
		if (begin == end)
		{
			cout << "Sign followed by no digit\n";
			exit(1);
		}
	}
	int i(0);
	while (begin != end && is_digit(*begin))
	{
		i = i * 10 + *begin - '0';
		++begin;
	}
	if (negative)
		return -i;
	return i;
}

inline void add_ints(vector<int> &ints, const std::string &int_list)
{
	if (int_list.empty())
		return;
	std::string::const_iterator begin(int_list.begin());
	std::string::const_iterator end(int_list.end());
	ints.push_back(parse_int(begin, end));
	while (begin != end)
	{
		if (*begin != ',')
		{
			cout << "Expecting a ',' but got '" << *begin << "' while reading an integer list\n";
			exit(1);
		}
		++begin;
		ints.push_back(parse_int(begin, end));
	}
}

inline void add_random_ints(vector<int> &ints, size_t int_count, int max_int)
{
	for (; int_count > 0; --int_count)
		ints.push_back(rand() % max_int);
}

int main(int argc, char **argv)
{
	vector<int> ints_to_insert, ints_to_delete, bounds;
	vector<int>::const_iterator i;
	multiset_type s;

	//Retrieve program name from program path-name
	grapenlp::string program_name(argv[0]);
#ifdef WIN32
	std::size_t last_slash_pos(program_name.find_last_of('\\'));
#else
	std::size_t last_slash_pos(program_name.find_last_of('/'));
#endif
	if (last_slash_pos != grapenlp::string::npos)
		program_name = program_name.substr(last_slash_pos + 1, program_name.length());
	// Declare the possible command line arguments
	options_description desc("Options");
	desc.add_options()
		("help,h", "Display this information")
		("insert,i", value<std::string>(), "Comma-separated list of integers to insert without spaces (e.g.: -i5,-3,18,9)")
		("sorted,s", "Use efficient insertion of sorted ranges of integers (though the list might not be sorted)")
		("delete,d", value<std::string>(), "Comma-separated list of integers to delete without spaces (e.g.: -d34,18,-3,0)")
		("bounds,b", value<std::string>(), "Comma-separated list of integers without spaces whose upper and lower bounds are to be computed (e.g.: -b10,-1,3,5)")
		("count,c", value<std::size_t>(), "Number of random integers to insert (if integer list is not provided)")
	;

	//Parse argument list
	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);
	notify(vm);

	if (vm.count("help"))
	{
		cout << "Usage: " << program_name.c_str() << " [options] grammar dictionary input output [validate]" << std::endl;
		cout << desc;
		return 0;
	}

	srand(time(NULL));
	if (vm.count("insert"))
	{
		add_ints(ints_to_insert, vm["insert"].as<std::string>());
	}
	else
	{
		add_random_ints(ints_to_insert, INTS_TO_INSERT, CEIL_INT);
	}
	if (vm.count("delete"))
		add_ints(ints_to_delete, vm["delete"].as<std::string>());
	else add_random_ints(ints_to_delete, INTS_TO_DELETE, CEIL_INT);
	if (vm.count("bounds"))
	{
		add_ints(bounds, vm["bounds"].as<std::string>());
	}
	else add_random_ints(bounds, BOUNDS, CEIL_INT);

	if (vm.count("sorted"))
	{
		std::cout << "Range insertion: ";
		multiset_type::iterator hint(s.begin());
		for (i = ints_to_insert.begin(); i != ints_to_insert.end(); ++i)
		{
			std::cout << *i << ' ';
			std::cout.flush();
			multiset_type::iterator k(s.insert(hint, *i));
			if (k != s.begin())
			{
				multiset_type::iterator l(k);
				--l;
				if (*k == *l)
					std::cout << "(repeated) ";
			}
		}
	}
	else
	{
		std::cout << "Inserting: ";
		for (i = ints_to_insert.begin(); i != ints_to_insert.end(); ++i)
		{
			std::cout << *i << ' ';
			std::cout.flush();
			multiset_type::iterator k(s.insert(*i));
			multiset_type::iterator l(k);
			--k;
			if (*k == *l)
				std::cout << "(repeated) ";
		}
	}

	std::cout << std::endl;
	std::cout << "Printing: ";
	s.serialize(std::cout);
	std::cout << std::endl;
	std::cout << "Reverse printing: ";
	s.reverse_serialize(std::cout);
	std::cout << std::endl;

	std::wofstream fout;
	fout.open("../rb_tree.dot");
	if (fout)
	{
		rb_tree_to_dot_serialize(fout, "rb_tree", s.get_tree());
		fout.close();
	}
	else std::wcerr << "Unable to open file \"rb_tree.dot\" for writing" << std::endl;
	std::cout << "Written \"../rb_tree.dot\"\n";

	for (i = bounds.begin(); i != bounds.end(); ++i)
	{
		std::cout << "Lower / upper bound of " << *i << " is ";
		std::cout.flush();
		multiset_type::iterator it(s.lower_bound(*i));
		if (it == s.end())
			std::cout << " none";
		else std::cout << *it;
		std::cout << " / ";
		it = s.upper_bound(*i);
		if (it == s.end())
			std::cout << " none";
		else std::cout << *it;
		std::cout << std::endl;
	}

/*	std::cout << "Deleting ";
	for (i = ints_to_delete.begin(); i != ints_to_delete.end(); ++i)
	{
		std::cout << *i << ' ';
		std::cout.flush();
		if (s.erase(*i))
			std::cout << "(present) ";
	}

	std::cout << std::endl;
	std::cout << "Printing: ";
	s.serialize(std::cout);
	std::cout << std::endl;
	std::cout << "Reverse printing: ";
	s.reverse_serialize(std::cout);
	std::cout << std::endl;

	fout.open("../rb_tree_deleted.dot");
	if (fout)
	{
		rb_tree_to_dot_serialize(fout, "rb_tree_deleted", s.get_tree());
		fout.close();
	}
	else std::wcerr << "Unable to open file \"rb_tree_deleted.dot\" for writing" << std::endl;
	std::cout << "Written \"../rb_tree_deleted.dot\"\n";
*/
	std::cout << "Destroying" << std::endl;
	return 0;
}
