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

#ifndef GRAPENLP_UL_FST2_READER_H
#define GRAPENLP_UL_FST2_READER_H

#include <algorithm>

#include <grapenlp/vector.h>
#include <grapenlp/u_text_dico_word_meta_mask_factory.h>
#include <grapenlp/u_compressed_dico_word_meta_mask_factory.h>
#include <grapenlp/ul_tag_input_factory.h>
#include <grapenlp/tag_reader_traits.h>
#include <grapenlp/u_context_mask.h>
#include <grapenlp/u_fst2_constants.h>
#include <grapenlp/l_rtno.h>

namespace grapenlp
{
	template<typename InputIterator, typename TagOutputReader, typename CaseNormalizer=u_tolower>
	struct ul_fst2_reader
	{
		struct transition_indexes
		{
			int label_index;
			int target_index;

			transition_indexes(int label_index_, int target_index_): label_index(label_index_), target_index(target_index_)
			{}
		};

		typedef std::vector<transition_indexes> transition_indexes_vector;
		typedef transition_indexes_vector* transition_indexes_vector_ref;

		typedef TagOutputReader tag_output_reader;
		typedef typename tag_reader_traits<TagOutputReader>::tag tag_output;
#ifdef TRACE
		typedef lns_rtno<InputIterator, tag_output, u_context_mask> machine;
#else
		typedef l_rtno<InputIterator, tag_output, u_context_mask> machine;
#endif
		typedef typename machine::state state;
		typedef typename state::ref state_ref;
		typedef typename state::const_ref state_const_ref;
		typedef array<state_ref> state_ref_array;

		struct ul_state_ref_x_transition_indexes_vector_ref
		{
			state_ref q_ref;
			transition_indexes_vector_ref tv_ref;

			ul_state_ref_x_transition_indexes_vector_ref(state_ref q_ref_, transition_indexes_vector_ref tv_ref_): q_ref(q_ref_), tv_ref(tv_ref_)
			{}
		};

		struct ul_state_ref_x_transition_indexes_vector_ref_vector: public std::vector<ul_state_ref_x_transition_indexes_vector_ref>
		{
			typedef std::vector<ul_state_ref_x_transition_indexes_vector_ref> base_type;

			ul_state_ref_x_transition_indexes_vector_ref_vector(): base_type()
			{}

			~ul_state_ref_x_transition_indexes_vector_ref_vector()
			{
				typename ul_state_ref_x_transition_indexes_vector_ref_vector::iterator i;
				for (i = this->begin(); i != this->end(); ++i)
					delete i->tv_ref;
			}
		};

		typedef ul_tag_input<InputIterator>* tag_input;

		struct tag
		{
			tag_input input;
			tag_output output;
			bool has_non_default_output;

			tag(tag_input input_): input(input_), output(), has_non_default_output(false)
			{}

			tag(tag_input input_, tag_output output_): input(input_), output(output_), has_non_default_output(true)
			{}
		};

		typedef ptr_vector<tag> tag_ref_vector;

		ul_fst2_reader()
		{}

	public:
		int operator() (FILE *f, machine &grammar, ul_tag_input_trie<unichar, InputIterator> &ult, tag_output_reader &tor, u_text_delaf<CaseNormalizer> &dico, u_context &ctx)
		{
			u_text_dico_word_meta_mask_factory<InputIterator, CaseNormalizer> dico_lexmask_factory(dico);
			return operator() (f, grammar, ult, tor, dico_lexmask_factory, ctx);
		}

		int operator() (FILE *f, machine &grammar, ul_tag_input_trie<unichar, InputIterator> &ult, tag_output_reader &tor, compressed_delaf &dico, u_context &ctx)
		{
			u_compressed_dico_word_meta_mask_factory<InputIterator, CaseNormalizer> dico_lexmask_factory(dico);
			return operator() (f, grammar, ult, tor, dico_lexmask_factory, ctx);
		}
	private:
		int operator() (FILE *f, machine &grammar, ul_tag_input_trie<unichar, InputIterator> &ult, tag_output_reader &tor, u_dico_word_meta_mask_factory<InputIterator> &dico_lexmask_factory, u_context &ctx)
		{
			if (!f) return 0;
			int graph_count;
			u_fscanf(f,"%d\n", &graph_count);
			if (graph_count == 0)
				return 1;

			int max_tag_index;
			unsigned int line_count = 2;
			//Array storing the initial state of each graph
			state_ref_array called_states(graph_count);
			//Vector storing pairs state/outgoing transitions,
			//where the second one are stored as a vector of pairs tag-or-called-state-index/target state
			ul_state_ref_x_transition_indexes_vector_ref_vector stv;
			//Reserve memory for at least the initial states of each graph
			stv.reserve(graph_count);

			//Load states and their transitions and create the corresponding RTNO states (no transitions added yet)
	#ifdef TRACE
			std::wcout << L"Reading states starting from line " << line_count << " of .fst2 file\n";
	#endif
			u_read_states(f, grammar, called_states, stv, max_tag_index, line_count);

			//Vector storing the input/output pairs
			//The size is the maximum tag index plus 1 since we start counting from 0
			tag_ref_vector trv;
			trv.reserve(max_tag_index + 1);

	#ifdef TRACE
			std::wcout << L"Reading tags starting from line " << line_count << " of .fst2 file\n";
	#endif
			u_read_tags(f, trv, ult, tor, dico_lexmask_factory, ctx, line_count);

	#ifdef TRACE
			std::wcout << L"Adding transitions\n";
	#endif
			add_transitions(called_states, stv, trv);
			return 0;
		}

		void u_read_states(FILE *f, machine &grammar, state_ref_array &called_states, ul_state_ref_x_transition_indexes_vector_ref_vector &stv, int &max_tag_index, unsigned int &line_count)
		{
			unichar called_state_name[10000];
			std::size_t i = 0;
			std::size_t state_index_offset = 0;
			std::size_t local_state_index = 0;
			max_tag_index = 0;

			//Read first graph digit and space after it
			int current_graph_index;
			u_fscanf(f,"%d ",&current_graph_index);
			current_graph_index = -1 - current_graph_index;
			//Read first graph name
			u_fgets(called_state_name, f);
			line_count++;

			//Read RTNO initial state, that is, the first state of the first graph
			if (!u_read_state(f, grammar, stv, 0, 0, max_tag_index, line_count))
				fatal_error("In line %u of .fst2 file: graph %d defines no states\n", line_count, 1 - current_graph_index);
			called_states[current_graph_index] = stv[0].q_ref;
			++local_state_index;

			//Read the other states of the first graph
			while (u_read_state(f, grammar, stv, current_graph_index, state_index_offset, max_tag_index, line_count))
				++local_state_index;

			// Read the states of the other graphs
			for (++i, state_index_offset += local_state_index, local_state_index = 0; i < called_states.size(); ++i, state_index_offset += local_state_index, local_state_index = 0)
			{
				//Read graph digit and space after it
				u_fscanf(f,"%d ",&current_graph_index);
				current_graph_index = -1 - current_graph_index;
				//Read graph name
				u_fgets(called_state_name, f);
				line_count++;

				//Read initial state of the current graph
				if (!u_read_state(f, grammar, stv, current_graph_index, state_index_offset, max_tag_index, line_count))
					fatal_error("In line %u of .fst2 file: graph %d defines no states\n", line_count, 1 - current_graph_index);
				called_states[current_graph_index] = stv.back().q_ref;
				++local_state_index;

				//Read other states
				while (u_read_state(f, grammar, stv, current_graph_index, state_index_offset, max_tag_index, line_count))
					++local_state_index;
			}
		}

		bool u_read_state(FILE *f, machine &grammar, ul_state_ref_x_transition_indexes_vector_ref_vector &stv, int current_graph_index, int state_index_offset, int &max_tag_index, unsigned int &line_count)
		{
			unichar c = (unichar)u_fgetc(f);
			if (c != end_of_section_char && c != final_state_char && c != non_final_state_char)
				fatal_error("In line %u of .fst2 file: unexpected character '%c' (expected 'f', 't' or ':')\n", line_count, c);
			unichar c2 = (unichar)u_fgetc(f);
			//Skip mandatory space after 'f', 't' or ':'
			if (c2 != ' ')
				fatal_error("In line %u of .fst2 file: Unexpected character '%c' after character '%c' (expected ' ')\n", line_count, c2, c);
			if (c == end_of_section_char)
			{
				//Skip mandatory EOL after 'f'
				c = (unichar)u_fgetc(f);
				if (c != U_ENDL)
					fatal_error("In line %u of .fst2 file: unexpected character '%c' after 'f' (expected EOL)\n", line_count, c);
				line_count++;
				return false;
			}

			state_ref s = grammar.create_state(c == final_state_char);
			stv.push_back(ul_state_ref_x_transition_indexes_vector_ref(s, new transition_indexes_vector()));
	//		u_printf("Added state %d ", stv.size() - 1); std::wcout << stv.back().first->wlabel() << std::endl;
			bool eol;
			int global_target_state_index, local_target_state_index;
			int tag_or_graph_index = u_read_int_or_eol(f, eol, line_count);
			while (!eol)
			{
				//Since graph indexes are negative they will always be less than the current max tag index
				max_tag_index = std::max(max_tag_index, tag_or_graph_index);

				local_target_state_index = u_read_int_or_eol(f, eol, line_count);
				if (eol)
					fatal_error("In line %u of .fst2 file: missing state digit in transition (graph %d, state %d)\n", line_count, 1 - current_graph_index, local_target_state_index);
				global_target_state_index = state_index_offset + local_target_state_index;
				//Add outgoing transition for the current state
				stv.back().tv_ref->push_back(transition_indexes(tag_or_graph_index, global_target_state_index));
	//			u_printf("Add transition "); std::wcout << stv.back().first->wlabel(); u_printf(" -> q%d with tag %d\n", global_target_state_index, tag_or_graph_index);
				tag_or_graph_index = u_read_int_or_eol(f, eol, line_count);
			}
			line_count++;
			return true;
		}

		void u_read_tags(FILE *f, tag_ref_vector &trv, ul_tag_input_trie<unichar, InputIterator> &ult, tag_output_reader &tor, u_dico_word_meta_mask_factory<InputIterator> &dico_lexmask_factory, u_context &ctx, unsigned int &line_count)
		{
			tag* t_ref(u_read_tag(f, ult, tor, dico_lexmask_factory, ctx, line_count));
			while (t_ref)
			{
				trv.push_back(t_ref);
				t_ref = u_read_tag(f, ult, tor, dico_lexmask_factory, ctx, line_count);
			}
		}

		tag* u_read_tag(FILE *f, ul_tag_input_trie<unichar, InputIterator> &ult, tag_output_reader &tor, u_dico_word_meta_mask_factory<InputIterator> &dico_lexmask_factory, u_context &ctx, unsigned int &line_count)
		{
			unichar c = u_fgetc(f);
			if (c == end_of_section_char)
			{
	#ifdef TRACE
				std::wcout << L"End of tags\n";
	#endif
				return NULL;
			}
			if (!(c == case_insensitive_char || c == case_sensitive_char))
				fatal_error("In line %u of .fst2 file: unexpected character '%c' in place of tag header ('%c' or '%c')\n", line_count, c, case_insensitive_char, case_sensitive_char);

			typename ul_tag_input_trie<unichar, InputIterator>::string::ref uls = &(ult.epsilon() + c);

			//Read tag input
			if ((c = (unichar)u_fgetc(f)) == U_ENDL)
				fatal_error("In line %u of .fst2 file: empty tag\n", line_count);
	#ifdef TRACE
			std::wcout << L"Input: '";
	#endif
			do
			{
				uls = &(*uls + c);
	#ifdef TRACE
				std::wcout << c;
	#endif
			} while ((c = (unichar)u_fgetc(f)) != in_out_separator_char && c != U_ENDL);
	#ifdef TRACE
			std::wcout << '\'' << std::endl;
	#endif

			//Retrieve lexical mask, if already created, or create a new one corresponding to this lexical mask code
			if (!uls->data)
				uls->data = make_ul_tag_input<InputIterator, CaseNormalizer>(*uls, dico_lexmask_factory, ctx);

			tag *t_ref;
			//Load tag output, if defined, then build tag
			if (c == in_out_separator_char)
			{
#ifdef TRACE
				std::wcout << L"Output: '";
#endif
				c = u_fgetc(f);
				t_ref = new tag(uls->data, tor(f, c, line_count));
				if (c != U_ENDL)
					fatal_error("In line %u of .fst2 file: expected EOL after tag output but got '%c'\n", line_count, c);
#ifdef TRACE
				std::wcout << '\'' << std::endl;
#endif
			}
			//If not defined, build tag with empty tag output
			else
			{
#ifdef TRACE
				std::wcout << L"Output: none" << std::endl;
#endif
				t_ref = new tag(uls->data);
			}
			line_count++;
			return t_ref;
		}

		int u_read_int_or_eol(FILE *f, bool &eol, unsigned int &line_count)
		{
			unichar c;
			//Skip spaces
			do c=(unichar)u_fgetc(f); while (c==' ');
			//Next char must be a digit, a minus or an EOL
			if (!(u_is_digit(c) || c == '-' || u_is_eol(c)))
				fatal_error("In line %u of .fst2 file: unexpected char '%c' (expected digit)\n", line_count, c);

			//EOL
			if (u_is_eol(c))
			{
				eol = true;
				return 0;
			}

			eol = false;
			int sign;

			//Minus
			if (c=='-')
			{
				sign = -1;
				c=(unichar)u_fgetc(f);
				if (!u_is_digit(c))
					fatal_error("Unexpected character in fst2 (read int 2): '%c'\n", c);
			}
			else sign = 1;

			//Read absolute value
			int value = c - '0';
			while(u_is_digit(c = u_fgetc(f)))
				value = value * 10 + (c - '0');

			//Set sign
			value *= sign;
			return value;
		}

		void add_transitions(state_ref_array &called_states, ul_state_ref_x_transition_indexes_vector_ref_vector &stv, tag_ref_vector &trv)
		{
			typename ul_state_ref_x_transition_indexes_vector_ref_vector::iterator i;
			typename transition_indexes_vector::iterator j;

			//For each state
			for (i = stv.begin(); i != stv.end(); ++i)
			{
#ifdef TRACE
				std::wcout << L"Adding outgoing transitions from state " << static_cast<state_const_ref>(i->q_ref)->wlabel(L'q') << std::endl;
#endif
				//And for each outgoing transition
				for (j = i->tv_ref->begin(); j != i->tv_ref->end(); ++j)
				{
#ifdef TRACE
					std::wcout << "-> " << static_cast<state_const_ref>(stv[j->target_index].q_ref)->wlabel(L'q') << " with label " << j->label_index << std::endl;
#endif
					//Add call-transition (negative tag index corresponds to a called state)
					if (j->label_index < 0)
						i->q_ref->add_call_transition(called_states[-1 - j->label_index], stv[j->target_index].q_ref);
					else
					{
						//Add epsilon transition (tag input lexical mask is NULL)
						switch (trv[j->label_index]->input->type)
						{
							case CONSUMING:
								//There is a defined output
								if (trv[j->label_index]->has_non_default_output)
									i->q_ref->add_translating_transition(trv[j->label_index]->input->lexmask_ref, trv[j->label_index]->output, stv[j->target_index].q_ref);
								//Else output is empty
								else
									i->q_ref->add_deleting_transition(trv[j->label_index]->input->lexmask_ref, stv[j->target_index].q_ref);
								break;
							case EPSILON:
								if (trv[j->label_index]->has_non_default_output)
									i->q_ref->add_inserting_transition(trv[j->label_index]->output, stv[j->target_index].q_ref);
								else
									i->q_ref->add_epsilon_transition(stv[j->target_index].q_ref);
	 							break;
                            case CONTEXT:
                                if (trv[j->label_index]->has_non_default_output)
                                    i->q_ref->add_inserting_context_transition(*trv[j->label_index]->input->context_mask_ref, trv[j->label_index]->output, stv[j->target_index].q_ref);
                                else
                                    i->q_ref->add_epsilon_context_transition(*trv[j->label_index]->input->context_mask_ref, stv[j->target_index].q_ref);
                                break;
							case NO_BLANK_EPSILON:
								if (trv[j->label_index]->has_non_default_output)
									i->q_ref->add_no_blank_inserting_transition(trv[j->label_index]->output, stv[j->target_index].q_ref);
								else
									i->q_ref->add_no_blank_epsilon_transition(stv[j->target_index].q_ref);
	 							break;
							case BLANK_EPSILON:
								if (trv[j->label_index]->has_non_default_output)
									i->q_ref->add_blank_inserting_transition(trv[j->label_index]->output, stv[j->target_index].q_ref);
								else
									i->q_ref->add_blank_epsilon_transition(stv[j->target_index].q_ref);
	 							break;
							default: fatal_error("Trying to create transition with invalid coarse lexmask type\n");
						}
					}
				}
			}
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_UL_FST2_READER*/
