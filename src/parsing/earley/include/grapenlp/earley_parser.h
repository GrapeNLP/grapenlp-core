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

#ifndef GRAPENLP_EARLEY_PARSER_H
#define GRAPENLP_EARLEY_PARSER_H

#ifdef TRACE
#include <iostream>
#include <fstream>
#include <grapenlp/tag_serializer_traits.h>
#endif

#include <queue>
#include <memory>

#include <grapenlp/sequence_impl_choice.h>
#include <grapenlp/set_impl_selector.h>
#include <grapenlp/tag_input_traits.h>
#include <grapenlp/u_context_mask.h>
#include <grapenlp/rtno.h>

namespace grapenlp
{
#ifdef TRACE
	template<typename TagInput, typename TagOutput, typename SourceRef, typename Blackboard, typename BlackboardSerializer, typename Transformer, typename Composer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
#else
	template<typename TagInput, typename TagOutput, typename SourceRef, typename Blackboard, typename Transformer, typename Composer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
#endif
	struct earley_parser
	{
		typedef TagInput tag_input;
		typedef TagOutput tag_output;
		typedef SourceRef source_ref;
		typedef typename source_ref::value_type input;
		typedef Blackboard blackboard;
#ifdef TRACE
		typedef BlackboardSerializer blackboard_serializer;
		typedef typename tag_serializer_traits<input>::type input_serializer;
		typedef typename tag_serializer_traits<tag_input>::type tag_input_serializer;
		typedef typename tag_serializer_traits<tag_output>::type tag_output_serializer;
#endif
		typedef typename set_impl_selector<output_set_impl_choice, blackboard>::type blackboard_set;
		typedef typename blackboard_set::const_iterator blackboard_set_const_iterator;
		typedef Transformer transformer;
		typedef Composer composer;

#ifdef TRACE
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

		//5-tuple (q, b, q_c, q_h, i) in (Q X B X {lambda} X Q X N)
		//We do not implement here a field q_c but a method get_q_c(). Derived classes must implement this function
		struct execution_state
		{
			state_const_ref q;
			const blackboard b;
			//q_c is always lambda; we do not represent it explicitly, it is inherent to the data type
			//state_ref q_c;
			state_const_ref q_h;
			std::size_t i;

			//Used to constructs a dummy paused execution state (see paused_execution_state constructor below)
			execution_state(): q(), b(), q_h(), i(0)
			{}

			//Constructs an active execution state by joining up the 5-tuple (in fact 4-tuple) elements
			execution_state(state_const_ref q_, const blackboard& b_, state_const_ref q_h_, std::size_t i_): q(q_), b(b_), q_h(q_h_), i(i_)
			{}

			virtual state_const_ref get_q_c() const = 0;

			virtual ~execution_state() {}

#ifdef TRACE
			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
			{
				out << '(';
				if (q)
					q->serialize(out, static_cast<CharT>('q'));
				else out << "void_state";
				blackboard_serializer()(out << ", ", b) << ", ";
				if (get_q_c())
					get_q_c()->serialize(out, static_cast<CharT>('q'));
				else out << "lambda";
				out << ", ";
				if (q_h)
					q_h->serialize(out, static_cast<CharT>('q'));
				else out << "void_state";
				return out << ", " << static_cast<int>(i) << ')';
			}
#endif
		};

		//5-tuple (q, b, q_c, q_h, i) in (Q X B X {lambda} X Q X N)
		//Since q_c is constant we implement method get_q_c() to return a constant value "lambda"
		struct active_execution_state: public execution_state
		{
			typedef active_execution_state* ref;
			typedef typename set_impl_selector<execution_state_set_impl_choice, active_execution_state>::type set;
			typedef std::queue<const active_execution_state *> const_ref_queue;

			//Constructs an active execution state by joining up the 5-tuple (in fact 4-tuple since field q_c is constant) elements
			active_execution_state(state_const_ref q_, const blackboard& b_, state_const_ref q_h_, std::size_t i_): execution_state(q_, b_, q_h_, i_)
			{}

			state_const_ref get_q_c() const
			{
				return state_ref(NULL);
			}

			//Field q_c is not taken into account for comparisons of active_execution_state objects since it is constant
			bool operator< (const active_execution_state& x2) const
			{
				if (this->q < x2.q)
					return true;
				if (x2.q < this->q)
					return false;
				if (this->q_h < x2.q_h)
					return true;
				if (x2.q_h < this->q_h)
					return false;
				if (this->i < x2.i)
					return true;
				if (x2.i < this->i)
					return false;
				//Last comparison, the most expensive
				return this->b < x2.b;
			}

			std::ptrdiff_t compare_3w(const active_execution_state& x2) const
			{
				std::ptrdiff_t result(reinterpret_cast<std::ptrdiff_t>(this->q) - reinterpret_cast<std::ptrdiff_t>(x2.q));
				if (result)
					return result;
				if ((result = reinterpret_cast<std::ptrdiff_t>(this->q_h) - reinterpret_cast<std::ptrdiff_t>(x2.q_h)))
					return result;
				if ((result = static_cast<std::ptrdiff_t>(this->i) - static_cast<std::ptrdiff_t>(x2.i)))
					return result;
				return grapenlp::compare_3w<blackboard>()(this->b, x2.b);
			}
		};

		typedef typename active_execution_state::ref active_execution_state_ref;
		typedef typename active_execution_state::set active_execution_state_set;
		typedef typename active_execution_state_set::iterator active_execution_state_set_iterator;
		typedef typename active_execution_state_set::const_iterator active_execution_state_set_const_iterator;
		typedef typename active_execution_state::const_ref_queue active_execution_state_const_ref_queue;

		//5-tuple (q, b, q_c, q_h, i) in (Q X B X Q X Q X N)
		//Earley_execution_state having a non-constant q_c field
		struct paused_execution_state: public execution_state
		{
			typedef paused_execution_state* ref;
			typedef typename set_impl_selector<execution_state_set_impl_choice, paused_execution_state>::type set;

			state_const_ref q_c;

			//Constructs a dummy paused execution state to be used as lower bound for the retrieval from ordered sets of execution states having a specific q_c (see Earley's completer in the eclosure function below)
			paused_execution_state(): execution_state(), q_c()
			{}

			//Constructs an active execution state by joining up the 5-tuple (in fact 4-tuple since field q_c is constant) elements
			paused_execution_state(state_const_ref q_, const blackboard& b_, state_const_ref q_c_, state_const_ref q_h_, std::size_t i_): execution_state(q_, b_, q_h_, i_), q_c(q_c_)
			{}

			state_const_ref get_q_c() const
			{ return q_c; }

			bool operator< (const paused_execution_state& x2) const
			{
				//Paused execution states depending on a called state q_c are resumed once a sub-execution state starting from that q_c is completed
				//We set state q_c as the first order criteria in order to accelerate the retrieval of paused execution states to be resumed
				if (this->q_c < x2.q_c)
					return true;
				if (x2.q_c < this->q_c)
					return false;
				if (this->q < x2.q)
					return true;
				if (x2.q < this->q)
					return false;
				if (this->q_h < x2.q_h)
					return true;
				if (x2.q_h < this->q_h)
					return false;
				if (this->i < x2.i)
					return true;
				if (x2.i < this->i)
					return false;
				//Most expensive comparison at the end
				return this->b < x2.b;
			}

			std::ptrdiff_t compare_3w(const paused_execution_state& x2) const
			{
				//Paused execution states depending on a called state q_c are resumed once a sub-execution state starting from that q_c is completed
				//We set state q_c as the first order criteria in order to accelerate the retrieval of paused execution states to be resumed
				std::ptrdiff_t result(reinterpret_cast<std::ptrdiff_t>(this->q_c) - reinterpret_cast<std::ptrdiff_t>(x2.q_c));
				if (result)
					return result;
				if ((result = reinterpret_cast<std::ptrdiff_t>(this->q) - reinterpret_cast<std::ptrdiff_t>(x2.q)))
					return result;
				if ((result = reinterpret_cast<std::ptrdiff_t>(this->q_h) - reinterpret_cast<std::ptrdiff_t>(x2.q_h)))
					return result;
				if ((result = static_cast<std::ptrdiff_t>(this->i) - static_cast<std::ptrdiff_t>(x2.i)))
					return result;
				return grapenlp::compare_3w<blackboard>()(this->b, x2.b);
			}
		};

		typedef typename paused_execution_state::ref paused_execution_state_ref;
		typedef typename paused_execution_state::set paused_execution_state_set;
		typedef typename paused_execution_state_set::iterator paused_execution_state_set_iterator;
		typedef typename paused_execution_state_set::const_iterator paused_execution_state_set_const_iterator;

		struct acceptor_execution_state_inserter
		{
			blackboard_set &t;
			state_const_ref initial_state;

			acceptor_execution_state_inserter(blackboard_set &t_, state_const_ref initial_state_): t(t_), initial_state(initial_state_)
			{}

			void operator()(const active_execution_state &x)
			{
				if (x.i == 0 && x.q->is_final() && x.q_h == initial_state)
				{
					t.insert(x.b);
#ifdef TRACE
					blackboard_serializer()(std::wcout, x.b) << " added to translation set" << std::endl;
#endif
				}
			}
		};

		struct no_op_on_execution_state
		{
			void operator()(const active_execution_state &x) const
			{}
		};

		struct chart_item
		{
			active_execution_state_set aess;
			paused_execution_state_set pess;
		};

		typedef array<chart_item> chart;

		//Epsilon-completion map: maps deletable states of the grammar (states that when called, can lead to a call completion without input consumption)
		//with pairs (r_c, set of r_f's), where r_c is the output state to be called (corresponding to the deletable called state)
		//and the r_f's are the final output states from where the call is epsilon-completed
		//Given an output state r_s from where the epsilon-completed call is performed and an output target state r_t,
		// we complete the call by adding the call transition r_s --r_c--> r_t and the filtered pop transitions
		//r_f -> r_t, for every r_f in the set of r_f's
		struct epsilon_completion
		{
			state_const_ref q;
			const blackboard *b_ref;

			//Constructor for q lower bound
			epsilon_completion(state_const_ref q_): q(q_), b_ref(NULL)
			{}

			epsilon_completion(state_const_ref q_, const blackboard *b_ref_): q(q_), b_ref(b_ref_)
			{}

			bool operator< (const epsilon_completion &ec) const
			{
				if (q < ec.q)
					return true;
				if (ec.q < q)
					return false;
				//Dummy epsilon completion is the only one having a NULL blackboard pointer
				return !b_ref || (ec.b_ref && *b_ref < *ec.b_ref);
			}

			std::ptrdiff_t compare_3w(const epsilon_completion &ec) const
			{
				std::ptrdiff_t result(reinterpret_cast<std::ptrdiff_t>(q) - reinterpret_cast<std::ptrdiff_t>(ec.q));
				if (result)
					return result;
				//Dummy epsilon completion is the only one having a NULL blackboard pointer
				if ((result = static_cast<std::ptrdiff_t>(!ec.b_ref) - static_cast<std::ptrdiff_t>(!b_ref)))
					return result;
				if ((result = static_cast<std::ptrdiff_t>(!ec.b_ref) - static_cast<std::ptrdiff_t>(!b_ref)))
					return result;
				return grapenlp::compare_3w<blackboard>()(*b_ref, *ec.b_ref);
			}

			epsilon_completion& operator= (const epsilon_completion &ec)
			{
				q = ec.q;
				b_ref = ec.b_ref;
				return *this;
			}
		};

		typedef typename set_impl_selector<execution_state_set_impl_choice, epsilon_completion>::type epsilon_completion_set;

		typedef typename epsilon_completion_set::iterator epsilon_completion_set_iterator;
		typedef typename epsilon_completion_set::const_iterator epsilon_completion_set_const_iterator;

		match input_match;
		transformer gamma;
		composer circ;
		chart the_chart;
		active_execution_state_const_ref_queue e;
		//Dummy paused execution state used as lower bound for the retrieval of every paused execution state having q_c == q_h
		paused_execution_state dummy_x_p;

		earley_parser(): input_match(), gamma(), circ(), the_chart(), e(), dummy_x_p()
		{}
		earley_parser(match input_match_, transformer gamma_, composer circ_): input_match(input_match_), gamma(gamma_), circ(circ_), the_chart(), e(), dummy_x_p()
		{}

		template<typename ExtraInsertOp>
#ifdef TRACE
		void process_epsilon_transitions(const active_execution_state &x_s, outgoing_epsilon_transition_set_iterator epsilon_transition_begin, outgoing_epsilon_transition_set_iterator epsilon_transition_end, chart_item &v, ExtraInsertOp op, const std::wstring &epsilon_transition_type = L"")
#else
		void process_epsilon_transitions(const active_execution_state &x_s, outgoing_epsilon_transition_set_iterator epsilon_transition_begin, outgoing_epsilon_transition_set_iterator epsilon_transition_end, chart_item &v, ExtraInsertOp op)
#endif
		{
			for (; epsilon_transition_begin != epsilon_transition_end; ++epsilon_transition_begin)
			{
				std::pair<active_execution_state_set_const_iterator, bool> result(v.aess.insert(active_execution_state(static_cast<state_const_ref>(epsilon_transition_begin->target), x_s.b, x_s.q_h, x_s.i)));
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
        void process_epsilon_context_transitions(const active_execution_state &x_s, outgoing_epsilon_context_transition_set_iterator epsilon_context_transition_begin, outgoing_epsilon_context_transition_set_iterator epsilon_context_transition_end, chart_item &v, const u_context &c, ExtraInsertOp op)
        {
            for (; epsilon_context_transition_begin != epsilon_context_transition_end; ++epsilon_context_transition_begin)
            {
                if (epsilon_context_transition_begin->mask.match(c))
                {
                    std::pair<active_execution_state_set_const_iterator, bool> result(v.aess.insert(
                            active_execution_state(static_cast<state_const_ref>(epsilon_context_transition_begin->target),
                                                   x_s.b, x_s.q_h, x_s.i)));
                    if (result.second) {
#ifdef TRACE
                        result.first->serialize(std::wcout) <<
                            L" (";
                        epsilon_context_transition_begin->mask.wserialize_context_expression(std::wcout) <<
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
		void process_inserting_transitions(const active_execution_state &x_s, outgoing_inserting_transition_set_iterator inserting_transition_begin, outgoing_inserting_transition_set_iterator inserting_transition_end, chart_item &v, SourceRef in, ExtraInsertOp op, const std::wstring &inserting_transition_type = L"")
#else
		void process_inserting_transitions(const active_execution_state &x_s, outgoing_inserting_transition_set_iterator inserting_transition_begin, outgoing_inserting_transition_set_iterator inserting_transition_end, chart_item &v, SourceRef in, ExtraInsertOp op)
#endif
		{
			for (; inserting_transition_begin != inserting_transition_end; ++inserting_transition_begin)
			{
				blackboard b_t(x_s.b);
				std::pair<active_execution_state_set_const_iterator, bool> result(v.aess.insert(active_execution_state(static_cast<state_const_ref>(inserting_transition_begin->target), gamma(b_t, in, inserting_transition_begin->output), x_s.q_h, x_s.i)));
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
        void process_inserting_context_transitions(const active_execution_state &x_s, outgoing_inserting_context_transition_set_iterator inserting_context_transition_begin, outgoing_inserting_context_transition_set_iterator inserting_context_transition_end, chart_item &v, SourceRef in, const u_context &c, ExtraInsertOp op)
        {
            for (; inserting_context_transition_begin != inserting_context_transition_end; ++inserting_context_transition_begin)
            {
                if (inserting_context_transition_begin->mask.match(c))
                {
                    blackboard b_t(x_s.b);
                    std::pair<active_execution_state_set_const_iterator, bool> result(v.aess.insert(
                            active_execution_state(
                                    static_cast<state_const_ref>(inserting_context_transition_begin->target),
                                    gamma(b_t, in, inserting_context_transition_begin->output), x_s.q_h, x_s.i)));
                    if (result.second) {
#ifdef TRACE
                        result.first->serialize(std::wcout) <<
                            L" (";
                        inserting_context_transition_begin->mask.wserialize_context_expression(std::wcout) <<
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
		void eclosure(std::size_t idx, SourceRef in, bool next_token_isnt_white_separated, const u_context &c, ExtraInsertOp op, const blackboard &empty_blackboard)
		{
			chart_item &v = the_chart[idx];
			epsilon_completion_set t;

			//While there are execution states pending to be processed
			while (!e.empty())
			{
				//Pop next pending active execution state (q, b, lambda, q_h, j)
				const active_execution_state &x_s(*e.front());
				e.pop();

				//Process epsilon and inserting transitions
				process_epsilon_transitions(x_s, x_s.q->outgoing_epsilon_transitions.begin(), x_s.q->outgoing_epsilon_transitions.end(), v, op);
				process_inserting_transitions(x_s, x_s.q->outgoing_inserting_transitions.begin(), x_s.q->outgoing_inserting_transitions.end(), v, in, op);

                //Process epsilon and inserting context transitions
                process_epsilon_context_transitions(x_s, x_s.q->outgoing_epsilon_context_transitions.begin(), x_s.q->outgoing_epsilon_context_transitions.end(), v, c, op);
                process_inserting_context_transitions(x_s, x_s.q->outgoing_inserting_context_transitions.begin(), x_s.q->outgoing_inserting_context_transitions.end(), v, in, c, op);

				//Process no-blank epsilon and inserting transitions
				//if there are no whites between the current (or input begin) and the next token (or input end)
				if (next_token_isnt_white_separated)
				{
#ifdef TRACE
					process_epsilon_transitions(x_s, x_s.q->outgoing_no_blank_epsilon_transitions.begin(), x_s.q->outgoing_no_blank_epsilon_transitions.end(), v, op, L"no-blank ");
					process_inserting_transitions(x_s, x_s.q->outgoing_no_blank_inserting_transitions.begin(), x_s.q->outgoing_no_blank_inserting_transitions.end(), v, in, op, L"no-blank ");
#else
					process_epsilon_transitions(x_s, x_s.q->outgoing_no_blank_epsilon_transitions.begin(), x_s.q->outgoing_no_blank_epsilon_transitions.end(), v, op);
					process_inserting_transitions(x_s, x_s.q->outgoing_no_blank_inserting_transitions.begin(), x_s.q->outgoing_no_blank_inserting_transitions.end(), v, in, op);
#endif
				}

				//Process blank epsilon and inserting transitions otherwise
				else
				{
#ifdef TRACE
					process_epsilon_transitions(x_s, x_s.q->outgoing_blank_epsilon_transitions.begin(), x_s.q->outgoing_blank_epsilon_transitions.end(), v, op, L"blank ");
					process_inserting_transitions(x_s, x_s.q->outgoing_blank_inserting_transitions.begin(), x_s.q->outgoing_blank_inserting_transitions.end(), v, in, op, L"blank ");
#else
					process_epsilon_transitions(x_s, x_s.q->outgoing_blank_epsilon_transitions.begin(), x_s.q->outgoing_blank_epsilon_transitions.end(), v, op);
					process_inserting_transitions(x_s, x_s.q->outgoing_blank_inserting_transitions.begin(), x_s.q->outgoing_blank_inserting_transitions.end(), v, in, op);
#endif
				}

				//Process call-transitions; Earley's predictor
				for (outgoing_call_transition_set_iterator call_transition_begin(x_s.q->outgoing_call_transitions.begin()); call_transition_begin != x_s.q->outgoing_call_transitions.end(); ++call_transition_begin)
				{
					//New paused execution state (q_r, b, q_c, q_h, j)
					std::pair<paused_execution_state_set_const_iterator, bool> x_p_result(v.pess.insert(paused_execution_state(static_cast<state_const_ref>(call_transition_begin->target), x_s.b, static_cast<state_const_ref>(call_transition_begin->called), x_s.q_h, x_s.i)));
					if (x_p_result.second)
					{
#ifdef TRACE
						x_p_result.first->serialize(std::wcout) << L" paused" << std::endl;
#endif
						epsilon_completion_set_const_iterator qc_bfs_ref_it(t.lower_bound(epsilon_completion(static_cast<state_const_ref>(call_transition_begin->called))));
						if (qc_bfs_ref_it == t.end())
						{
							//New subanalysis active execution state (q_c, epsilon, lambda, q_c, k)
							std::pair<active_execution_state_set_const_iterator, bool> x_t_result(v.aess.insert(active_execution_state(static_cast<state_const_ref>(call_transition_begin->called), empty_blackboard, static_cast<state_const_ref>(call_transition_begin->called), idx)));
							if (x_t_result.second)
							{
								e.push(&(*x_t_result.first));
								op(*x_t_result.first);
#ifdef TRACE
								x_t_result.first->serialize(std::wcout) << L" subanalysis" << std::endl;
#endif
							}
						}
						//Epsilon-completions due to precedent pops in the same Earley chart item without input consumption
						else
						{
							//Add first epsilon completion
							blackboard b_t(x_s.b);
							std::pair<active_execution_state_set_const_iterator, bool> x_t_result(v.aess.insert(active_execution_state(static_cast<state_const_ref>(call_transition_begin->target), circ(b_t, *(qc_bfs_ref_it->b_ref)), x_s.q_h, x_s.i)));
							if (x_t_result.second)
							{
#ifdef TRACE
								x_t_result.first->serialize(std::wcout)  << L" epsilon-completion" << std::endl;
#endif
								e.push(&(*x_t_result.first));
								op(*x_t_result.first);
							}
							++qc_bfs_ref_it;
							//Add the remaining epsilon completions with insertion hint, since epsilon completions are sorted
							while (qc_bfs_ref_it != t.end() && qc_bfs_ref_it->q == call_transition_begin->called)
							{
								b_t = x_s.b;
								x_t_result = insert_and_report(v.aess, x_t_result.first, active_execution_state(static_cast<state_const_ref>(call_transition_begin->target), circ(b_t, *(qc_bfs_ref_it->b_ref)), x_s.q_h, x_s.i));
								if (x_t_result.second)
								{
#ifdef TRACE
									x_t_result.first->serialize(std::wcout)  << L" epsilon-completion" << std::endl;
#endif
									e.push(&(*x_t_result.first));
									op(*x_t_result.first);
								}
								++qc_bfs_ref_it;
							}
						}
					}
				}

				//Process pop-transition; Earley's completer
				if (x_s.q->is_final())
				{
					//Dummy paused execution state used as lower bound for the retrieval of every paused execution state having q_c == q_h
					dummy_x_p.q_c = x_s.q_h;
					paused_execution_state_set_iterator pk(the_chart[x_s.i].pess.lower_bound(dummy_x_p));

					//If this is a completion of a subanalysis, that is, there is at least one superanalysis depending on it (if not, there is nothing to be completed)
					if (pk != the_chart[x_s.i].pess.end() && pk->q_c == x_s.q_h)
					{
						//If this is an epsilon-completion, store epsilon translation for future completions within the same Earley chart item
						if (x_s.i == idx)
							t.insert(epsilon_completion(x_s.q_h, &x_s.b));

						//For each paused execution state (q', b', q_h, q_h', i) in V_j
						do
						{
							//New resumed execution state (q', b'*b, lambda, q_h', i)
							blackboard b_t(pk->b);
							std::pair<active_execution_state_set_const_iterator, bool> result(v.aess.insert(active_execution_state(pk->q, circ(b_t, x_s.b), pk->q_h, pk->i)));
							if (result.second)
							{
#ifdef TRACE
								result.first->serialize(std::wcout) << L" resumed" << std::endl;
#endif
								e.push(&(*result.first));
								op(*result.first);
							}
							++pk;
						}while (pk != the_chart[x_s.i].pess.end() && pk->q_c == x_s.q_h);
					}
				}
			}
		}


		//Earley scanner: adds a new item to the parsing chart and initializes it with the attainable set of execution states from the former last chart item set of execution states through the consumption of an input symbol sigma
		template<typename ExtraInsertOp>
		void translate_symbol(size_t idx, SourceRef in_i, ExtraInsertOp op)
		{
			chart_item &v = the_chart[idx];
			chart_item &w = the_chart[idx + 1];
			//For each (q, b, lambda, q_h, i) in v
			for (active_execution_state_set_const_iterator x_s_it(v.aess.begin()); x_s_it != v.aess.end(); ++x_s_it)
			{
				//For each (q', lambda) = delta(q, (sigma, epsilon))
				//Process deleting transitions
				for (outgoing_deleting_transition_set_const_iterator odt_it(x_s_it->q->outgoing_deleting_transitions.begin()); odt_it != x_s_it->q->outgoing_deleting_transitions.end(); ++odt_it)
				{
					if (input_match(*in_i, odt_it->input))
					{
						//w = w union (q', b, lambda, q_h, i)
						std::pair<active_execution_state_set_const_iterator, bool> result(w.aess.insert(active_execution_state(static_cast<state_const_ref>(odt_it->target), x_s_it->b, x_s_it->q_h, x_s_it->i)));
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
				for (outgoing_translating_transition_set_const_iterator ott_it(x_s_it->q->outgoing_translating_transitions.begin()); ott_it != x_s_it->q->outgoing_translating_transitions.end(); ++ott_it)
				{
					if (input_match(*in_i, ott_it->input))
					{
						//w = w union (q', bg, lambda, q_h, i)
						blackboard b_t(x_s_it->b);
						std::pair<active_execution_state_set_const_iterator, bool> result(w.aess.insert(active_execution_state(static_cast<state_const_ref>(ott_it->target), gamma(b_t, in_i, ott_it->output), x_s_it->q_h, x_s_it->i)));
						if (result.second)
						{
#ifdef TRACE
							result.first->serialize(std::wcout) << L" (";
							input_serializer()(std::wcout, *in_i) << L" : ";
							tag_output_serializer()(std::wcout, ott_it->output) << L')' << std::endl;
#endif
							e.push(&(*result.first));
							op(*result.first);
						}
					}
				}
			}
		}

		//Build V_0 as the eclosure of Q X {b_emptyset} X {lambda};
		template<typename ExtraInsertOp>
		void build_initial_ses(state_const_ref initial_state, bool hasnt_white_at_begin, ExtraInsertOp op, const blackboard &empty_blackboard)
		{
#ifdef TRACE
			std::wcout << L"----- V[0] -----" << std::endl;
#endif
			std::pair<active_execution_state_set_iterator, bool> result(the_chart[0].aess.insert(active_execution_state(initial_state, empty_blackboard, initial_state, 0)));
			e.push(&(*result.first));
			op(*result.first);
#ifdef TRACE
			result.first->serialize(std::wcout) << L" initial" << std::endl;
#endif
		}

		//Compute the r-translations of the input range [input_being, input_end) and add them to the set t
		blackboard_set& operator()(const machine& grammar, SourceRef input_begin, SourceRef input_end, bool hasnt_white_at_begin, bool hasnt_white_at_end, const u_context &c, blackboard_set& t, const blackboard &empty_blackboard = blackboard())
		{
#ifdef TRACE
			std::wcout << L"Begin parsing\n";
#endif
			//Initialize chart
			std::size_t chart_size(std::distance(input_begin, input_end) + 1);
			the_chart.reset(chart_size);

			no_op_on_execution_state no_op;
			acceptor_execution_state_inserter ins_op(t, grammar.initial_state());

			//Build V_0 as the closure of {(q, epsilon, lambda, q, 0) | q in Q_I};
			//If empty input, build initial and final V[0]
			if (input_begin == input_end)
			{
				build_initial_ses(grammar.initial_state(), hasnt_white_at_begin, ins_op, empty_blackboard);
				//First token is white separated if there are trailing whites at the beginning
				eclosure(0, input_begin, hasnt_white_at_begin, c, ins_op, empty_blackboard);
			}
			//Else build initial V[0] and the remaining V[i]
			else
			{
				build_initial_ses(grammar.initial_state(), hasnt_white_at_begin, no_op, empty_blackboard);
				//First token is white separated if there are trailing whites at the beginning
				eclosure(0, input_begin, hasnt_white_at_begin, c, no_op, empty_blackboard);

				std::size_t idx(0);
				//While the last chart item active set of execution states is not empty and there are input symbols left, compute the next chart item
				std::size_t last_idx(chart_size - 2);
				SourceRef input_begin_plus_1(input_begin);
				while (!the_chart[idx].aess.empty() && idx < last_idx)
				{
#ifdef TRACE
					std::wcout << "----- V[" << static_cast<int>(idx) + 1 << "] -----" << std::endl;
#endif
					++input_begin_plus_1;
					translate_symbol(idx, input_begin, no_op);
					++idx;
					eclosure(idx, input_begin_plus_1, (*input_begin)->end == (*input_begin_plus_1)->begin, c, no_op, empty_blackboard);
					++input_begin;
				}

				//Compute last chart item
				if (!the_chart[idx].aess.empty())
				{
#ifdef TRACE
					std::wcout << "----- V[" << static_cast<int>(idx) + 1 << "] -----" << std::endl;
#endif
					++input_begin_plus_1;
					translate_symbol(idx, input_begin, ins_op);
					++idx;
					//Next token is the input end... it is white separated if there are trailing whites at the end
					eclosure(idx, input_begin_plus_1, hasnt_white_at_end, c, ins_op, empty_blackboard);
					++input_begin;
				}
			}
			the_chart.reset();
#ifdef TRACE
			std::wcout << L"End parsing\n";
#endif
			return t;
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_EARLEY_PARSER_H*/
