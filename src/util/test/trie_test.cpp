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

#include <gtest/gtest.h>
#include <list>
#include <grapenlp/array.h>
#include <grapenlp/trie.h>
#include <grapenlp/set_trie.h>

using namespace std;
using namespace grapenlp;

typedef trie<char> c_trie;
typedef c_trie::string ct_string;
typedef set_trie<char> c_set_trie;
typedef c_set_trie::string cst_string;
typedef grapenlp::array<char> c_array;
/*
int mainx(int argc, char **argv)
{
	setlocale(LC_CTYPE,"");
	c_trie ct;

	std::array<char, 3> cfsa_aaa = { {'a', 'a', 'a'} };
	std::array<char, 3> cfsa_aab = { {'a', 'a', 'b'} };
	std::array<char, 3> cfsa_aac = { {'a', 'a', 'c'} };
	std::array<char, 3> cfsa_aba = { {'a', 'b', 'a'} };
	std::array<char, 3> cfsa_abb = { {'a', 'b', 'b'} };
	std::array<char, 3> cfsa_abc = { {'a', 'b', 'c'} };
	std::array<char, 3> cfsa_aca = { {'a', 'c', 'a'} };
	std::array<char, 3> cfsa_acb = { {'a', 'c', 'b'} };
	std::array<char, 3> cfsa_acc = { {'a', 'c', 'c'} };

	std::array<char, 3> cfsa_baa = { {'b', 'a', 'a'} };
	std::array<char, 3> cfsa_bab = { {'b', 'a', 'b'} };
	std::array<char, 3> cfsa_bac = { {'b', 'a', 'c'} };
	std::array<char, 3> cfsa_bba = { {'b', 'b', 'a'} };
	std::array<char, 3> cfsa_bbb = { {'b', 'b', 'b'} };
	std::array<char, 3> cfsa_bbc = { {'b', 'b', 'c'} };
	std::array<char, 3> cfsa_bca = { {'b', 'c', 'a'} };
	std::array<char, 3> cfsa_bcb = { {'b', 'c', 'b'} };
	std::array<char, 3> cfsa_bcc = { {'b', 'c', 'c'} };

	std::array<char, 3> cfsa_caa = { {'c', 'a', 'a'} };
	std::array<char, 3> cfsa_cab = { {'c', 'a', 'b'} };
	std::array<char, 3> cfsa_cac = { {'c', 'a', 'c'} };
	std::array<char, 3> cfsa_cba = { {'c', 'b', 'a'} };
	std::array<char, 3> cfsa_cbb = { {'c', 'b', 'b'} };
	std::array<char, 3> cfsa_cbc = { {'c', 'b', 'c'} };
	std::array<char, 3> cfsa_cca = { {'c', 'c', 'a'} };
	std::array<char, 3> cfsa_ccb = { {'c', 'c', 'b'} };
	std::array<char, 3> cfsa_ccc = { {'c', 'c', 'c'} };

	ct_string &ctstr_aaa = ct.epsilon().concat(cfsa_aaa.begin(), cfsa_aaa.end());
	ct_string &ctstr_aab = ct.epsilon().concat(cfsa_aab.begin(), cfsa_aab.end());
	ct_string &ctstr_aac = ct.epsilon().concat(cfsa_aac.begin(), cfsa_aac.end());
	ct_string &ctstr_aba = ct.epsilon().concat(cfsa_aba.begin(), cfsa_aba.end());
	ct_string &ctstr_abb = ct.epsilon().concat(cfsa_abb.begin(), cfsa_abb.end());
	ct_string &ctstr_abc = ct.epsilon().concat(cfsa_abc.begin(), cfsa_abc.end());
	ct_string &ctstr_aca = ct.epsilon().concat(cfsa_aca.begin(), cfsa_aca.end());
	ct_string &ctstr_acb = ct.epsilon().concat(cfsa_acb.begin(), cfsa_acb.end());
	ct_string &ctstr_acc = ct.epsilon().concat(cfsa_acc.begin(), cfsa_acc.end());

	ct_string &ctstr_baa = ct.epsilon().concat(cfsa_baa.begin(), cfsa_baa.end());
	ct_string &ctstr_bab = ct.epsilon().concat(cfsa_bab.begin(), cfsa_bab.end());
	ct_string &ctstr_bac = ct.epsilon().concat(cfsa_bac.begin(), cfsa_bac.end());
	ct_string &ctstr_bba = ct.epsilon().concat(cfsa_bba.begin(), cfsa_bba.end());
	ct_string &ctstr_bbb = ct.epsilon().concat(cfsa_bbb.begin(), cfsa_bbb.end());
	ct_string &ctstr_bbc = ct.epsilon().concat(cfsa_bbc.begin(), cfsa_bbc.end());
	ct_string &ctstr_bca = ct.epsilon().concat(cfsa_bca.begin(), cfsa_bca.end());
	ct_string &ctstr_bcb = ct.epsilon().concat(cfsa_bcb.begin(), cfsa_bcb.end());
	ct_string &ctstr_bcc = ct.epsilon().concat(cfsa_bcc.begin(), cfsa_bcc.end());

	ct_string &ctstr_caa = ct.epsilon().concat(cfsa_caa.begin(), cfsa_caa.end());
	ct_string &ctstr_cab = ct.epsilon().concat(cfsa_cab.begin(), cfsa_cab.end());
	ct_string &ctstr_cac = ct.epsilon().concat(cfsa_cac.begin(), cfsa_cac.end());
	ct_string &ctstr_cba = ct.epsilon().concat(cfsa_cba.begin(), cfsa_cba.end());
	ct_string &ctstr_cbb = ct.epsilon().concat(cfsa_cbb.begin(), cfsa_cbb.end());
	ct_string &ctstr_cbc = ct.epsilon().concat(cfsa_cbc.begin(), cfsa_cbc.end());
	ct_string &ctstr_cca = ct.epsilon().concat(cfsa_cca.begin(), cfsa_cca.end());
	ct_string &ctstr_ccb = ct.epsilon().concat(cfsa_ccb.begin(), cfsa_ccb.end());
	ct_string &ctstr_ccc = ct.epsilon().concat(cfsa_ccc.begin(), cfsa_ccc.end());

	for (ct_string::const_iterator itt(ctstr_abc.begin()); itt != ctstr_abc.end(); ++itt)
	{
		cout << *itt;
		cout << endl;
	}
	cout << endl;
	for (ct_string::const_iterator itt2(ctstr_abc.begin()); itt2 != ctstr_abc.end(); ++itt2)
	{
		cout << *itt2;
		cout << endl;
	}

	ctstr_aaa.serialize(cout) << " ";
	ct.get(cfsa_aaa.begin(), cfsa_aaa.end())->serialize(cout) << endl;
	ctstr_aab.serialize(cout) << " ";
	ct.get(cfsa_aab.begin(), cfsa_aab.end())->serialize(cout) << endl;
	ctstr_aac.serialize(cout) << " ";
	ct.get(cfsa_aac.begin(), cfsa_aac.end())->serialize(cout) << endl;
	ctstr_aba.serialize(cout) << " ";
	ct.get(cfsa_aba.begin(), cfsa_aba.end())->serialize(cout) << endl;
	ctstr_abb.serialize(cout) << " ";
	ct.get(cfsa_abb.begin(), cfsa_abb.end())->serialize(cout) << endl;
	ctstr_abc.serialize(cout) << " ";
	ct.get(cfsa_abc.begin(), cfsa_abc.end())->serialize(cout) << endl;
	ctstr_aca.serialize(cout) << " ";
	ct.get(cfsa_aca.begin(), cfsa_aca.end())->serialize(cout) << endl;
	ctstr_acb.serialize(cout) << " ";
	ct.get(cfsa_acb.begin(), cfsa_acb.end())->serialize(cout) << endl;
	ctstr_acc.serialize(cout) << " ";
	ct.get(cfsa_acc.begin(), cfsa_acc.end())->serialize(cout) << endl;

	ctstr_baa.serialize(cout) << " ";
	ct.get(cfsa_baa.begin(), cfsa_baa.end())->serialize(cout) << endl;
	ctstr_bab.serialize(cout) << " ";
	ct.get(cfsa_bab.begin(), cfsa_bab.end())->serialize(cout) << endl;
	ctstr_bac.serialize(cout) << " ";
	ct.get(cfsa_bac.begin(), cfsa_bac.end())->serialize(cout) << endl;
	ctstr_bba.serialize(cout) << " ";
	ct.get(cfsa_bba.begin(), cfsa_bba.end())->serialize(cout) << endl;
	ctstr_bbb.serialize(cout) << " ";
	ct.get(cfsa_bbb.begin(), cfsa_bbb.end())->serialize(cout) << endl;
	ctstr_bbc.serialize(cout) << " ";
	ct.get(cfsa_bbc.begin(), cfsa_bbc.end())->serialize(cout) << endl;
	ctstr_bca.serialize(cout) << " ";
	ct.get(cfsa_bca.begin(), cfsa_bca.end())->serialize(cout) << endl;
	ctstr_bcb.serialize(cout) << " ";
	ct.get(cfsa_bcb.begin(), cfsa_bcb.end())->serialize(cout) << endl;
	ctstr_bcc.serialize(cout) << " ";
	ct.get(cfsa_bcc.begin(), cfsa_bcc.end())->serialize(cout) << endl;

	ctstr_caa.serialize(cout) << " ";
	ct.get(cfsa_caa.begin(), cfsa_caa.end())->serialize(cout) << endl;
	ctstr_cab.serialize(cout) << " ";
	ct.get(cfsa_cab.begin(), cfsa_cab.end())->serialize(cout) << endl;
	ctstr_cac.serialize(cout) << " ";
	ct.get(cfsa_cac.begin(), cfsa_cac.end())->serialize(cout) << endl;
	ctstr_cba.serialize(cout) << " ";
	ct.get(cfsa_cba.begin(), cfsa_cba.end())->serialize(cout) << endl;
	ctstr_cbb.serialize(cout) << " ";
	ct.get(cfsa_cbb.begin(), cfsa_cbb.end())->serialize(cout) << endl;
	ctstr_cbc.serialize(cout) << " ";
	ct.get(cfsa_cbc.begin(), cfsa_cbc.end())->serialize(cout) << endl;
	ctstr_cca.serialize(cout) << " ";
	ct.get(cfsa_cca.begin(), cfsa_cca.end())->serialize(cout) << endl;
	ctstr_ccb.serialize(cout) << " ";
	ct.get(cfsa_ccb.begin(), cfsa_ccb.end())->serialize(cout) << endl;
	ctstr_ccc.serialize(cout) << " ";
	ct.get(cfsa_ccc.begin(), cfsa_ccc.end())->serialize(cout) << endl;

	c_trie::iterator it(ct.begin());
	//Skip epsilon string
	++it;
	while (it != ct.end())
	{
		cout << it->back();
		++it;
	}
	cout << endl;

	c_array ca_aaa(ctstr_aaa.size());
	ctstr_aaa.to_array(ca_aaa);
	cout << ca_aaa << endl;

	c_array ca_bbb(ctstr_bbb.size());
	ctstr_bbb.to_array(ca_bbb);
	cout << ca_bbb << endl;

	c_set_trie cst;

	cst_string::ref s(&cst.epsilon());
	size_t i(0);
	cout << i << ' ' << s->data << endl;
	for (; i < 10; ++i)
	{
		s = &(*s + 'a');
		cout << i << ' ' << s->data << endl;
	}
	for (i = 0; i < 10; ++i)
	{
		s = &(*s + 'a');
		s->data = true;
		cout << i << ' ' << s->data << endl;
	}
	for (i = 0; i < 10; ++i)
	{
		s = &(*s + 'a');
		s->data = false;
		cout << i << ' ' << s->data << endl;
	}

	int *ptr_a(new int(1));
	int *ptr_b(new int(2));

	trie_with_ptr_data<char, int> ptr_t;
	ptr_t.epsilon().concat(cfsa_aaa.begin(), cfsa_aaa.end(), ptr_a);
	ptr_t.epsilon().concat(cfsa_bbb.begin(), cfsa_bbb.end(), ptr_b);

	c_set_trie cst2;
	cst2.add(cfsa_aaa.begin(), cfsa_aaa.end());
	cout << cst.includes(cfsa_aaa.begin(), cfsa_aaa.end()) << endl;
	cout << cst.includes(cfsa_bbb.begin(), cfsa_bbb.end()) << endl;
	return 0;
}
*/

static const string abc_strings[] {
        "aaa",
        "aab",
        "aac",
        "aba",
        "abb",
        "abc",
        "aca",
        "acb",
        "acc",
        "baa",
        "bab",
        "bac",
        "bba",
        "bbb",
        "bbc",
        "bca",
        "bcb",
        "bcc",
        "caa",
        "cab",
        "cac",
        "cba",
        "cbb",
        "cbc",
        "cca",
        "ccb",
        "ccc"
};

static const string abc_string_prefixes[] {
        "",
        "a",
        "aa",
        "aaa",
        "aab",
        "aac",
        "ab",
        "aba",
        "abb",
        "abc",
        "ac",
        "aca",
        "acb",
        "acc",
        "b",
        "ba",
        "baa",
        "bab",
        "bac",
        "bb",
        "bba",
        "bbb",
        "bbc",
        "bc",
        "bca",
        "bcb",
        "bcc",
        "c",
        "ca",
        "caa",
        "cab",
        "cac",
        "cb",
        "cba",
        "cbb",
        "cbc",
        "cc",
        "cca",
        "ccb",
        "ccc"
};

// A new one of these is create for each test
class trie_test : public ::testing::TestWithParam<pair<const string[], const string[]>>
{};

INSTANTIATE_TEST_CASE_P(jandermander,
                        trie_test,
                        ::testing::Values(make_pair<const std::array<const string, 0>, const std::array<const string, 0>>({}, {}),
                                          make_pair<const std::array<const string, 1>, const std::array<const string, 1>>({""}, {""}),
                                          make_pair<const std::array<const string, 1>, const std::array<const string, 2>>({"a"}, {"", "a"})));

TEST_P(trie_test, after_adding_a_set_of_strings_to_a_trie_the_trie_contains_all_the_added_strings_and_all_their_prefixes_but_no_other_strings)
{
    auto& strings_to_insert = GetParam().first;

    trie<char> t;
    for (const string s: strings_to_insert);
        t.epsilon().concat(s);
    auto expected_it = begin(test_params.second);
    auto actual_it(t.begin());
    while (expected_it != test_params.second->end() && actual_it != t.end())
    {
        string t_string{actual_it->begin(), actual_it->end()};
        cout << *expected_it << "/";
        actual_it->serialize(cout) << endl;
        ASSERT_EQ(*expected_it, t_string);
        ++expected_it;
        ++actual_it;
    }
    ASSERT_TRUE(expected_it == test_params.second->end()) << "Trie contains less strings than expected";
    ASSERT_TRUE(actual_it == t.end()) << "Trie contains more strings than expected";
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
