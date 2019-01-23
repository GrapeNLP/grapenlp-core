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

#include <grapenlp/algorithm.h>
#include <grapenlp/u_text_delaf_reader.h>
#include <grapenlp/u_text_delaf_writer.h>
#include <grapenlp/u_text_delaf_entry_filter_factory.h>

#define SRC_DICO "../Data/Unitex/Spanish/Dela/delaf.dic"
#define BAK_DICO "../Data/Unitex/Spanish/Dela/delaf.bak"

using namespace grapenlp;

typedef u_union_text_delaf_entry_filter<u_identity> uid_union_text_delaf_entry_filter;
typedef u_text_delaf<u_identity> uid_text_delaf;

void u_read_dico(uid_text_delaf &dico)
{
	FILE *f(u_fopen(SRC_DICO, U_READ));
	if (f == NULL)
		fatal_error("Unable to open source DELAF file to read\n");
	u_read(f, dico);
	u_fclose(f);
}

void u_read_semantic_traits_to_edit(uid_text_delaf &dico, uid_text_delaf::ust_set &semantic_traits_to_add, uid_text_delaf::ust_set &semantic_traits_to_substract)
{
	FILE *f(u_fopen("../semantic_traits_to_edit.txt", U_READ));
	if (f == NULL)
		fatal_error("Unable to open semantic_traits_to_edit.txt to read\n");
	size_t input_byte_count(u_fsize(f)); //file size minus 2 bytes of Byte-Order-Mark
	size_t input_unichar_count = input_byte_count / 2;
	unichar* s(new unichar[input_unichar_count]);
	u_fread(s, input_unichar_count, f);
	make_u_semantic_traits_to_edit<u_identity, unichar*>(s, s + input_unichar_count, dico, semantic_traits_to_add, semantic_traits_to_substract);
	u_fclose(f);
}

std::unique_ptr<uid_union_text_delaf_entry_filter> u_read_union_text_delaf_entry_filter(uid_text_delaf &dico)
{
	FILE *f(u_fopen("../delaf_entry_filter.txt", U_READ));
	if (f == NULL)
		fatal_error("Unable to open delaf_entry_filter.txt to read\n");
	size_t input_byte_count(u_fsize(f)); //file size minus 2 bytes of Byte-Order-Mark
	size_t input_unichar_count = input_byte_count / 2;
	unichar* s(new unichar[input_unichar_count]);
	u_fread(s, input_unichar_count, f);
	std::unique_ptr<uid_union_text_delaf_entry_filter> udef_ref(new uid_union_text_delaf_entry_filter());
	make_u_union_text_delaf_entry_filter<u_identity, unichar*>(s, s + input_unichar_count, dico, *udef_ref);
	u_fclose(f);
	return udef_ref;
}

void u_write_edited_dico(uid_text_delaf &dico, uid_union_text_delaf_entry_filter &udef, uid_text_delaf::ust_set &semantic_traits_to_add, uid_text_delaf::ust_set &semantic_traits_to_substract)
{
	FILE *f = u_fopen(SRC_DICO, U_WRITE);
	if (f == NULL)
		fatal_error("Unable to open source DELAF file for writing\n");

	uid_text_delaf::lemma_trie_with_entry_data::iterator i(dico.begin());
	uid_text_delaf::entry_list::const_iterator j;

	//While there are dico trie nodes left
	while (i != dico.end())
	{
		//If current dico trie node represents a complete word passing the filter, write it
		if (i->data)
			for (j = i->data->begin(); j != i->data->end(); ++j)
			{
				if (udef.match(**j))
				{
					(*j)->semantic_traits.insert(semantic_traits_to_add.begin(), semantic_traits_to_add.end());
					set_substraction((*j)->semantic_traits, semantic_traits_to_substract.begin(), semantic_traits_to_substract.end());
				}
				u_write<u_identity>(f, **j);
				u_fputc('\n', f);
			}
		//Go for the next dico trie node
		++i;
	}

	u_fclose(f);
}

int main(int argc, char **argv)
{
	uid_text_delaf dico;
	std::wcout << L"Reading DELAF dico" << std::endl;
	u_read_dico(dico);
	std::wcout << L"Renaming DELAF dico to .bak" << std::endl;
	remove(BAK_DICO);
	if (rename(SRC_DICO, BAK_DICO))
		fatal_error("Unable to rename source dico to backup dico\n");
	std::wcout << L"Reading DELAF word filter" << std::endl;
	std::unique_ptr<uid_union_text_delaf_entry_filter> udef_ref(u_read_union_text_delaf_entry_filter(dico));
	uid_text_delaf::ust_set semantic_traits_to_add, semantic_traits_to_substract;
	std::wcout << L"Reading semantic traits to edit" << std::endl;
	u_read_semantic_traits_to_edit(dico, semantic_traits_to_add, semantic_traits_to_substract);
	std::wcout << L"Writing edited DELAF" << std::endl;
	u_write_edited_dico(dico, *udef_ref, semantic_traits_to_add, semantic_traits_to_substract);
}
