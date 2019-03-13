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

#ifndef GRAPENLP_FPRTN_TOP_BLACKBOARD_EXTRACTOR_H
#define GRAPENLP_FPRTN_TOP_BLACKBOARD_EXTRACTOR_H

#ifdef TRACE
#include <iostream>
#include <grapenlp/tag_serializer_traits.h>
#endif

#include <algorithm>
#include <queue>

#include <grapenlp/array.h>
#include <grapenlp/weight_transformer_traits.h>
#include <grapenlp/weighted_tag_output_traits.h>
#include <grapenlp/output_fprtn_top.h>
#include <grapenlp/u_context_mask.h>

namespace grapenlp
{
#ifdef TRACE
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, typename Blackboard, typename BlackboardSerializer, typename UnweightedReverseTransformer, typename WeightTransformer, assoc_container_impl_choice execution_state_set_impl_choice>
#else
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, typename Blackboard, typename UnweightedReverseTransformer, typename WeightTransformer, assoc_container_impl_choice execution_state_set_impl_choice>
#endif
	class wfprtn_top_blackboard_extractor
	{
	public:
		typedef TagInput tag_input;
		typedef typename weighted_tag_output_traits<tag_input>::weight weight;
		typedef typename weighted_tag_output_traits<tag_input>::weight_getter weight_getter;
		//The getter of the consuming transition tag part that is not the weight:
		typedef typename weighted_tag_output_traits<tag_input>::non_weight_getter non_weight_getter;
		typedef SourceRef source_ref;
		typedef typename source_ref::value_type input;
		typedef Blackboard blackboard;
		typedef WeightTransformer weight_transformer;
		typedef weight_transformer_traits<WeightTransformer> the_weight_transformer_traits;
#ifdef TRACE
		typedef BlackboardSerializer blackboard_serializer;
		typedef typename tag_serializer_traits<tag_input>::type tag_input_serializer;
#endif
		typedef UnweightedReverseTransformer unweighted_converse_transformer;

		typedef output_fprtn_top<u_context_mask, source_ref, tag_input, RTNOTagInput, execution_state_set_impl_choice> machine;
		typedef typename machine::state state;
		typedef typename machine::state_ref state_ref;
		typedef typename machine::state_const_ref state_const_ref;
		typedef std::queue<state_ref> state_ref_queue;

		typedef	typename machine::outgoing_epsilon_transition_iterator outgoing_epsilon_transition_iterator;
		typedef	typename machine::outgoing_consuming_transition_iterator outgoing_consuming_transition_iterator;
		typedef	typename machine::outgoing_call_transition_iterator outgoing_call_transition_iterator;
		typedef	typename machine::outgoing_filtered_pop_transition_iterator outgoing_filtered_pop_transition_iterator;
		typedef	typename machine::incoming_filtered_pop_transition_iterator incoming_filtered_pop_transition_iterator;

		typedef	typename machine::paused_execution_state_iterator paused_execution_state_iterator;
		typedef typename machine::source_rtno_state_const_ref source_rtno_state_const_ref;

		typedef typename machine::chart chart;
		typedef typename chart::iterator chart_iterator;

	protected:
		unweighted_converse_transformer cgamma;

		wfprtn_top_blackboard_extractor(): cgamma()
		{}

		wfprtn_top_blackboard_extractor(unweighted_converse_transformer cgamma_): cgamma(cgamma_)
		{}

	public:
		void top_reverse_path(machine& m, weight w_init)
		{
#ifdef TRACE
			std::wcout << L"Begin top reverse path\n";
#endif
			weight w_min(m.global_acceptor_state.second.top_w);
			m.initial_state.second.top_w = w_init;
#ifdef TRACE
			std::wcout << m.initial_state.second.wlabel() << L" top w = " << m.initial_state.second.top_w << std::endl;
#endif
			state_ref_queue e;
			e.push(&m.initial_state);
#ifdef TRACE
			std::wcout << L"push " << m.initial_state.second.wlabel() << std::endl;
#endif
			state_ref r_s;
			state_ref r_t;
			while (!e.empty())
			{
				r_s = e.front();
				e.pop();
#ifdef TRACE
				std::wcout << L"pop " << r_s->second.wlabel() << std::endl;
#endif
				/**************************/
				/* Blackboard composition */
				/**************************/
				//For each incoming filtered pop transition from r_f to r_s
				while (!r_s->second.incoming_filtered_pop_transitions.empty())
				{
					//For each source state r of the call completed by the pop transition
					paused_execution_state_iterator pes_begin(r_s->second.incoming_filtered_pop_transitions.begin()->pes_begin);
					paused_execution_state_iterator pes_end(m.the_chart[r_s->second.incoming_filtered_pop_transitions.begin()->target->first.i].pess.end());
					r_t = r_s->second.incoming_filtered_pop_transitions.front().target;
					source_rtno_state_const_ref q_c(pes_begin->first.q_c);
#ifdef TRACE
					std::wcout << L"processing incoming filtered pop transition (" << r_t->second.wlabel() << L", " << r_s->second.wlabel() << UP_ARROW << L", " << r_s->second.wlabel() << L')' << std::endl;
#endif
					state_ref r_ps_max(pes_begin->first.r);
					//Forward search
					while (++pes_begin != pes_end && pes_begin->first.q == r_s->first.q && pes_begin->first.i == r_s->first.i && pes_begin->first.q_h == r_s->first.q_h && pes_begin->first.q_c == q_c)
						if (r_ps_max->second.top_w < pes_begin->first.r->second.top_w)
							r_ps_max = pes_begin->first.r;
					//Backwards search: elements to search are in consecutive positions of the pes set, but nothing guarantees that
					//they will only be at position pes_begin and afterwards
					pes_begin = r_s->second.incoming_filtered_pop_transitions.begin()->pes_begin;
					pes_end = m.the_chart[r_s->second.incoming_filtered_pop_transitions.begin()->target->first.i].pess.begin();
					while (pes_begin != pes_end && (--pes_begin)->first.q == r_s->first.q && pes_begin->first.i == r_s->first.i && pes_begin->first.q_h == r_s->first.q_h && pes_begin->first.q_c == q_c)
						if (r_ps_max->second.top_w < pes_begin->first.r->second.top_w)
							r_ps_max = pes_begin->first.r;
					weight top_w(weight_transformer()(r_ps_max->second.top_w, r_t->second.top_w));
					if (r_s->second.top_w < top_w)
					{
						r_s->second.top_w = top_w;
						r_s->second.top_r_t = r_ps_max;
						r_s->second.top_r_c = r_t;
						r_s->second.top_reverse_transition_type = OUTPUT_FPRTN_REVERSE_PUSH_TRANSITION_TYPE;
#ifdef TRACE
						std::wcout << r_s->second.wlabel() << " top w = " << r_s->second.top_w << ", top reverse transition is call (" << r_s->second.wlabel() << ", " << static_cast<state_ref>(r_s->second.top_r_c)->second.wlabel() << ", " << static_cast<state_ref>(r_s->second.top_r_t)->second.wlabel() << ')' << std::endl;
#endif
					}
					r_s->second.incoming_filtered_pop_transitions.pop_front();
				}

				/***********************/
				/* Epsilon transitions */
				/***********************/
				while (!r_s->second.outgoing_epsilon_transitions.empty())
				{
					r_t = r_s->second.outgoing_epsilon_transitions.front().target;
#ifdef TRACE
					std::wcout << L"processing outgoing epsilon transition (" << r_s->second.wlabel() << L", \\varepsilon, " << r_t->second.wlabel() << L')' << std::endl;
#endif
					if (r_t->second.top_w < r_s->second.top_w)
					{
						r_t->second.top_w = r_s->second.top_w;
						r_t->second.top_r_t = r_s;
						r_t->second.top_reverse_transition_type = OUTPUT_FPRTN_REVERSE_EPSILON_TRANSITION_TYPE;
#ifdef TRACE
						std::wcout << r_t->second.wlabel() << " top w = " << r_t->second.top_w << ", top reverse transition is epsilon (" << r_t->second.wlabel() << ", \\varepsilon, " << static_cast<state_ref>(r_t->second.top_r_t)->second.wlabel() << ')' << std::endl;
#endif
					}
					//Remove the incoming epsilon transition corresponding to the current outgoing epsilon transition
					r_t->second.incoming_epsilon_transitions.erase(r_s->second.outgoing_epsilon_transitions.front().r_trans_it);
					//Remove the current outgoing epsilon transition
					r_s->second.outgoing_epsilon_transitions.pop_front();
					if (r_t->second.incoming_consuming_transitions.empty() && r_t->second.incoming_epsilon_transitions.empty() && r_t->second.incoming_call_transitions.empty() && !r_t->second.ifptc)
					{
						e.push(r_t);
#ifdef TRACE
						std::wcout << L"push " << r_t->second.wlabel() << std::endl;
#endif
					}
				}

				/*************************/
				/* Consuming transitions */
				/*************************/
				while (!r_s->second.outgoing_consuming_transitions.empty())
				{
					r_t = r_s->second.outgoing_consuming_transitions.front().target;
#ifdef TRACE
					std::wcout << L"processing outgoing consuming transition (" << r_s->second.wlabel() << L", ";
					tag_input_serializer()(std::wcout, r_s->second.outgoing_consuming_transitions.front().input) << L", ";
					std::wcout << r_t->second.wlabel() << L')' << std::endl;
#endif
					weight top_w(weight_transformer()(r_s->second.top_w, weight_getter()(r_s->second.outgoing_consuming_transitions.front().input)));
					if (r_t->second.top_w < top_w)
					{
						r_t->second.top_w = top_w;
						r_t->second.top_r_t = r_s;
						r_t->second.top_reverse_transition_type = OUTPUT_FPRTN_REVERSE_CONSUMING_TRANSITION_TYPE;
						r_t->second.top_non_w = non_weight_getter()(r_s->second.outgoing_consuming_transitions.front().input);
#ifdef TRACE
						std::wcout << r_t->second.wlabel() << " top w = " << r_t->second.top_w << ", top reverse transition is consuming (" << r_t->second.wlabel() << ", ";
						tag_input_serializer()(std::wcout, r_s->second.outgoing_consuming_transitions.front().input) << ", " << static_cast<state_ref>(r_t->second.top_r_t)->second.wlabel() << ')' << std::endl;
#endif
					}
					//Remove the incoming consuming transition corresponding to the current outgoing consuming transition
					r_t->second.incoming_consuming_transitions.erase(r_s->second.outgoing_consuming_transitions.front().r_trans_it);
					//Remove the current outgoing consuming transition
					r_s->second.outgoing_consuming_transitions.pop_front();
					if (r_t->second.incoming_consuming_transitions.empty() && r_t->second.incoming_epsilon_transitions.empty() && r_t->second.incoming_call_transitions.empty() && !r_t->second.ifptc)
					{
						e.push(r_t);
#ifdef TRACE
						std::wcout << L"push " << r_t->second.wlabel() << std::endl;
#endif
					}
				}

				/********************/
				/* Push transitions */
				/********************/
				while (!r_s->second.outgoing_call_transitions.empty())
				{

					r_t = r_s->second.outgoing_call_transitions.front().target;
#ifdef TRACE
					std::wcout << L"processing outgoing call transition (" << r_s->second.wlabel() << L", " << r_s->second.outgoing_call_transitions.front().called->second.wlabel() << L", " << r_t->second.wlabel() << L')' << std::endl;
#endif
					//Remove the incoming call transition corresponding to the current outgoing call transition
					r_t->second.incoming_call_transitions.erase(r_s->second.outgoing_call_transitions.front().r_trans_it);
					if (r_t->second.incoming_consuming_transitions.empty() && r_t->second.incoming_epsilon_transitions.empty() && r_t->second.incoming_call_transitions.empty() && !r_t->second.ifptc)
					{
						e.push(r_t);
#ifdef TRACE
						std::wcout << L"push " << r_t->second.wlabel() << std::endl;
#endif
					}
					else
					{
						state_ref r_c(r_s->second.outgoing_call_transitions.front().called);
						if (r_c->second.top_w == w_min)
						{
							r_c->second.top_w = w_init;
#ifdef TRACE
							std::wcout << L"initialized " << r_c->second.wlabel() << " top_w to " << r_c->second.top_w << std::endl;
#endif
							if (r_c->second.incoming_consuming_transitions.empty() && r_c->second.incoming_epsilon_transitions.empty() && r_c->second.incoming_call_transitions.empty() && !r_c->second.ifptc)
							{
								e.push(r_c);
#ifdef TRACE
								std::wcout << L"push " << r_c->second.wlabel() << std::endl;
#endif
							}
						}
					}
					//Remove the current outgoing call transition
					r_s->second.outgoing_call_transitions.pop_front();
				}

				/*******************/
				/* Pop transitions */
				/*******************/
				while (!r_s->second.outgoing_filtered_pop_transitions.empty())
				{
					r_t = r_s->second.outgoing_filtered_pop_transitions.front().target;
#ifdef TRACE
					std::wcout << L"processing outgoing filtered pop transition (" << r_s->second.wlabel() << L", " << r_t->second.wlabel() << UP_ARROW << ", " << r_t->second.wlabel() << L')' << std::endl;
#endif
					--(r_t->second.ifptc);
#ifdef TRACE
					std::wcout << r_t->second.wlabel() << " incoming transition count = " << r_t->second.ifptc << std::endl;
#endif
					if (r_t->second.incoming_consuming_transitions.empty() && r_t->second.incoming_epsilon_transitions.empty() && r_t->second.incoming_call_transitions.empty() && !r_t->second.ifptc)
					{
						e.push(r_t);
#ifdef TRACE
						std::wcout << L"push " << r_t->second.wlabel() << std::endl;
#endif
					}
					r_s->second.outgoing_filtered_pop_transitions.pop_front();
				}
			}
#ifdef TRACE
			std::wcout << L"End of top reverse path\n";
#endif
		}

		blackboard operator()(machine& m, const blackboard &empty_blackboard = blackboard(the_weight_transformer_traits::identity()))
		{
			typedef std::deque<state_const_ref> state_const_ref_stack;
#ifdef TRACE
			typedef typename state_const_ref_stack::const_iterator state_const_ref_stack_const_iterator;
#endif

			top_reverse_path(m, the_weight_transformer_traits::identity());
#ifdef TRACE
			std::wcout << L"Begin top blackboard construction\n";
#endif
			state_const_ref r_t(&m.global_acceptor_state);
			blackboard b_t(empty_blackboard);
			state_const_ref_stack pi;
#ifdef TRACE
			b_t.w = m.global_acceptor_state.second.top_w;
			std::wcout << '(' << r_t->second.wlabel() << ", ";
			blackboard_serializer()(std::wcout, b_t) << ", ";
			for (state_const_ref_stack_const_iterator i(pi.begin()); i != pi.end(); ++i)
				std::wcout << (*i)->second.wlabel();
			std::wcout << ')' << std::endl;
#endif
			do
			{
				switch (r_t->second.top_reverse_transition_type)
				{
				case OUTPUT_FPRTN_REVERSE_POP_TRANSITION_TYPE:
					r_t = pi.back();
					pi.pop_back();
					break;
				case OUTPUT_FPRTN_REVERSE_PUSH_TRANSITION_TYPE:
					pi.push_back(static_cast<state_ref>(r_t->second.top_r_t));
					r_t = static_cast<state_const_ref>(r_t->second.top_r_c);
					break;
				case OUTPUT_FPRTN_REVERSE_EPSILON_TRANSITION_TYPE:
					r_t = static_cast<state_ref>(r_t->second.top_r_t);
					break;
				case OUTPUT_FPRTN_REVERSE_CONSUMING_TRANSITION_TYPE:
					cgamma(b_t, r_t->second.src_ref, r_t->second.top_non_w);
					r_t = static_cast<state_ref>(r_t->second.top_r_t);
					break;
				}
#ifdef TRACE
				b_t.w = r_t->second.top_w;
				std::wcout << '(' << r_t->second.wlabel() << ", ";
				blackboard_serializer()(std::wcout, b_t) << ", ";
				for (state_const_ref_stack_const_iterator i(pi.begin()); i != pi.end(); ++i)
					std::wcout << (*i)->second.wlabel();
				std::wcout << ')' << std::endl;
#endif
			} while (r_t != &m.initial_state);
#ifndef TRACE
			b_t.w = m.global_acceptor_state.second.top_w;
#else
			std::wcout << L"End of top blackboard construction\n";
#endif
			return b_t;
		}
	};
}

#endif /*GRAPENLP_FPRTN_TOP_BLACKBOARD_EXTRACTOR_H*/
