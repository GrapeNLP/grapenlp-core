/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2019 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
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
#include <grapenlp/u_array.h>
#include <grapenlp/u_trie.h>
#include <grapenlp/u_set_trie.h>

using namespace std;
using namespace grapenlp;

int main(int argc, char **argv)
{
#ifndef MTRACE
	setlocale(LC_CTYPE,"");
#endif
	u_trie ut;

	std::array<unichar, 3> ufsa_aaa = { {L'a', L'a', L'a'} };
	std::array<unichar, 3> ufsa_aab = { {L'a', L'a', L'b'} };
	std::array<unichar, 3> ufsa_aac = { {L'a', L'a', L'c'} };
	std::array<unichar, 3> ufsa_aba = { {L'a', L'b', L'a'} };
	std::array<unichar, 3> ufsa_abb = { {L'a', L'b', L'b'} };
	std::array<unichar, 3> ufsa_abc = { {L'a', L'b', L'c'} };
	std::array<unichar, 3> ufsa_aca = { {L'a', L'c', L'a'} };
	std::array<unichar, 3> ufsa_acb = { {L'a', L'c', L'b'} };
	std::array<unichar, 3> ufsa_acc = { {L'a', L'c', L'c'} };

	std::array<unichar, 3> ufsa_baa = { {L'b', L'a', L'a'} };
	std::array<unichar, 3> ufsa_bab = { {L'b', L'a', L'b'} };
	std::array<unichar, 3> ufsa_bac = { {L'b', L'a', L'c'} };
	std::array<unichar, 3> ufsa_bba = { {L'b', L'b', L'a'} };
	std::array<unichar, 3> ufsa_bbb = { {L'b', L'b', L'b'} };
	std::array<unichar, 3> ufsa_bbc = { {L'b', L'b', L'c'} };
	std::array<unichar, 3> ufsa_bca = { {L'b', L'c', L'a'} };
	std::array<unichar, 3> ufsa_bcb = { {L'b', L'c', L'b'} };
	std::array<unichar, 3> ufsa_bcc = { {L'b', L'c', L'c'} };

	std::array<unichar, 3> ufsa_caa = { {L'c', L'a', L'a'} };
	std::array<unichar, 3> ufsa_cab = { {L'c', L'a', L'b'} };
	std::array<unichar, 3> ufsa_cac = { {L'c', L'a', L'c'} };
	std::array<unichar, 3> ufsa_cba = { {L'c', L'b', L'a'} };
	std::array<unichar, 3> ufsa_cbb = { {L'c', L'b', L'b'} };
	std::array<unichar, 3> ufsa_cbc = { {L'c', L'b', L'c'} };
	std::array<unichar, 3> ufsa_cca = { {L'c', L'c', L'a'} };
	std::array<unichar, 3> ufsa_ccb = { {L'c', L'c', L'b'} };
	std::array<unichar, 3> ufsa_ccc = { {L'c', L'c', L'c'} };

	u_trie_string &utstr_aaa = ut.epsilon().concat(ufsa_aaa.begin(), ufsa_aaa.end());
	u_trie_string &utstr_aab = ut.epsilon().concat(ufsa_aab.begin(), ufsa_aab.end());
	u_trie_string &utstr_aac = ut.epsilon().concat(ufsa_aac.begin(), ufsa_aac.end());
	u_trie_string &utstr_aba = ut.epsilon().concat(ufsa_aba.begin(), ufsa_aba.end());
	u_trie_string &utstr_abb = ut.epsilon().concat(ufsa_abb.begin(), ufsa_abb.end());
	u_trie_string &utstr_abc = ut.epsilon().concat(ufsa_abc.begin(), ufsa_abc.end());
	u_trie_string &utstr_aca = ut.epsilon().concat(ufsa_aca.begin(), ufsa_aca.end());
	u_trie_string &utstr_acb = ut.epsilon().concat(ufsa_acb.begin(), ufsa_acb.end());
	u_trie_string &utstr_acc = ut.epsilon().concat(ufsa_acc.begin(), ufsa_acc.end());

	u_trie_string &utstr_baa = ut.epsilon().concat(ufsa_baa.begin(), ufsa_baa.end());
	u_trie_string &utstr_bab = ut.epsilon().concat(ufsa_bab.begin(), ufsa_bab.end());
	u_trie_string &utstr_bac = ut.epsilon().concat(ufsa_bac.begin(), ufsa_bac.end());
	u_trie_string &utstr_bba = ut.epsilon().concat(ufsa_bba.begin(), ufsa_bba.end());
	u_trie_string &utstr_bbb = ut.epsilon().concat(ufsa_bbb.begin(), ufsa_bbb.end());
	u_trie_string &utstr_bbc = ut.epsilon().concat(ufsa_bbc.begin(), ufsa_bbc.end());
	u_trie_string &utstr_bca = ut.epsilon().concat(ufsa_bca.begin(), ufsa_bca.end());
	u_trie_string &utstr_bcb = ut.epsilon().concat(ufsa_bcb.begin(), ufsa_bcb.end());
	u_trie_string &utstr_bcc = ut.epsilon().concat(ufsa_bcc.begin(), ufsa_bcc.end());

	u_trie_string &utstr_caa = ut.epsilon().concat(ufsa_caa.begin(), ufsa_caa.end());
	u_trie_string &utstr_cab = ut.epsilon().concat(ufsa_cab.begin(), ufsa_cab.end());
	u_trie_string &utstr_cac = ut.epsilon().concat(ufsa_cac.begin(), ufsa_cac.end());
	u_trie_string &utstr_cba = ut.epsilon().concat(ufsa_cba.begin(), ufsa_cba.end());
	u_trie_string &utstr_cbb = ut.epsilon().concat(ufsa_cbb.begin(), ufsa_cbb.end());
	u_trie_string &utstr_cbc = ut.epsilon().concat(ufsa_cbc.begin(), ufsa_cbc.end());
	u_trie_string &utstr_cca = ut.epsilon().concat(ufsa_cca.begin(), ufsa_cca.end());
	u_trie_string &utstr_ccb = ut.epsilon().concat(ufsa_ccb.begin(), ufsa_ccb.end());
	u_trie_string &utstr_ccc = ut.epsilon().concat(ufsa_ccc.begin(), ufsa_ccc.end());

	utstr_aaa.serialize(wcout) << L" ";
	ut.get(ufsa_aaa.begin(), ufsa_aaa.end())->serialize(wcout) << endl;
	utstr_aab.serialize(wcout) << L" ";
	ut.get(ufsa_aab.begin(), ufsa_aab.end())->serialize(wcout) << endl;
	utstr_aac.serialize(wcout) << L" ";
	ut.get(ufsa_aac.begin(), ufsa_aac.end())->serialize(wcout) << endl;
	utstr_aba.serialize(wcout) << L" ";
	ut.get(ufsa_aba.begin(), ufsa_aba.end())->serialize(wcout) << endl;
	utstr_abb.serialize(wcout) << L" ";
	ut.get(ufsa_abb.begin(), ufsa_abb.end())->serialize(wcout) << endl;
	utstr_abc.serialize(wcout) << L" ";
	ut.get(ufsa_abc.begin(), ufsa_abc.end())->serialize(wcout) << endl;
	utstr_aca.serialize(wcout) << L" ";
	ut.get(ufsa_aca.begin(), ufsa_aca.end())->serialize(wcout) << endl;
	utstr_acb.serialize(wcout) << L" ";
	ut.get(ufsa_acb.begin(), ufsa_acb.end())->serialize(wcout) << endl;
	utstr_acc.serialize(wcout) << L" ";
	ut.get(ufsa_acc.begin(), ufsa_acc.end())->serialize(wcout) << endl;

	utstr_baa.serialize(wcout) << L" ";
	ut.get(ufsa_baa.begin(), ufsa_baa.end())->serialize(wcout) << endl;
	utstr_bab.serialize(wcout) << L" ";
	ut.get(ufsa_bab.begin(), ufsa_bab.end())->serialize(wcout) << endl;
	utstr_bac.serialize(wcout) << L" ";
	ut.get(ufsa_bac.begin(), ufsa_bac.end())->serialize(wcout) << endl;
	utstr_bba.serialize(wcout) << L" ";
	ut.get(ufsa_bba.begin(), ufsa_bba.end())->serialize(wcout) << endl;
	utstr_bbb.serialize(wcout) << L" ";
	ut.get(ufsa_bbb.begin(), ufsa_bbb.end())->serialize(wcout) << endl;
	utstr_bbc.serialize(wcout) << L" ";
	ut.get(ufsa_bbc.begin(), ufsa_bbc.end())->serialize(wcout) << endl;
	utstr_bca.serialize(wcout) << L" ";
	ut.get(ufsa_bca.begin(), ufsa_bca.end())->serialize(wcout) << endl;
	utstr_bcb.serialize(wcout) << L" ";
	ut.get(ufsa_bcb.begin(), ufsa_bcb.end())->serialize(wcout) << endl;
	utstr_bcc.serialize(wcout) << L" ";
	ut.get(ufsa_bcc.begin(), ufsa_bcc.end())->serialize(wcout) << endl;

	utstr_caa.serialize(wcout) << L" ";
	ut.get(ufsa_caa.begin(), ufsa_caa.end())->serialize(wcout) << endl;
	utstr_cab.serialize(wcout) << L" ";
	ut.get(ufsa_cab.begin(), ufsa_cab.end())->serialize(wcout) << endl;
	utstr_cac.serialize(wcout) << L" ";
	ut.get(ufsa_cac.begin(), ufsa_cac.end())->serialize(wcout) << endl;
	utstr_cba.serialize(wcout) << L" ";
	ut.get(ufsa_cba.begin(), ufsa_cba.end())->serialize(wcout) << endl;
	utstr_cbb.serialize(wcout) << L" ";
	ut.get(ufsa_cbb.begin(), ufsa_cbb.end())->serialize(wcout) << endl;
	utstr_cbc.serialize(wcout) << L" ";
	ut.get(ufsa_cbc.begin(), ufsa_cbc.end())->serialize(wcout) << endl;
	utstr_cca.serialize(wcout) << L" ";
	ut.get(ufsa_cca.begin(), ufsa_cca.end())->serialize(wcout) << endl;
	utstr_ccb.serialize(wcout) << L" ";
	ut.get(ufsa_ccb.begin(), ufsa_ccb.end())->serialize(wcout) << endl;
	utstr_ccc.serialize(wcout) << L" ";
	ut.get(ufsa_ccc.begin(), ufsa_ccc.end())->serialize(wcout) << endl;

	u_trie::iterator it(ut.begin());
	//Skip epsilon string
	++it;
	while (it != ut.end())
	{
		u_printf("%c", it->back());
		++it;
	}
	wcout << endl;

	u_array ua_aaa(utstr_aaa.size());
	utstr_aaa.to_array(ua_aaa);
	wcout << ua_aaa << endl;

	u_array ua_bbb(utstr_bbb.size());
	utstr_bbb.to_array(ua_bbb);
	wcout << ua_bbb << endl;

	u_set_trie ust;

	ust_string::ref s(&ust.epsilon());
	size_t i(0);
	wcout << i << L' ' << s->data << endl;
	for (; i < 10; ++i)
	{
		s = &(*s + L'a');
		wcout << i << L' ' << s->data << endl;
	}
	for (i = 0; i < 10; ++i)
	{
		s = &(*s + L'a');
		s->data = true;
		wcout << i << L' ' << s->data << endl;
	}
	for (i = 0; i < 10; ++i)
	{
		s = &(*s + L'a');
		s->data = false;
		wcout << i << L' ' << s->data << endl;
	}

	int *ptr_a(new int(1));
	int *ptr_b(new int(2));

	trie_with_ptr_data<unichar, int> ptr_t;
	ptr_t.epsilon().concat(ufsa_aaa.begin(), ufsa_aaa.end(), ptr_a);
	ptr_t.epsilon().concat(ufsa_bbb.begin(), ufsa_bbb.end(), ptr_b);

	u_set_trie set_t;
	set_t.add(ufsa_aaa.begin(), ufsa_aaa.end());
	wcout << set_t.includes(ufsa_aaa.begin(), ufsa_aaa.end()) << endl;
	wcout << set_t.includes(ufsa_bbb.begin(), ufsa_bbb.end()) << endl;
	return 0;
}
