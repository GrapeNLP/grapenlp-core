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

#include <cstdlib>
#include <ctime>
#include <fstream>

#include <boost/program_options.hpp>

#include <grapenlp/string.h>
#include <grapenlp/functional.h>

template<typename First, typename Second, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const std::pair<First, Second> &p)
{ return out << '(' << p.first << ", " << p.second << ')'; }

#include <grapenlp/lrb_tree_map.h>
#include <grapenlp/lrb_tree_to_dot_serializer.h>

#define CEIL_INT 1000
#define INTS_TO_INSERT 100
#define INTS_TO_DELETE 100
#define BOUNDS 10

using namespace std;
using namespace boost;
using namespace boost::program_options;
using namespace grapenlp;

typedef lrb_tree_map<int, int> map_type;

bool is_digit(char c)
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

std::pair<int, int> parse_int_pair(std::string::const_iterator &begin, std::string::const_iterator end)
{
	int i(parse_int(begin, end));
	if (begin == end)
	{
		cout << "Expected a pair of ints but found only one\n";
		exit(1);
	}
	if (*begin != ',')
	{
		cout << "Expected ',' but got '" << *begin << "'\n";
		exit(1);
	}
	++begin;
	int j(parse_int(begin, end));
	return std::make_pair(i, j);
}

void add_int_pairs(vector<std::pair<int, int> > &ints, const std::string &int_list)
{
	if (int_list.empty())
		return;
	std::string::const_iterator begin(int_list.begin());
	std::string::const_iterator end(int_list.end());
	ints.push_back(parse_int_pair(begin, end));
	while (begin != end)
	{
		if (*begin != ',')
		{
			cout << "Expecting a ',' but got '" << *begin << "' while reading an integer list\n";
			exit(1);
		}
		++begin;
		ints.push_back(parse_int_pair(begin, end));
	}
}

void add_random_int_pairs(vector<std::pair<int, int> > &ints, size_t int_count, int max_int)
{
	for (; int_count > 0; --int_count)
		ints.push_back(std::pair<int, int>(rand() % max_int, rand() &max_int));
}

void add_ints(vector<int> &ints, const std::string &int_list)
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

void add_random_ints(vector<int> &ints, size_t int_count, int max_int)
{
	for (; int_count > 0; --int_count)
		ints.push_back(rand() % max_int);
}

int main(int argc, char **argv)
{
	vector<std::pair<int, int> > ints_to_insert;
	vector<int> ints_to_delete, bounds;
	vector<std::pair<int, int> >::const_iterator i;
	vector<int>::const_iterator j;
	map_type m;

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
		("insert,i", value<std::string>(), "Comma-separated list of pairs of integers to insert without spaces (e.g.: -i5,-3,18,9 where 5 maps -3 and 18 maps 9)")
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
		add_int_pairs(ints_to_insert, vm["insert"].as<std::string>());
	else add_random_int_pairs(ints_to_insert, INTS_TO_INSERT, CEIL_INT);
	if (vm.count("delete"))
		add_ints(ints_to_delete, vm["delete"].as<std::string>());
	else add_random_ints(ints_to_delete, INTS_TO_DELETE, CEIL_INT);
	if (vm.count("bounds"))
		add_ints(bounds, vm["bounds"].as<std::string>());
	else add_random_ints(bounds, BOUNDS, CEIL_INT);

	if (vm.count("sorted"))
	{
		std::cout << "Range insertion: ";
		map_type::iterator hint(m.begin());
		for (i = ints_to_insert.begin(); i != ints_to_insert.end(); ++i)
		{
			std::cout << *i << ' ';
			std::cout.flush();
			if (!m.insert_and_report(hint, *i).second)
				std::cout << "(repeated) ";
		}
	}
	else
	{
		std::cout << "Inserting: ";
		for (i = ints_to_insert.begin(); i != ints_to_insert.end(); ++i)
		{
			std::cout << *i << ' ';
			std::cout.flush();
			if (!m.insert(*i).second)
				std::cout << "(repeated) ";
		}
	}

	std::cout << std::endl;
	std::cout << "Printing: ";
	m.serialize(std::cout);
	std::cout << std::endl;
	std::cout << "Reverse printing: ";
	m.reverse_serialize(std::cout);
	std::cout << std::endl;

	std::wofstream fout;
	fout.open("../lrb_tree.dot");
	if (fout)
	{
		lrb_tree_to_dot_serialize(fout, "lrb_tree", m.get_tree());
		fout.close();
	}
	else std::wcerr << "Unable to open file \"lrb_tree.dot\" for writing" << std::endl;
	std::cout << "Written \"../lrb_tree.dot\"\n";

	for (j = bounds.begin(); j != bounds.end(); ++j)
	{
		std::cout << "Lower / upper bound of " << *j << " is ";
		std::cout.flush();
		map_type::iterator it(m.lower_bound(*j));
		if (it == m.end())
			std::cout << " none";
		else std::cout << *it;
		std::cout << " / ";
		it = m.upper_bound(*j);
		if (it == m.end())
			std::cout << " none";
		else std::cout << *it;
		std::cout << std::endl;
	}

	std::cout << "Deleting ";
	for (j = ints_to_delete.begin(); j != ints_to_delete.end(); ++j)
	{
		std::cout << *j << ' ';
		std::cout.flush();
		if (m.erase(*j))
			std::cout << "(present) ";
	}

	std::cout << std::endl;
	std::cout << "Printing: ";
	m.serialize(std::cout);
	std::cout << std::endl;
	std::cout << "Reverse printing: ";
	m.reverse_serialize(std::cout);
	std::cout << std::endl;

	fout.open("../lrb_tree_deleted.dot");
	if (fout)
	{
		lrb_tree_to_dot_serialize(fout, "lrb_tree_deleted", m.get_tree());
		fout.close();
	}
	else std::wcerr << "Unable to open file \"lrb_tree_deleted.dot\" for writing" << std::endl;
	std::cout << "Written \"../lrb_tree_deleted.dot\"\n";

	std::cout << "Destroying" << std::endl;
	return 0;
}
