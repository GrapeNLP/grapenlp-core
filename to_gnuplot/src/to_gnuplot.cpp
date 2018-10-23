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


#include <cstdarg>
#include <string>
#include <fstream>
#include <limits>
#include <functional>
#include <list>

#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

#include <grapenlp/algorithm.h>
#include <grapenlp/set_trie.h>
#include <array>
#include <grapenlp/iostream.h>
#include <grapenlp/ansi_text_attribute_codes.h>

using namespace boost;
using namespace boost::program_options;

void fatal_error(const char* format,...) {
va_list list;
va_start(list,format);
vfprintf(stderr,format,list);
va_end(list);
exit(1);
}

void help(const std::string &program_name, const options_description &desc)
{
	std::cout << "Usage: " << program_name.c_str() << " output" << std::endl;
	std::cout << desc;
}

#ifdef UNIX
const std::array<char, 14> parser_header_label = { {'\033', '[', '1', ';', '3', '6', 'm', '\033', '[', '4', '0', 'm', '*', '*'} };
#else
const std::array<char, 2> parser_header_label = { {'*', '*'} };
#endif
const std::array<char, 14> grammar_states_label = { {'G', 'r', 'a', 'm', 'm', 'a', 'r', ' ', 's', 't', 'a', 't', 'e', 's'} };
const std::array<char, 19> grammar_transitions_label = { {'G', 'r', 'a', 'm', 'm', 'a', 'r', ' ', 't', 'r', 'a', 'n', 's', 'i', 't', 'i', 'o', 'n', 's'} };
const std::array<char, 11> input_chars_label = { {'I', 'n', 'p', 'u', 't', ' ', 'c', 'h', 'a', 'r', 's'} };
const std::array<char, 12> input_tokens_label = { {'I', 'n', 'p', 'u', 't', ' ', 't', 'o', 'k', 'e', 'n', 's'} };
const std::array<char, 15> input_sentences_label = { {'I', 'n', 'p', 'u', 't', ' ', 's', 'e', 'n', 't', 'e', 'n', 'c', 'e', 's'} };
const std::array<char, 12> input_parses_label = { {'I', 'n', 'p', 'u', 't', ' ', 'p', 'a', 'r', 's', 'e', 's'} };
const std::array<char, 23> average_chars_per_token_label = { {'A', 'v', 'e', 'r', 'a', 'g', 'e', ' ', 'c', 'h', 'a', 'r', 's', ' ', 'p', 'e', 'r', ' ', 't', 'o', 'k', 'e', 'n'} };
const std::array<char, 27> average_tokens_per_sentence_label = { {'A', 'v', 'e', 'r', 'a', 'g', 'e', ' ', 't', 'o', 'k', 'e', 'n', 's', ' ', 'p', 'e', 'r', ' ', 's', 'e', 'n', 't', 'e', 'n', 'c', 'e'} };
const std::array<char, 26> average_chars_per_sentence_label = { {'A', 'v', 'e', 'r', 'a', 'g', 'e', ' ', 'c', 'h', 'a', 'r', 's', ' ', 'p', 'e', 'r', ' ', 's', 'e', 'n', 't', 'e', 'n', 'c', 'e'} };
const std::array<char, 27> average_parses_per_sentence_label = { {'A', 'v', 'e', 'r', 'a', 'g', 'e', ' ', 'p', 'a', 'r', 's', 'e', 's', ' ', 'p', 'e', 'r', ' ', 's', 'e', 'n', 't', 'e', 'n', 'c', 'e'} };
const std::array<char, 11> total_chars_label = { {'T', 'o', 't', 'a', 'l', ' ', 'c', 'h', 'a', 'r', 's'} };
const std::array<char, 12> total_tokens_label = { {'T', 'o', 't', 'a', 'l', ' ', 't', 'o', 'k', 'e', 'n', 's'} };
const std::array<char, 15> total_sentences_label = { {'T', 'o', 't', 'a', 'l', ' ', 's', 'e', 'n', 't', 'e', 'n', 'c', 'e', 's'} };
const std::array<char, 12> total_parses_label = { {'T', 'o', 't', 'a', 'l', ' ', 'p', 'a', 'r', 's', 'e', 's'} };
const std::array<char, 21> total_elapsed_seconds_label = { {'T', 'o', 't', 'a', 'l', ' ', 'e', 'l', 'a', 'p', 's', 'e', 'd', ' ', 's', 'e', 'c', 'o', 'n', 'd', 's'} };
const std::array<char, 28> average_seconds_per_sentence_label = { {'A', 'v', 'e', 'r', 'a', 'g', 'e', ' ', 's', 'e', 'c', 'o', 'n', 'd', 's', ' ', 'p', 'e', 'r', ' ', 's', 'e', 'n', 't', 'e', 'n', 'c', 'e'} };
const std::array<char, 21> asps_sd_cv_p_min_max_label = { {'S', 'D', ',', ' ', 'C', 'V', '%', ',', ' ', 'P', '%', ',', ' ', 'm', 'i', 'n', ',', ' ', 'm', 'a', 'x'} };
const std::array<char, 28> average_sentences_per_second_label = { {'A', 'v', 'e', 'r', 'a', 'g', 'e', ' ', 's', 'e', 'n', 't', 'e', 'n', 'c', 'e', 's', ' ', 'p', 'e', 'r', ' ', 's', 'e', 'c', 'o', 'n', 'd'} };

grapenlp::set_trie<char> the_stats_label_set_trie;

class stats_label_dico
{
public:
	grapenlp::set_trie<char>::string::const_ref parser_header;
	grapenlp::set_trie<char>::string::const_ref grammar_states;
	grapenlp::set_trie<char>::string::const_ref grammar_transitions;
	grapenlp::set_trie<char>::string::const_ref input_chars;
	grapenlp::set_trie<char>::string::const_ref input_tokens;
	grapenlp::set_trie<char>::string::const_ref input_sentences;
	grapenlp::set_trie<char>::string::const_ref input_parses;
	grapenlp::set_trie<char>::string::const_ref average_chars_per_token;
	grapenlp::set_trie<char>::string::const_ref average_tokens_per_sentence;
	grapenlp::set_trie<char>::string::const_ref average_chars_per_sentence;
	grapenlp::set_trie<char>::string::const_ref average_parses_per_sentence;
	grapenlp::set_trie<char>::string::const_ref total_chars;
	grapenlp::set_trie<char>::string::const_ref total_tokens;
	grapenlp::set_trie<char>::string::const_ref total_sentences;
	grapenlp::set_trie<char>::string::const_ref total_parses;
	grapenlp::set_trie<char>::string::const_ref total_elapsed_seconds;
	grapenlp::set_trie<char>::string::const_ref average_seconds_per_sentence;
	grapenlp::set_trie<char>::string::const_ref asps_sd_cv_p_min_max;
	grapenlp::set_trie<char>::string::const_ref average_sentences_per_second;

	stats_label_dico(grapenlp::set_trie<char> &stats_label_trie):
		parser_header(&(stats_label_trie.add(parser_header_label.begin(), parser_header_label.end()))),
		grammar_states(&(stats_label_trie.add(grammar_states_label.begin(), grammar_states_label.end()))),
		grammar_transitions(&(stats_label_trie.add(grammar_transitions_label.begin(), grammar_transitions_label.end()))),
		input_chars(&(stats_label_trie.add(input_chars_label.begin(), input_chars_label.end()))),
		input_tokens(&(stats_label_trie.add(input_tokens_label.begin(), input_tokens_label.end()))),
		input_sentences(&(stats_label_trie.add(input_sentences_label.begin(), input_sentences_label.end()))),
		input_parses(&(stats_label_trie.add(input_parses_label.begin(), input_parses_label.end()))),
		average_chars_per_token(&(stats_label_trie.add(average_chars_per_token_label.begin(), average_chars_per_token_label.end()))),
		average_tokens_per_sentence(&(stats_label_trie.add(average_tokens_per_sentence_label.begin(), average_tokens_per_sentence_label.end()))),
		average_chars_per_sentence(&(stats_label_trie.add(average_chars_per_sentence_label.begin(), average_chars_per_sentence_label.end()))),
		average_parses_per_sentence(&(stats_label_trie.add(average_parses_per_sentence_label.begin(), average_parses_per_sentence_label.end()))),
		total_chars(&(stats_label_trie.add(total_chars_label.begin(), total_chars_label.end()))),
		total_tokens(&(stats_label_trie.add(total_tokens_label.begin(), total_tokens_label.end()))),
		total_sentences(&(stats_label_trie.add(total_sentences_label.begin(), total_sentences_label.end()))),
		total_parses(&(stats_label_trie.add(total_parses_label.begin(), total_parses_label.end()))),
		total_elapsed_seconds(&(stats_label_trie.add(total_elapsed_seconds_label.begin(), total_elapsed_seconds_label.end()))),
		average_seconds_per_sentence(&(stats_label_trie.add(average_seconds_per_sentence_label.begin(), average_seconds_per_sentence_label.end()))),
		asps_sd_cv_p_min_max(&(stats_label_trie.add(asps_sd_cv_p_min_max_label.begin(), asps_sd_cv_p_min_max_label.end()))),
		average_sentences_per_second(&(stats_label_trie.add(average_sentences_per_second_label.begin(), average_sentences_per_second_label.end())))
	{}
} the_stats_label_dico(the_stats_label_set_trie);

struct stats
{
	std::string parser_name;
	std::string grammar_states;
	std::string grammar_transitions;
	std::string input_chars;
	std::string input_tokens;
	std::string input_sentences;
	std::string input_parses;
	std::string average_chars_per_token;
	std::string average_tokens_per_sentence;
	std::string average_chars_per_sentence;
	std::string average_parses_per_sentence;
	std::string total_chars;
	std::string total_tokens;
	std::string total_sentences;
	std::string total_parses;
	std::string total_elapsed_seconds;
	std::string average_seconds_per_sentence;
	std::string asps_sd, asps_cv, asps_p, asps_min, asps_max;
	std::string average_sentences_per_second;
	std::string iasps_sd, iasps_cv, iasps_p, iasps_min, iasps_max;

	stats():
		parser_name(),
		grammar_states(),
		grammar_transitions(),
		input_chars(),
		input_tokens(),
		input_sentences(),
		input_parses(),
		average_chars_per_token(),
		average_tokens_per_sentence(),
		average_chars_per_sentence(),
		average_parses_per_sentence(),
		total_chars(),
		total_tokens(),
		total_sentences(),
		total_parses(),
		total_elapsed_seconds(),
		average_seconds_per_sentence(),
		asps_sd(), asps_cv(), asps_p(), asps_min(), asps_max(),
		average_sentences_per_second(),
		iasps_sd(), iasps_cv(), iasps_p(), iasps_min(), iasps_max()
	{}

	void reset()
	{
		parser_name = "";
		grammar_states = "";
		grammar_transitions = "";
		input_chars = "";
		input_tokens = "";
		input_sentences = "";
		input_parses = "";
		average_chars_per_token = "";
		average_tokens_per_sentence = "";
		average_chars_per_sentence = "";
		average_parses_per_sentence = "";
		total_chars = "";
		total_tokens = "";
		total_sentences = "";
		total_parses = "";
		total_elapsed_seconds = "";
		average_seconds_per_sentence = "";
		asps_sd = ""; asps_cv = ""; asps_p = ""; asps_min = ""; asps_max = "";
		average_sentences_per_second = "";
		iasps_sd = ""; iasps_cv = ""; iasps_p = ""; iasps_min = ""; iasps_max = "";
	}
};

int fill_style(const std::string &parser_name)
{
	if (grapenlp::includes(parser_name, "-o"))
		return 1;
	if (grapenlp::includes(parser_name, "fprtn "))
		return 2;
	return 0;
}

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& skip_up_to_char(std::basic_istream<CharT, Traits> &in, char c)
{ return in.ignore(std::numeric_limits<std::streamsize>::max(),in.widen(c)); }

template<typename CharT, typename Traits>
inline std::basic_istream<CharT, Traits>& skip_line(std::basic_istream<CharT, Traits> &in)
{ return skip_up_to_char(in, '\n'); }

inline bool is_digit(char c)
{ return c >= '0' && c <= '9'; }

inline bool is_digit_or_dot(char c)
{ return is_digit(c) || c == '.'; }

inline bool is_digit_or_dot_or_sign_or_e(char c)
{ return is_digit_or_dot(c) || c == '+' || c == '-' || c == 'e' || c == 'E'; }

std::pair<std::string, std::string::const_iterator> get_ending_figure_string(const std::string &line, std::string::const_iterator end)
{
	while (end != line.begin() && !is_digit_or_dot(*(--end)));
	if (end == line.begin())
		return std::make_pair("", end);
	std::string::const_iterator begin = end;
	while (begin != line.begin() && is_digit_or_dot_or_sign_or_e(*(--begin)));
	++begin;
	++end;
	return std::make_pair(std::string(begin, end), begin);
}

inline std::pair<std::string, std::string::const_iterator> get_ending_figure_string(const std::string &line)
{ return get_ending_figure_string(line, line.end()); }

void get_sd_cv_p_min_max(const std::string &line, std::string &sd, std::string &cv, std::string &p, std::string &min, std::string &max)
{
	std::pair<std::string, std::string::const_iterator> result(get_ending_figure_string(line));
	max = result.first;
	result = get_ending_figure_string(line, result.second);
	min = result.first;
	result = get_ending_figure_string(line, result.second);
	p = result.first;
	result = get_ending_figure_string(line, result.second);
	cv = result.first;
	result = get_ending_figure_string(line, result.second);
	sd = result.first;
}

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>> (std::basic_istream<CharT, Traits> &in, stats &s)
{
	s.reset();
	//Skip up to next parser header box
	skip_up_to_char(in, '*');
	skip_up_to_char(in, ' ');
	std::getline(in, s.parser_name, '*');
	s.parser_name = s.parser_name.substr(0, s.parser_name.size() - 1);
	skip_line(in);
	skip_line(in);
	grapenlp::set_trie<char>::string::ref stsr;
	std::string line;
	bool asps_sd_cv_p_min_max_read(false);
	while(!in.eof())
	{
		std::getline(in, line);
		stsr = the_stats_label_set_trie.get_longest_match(line.begin(), line.end());
		if (!stsr->data)
			continue;
		if (stsr == the_stats_label_dico.parser_header) return in;
		else if (stsr == the_stats_label_dico.grammar_states) s.grammar_states = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.grammar_transitions) s.grammar_transitions = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.input_chars) s.input_chars = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.input_tokens) s.input_tokens = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.input_sentences) s.input_sentences = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.input_parses) s.input_parses = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.average_chars_per_token) s.average_chars_per_token = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.average_tokens_per_sentence) s.average_tokens_per_sentence = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.average_chars_per_sentence) s.average_chars_per_sentence = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.average_parses_per_sentence) s.average_parses_per_sentence = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.total_chars) s.total_chars = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.total_tokens) s.total_tokens = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.total_sentences) s.total_sentences = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.total_parses) s.total_parses = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.total_elapsed_seconds) s.total_elapsed_seconds = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.average_seconds_per_sentence) s.average_seconds_per_sentence = get_ending_figure_string(line).first;
		else if (stsr == the_stats_label_dico.asps_sd_cv_p_min_max)
		{
			if (asps_sd_cv_p_min_max_read)
				get_sd_cv_p_min_max(line, s.iasps_sd, s.iasps_cv, s.iasps_p, s.iasps_min, s.iasps_max);
			else
			{
				get_sd_cv_p_min_max(line, s.asps_sd, s.asps_cv, s.asps_p, s.asps_min, s.asps_max);
				asps_sd_cv_p_min_max_read = true;
			}
		}
		else if (stsr == the_stats_label_dico.average_sentences_per_second) s.average_sentences_per_second = get_ending_figure_string(line.substr(0, line.size() - 4)).first;
	}
	return in;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const stats &s)
{
	if (s.parser_name.empty())
	{
		out << "empty";
		return out;
	}
	grapenlp::serialize_starbox(out, s.parser_name.begin(), s.parser_name.end(), std::string(ANSI_BRIGHT_CYAN_FG) + std::string(ANSI_BLACK_BG), std::string(ANSI_DEFAULT));
	if (!s.grammar_states.empty())
		the_stats_label_dico.grammar_states->serialize(out) << ": " << s.grammar_states << std::endl;
	if (!s.grammar_transitions.empty())
		the_stats_label_dico.grammar_transitions->serialize(out) << ": " << s.grammar_transitions << std::endl;
	if (!s.input_chars.empty())
		the_stats_label_dico.input_chars->serialize(out) << ": " << s.input_chars << std::endl;
	if (!s.input_tokens.empty())
		the_stats_label_dico.input_tokens->serialize(out) << ": " << s.input_tokens << std::endl;
	if (!s.input_sentences.empty())
		the_stats_label_dico.input_sentences->serialize(out) << ": " << s.input_sentences << std::endl;
	if (!s.input_parses.empty())
		the_stats_label_dico.input_parses->serialize(out) << ": " << s.input_parses << std::endl;
	if (!s.average_chars_per_token.empty())
		the_stats_label_dico.average_chars_per_token->serialize(out) << ": " << s.average_chars_per_token << std::endl;
	if (!s.average_tokens_per_sentence.empty())
		the_stats_label_dico.average_tokens_per_sentence->serialize(out) << ": " << s.average_tokens_per_sentence << std::endl;
	if (!s.average_chars_per_sentence.empty())
		the_stats_label_dico.average_chars_per_sentence->serialize(out) << ": " << s.average_chars_per_sentence << std::endl;
	if (!s.average_parses_per_sentence.empty())
		the_stats_label_dico.average_parses_per_sentence->serialize(out) << ": " << s.average_parses_per_sentence << std::endl;
	if (!s.total_chars.empty())
		the_stats_label_dico.total_chars->serialize(out) << ": " << s.total_chars << std::endl;
	if (!s.total_tokens.empty())
		the_stats_label_dico.total_tokens->serialize(out) << ": " << s.total_tokens << std::endl;
	if (!s.total_sentences.empty())
		the_stats_label_dico.total_sentences->serialize(out) << ": " << s.total_sentences << std::endl;
	if (!s.total_parses.empty())
		the_stats_label_dico.total_parses->serialize(out) << ": " << s.total_parses << std::endl;
	if (!s.total_elapsed_seconds.empty())
		the_stats_label_dico.total_elapsed_seconds->serialize(out) << ": " << s.total_elapsed_seconds << std::endl;
	if (!s.average_seconds_per_sentence.empty())
		the_stats_label_dico.average_seconds_per_sentence->serialize(out) << ": " << s.average_seconds_per_sentence << std::endl;
	if (!s.asps_sd.empty())
		the_stats_label_dico.asps_sd_cv_p_min_max->serialize(out) << ": " << s.asps_sd << ", " << s.asps_cv << ", " << s.asps_p << ", " << s.asps_min << ", " << s.asps_max << std::endl;
	if (!s.average_sentences_per_second.empty())
		the_stats_label_dico.average_sentences_per_second->serialize(out) << ": " << s.average_sentences_per_second << std::endl;
	if (!s.iasps_sd.empty())
		the_stats_label_dico.asps_sd_cv_p_min_max->serialize(out) << ": " << s.iasps_sd << ", " << s.iasps_cv << ", " << s.iasps_p << ", " << s.iasps_min << ", " << s.iasps_max << std::endl;
	return out;
}

struct average_sentences_per_second_stat_comparator: public std::binary_function<stats, stats, bool>
{
	bool operator() (const stats &s1, const stats &s2) const
	{ return boost::lexical_cast<long double>(s1.average_sentences_per_second) < boost::lexical_cast<long double>(s2.average_sentences_per_second); }
};

template<typename CharT, typename Traits>
void write(std::list<stats>::const_iterator begin,
		std::size_t count,
		std::basic_ostream<CharT, Traits> &out_plt,
		std::basic_ostream<CharT, Traits> &out_dat,
		const std::string &out_tex_path_name,
		const std::string &lmargin,
		const std::string &rmargin,
		const std::string &width,
		const std::string &height
		)
{
	for (std::size_t i(0); i < count; ++i, ++begin)
	{
		out_dat << begin->parser_name << '\t' << begin->average_sentences_per_second << '\t' << begin->iasps_min << '\t' << begin->iasps_max << '\t' << begin->iasps_sd << '\t' << fill_style(begin->parser_name) << std::endl;
	}

	out_plt << "set terminal epslatex" << std::endl <<
		"set output " << out_tex_path_name << std::endl <<
		"set lmargin " << lmargin << std::endl <<
		"set rmargin " << rmargin << std::endl <<
		"set size " << width << "," << height << std::endl <<
		"set boxwidth 0.8" << std::endl <<
		"set bars 2.5" << std::endl <<

		"set xtic rotate by 90 scale 0" << std::endl <<
		"set xrange [-0.575:" << (static_cast<float>(count) - 0.575) << "]" << std::endl <<

		"unset ytics" << std::endl <<
		"set y2tics rotate by 180 offset 4" << std::endl <<

		#set yrange [10000:0];
		#set y2tics ("\\phantom{$1000$}$0$" 0, "\\phantom{$1$}$2000$" 2000, "\\phantom{$1$}$4000$" 4000, "\\phantom{$1$}$6000$" 6000, "\\phantom{$1$}$8000$" 8000, "$10000$" 10000)
		set yrange [0:2000];
		set y2tics ("\\phantom{$200$}$0$" 0, "\\phantom{$2$}$400$" 400, "\\phantom{$2$}$800$" 800, "$1200$" 1200, "$1600$" 1600, "$2000$" 2000)
		set y2label 'Parsed sentences per second' offset 1
		set datafile separator "\t"
		#plot 'stats.dat' using 2 title ' ', '' u ($2/2.0+rand(0)/10.0) title ' ', '' u 0:(0):xticlabel(1) w l title ''

		round(x)=int(x+0.5)

		default_color = "#202020"; to_fprtn_color = "#404040"; no_output_color = "#808080"

		plot \
		'stats_no_keyword.dat' using ($0 - 0.075):($6 == 0?$2:0) with boxes fs solid border 1 lc rgb "red" title '', \
		'stats_no_keyword.dat' using ($0 - 0.075):($6 == 1?$2:0) with boxes fs solid border 1 lc rgb "green" title '', \
		'stats_no_keyword.dat' using ($0 - 0.075):($6 == 2?$2:0) with boxes fs solid border 1 lc rgb "blue" title '', \
		'stats_no_keyword.dat' using ($0 - 0.075):2:3:4 with errorbars ps 0 lt 1 lc rgb "black" title '', \
		'' using 0:($3 > 2000 ? 2000 - 85 : $3 - 85):(sprintf("%.0f",$2)) with labels right rotate by 90 title '', \
		'' using 0:(0):xticlabel((sprintf("%d %s",$0+1,stringcolumn(1)))) with lines title ''
		#'stats_no_keyword.dat' using 0:2 with boxes fillstyle solid lt rgb "violet" title ''


		#'' using 0:(0):xticlabel(sprintf("%.0f",$2)) with lines title '', \
//////////
		"set xrange [-0.5:" << (static_cast<float>(count) - 0.5) << std::endl <<
//	#set yrange [10000:0];
//	#set y2tics ("\\phantom{$1000$}$0$" 0, "\\phantom{$1$}$2000$" 2000, "\\phantom{$1$}$4000$" 4000, "\\phantom{$1$}$6000$" 6000, "\\phantom{$1$}$8000$" 8000, "$10000$" 10000)
//		"set yrange [2000:0]";
//		set y2tics ("\\phantom{$200$}$0$" 0, "\\phantom{$2$}$400$" 400, "\\phantom{$2$}$800$" 800, "$1200$" 1200, "$1600$" 1600, "$2000$" 2000)
		"set y2label 'Parsed sentences per second' offset 1" << std::endl <<
		"set datafile separator '\t'" << std::endl <<
		"plot \\" << std::endl <<
		"'stats_no_keyword.dat' using 0:($6 == 0?$2:0) with boxes fs solid 0 lt -1 title '', \\" << std::endl <<
		"'stats_no_keyword.dat' using 0:($6 == 1?$2:0) with boxes fs solid 0.25 lt -1 title '', \\" << std::endl <<
		"'stats_no_keyword.dat' using 0:($6 == 2?$2:0) with boxes fs solid 0.5 lt 1 title '', \\" << std::endl <<
		"'stats_no_keyword.dat' using 0:2:3:4 with errorbars lt -1 title '', \\" << std::endl <<
		"'' using 0:(0):xticlabel(sprintf(\"%.0f\",$2)) with lines title '', \\" << std::endl <<
		"'' using 0:(0):x2ticlabel(1) with lines title ''" << std::endl;
}

template<typename CharT, typename Traits>
void doit(std::basic_istream<CharT, Traits> &in,
		std::basic_ostream<CharT, Traits> &out_plt,
		std::basic_ostream<CharT, Traits> &out_dat,
		const std::string &out_tex_path_name,
		const std::string &lmargin,
		const std::string &rmargin,
		const std::string &width,
		const std::string &height
		)
{
	stats s;
	std::list<stats> stat_list;
	while (!in.eof())
	{
		in >> s;
		stat_list.push_back(s);
	}
	stat_list.sort(average_sentences_per_second_stat_comparator());
	if ()
	{
		s
	}
}

int main(int argc, char **argv)
{
	//Retrieve program name from program path-name
	std::string program_name(argv[0]);
#ifdef WIN32
	std::size_t last_slash_pos(program_name.find_last_of('\\'));
#else
	std::size_t last_slash_pos(program_name.find_last_of('/'));
#endif
	if (last_slash_pos != std::string::npos)
		program_name = program_name.substr(last_slash_pos + 1, program_name.length());
	// Declare the possible command line arguments
	options_description desc("Options");
	desc.add_options()
		("help,h", "Display this information")
		("input,i", value<std::string>(), "Input file containing stats from nlp program (standard input if omitted)")
	    ("output,o", value<std::string>(), "Name without extension to give to output files (gnuplot script and data file)")
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

	if (!vm.count("output"))
	{
		std::wcout << "Unespecified output\n";
		help(program_name, desc);
		return 1;
	}
	std::string out_path_name(vm["output"].as<std::string>());
	std::string out_plt_path_name(out_path_name + std::string(".plt"));
	std::string out_dat_path_name(out_path_name + std::string(".dat"));
	std::ofstream fout_plt;
	fout_plt.open(out_plt_path_name.c_str());
	if (!fout_plt)
		fatal_error(std::string("Unable to open file \"%s\" for writing\n").c_str(), out_plt_path_name.c_str());
	std::ofstream fout_dat;
	fout_dat.open(out_dat_path_name.c_str());
	if (!fout_dat)
		fatal_error(std::string("Unable to open file \"%s\" for writing\n").c_str(), out_plt_path_name.c_str());

	std::string input_path_name;
	if (vm.count("input"))
	{
		std::string in_path_name(vm["input"].as<std::string>());
		std::ifstream fin;
		fin.open(in_path_name.c_str());
		if (!fin)
			fatal_error(std::string("Unable to open file \"%s\" for reading\n").c_str(), in_path_name.c_str());
		doit(fin, fout_plt, fout_dat);
		fin.close();
	}
	else doit(std::cin, fout_plt, fout_dat);

	fout_plt.close();
	fout_dat.close();
	return 0;
}
