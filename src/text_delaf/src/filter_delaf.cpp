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

#include <grapenlp/u_text_delaf_reader.h>
#include <grapenlp/u_text_delaf_writer.h>
#include <grapenlp/u_text_delaf_entry_filter_factory.h>

using namespace grapenlp;

typedef u_union_text_delaf_entry_filter<u_identity> uid_union_text_delaf_entry_filter;
typedef u_text_delaf<u_identity> uid_text_delaf;

void u_read_dico(const char* dico_path, uid_text_delaf &dico)
{
	FILE *f(u_fopen(dico_path, U_READ));
	if (f == NULL)
		fatal_error("Unable to open delaf file to read\n");
	u_read(f, dico);
	u_fclose(f);
}

std::unique_ptr<uid_union_text_delaf_entry_filter> u_read_union_text_delaf_entry_filter(const char *mask_path, uid_text_delaf &dico)
{
	FILE *f(u_fopen(mask_path, U_READ));
	if (f == NULL)
		fatal_error("Unable to open delaf_entry_filter.txt to read\n");
	size_t input_byte_count(u_fsize(f)); //file size minus 2 bytes of Byte-Order-Mark
	size_t input_unichar_count = input_byte_count / 2;
	std::unique_ptr<unichar> s(new unichar[input_unichar_count]);
	u_fread(s.get(), input_unichar_count, f);
    const unichar *trim_begin = u_non_white_begin(s.get(), s.get() + input_unichar_count);
    const unichar *trim_end = u_non_white_end(s.get(), s.get() + input_unichar_count);
	std::unique_ptr<uid_union_text_delaf_entry_filter> udef_ref(new uid_union_text_delaf_entry_filter());
	make_u_union_text_delaf_entry_filter<u_identity, const unichar*>(trim_begin, trim_end, dico, *udef_ref);
	u_fclose(f);
	return udef_ref;
}

void u_write_filtered_dico(const char *out_path, uid_text_delaf &dico, uid_union_text_delaf_entry_filter &udef)
{
	FILE *f = u_fopen(out_path, U_WRITE);
	if (f == NULL)
		fatal_error("Unable to open file filtered_dico.txt for writing\n");

	uid_text_delaf::lemma_trie_with_entry_data::iterator i(dico.begin());
	uid_text_delaf::entry_list::const_iterator j;

	//While there are dico trie nodes left
	while (i != dico.end())
	{
		//If current dico trie node represents a complete word passing the filter, write it
		if (i->data)
			for (j = i->data->begin(); j != i->data->end(); ++j)
				if (udef.match(**j))
				{
					u_write<u_identity>(f, **j);
					u_fputc('\n', f);
				}
		//Go for the next dico trie node
		++i;
	}

	//u_write(f, dico);
	u_fclose(f);
}

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::wcout << L"Mandatory arguments:" << std::endl;
		std::wcout << L"1) Input DELAF .dic dictionary" << std::endl;
		std::wcout << L"2) Filter lexical mask" << std::endl;
        std::wcout << L"3) Filtered output DELAF .dic dictionary" << std::endl;
		exit(1);
	}
	uid_text_delaf dico;
	std::wcout << L"Reading DELAF dico" << std::endl;
	u_read_dico(argv[1], dico);
	std::wcout << L"Reading DELAF word filter" << std::endl;
	std::unique_ptr<uid_union_text_delaf_entry_filter> udef_ref(u_read_union_text_delaf_entry_filter(argv[2], dico));
	std::wcout << L"Writing filtered DELAF entries" << std::endl;
	u_write_filtered_dico(argv[3], dico, *udef_ref);
}
