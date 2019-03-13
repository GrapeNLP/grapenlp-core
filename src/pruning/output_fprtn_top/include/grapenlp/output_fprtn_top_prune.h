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

#ifndef GRAPENLP_OUTPUT_FPRTN_TOP_PRUNE_H
#define GRAPENLP_OUTPUT_FPRTN_TOP_PRUNE_H

#include <grapenlp/output_fprtn_top.h>
#include <grapenlp/output_fprtn_prune.h>

namespace grapenlp
{
	/*
	 * Marks as useless every state of the output FPRTN that is not reversely reachable from the global acceptor state
	 */
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	void mark_unreachable_states_top(output_fprtn_top<u_context_mask, SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice> &m, typename weighted_tag_output_traits<typename output_fprtn_top<u_context_mask, SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice>::tag_input>::weight w_min)
	{
		typedef output_fprtn_top<u_context_mask, SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice> machine;
		typedef typename machine::state_ref state_ref;
		typedef typename machine::state_ref_queue state_ref_queue;
		typedef typename machine::outgoing_epsilon_transition_iterator outgoing_epsilon_transition_iterator;
		typedef typename machine::outgoing_consuming_transition_iterator outgoing_consuming_transition_iterator;
		typedef typename machine::outgoing_call_transition_iterator outgoing_call_transition_iterator;
		typedef typename machine::incoming_filtered_pop_transition_iterator incoming_filtered_pop_transition_iterator;

		state_ref_queue pending_states;
		state_ref s;

		//Otherwise, begin by marking the global acceptor state as a reachable state
		m.global_acceptor_state.second.useless_flag = false;
		m.global_acceptor_state.second.ifptc = 0;
		m.global_acceptor_state.second.top_w = w_min;
		m.global_acceptor_state.second.top_reverse_transition_type = OUTPUT_FPRTN_REVERSE_POP_TRANSITION_TYPE;
#ifdef TRACE
		std::wcout << L"start search of reversely reachable states from " << m.global_acceptor_state.second.wlabel() << std::endl;
#endif
		//And add the final state to the queue of states to process
		pending_states.push(&m.global_acceptor_state);

		//While there are states to pending to be processed
		while (!pending_states.empty())
		{
			//Pop next state to process
			s = pending_states.front();
			pending_states.pop();
			//For every consuming transition coming to the current state,
			//mark its source state as reachable and add it to the queue
			for (outgoing_consuming_transition_iterator oconst_it(s->second.incoming_consuming_transitions.begin()); oconst_it != s->second.incoming_consuming_transitions.end(); ++oconst_it)
			{
				if (oconst_it->target->second.useless_flag)
				{
#ifdef TRACE
					std::wcout << L"reached state " << oconst_it->target->second.wlabel() << " from " << s->second.wlabel() << std::endl;
#endif
					oconst_it->target->second.useless_flag = false;
					oconst_it->target->second.ifptc = 0;
					oconst_it->target->second.top_w = w_min;
					oconst_it->target->second.top_reverse_transition_type = OUTPUT_FPRTN_REVERSE_POP_TRANSITION_TYPE;
					pending_states.push(oconst_it->target);
				}
			}
			//For every consuming transition coming to the current state,
			//mark its source state as reachable and add it to the queue
			for (outgoing_epsilon_transition_iterator oet_it(s->second.incoming_epsilon_transitions.begin()); oet_it != s->second.incoming_epsilon_transitions.end(); ++oet_it)
			{
				if (oet_it->target->second.useless_flag)
				{
#ifdef TRACE
					std::wcout << L"reached state " << oet_it->target->second.wlabel() << " from " << s->second.wlabel() << std::endl;
#endif
					oet_it->target->second.useless_flag = false;
					oet_it->target->second.ifptc = 0;
					oet_it->target->second.top_w = w_min;
					oet_it->target->second.top_reverse_transition_type = OUTPUT_FPRTN_REVERSE_POP_TRANSITION_TYPE;
					pending_states.push(oet_it->target);
				}
			}
			//For every call transition coming to this state,
			//mark its source state as reachable and add it to the queue
			for (outgoing_call_transition_iterator ocallt_it(s->second.incoming_call_transitions.begin()); ocallt_it != s->second.incoming_call_transitions.end(); ++ocallt_it)
			{
				if (ocallt_it->target->second.useless_flag)
				{
#ifdef TRACE

					std::wcout << L"reached state " << ocallt_it->target->second.wlabel() << " from " << s->second.wlabel() << std::endl;
#endif
					ocallt_it->target->second.useless_flag = false;
					ocallt_it->target->second.ifptc = 0;
					ocallt_it->target->second.top_w = w_min;
					ocallt_it->target->second.top_reverse_transition_type = OUTPUT_FPRTN_REVERSE_POP_TRANSITION_TYPE;
					pending_states.push(ocallt_it->target);
				}
			}
			//For every popping transition coming to this state,
			//mark its source state as reachable and add it to the queue
			for (incoming_filtered_pop_transition_iterator ifpt_it(s->second.incoming_filtered_pop_transitions.begin()); ifpt_it != s->second.incoming_filtered_pop_transitions.end(); ++ifpt_it)
			{
				if (ifpt_it->target->second.useless_flag)
				{
#ifdef TRACE

					std::wcout << L"reached state " << ifpt_it->target->second.wlabel() << " from " << s->second.wlabel() << std::endl;
#endif
					ifpt_it->target->second.useless_flag = false;
					ifpt_it->target->second.ifptc = 0;
					ifpt_it->target->second.top_w = w_min;
					ifpt_it->target->second.top_reverse_transition_type = OUTPUT_FPRTN_REVERSE_POP_TRANSITION_TYPE;
					pending_states.push(ifpt_it->target);
				}
				++(s->second.ifptc);
#ifdef TRACE
				std::wcout << s->second.wlabel() << " ifptc = " << s->second.ifptc << std::endl;
#endif
			}
		}
	}

	//Remove all paths which do not reach the specified state from anywhere.
	//Notice that after parsing, every state in the OUTPUT_FPRTN is derivable from an initial state except
	//the ones belonging to uncompleted calls, and that the algorithm creates a single
	//global final state, thus by specifying this final state as argument for this method
	//the OUTPUT_FPRTN will be pruned (every useless path will be deleted)
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	bool prune_top(output_fprtn_top<u_context_mask, SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice> &m, typename weighted_tag_output_traits<TagInput>::weight w_min)
	{
#ifdef TRACE
		std::wcout << L"Begin removing unused paths\n";
#endif

		//If there are no popping transitions towards the final state,
		//the OUTPUT_FPRTN is equivalent to an empty OUTPUT_FPRTN, so clear it and return
		if (m.global_acceptor_state.second.incoming_filtered_pop_transitions.empty())
		{
#ifdef TRACE
			std::wcout << L"OUTPUT_FPRTN cleared: no interpretations found\n";
#endif
			m.clear();
#ifdef TRACE
			write_fprtn_dot("parses", "../parses.dot", m);
			write_inv_fprtn_dot("inv_parses", "../inv_parses.dot", m);
#endif
			return false;
		}

		mark_unreachable_states_top<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice>(m, w_min);
		remove_unreachable_states(m);

#ifdef TRACE
		std::wcout << L"End removing unused paths\n";
		write_fprtn_dot("parses", "../parses.dot", m);
		write_inv_fprtn_dot("inv_parses", "../inv_parses.dot", m);
#endif
		return true;
	}
}

#endif /*GRAPENLP_OUTPUT_FPRTN_TOP_PRUNE_H*/
