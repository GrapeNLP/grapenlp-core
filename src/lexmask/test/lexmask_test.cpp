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

#include <grapenlp/u_text_delaf_reader.h>
#include <grapenlp/lexmask.h>
#include <grapenlp/u_array.h>
#include <grapenlp/u_text_delaf_entry_filter.h>

using namespace std;
using namespace grapenlp;

typedef u_array::const_iterator ua_input_iterator;

typedef token_meta_mask<ua_input_iterator> ua_token_meta_mask;
typedef digit_meta_mask<ua_input_iterator> ua_digit_meta_mask;
typedef no_digit_meta_mask<ua_input_iterator> ua_no_digit_meta_mask;
typedef word_meta_mask<ua_input_iterator> ua_word_meta_mask;
typedef no_word_meta_mask<ua_input_iterator> ua_no_word_meta_mask;
typedef upper_word_meta_mask<ua_input_iterator> ua_upper_word_meta_mask;
typedef no_upper_word_meta_mask<ua_input_iterator> ua_no_upper_word_meta_mask;
typedef lower_word_meta_mask<ua_input_iterator> ua_lower_word_meta_mask;
typedef no_lower_word_meta_mask<ua_input_iterator> ua_no_lower_word_meta_mask;
typedef first_upper_word_meta_mask<ua_input_iterator> ua_first_upper_word_meta_mask;
typedef no_first_upper_word_meta_mask<ua_input_iterator> ua_no_first_upper_word_meta_mask;
typedef symbol_mask<ua_input_iterator> ua_symbol_mask;
typedef case_sensitive_word_mask<ua_input_iterator> ua_case_sensitive_word_mask;
typedef case_insensitive_word_mask<ua_input_iterator, u_tolower> ualc_case_insensitive_word_mask;
typedef constrained_text_dico_word_meta_mask<ua_input_iterator, u_tolower> ualc_constrained_text_dico_word_meta_mask;

typedef text_delaf_entry_filter<unichar, u_tolower> ulc_text_delaf_entry_filter;
typedef u_true_text_delaf_entry_filter<u_tolower> ulc_true_text_delaf_entry_filter;
typedef u_false_text_delaf_entry_filter<u_tolower> ulc_false_text_delaf_entry_filter;
typedef u_canonical_form_text_delaf_entry_filter<u_tolower> ulc_canonical_form_text_delaf_entry_filter;
typedef u_negated_canonical_form_text_delaf_entry_filter<u_tolower> ulc_negated_canonical_form_text_delaf_entry_filter;
typedef u_semantic_traits_text_delaf_entry_filter<u_tolower> ulc_semantic_traits_text_delaf_entry_filter;
typedef u_negated_semantic_traits_text_delaf_entry_filter<u_tolower> ulc_negated_semantic_traits_text_delaf_entry_filter;
typedef u_canonical_form_and_semantic_traits_text_delaf_entry_filter<u_tolower> ulc_canonical_form_and_semantic_traits_text_delaf_entry_filter;
typedef u_negated_canonical_form_and_semantic_traits_text_delaf_entry_filter<u_tolower> ulc_negated_canonical_form_and_semantic_traits_text_delaf_entry_filter;
typedef u_semantic_and_possible_flexional_traits_text_delaf_entry_filter<u_tolower> ulc_semantic_and_possible_flexional_traits_text_delaf_entry_filter;
typedef u_negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter<u_tolower> ulc_negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter;
typedef u_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<u_tolower> ulc_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;
typedef u_negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<u_tolower> ulc_negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

const std::array<unichar, 2> le_array = { {'l', 'e'} };
const std::array<unichar, 4> leer_array = { {'l', 'e', 'e', 'r'} };
const std::array<unichar, 4> pron_array = { {'P', 'R', 'O', 'N'} };
const std::array<unichar, 2> od_array = { {'o', 'd'} };

void u_read_dico(tolower_u_text_delaf &dico)
{
	FILE *f(u_fopen("../Data/Unitex/Spanish/Dela/delaf_mini.dic", U_READ));
	if (f == NULL)
		fatal_error("Unable to open delaf file to read\n");
	u_read(f, dico);
	u_fclose(f);
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	std::array<unichar, 4> hola = { {'h', 'o', 'l', 'a'} };
	std::array<unichar, 5> adios = { {'a', 'd', 'i', 'o', 's'} };

	tolower_u_text_delaf dico;
	u_read_dico(dico);

	tolower_u_text_delaf::lemma_string::ref le_ref(dico.get(le_array.begin(), le_array.end()));
	if (!le_ref)
		fatal_error("\"le\" not included in the dictionary\n");

	tolower_u_text_delaf::lemma_string::ref leer_ref(dico.get(leer_array.begin(), leer_array.end()));
	if (!leer_ref)
		fatal_error("\"leer\" not included in the dictionary\n");

	u_set_trie::string::ref pron_pos_ref(dico.ppooss.get(pron_array.begin(), pron_array.end()));
	if (!pron_pos_ref)
		fatal_error("\"PRON\" pos not included in the dictionary\n");

	u_set_trie::string::ref od_semantic_trait_ref(dico.semantic_traits.get(od_array.begin(), od_array.end()));
	if (!od_semantic_trait_ref)
		fatal_error("\"od\" semantic trait not included in the dictionary\n");

	std::unique_ptr<tolower_u_text_delaf::ust_set> pron_poss_ref1(new tolower_u_text_delaf::ust_set);
	pron_poss_ref1->insert(pron_pos_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> pron_poss_ref2(new tolower_u_text_delaf::ust_set);
	pron_poss_ref2->insert(pron_pos_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> pron_poss_ref3(new tolower_u_text_delaf::ust_set);
	pron_poss_ref3->insert(pron_pos_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> pron_poss_ref4(new tolower_u_text_delaf::ust_set);
	pron_poss_ref4->insert(pron_pos_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> pron_poss_ref5(new tolower_u_text_delaf::ust_set);
	pron_poss_ref5->insert(pron_pos_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> pron_poss_ref6(new tolower_u_text_delaf::ust_set);
	pron_poss_ref6->insert(pron_pos_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> pron_poss_ref7(new tolower_u_text_delaf::ust_set);
	pron_poss_ref7->insert(pron_pos_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> pron_poss_ref8(new tolower_u_text_delaf::ust_set);
	pron_poss_ref8->insert(pron_pos_ref);

	std::unique_ptr<tolower_u_text_delaf::ust_set> od_semantic_traits_ref1(new tolower_u_text_delaf::ust_set);
	od_semantic_traits_ref1->insert(od_semantic_trait_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> od_semantic_traits_ref2(new tolower_u_text_delaf::ust_set);
	od_semantic_traits_ref2->insert(od_semantic_trait_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> od_semantic_traits_ref3(new tolower_u_text_delaf::ust_set);
	od_semantic_traits_ref3->insert(od_semantic_trait_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> od_semantic_traits_ref4(new tolower_u_text_delaf::ust_set);
	od_semantic_traits_ref4->insert(od_semantic_trait_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> od_semantic_traits_ref5(new tolower_u_text_delaf::ust_set);
	od_semantic_traits_ref5->insert(od_semantic_trait_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> od_semantic_traits_ref6(new tolower_u_text_delaf::ust_set);
	od_semantic_traits_ref6->insert(od_semantic_trait_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> od_semantic_traits_ref7(new tolower_u_text_delaf::ust_set);
	od_semantic_traits_ref7->insert(od_semantic_trait_ref);
	std::unique_ptr<tolower_u_text_delaf::ust_set> od_semantic_traits_ref8(new tolower_u_text_delaf::ust_set);
	od_semantic_traits_ref8->insert(od_semantic_trait_ref);

	u_set *ms_flexional_traits_ref1(new u_set);
	ms_flexional_traits_ref1->insert('m');
	ms_flexional_traits_ref1->insert('s');
	u_set *ms_flexional_traits_ref2(new u_set);
	ms_flexional_traits_ref2->insert('m');
	ms_flexional_traits_ref2->insert('s');
	u_set *ms_flexional_traits_ref3(new u_set);
	ms_flexional_traits_ref3->insert('m');
	ms_flexional_traits_ref3->insert('s');
	u_set *ms_flexional_traits_ref4(new u_set);
	ms_flexional_traits_ref4->insert('m');
	ms_flexional_traits_ref4->insert('s');

	u_set *fs_flexional_traits_ref1(new u_set);
	fs_flexional_traits_ref1->insert('f');
	fs_flexional_traits_ref1->insert('s');
	u_set *fs_flexional_traits_ref2(new u_set);
	fs_flexional_traits_ref2->insert('f');
	fs_flexional_traits_ref2->insert('s');
	u_set *fs_flexional_traits_ref3(new u_set);
	fs_flexional_traits_ref3->insert('f');
	fs_flexional_traits_ref3->insert('s');
	u_set *fs_flexional_traits_ref4(new u_set);
	fs_flexional_traits_ref4->insert('f');
	fs_flexional_traits_ref4->insert('s');

	std::unique_ptr<tolower_u_text_delaf::flexional_traits_list> ms_fs_possible_flexional_traits_ref1(new tolower_u_text_delaf::flexional_traits_list);
	ms_fs_possible_flexional_traits_ref1->push_back(ms_flexional_traits_ref1);
	ms_fs_possible_flexional_traits_ref1->push_back(fs_flexional_traits_ref1);
	std::unique_ptr<tolower_u_text_delaf::flexional_traits_list> ms_fs_possible_flexional_traits_ref2(new tolower_u_text_delaf::flexional_traits_list);
	ms_fs_possible_flexional_traits_ref2->push_back(ms_flexional_traits_ref2);
	ms_fs_possible_flexional_traits_ref2->push_back(fs_flexional_traits_ref2);
	std::unique_ptr<tolower_u_text_delaf::flexional_traits_list> ms_fs_possible_flexional_traits_ref3(new tolower_u_text_delaf::flexional_traits_list);
	ms_fs_possible_flexional_traits_ref3->push_back(ms_flexional_traits_ref3);
	ms_fs_possible_flexional_traits_ref3->push_back(fs_flexional_traits_ref3);
	std::unique_ptr<tolower_u_text_delaf::flexional_traits_list> ms_fs_possible_flexional_traits_ref4(new tolower_u_text_delaf::flexional_traits_list);
	ms_fs_possible_flexional_traits_ref4->push_back(ms_flexional_traits_ref4);
	ms_fs_possible_flexional_traits_ref4->push_back(fs_flexional_traits_ref4);

	ua_token_meta_mask tmm;
	u_printf("Token meta mask: ");
	tmm.wserialize(std::wcout) << endl;

	ua_digit_meta_mask dmm;
	u_printf("Digit meta mask: ");
	dmm.wserialize(std::wcout) << endl;

	ua_no_digit_meta_mask ndmm;
	u_printf("No digit meta mask: ");
	ndmm.wserialize(std::wcout) << endl;

	ua_word_meta_mask wmm;
	u_printf("Word meta mask: ");
	wmm.wserialize(std::wcout) << endl;

	ua_no_word_meta_mask nwmm;
	u_printf("Not a word meta mask: ");
	nwmm.wserialize(std::wcout) << endl;

	ua_upper_word_meta_mask uwmm;
	u_printf("Upper word meta mask: ");
	uwmm.wserialize(std::wcout) << endl;

	ua_no_upper_word_meta_mask nuwmm;
	u_printf("Not a upper word meta mask: ");
	nuwmm.wserialize(std::wcout) << endl;

	ua_lower_word_meta_mask lwmm;
	u_printf("Lower word meta mask: ");
	lwmm.wserialize(std::wcout) << endl;

	ua_no_lower_word_meta_mask nlwmm;
	u_printf("Not a lower word meta mask: ");
	nlwmm.wserialize(std::wcout) << endl;

	ua_first_upper_word_meta_mask fuwmm;
	u_printf("First upper word meta mask: ");
	fuwmm.wserialize(std::wcout) << endl;

	ua_no_first_upper_word_meta_mask nfuwmm;
	u_printf("Not a first upper word meta mask: ");
	nfuwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> tdef_ref(new ulc_true_text_delaf_entry_filter);
	ualc_constrained_text_dico_word_meta_mask dwmm(dico, std::move(tdef_ref));
	u_printf("Dico word meta mask: ");
	dwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> fdef_ref(new ulc_false_text_delaf_entry_filter);
	ualc_constrained_text_dico_word_meta_mask ndwmm(dico, std::move(fdef_ref));
	u_printf("No dico word meta mask: ");
	ndwmm.wserialize(std::wcout) << endl;

	ua_symbol_mask smm('$');
	u_printf("Symbol meta mask: ");
	smm.wserialize(std::wcout) << endl;

	ualc_case_insensitive_word_mask ciwm(hola);
	u_printf("Case insensitive word mask \"HoLa\": ");
	ciwm.wserialize(std::wcout) << endl;

	ua_case_sensitive_word_mask cswm(adios);
	u_printf("Case sensitive word mask \"aDioS\": ");
	cswm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> cfdef_ref(new ulc_canonical_form_text_delaf_entry_filter(*leer_ref));
	ualc_constrained_text_dico_word_meta_mask ccfdwmm(dico, std::move(cfdef_ref));
	u_printf("Constrained canonical form dico word meta mask \"leer\": ");
	ccfdwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> ncfdef_ref(new ulc_negated_canonical_form_text_delaf_entry_filter(*leer_ref));
	ualc_constrained_text_dico_word_meta_mask nccfdwmm(dico, std::move(ncfdef_ref));
	u_printf("Negated constrained canonical form dico word meta mask \"leer\": ");
	nccfdwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> stdef_ref(new ulc_semantic_traits_text_delaf_entry_filter(std::move(pron_poss_ref1), std::move(od_semantic_traits_ref1)));
	ualc_constrained_text_dico_word_meta_mask cstdwmm(dico, std::move(stdef_ref));
	u_printf("Constrained semantic traits dico word meta mask \"PRON-od\": ");
	cstdwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> nstdef_ref(new ulc_negated_semantic_traits_text_delaf_entry_filter(std::move(pron_poss_ref2), std::move(od_semantic_traits_ref2)));
	ualc_constrained_text_dico_word_meta_mask ncstdwmm(dico, std::move(nstdef_ref));
	u_printf("Negated constrained semantic traits dico word meta mask \"PRON-od\": ");
	ncstdwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> cfstdef_ref(new ulc_canonical_form_and_semantic_traits_text_delaf_entry_filter(*le_ref, std::move(pron_poss_ref3), std::move(od_semantic_traits_ref3)));
	ualc_constrained_text_dico_word_meta_mask ccfstdwmm(dico, std::move(cfstdef_ref));
	u_printf("Constrained canonical form and semantic traits dico word meta mask \"le.PRON-od\": ");
	ccfstdwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> ncfstdef_ref(new ulc_negated_canonical_form_and_semantic_traits_text_delaf_entry_filter(*le_ref, std::move(pron_poss_ref4), std::move(od_semantic_traits_ref4)));
	ualc_constrained_text_dico_word_meta_mask nccfstdwmm(dico, std::move(ncfstdef_ref));
	u_printf("Negated constrained canonical form and semantic traits dico word meta mask \"le.PRON-od\": ");
	nccfstdwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> sftdef_ref(new ulc_semantic_and_possible_flexional_traits_text_delaf_entry_filter(std::move(pron_poss_ref5), std::move(od_semantic_traits_ref5), std::move(ms_fs_possible_flexional_traits_ref1)));
	ualc_constrained_text_dico_word_meta_mask csftdwmm(dico, std::move(sftdef_ref));
	u_printf("Constrained semantic and possible flexional traits dico word meta mask \"PRON-od:ms:fs\": ");
	csftdwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> nsftdef_ref(new ulc_negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter(std::move(pron_poss_ref6), std::move(od_semantic_traits_ref6), std::move(ms_fs_possible_flexional_traits_ref2)));
	ualc_constrained_text_dico_word_meta_mask ncsftdwmm(dico, std::move(nsftdef_ref));
	u_printf("Negated constrained semantic traits and possible flexional traits dico word meta mask \"PRON-od:ms:fs\": ");
	ncsftdwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> cfsftdef_ref(new ulc_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(*le_ref, std::move(pron_poss_ref7), std::move(od_semantic_traits_ref7), std::move(ms_fs_possible_flexional_traits_ref3)));
	ualc_constrained_text_dico_word_meta_mask ccfsftdwmm(dico, std::move(cfsftdef_ref));
	u_printf("Constrained canonical form and semantic and possible flexional traits dico word meta mask \"le.PRON-od:ms:fs\": ");
	ccfsftdwmm.wserialize(std::wcout) << endl;

	std::unique_ptr<ulc_text_delaf_entry_filter> ncfsftdef_ref(new ulc_negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(*le_ref, std::move(pron_poss_ref8), std::move(od_semantic_traits_ref8), std::move(ms_fs_possible_flexional_traits_ref4)));
	ualc_constrained_text_dico_word_meta_mask nccfsftdwmm(dico, std::move(ncfsftdef_ref));
	u_printf("Negated constrained canonical form and semantic and possible flexional traits dico word meta mask \"le.PRON-od:ms:fs\": ");
	nccfsftdwmm.wserialize(std::wcout) << endl;

/*	lexmask<u_array::const_iterator, unichar> & l1 = m1;
	u_printf("Case insensitive word mask: ");
	wcout << l1 << endl;
	lexmask<u_array::const_iterator, unichar> & l2 = m2;
	u_printf("Case sensitive word mask: ");
	wcout << l2 << endl;
	lexmask<u_array::const_iterator, unichar> & l3 = m3;
	u_printf("Case word meta mask: ");
	wcout << l3 << endl;

	u_printf("cil ");
	m1 < m1;
	u_printf("csl ");
	m2 < m2;
	u_printf("wmm ");
	m3 < m3;
	u_printf("\r\n");

	u_printf("cil ");
	static_cast<case_insensitive_word_mask<u_array::const_iterator, unichar, u_tolower>&>(l1) < static_cast<case_insensitive_word_mask<u_array::const_iterator, unichar, u_tolower>&>(l1);
	u_printf("\r\n");

	u_printf("cil ");
	l1 < l1;
	u_printf("lex ");
	l1 < l2;
	u_printf("lex ");
	l1 < l3;
	u_printf("\r\n");

	u_printf("lex ");
	l2 < l1;
	u_printf("csl ");
	l2 < l2;
	u_printf("lex ");
	l2 < l3;
	u_printf("\r\n");

	u_printf("lex ");
	l3 < l1;
	u_printf("lex ");
	l3 < l2;
	u_printf("wmm ");
	l3 < l3;
*/
	return 1;
}
