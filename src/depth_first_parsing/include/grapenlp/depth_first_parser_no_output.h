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

#ifndef GRAPENLP_DEPTH_FIRST_PARSER_NO_OUTPUT_H
#define GRAPENLP_DEPTH_FIRST_PARSER_NO_OUTPUT_H

#ifdef TRACE
#include <iostream>
#include <fstream>
#include <grapenlp/tag_serializer_traits.h>
#endif

#include <memory>

#include <grapenlp/sequence_impl_choice.h>
#include <grapenlp/tag_input_traits.h>
#include <grapenlp/context.h>
#include <grapenlp/pool.h>
#include <grapenlp/rtno.h>

namespace grapenlp
{
	template<typename TagInput, typename TagOutput, typename SourceRef, typename ContextKey, typename ContextValue, typename StateConstRefStackPool>
	struct depth_first_parser_no_output
	{
		typedef TagInput tag_input;
		typedef TagOutput tag_output;
		typedef SourceRef source_ref;
		typedef typename source_ref::value_type input;
		typedef ContextKey context_key;
		typedef ContextValue context_value;
		typedef context<context_key, context_value> context_type;
		typedef typename context_type::optimized_key optimized_context_key;
		typedef typename context_type::optimized_value optimized_context_value;

#ifdef TRACE
		typedef ns_rtno<tag_input, tag_output, typename context<ContextKey, ContextValue>::optimized_context_key, typename context<ContextKey, ContextValue>::optimized_context_value> machine;
		typedef typename tag_serializer<input>::type input_serializer;
		typedef typename tag_serializer<tag_input>::type tag_input_serializer;
		typedef typename tag_serializer<tag_output>::type tag_output_serializer;
#else
		typedef rtno<tag_input, tag_output, typename context<ContextKey, ContextValue>::optimized_context_key, typename context<ContextKey, ContextValue>::optimized_context_value> machine;
#endif
		typedef typename tag_input_traits<tag_input>::match match;
		typedef typename machine::state state;
		typedef typename machine::state_const_ref state_const_ref;
		typedef typename machine::state_ref_list_const_iterator state_ref_list_const_iterator;

		typedef	typename machine::outgoing_epsilon_transition outgoing_epsilon_transition;
		typedef	typename machine::outgoing_epsilon_transition_set outgoing_epsilon_transition_set;
		typedef typename outgoing_epsilon_transition_set::const_iterator outgoing_epsilon_transition_set_const_iterator;

        typedef	typename machine::outgoing_epsilon_context_transition outgoing_epsilon_context_transition;
        typedef	typename machine::outgoing_epsilon_context_transition_set outgoing_epsilon_context_transition_set;
        typedef typename outgoing_epsilon_context_transition_set::const_iterator outgoing_epsilon_context_transition_set_const_iterator;

		typedef	typename machine::outgoing_deleting_transition outgoing_deleting_transition;
		typedef	typename machine::outgoing_deleting_transition_set outgoing_deleting_transition_set;
		typedef typename outgoing_deleting_transition_set::const_iterator outgoing_deleting_transition_set_const_iterator;

		typedef	typename machine::outgoing_translating_transition outgoing_translating_transition;
		typedef	typename machine::outgoing_translating_transition_set outgoing_translating_transition_set;
		typedef typename outgoing_translating_transition_set::const_iterator outgoing_translating_transition_set_const_iterator;

		typedef	typename machine::outgoing_inserting_transition outgoing_inserting_transition;
		typedef	typename machine::outgoing_inserting_transition_set outgoing_inserting_transition_set;
		typedef typename outgoing_inserting_transition_set::const_iterator outgoing_inserting_transition_set_const_iterator;

        typedef	typename machine::outgoing_inserting_context_transition outgoing_inserting_context_transition;
        typedef	typename machine::outgoing_inserting_context_transition_set outgoing_inserting_context_transition_set;
        typedef typename outgoing_inserting_context_transition_set::const_iterator outgoing_inserting_context_transition_set_const_iterator;

		typedef	typename machine::outgoing_call_transition outgoing_call_transition;
		typedef	typename machine::outgoing_call_transition_set outgoing_call_transition_set;
		typedef typename outgoing_call_transition_set::const_iterator outgoing_call_transition_set_const_iterator;

		typedef StateConstRefStackPool state_const_ref_stack_pool;
		typedef typename pool_traits<state_const_ref_stack_pool>::value_type state_const_ref_stack;
		typedef typename pool_traits<state_const_ref_stack_pool>::iterator state_const_ref_stack_iterator;
		typedef typename pool_traits<state_const_ref_stack_pool>::const_iterator state_const_ref_stack_const_iterator;

		//(q, pi) in (Q X Q*)
		//We do not implement here a field q_c but a method get_q_c(). Derived classes must implement this function
		struct execution_state
		{
			state_const_ref q;
			state_const_ref_stack pi;
			source_ref in;
#ifdef TRACE
			std::size_t i;
#endif

			execution_state(state_const_ref q_,
							state_const_ref_stack pi_,
							source_ref in_
#ifdef TRACE
							, std::size_t i_
#endif
			): q(q_), pi(pi_), in(in_)
#ifdef TRACE
							, i(i_)
#endif
			{}

#ifdef TRACE
			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
			{
				out << '(';
				if (q)
					q->serialize(out, static_cast<CharT>('q'));
				else out << "void_state";
				out << ", ";
				if (pi.empty())
					out << "lambda";
				else
				{
					for (state_const_ref_stack_const_iterator j(pi.begin()); j != pi.end(); ++j)
						static_cast<state_const_ref>(*j)->serialize(out, static_cast<CharT>('q'));
				}
				return out << ", " << i << ')';
			}
#endif
		};

		match input_match;

		depth_first_parser_no_output(): input_match()
		{}
		depth_first_parser_no_output(match input_match_): input_match(input_match_)
		{}

		//Develop first execution state of the queue of pending execution states
		bool traverse(execution_state &x_s, source_ref input_end, bool next_token_isnt_white_separated, bool hasnt_white_at_end, const context_type &c)
		{
			//If this execution state is complete (it corresponds to a final state with no pending calls after having consumed the whole input)
			//add its blackboard to the result set
			if (x_s.in == input_end && x_s.q->is_final() && x_s.pi.empty())
			{
#ifdef TRACE
				std::wcout << L" acceptor execution state found" << std::endl;
#endif
				return true;
			}

			if (x_s.in != input_end)
			{
				source_ref in_plus_1(x_s.in);
				++in_plus_1;
				bool next_next_token_isnt_white_separated((in_plus_1 != input_end && (*x_s.in)->end == (*in_plus_1)->begin) || (in_plus_1 == input_end && hasnt_white_at_end));
				for (outgoing_deleting_transition_set_const_iterator odt_it(x_s.q->outgoing_deleting_transitions.begin()); odt_it != x_s.q->outgoing_deleting_transitions.end(); ++odt_it)
				{
					if (input_match(*x_s.in, odt_it->input))
					{
#ifdef TRACE
						execution_state x_t(static_cast<state_const_ref>(odt_it->target), x_s.pi, in_plus_1, x_s.i + 1);
						x_t.serialize(std::wcout)  << L" (";
						input_serializer()(std::wcout, *x_s.in) << L" : <E>)" << std::endl;
#else
						execution_state x_t(odt_it->target, x_s.pi, in_plus_1);
#endif
						if (traverse(x_t, input_end, next_next_token_isnt_white_separated, hasnt_white_at_end, c))
							return true;
#ifdef TRACE
						x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
					}
				}
				for (outgoing_translating_transition_set_const_iterator ott_it(x_s.q->outgoing_translating_transitions.begin()); ott_it != x_s.q->outgoing_translating_transitions.end(); ++ott_it)
				{
					if (input_match(*x_s.in, ott_it->input))
					{
#ifdef TRACE
						execution_state x_t(static_cast<state_const_ref>(ott_it->target), x_s.pi, in_plus_1, x_s.i + 1);
						x_t.serialize(std::wcout) << L" (";
						input_serializer()(std::wcout, *x_s.in) << L" : ";
						tag_output_serializer()(std::wcout, ott_it->output) << L')' << std::endl;
#else
						execution_state x_t(ott_it->target, x_s.pi, in_plus_1);
#endif
						if (traverse(x_t, input_end, next_next_token_isnt_white_separated, hasnt_white_at_end, c))
							return true;
#ifdef TRACE
						x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
					}
				}
			}
			outgoing_epsilon_transition_set_const_iterator oet_it(x_s.q->outgoing_epsilon_transitions.begin());
			for (; oet_it != x_s.q->outgoing_epsilon_transitions.end(); ++oet_it)
			{
#ifdef TRACE
				execution_state x_t(static_cast<state_const_ref>(oet_it->target), x_s.pi, x_s.in, x_s.i);
				x_t.serialize(std::wcout) << L" (<E> : <E>)" << std::endl;
#else
				execution_state x_t(oet_it->target, x_s.pi, x_s.in);
#endif
				if (traverse(x_t, input_end, next_token_isnt_white_separated, hasnt_white_at_end, c))
					return true;
#ifdef TRACE
				x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
			}
            outgoing_epsilon_context_transition_set_const_iterator oect_it(x_s.q->outgoing_epsilon_context_transitions.begin());
            for (; oect_it != x_s.q->outgoing_epsilon_context_transitions.end(); ++oect_it)
            {
                if (c.equals(oect_it->key, oect_it->value))
                {
#ifdef TRACE
                    execution_state x_t(static_cast<state_const_ref>(oect_it->target), x_s.pi, x_s.in, x_s.i);
                    x_t.serialize(std::wcout) << L" (<E> : <E>)" << std::endl;
#else
                    execution_state x_t(oect_it->target, x_s.pi, x_s.in);
#endif
                    if (traverse(x_t, input_end, next_token_isnt_white_separated, hasnt_white_at_end, c))
                        return true;
#ifdef TRACE
                    x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
                }
            }
			outgoing_inserting_transition_set_const_iterator oit_it(x_s.q->outgoing_inserting_transitions.begin());
			for (; oit_it != x_s.q->outgoing_inserting_transitions.end(); ++oit_it)
			{
#ifdef TRACE
				execution_state x_t(static_cast<state_const_ref>(oit_it->target), x_s.pi, x_s.in, x_s.i);
				x_t.serialize(std::wcout) << L" (<E> : ";
				tag_output_serializer()(std::wcout, oit_it->output) << L')' << std::endl;
#else
				execution_state x_t(oit_it->target, x_s.pi, x_s.in);
#endif
				if (traverse(x_t, input_end, next_token_isnt_white_separated, hasnt_white_at_end, c))
					return true;
#ifdef TRACE
				x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
			}
            outgoing_inserting_context_transition_set_const_iterator oict_it(x_s.q->outgoing_inserting_context_transitions.begin());
            for (; oict_it != x_s.q->outgoing_inserting_context_transitions.end(); ++oict_it)
            {
                if (c.equals(oict_it->key, oict_it->value))
                {
#ifdef TRACE
                    execution_state x_t(static_cast<state_const_ref>(oict_it->target), x_s.pi, x_s.in, x_s.i);
                    x_t.serialize(std::wcout) << L" (<E> : ";
                    tag_output_serializer()(std::wcout, oict_it->output) << L')' << std::endl;
#else
                    execution_state x_t(oict_it->target, x_s.pi, x_s.in);
#endif
                    if (traverse(x_t, input_end, next_token_isnt_white_separated, hasnt_white_at_end, c))
                        return true;
#ifdef TRACE
                    x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
                }
            }
			if (next_token_isnt_white_separated)
			{
				for (oet_it = x_s.q->outgoing_no_blank_epsilon_transitions.begin(); oet_it != x_s.q->outgoing_no_blank_epsilon_transitions.end(); ++oet_it)
				{
#ifdef TRACE
					execution_state x_t(static_cast<state_const_ref>(oet_it->target), x_s.pi, x_s.in, x_s.i);
					x_t.serialize(std::wcout) << L" no-blank (<E> : <E>)" << std::endl;
#else
					execution_state x_t(oet_it->target, x_s.pi, x_s.in);
#endif
					if (traverse(x_t, input_end, next_token_isnt_white_separated, hasnt_white_at_end, c))
						return true;
#ifdef TRACE
					x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
				}
				for (oit_it = x_s.q->outgoing_no_blank_inserting_transitions.begin(); oit_it != x_s.q->outgoing_no_blank_inserting_transitions.end(); ++oit_it)
				{
#ifdef TRACE
					execution_state x_t(static_cast<state_const_ref>(oit_it->target), x_s.pi, x_s.in, x_s.i);
					tag_output_serializer()(std::wcout, oit_it->output) << std::endl;
#else
					execution_state x_t(oit_it->target, x_s.pi, x_s.in);
#endif
					if (traverse(x_t, input_end, next_token_isnt_white_separated, hasnt_white_at_end, c))
						return true;
#ifdef TRACE
					x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
				}
			}
			else
			{
				for (oet_it = x_s.q->outgoing_blank_epsilon_transitions.begin(); oet_it != x_s.q->outgoing_blank_epsilon_transitions.end(); ++oet_it)
				{
#ifdef TRACE
					execution_state x_t(static_cast<state_const_ref>(oet_it->target), x_s.pi, x_s.in, x_s.i);
					x_t.serialize(std::wcout) << L" blank (<E> : <E>)" << std::endl;
#else
					execution_state x_t(oet_it->target, x_s.pi, x_s.in);
#endif
					if (traverse(x_t, input_end, next_token_isnt_white_separated, hasnt_white_at_end, c))
						return true;
#ifdef TRACE
					x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
				}
				for (oit_it = x_s.q->outgoing_blank_inserting_transitions.begin(); oit_it != x_s.q->outgoing_blank_inserting_transitions.end(); ++oit_it)
				{
#ifdef TRACE
					execution_state x_t(static_cast<state_const_ref>(oit_it->target), x_s.pi, x_s.in, x_s.i);
					x_t.serialize(std::wcout) << L" (<E> : ";
					tag_output_serializer()(std::wcout, oit_it->output) << std::endl;
#else
					execution_state x_t(oit_it->target, x_s.pi, x_s.in);
#endif
					if (traverse(x_t, input_end, next_token_isnt_white_separated, hasnt_white_at_end, c))
						return true;
#ifdef TRACE
					x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
				}
			}
			for (outgoing_call_transition_set_const_iterator ocallt_it(x_s.q->outgoing_call_transitions.begin()); ocallt_it != x_s.q->outgoing_call_transitions.end(); ++ocallt_it)
			{
				state_const_ref target(static_cast<state_const_ref>(ocallt_it->target));
#ifdef TRACE
				execution_state x_t(static_cast<state_const_ref>(ocallt_it->called), x_s.pi + target, x_s.in, x_s.i);
				x_t.serialize(std::wcout) << L" push" << std::endl;
#else
				execution_state x_t(ocallt_it->called, x_s.pi + target, x_s.in);
#endif
				if (traverse(x_t, input_end, next_token_isnt_white_separated, hasnt_white_at_end, c))
					return true;
#ifdef TRACE
				x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
			}
			if (x_s.q->is_final() && !x_s.pi.empty())
			{
#ifdef TRACE
				execution_state x_t(static_cast<state_const_ref>(x_s.pi.back()), x_s.pi.prefix(), x_s.in, x_s.i);
				x_t.serialize(std::wcout) << L" pop" << std::endl;
#else
				execution_state x_t(x_s.pi.back(), x_s.pi.prefix(), x_s.in);
#endif
				if (traverse(x_t, input_end, next_token_isnt_white_separated, hasnt_white_at_end, c))
					return true;
#ifdef TRACE
				x_s.serialize(std::wcout << "back to ") << std::endl;
#endif
			}
			return false;
		}

		//Compute the r-translations of the input range [input_being, input_end) and add them to the set t
		bool operator()(const machine& grammar, SourceRef input_begin, SourceRef input_end, bool hasnt_white_at_begin, bool hasnt_white_at_end, const context_type &c)
		{
#ifdef TRACE
			std::wcout << L"Begin parsing\n";
#endif
			//Initialize pool of state sequences
			state_const_ref_stack_pool scrsp;

			//Launch whole grammar exploration from the initial execution state (q_I, lambda, 0)
#ifdef TRACE
			execution_state x_i(grammar.initial_state(), scrsp.empty(), input_begin, 0);
			x_i.serialize(std::wcout) << L" initial" << std::endl;
#else
			execution_state x_i(grammar.initial_state(), scrsp.empty(), input_begin);
#endif
			if (traverse(x_i, input_end, hasnt_white_at_begin, hasnt_white_at_end, c))
			{
#ifdef TRACE
				std::wcout << L"Input accepted\n";
				std::wcout << L"End parsing\n";
#endif
				return true;
			}
#ifdef TRACE
			x_i.serialize(std::wcout << "back to ") << std::endl;
			std::wcout << L"Input rejected\n";
			std::wcout << L"End parsing\n";
#endif
			return false;
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_DEPTH_FIRST_PARSER_NO_OUTPUT_H*/
