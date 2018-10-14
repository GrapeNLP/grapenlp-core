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

#include <grape/mtrace.h>

#include <set>
#include <grape/lrb_tree_set.h>
#include <grape/lrb_tree_set_3w.h>
#include <grape/map_impl_selector.h>
#include <list>
#include <boost/timer.hpp>
#include <grape/string.h>

#ifdef TRACE
#define COUNT 2
#else
#define COUNT 40000000
#endif

#ifdef TRACE
std::size_t defconstruct = 0;
std::size_t construct = 0;
std::size_t copy = 0;
//std::size_t rcopy = 0;
std::size_t destruct = 0;
#endif

struct key
{
	std::size_t i;
	std::size_t j;

	key()
	{}

	key(std::size_t i_, std::size_t j_): i(i_), j(j_)
	{}

	key(const key &k): i(k.i), j(k.j)
	{}

//	key(key &&k): i(k.i), j(k.j)
//	{}

	bool operator< (const key &k) const
	{
		if (i < k.i)
			return true;
		if (k.i < i)
			return false;
		return j < k.j;
	}

	std::ptrdiff_t compare_3w(const key &k) const
	{
		std::ptrdiff_t result(i - k.i);
		if (result)
			return result;
		return j - k.j;
	}
};

struct mapped
{
	std::size_t k;
	std::size_t l;
	std::list<std::size_t> l1;
	std::list<std::size_t> l2;
	std::list<std::size_t> l3;
	std::list<std::size_t> l4;

	mapped(): l1(), l2(), l3(), l4()
	{
#ifdef TRACE
		++defconstruct;
//		std::cout << " defconstruct " << defconstruct;
//		std::cout.flush();
#endif
	}

	mapped(std::size_t k_, std::size_t l_): k(k_), l(l_), l1(), l2(), l3(), l4()
	{
#ifdef TRACE
		++construct;
//		std::cout << " construct " << construct;
//		std::cout.flush();
#endif
	}

	mapped(const mapped &m): k(m.k), l(m.l), l1(m.l1), l2(m.l2), l3(m.l3), l4(m.l4)
	{
#ifdef TRACE
		++copy;
//		std::cout << " copy " << copy;
//		std::cout.flush();
#endif
	}

//	mapped(mapped &&m): k(m.k), l(m.l), l1(std::move(m.l1)), l2(std::move(m.l2)), l3(std::move(m.l3)), l4(std::move(m.l4))
//	{

//		++rcopy;
//		std::cout << " copy " << copy;
//		std::cout.flush();
//	}

	~mapped()
	{
#ifdef TRACE
		++destruct;
//		std::cout << " destruct " << destruct;
//		std::cout.flush();
#endif
	}
};

struct map_elem: public std::pair<const key, mapped>
{
	typedef std::pair<const key, mapped> base_type;

	map_elem(std::size_t i, std::size_t j, std::size_t k, std::size_t l): base_type(key(i, j), mapped(k, l))
	{}

/*	map_elem(std::size_t i, std::size_t j, std::size_t k, std::size_t l): base_type()
	{
		const_cast<key&>(base_type::first).i = i;
		const_cast<key&>(base_type::first).j = j;
		base_type::second.k = k;
		base_type::second.l = l;
	}
*/
	map_elem(const map_elem &me): base_type(me)
	{}

	void set_mapped(std::size_t k, std::size_t l)
	{
		second.k = k;
		second.l = l;
	}
//	map_elem(map_elem &&me): base_type(std::move(me))
//	{}
};

struct set_elem
{
	std::size_t i;
	std::size_t j;
	mutable std::size_t k;
	mutable std::size_t l;
	mutable std::list<std::size_t> l1;
	mutable std::list<std::size_t> l2;
	mutable std::list<std::size_t> l3;
	mutable std::list<std::size_t> l4;

	set_elem(std::size_t i_, std::size_t j_, std::size_t k_, std::size_t l_): i(i_), j(j_), k(k_), l(l_), l1(), l2(), l3(), l4()
	{
#ifdef TRACE
		++construct;
//		std::cout << "construct " << construct << std::endl;
#endif
	}

	set_elem(const set_elem &se): i(se.i), j(se.j), k(se.k), l(se.l), l1(se.l1), l2(se.l2), l3(se.l3), l4(se.l4)
	{
#ifdef TRACE
		++copy;
//		std::cout << "copy " << copy << std::endl;
#endif
	}

//	set_elem(set_elem &&se): i(se.i), j(se.j), k(se.k), l(se.l), l1(std::move(se.l1)), l2(std::move(se.l2)), l3(std::move(se.l3)), l4(std::move(se.l4))
//	{
//		++rcopy;
//		std::cout << "copy " << copy << std::endl;
//	}

	~set_elem()
	{
#ifdef TRACE
		++destruct;
//		std::cout << "destruct " << destruct << std::endl;
#endif
	}

	bool operator< (const set_elem &se) const
	{
		if (i < se.i)
			return true;
		if (se.i < i)
			return false;
		return j < se.j;
	}

	std::ptrdiff_t compare_3w(const set_elem &se) const
	{
		std::ptrdiff_t result(i - se.i);
		if (result)
			return result;
		return j - se.j;
	}
};

void syntax_error(char *pn)
{
	//Retrieve program name from program path-name
	grape::string program_name(pn);
#ifdef WIN32
	std::size_t last_slash_pos(program_name.find_last_of('\\'));
#else
	std::size_t last_slash_pos(program_name.find_last_of('/'));
#endif
	if (last_slash_pos != grape::string::npos)
		program_name = program_name.substr(last_slash_pos + 1, program_name.length());

	std::cout << "Syntax: " << program_name << " [123456], where" << std::endl;
	std::cout << "1 chooses std::set" << std::endl;
	std::cout << "2 chooses grape::lrb_tree_set" << std::endl;
	std::cout << "3 chooses grape::lrb_tree_set_3w" << std::endl;
	std::cout << "4 chooses std::map" << std::endl;
	std::cout << "5 chooses grape::lrb_tree_map" << std::endl;
	std::cout << "6 chooses grape::lrb_tree_map_3w" << std::endl;
	std::cout << "7 chooses std::map with def mapped value" << std::endl;
	std::cout << "8 chooses grape::lrb_tree_map with def mapped value" << std::endl;
	std::cout << "9 chooses grape::lrb_tree_map_3w with def mapped value" << std::endl;
	exit(1);
}

char get_option(int argc, char **argv)
{
	if (argc != 2)
		syntax_error(*argv);
	if (argv[1][1] != '\0')
		syntax_error(*argv);
	char c(argv[1][0]);
	if (c < '1' || c > '9')
		syntax_error(*argv);
	return c;
}

int main(int argc, char **argv)
{
	char c(get_option(argc, argv));

	std::cout.precision(12);
	boost::timer t;

	std::set<set_elem> *m1;
	grape::lrb_tree_set<set_elem> *m2;
	grape::lrb_tree_set_3w<set_elem> *m3;
	std::map<key, mapped> *m4;
	grape::lrb_tree_map<key, mapped> *m5;
	grape::lrb_tree_map_3w<key, mapped> *m6;

	switch (c)
	{
	case '1':
		m1 = new std::set<set_elem>();
		t.restart();
		for (std::size_t i(0); i < COUNT; ++i)
			m1->insert(set_elem(i, i, i, i));
		delete m1;
		std::cout << "std::set: " << t.elapsed() << std::endl;
		break;
	case '2':
		m2 = new grape::lrb_tree_set<set_elem>();
		t.restart();
		for (std::size_t i(0); i < COUNT; ++i)
			m2->insert(set_elem(i, i, i, i));
		delete m2;
		std::cout << "lrb_tree_set: " << t.elapsed() << std::endl;
		break;
	case '3':
		m3 = new grape::lrb_tree_set_3w<set_elem>();
		t.restart();
		for (std::size_t i(0); i < COUNT; ++i)
			m3->insert(set_elem(i, i, i, i));
		delete m3;
		std::cout << "lrb_tree_set_3w: " << t.elapsed() << std::endl;
		break;
	case '4':
		m4 = new std::map<key, mapped>();
		t.restart();
		for (std::size_t i(0); i < COUNT; ++i)
			m4->insert(map_elem(i, i, i, i));
		delete m4;
		std::cout << "std::map: " << t.elapsed() << std::endl;
		break;
	case '5':
		m5 = new grape::lrb_tree_map<key, mapped>();
		t.restart();
		for (std::size_t i(0); i < COUNT; ++i)
			m5->insert(map_elem(i, i, i, i));
		delete m5;
		std::cout << "lrb_tree_map: " << t.elapsed() << std::endl;
		break;
	case '6':
		m6 = new grape::lrb_tree_map_3w<key, mapped>();
		t.restart();
		for (std::size_t i(0); i < COUNT; ++i)
			m6->insert(map_elem(i, i, i, i));
		delete m6;
		std::cout << "lrb_tree_map_3w: " << t.elapsed() << std::endl;
		break;
/*	case '7':
		m4 = new std::map<key, mapped>();
		t.restart();
		for (std::size_t i(0); i < COUNT; ++i)
		{
			std::pair<std::map<key, mapped>::iterator, bool> result(insert_with_default_mapped_value(*m4, key(i, i)));
			static_cast<map_elem&>(*result.first).set_mapped(i, i);
		}
		delete m4;
		std::cout << "std::map def: " << t.elapsed() << std::endl;
		break;
*/	case '8':
		m5 = new grape::lrb_tree_map<key, mapped>();
		t.restart();
		for (std::size_t i(0); i < COUNT; ++i)
		{
			std::pair<grape::lrb_tree_map<key, mapped>::iterator, bool> result(insert_with_default_mapped_value(*m5, key(i, i)));
			static_cast<map_elem&>(*result.first).set_mapped(i, i);
		}
		delete m5;
		std::cout << "lrb_tree_map def: " << t.elapsed() << std::endl;
		break;
	case '9':
		m6 = new grape::lrb_tree_map_3w<key, mapped>();
		t.restart();
		for (std::size_t i(0); i < COUNT; ++i)
		{
			std::pair<grape::lrb_tree_map_3w<key, mapped>::iterator, bool> result(insert_with_default_mapped_value(*m6, key(i, i)));
			static_cast<map_elem&>(*result.first).set_mapped(i, i);
		}
		delete m6;
		std::cout << "lrb_tree_map_3w def: " << t.elapsed() << std::endl;
		break;
	default: break;
	}

#ifdef TRACE
	std::cout << "defconstruct " << defconstruct << std::endl;
	std::cout << "construct " << construct << std::endl;
	std::cout << "copy " << copy << std::endl;
//	std::cout << "rcopy " << rcopy << std::endl;
	std::cout << "destruct " << destruct << std::endl;
#endif
	return 0;
}
