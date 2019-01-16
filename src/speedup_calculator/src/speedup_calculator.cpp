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

#include <fstream>
#include <vector>

#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

#include <grapenlp/stats.h>

using namespace boost;
using namespace boost::program_options;

void help(const std::string &program_name, const options_description &desc)
{
	std::cout << "Usage: " << program_name.c_str() << " output" << std::endl;
	std::cout << desc;
	std::cout << std::endl;
	std::cout << "Example: " << "-adepth-first,breadth-first -po#t?e?b? -st -istats_no_keyword.txt" << std::endl;
	std::cout << "Algorithms: depth-first and breadth-first" << std::endl;
	std::cout << "Key parameter identifiers: 'o' (no output)" << std::endl;
	std::cout << "Optional parameters: 't' (use trie optimization), 'e' (implementation of sets of execution states) and 'b' (implementation of blackboard sets)" << std::endl;
	std::cout << "No mandatory or forbidden parameters" << std::endl;
	std::cout << "Speedup parameter: 't' (compute speedups depending on the use of trie strings or not)" << std::endl;
	std::cout << "Get as input file 'stats_no_keywords.txt'" << std::endl;
	std::cout << "Output to standard output" << std::endl;
}

typedef std::list<grapenlp::alg_trie::string::ref> alg_ptr_list;

inline void inc_until_ref_parser(grapenlp::stat_list::const_iterator &i, grapenlp::stat_list::const_iterator end, char speedup_param)
{
	while (i != end && i->pitvm.find(speedup_param) == i->pitvm.end())
		++i;
	if (i != end)
	{
		std::cout << "*******";
		grapenlp::serialize_parser_name_and_parameters(std::cout, *i) << "*******" << std::endl;
	}
}

template<typename CharT, typename Traits>
void doit(
		std::basic_istream<CharT, Traits> &in,
		std::basic_ostream<CharT, Traits> &out,
		const grapenlp::alg_trie &algorithms,
		const grapenlp::char_list &params,
		const grapenlp::char_list &key_list,
		const grapenlp::char_set &mandatory,
		const grapenlp::char_set &forbidden,
		const char speedup_param
		)
{
	grapenlp::stat_list sl;
	grapenlp::read_stat_list(in, algorithms, key_list, mandatory, forbidden, sl);
	sl.sort(grapenlp::desc_algorithm_names_and_parameters_comparator(params));

	grapenlp::stat_list::const_iterator i(sl.begin());
	inc_until_ref_parser(i, sl.end(), speedup_param);
	grapenlp::stat_list::const_iterator j(i);
	++j;
	grapenlp::param_id_to_value_map::const_iterator pit1, pit2;
	bool comparable;
	long double min_speedup(std::numeric_limits<long double>::max());
	long double max_speedup(std::numeric_limits<long double>::min());
	while (j != sl.end())
	{
		comparable = false;
		if (i->parser_name == j->parser_name)
		{
			pit1 = i->pitvm.begin();
			pit2 = j->pitvm.begin();
			while (true)
			{
				if (pit1 == i->pitvm.end())
				{
					if (pit2 != j->pitvm.end())
						break;
					comparable = true;
					break;
				}
				if (pit2 == j->pitvm.end())
				{
					if (pit1->first == speedup_param)
					{
						pit1++;
						if (pit1 == i->pitvm.end())
							comparable = true;
					}
					break;
				}
				if (pit1->first == speedup_param)
				{
					if (pit2->first != speedup_param)
					{
						pit1++;
						continue;
					}
				}
				else if (pit1->second != pit2->second)
					break;
				pit1++;
				pit2++;
			}
		}
		if (comparable)
		{
			long double m1(boost::lexical_cast<long double>(i->average_sentences_per_second));
			long double m2(boost::lexical_cast<long double>(j->average_sentences_per_second));
			long double speedup(100.0 * (1.0 - (m2/m1)));
			if (speedup > max_speedup)
				max_speedup = speedup;
			if (speedup < min_speedup)
				min_speedup = speedup;
			grapenlp::serialize_parser_name_and_parameters(std::cout, *j) << " " << speedup << '%' << std::endl;
		}
		else
		{
			i = j;
			inc_until_ref_parser(i, sl.end(), speedup_param);
			j = i;
		}
		++j;
	}
	std::cout << "speedup range [" << min_speedup << ", " << max_speedup << "]" << std::endl;
}

int main(int argc, char **argv)
{
	//Retrieve program name from program path-name
	std::string program_name(argv[0]);
#ifdef COMPILEFORWINDOWS
	std::size_t last_slash_pos(program_name.find_last_of('\\'));
#else
	std::size_t last_slash_pos(program_name.find_last_of('/'));
#endif
	if (last_slash_pos != std::string::npos)
		program_name = program_name.substr(last_slash_pos + 1, program_name.length());
	// Declare the possible command line arguments
	options_description desc("Options");
	desc.add_options()
		("help,?", "Display this information")
		("algorithms,a", value<std::string>(), "Comma-separated list of algorithm names to take into account")
		("params,p", value<std::string>(), "id1[?#]...idn[?#] a non-separated ordered list of optional/key/mandatory parameter identifiers, where a parameter is optional if it is followed by '?', is a key parameter (optional by default, add it to mandatory list if not) if it is followed by '#', and is just mandatory otherwise; each algorithm parameter is expected to be a string of length greater than 1, where the second letter is taken as the parameter identifier (e.g.: \"-t\", where \"t\" is unique); this list specifies the columns of the chart label table and their order; algorithms not defining mandatory parameters will be omitted")
		("mandatory,m", value<std::string>(), "Non-separated list of mandatory parameters that are either keys or simply not to be printed in the chart label table")
		("forbidden,f", value<std::string>(), "Non-separated list of forbidden parameter identifiers; algorithms defining a forbidden parameter will be omitted")
		("speedup-param,s", value<char>(), "-sx takes x as speedup parameter identifier, where x must be an optional parameter; speedups will be given for algorithms with parameter x wrt. the algorithms using the same parameters minus parameter x")
		("input,i", value<std::string>(), "Input file containing stats from nlp program (standard input if omitted)")
	    ("output,o", value<std::string>(), "Output latex file to generate (standard output if omitted)")
/*
	    ("height,h", value<std::string>(), "Row height in Latex format (e.g.: -h1ex)")
		("widths,w", value<std::string>(), "Comma-separated list of algorithm name and parameter column widths in Latex format (e.g.: -w5cm,2cm,\\col3width,...)")
		("max-value,v", value<long double>(), "Max represented value by bar lengths")
		("max-rows,r", value<std::size_t>(), "Max rows per table")
		("units,u", value<std::string>(), "Label specifying the value unit")
		("number-of-tics,n", value<std::size_t>(), "Number of tic marcs to draw along the value axe, without counting the one for the coordinate origin; omit or set to 0 if no tics are required")
		("position", value<std::string>(), "Code specifying figure placement (XXX in \\begin{figure}[XXX]")
		("title,t", value<std::string>(), "Title of graph (latex caption)")
		("label,l", value<std::string>(), "Graph identifier (latex label)")
*/
	;

	//Declare which one of the arguments are positional (do not need a code indicating which
	//argument they correspond to but this information may be given by their position in the argument list)
	positional_options_description pod;
	pod.add("output", 1);

	//Parse argument list
	variables_map vm;
	try
	{
		store(command_line_parser(argc, argv).options(desc).positional(pod).run(), vm);
	}
	catch(unknown_option e)
	{ fatal_error("%s\n", e.what()); }
	catch(too_many_positional_options_error e)
	{ fatal_error("%s\n",e.what()); }
	notify(vm);

	//Verify and extract arguments
	if (vm.count("help"))
	{ help(program_name, desc); return 0; }

	grapenlp::alg_trie algorithms;
	alg_ptr_list alg_ptrs;
	if (vm.count("algorithms"))
	{
		std::string algs(vm["algorithms"].as<std::string>());
		std::string::const_iterator i(algs.begin());
		while (true)
		{
			if (i == algs.end() || *i == ',')
				fatal_error("Empty algorithm name specified\n");
			grapenlp::alg_trie::string::ref s(&algorithms.epsilon());
			while (i != algs.end() && *i != ',')
			{
				s = &s->concat(*i);
				++i;
			}
			if (s->get('$'))
				fatal_error("Repeated algorithm name\n");
			s = &s->concat('$');
			alg_ptrs.push_back(s);
			if (i == algs.end())
				break;
			++i;
		}
	}
	else fatal_error("Algorithm names not specified\n");

	if (!vm.count("speedup-param"))
		fatal_error("The speedup parameter has not been specified\n");
	char speedup_param(vm["speedup-param"].as<char>());

	grapenlp::char_list params;
	grapenlp::char_set key;
	grapenlp::char_list key_list;
	grapenlp::char_set mandatory;
	bool speedup_param_found(false);

	if (!vm.count("params"))
		fatal_error("A parameter list containing at least the speedup parameter must be specified\n");
	std::string ps(vm["params"].as<std::string>());
	std::string::const_iterator i(ps.begin());
	while (i != ps.end())
	{
		char c(*i);
		if (c == speedup_param)
			speedup_param_found = true;
		else params.push_back(c);
		++i;
		if (i != ps.end() && (*i == '?' || *i == '#'))
		{
			if (*i == '#')
			{
				key.insert(c);
				key_list.push_back(c);
			}
			++i;
		}
		else mandatory.insert(c);
	}
	if (!speedup_param_found)
		fatal_error("The speedup parameter was not found within the parameter list\n");
	params.push_back(speedup_param);

	if (vm.count("mandatory"))
	{
		std::string ms(vm["mandatory"].as<std::string>());
		for (std::string::const_iterator i(ms.begin()); i != ms.end(); ++i)
			mandatory.insert(*i);
	}

	grapenlp::char_set forbidden;
	if (vm.count("forbidden"))
	{
		std::string fs(vm["forbidden"].as<std::string>());
		for (std::string::const_iterator i(fs.begin()); i != fs.end(); ++i)
			forbidden.insert(*i);
	}

	std::ifstream fin;
	bool input_is_stdin(true);
	if (vm.count("input"))
	{
		std::string in_path_name(vm["input"].as<std::string>());
		fin.open(in_path_name.c_str());
		if (!fin)
			fatal_error(std::string("Unable to open file \"%s\" for reading\n").c_str(), in_path_name.c_str());
		input_is_stdin = false;
	}
	std::ofstream fout;
	bool output_is_stdout(true);
	if (vm.count("output"))
	{
		std::string out_path_name(vm["output"].as<std::string>());
		fout.open(out_path_name.c_str());
		if (!fout)
			fatal_error(std::string("Unable to open file \"%s\" for writing\n").c_str(), out_path_name.c_str());
		output_is_stdout = false;
	}
	doit(input_is_stdin ? std::cin : fin, output_is_stdout ? std::cout : fout, algorithms, params, key_list, mandatory, forbidden, speedup_param);
	if (!input_is_stdin)
		fin.close();
	if (!output_is_stdout)
		fout.close();
	return 0;
}
