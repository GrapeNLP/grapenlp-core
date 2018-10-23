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

#include <grapenlp/stats.h>

namespace grapenlp
{
	set_trie<char> the_stats_label_set_trie;
	stats_label_dico the_stats_label_dico(the_stats_label_set_trie);

	stats::stats():
		parser_name(),
		pitvm(),
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

	void stats::reset()
	{
		parser_name = "";
		pitvm.clear();
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

	bool algorithm_names_and_parameters_comparator::operator() (const stats &s1, const stats &s2) const
	{
		std::ptrdiff_t c(lexicographical_compare_3way(s1.parser_name.begin(), s1.parser_name.end(), s2.parser_name.begin(), s2.parser_name.end()));
		if (c)
			return c < 0;
		char_list::const_iterator i;
		param_id_to_value_map::const_iterator pit1, pit2;
		for (i = params.begin(); i != params.end(); ++i)
		{
			//s1 has param
			if ((pit1 = s1.pitvm.find(*i)) != s1.pitvm.end())
			{
				//but s2 doesn't
				if ((pit2 = s2.pitvm.find(*i)) == s2.pitvm.end())
					return false;
				c = lexicographical_compare_3way(pit1->second.begin(), pit1->second.end(), pit2->second.begin(), pit2->second.end());
				if (c)
					return c < 0;
			}
			//s1 hasn't param but s2 has
			else if (s2.pitvm.find(*i) != s2.pitvm.end())
				return true;
		}
		return false;
	}

	bool desc_algorithm_names_and_parameters_comparator::operator() (const stats &s1, const stats &s2) const
	{
		std::ptrdiff_t c(lexicographical_compare_3way(s1.parser_name.begin(), s1.parser_name.end(), s2.parser_name.begin(), s2.parser_name.end()));
		if (c)
			return c > 0;
		char_list::const_iterator i;
		param_id_to_value_map::const_iterator pit1, pit2;
		for (i = params.begin(); i != params.end(); ++i)
		{
			//s1 has param
			if ((pit1 = s1.pitvm.find(*i)) != s1.pitvm.end())
			{
				//but s2 doesn't
				if ((pit2 = s2.pitvm.find(*i)) == s2.pitvm.end())
					return true;
				c = lexicographical_compare_3way(pit1->second.begin(), pit1->second.end(), pit2->second.begin(), pit2->second.end());
				if (c)
					return c > 0;
			}
			//s1 hasn't param but s2 has
			else if (s2.pitvm.find(*i) != s2.pitvm.end())
				return false;
		}
		return false;
	}

	bool algorithm_is_a_chosen_one(const alg_trie &algorithms, const char_list &key_list, const char_set &mandatory, const char_set &forbidden, const stats &s)
	{
		alg_trie::string::const_ref s2(algorithms.epsilon().get(s.parser_name.begin(), s.parser_name.end()));
		if (!s2 || !(s2 = s2->get('$')))
			return false;

		for (param_id_to_value_map::const_iterator i(s.pitvm.begin()); i != s.pitvm.end(); ++i)
			if (forbidden.find(i->first) != forbidden.end())
				return false;

		for (char_set::const_iterator i(mandatory.begin()); i != mandatory.end(); ++i)
			if (s.pitvm.find(*i) == s.pitvm.end())
				return false;

/*		for (char_list::const_iterator i(key_list.begin()); i != key_list.end(); ++i)
		{
			param_id_to_value_map::const_iterator j(s.pitvm.find(*i));
			if (j != s.pitvm.end())
			{
				s2 = s2->get(j->second.begin(), j->second.end());
				if (!s2)
					fatal_error("Key value not present in color list\n");
			}
			if (!(s2 = s2->get('$')))
				fatal_error("Key value not present in color list\n");
		}
		if (!s2->data)
			fatal_error("Incomplete key value list\n");
*/
		return true;
	}
} //namespace grapenlp
