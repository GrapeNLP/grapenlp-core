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

#ifndef GRAPENLP_STATS_H
#define GRAPENLP_STATS_H

#include <string>
#include <limits>
#include <functional>
#include <array>
#include <list>
#include <set>

#include <boost/lexical_cast.hpp>

#include <grapenlp/error.h>
#include <grapenlp/algorithm.h>
#include <grapenlp/set_trie.h>
#include <grapenlp/iostream.h>
#include <grapenlp/ansi_text_attribute_codes.h>
#include <grapenlp/array.h>

namespace grapenlp
{
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

	class stats_label_dico
	{
	public:
		set_trie<char>::string::const_ref parser_header;
		set_trie<char>::string::const_ref grammar_states;
		set_trie<char>::string::const_ref grammar_transitions;
		set_trie<char>::string::const_ref input_chars;
		set_trie<char>::string::const_ref input_tokens;
		set_trie<char>::string::const_ref input_sentences;
		set_trie<char>::string::const_ref input_parses;
		set_trie<char>::string::const_ref average_chars_per_token;
		set_trie<char>::string::const_ref average_tokens_per_sentence;
		set_trie<char>::string::const_ref average_chars_per_sentence;
		set_trie<char>::string::const_ref average_parses_per_sentence;
		set_trie<char>::string::const_ref total_chars;
		set_trie<char>::string::const_ref total_tokens;
		set_trie<char>::string::const_ref total_sentences;
		set_trie<char>::string::const_ref total_parses;
		set_trie<char>::string::const_ref total_elapsed_seconds;
		set_trie<char>::string::const_ref average_seconds_per_sentence;
		set_trie<char>::string::const_ref asps_sd_cv_p_min_max;
		set_trie<char>::string::const_ref average_sentences_per_second;

		stats_label_dico(set_trie<char> &stats_label_trie):
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
	};
	extern set_trie<char> the_stats_label_set_trie;
	extern stats_label_dico the_stats_label_dico;

	typedef std::map<char, std::string> param_id_to_value_map;

	struct stats
	{
		std::string parser_name;
		param_id_to_value_map pitvm;
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

		stats();
		void reset();
	};

	typedef std::list<stats> stat_list;
	typedef std::set<char> char_set;
	typedef std::list<char> char_list;

	typedef trie_with_def_data<char, zero_func<std::size_t> > alg_trie;

	template<typename CharT, typename Traits>
	std::basic_istream<CharT, Traits>& skip_up_to_char(std::basic_istream<CharT, Traits> &in, char c)
	{ return in.ignore(std::numeric_limits<std::streamsize>::max(),in.widen(c)); }

	template<typename CharT, typename Traits>
	std::basic_istream<CharT, Traits>& skip_line(std::basic_istream<CharT, Traits> &in)
	{ return skip_up_to_char(in, '\n'); }

	bool is_digit_or_dot(char c)
	{ return isdigit(c) || c == '.'; }

	bool is_digit_or_dot_or_sign_or_e(char c)
	{ return is_digit_or_dot(c) || c == '+' || c == '-' || c == 'e' || c == 'E'; }

	std::pair<std::string, std::string::const_iterator> get_ending_figure_string(const std::string &line, std::string::const_iterator end);

	std::pair<std::string, std::string::const_iterator> get_ending_figure_string(const std::string &line)
	{ return get_ending_figure_string(line, line.end()); }

	void get_sd_cv_p_min_max(const std::string &line, std::string &sd, std::string &cv, std::string &p, std::string &min, std::string &max);

	template<typename CharT, typename Traits>
	std::basic_istream<CharT, Traits>& operator>> (std::basic_istream<CharT, Traits> &in, stats &s)
	{
		s.reset();
		//Skip up to next parser header box
		skip_up_to_char(in, '*');
		skip_up_to_char(in, ' ');
		std::string parser_name;
		std::getline(in, parser_name, '*');
		std::size_t i(0);
		std::size_t j(parser_name.find(' '));
		if (!j)
			fatal_error("Empty parser name\n");
		if (j == std::string::npos)
			fatal_error("Invalid input file format: missing space after algorithm name\n");
		s.parser_name = parser_name.substr(0, j);
		i = j + 1;
		while (i < parser_name.size() - 1)
		{
			j = parser_name.find(' ', i);
			if (j == std::string::npos)
				fatal_error("Invalid input file format: missing space after algorithm parameter\n");
			if (i == j)
				fatal_error("Empty parser parameter\n");
			if ((j - i) < 2)
				fatal_error("Parser parameter has less than 2 chars\n");
			if (!(s.pitvm.insert(std::make_pair(parser_name[i+1], parser_name.substr(i, j - i))).second))
				fatal_error("Repeated param id '%c'\n", parser_name[i+1]);
			i = j + 1;
		}
		skip_line(in);
		skip_line(in);
		set_trie<char>::string::ref stsr;
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
	std::basic_ostream<CharT, Traits>& serialize_parser_name_and_parameters(std::basic_ostream<CharT, Traits> &out, const stats &s)
	{
		out << s.parser_name;
		for (param_id_to_value_map::const_iterator i(s.pitvm.begin()); i != s.pitvm.end(); ++i)
			out << " " << i->second;
		return out;
	}

	template<typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const stats &s)
	{
		std::string parser_name(s.parser_name);
		for (param_id_to_value_map::const_iterator i(s.pitvm.begin()); i != s.pitvm.end(); ++i)
			parser_name += std::string(" ") + i->second;
		serialize_starbox(out, parser_name.begin(), parser_name.end(), std::string(ANSI_BRIGHT_CYAN_FG) + std::string(ANSI_BLACK_BG), std::string(ANSI_DEFAULT));
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
		{ return boost::lexical_cast<long double>(s1.average_sentences_per_second) > boost::lexical_cast<long double>(s2.average_sentences_per_second); }
	};

	struct algorithm_names_and_parameters_comparator: public std::binary_function<stats, stats, bool>
	{
		const char_list &params;

		algorithm_names_and_parameters_comparator(const char_list &params_): params(params_)
		{}

		bool operator() (const stats &s1, const stats &s2) const;
	};

	struct desc_algorithm_names_and_parameters_comparator: public std::binary_function<stats, stats, bool>
	{
		const char_list &params;

		desc_algorithm_names_and_parameters_comparator(const char_list &params_): params(params_)
		{}

		bool operator() (const stats &s1, const stats &s2) const;
	};

	bool algorithm_is_a_chosen_one(const alg_trie &algorithms, const char_list &key_list, const char_set &mandatory, const char_set &forbidden, const stats &s);

	template<typename CharT, typename Traits>
	std::basic_istream<CharT, Traits>& read_stat_list(
		std::basic_istream<CharT, Traits> &in,
		const alg_trie &algorithms,
		const char_list &key_list,
		const char_set &mandatory,
		const char_set &forbidden,
		stat_list &sl)
	{
		stats s;
		in >> s;
		if (s.parser_name.empty())
			fatal_error("No algorithm stats found\n");
		if (algorithm_is_a_chosen_one(algorithms, key_list, mandatory, forbidden, s))
			sl.push_back(s);
		while (!in.eof())
		{
			in >> s;
			if (algorithm_is_a_chosen_one(algorithms, key_list, mandatory, forbidden, s))
				sl.push_back(s);
		}
		return in;
	}
} //namespace grapenlp

#endif /*GRAPENLP_STATS_H*/
