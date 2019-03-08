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

#ifndef GRAPENLP_TO_FPRTN_TOP_PARSER_H
#define GRAPENLP_TO_FPRTN_TOP_PARSER_H

#ifdef TRACE
#include <iostream>
#include <fstream>
#endif

#include <list>
#include <queue>
#include <memory>
#include <limits>

#include <grapenlp/set_impl_selector.h>
#include <grapenlp/tag_input_traits.h>
#include <grapenlp/u_context_mask.h>
#include <grapenlp/rtno.h>
#include <grapenlp/output_fprtn_top_prune.h>

#ifdef TRACE
#include <grapenlp/output_fprtn_to_dot_serializer.h>
#include <grapenlp/inv_output_fprtn_to_dot_serializer.h>
#endif

namespace grapenlp
{
	template<typename TagInput, typename TagOutput, typename SourceRef, assoc_container_impl_choice execution_state_set_impl_choice>
	struct to_fprtn_top_parser
	{
		typedef TagInput tag_input;
		typedef TagOutput tag_output;
		typedef SourceRef source_ref;
		typedef typename source_ref::value_type input;

#ifdef TRACE
		typedef typename tag_serializer<input>::type input_serializer;
		typedef typename tag_serializer<tag_input>::type tag_input_serializer;
		typedef typename tag_serializer<tag_output>::type tag_output_serializer;
		typedef ns_rtno<tag_input, tag_output, u_context_mask> in_machine;
#else
		typedef rtno<tag_input, tag_output, u_context_mask> in_machine;
#endif
		typedef typename tag_input_traits<tag_input>::match match;
		typedef typename in_machine::state in_state;
		typedef typename in_machine::state_ref in_state_ref;
		typedef typename in_machine::state_const_ref in_state_const_ref;
		typedef typename in_machine::state_ref_list_const_iterator in_state_ref_list_const_iterator;

		typedef	typename in_machine::outgoing_epsilon_transition in_outgoing_epsilon_transition;
		typedef	typename in_machine::outgoing_epsilon_transition_set in_outgoing_epsilon_transition_set;
		typedef typename in_outgoing_epsilon_transition_set::iterator in_outgoing_epsilon_transition_set_iterator;
		typedef typename in_outgoing_epsilon_transition_set::const_iterator in_outgoing_epsilon_transition_set_const_iterator;

        typedef	typename in_machine::outgoing_epsilon_context_transition in_outgoing_epsilon_context_transition;
        typedef	typename in_machine::outgoing_epsilon_context_transition_set in_outgoing_epsilon_context_transition_set;
        typedef typename in_outgoing_epsilon_context_transition_set::iterator in_outgoing_epsilon_context_transition_set_iterator;
        typedef typename in_outgoing_epsilon_context_transition_set::const_iterator in_outgoing_epsilon_context_transition_set_const_iterator;

		typedef	typename in_machine::outgoing_deleting_transition in_outgoing_deleting_transition;
		typedef	typename in_machine::outgoing_deleting_transition_set in_outgoing_deleting_transition_set;
		typedef typename in_outgoing_deleting_transition_set::iterator in_outgoing_deleting_transition_set_iterator;
		typedef typename in_outgoing_deleting_transition_set::const_iterator in_outgoing_deleting_transition_set_const_iterator;

		typedef	typename in_machine::outgoing_translating_transition in_outgoing_translating_transition;
		typedef	typename in_machine::outgoing_translating_transition_set in_outgoing_translating_transition_set;
		typedef typename in_outgoing_translating_transition_set::iterator in_outgoing_translating_transition_set_iterator;
		typedef typename in_outgoing_translating_transition_set::const_iterator in_outgoing_translating_transition_set_const_iterator;

		typedef	typename in_machine::outgoing_inserting_transition in_outgoing_inserting_transition;
		typedef	typename in_machine::outgoing_inserting_transition_set in_outgoing_inserting_transition_set;
		typedef typename in_outgoing_inserting_transition_set::iterator in_outgoing_inserting_transition_set_iterator;
		typedef typename in_outgoing_inserting_transition_set::const_iterator in_outgoing_inserting_transition_set_const_iterator;

        typedef	typename in_machine::outgoing_inserting_context_transition in_outgoing_inserting_context_transition;
        typedef	typename in_machine::outgoing_inserting_context_transition_set in_outgoing_inserting_context_transition_set;
        typedef typename in_outgoing_inserting_context_transition_set::iterator in_outgoing_inserting_context_transition_set_iterator;
        typedef typename in_outgoing_inserting_context_transition_set::const_iterator in_outgoing_inserting_context_transition_set_const_iterator;

		typedef	typename in_machine::outgoing_call_transition in_outgoing_call_transition;
		typedef	typename in_machine::outgoing_call_transition_set in_outgoing_call_transition_set;
		typedef typename in_outgoing_call_transition_set::iterator in_outgoing_call_transition_set_iterator;
		typedef typename in_outgoing_call_transition_set::const_iterator in_outgoing_call_transition_set_const_iterator;

		typedef typename output_fprtn_top<u_context_mask, SourceRef, TagOutput, TagInput, execution_state_set_impl_choice>::type out_machine;
		typedef typename out_machine::chart_item chart_item;
		typedef typename out_machine::state out_state;
		typedef typename out_machine::state_ref out_state_ref;
		typedef typename out_machine::state_ref_queue out_state_ref_queue;
		typedef typename out_machine::state_const_ref out_state_const_ref;
		typedef typename out_machine::state_map out_state_map;
		typedef typename out_state_map::iterator out_state_map_iterator;
		typedef typename out_state_map::const_iterator out_state_map_const_iterator;

		typedef typename out_machine::paused_execution_state_key paused_execution_state_key;
		typedef typename out_machine::paused_execution_state paused_execution_state;
		typedef typename paused_execution_state::map paused_execution_state_map;
		typedef typename paused_execution_state_map::iterator paused_execution_state_map_iterator;
		typedef typename paused_execution_state_map::const_iterator paused_execution_state_map_const_iterator;

		typedef typename weighted_tag_output_traits<tag_output>::weight weight;

		struct acceptor_execution_state_inserter
		{
			out_state &global_acceptor_state;
			in_state_const_ref in_initial_state;
			paused_execution_state_map_iterator ini_call_pes_it;

			acceptor_execution_state_inserter(out_state &global_acceptor_state_, in_state_const_ref in_initial_state_, paused_execution_state_map_iterator ini_call_pes_it_): global_acceptor_state(global_acceptor_state_), in_initial_state(in_initial_state_), ini_call_pes_it(ini_call_pes_it_)
			{}

			void operator()(out_state &x)
			{
				if (x.first.i == 0 && x.is_final() && x.first.q_h == in_initial_state)
				{
					x.add_filtered_pop_transition(&global_acceptor_state, ini_call_pes_it);
#ifdef TRACE
					std::wcout << L"added filtered pop transition from " << x.second.wlabel() << " to global acceptor state" << std::endl;
#endif
				}
			}
		};

		struct no_op_on_execution_state
		{
			void operator()(__attribute__((unused)) out_state &x) const
			{}
		};

		//Epsilon-completion: triplet (q_c, r_c, r_f) where q_c is a deletable state (call to q_c is completed without input consumption),
		//r_c is the output state to be called (corresponding to the deletable called state)
		//and the r_f is a final output state from where the call is epsilon-completed
		struct epsilon_completion
		{
			typedef lrb_tree_set<epsilon_completion> set;

			in_state_const_ref q_c;
			out_state_ref r_c;
			out_state_ref r_f;

			epsilon_completion(in_state_const_ref q_c_, out_state_ref r_c_, out_state_ref r_f_): q_c(q_c_), r_c(r_c_), r_f(r_f_)
			{}

			bool operator< (const epsilon_completion &ec) const
			{
				if (q_c < ec.q_c)
					return true;
				if (ec.q_c < q_c)
					return false;
				if (r_c < ec.r_c)
					return true;
				if (ec.r_c < r_c)
					return false;
				return r_f < ec.r_f;
			}
		};

		typedef typename epsilon_completion::set epsilon_completion_set;
		typedef typename epsilon_completion_set::iterator epsilon_completion_set_iterator;
		typedef typename epsilon_completion_set::const_iterator epsilon_completion_set_const_iterator;

		match input_match;
		out_state_ref_queue e;
		//Dummy paused execution state used as lower bound for the retrieval of every paused execution state having q_c == q_h
		paused_execution_state_key dummy_x_p_key;
		epsilon_completion dummy_e_comp;

		to_fprtn_top_parser(): input_match(), e(), dummy_x_p_key(NULL, NULL, NULL, NULL, 0), dummy_e_comp(NULL, NULL, NULL)
		{}
		to_fprtn_top_parser(match input_match_): input_match(input_match_), e(), dummy_x_p_key(NULL, NULL, NULL, NULL, 0), dummy_e_comp(NULL, NULL, NULL)
		{}

		template<typename ExtraInsertOp>
#ifdef TRACE
		void process_epsilon_transitions(out_state &x_s, in_outgoing_epsilon_transition_set_iterator epsilon_transition_begin, in_outgoing_epsilon_transition_set_iterator epsilon_transition_end, chart_item &v, SourceRef in, out_machine &out, ExtraInsertOp op, const char *epsilon_transition_type = "")
#else
		void process_epsilon_transitions(out_state &x_s, in_outgoing_epsilon_transition_set_iterator epsilon_transition_begin, in_outgoing_epsilon_transition_set_iterator epsilon_transition_end, chart_item &v, SourceRef in, out_machine &out, ExtraInsertOp op)
#endif
		{
			for (; epsilon_transition_begin != epsilon_transition_end; ++epsilon_transition_begin)
			{
				std::pair<out_state_map_iterator, bool> result(v.create_other_state(static_cast<in_state_const_ref>(epsilon_transition_begin->target), x_s.first.q_h, x_s.first.i, in));
//				std::pair<out_state_map_iterator, bool> result(v.create_other_state(static_cast<in_state_const_ref>(epsilon_transition_begin->target), x_s.first.q_h, x_s.first.i));
				//an e-trans from x_s to x_t can only be added once, since the RTNO has a unique e2-trans from q_s to q_t
				x_s.add_epsilon_transition(static_cast<out_state_ref>(&(*result.first)));
				if (result.second)
				{
//					static_cast<out_state&>(*result.first).set_mapped(in);
#ifdef TRACE
					static_cast<out_state&>(*result.first).serialize_earley_exe_state(std::wcout) << " (" << epsilon_transition_type << "<E> : <E>)" << std::endl;
#endif
					e.push(static_cast<out_state_ref>(&(*result.first)));
					op(static_cast<out_state&>(*result.first));
				}
			}
		}

        template<typename ExtraInsertOp>
        void process_epsilon_context_transitions(out_state &x_s, in_outgoing_epsilon_context_transition_set_iterator epsilon_context_transition_begin, in_outgoing_epsilon_context_transition_set_iterator epsilon_context_transition_end, chart_item &v, SourceRef in, const u_context &c, out_machine &out, ExtraInsertOp op)
        {
            for (; epsilon_context_transition_begin != epsilon_context_transition_end; ++epsilon_context_transition_begin)
            {
                if (epsilon_context_transition_begin->mask.match(c))
                {
                    std::pair<out_state_map_iterator, bool> result(v.create_other_state(
                            static_cast<in_state_const_ref>(epsilon_context_transition_begin->target), x_s.first.q_h,
                            x_s.first.i, in));
//	    			std::pair<out_state_map_iterator, bool> result(v.create_other_state(static_cast<in_state_const_ref>(epsilon_transition_begin->target), x_s.first.q_h, x_s.first.i));
                    //an e-trans from x_s to x_t can only be added once, since the RTNO has a unique e2-trans from q_s to q_t
                    x_s.add_epsilon_transition(static_cast<out_state_ref>(&(*result.first)));
                    if (result.second) {
//	    				static_cast<out_state&>(*result.first).set_mapped(in);
#ifdef TRACE
                        static_cast<out_state &>(*result.first).serialize_earley_exe_state(std::wcout) <<
                            L" (";
                        epsilon_context_transition_begin->mask.wserialize_context_expression(std::wcout) <<
                            L" : <E>)" <<
                            std::endl;
#endif
                        e.push(static_cast<out_state_ref>(&(*result.first)));
                        op(static_cast<out_state &>(*result.first));
                    }
                }
            }
        }

		template<typename ExtraInsertOp>
#ifdef TRACE
		void process_inserting_transitions(out_state &x_s, in_outgoing_inserting_transition_set_iterator inserting_transition_begin, in_outgoing_inserting_transition_set_iterator inserting_transition_end, chart_item &v, SourceRef in, out_machine &out, ExtraInsertOp op, const char *inserting_transition_type = "")
#else
		void process_inserting_transitions(out_state &x_s, in_outgoing_inserting_transition_set_iterator inserting_transition_begin, in_outgoing_inserting_transition_set_iterator inserting_transition_end, chart_item &v, SourceRef in, out_machine &out, ExtraInsertOp op)
#endif
		{
			for (; inserting_transition_begin != inserting_transition_end; ++inserting_transition_begin)
			{
				std::pair<out_state_map_iterator, bool> result(v.create_other_state(static_cast<in_state_const_ref>(inserting_transition_begin->target), x_s.first.q_h, x_s.first.i, in));
//				std::pair<out_state_map_iterator, bool> result(v.create_other_state(static_cast<in_state_const_ref>(inserting_transition_begin->target), x_s.first.q_h, x_s.first.i));
				//The same consuming transition might be added twice due to two translating transitions from q_s to q_t having different input but the same output
				//However, the probability is low and this does not break further processing, just will waste time repeating the same transition processing
				//However, this time is meaningless in comparison with the time of storing transitions in set structures instead of lists
				x_s.add_consuming_transition(inserting_transition_begin->output, static_cast<out_state_ref>(&(*result.first)));
				if (result.second)
				{
//					static_cast<out_state&>(*result.first).set_mapped(in);
#ifdef TRACE
					static_cast<out_state&>(*result.first).serialize_earley_exe_state(std::wcout) << " (" << inserting_transition_type << "<E> : ";
					tag_output_serializer()(std::wcout, inserting_transition_begin->output) << ')' << std::endl;
#endif
					e.push(static_cast<out_state_ref>(&(*result.first)));
					op(static_cast<out_state&>(*result.first));
				}
			}
		}

        template<typename ExtraInsertOp>
        void process_inserting_context_transitions(out_state &x_s, in_outgoing_inserting_context_transition_set_iterator inserting_context_transition_begin, in_outgoing_inserting_context_transition_set_iterator inserting_context_transition_end, chart_item &v, SourceRef in, const u_context &c, out_machine &out, ExtraInsertOp op)
        {
            for (; inserting_context_transition_begin != inserting_context_transition_end; ++inserting_context_transition_begin)
            {
                if (inserting_context_transition_begin->mask.match(c))
                {
                   std::pair<out_state_map_iterator, bool> result(v.create_other_state(static_cast<in_state_const_ref>(inserting_context_transition_begin->target), x_s.first.q_h, x_s.first.i, in));
//	    			std::pair<out_state_map_iterator, bool> result(v.create_other_state(static_cast<in_state_const_ref>(inserting_transition_begin->target), x_s.first.q_h, x_s.first.i));
                    //The same consuming transition might be added twice due to two translating transitions from q_s to q_t having different input but the same output
                    //However, the probability is low and this does not break further processing, just will waste time repeating the same transition processing
                    //However, this time is meaningless in comparison with the time of storing transitions in set structures instead of lists
                    x_s.add_consuming_transition(inserting_context_transition_begin->output, static_cast<out_state_ref>(&(*result.first)));
                    if (result.second)
                    {
//					    static_cast<out_state&>(*result.first).set_mapped(in);
#ifdef TRACE
                        static_cast<out_state &>(*result.first).serialize_earley_exe_state(std::wcout) <<
                            L" (";
                        inserting_context_transition_begin->mask.wserialize_context_expression(std::wcout) <<
                            L" : ";
                        tag_output_serializer()(std::wcout, inserting_context_transition_begin->output) << ')' << std::endl;
#endif
                        e.push(static_cast<out_state_ref>(&(*result.first)));
                        op(static_cast<out_state&>(*result.first));
                    }
                }
            }
        }

		//Increment parsing chart with the epsilon-closure of the last active set of execution states
		template<typename ExtraInsertOp>
		void eclosure(std::size_t idx, SourceRef in, bool next_token_isnt_white_separated, const u_context &c, out_machine& out, ExtraInsertOp op)
		{
			chart_item &v = out.the_chart[idx];
			epsilon_completion_set t;
			out_state_ref x_s_ref;

			//While there are execution states pending to be processed
			while (!e.empty())
			{
				//Pop next pending active execution state (q, r, lambda, q_h, j)
				x_s_ref = e.front();
				e.pop();

				//Process epsilon and inserting transitions
				process_epsilon_transitions(*x_s_ref, x_s_ref->first.q->outgoing_epsilon_transitions.begin(), x_s_ref->first.q->outgoing_epsilon_transitions.end(), v, in, out, op);
                process_epsilon_context_transitions(*x_s_ref, x_s_ref->first.q->outgoing_epsilon_context_transitions.begin(), x_s_ref->first.q->outgoing_epsilon_context_transitions.end(), v, in, c, out, op);

                //Process epsilon and inserting context transitions
				process_inserting_transitions(*x_s_ref, x_s_ref->first.q->outgoing_inserting_transitions.begin(), x_s_ref->first.q->outgoing_inserting_transitions.end(), v, in, out, op);
                process_inserting_context_transitions(*x_s_ref, x_s_ref->first.q->outgoing_inserting_context_transitions.begin(), x_s_ref->first.q->outgoing_inserting_context_transitions.end(), v, in, c, out, op);

				//Process no-blank epsilon and inserting transitions
				//if there are no whites between the current (or input begin) and the next token (or input end)
				if (next_token_isnt_white_separated)
				{
#ifdef TRACE
					process_epsilon_transitions(*x_s_ref, x_s_ref->first.q->outgoing_no_blank_epsilon_transitions.begin(), x_s_ref->first.q->outgoing_no_blank_epsilon_transitions.end(), v, in, out, op, "no-blank ");
					process_inserting_transitions(*x_s_ref, x_s_ref->first.q->outgoing_no_blank_inserting_transitions.begin(), x_s_ref->first.q->outgoing_no_blank_inserting_transitions.end(), v, in, out, op, "no-blank ");
#else
					process_epsilon_transitions(*x_s_ref, x_s_ref->first.q->outgoing_no_blank_epsilon_transitions.begin(), x_s_ref->first.q->outgoing_no_blank_epsilon_transitions.end(), v, in, out, op);
					process_inserting_transitions(*x_s_ref, x_s_ref->first.q->outgoing_no_blank_inserting_transitions.begin(), x_s_ref->first.q->outgoing_no_blank_inserting_transitions.end(), v, in, out, op);
#endif
				}

				//Process blank epsilon and inserting transitions otherwise
				else
				{
#ifdef TRACE
					process_epsilon_transitions(*x_s_ref, x_s_ref->first.q->outgoing_blank_epsilon_transitions.begin(), x_s_ref->first.q->outgoing_blank_epsilon_transitions.end(), v, in, out, op, "blank ");
					process_inserting_transitions(*x_s_ref, x_s_ref->first.q->outgoing_blank_inserting_transitions.begin(), x_s_ref->first.q->outgoing_blank_inserting_transitions.end(), v, in, out, op, "blank ");
#else
					process_epsilon_transitions(*x_s_ref, x_s_ref->first.q->outgoing_blank_epsilon_transitions.begin(), x_s_ref->first.q->outgoing_blank_epsilon_transitions.end(), v, in, out, op);
					process_inserting_transitions(*x_s_ref, x_s_ref->first.q->outgoing_blank_inserting_transitions.begin(), x_s_ref->first.q->outgoing_blank_inserting_transitions.end(), v, in, out, op);
#endif
				}

				//Process call-transitions; Earley's predictor
				for (in_outgoing_call_transition_set_iterator call_transition_begin(x_s_ref->first.q->outgoing_call_transitions.begin()); call_transition_begin != x_s_ref->first.q->outgoing_call_transitions.end(); ++call_transition_begin)
				{
					//New paused execution state (q_r, r, q_c, q_h, j)
					std::pair<paused_execution_state_map_iterator, bool> x_p_result(v.pess.insert(paused_execution_state(static_cast<in_state_const_ref>(call_transition_begin->target), x_s_ref, static_cast<in_state_const_ref>(call_transition_begin->called), x_s_ref->first.q_h, x_s_ref->first.i)));
					if (x_p_result.second)
					{
						paused_execution_state_map_iterator previous_x_p, next_x_p;
						//The first paused execution state created in a SES V_j for a given (q, q_c, q_h, i) is the filtered pop transition creator
						//(what may vary is r, the source FPRTN state of the call)
						x_p_result.first->second.is_filtered_popping_transition_creator =
							//No other paused ESs like this one after this one
							((++(next_x_p = x_p_result.first)) == v.pess.end() ||
							next_x_p->first.q != x_p_result.first->first.q ||
							next_x_p->first.q_c != x_p_result.first->first.q_c ||
							next_x_p->first.q_h != x_p_result.first->first.q_h ||
							next_x_p->first.i != x_p_result.first->first.i)
							&&
							//No other paused ESs like this one before this one
							//(probably new paused ESs like this one will go after,
							//since r will be allocated in a greater memory position,
							//but that's not for sure since a lower memory position
							//big enough to hold r might have been freed)
							(x_p_result.first == v.pess.begin() ||
							(--(previous_x_p = x_p_result.first))->first.q != x_p_result.first->first.q ||
							previous_x_p->first.q_c != x_p_result.first->first.q_c ||
							previous_x_p->first.q_h != x_p_result.first->first.q_h ||
							previous_x_p->first.i != x_p_result.first->first.i);
						dummy_e_comp.q_c = static_cast<in_state_const_ref>(call_transition_begin->called);
						epsilon_completion_set_iterator e_comp_it(t.lower_bound(dummy_e_comp));
						if (e_comp_it == t.end() || e_comp_it->q_c != call_transition_begin->called)
						{
							//New subanalysis active execution state (q_c, epsilon, lambda, q_c, k)
							std::pair<out_state_map_iterator, bool> x_t_result(v.create_other_state(static_cast<in_state_const_ref>(call_transition_begin->called), static_cast<in_state_const_ref>(call_transition_begin->called), idx, in));
//							std::pair<out_state_map_iterator, bool> x_t_result(v.create_other_state(static_cast<in_state_const_ref>(call_transition_begin->called), static_cast<in_state_const_ref>(call_transition_begin->called), idx));
							//We do not define the call transition yet since the target state of this call transition does not exist yet: it is created once the call is completed
							//Register the call state for the creation of the call transition once the call will be completed
							x_p_result.first->second.r_c = static_cast<out_state_ref>(&(*x_t_result.first));
							if (x_t_result.second)
							{
//								static_cast<out_state&>(*x_t_result.first).set_mapped(in);
								e.push(static_cast<out_state_ref>(&(*x_t_result.first)));
								op(static_cast<out_state&>(*x_t_result.first));
#ifdef TRACE
								static_cast<paused_execution_state&>(*x_p_result.first).serialize(std::wcout) << " paused" << std::endl;
								static_cast<out_state&>(*x_t_result.first).serialize_earley_exe_state(std::wcout) << " subanalysis" << std::endl;
#endif
							}
							//Register the call state for the creation of the call transition once the call will be completed
							else
							{
#ifdef TRACE
								static_cast<paused_execution_state&>(*x_p_result.first).serialize(std::wcout) << " paused" << std::endl;
								static_cast<out_state&>(*x_t_result.first).serialize_earley_exe_state(std::wcout << L"subanalysis already existent: ") << std::endl;
#endif
							}
						}
						//Epsilon-completions due to precedent pops in the same Earley chart item without input consumption
						else
						{
							x_p_result.first->second.r_c = e_comp_it->r_c;
#ifdef TRACE
							static_cast<paused_execution_state&>(*x_p_result.first).serialize(std::wcout) << " paused" << std::endl;
#endif
							std::pair<out_state_map_iterator, bool> x_t_result(v.create_other_state(static_cast<in_state_const_ref>(call_transition_begin->target), x_s_ref->first.q_h, x_s_ref->first.i, in));
//							std::pair<out_state_map_iterator, bool> x_t_result(v.create_other_state(static_cast<in_state_const_ref>(call_transition_begin->target), x_s_ref->first.q_h, x_s_ref->first.i));
							//Add next call transition and register x_p's completion
							//In this case, this x_p's completion is surely the first one
							//(the e-completer completes only new paused ESs for a call that has previously been e-completed)
							//Therefore, the call transition is unconditionally added and x_p's completion registered
							x_s_ref->add_call_transition(e_comp_it->r_c, static_cast<out_state_ref>(&(*x_t_result.first)));
							if (x_t_result.second)
							{
//								static_cast<out_state&>(*x_t_result.first).set_mapped(in);
#ifdef TRACE
								static_cast<out_state&>(*x_t_result.first).serialize_earley_exe_state(std::wcout) << " e-resumed" << std::endl;
#endif
								x_p_result.first->second.last_resumed_index = idx;
								if (x_p_result.first->second.is_filtered_popping_transition_creator)
									for (;e_comp_it != t.end() && e_comp_it->q_c == call_transition_begin->called; ++e_comp_it)
										e_comp_it->r_f->add_filtered_pop_transition(static_cast<out_state_ref>(&(*x_t_result.first)), x_p_result.first);
								e.push(static_cast<out_state_ref>(&(*x_t_result.first)));
								op(static_cast<out_state&>(*x_t_result.first));
							}
							else
							{
#ifdef TRACE
								static_cast<out_state&>(*x_t_result.first).serialize_earley_exe_state(std::wcout) << "e-resumed already existent" << std::endl;
#endif
								x_p_result.first->second.last_resumed_index = idx;
								if (x_p_result.first->second.is_filtered_popping_transition_creator)
									for (;e_comp_it != t.end() && e_comp_it->q_c == call_transition_begin->called; ++e_comp_it)
										e_comp_it->r_f->add_filtered_pop_transition(static_cast<out_state_ref>(&(*x_t_result.first)), x_p_result.first);
							}
						}
					}
				}

				//Process pop-transition; Earley's completer
				if (x_s_ref->is_final())
				{
					//Dummy paused execution state used as lower bound for the retrieval of every paused execution state having q_c == q_h
					dummy_x_p_key.q_c = x_s_ref->first.q_h;
					paused_execution_state_map_iterator x_p_it(out.the_chart[x_s_ref->first.i].pess.lower_bound(dummy_x_p_key));

					//If this is a completion of a subanalysis, that is, there is at least one superanalysis depending on it (if not, there is nothing to be completed)
					if (x_p_it != out.the_chart[x_s_ref->first.i].pess.end() && x_p_it->first.q_c == x_s_ref->first.q_h)
					{
						//If this is an epsilon-completion, store epsilon translation for future completions within the same Earley chart item
						if (x_s_ref->first.i == idx)
						{
#ifdef TRACE
							x_s_ref->first.q_h->serialize(std::wcout, L'q') << " is deletable\n";
#endif
							t.insert(epsilon_completion(x_s_ref->first.q_h, x_p_it->second.r_c, x_s_ref));
						}

						//For each paused execution state (q', r', q_h, q_h', i) in V_j
						do
						{
							//New resumed execution state (q', r_t, lambda, q_h', i)
							std::pair<out_state_map_iterator, bool> x_t_result(v.create_other_state(x_p_it->first.q, x_p_it->first.q_h, x_p_it->first.i, in));
//							std::pair<out_state_map_iterator, bool> x_t_result(v.create_other_state(x_p_it->first.q, x_p_it->first.q_h, x_p_it->first.i));
							if (x_t_result.second)
							{
//								static_cast<out_state&>(*x_t_result.first).set_mapped(in);
#ifdef TRACE
								static_cast<paused_execution_state&>(*x_p_it).serialize(std::wcout) << " resumed as ";
								static_cast<out_state&>(*x_t_result.first).serialize_earley_exe_state(std::wcout) << std::endl;
#endif
								//add new call transition and register x_p's completion
								x_p_it->first.r->add_call_transition(x_p_it->second.r_c, static_cast<out_state_ref>(&(*x_t_result.first)));
								x_p_it->second.last_resumed_index = idx;
								if (x_p_it->second.is_filtered_popping_transition_creator)
									x_s_ref->add_filtered_pop_transition(static_cast<out_state_ref>(&(*x_t_result.first)), x_p_it);
								e.push(static_cast<out_state_ref>(&(*x_t_result.first)));
								op(static_cast<out_state&>(*x_t_result.first));
							}
							else
							{
#ifdef TRACE
								static_cast<paused_execution_state&>(*x_p_it).serialize(std::wcout) << " resumed (already existent) as ";
								static_cast<out_state&>(*x_t_result.first).serialize_earley_exe_state(std::wcout) << std::endl;
#endif
								//If x_p has not been resumed yet during the computation of this eclosure
								//add new call transition and register x_p's completion
								if (x_p_it->second.last_resumed_index != idx)
								{
									x_p_it->first.r->add_call_transition(x_p_it->second.r_c, static_cast<out_state_ref>(&(*x_t_result.first)));
									x_p_it->second.last_resumed_index = idx;
								}
								if (x_p_it->second.is_filtered_popping_transition_creator)
									x_s_ref->add_filtered_pop_transition(static_cast<out_state_ref>(&(*x_t_result.first)), x_p_it);
							}
							++x_p_it;
						}while (x_p_it != out.the_chart[x_s_ref->first.i].pess.end() && x_p_it->first.q_c == x_s_ref->first.q_h);
					}
				}
			}
		}


		//Earley scanner: adds a new item to the parsing chart and initializes it with the attainable set of execution states from the former last chart item set of execution states through the consumption of an input symbol sigma
		template<typename ExtraInsertOp>
		void translate_symbol(size_t idx, SourceRef in_i, SourceRef in_j, out_machine& out, ExtraInsertOp op)
		{
			chart_item &v(out.the_chart[idx]);
			chart_item &w(out.the_chart[idx + 1]);

			//For each (q, r, lambda, q_h, i) in v
			for (out_state_map_iterator x_s_it(v.other_states.begin()); x_s_it != v.other_states.end(); ++x_s_it)
			{
				//For each (q', lambda) = delta(q, (sigma, epsilon))
				//Process deleting transitions
				for (in_outgoing_deleting_transition_set_const_iterator dt_it(x_s_it->first.q->outgoing_deleting_transitions.begin()); dt_it != x_s_it->first.q->outgoing_deleting_transitions.end(); ++dt_it)
				{
					if (input_match(*in_i, dt_it->input))
					{
						//w = w union (q', r, lambda, q_h, i)
						std::pair<out_state_map_iterator, bool> result(w.create_other_state(static_cast<in_state_const_ref>(dt_it->target), x_s_it->first.q_h, x_s_it->first.i, in_j));
//						std::pair<out_state_map_iterator, bool> result(w.create_other_state(static_cast<in_state_const_ref>(dt_it->target), x_s_it->first.q_h, x_s_it->first.i));
						if (result.second)
						{
//							static_cast<out_state&>(*result.first).set_mapped(in_j);
#ifdef TRACE
							static_cast<out_state&>(*result.first).serialize_earley_exe_state(std::wcout) << " (";
							input_serializer()(std::wcout, *in_i) << " : <E>)" << std::endl;
#endif
							static_cast<out_state&>(*x_s_it).add_epsilon_transition(static_cast<out_state_ref>(&(*result.first)));
							e.push(static_cast<out_state_ref>(&(*result.first)));
							op(static_cast<out_state&>(*result.first));
						}
						else static_cast<out_state&>(*x_s_it).add_epsilon_transition(static_cast<out_state_ref>(&(*result.first)));
					}
				}
				//For each (q', lambda) = delta(q, (sigma, g))
				//Process translating transitions
				for (in_outgoing_translating_transition_set_const_iterator tt_it(x_s_it->first.q->outgoing_translating_transitions.begin()); tt_it != x_s_it->first.q->outgoing_translating_transitions.end(); ++tt_it)
				{
					if (input_match(*in_i, tt_it->input))
					{
						//w = w union (q', r_t, lambda, q_h, i)
						std::pair<out_state_map_iterator, bool> result(w.create_other_state(static_cast<in_state_const_ref>(tt_it->target), x_s_it->first.q_h, x_s_it->first.i, in_j));
//						std::pair<out_state_map_iterator, bool> result(w.create_other_state(static_cast<in_state_const_ref>(tt_it->target), x_s_it->first.q_h, x_s_it->first.i));
						static_cast<out_state&>(*x_s_it).add_consuming_transition(tt_it->output, static_cast<out_state_ref>(&(*result.first)));
						if (result.second)
						{
//							static_cast<out_state&>(*result.first).set_mapped(in_j);
#ifdef TRACE
							static_cast<out_state&>(*result.first).serialize_earley_exe_state(std::wcout) << " (";
							input_serializer()(std::wcout, *in_i) << " : ";
							tag_output_serializer()(std::wcout, tt_it->output) << ')' << std::endl;
#endif
							e.push(static_cast<out_state_ref>(&(*result.first)));
							op(static_cast<out_state&>(*result.first));
						}
					}
				}
			}
		}

		template<typename ExtraInsertOp>
		void build_initial_ses(in_state_const_ref in_initial_state, bool hasnt_white_at_begin, out_machine &out, ExtraInsertOp op)
		{
#ifdef TRACE
			std::wcout << L"----- V[0] -----" << std::endl;
#endif
			std::pair<out_state_map_iterator, bool> result(out.create_other_state(in_initial_state, in_initial_state, 0, 0, out.initial_state.second.src_ref));
//			std::pair<out_state_map_iterator, bool> result(out.create_other_state(in_initial_state, in_initial_state, 0, 0));
//			static_cast<out_state&>(*result.first).set_mapped(out.initial_state.second.src_ref);
			e.push(static_cast<out_state_ref>(&(*result.first)));
			out.initial_state.add_call_transition(static_cast<out_state_ref>(&(*result.first)), &out.global_acceptor_state);
			op(static_cast<out_state&>(*result.first));
#ifdef TRACE
			static_cast<out_state&>(*result.first).serialize_earley_exe_state(std::wcout) << L" initial" << std::endl;
#endif
		}

		//Compute the r-translations of the input range [input_being, input_end) and add them to the set t
		void operator()(const in_machine& grammar, bool hasnt_white_at_begin, bool hasnt_white_at_end, const u_context &c, out_machine& out, weight w_min)
		{
#ifdef TRACE
			std::wcout << L"Begin parsing\n";
			//Keep the original input begin for drawing the resulting FPRTN
#endif
			SourceRef input_begin(out.initial_state.second.src_ref);
			SourceRef input_end(out.global_acceptor_state.second.src_ref);

			//Add common paused execution state for every initial call
			//The only important data here is the FPRTN initial state,
			//which will be used for computing the composition of its initial
			//blackboard set {b_empty} with the blackboard of each FPRTN state
			//accepting an initial call
			std::pair<paused_execution_state_map_iterator, bool> result(out.the_chart[0].pess.insert(paused_execution_state(NULL, &out.initial_state, NULL, NULL, 0)));
#ifdef TRACE
			std::wcout << L"added init pes for init state " << out.initial_state.second.wlabel() << std::endl;
#endif
			no_op_on_execution_state no_op;
			acceptor_execution_state_inserter ins_op(out.global_acceptor_state, grammar.initial_state(), result.first);

			//Build V_0 as the closure of {(q, {r_I}, lambda, q, 0) | q in Q_I};
			//If empty input, build initial and final V[0]
			if (input_begin == input_end)
			{
				build_initial_ses(grammar.initial_state(), hasnt_white_at_begin, out, ins_op);
				//First token is white separated if there are trailing whites at the beginning
				eclosure(0, input_begin, hasnt_white_at_begin, c, out, ins_op);
			}
			//Else build initial V[0] and the remaining V[i]
			else
			{
				build_initial_ses(grammar.initial_state(), hasnt_white_at_begin, out, no_op);
				//First token is white separated if there are trailing whites at the beginning
				eclosure(0, input_begin, hasnt_white_at_begin, c, out, no_op);

				std::size_t idx(0);
				//While the last chart item active set of execution states is not empty and there are input symbols left, compute the next chart item
				std::size_t last_idx(out.the_chart.size() - 2);
				SourceRef input_begin_plus_1(input_begin);
				while (!out.the_chart[idx].other_states.empty() && idx < last_idx)
				{
#ifdef TRACE
					std::wcout << L"----- V[" << static_cast<int>(idx) + 1 << "] -----" << std::endl;
#endif
					++input_begin_plus_1;
					translate_symbol(idx, input_begin, input_begin_plus_1, out, no_op);
					++idx;
					eclosure(idx, input_begin_plus_1, (*input_begin)->end == (*input_begin_plus_1)->begin, c, out, no_op);
					++input_begin;
				}

				//Compute last chart item
				if (!out.the_chart[idx].other_states.empty())
				{
#ifdef TRACE
					std::wcout << L"----- V[" << static_cast<int>(idx) + 1 << "] -----" << std::endl;
#endif
					++input_begin_plus_1;
					translate_symbol(idx, input_begin, input_begin_plus_1, out, ins_op);
					++idx;
					//Next token is the input end... it is white separated if there are trailing whites at the end
					eclosure(idx, input_begin_plus_1, hasnt_white_at_end, c, out, ins_op);
					++input_begin;
				}
			}
#ifdef TRACE
			std::wcout << L"***** Paused ESs *****\n";
			std::wcout << L"----- V[0] -----\n";
			paused_execution_state_map_const_iterator x_p_it(out.the_chart[0].pess.begin());
			std::wcout << L"initial paused execution state with source FPRTN state ";
			x_p_it->first.r->serialize_fprtn_state(std::wcout) << std::endl;
			for (++x_p_it; x_p_it != out.the_chart[0].pess.end(); ++x_p_it)
				static_cast<const paused_execution_state&>(*x_p_it).serialize(std::wcout) << std::endl;
			input_begin = out.initial_state.second.src_ref;
			std::size_t idx(1);
			for (; input_begin != input_end; ++input_begin, ++idx)
			{
				std::wcout << L"----- V[" << static_cast<int>(idx) << "] -----\n";
				for (x_p_it = out.the_chart[idx].pess.begin(); x_p_it != out.the_chart[idx].pess.end(); ++x_p_it)
					static_cast<const paused_execution_state&>(*x_p_it).serialize(std::wcout) << std::endl;
			}
			std::wcout << L"***** End of paused ESs *****\n";
			std::wcout << L"End parsing\n";
			write_fprtn_dot("dirty_parses", "../dirty_parses.dot", out);
#endif
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_TO_FPRTN_TOP_PARSER_H*/
