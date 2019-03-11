/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2008 Université de Marne-la-Vallée <javier.sastre@univ-mlv.fr>
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

#ifndef GRAPENLP_BREADTH_FIRST_PARSER_NO_OUTPUT_H
#define GRAPENLP_BREADTH_FIRST_PARSER_NO_OUTPUT_H

#ifdef TRACE
#include <iostream>
#include <fstream>
#include <grapenlp/tag_serializer_traits.h>
#endif

#include <queue>
#include <memory>

#include <grapenlp/functional.h>
#include <grapenlp/sequence_impl_choice.h>
#include <grapenlp/set_impl_selector.h>
#include <grapenlp/tag_input_traits.h>
#include <grapenlp/u_context_mask.h>
#include <grapenlp/pool.h>
#include <grapenlp/rtno.h>

namespace grapenlp
{
	template<typename TagInput, typename TagOutput, typename SourceRef, typename StateConstRefStackPool, assoc_container_impl_choice execution_state_set_impl_choice>
	struct breadth_first_parser_no_output
	{
		typedef TagInput tag_input;
		typedef TagOutput tag_output;
		typedef SourceRef source_ref;
		typedef typename source_ref::value_type input;
#ifdef TRACE
		typedef typename tag_serializer_traits<input>::type input_serializer;
		typedef typename tag_serializer_traits<tag_input>::type tag_input_serializer;
		typedef typename tag_serializer_traits<tag_output>::type tag_output_serializer;
		typedef ns_rtno<tag_input, tag_output, u_context_mask> machine;
#else
		typedef rtno<tag_input, tag_output, u_context_mask> machine;
#endif
		typedef typename tag_input_traits<tag_input>::match match;
		typedef typename machine::state state;
		typedef typename machine::state_ref state_ref;
		typedef typename machine::state_const_ref state_const_ref;
		typedef typename machine::state_ref_list_const_iterator state_ref_list_const_iterator;

		typedef	typename machine::outgoing_epsilon_transition outgoing_epsilon_transition;
		typedef	typename machine::outgoing_epsilon_transition_set outgoing_epsilon_transition_set;
		typedef typename outgoing_epsilon_transition_set::iterator outgoing_epsilon_transition_set_iterator;
		typedef typename outgoing_epsilon_transition_set::const_iterator outgoing_epsilon_transition_set_const_iterator;

		typedef	typename machine::outgoing_epsilon_context_transition outgoing_epsilon_context_transition;
		typedef	typename machine::outgoing_epsilon_context_transition_set outgoing_epsilon_context_transition_set;
		typedef typename outgoing_epsilon_context_transition_set::iterator outgoing_epsilon_context_transition_set_iterator;
		typedef typename outgoing_epsilon_context_transition_set::const_iterator outgoing_epsilon_context_transition_set_const_iterator;

		typedef	typename machine::outgoing_deleting_transition outgoing_deleting_transition;
		typedef	typename machine::outgoing_deleting_transition_set outgoing_deleting_transition_set;
		typedef typename outgoing_deleting_transition_set::iterator outgoing_deleting_transition_set_iterator;
		typedef typename outgoing_deleting_transition_set::const_iterator outgoing_deleting_transition_set_const_iterator;

		typedef	typename machine::outgoing_translating_transition outgoing_translating_transition;
		typedef	typename machine::outgoing_translating_transition_set outgoing_translating_transition_set;
		typedef typename outgoing_translating_transition_set::iterator outgoing_translating_transition_set_iterator;
		typedef typename outgoing_translating_transition_set::const_iterator outgoing_translating_transition_set_const_iterator;

		typedef	typename machine::outgoing_inserting_transition outgoing_inserting_transition;
		typedef	typename machine::outgoing_inserting_transition_set outgoing_inserting_transition_set;
		typedef typename outgoing_inserting_transition_set::iterator outgoing_inserting_transition_set_iterator;
		typedef typename outgoing_inserting_transition_set::const_iterator outgoing_inserting_transition_set_const_iterator;

		typedef	typename machine::outgoing_inserting_context_transition outgoing_inserting_context_transition;
		typedef	typename machine::outgoing_inserting_context_transition_set outgoing_inserting_context_transition_set;
		typedef typename outgoing_inserting_context_transition_set::iterator outgoing_inserting_context_transition_set_iterator;
		typedef typename outgoing_inserting_context_transition_set::const_iterator outgoing_inserting_context_transition_set_const_iterator;

		typedef	typename machine::outgoing_call_transition outgoing_call_transition;
		typedef	typename machine::outgoing_call_transition_set outgoing_call_transition_set;
		typedef typename outgoing_call_transition_set::iterator outgoing_call_transition_set_iterator;
		typedef typename outgoing_call_transition_set::const_iterator outgoing_call_transition_set_const_iterator;

		typedef StateConstRefStackPool state_const_ref_stack_pool;
		typedef typename pool_traits<state_const_ref_stack_pool>::value_type state_const_ref_stack;
		typedef typename pool_traits<state_const_ref_stack_pool>::iterator state_const_ref_stack_iterator;
		typedef typename pool_traits<state_const_ref_stack_pool>::const_iterator state_const_ref_stack_const_iterator;
		typedef typename pool_traits<state_const_ref_stack_pool>::less state_const_ref_stack_less;
		typedef typename pool_traits<state_const_ref_stack_pool>::compare_3w state_const_ref_stack_compare_3w;

		//(q, b, pi) in (Q X B X Q*)
		//We do not implement here a field q_c but a method get_q_c(). Derived classes must implement this function
		struct execution_state
		{
			typedef execution_state* ref;
			typedef typename set_impl_selector<execution_state_set_impl_choice, execution_state>::type set;
			typedef std::queue<const execution_state *> const_ref_queue;

			state_const_ref q;
			state_const_ref_stack pi;

			execution_state(state_const_ref q_, state_const_ref_stack pi_): q(q_), pi(pi_)
			{}

			bool operator< (const execution_state& x2) const
			{
				if (q < x2.q)
					return true;
				if (x2.q < q)
					return false;
				//We don't care here about lexicographical comparison, we simply compare the object addresses in order to optimize comparison
				return state_const_ref_stack_less()(pi, x2.pi);
			}

			std::ptrdiff_t compare_3w(const execution_state& x2) const
			{
				//We don't care here about lexicographical comparison, we simply compare the object addresses in order to optimize comparison
				std::ptrdiff_t result(reinterpret_cast<std::ptrdiff_t>(q) - reinterpret_cast<std::ptrdiff_t>(x2.q));
				if (result)
					return result;
				return state_const_ref_stack_compare_3w()(pi, x2.pi);
			}

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
					for (state_const_ref_stack_const_iterator i(pi.begin()); i != pi.end(); ++i)
						(*i)->serialize(out, static_cast<CharT>('q'));
				}
				return out << ')';
			}
#endif
		};

		typedef typename execution_state::ref execution_state_ref;
		typedef typename execution_state::set execution_state_set;
		typedef typename execution_state_set::iterator execution_state_set_iterator;
		typedef typename execution_state_set::const_iterator execution_state_set_const_iterator;
		typedef typename execution_state::const_ref_queue execution_state_const_ref_queue;

		struct acceptor_execution_state_acknowledger
		{
			bool &accept;

			acceptor_execution_state_acknowledger(bool &accept_): accept(accept_)
			{}

			void operator()(const execution_state &x)
			{
				accept = accept || (x.q->is_final() && x.pi.empty());
#ifdef TRACE
				if (x.q->is_final() && x.pi.empty())
					std::wcout << L"acceptor execution state found" << std::endl;
#endif
			}
		};

		struct no_op_on_execution_state
		{
			void operator()(__attribute__((unused)) const execution_state &x) const
			{}
		};

		match input_match;
		execution_state_set v;
		execution_state_const_ref_queue e;

		breadth_first_parser_no_output(): input_match(), v()
		{}
		breadth_first_parser_no_output(match input_match_): input_match(input_match_), v()
		{}

		template<typename ExtraInsertOp>
#ifdef TRACE
		void process_epsilon_transitions(const execution_state &x_s, outgoing_epsilon_transition_set_iterator epsilon_transition_begin, outgoing_epsilon_transition_set_iterator epsilon_transition_end, ExtraInsertOp op, const std::wstring &epsilon_transition_type = L"")
#else
		void process_epsilon_transitions(const execution_state &x_s, outgoing_epsilon_transition_set_iterator epsilon_transition_begin, outgoing_epsilon_transition_set_iterator epsilon_transition_end, ExtraInsertOp op)
#endif
		{
			for (; epsilon_transition_begin != epsilon_transition_end; ++epsilon_transition_begin)
			{
				std::pair<execution_state_set_iterator, bool> result(v.insert(execution_state(static_cast<state_const_ref>(epsilon_transition_begin->target), x_s.pi)));
				if (result.second)
				{
#ifdef TRACE
					result.first->serialize(std::wcout) << L" (" << epsilon_transition_type << L"<E> : <E>)" << std::endl;
#endif
					e.push(&(*result.first));
					op(*result.first);
				}
			}
		}

		template<typename ExtraInsertOp>
		void process_epsilon_context_transitions(const execution_state &x_s, outgoing_epsilon_context_transition_set_iterator epsilon_context_transition_begin, outgoing_epsilon_context_transition_set_iterator epsilon_context_transition_end, const u_context &c, ExtraInsertOp op)
		{
			for (; epsilon_context_transition_begin != epsilon_context_transition_end; ++epsilon_context_transition_begin)
			{
                if (epsilon_context_transition_begin->mask.match(c))
                {
    				std::pair<execution_state_set_iterator, bool> result(v.insert(execution_state(static_cast<state_const_ref>(epsilon_context_transition_begin->target), x_s.pi)));
    				if (result.second)
    				{
#ifdef TRACE
                        result.first->serialize(std::wcout) <<
							L" (";
						epsilon_context_transition_begin->mask.wserialize(std::wcout) <<
							L" : <E>)" <<
							std::endl;
#endif
	    				e.push(&(*result.first));
		    			op(*result.first);
    				}
                }
			}
		}

		template<typename ExtraInsertOp>
#ifdef TRACE
		void process_inserting_transitions(const execution_state &x_s, outgoing_inserting_transition_set_iterator inserting_transition_begin, outgoing_inserting_transition_set_iterator inserting_transition_end, SourceRef in, ExtraInsertOp op, const std::wstring &inserting_transition_type = L"")
#else
		void process_inserting_transitions(const execution_state &x_s, outgoing_inserting_transition_set_iterator inserting_transition_begin, outgoing_inserting_transition_set_iterator inserting_transition_end, SourceRef in, ExtraInsertOp op)
#endif
		{
			for (; inserting_transition_begin != inserting_transition_end; ++inserting_transition_begin)
			{
				std::pair<execution_state_set_iterator, bool> result(v.insert(execution_state(static_cast<state_const_ref>(inserting_transition_begin->target), x_s.pi)));
				if (result.second)
				{
#ifdef TRACE
					result.first->serialize(std::wcout) << L" (" << inserting_transition_type << "<E> : ";
					tag_output_serializer()(std::wcout, inserting_transition_begin->output) << L')' << std::endl;
#endif
					e.push(&(*result.first));
					op(*result.first);
				}
			}
		}

        template<typename ExtraInsertOp>
        void process_inserting_context_transitions(const execution_state &x_s, outgoing_inserting_context_transition_set_iterator inserting_context_transition_begin, outgoing_inserting_context_transition_set_iterator inserting_context_transition_end, SourceRef in, const u_context &c, ExtraInsertOp op)
        {
            for (; inserting_context_transition_begin != inserting_context_transition_end; ++inserting_context_transition_begin)
            {
                if (inserting_context_transition_begin->mask.match(c))
                {
                    std::pair<execution_state_set_iterator, bool> result(v.insert(
                            execution_state(static_cast<state_const_ref>(inserting_context_transition_begin->target), x_s.pi)));
                    if (result.second) {
#ifdef TRACE
                        result.first->serialize(std::wcout) <<
							L" (<@";
						inserting_context_transition_begin->mask.wserialize(std::wcout) <<
							L" : ";
						tag_output_serializer()(std::wcout, inserting_context_transition_begin->output) <<
							L')' <<
							std::endl;
#endif
                        e.push(&(*result.first));
                        op(*result.first);
                    }
                }
            }
        }

		//Increment parsing chart with the epsilon-closure of the last active set of execution states
		template<typename ExtraInsertOp>
		void eclosure(SourceRef in, bool next_token_isnt_white_separated, const u_context &c, ExtraInsertOp op)
		{
			//While there are execution states pending to be processed
			while (!e.empty())
			{
				//Pop next pending active execution state (q, b, lambda, q_h, j)
				const execution_state &x_s(*e.front());
				e.pop();

				//Process epsilon and inserting transitions
				process_epsilon_transitions(x_s, x_s.q->outgoing_epsilon_transitions.begin(), x_s.q->outgoing_epsilon_transitions.end(), op);
				process_inserting_transitions(x_s, x_s.q->outgoing_inserting_transitions.begin(), x_s.q->outgoing_inserting_transitions.end(), in, op);

                //Process epsilon and inserting context transitions
                process_epsilon_context_transitions(x_s, x_s.q->outgoing_epsilon_context_transitions.begin(), x_s.q->outgoing_epsilon_context_transitions.end(), c, op);
                process_inserting_context_transitions(x_s, x_s.q->outgoing_inserting_context_transitions.begin(), x_s.q->outgoing_inserting_context_transitions.end(), in, c, op);

				//Process no-blank epsilon and inserting transitions
				//if there are no whites between the current (or input begin) and the next token (or input end)
				if (next_token_isnt_white_separated)
				{
#ifdef TRACE
					process_epsilon_transitions(x_s, x_s.q->outgoing_no_blank_epsilon_transitions.begin(), x_s.q->outgoing_no_blank_epsilon_transitions.end(), op, L"no-blank ");
					process_inserting_transitions(x_s, x_s.q->outgoing_no_blank_inserting_transitions.begin(), x_s.q->outgoing_no_blank_inserting_transitions.end(), in, op, L"no-blank ");
#else
					process_epsilon_transitions(x_s, x_s.q->outgoing_no_blank_epsilon_transitions.begin(), x_s.q->outgoing_no_blank_epsilon_transitions.end(), op);
					process_inserting_transitions(x_s, x_s.q->outgoing_no_blank_inserting_transitions.begin(), x_s.q->outgoing_no_blank_inserting_transitions.end(), in, op);
#endif
				}

				//Process blank epsilon and inserting transitions otherwise
				else
				{
#ifdef TRACE
					process_epsilon_transitions(x_s, x_s.q->outgoing_blank_epsilon_transitions.begin(), x_s.q->outgoing_blank_epsilon_transitions.end(), op, L"blank ");
					process_inserting_transitions(x_s, x_s.q->outgoing_blank_inserting_transitions.begin(), x_s.q->outgoing_blank_inserting_transitions.end(), in, op, L"blank ");
#else
					process_epsilon_transitions(x_s, x_s.q->outgoing_blank_epsilon_transitions.begin(), x_s.q->outgoing_blank_epsilon_transitions.end(), op);
					process_inserting_transitions(x_s, x_s.q->outgoing_blank_inserting_transitions.begin(), x_s.q->outgoing_blank_inserting_transitions.end(), in, op);
#endif
				}

				//Process call-transitions; Earley's predictor
				for (outgoing_call_transition_set_iterator call_transition_begin(x_s.q->outgoing_call_transitions.begin()); call_transition_begin != x_s.q->outgoing_call_transitions.end(); ++call_transition_begin)
				{
					state_const_ref target(static_cast<state_const_ref>(call_transition_begin->target));
					std::pair<execution_state_set_iterator, bool> result(v.insert(execution_state(static_cast<state_const_ref>(call_transition_begin->called), x_s.pi + target)));
					if (result.second)
					{
#ifdef TRACE
						result.first->serialize(std::wcout) << L" push" << std::endl;
#endif
						e.push(&(*result.first));
						op(*result.first);
					}
				}

				//Process pop-transition; Earley's completer
				if (x_s.q->is_final() && !x_s.pi.empty())
				{
					std::pair<execution_state_set_iterator, bool> result(v.insert(execution_state(static_cast<state_const_ref>(x_s.pi.back()), x_s.pi.prefix())));
					if (result.second)
					{
#ifdef TRACE
						result.first->serialize(std::wcout) << L" pop" << std::endl;
#endif
						e.push(&(*result.first));
						op(*result.first);
					}
				}
			}
		}


		//Earley scanner: adds a new item to the parsing chart and initializes it with the attainable set of execution states from the former last chart item set of execution states through the consumption of an input symbol sigma
		template<typename ExtraInsertOp>
		execution_state_set translate_symbol(SourceRef in_i, ExtraInsertOp op)
		{
			execution_state_set w;

			//For each (q, b, lambda, q_h, i) in v
			for (execution_state_set_const_iterator x_s_it(v.begin()); x_s_it != v.end(); ++x_s_it)
			{
				//For each (q', lambda) = delta(q, (sigma, epsilon))
				//Process deleting transitions
				for (outgoing_deleting_transition_set_const_iterator dt_it(x_s_it->q->outgoing_deleting_transitions.begin()); dt_it != x_s_it->q->outgoing_deleting_transitions.end(); ++dt_it)
				{
					if (input_match(*in_i, dt_it->input))
					{
						//w = w union (q', b, lambda, q_h, i)
						std::pair<execution_state_set_iterator, bool> result(w.insert(execution_state(static_cast<state_const_ref>(dt_it->target), x_s_it->pi)));
						if (result.second)
						{
#ifdef TRACE
							result.first->serialize(std::wcout) << L" (";
							input_serializer()(std::wcout, *in_i) << L" : <E>)" << std::endl;
#endif
							e.push(&(*result.first));
							op(*result.first);
						}
					}
				}
				//For each (q', lambda) = delta(q, (sigma, g))
				//Process translating transitions
				for (outgoing_translating_transition_set_const_iterator tt_it(x_s_it->q->outgoing_translating_transitions.begin()); tt_it != x_s_it->q->outgoing_translating_transitions.end(); ++tt_it)
				{
					if (input_match(*in_i, tt_it->input))
					{
						//w = w union (q', bg, lambda, q_h, i)
						std::pair<execution_state_set_iterator, bool> result(w.insert(execution_state(static_cast<state_const_ref>(tt_it->target), x_s_it->pi)));
						if (result.second)
						{
#ifdef TRACE
							result.first->serialize(std::wcout) << L" (";
							input_serializer()(std::wcout, *in_i) << L" : ";
							tag_output_serializer()(std::wcout, tt_it->output) << L')' << std::endl;
#endif
							e.push(&(*result.first));
							op(*result.first);
						}
					}
				}
			}
			return w;
		}


		//Build V_0 as the eclosure of Q X {b_emptyset} X {lambda};
		template<typename ExtraInsertOp>
		void build_initial_ses(state_const_ref initial_state, state_const_ref_stack empty_stack, bool hasnt_white_at_begin, ExtraInsertOp op)
		{
#ifdef TRACE
			std::wcout << L"----- V[0] -----" << std::endl;
#endif
			std::pair<execution_state_set_iterator, bool> result(v.insert(execution_state(initial_state, empty_stack)));
			e.push(&(*result.first));
			op(*e.back());
#ifdef TRACE
			e.back()->serialize(std::wcout) << L" initial" << std::endl;
#endif
		}

		//Compute the r-translations of the input range [input_being, input_end) and add them to the set t
		bool operator()(const machine& grammar, SourceRef input_begin, SourceRef input_end, bool hasnt_white_at_begin, bool hasnt_white_at_end, const u_context &c)
		{
#ifdef TRACE
			std::wcout << L"Begin parsing\n";
#endif
			bool accept(false);

			//Initialize pool of state sequences
			state_const_ref_stack_pool scrsp;

			//Initialize sets of execution states V and V^prime
			v.clear();

			no_op_on_execution_state no_op;
			acceptor_execution_state_acknowledger ack_op(accept);

			//Build V_0 as the closure of Q X {b_emptyset} X {lambda};
			//If empty input, build initial and final V[0]
			if (input_begin == input_end)
			{
				build_initial_ses(grammar.initial_state(), scrsp.empty(), hasnt_white_at_begin, ack_op);
				//First token is white separated if there are trailing whites at the beginning
				eclosure(input_begin, hasnt_white_at_begin, c, ack_op);
			}
			//Else build initial V[0] and the remaining V[i]
			else
			{
				build_initial_ses(grammar.initial_state(), scrsp.empty(), hasnt_white_at_begin, no_op);
				//First token is white separated if there are trailing whites at the beginning
				eclosure(input_begin, hasnt_white_at_begin, c, no_op);
#ifdef TRACE
				std::size_t idx(0);
#endif
				SourceRef input_begin_plus_1(input_begin);
				--input_end;
				//While the last set of execution states is not empty and there are input symbols left, compute the next set of execution states
				while (!v.empty() && input_begin != input_end)
				{
#ifdef TRACE
					std::wcout << L"----- V[" << static_cast<int>(idx) + 1 << L"] -----" << std::endl;
#endif
					++input_begin_plus_1;
					execution_state_set w(translate_symbol(input_begin, no_op));
#ifdef TRACE
					++idx;
#endif
					v.swap(w);
					eclosure(input_begin_plus_1, (*input_begin)->end == (*input_begin_plus_1)->begin, c, no_op);
					++input_begin;
				}
				++input_end;

				//Compute last set of execution states
				if (!v.empty())
				{
#ifdef TRACE
					std::wcout << L"Last----- V[" << static_cast<int>(idx) + 1 << L"] -----" << std::endl;
#endif
					++input_begin_plus_1;
					execution_state_set w(translate_symbol(input_begin, ack_op));
#ifdef TRACE
					++idx;
#endif
					v.swap(w);
					//Next token is the input end... it is white separated if there are trailing whites at the end
					eclosure(input_begin_plus_1, hasnt_white_at_end, c, ack_op);
					++input_begin;
				}
			}
#ifdef TRACE
			std::wcout << L"End parsing\n";
#endif
			return accept;
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_BREADTH_FIRST_PARSER_NO_OUTPUT_H*/
