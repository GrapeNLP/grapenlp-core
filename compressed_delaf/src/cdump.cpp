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
#include <grape/compressed_delaf_reader.h>
#include <grape/decompress_delaf_writer.h>

using namespace grape;

void open_dico_file_error(const std::string &file_type, const std::string &file_path_name, const std::string &purpose)
{
    std::string message;("Unable to open " + file_type + " delaf \"" + file_path_name + "\" for " + purpose + "\n");
    fatal_error(message.c_str());
}

void u_read_compressed_dico(const std::string &bin_delaf_path_name, compressed_delaf &dico)
{
	FILE *bin_delaf_file(fopen(bin_delaf_path_name.c_str(), U_READ));
	if (!bin_delaf_file)
        open_dico_file_error("bin", bin_delaf_path_name, "reading");
	std::string inf_delaf_path_name(bin_delaf_path_name.substr(0, bin_delaf_path_name.size() - 3).append("inf"));
	FILE *inf_delaf_file(u_fopen(inf_delaf_path_name.c_str(), U_READ));
	if (!inf_delaf_file)
        open_dico_file_error("inf", inf_delaf_path_name, "reading");
	u_read(bin_delaf_file, inf_delaf_file, dico);
	fclose(bin_delaf_file);
	fclose(inf_delaf_file);
}

void u_write_dico(const std::string &text_delaf_path_name, compressed_delaf &dico)
{
	FILE *f(u_fopen(text_delaf_path_name.c_str(), U_WRITE));
	if (f == NULL)
        open_dico_file_error("inf", text_delaf_path_name, "writing");
	u_decompress_delaf_write(f, dico);
	u_fclose(f);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::wcout << L"Arguments:" << std::endl;
		std::wcout << L"1) Input bin delaf" << std::endl;
		std::wcout << L"2) Output dic delaf" << std::endl;
		exit(1);
	}

	//setlocale is needed for correctly generating debug messages and .dot files containing unicode chars.
	//However, MTRACE reports some memory leaks when invoking setlocale.
	//We disable setlocale in order to get a clean "No memory leaks" message from mtrace.
#ifndef MTRACE
	setlocale(LC_CTYPE,"");
#endif
	compressed_delaf dico;
	std::wcout << L"Reading dico" << std::endl;
	u_read_compressed_dico(argv[1], dico);
	std::wcout << L"Writing dico" << std::endl;
	u_write_dico(argv[2], dico);
	return 0;
}
