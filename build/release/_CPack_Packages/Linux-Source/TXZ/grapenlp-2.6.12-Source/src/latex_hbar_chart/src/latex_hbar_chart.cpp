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
	std::cout << "Example: " << "-adepth-first,breadth-first -po#t?e?b? -c-o,depth-first-no-output-color.,depth-first-color:-o,breadth-first-no-output-color.,breadth-first-color -l5 -v10000 -r12 -istats_no_keyword.txt" << std::endl;
	std::cout << "Algorithms: depth-first and breadth-first" << std::endl;
	std::cout << "Key parameter identifiers: 'o' (no output)" << std::endl;
	std::cout << "Optional parameters: 't' (use trie optimization), 'e' (implementation of sets of execution states) and 'b' (implementation of blackboard sets)" << std::endl;
	std::cout << "No mandatory or forbidden parameters" << std::endl;
	std::cout << "Colors: depth-first without output gets 'depth-first-no-output-color' color, depth-first with output gets 'depth-first-color' color, etc" << std::endl;
	std::cout << "Max bar lengths once printed: 5cm" << std::endl;
	std::cout << "Max represented value: 10000" << std::endl;
	std::cout << "Split table each 12 algorithms" << std::endl;
	std::cout << "Get as input file 'stats_no_keywords.txt'" << std::endl;
	std::cout << "Output to standard output" << std::endl;
}

struct first_x_color
{
	bool first;
	std::string color;

	first_x_color(bool first_, const std::string &color_): first(first_), color(color_)
	{}
};

typedef std::list<grapenlp::alg_trie::string::ref> alg_ptr_list;

first_x_color& get_first_x_color(const grapenlp::alg_trie &algorithms, const grapenlp::char_list &key_list, const grapenlp::stats &s)
{
	grapenlp::alg_trie::string::const_ref s2(algorithms.get(s.parser_name.begin(), s.parser_name.end())->get('$'));

	for (grapenlp::char_list::const_iterator i(key_list.begin()); i != key_list.end(); ++i)
	{
		grapenlp::param_id_to_value_map::const_iterator j(s.pitvm.find(*i));
		if (j != s.pitvm.end())
			s2 = s2->get(j->second.begin(), j->second.end());
		s2 = s2->get('$');
	}
	return *reinterpret_cast<first_x_color*>(s2->data);
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& write_chart(
		std::basic_ostream<CharT, Traits> &out,
		const grapenlp::alg_trie &algorithms,
		const grapenlp::char_list &params,
		const grapenlp::char_list &key_list,
		const grapenlp::stat_list &sl,
		const std::string &height,
		const std::vector<std::string> &widths,
		long double max_bar_value,
		std::size_t max_rows,
		std::string units,
		std::size_t tics,
		std::string figure_position,
		std::string title,
		std::string label
		)
{
	out.precision(3);
	out << std::fixed;

	std::size_t row_count(0);
	std::size_t ranking(1);
	grapenlp::stat_list::const_iterator s(sl.begin());
	std::size_t rows;

	out << "\\footnotesize" << std::endl;
	out << "\\settowidth{\\rankingwidth}{ ";
	for (std::size_t n(sl.size()); n > 0; n /= 10)
		out << '7';
	out << " }" << std::endl;
	std::size_t max_value_digits(0);
	for (std::size_t n(max_bar_value); n > 0; n /= 10)
		++max_value_digits;
	do
	{
		std::size_t remaining_rows = sl.size() - row_count;
		rows = remaining_rows < max_rows ? remaining_rows : max_rows;
		out << "\\begin{figure}";
		if (figure_position.size())
			out << '[' << figure_position << ']';
		out << std::endl;
		out << "\\begin{center}" << std::endl;
		out << "\\footnotesize" << std::endl;
		out << "\\begin{tikzpicture}" << std::endl;
//		out << "\\begin{tikzpicture}[every node/.style=draw]" << std::endl;
		out << std::endl;

		//Coordinate for bottom left
		out << "\\path (0,0) coordinate (bl);" << std::endl;
		std::size_t r(rows - 1);
		//Coordinate for last row's ranking column
		out << "\\path (bl)+(0," << height << "/2) coordinate (r" << r << "c0);" << std::endl;
		//Coordinate for last row's parser name column
		out << "\\path (r" << r << "c0) +(\\rankingwidth,0) coordinate (r" << r << "c1);" << std::endl;
		std::size_t c(0);
		//Coordinates for last row's remaining columns
		for (; c != widths.size(); ++c)
			out << "\\path (r" << r << 'c' << (c+1) << ") +(" << widths[c] << ",0) coordinate (r" << r << 'c' << (c+2) << ");" << std::endl;
		//Coordinate for bottom middle
		out << "\\path (r" << r << 'c' << (c+1) << ") +(0,-" << height << "/2) coordinate (bm);" << std::endl;
		//Coordinate for bottom right
		out << "\\path (\\textwidth-1.45ex,0) coordinate (br);" << std::endl;
		//Coordinate for last row's right border
		out << "\\path (br) +(0,\\barchartrowheight/2) coordinate (r" << r << "r);" << std::endl;
		//Coordinate for last row's top-right border
		out << "\\path (br) + (0,\\barchartrowheight) coordinate (r" << r << "tr);" << std::endl;
		//Coordinate for last row's bottom-left
		out << "\\path (bl) coordinate (r" << r << "bl);" << std::endl;
		//Coordinate for last row's top-middle
		out << "\\path (bm) + (0,\\barchartrowheight) coordinate (r" << r << "tm);" << std::endl;
		out << std::endl;

		//Coordinates for remaining rows
		for (--r; r != std::numeric_limits<std::size_t>::max(); --r)
		{
			//Coordinate for ranking column
			out << "\\path (r" << (r + 1) << "c0) +(0," << height << ") coordinate (r" << r << "c0);" << std::endl;
			//Coordinate for parser name column
			out << "\\path (r" << r << "c0) +(\\rankingwidth,0) coordinate (r" << r << "c1);" << std::endl;
			//Coordinate for the remaining columns
			for (c = 0; c != widths.size(); ++c)
				out << "\\path (r" << r << 'c' << (c + 1) << ") +(" << widths[c] << ",0) coordinate (r" << r << 'c' << (c+2) << ");" << std::endl;
			//Coordinate for right border
			out << "\\path (r" << (r+1) << "r) +(0,\\barchartrowheight) coordinate (r" << r << "r);" << std::endl;
			//Coordinate for top-right border
			out << "\\path (r" << (r+1) << "tr) + (0,\\barchartrowheight) coordinate (r" << r << "tr);" << std::endl;
			//Coordinate for bottom-left
			out << "\\path (r" << (r+1) << "bl) + (0,\\barchartrowheight) coordinate (r" << r << "bl);" << std::endl;
			//Coordinate for top-middle
			out << "\\path (r" << (r+1) << "tm) + (0,\\barchartrowheight) coordinate (r" << r << "tm);" << std::endl;
			out << std::endl;
		}

		out << std::endl;
		//Coordinate for top left
		out << "\\path (r0c0) +(0," << height << "/2) coordinate (tl);" << std::endl;
		//Coordinate for top middle
		out << "\\path (r0c" << (c + 1) << ") +(0," << height << "/2) coordinate (tm);" << std::endl;
		//Coordinate for top right
		out << "\\path (tl) +(\\textwidth-1.45ex" << ",0) coordinate (tr);" << std::endl;

		grapenlp::stat_list::const_iterator s2(s);
		//For each row
		for (r = 0; r != rows; ++r, ++s, ++row_count, ++ranking)
		{
			first_x_color &fxc(get_first_x_color(algorithms, key_list, *s));
			if (!fxc.first)
			{
				fxc.first = true;
				out << "\\fill[color=" << fxc.color << "] (r" << r << "bl) rectangle (r" << r << "tm);" << std::endl;
				out << "\\draw (r" << r << "bl) rectangle (r" << r << "tm);" << std::endl;
			}
			//Draw ranking
			out << "\\path (r" << r << "c1) node[left] {" << ranking << "};" << std::endl;
			//Draw parser name
			out << "\\path (r" << r << "c1) node[right] {" << s->parser_name << "};" << std::endl;
			c = 2;
			//Draw params
			for (grapenlp::char_list::const_iterator p(params.begin()); p != params.end(); ++p, ++c)
			{
				grapenlp::param_id_to_value_map::const_iterator p2(s->pitvm.find(*p));
				if (p2 != s->pitvm.end())
					out << "\\path (r" << r << 'c' << c << ") node[right] {" << p2->second << "};" << std::endl;
			}
			long double average_sentences_per_second(boost::lexical_cast<long double>(s->average_sentences_per_second));
			float v(average_sentences_per_second / max_bar_value);
			//Coordinates for this row's value bottom-left corner
			out << "\\path (r" << r << 'c' << c << ") +(0,-\\barchartrowheight/2) coordinate (v" << r << "bl);" << std::endl;
			out << "\\begin{scope}" << std::endl;
			out << "\\clip (v" << r << "bl) rectangle (r" << r << "tr);" << std::endl;
			//Coordinate for this row's value
			out << "\\path ($" << (1-v) << "*(r" << r << 'c' << c << ") + " << v << "*(r" << r << "r)$) coordinate (v" << r << ");" << std::endl;
			//Coordinate for this row's value top-right corner
			out << "\\path (v" << r << ") +(0,\\barchartrowheight/2) coordinate (v" << r << "tr);" << std::endl;
			//Draw bar content
//			out << "\\shade[left color=" << fxc.color << ",right color=" << fxc.color << "!0.25] (v" << r << "bl) rectangle (v" << r << "tr);" << std::endl;
			out << "\\fill[color=" << fxc.color << "] (v" << r << "bl) rectangle (v" << r << "tr);" << std::endl;
			out << "\\end{scope}" << std::endl;
		}

		if (tics)
		{
			out << "\\path (tm) +(0,\\barchartrowheight/2 - 0.75em) node[right,rotate=90] {0};" << std::endl;
			for (std::size_t t(1); t < tics; ++t)
			{
				float y(static_cast<float>(t)/static_cast<float>(tics));
				out << "\\path ($" << (1.0 - y) << "*(tm)+" << y << "*(tr)$) coordinate (t" << t << ");" << std::endl;
				out << "\\path ($" << (1.0 - y) << "*(bm)+" << y << "*(br)$) coordinate (b" << t << ");" << std::endl;
				out << "\\draw[color=gray] (t" << t << ") -- (b" << t << ");" << std::endl;
				out << "\\path (t" << t << ") +(0,\\barchartrowheight/2 - 0.75em) node[right,rotate=90] {";
				out.precision(0);
				out << (y * max_bar_value);
				out.precision(3);
				out << "};" << std::endl;
			}
			out << "\\path (tr) +(0,\\barchartrowheight/2 - 0.75em) node[right,rotate=90] {";
			out.precision(0);
			out << max_bar_value;
			out.precision(3);
			out << "};" << std::endl;
		}

		//For each row
		for (r = 0; r != rows; ++r, ++s2)
		{
			long double average_sentences_per_second(boost::lexical_cast<long double>(s2->average_sentences_per_second));
			float v_min(boost::lexical_cast<long double>(s2->iasps_min) / max_bar_value);
			float v_max(boost::lexical_cast<long double>(s2->iasps_max) / max_bar_value);
			out << "\\begin{scope}" << std::endl;
			out << "\\clip (v" << r << "bl) rectangle (r" << r << "tr);" << std::endl;
			//Coordinates for this row's min & max value
			out << "\\path ($" << (1-v_min) << "*(r" << r << 'c' << c << ") + " << v_min << "*(r" << r << "r)$) coordinate (v" << r << "min);" << std::endl;
			out << "\\path ($" << (1-v_max) << "*(r" << r << 'c' << c << ") + " << v_max << "*(r" << r << "r)$) coordinate (v" << r << "max);" << std::endl;
			//Coordinates for this row's error segment top and bottom
			out << "\\path (v" << r << "min) +(0,-0.333*\\barchartrowheight) coordinate (v" << r << "minb);" << std::endl;
			out << "\\path (v" << r << "min) +(0,0.333*\\barchartrowheight) coordinate (v" << r << "mint);" << std::endl;
			out << "\\path (v" << r << "max) +(0,-0.333*\\barchartrowheight) coordinate (v" << r << "maxb);" << std::endl;
			out << "\\path (v" << r << "max) +(0,0.333*\\barchartrowheight) coordinate (v" << r << "maxt);" << std::endl;
			//Draw bar profile & error segment
			out << "\\draw (v" << r << "bl) rectangle (v" << r << "tr);" << std::endl;
			out << "\\draw (v" << r << "min) -- (v" << r << "max);" << std::endl;
			out << "\\draw (v" << r << "minb) -- (v" << r << "mint);" << std::endl;
			out << "\\draw (v" << r << "maxb) -- (v" << r << "maxt);" << std::endl;
			//Draw value label
			out << "\\path (";
			if (v_min < 1.0)
				out << 'v' << r << "min";
			else out << 'r' << r << "r";
			out << ") node[left] {$";
			out.precision(0);
			out << average_sentences_per_second;
			out.precision(3);
			if (boost::lexical_cast<long double>(s2->average_sentences_per_second) > max_bar_value)
				out << "\\ggg";
			out << "$};" << std::endl;
			out << "\\end{scope}" << std::endl;
		}

		//Coordinate for ytitle
		out << "\\path ($.5*(tm) + .5*(tr)$) coordinate (tc);" << std::endl;
		out << "\\path (tc) +(0," << max_value_digits << "em) coordinate (ytitle);" << std::endl;
		//Draw ytitle
		out << "\\path (ytitle) node {" << units << "};" << std::endl;

		//Draw chart box
		out << "\\draw[line width=1pt] (bm) rectangle (tr);" << std::endl;

		out << "\\end{tikzpicture}" << std::endl;
		out << "\\normalsize" << std::endl;
		if (s == sl.end())
		{
			if (title.size())
				out << "\\caption{" << title << '}' << std::endl;
			if (label.size())
				out << "\\label{" << label << '}' << std::endl;
		}
		out << "\\end{center}" << std::endl;
		out << "\\end{figure}" << std::endl;
		out << std::endl;
		out << std::endl;
	} while(s != sl.end());
	return out;
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
		const std::string &height,
		const std::vector<std::string> &widths,
		long double max_bar_value,
		std::size_t max_rows,
		std::string units,
		std::size_t tics,
		std::string figure_position,
		std::string title,
		std::string label
		)
{
	grapenlp::stat_list sl;
	grapenlp::read_stat_list(in, algorithms, key_list, mandatory, forbidden, sl);
	sl.sort(grapenlp::average_sentences_per_second_stat_comparator());
	write_chart(out, algorithms, params, key_list, sl, height, widths, max_bar_value, max_rows, units, tics, figure_position, title, label);
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
		("height,h", value<std::string>(), "Row height in Latex format (e.g.: -h1ex)")
		("widths,w", value<std::string>(), "Comma-separated list of algorithm name and parameter column widths in Latex format (e.g.: -w5cm,2cm,\\col3width,...)")
		("max-value,v", value<long double>(), "Max represented value by bar lengths")
		("max-rows,r", value<std::size_t>(), "Max rows per table")
		("units,u", value<std::string>(), "Label specifying the value unit")
		("number-of-tics,n", value<std::size_t>(), "Number of tic marcs to draw along the value axe, without counting the one for the coordinate origin; omit or set to 0 if no tics are required")
		("colors,c", value<std::string>(), "(key_value,)*color(.(key_value,)*color)*(:(key_value,)*color(.(key_value,)*color)*) Color specification of each algorithm and combination of key parameter values; there must be a color specification for each algorithm and possible set of key parameter values")
		("position", value<std::string>(), "Code specifying figure placement (XXX in \\begin{figure}[XXX]")
		("title,t", value<std::string>(), "Title of graph (latex caption)")
		("label,l", value<std::string>(), "Graph identifier (latex label)")
		("input,i", value<std::string>(), "Input file containing stats from nlp program (standard input if omitted)")
	    ("output,o", value<std::string>(), "Output latex file to generate (standard output if omitted)")
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

	grapenlp::char_list params;
	grapenlp::char_set key;
	grapenlp::char_list key_list;
	grapenlp::char_set mandatory;
	if (vm.count("params"))
	{
		std::string ps(vm["params"].as<std::string>());
		std::string::const_iterator i(ps.begin());
		while (i != ps.end())
		{
			params.push_back(*i);
			char c(*i);
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
	}

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

	std::list<first_x_color> first_and_colors;
	if (vm.count("colors"))
	{
		std::string colors(vm["colors"].as<std::string>());
		std::string::const_iterator i(colors.begin());
		alg_ptr_list::const_iterator j(alg_ptrs.begin());
		//For each algorithm name
		while (true)
		{
			grapenlp::alg_trie::string::ref s(*j);
			//While there are key value/color combinations for this algorithm
			if (i == colors.end() || *i == ':')
				fatal_error("Empty color list for algorithm\n");
			//For each combination of key param values
			while (true)
			{
				grapenlp::alg_trie::string::ref s2(s);
				//For each key param value
				for (grapenlp::char_list::const_iterator k(key_list.begin()); k != key_list.end(); ++k)
				{
					//Append param value to algorithm trie string
					while (i != colors.end() && *i != ',' && *i != '.' && *i != ':')
					{
						s2 = &s2->concat(*i);
						++i;
					}
					if (i == colors.end())
						fatal_error("Unexpected end key value list\n");
					if (*i != ',')
						fatal_error("Unexpected separator in key value\n");
					//Append end of param value string
					s2 = &s2->concat('$');
					//Skip ','
					++i;
				}
				//Get color bounds
				std::string::const_iterator k(i);
				while (k != colors.end() && *k != '.' && *k != ':' && *k != ',')
					++k;
				if (k != colors.end() && *k == ',')
				{
					std::cerr << "Unexpected separator '" << *k << "' after color '" << std::string(i, k).c_str() << "' in '";
					s2->serialize(std::cerr);
					std::cerr << '\'' << std::endl;
					exit(1);
				}
				//Add color to color list
				first_and_colors.push_back(first_x_color(false, std::string(i, k)));
				//Set algorithm pointer to first_x_color
				s2->data = reinterpret_cast<std::size_t>(&(*(--first_and_colors.end())));
				i = k;
				if (i == colors.end() || *i == ':')
					break;
				//Skip '.'
				++i;
			}
			if (i == colors.end())
				break;
			//Skip ':'
			++i;
			++j;
			if (j == alg_ptrs.end())
				fatal_error("There are less algorithm color specifications than listed algorithms\n");
		}
		if (i != colors.end())
			fatal_error("There are more algorithm color specifications than listed algorithms\n");
	}
	else fatal_error("Key values and colors not specified\n");

	if (!vm.count("height"))
		fatal_error("Must specify row height");
	if (!vm.count("widths"))
		fatal_error("Must specify column widths");
	if (!vm.count("max-value"))
		fatal_error("Must specify max represented value by bar lengths");
	long double max_bar_value(vm["max-value"].as<long double>());

	std::string height(vm["height"].as<std::string>());
	std::string ws(vm["widths"].as<std::string>());
	std::vector<std::string> widths;
	widths.reserve(1 + params.size());
	std::size_t j(ws.find(',',0));
	if (ws.empty())
		fatal_error("Empty list of column widths\n");
	if (j == std::string::npos)
		j = ws.size();
	widths.push_back(ws.substr(0, j));
	std::size_t i(j);
	for (std::size_t k(params.size()); k > 0; --k)
	{
		if (i == ws.size())
			fatal_error("Missing column widths\n");
		++i;
		j = ws.find(',',i);
		if (j == std::string::npos)
			j = ws.size();
		widths.push_back(ws.substr(i, j - i));
		i = j;
	}
	if (i != ws.size())
		fatal_error("Too many column widths specified\n");

	std::size_t max_rows(std::numeric_limits<std::size_t>::max());
	if (vm.count("max-rows"))
	{
		max_rows = (vm["max-rows"].as<std::size_t>());
		if (!max_rows)
			fatal_error("Max number of rows per table must be greater than 0\n");
	}

	if (!vm.count("units"))
		fatal_error("Missing label describing value units\n");
	std::string units(vm["units"].as<std::string>());

	std::size_t tics(0);
	if (vm.count("number-of-tics"))
		tics = (vm["number-of-tics"].as<std::size_t>());

	std::string figure_position("");
	if (vm.count("position"))
		figure_position = (vm["position"].as<std::string>());

	std::string title("");
	if (vm.count("title"))
		title = (vm["title"].as<std::string>());

	std::string label("");
	if (vm.count("label"))
		label = (vm["label"].as<std::string>());

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
	doit(input_is_stdin ? std::cin : fin, output_is_stdout ? std::cout : fout, algorithms, params, key_list, mandatory, forbidden, height, widths, max_bar_value, max_rows, units, tics, figure_position, title, label);
	if (!input_is_stdin)
		fin.close();
	if (!output_is_stdout)
		fout.close();
	return 0;
}
