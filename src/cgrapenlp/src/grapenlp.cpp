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

#include <locale>

#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>

#include <grapenlp/config.h>
#include <grapenlp/ansi_text_attribute_codes.h>
#include <grapenlp/stats.h>
#include <grapenlp/u_context_reader.h>
#include <grapenlp/ualxiw_manager.h>

using namespace boost;
using namespace boost::program_options;
using namespace grapenlp;

const unichar sentence_bound_char = '$';
const unichar output_bound_char = '#';

struct global_timer_struct
{
	timer t;
	global_timer_struct(): t()
	{}
	double elapsed()
	{ return t.elapsed(); }
} global_timer;

struct input_range
{
	ua_input_iterator left, right;

	input_range(ua_input_iterator left_, ua_input_iterator right_): left(left_), right(right_)
	{}
};

typedef std::vector<input_range> input_range_vector;

void help(const grapenlp::string &program_name, const options_description &desc)
{
	std::cout << "Usage: " << program_name.c_str() << " [options] grammar dictionary input output [validate]" << std::endl;
	std::cout << desc;
	std::cout << "Note all input text files must be in UTF16-LE format with BOM" << std::endl;
}

std::string::const_iterator get_repeat_argument_end(const std::string &s, std::string::const_iterator begin)
{
	while (begin != arg.end() && ((*begin >= '0' && *begin <= '9') || *begin == '+' || *begin == '-' || *begin == '.'))
		++begin;
	if (begin == arg.begin())
		fatal_error("Repeat argument missing beginning char ('t', 's' or 'r')\n");
	return begin;
}

std::string get_parser_desc(rtno_type grammar_type, rtno_parser_type the_parser_type, bool trie_strings, bool no_output, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice)
{
	std::string parser_desc("");
	switch (the_parser_type)
	{
	case DEPTH_FIRST_RTNO_PARSER: parser_desc += std::string("depth-first"); break;
	case BREADTH_FIRST_RTNO_PARSER: parser_desc += std::string("breadth-first"); break;
	case EARLEY_RTNO_PARSER: parser_desc += std::string("earley"); break;
	case TO_FPRTN_RTNO_PARSER: parser_desc += std::string("to-fprtn"); break;
	case TO_FPRTN_ZPPS_RTNO_PARSER: parser_desc += std::string("to-fprtn-zpps"); break;
	case TO_FPRTN_TOP_RTNO_PARSER: parser_desc += std::string("to-fprtn-top"); break;
	case TO_FPRTN_AND_BREADTH_FIRST_EXPAND_RTNO_PARSER: parser_desc += ("to-fprtn-bfe"); break;
	case TO_FPRTN_AND_BLACKBOARD_SET_EXPAND_RTNO_PARSER: parser_desc += ("to-fprtn-bse"); break;
	case TO_FPRTN_AND_TOP_BLACKBOARD_EXTRACT_RTNO_PARSER: parser_desc += ("to-fprtn-tbe"); break;
	}
	if (the_parser_type != DEPTH_FIRST_RTNO_PARSER)
	{
		parser_desc += std::string(" -e");
		switch (execution_state_set_impl_choice)
		{
		case STD: parser_desc += std::string("std"); break;
		case LRB_TREE: parser_desc += std::string("lrb"); break;
		case LRB_TREE_3W: parser_desc += std::string("lrb-3w"); break;
		default: fatal_error("Unsupported associative container implementation");
		}
	}
	if (!no_output && the_parser_type != TO_FPRTN_RTNO_PARSER && the_parser_type != TO_FPRTN_ZPPS_RTNO_PARSER && the_parser_type != TO_FPRTN_TOP_RTNO_PARSER && !(the_parser_type == TO_FPRTN_AND_TOP_BLACKBOARD_EXTRACT_RTNO_PARSER && grammar_type == LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO))
	{
		parser_desc += std::string(" -b");
		switch (output_set_impl_choice)
		{
		case STD: parser_desc += std::string("std"); break;
		case LRB_TREE: parser_desc += std::string("lrb"); break;
		case LRB_TREE_3W: parser_desc += std::string("lrb-3w"); break;
		default: fatal_error("Unsupported associative container implementation");
		}
	}
	if (trie_strings)
		parser_desc += std::string(" +t");
	if (no_output)
		parser_desc += std::string(" -o");
	return parser_desc;
}

rtno_parser_type compute_parser_type(const std::string &parser_name)
{
	if (parser_name == "depth-first")
		return DEPTH_FIRST_RTNO_PARSER;
	if (parser_name == "breadth-first")
		return BREADTH_FIRST_RTNO_PARSER;
	if (parser_name == "earley")
		return EARLEY_RTNO_PARSER;
	if (parser_name == "to-fprtn")
		return TO_FPRTN_RTNO_PARSER;
	if (parser_name == "to-fprtn-zpps")
		return TO_FPRTN_ZPPS_RTNO_PARSER;
	if (parser_name == "to-fprtn-top")
		return TO_FPRTN_TOP_RTNO_PARSER;
	if (parser_name == "to-fprtn-and-breadth-first-expand")
		return TO_FPRTN_AND_BREADTH_FIRST_EXPAND_RTNO_PARSER;
	if (parser_name == "to-fprtn-and-blackboard-set-expand")
		return TO_FPRTN_AND_BLACKBOARD_SET_EXPAND_RTNO_PARSER;
	if (parser_name == "to-fprtn-and-top-blackboard-extract")
		return TO_FPRTN_AND_TOP_BLACKBOARD_EXTRACT_RTNO_PARSER;
	fatal_error("Invalid parser code \"%s\"; use option --help for listing the valid parser codes\n", parser_name.c_str());
	return DEFAULT_PARSER;
}

assoc_container_impl_choice compute_assoc_container_impl_choice(const std::string &assoc_container_impl_choice_name, const std::string &set_impl_case)
{
	if (assoc_container_impl_choice_name == "std")
		return STD;
	if (assoc_container_impl_choice_name == "lrb-tree")
		return LRB_TREE;
	if (assoc_container_impl_choice_name == "lrb-tree-3w")
		return LRB_TREE_3W;
	fatal_error((std::string("Invalid " ) + set_impl_case + std::string(" set implementation choice \"%s\"; use option --help for listing the valid choices\n")).c_str(), assoc_container_impl_choice_name.c_str());
	return STD;
}

void parse_repeat_arguments(const std::string &arg, std::size_t &repeat_times, long double &repeat_seconds, std::size_t &rerepeats)
{
	if (arg.begin() == arg.end())
		fatal_error("Repeat option without arguments\n");
	std::string::const_iterator begin(arg.begin());
	std::string::const_iterator end(get_repeat_argument_end(arg, arg.begin()));

	//repeat and re-repeat times default to 1
	rerepeats = 1;
	repeat_times = 1;
	bool repeat_times_specified(false);
	bool repeat_seconds_specified(false);
	bool rerepeats_specified(false);
	while (true)
	{
		switch (*end)
		{
		case 't':
			if (repeat_times_specified)
				fatal_error("Repeat times specified twice\n");
			repeat_times = boost::lexical_cast<std::size_t>(std::string(begin, end).c_str());
			repeat_times_specified = true;
			break;
		case 's':
			if (repeat_seconds_specified)
				fatal_error("Repeat seconds specified twice\n");
			repeat_seconds = boost::lexical_cast<long double>(std::string(begin, end).c_str());
			if (repeat_seconds < 0)
				fatal_error("Repeat seconds must be greater than or equal to 0\n");
			repeat_seconds_specified = true;
			break;
		case 'r':
			if (rerepeats_specified)
				fatal_error("Re-repeats specified twice\n");
			rerepeats = boost::lexical_cast<std::size_t>(std::string(begin, end).c_str());
			rerepeats_specified = true;
			break;
		default:
			fatal_error("Unknown repeat argument type specifier '%c' (expected 't', 's' or 'r')\n", *end);
		}
		begin = end;
		++begin;
		if (begin == arg.end())
		{
			if (!repeat_times_specified && !repeat_seconds_specified)
				fatal_error("Repeat option requires to specify the minimum number of repeats and/or the minimum amount of processing time");
			return;
		}
		end = get_repeat_argument_end(arg, begin);
	}
}

u_array generate_anbn(unsigned int n)
{
	if (!n)
		return u_array();
	u_array result(4 * n - 1);
	u_array::iterator i(result.begin());
	u_array::iterator j(result.begin() + 2 * n);

	for (; i != j; ++i)
	{
		*i = 'a';
		++i;
		*i = ' ';
	}

	j = result.end();
	--j;
	for (; i != j; ++i)
	{
		*i = 'b';
		++i;
		*i = ' ';
	}
	*i = 'b';
	return result;
}

bool get_next_bound(ua_input_iterator &input_begin, const ua_input_iterator &input_end, input_range_vector &irv, unichar bound_char, std::size_t &char_count)
{
	//Search for left input bound
	while (input_begin != input_end && *input_begin != bound_char)
		++input_begin;
	//If no more bounds present, return false
	if (input_begin == input_end)
		return false;
	//Skip bound char
	++input_begin;
	//Reset right input bound to last found left input bound
	ua_input_iterator right(input_begin);
	//Search for right input bound
	while (right != input_end && *right != bound_char)
		++right;
	//Right input bound is mandatory!! exit with error if not found
	if (right == input_end)
		fatal_error("Unexpected EOF while looking for right input bound char\n");
	char_count += std::distance(input_begin, right);
	//Add input range
	irv.push_back(input_range(input_begin, right));
	//Shift input begin iterator to the first char right after the last found input bound
	input_begin = right;
	++input_begin;
	return true;
}

input_range_vector& get_sentence_bounds(ua_input_iterator input_begin, ua_input_iterator input_end, input_range_vector &srv, std::size_t &sentence_char_count)
{
	sentence_char_count = 0;
	while (get_next_bound(input_begin, input_end, srv, sentence_bound_char, sentence_char_count));
	return srv;
}

void get_aligned_sentence_bounds(ua_input_iterator input_begin, ua_input_iterator input_end, input_range_vector &srv, std::size_t &sentence_char_count, input_range_vector &orv, std::size_t output_char_count)
{
	sentence_char_count = 0;
	output_char_count = 0;
	while (true)
	{
		if (!get_next_bound(input_begin, input_end, srv, sentence_bound_char, sentence_char_count))
			break;
		if (!get_next_bound(input_begin, input_end, orv, output_bound_char, output_char_count))
			fatal_error("Sentence missing expected output in aligned corpus\n");
	}
}

std::pair<std::size_t, std::size_t> process(ualxiw_manager &the_manager, rtno_parser_type the_parser_type, bool no_output, ua_input_iterator input_begin, ua_input_iterator input_end, const u_context &ctx)
{
	the_manager.set_context(ctx);
	std::size_t token_count(the_manager.tokenize(input_begin, input_end));
	std::size_t parse_count(the_manager.parse());
#if !(defined(DISABLE_LUX_GRAMMAR) && defined(DISABLE_LUXW_GRAMMAR))
#ifdef SIMPLIFIED_OUTPUT
    if (!no_output && the_parser_type != TO_FPRTN_RTNO_PARSER && the_parser_type != TO_FPRTN_ZPPS_RTNO_PARSER && the_parser_type != TO_FPRTN_TOP_RTNO_PARSER && the_manager.get_grammar_type() == LEXMASK_X_WEIGHTED_EXTRACTION_RTNO)
		the_manager.simplify(input_begin, input_end);
#endif
#ifdef SERIALIZED_OUTPUT
	if (!no_output && the_parser_type != TO_FPRTN_RTNO_PARSER && the_parser_type != TO_FPRTN_ZPPS_RTNO_PARSER && the_parser_type != TO_FPRTN_TOP_RTNO_PARSER && (the_manager.get_grammar_type() == LEXMASK_X_EXTRACTION_RTNO || the_manager.get_grammar_type() == LEXMASK_X_WEIGHTED_EXTRACTION_RTNO))
		the_manager.serialize(input_begin, input_end);
#endif
#endif
	return std::make_pair(token_count, parse_count);
}


std::pair<long double, std::size_t> process_corpus_for_stats(ualxiw_manager &the_manager, rtno_parser_type the_parser_type, bool no_output, input_range_vector::const_iterator begin, input_range_vector::const_iterator end, const u_context &ctx, std::size_t min_repeats, long double min_elapsed_seconds)
{
	std::size_t actual_repeats(0);
	timer total_timer;
	do
	{
		for (input_range_vector::const_iterator sentence_it(begin); sentence_it != end; ++sentence_it)
			process(the_manager, the_parser_type, no_output, sentence_it->left, sentence_it->right, ctx);
		++actual_repeats;
	} while (actual_repeats < min_repeats || total_timer.elapsed() < min_elapsed_seconds);
	return std::make_pair(total_timer.elapsed(), actual_repeats);
}

std::pair<long double, std::size_t> process_sentence_for_stats(ualxiw_manager &the_manager, rtno_parser_type the_parser_type, bool no_output, ua_input_iterator begin, ua_input_iterator end, const u_context &ctx, std::size_t min_repeats, long double min_elapsed_seconds)
{
	std::size_t actual_repeats(0);
	timer total_timer;
	do
	{
		process(the_manager, the_parser_type, no_output, begin, end, ctx);
		++actual_repeats;
	}
	while (actual_repeats < min_repeats || total_timer.elapsed() < min_elapsed_seconds);
	return std::make_pair(total_timer.elapsed(), actual_repeats);
}

std::pair<std::size_t, std::size_t> process_and_get_fprtn_stats(ualxiw_manager &the_manager, rtno_parser_type the_parser_type, bool no_output, ua_input_iterator input_begin, ua_input_iterator input_end, const u_context &ctx, std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
{
	the_manager.set_context(ctx);
	std::size_t token_count(the_manager.tokenize(input_begin, input_end));
	std::size_t parse_count(the_manager.parse_and_get_fprtn_stats(state_count, transition_count, pruned_state_count, pruned_transition_count));
#if defined(SERIALIZED_OUTPUT) && !(defined(DISABLE_LUX_GRAMMAR) && defined(DISABLE_LUXW_GRAMMAR))
	if (!no_output && the_parser_type != TO_FPRTN_RTNO_PARSER && the_parser_type != TO_FPRTN_ZPPS_RTNO_PARSER && the_parser_type != TO_FPRTN_TOP_RTNO_PARSER && (the_manager.get_grammar_type() == LEXMASK_X_EXTRACTION_RTNO || the_manager.get_grammar_type() == LEXMASK_X_WEIGHTED_EXTRACTION_RTNO))
		the_manager.serialize(input_begin, input_end);
#endif
	return std::make_pair(token_count, parse_count);
}

void disabled_error(const char *message, rtno_type grammar_type, rtno_parser_type the_parser_type, bool trie_strings, bool no_output, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice)
{ fatal_error((std::string(message) + std::string(" (in ") + get_parser_desc(grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice) + std::string(")\n")).c_str()); }

void verify_requested_parser_is_not_disabled(rtno_type grammar_type, rtno_parser_type the_parser_type, bool trie_strings, bool no_output, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice)
{
	switch (the_parser_type)
	{
	case DEPTH_FIRST_RTNO_PARSER:
#ifdef DISABLE_DEPTH_FIRST_PARSER
		disabled_error("Depth-first parser has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case BREADTH_FIRST_RTNO_PARSER:
#ifdef DISABLE_BREADTH_FIRST_PARSER
	disabled_error("Breadth-first parser has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case EARLEY_RTNO_PARSER:
#ifdef DISABLE_EARLEY_PARSER
		disabled_error("Earley parser has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case TO_FPRTN_RTNO_PARSER:
#ifdef DISABLE_TO_FPRTN_PARSER
		disabled_error("To FPRTN parser has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case TO_FPRTN_ZPPS_RTNO_PARSER:
#ifdef DISABLE_TO_FPRTN_ZPPS_PARSER
		disabled_error("To FPRTN & zpps map parser has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case TO_FPRTN_TOP_RTNO_PARSER:
#ifdef DISABLE_TO_FPRTN_TOP_PARSER
		disabled_error("To FPRTN & top zpps map parser has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case TO_FPRTN_AND_BREADTH_FIRST_EXPAND_RTNO_PARSER:
#ifdef DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER
		disabled_error("To FPRTN & breadth-first expand parser has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case TO_FPRTN_AND_BLACKBOARD_SET_EXPAND_RTNO_PARSER:
#ifdef DISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER
	disabled_error("To FPRTN & blackboard set expand parser has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case TO_FPRTN_AND_TOP_BLACKBOARD_EXTRACT_RTNO_PARSER:
#ifdef DISABLE_TO_FPRTN_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR
	disabled_error("To FPRTN & top blackboard extract parser has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	}

	switch (execution_state_set_impl_choice)
	{
	case STD:
#ifdef DISABLE_STD_SES
		disabled_error("STD execution state set implementation has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case LRB_TREE:
#ifdef DISABLE_LRB_TREE_SES
		disabled_error("LRB-TREE execution state set implementation has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case LRB_TREE_3W:
#ifdef DISABLE_LRB_TREE_3W_SES
		disabled_error("LRB-TREE-3W execution state set implementation has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	}

	switch (output_set_impl_choice)
	{
	case STD:
#ifdef DISABLE_STD_BS
		disabled_error("STD output set implementation has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case LRB_TREE:
#ifdef DISABLE_LRB_TREE_BS
		disabled_error("LRB-TREE output set implementation has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	case LRB_TREE_3W:
#ifdef DISABLE_LRB_TREE_3W_BS
		disabled_error("LRB-TREE-3W output set implementation has been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
		break;
	}

#ifdef DISABLE_TRIE_STRING_PARSERS
	if (trie_strings)
		disabled_error("Trie-string parsers have been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif

#ifdef DISABLE_ARRAY_PARSERS
	if (!trie_strings)
		disabled_error("Non-trie-string parsers have been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif

#ifdef DISABLE_PARSERS_WITHOUT_OUTPUT
	if (no_output)
		disabled_error("Parsers without output have been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif

#ifdef DISABLE_PARSERS_WITH_OUTPUT
	if (!no_output)
		disabled_error("Parsers with output have been disabled", grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
#endif
}

int main(int argc, char **argv)
{
	//setlocale is needed for correctly generating debug messages and .dot files containing unicode chars.
	//However, MTRACE reports some memory leaks when invoking setlocale.
	//We disable setlocale in order to get a clean "No memory leaks" message from mtrace.
#ifndef MTRACE
	setlocale(LC_CTYPE,"");
#endif
#ifdef TRACE
	std::wcout << std::boolalpha;
#endif
	//Retrieve program name from program path-name
	grapenlp::string program_name(argv[0]);
#ifdef WIN32
	std::size_t last_slash_pos(program_name.find_last_of('\\'));
#else
	std::size_t last_slash_pos(program_name.find_last_of('/'));
#endif
	if (last_slash_pos != grapenlp::string::npos)
		program_name = program_name.substr(last_slash_pos + 1, program_name.length());
	// Declare the possible command line arguments
	options_description desc("Options");
	desc.add_options()
		("help,h", "Display this information")
		("version", "Print version number")
		("desc-parser", "Print description of chosen parser")
		("anbn,a", value<unsigned int>(), "-an take as input the sequence a^n b^n")
		("corpus", "Input contains a set of sentences rather than a single one, an possibly other text to be omitted; each sentence must start and end by a '$' symbol (e.g.: [comment0]$sentence1$[comment1]$sentence2$[comment2]...")
		("letter,l", "Letter output grammar (default)")
		("extraction,x", "Extraction grammar")
		("bracketing,k", "Bracketing grammar")
	    ("weighted,w", "Weighted grammar")
	    ("merge,m", "Merge mode: consuming transitions that do not generate output (apart from a weight, for the case of weighted grammars) generate the input they consume")
	    ("repeat,r", value<std::string>(), (std::string("-r(xt|ys|xtys)[zr] Repeats the parsing stage...\n")+
											std::string("-rxt ...x times\n")+
											std::string("-rys ...the minimum amount of times so that it takes at least y seconds\n")+
											std::string("-rxtys ...no less than x times so that it takes a minimum of y seconds\n")+
											std::string("-r(xt|ys|xtys)zr ...as before, but re-repeat the parsing process z times and return the mean and standard deviation\n")).c_str())
	    ("stats,s", "Show stats")
	    ("fprtn-stats", "Compute also the FPRTN size (the average FPRTN size for the case of a corpus of sentences); do not use this option for measuring the algorithm execution times since they will be greater due to this additional computation")
		("parser,p", value<std::string>(), (std::string("Parser algorithm; valid arg values are:\n")+
										   std::string("depth-first\n")+
										   std::string("breadth-first\n")+
										   std::string("earley\n")+
										   std::string("to-fprtn (expansion omitted)\n")+
										   std::string("to-fprtn-and-breadth-first-expand (default)\n")+
										   std::string("to-fprtn-and-blackboard-set-expand and\n")+
										   std::string("to-fprtn-and-top-blackboard-extract\n")).c_str())
		("no-output,n", "Use an acceptor only version of the parsing algorithm (grammar output labels are ignored and returned output is either true or false); this option is not available for to-fprtn parsers")
		("trie-strings,t", (std::string("optimize the management of the parser's sequence-like structures with tries; this option is only available for the parsers whose execution states are composed by a stack of states and/or one or more output sequences, namely:\n")+
							std::string("depth-first with or without output sequences\n")+
							std::string("breadth-first with or without output sequences\n")+
							std::string("earley with output sequences, though performance may be decreased\n")+
							std::string("to-fprtn-and-breadth-first-expand with or without string-like output\n")+
							std::string("to-fprtn-and-blackboard-set-expand with string-like output\n")+
							std::string("to-fprtn-and-top-blackboard-extract with string-like output\n")).c_str())
		("ses-impl,e", value<std::string>(), (std::string("Set implementation to be used for the representation of sets of execution states; valid arg values are:\n")+
								   std::string("std (STL standard sets, usually backed by a red-black tree)\n")+
								   std::string("lrb-tree (custom sets backed by a double linked red-black tree)\n")+
								   std::string("lrb-tree-3w (as the precedent option, but using a 3-way element comparator instead of operator \"less than\")\n")+
								   std::string("")).c_str())
	    ("bs-impl,b", value<std::string>(), "Set implementation to be used for the representation of blackboard sets; valid arg values are the same than for the precedent option")
	    ("grammar,g", value<std::string>(), "Grammar file")
	    ("dico,d", value<std::string>(), "Text or compressed dictionary file; if dictionary is compressed, only the .bin or the .inf file must be specified (the other file will be searched in the same folder)")
	    ("input,i", value<std::string>(), "Input file containing the text to apply the grammar to")
		("context,c", value<std::string>(), "Input context file having a context mapping per line (e.g. key=value)")
	    ("output,o", value<std::string>(), "Output file; if no-output option is specified, the output will consist in a true/false value for each input sentence indicating whether the sentence was accepted or rejected")
	    ("validate,v", value<std::string>(), (std::string("Validation file; if none specified, output validation will be skipped; this option requires the input to be an aligned corpus formatted as follows: ")+
											 std::string("[comment_a1]$sentence1$[comment_b1]#expected_result1#[comment_a2]$sentence2[comment_b2]#expected_result2#...")).c_str())
	;

	//Declare which one of the arguments are positional (do not need a code indicating which
	//argument they correspond to but this information may be given by their position in the argument list)
	positional_options_description pod;
	pod.add("grammar", 1);
	pod.add("dico", 1);
	pod.add("input", 1);
	pod.add("context", 1);
	pod.add("output", 1);
	pod.add("validate", 1);

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
	if (argc == 1 || vm.count("help"))
	{
	    help(program_name, desc);
	    return 0;
	}

    if (vm.count("version"))
    {
        std::cout << "GRAPENLP_VERSION_MAJOR.GRAPENLP_VERSION_MINOR.GRAPENLP_VERSION_PATCH" << std::endl;
        return 0;
    }

    bool is_anbn(vm.count("anbn"));
	bool is_corpus(vm.count("corpus"));
	if (is_anbn && is_corpus)
		fatal_error("Corpus input and a^n b^n input are mutually exclusive\n");
	bool validate(vm.count("validate"));
	std::string validate_path_name;
	if (validate)
	{
		if (!is_corpus)
		fatal_error("Output validations is only available for (aligned) corpus input\n");
		validate_path_name = (vm["validate"].as<std::string>());
	}

	bool is_letter(vm.count("letter"));
#ifdef DISABLE_LETTER_OUTPUT_GRAMMARS
	if (is_letter)
		fatal_error("Letter grammars have been disabled\n");
#endif
	bool is_extraction(vm.count("extraction"));
#ifdef DISABLE_EXTRACTION_GRAMMARS
	if (is_extraction)
		fatal_error("Extraction grammars have been disabled\n");
#endif
	bool is_bracketing(vm.count("bracketing"));
#ifdef DISABLE_BRACKETING_GRAMMARS
	if (is_bracketing)
		fatal_error("Bracketing grammars have been disabled\n");
#endif
	bool is_weighted(vm.count("weighted"));
#ifdef DISABLE_WEIGHTED_GRAMMARS
	if (is_weighted)
		fatal_error("Weighted grammars have been disabled\n");
#elif defined(DISABLE_UNWEIGHTED_GRAMMARS)
	if (!is_weighted)
		fatal_error("Unweighted grammars have been disabled\n");
#endif
	bool show_stats(vm.count("stats"));

	if ((is_letter + is_extraction + is_bracketing) > 1)
		fatal_error("Choose either letter output grammar (-l), extraction grammar (-x) or bracketing grammar (-k)\n");

	bool merge_mode(vm.count("merge"));
	bool compute_fprtn_stats(vm.count("fprtn-stats"));

	std::size_t repeat_times(0);
	long double repeat_seconds(0.0);
	std::size_t rerepeats(0);
	if (vm.count("repeat"))
		parse_repeat_arguments(vm["repeat"].as<std::string>(), repeat_times, repeat_seconds, rerepeats);

	if (!vm.count("grammar"))
	{
		std::wcout << L"Unespecified grammar\n";
		help(program_name, desc);
		return 1;
	}
	if (!vm.count("dico"))
	{
		std::wcout << L"Unespecified dictionary\n";
		help(program_name, desc);
		return 1;
	}
	bool is_file_input(vm.count("input"));
	if (!is_anbn && !is_file_input)
	{
		std::wcout << L"Unespecified input\n";
		help(program_name, desc);
		return 1;
	}
	else if (is_anbn && is_file_input)
		fatal_error("File input and a^n b^n input are mutually exclusive\n");
	else if (is_anbn)
	if (!vm.count("output"))
	{
		std::wcout << L"Unespecified output\n";
		help(program_name, desc);
		return 1;
	}
	//Compute grammar type
	rtno_type grammar_type;

	if (is_extraction)
	{
		if (is_weighted)
		{
#ifdef DISABLE_LUXW_GRAMMAR
			fatal_error("Weigthed extraction grammars have been disabled\n");
#endif
			grammar_type = LEXMASK_X_WEIGHTED_EXTRACTION_RTNO;
		}
		else
		{
#ifdef DISABLE_LUX_GRAMMAR
			fatal_error("Unweighted extraction grammars have been disabled\n");
#endif
			grammar_type = LEXMASK_X_EXTRACTION_RTNO;
		}
	}
	else if (is_bracketing)
	{
		if (is_weighted)
		{
#ifdef DISABLE_LUXW_GRAMMAR
			fatal_error("Weigthed bracketing grammars have been disabled\n");
#endif
			grammar_type = LEXMASK_X_WEIGHTED_BRACKETING_RTNO;
		}
		else
		{
#ifdef DISABLE_LUX_GRAMMAR
			fatal_error("Unweighted bracketing grammars have been disabled\n");
#endif
			grammar_type = LEXMASK_X_BRACKETING_RTNO;
		}
	}
	else //is_letter, default choice
	{
		if (is_weighted)
		{
#ifdef DISABLE_LUAW_GRAMMAR
			fatal_error("Weighted letter grammars have been disabled\n");
#endif
			grammar_type = LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO;
		}
		else
		{
#ifdef DISABLE_LUA_GRAMMAR
			fatal_error("Unweighted letter grammars have been disabled\n");
#endif
			grammar_type = LEXMASK_X_LETTER_ARRAY_RTNO;
		}
	}

	//Compute parser type
	rtno_parser_type the_parser_type(DEFAULT_PARSER);
	if (vm.count("parser"))
		the_parser_type = compute_parser_type(vm["parser"].as<std::string>());

	assoc_container_impl_choice execution_state_set_impl_choice(DEFAULT_SES_IMPL);
	if (vm.count("ses-impl"))
		execution_state_set_impl_choice = compute_assoc_container_impl_choice(vm["ses-impl"].as<std::string>(), std::string("execution state"));

	assoc_container_impl_choice output_set_impl_choice(DEFAULT_BS_IMPL);
	if (the_parser_type == TO_FPRTN_AND_TOP_BLACKBOARD_EXTRACT_RTNO_PARSER && grammar_type == LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO)
		output_set_impl_choice = STD;
	else if (vm.count("bs-impl"))
		output_set_impl_choice = compute_assoc_container_impl_choice(vm["bs-impl"].as<std::string>(), std::string("blackboard"));

	bool trie_strings(vm.count("trie-strings"));
	bool no_output(vm.count("no-output"));

	if (no_output && (the_parser_type == TO_FPRTN_RTNO_PARSER || the_parser_type == TO_FPRTN_ZPPS_RTNO_PARSER || the_parser_type == TO_FPRTN_AND_BREADTH_FIRST_EXPAND_RTNO_PARSER || the_parser_type == TO_FPRTN_AND_BLACKBOARD_SET_EXPAND_RTNO_PARSER || the_parser_type == TO_FPRTN_AND_TOP_BLACKBOARD_EXTRACT_RTNO_PARSER))
		fatal_error("To FPRTN parsers require output generation; you may use an Earley parser without output instead\n");

	std::string grammar_path_name(vm["grammar"].as<std::string>());
	std::string dico_path_name(vm["dico"].as<std::string>());
	std::string output_path_name(vm["output"].as<std::string>());
	//Load/generate input
	u_array input;
	if (is_file_input)
	{
		std::string input_path_name(vm["input"].as<std::string>());
		input.reset(u_fread(input_path_name.c_str()));
	}
	else
	{
		unsigned int n(vm["anbn"].as<unsigned int>());
		input.reset(generate_anbn(n));
	}

	verify_requested_parser_is_not_disabled(grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);
	if (compute_fprtn_stats && !is_fprtn_based_parser(the_parser_type))
		std::wcout << L"The specified parser is not based on FPRTNs, so FPRTN sizes will not be computed\n";

	if (vm.count("desc-parser"))
	{
		std::string parser_desc(get_parser_desc(grammar_type, the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice));
		serialize_starbox(std::wcout, parser_desc.begin(), parser_desc.end(), std::wstring(WANSI_BRIGHT_CYAN_FG) + std::wstring(WANSI_BLACK_BG), std::wstring(WANSI_DEFAULT));
	}

	//Create parsing manager and load grammar and dico
	ualxiw_manager the_manager;
	the_manager.load_grammar_and_dico(grammar_type, grammar_path_name, dico_path_name);
	the_manager.set_parser(the_parser_type, trie_strings, no_output, execution_state_set_impl_choice, output_set_impl_choice);

	//Load input context
	u_context the_context(the_manager.get_context_key_value_hasher());
	if (vm.count("context"))
	{
		std::string input_context_path_name(vm["context"].as<std::string>());
#ifdef TRACE
		std::wcout << L"Loading input context" << std::endl;
#endif
		FILE *input_context_file(u_fopen(input_context_path_name.c_str(), U_READ));
		if (input_context_file == NULL)
			fatal_error("Unable to open input context file to read\n");
		u_read_context(input_context_file, the_context);
	}

	//Get parsing result
	u_array output;
	std::size_t sentence_char_count(0);
	std::size_t output_char_count(0);
	std::size_t token_count(0);
	std::size_t parse_count(0);
	std::size_t sentence_count(0);
	std::size_t invalid_sentence_count(0);
	FILE *f(u_fopen(output_path_name.c_str(), U_WRITE));
	FILE *validate_file(NULL);
	if (f == NULL)
		fatal_error("Unable to open file result.txt for writing\n");
	input_range_vector srv, rrv;
	stats<long double> seconds_per_sentence_stats(rerepeats);
	stats<long double> sentences_per_second_stats(rerepeats);
	std::size_t total_repeats(0);

	//Determine corpus sentence bounds and set sentence and sentence char counts
	if (is_corpus) //Input is a corpus of sentences
	{
		if (validate) //The corpus is aligned with the outputs that should be returned
		{
			get_aligned_sentence_bounds(input.begin(), input.end(), srv, sentence_char_count, rrv, output_char_count);
			validate_file = u_fopen(validate_path_name.c_str(), U_WRITE);
			if (!validate_file)
				fatal_error("Unable to open %s file\n", validate_path_name.c_str());
		}
		else get_sentence_bounds(input.begin(), input.end(), srv, sentence_char_count); //The corpus is not aligned, that is, it simply contains a set of input sentences
		sentence_count = srv.size();
	}
	//Input is a single sentence: set sentence and sentence char counts
	else
	{
		sentence_count = 1;
		sentence_char_count = input.size();
	}

	stats<long double> output_fprtn_state_stats(sentence_count);
	stats<long double> output_fprtn_transition_stats(sentence_count);
	stats<long double> pruned_output_fprtn_state_stats(sentence_count);
	stats<long double> pruned_output_fprtn_transition_stats(sentence_count);

	if (is_corpus) //Input is a corpus of sentences
	{
		input_range_vector::const_iterator sri(srv.begin());
		input_range_vector::const_iterator rri(rrv.begin());
		if (compute_fprtn_stats)
		{
			std::size_t output_fprtn_state_count;
			std::size_t output_fprtn_transition_count;
			std::size_t pruned_output_fprtn_state_count;
			std::size_t pruned_output_fprtn_transition_count;
			for (; sri != srv.end(); ++sri, ++rri) //for each sentence
			{
				u_fputc(sentence_bound_char, f);
				u_fwrite(sri->left, std::distance(sri->left, sri->right), f); //write the sentence
				u_fputc(sentence_bound_char, f);
				u_fputc('\n', f);
				std::pair<std::size_t, std::size_t> result(process_and_get_fprtn_stats(the_manager, the_parser_type, no_output, sri->left, sri->right, the_context, output_fprtn_state_count, output_fprtn_transition_count, pruned_output_fprtn_state_count, pruned_output_fprtn_transition_count));
				token_count += result.first;
				parse_count += result.second;
				output_fprtn_state_stats.add(output_fprtn_state_count);
				output_fprtn_transition_stats.add(output_fprtn_transition_count);
				pruned_output_fprtn_state_stats.add(pruned_output_fprtn_state_count);
				pruned_output_fprtn_transition_stats.add(pruned_output_fprtn_transition_count);
#ifdef SERIALIZED_OUTPUT
				u_fputc(output_bound_char, f);
				if (no_output || grammar_type == LEXMASK_X_EXTRACTION_RTNO || grammar_type == LEXMASK_X_WEIGHTED_EXTRACTION_RTNO) //write processing result
					u_fwrite(the_manager.get_output_u_array().begin(), the_manager.get_output_u_array().size(), f);
				else //write processing result
				{
					switch (the_manager.get_output_set_impl_choice())
					{
					case STD: u_write(f, the_manager.get_output_u_array_set<STD>().begin(), the_manager.get_output_u_array_set<STD>().end(), static_cast<unichar>('\n')); break;
					case LRB_TREE: u_write(f, the_manager.get_output_u_array_set<LRB_TREE>().begin(), the_manager.get_output_u_array_set<LRB_TREE>().end(), static_cast<unichar>('\n')); break;
					case LRB_TREE_3W: u_write(f, the_manager.get_output_u_array_set<LRB_TREE_3W>().begin(), the_manager.get_output_u_array_set<LRB_TREE_3W>().end(), static_cast<unichar>('\n')); break;
					}
				}
				u_fputc(output_bound_char, f);
				u_fprintf(f, "\n\n");
				if (validate && !grapenlp::equal(rri->left, rri->right, the_manager.get_output_u_array().begin(), the_manager.get_output_u_array().end())) //if unexpected result, write also the expected one
				{
					u_fputc(sentence_bound_char, validate_file);
					u_fwrite(sri->left, std::distance(sri->left, sri->right), validate_file);
					u_fputc(sentence_bound_char, validate_file);
					u_fputc('\n', validate_file);

					u_fputc(output_bound_char, validate_file);
					u_fwrite(rri->left, std::distance(rri->left, rri->right), validate_file);
					u_fputc(output_bound_char, validate_file);
					u_fputc('\n', validate_file);

					u_fputc(output_bound_char, validate_file);
					u_fwrite(the_manager.get_output_u_array().begin(), the_manager.get_output_u_array().size(), validate_file);
					u_fputc(output_bound_char, validate_file);
					u_fprintf(validate_file, "\n\n");

					++invalid_sentence_count;
				}
#endif
			}
			output_fprtn_state_stats.compute_stats();
			output_fprtn_transition_stats.compute_stats();
			pruned_output_fprtn_state_stats.compute_stats();
			pruned_output_fprtn_transition_stats.compute_stats();
		}
		else
		{
			for (; sri != srv.end(); ++sri, ++rri) //for each sentence
			{
				u_fputc(sentence_bound_char, f);
				u_fwrite(sri->left, std::distance(sri->left, sri->right), f); //write the sentence
				u_fputc(sentence_bound_char, f);
				u_fputc('\n', f);
				std::pair<std::size_t, std::size_t> result(process(the_manager, the_parser_type, no_output, sri->left, sri->right, the_context));
				token_count += result.first;
				parse_count += result.second;
#ifdef SERIALIZED_OUTPUT
				u_fputc(output_bound_char, f);
				if (no_output || grammar_type == LEXMASK_X_EXTRACTION_RTNO || grammar_type == LEXMASK_X_WEIGHTED_EXTRACTION_RTNO) //write processing result
					u_fwrite(the_manager.get_output_u_array().begin(), the_manager.get_output_u_array().size(), f);
				else //write processing result
				{
					switch (the_manager.get_output_set_impl_choice())
					{
					case STD: u_write(f, the_manager.get_output_u_array_set<STD>().begin(), the_manager.get_output_u_array_set<STD>().end(), static_cast<unichar>('\n')); break;
					case LRB_TREE: u_write(f, the_manager.get_output_u_array_set<LRB_TREE>().begin(), the_manager.get_output_u_array_set<LRB_TREE>().end(), static_cast<unichar>('\n')); break;
					case LRB_TREE_3W: u_write(f, the_manager.get_output_u_array_set<LRB_TREE_3W>().begin(), the_manager.get_output_u_array_set<LRB_TREE_3W>().end(), static_cast<unichar>('\n')); break;
					}
				}
				u_fputc(output_bound_char, f);
				u_fprintf(f, "\n\n");
				if (validate && !grapenlp::equal(rri->left, rri->right, the_manager.get_output_u_array().begin(), the_manager.get_output_u_array().end())) //if unexpected result, write also the expected one
				{
					u_fputc(sentence_bound_char, validate_file);
					u_fwrite(sri->left, std::distance(sri->left, sri->right), validate_file);
					u_fputc(sentence_bound_char, validate_file);
					u_fputc('\n', validate_file);

					u_fputc(output_bound_char, validate_file);
					u_fwrite(rri->left, std::distance(rri->left, rri->right), validate_file);
					u_fputc(output_bound_char, validate_file);
					u_fputc('\n', validate_file);

					u_fputc(output_bound_char, validate_file);
					u_fwrite(the_manager.get_output_u_array().begin(), the_manager.get_output_u_array().size(), validate_file);
					u_fputc(output_bound_char, validate_file);
					u_fprintf(validate_file, "\n\n");

					++invalid_sentence_count;
				}
#endif
			}
		}
		if (validate) //Warn about unexpected results
		{
			u_fclose(validate_file);
			if (invalid_sentence_count)
			{
				std::wcout << WANSI_BRIGHT_RED_FG << "*** Warning ***\n";
				std::wcout << L"Unexpected results obtained for " << invalid_sentence_count << " sentences of " << sentence_count << std::endl;
				std::wcout << L"Invalid sentences written in file " << validate_path_name.c_str() << WANSI_DEFAULT << std::endl;
			}
			else std::wcout << WANSI_BRIGHT_GREEN_FG << "Validation 100% O.K." << WANSI_DEFAULT << std::endl;
		}
	}
	else //The input is just a single sentence
	{
		if (compute_fprtn_stats)
		{
			std::size_t output_fprtn_state_count;
			std::size_t output_fprtn_transition_count;
			std::size_t pruned_output_fprtn_state_count;
			std::size_t pruned_output_fprtn_transition_count;
			std::pair<std::size_t, std::size_t> result(process_and_get_fprtn_stats(the_manager, the_parser_type, no_output, input.begin(), input.end(), the_context, output_fprtn_state_count, output_fprtn_transition_count, pruned_output_fprtn_state_count, pruned_output_fprtn_transition_count));
			token_count += result.first;
			parse_count += result.second;
			output_fprtn_state_stats.add(output_fprtn_state_count);
			output_fprtn_transition_stats.add(output_fprtn_transition_count);
			pruned_output_fprtn_state_stats.add(pruned_output_fprtn_state_count);
			pruned_output_fprtn_transition_stats.add(pruned_output_fprtn_transition_count);
			output_fprtn_state_stats.compute_stats();
			output_fprtn_transition_stats.compute_stats();
			pruned_output_fprtn_state_stats.compute_stats();
			pruned_output_fprtn_transition_stats.compute_stats();
		}
		else
		{
			std::pair<std::size_t, std::size_t> result(process(the_manager, the_parser_type, no_output, input.begin(), input.end(), the_context));
			token_count += result.first;
			parse_count += result.second;
		}
#ifdef SERIALIZED_OUTPUT
		if (no_output || grammar_type == LEXMASK_X_EXTRACTION_RTNO || grammar_type == LEXMASK_X_WEIGHTED_EXTRACTION_RTNO)
			u_fwrite(the_manager.get_output_u_array().begin(), std::distance(the_manager.get_output_u_array().begin(), the_manager.get_output_u_array().end()), f);
		else
		{
			switch (the_manager.get_output_set_impl_choice())
			{
			case STD: u_write(f, the_manager.get_output_u_array_set<STD>().begin(), the_manager.get_output_u_array_set<STD>().end(), static_cast<unichar>('\n')); break;
			case LRB_TREE: u_write(f, the_manager.get_output_u_array_set<LRB_TREE>().begin(), the_manager.get_output_u_array_set<LRB_TREE>().end(), static_cast<unichar>('\n')); break;
			case LRB_TREE_3W: u_write(f, the_manager.get_output_u_array_set<LRB_TREE_3W>().begin(), the_manager.get_output_u_array_set<LRB_TREE_3W>().end(), static_cast<unichar>('\n')); break;
			}
		}
#endif
	}
	u_fclose(f);

	if (rerepeats > 0)
	{
		if (is_corpus)
		{
			for (std::size_t rr(0); rr < rerepeats; ++rr)
			{
				std::pair<long double, std::size_t> total_elapsed_x_repeats(process_corpus_for_stats(the_manager, the_parser_type, no_output, srv.begin(), srv.end(), the_context, repeat_times, repeat_seconds));
				total_repeats += total_elapsed_x_repeats.second;
				long double average_corpus_processing_time(total_elapsed_x_repeats.first / total_elapsed_x_repeats.second);
				seconds_per_sentence_stats.add(average_corpus_processing_time / static_cast<long double>(sentence_count));
				sentences_per_second_stats.add(static_cast<long double>(sentence_count) / average_corpus_processing_time);
			}
		}
		else
		{
			for (std::size_t rr(0); rr < rerepeats; ++rr)
			{
				std::pair<long double, std::size_t> total_elapsed_x_repeats(process_sentence_for_stats(the_manager, the_parser_type, no_output, input.begin(), input.end(), the_context, repeat_times, repeat_seconds));
				total_repeats = total_elapsed_x_repeats.second;
				seconds_per_sentence_stats.add(total_elapsed_x_repeats.first / total_elapsed_x_repeats.second);
				sentences_per_second_stats.add(total_elapsed_x_repeats.second / total_elapsed_x_repeats.first);
			}
		}
		seconds_per_sentence_stats.compute_stats();
		sentences_per_second_stats.compute_stats();
	}

	if (show_stats)
	{
		std::size_t total_chars(sentence_char_count * total_repeats);
		std::size_t total_tokens(token_count * total_repeats);
		std::size_t total_sentences(sentence_count * total_repeats);
		std::size_t total_parses(parse_count * total_repeats);
		std::wcout.precision(12);
		std::wcout << L"Grammar states: " << the_manager.grammar_state_count() << std::endl;
		std::wcout << L"Grammar transitions: " << the_manager.grammar_transition_count() << std::endl;
		if (compute_fprtn_stats)
		{
			long double state_reduction_ratio(100.0L * pruned_output_fprtn_state_stats.mean() / output_fprtn_state_stats.mean());
			long double transition_reduction_ratio(100.0L * pruned_output_fprtn_transition_stats.mean() / output_fprtn_transition_stats.mean());
			if (is_corpus)
			{
				std::wcout << L"Average FPRTN states " << output_fprtn_state_stats << std::endl;
				std::wcout << L"Average pruned FPRTN states " << pruned_output_fprtn_state_stats << std::endl;
				std::wcout << L"Average FPRTN transitions " << output_fprtn_transition_stats << std::endl;
				std::wcout << L"Average pruned FPRTN transitions " << pruned_output_fprtn_transition_stats << std::endl;
				std::wcout << L"Reduction ratio (states, transitions): (" << state_reduction_ratio << ", " << transition_reduction_ratio << ")\n";
			}
			else
			{
				std::wcout << L"FPRTN states (before pruning, after pruning, reduction ratio): " << output_fprtn_state_stats.mean() << ", " << pruned_output_fprtn_state_stats.mean() << ", " << state_reduction_ratio << std::endl;
				std::wcout << L"FPRTN transitions (before pruning, after pruning, reduction ratio): " << output_fprtn_transition_stats.mean() << ", " << pruned_output_fprtn_transition_stats.mean() << ", " << transition_reduction_ratio << std::endl;
			}
		}
		std::wcout << L"Input chars: " << sentence_char_count << std::endl;
		std::wcout << L"Input tokens: " << token_count << std::endl;
		std::wcout << L"Input sentences: " << sentence_count << std::endl;
		std::wcout << L"Input parses: " << parse_count << std::endl;
		if (token_count)
			std::wcout << L"Average chars per token: " << static_cast<long double>(sentence_char_count) / static_cast<long double>(token_count) << std::endl;
		if (is_corpus && sentence_count)
		{
			std::wcout << L"Average tokens per sentence: " << static_cast<long double>(token_count) / static_cast<long double>(sentence_count) << std::endl;
			std::wcout << L"Average chars per sentence: " << static_cast<long double>(sentence_char_count) / static_cast<long double>(sentence_count) << std::endl;
			std::wcout << L"Average parses per sentence: " << static_cast<long double>(parse_count) / static_cast<long double>(sentence_count) << std::endl;
		}
		if (rerepeats > 0)
		{
			std::wcout << L"Total chars (x" << total_repeats << "): " << total_chars << std::endl;
			std::wcout << L"Total tokens (x" << total_repeats << "): " << total_tokens << std::endl;
			std::wcout << L"Total sentences (x" << total_repeats << "): " << total_sentences << std::endl;
			if (the_parser_type == TO_FPRTN_RTNO_PARSER || the_parser_type == TO_FPRTN_ZPPS_RTNO_PARSER)
				std::wcout << L"Total parses: not computed for this parsing algorithm" << std::endl;
			else std::wcout << L"Total parses (x" << total_repeats << "): " << total_parses << std::endl;
			std::wcout << L"Total elapsed seconds: " << global_timer.elapsed() << std::endl;
		}
		if (sentence_count && rerepeats)
		{
			std::wcout << L"Average seconds per sentence: " << seconds_per_sentence_stats.mean() << std::endl;
			std::wcout << L"SD, CV%, P%, min, max: " << seconds_per_sentence_stats.std_dev() << ", " << seconds_per_sentence_stats.cv() << ", " << seconds_per_sentence_stats.p() << ", " << seconds_per_sentence_stats.min() << ", " << seconds_per_sentence_stats.max() << std::endl;
			std::wcout << L"Average sentences per second:" << WANSI_BRIGHT_RED_FG << WANSI_BLACK_BG << ' ' << sentences_per_second_stats.mean() << WANSI_DEFAULT << std::endl;
			std::wcout << L"SD, CV%, P%, min, max: " << sentences_per_second_stats.std_dev() << ", " << sentences_per_second_stats.cv() << ", " << sentences_per_second_stats.p() << ", " << sentences_per_second_stats.min() << ", " << sentences_per_second_stats.max() << std::endl;
		}
	}
	return 0;
}
