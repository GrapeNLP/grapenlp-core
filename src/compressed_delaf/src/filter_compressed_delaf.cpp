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

#include <grapenlp/compressed_delaf_reader.h>
#include <grapenlp/decompress_delaf_writer.h>
#include <grapenlp/compressed_delaf_entry_filter_factory.h>

using namespace grapenlp;

typedef union_compressed_delaf_entry_filter<compressed_delaf::word::u_const_iterator> a_union_compressed_delaf_entry_filter;

void u_read_compressed_dico(const char *dico_bin_path, compressed_delaf &dico)
{
	FILE *bin_delaf_file(fopen(dico_bin_path, U_READ));
	if (!bin_delaf_file)
		fatal_error("Unable to open bin delaf file\n");
	const char *aux(dico_bin_path);
    std::size_t s = sizeof(dico_bin_path);
	std::unique_ptr<char> dico_inf_path(new char[s]);
	std::copy(dico_bin_path, dico_bin_path + s, dico_inf_path.get());
    s -= 5;
    dico_inf_path.get()[s] = '.';
    ++s;
	dico_inf_path.get()[s] = 'i';
	++s;
	dico_inf_path.get()[s] = 'n';
	++s;
	dico_inf_path.get()[s] = 'f';
    ++s;
    dico_inf_path.get()[s] = '\0';
	FILE *inf_delaf_file(u_fopen(dico_inf_path.get(), U_READ));
	if (!inf_delaf_file)
		fatal_error("Unable to open inf delaf file\n");
	u_read(bin_delaf_file, inf_delaf_file, dico);
	fclose(bin_delaf_file);
	fclose(inf_delaf_file);
}

std::unique_ptr<a_union_compressed_delaf_entry_filter> u_read_union_compressed_delaf_entry_filter(const char *mask_path, compressed_delaf &dico)
{
	FILE *f(u_fopen(mask_path, U_READ));
	if (f == NULL)
		fatal_error("Unable to open delaf_entry_filter.txt to read\n");
	size_t input_byte_count(u_fsize(f)); //file size minus 2 bytes of Byte-Order-Mark
	size_t input_unichar_count = input_byte_count / 2;
	unichar* s(new unichar[input_unichar_count]);
	u_fread(s, input_unichar_count, f);
	std::unique_ptr<a_union_compressed_delaf_entry_filter> udef_ref(new a_union_compressed_delaf_entry_filter());
	make_union_compressed_delaf_entry_filter<u_tolower, u_array::const_iterator, compressed_delaf::word::u_const_iterator>(s, s + input_unichar_count, dico, *udef_ref);
	u_fclose(f);
	return udef_ref;
}

void u_write_filtered_compressed_dico_word(FILE *f, const compressed_delaf::word &w, a_union_compressed_delaf_entry_filter &ucdef)
{
	inf_delaf::ambiguous_entry::const_iterator j(w.properties.begin());
	for (; j != w.properties.end(); ++j)
		if (ucdef.match(w.begin, w.end, **j))
		{
			u_decompress_delaf_write(f, w.begin, w.end, **j);
			u_fputc('\n', f);
		}
}

void u_write_filtered_dico(const char* filtered_dico, compressed_delaf &dico, a_union_compressed_delaf_entry_filter &ucdef)
{
	FILE *f = u_fopen(filtered_dico, U_WRITE);
	if (f == NULL)
		fatal_error("Unable to open file filtered_dico.txt for writing\n");

	compressed_delaf::const_word_iterator i(dico.const_word_begin());
	inf_delaf::ambiguous_entry::const_iterator j;

	//For each word, and for each one of its interpretations, write it if it matches the filter
	for (; i != dico.const_word_end(); ++i)
		u_write_filtered_compressed_dico_word(f, *i, ucdef);

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

	compressed_delaf dico;
	std::wcout << L"Reading compressed DELAF dico" << std::endl;
	u_read_compressed_dico(argv[1], dico);

	std::wcout << L"Reading DELAF word filter" << std::endl;
	std::unique_ptr<a_union_compressed_delaf_entry_filter> ucdef_ref(u_read_union_compressed_delaf_entry_filter(argv[2], dico));
	std::wcout << L"Writing filtered DELAF entries" << std::endl;
	u_write_filtered_dico(argv[3], dico, *ucdef_ref);
}
