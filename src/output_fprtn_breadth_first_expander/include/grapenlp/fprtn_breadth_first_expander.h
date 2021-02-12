/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@gmail.com>
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

#ifndef GRAPENLP_FPRTN_BREADTH_FIRST_EXPANDER_H
#define GRAPENLP_FPRTN_BREADTH_FIRST_EXPANDER_H

#ifdef TRACE
#include <iostream>
#include <grapenlp/tag_serializer_traits.h>
#endif

#include <algorithm>
#include <queue>

#include <grapenlp/array.h>
#include <grapenlp/trie.h>
#include <grapenlp/output_fprtn.h>
#include <grapenlp/pool.h>
#include <grapenlp/u_context_mask.h>

namespace grapenlp
{
#ifdef TRACE
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, typename Blackboard, typename BlackboardSerializer, typename Transformer, typename StateConstRefStackRefPool, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
#else
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, typename Blackboard, typename Transformer, typename StateConstRefStackRefPool, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
#endif
	class fprtn_breadth_first_expander
	{
	public:
		typedef TagInput tag_input;
		typedef SourceRef source_ref;
		typedef typename source_ref::value_type input;
		typedef Blackboard blackboard;
#ifdef TRACE
		typedef BlackboardSerializer blackboard_serializer;
		typedef typename tag_serializer_traits<input>::type input_serializer;
		typedef typename tag_serializer_traits<tag_input>::type tag_input_serializer;
#endif
		typedef typename set_impl_selector<output_set_impl_choice, blackboard>::type blackboard_set;
		typedef typename blackboard_set::const_iterator blackboard_set_const_iterator;
		typedef Transformer transformer;

		typedef output_fprtn<u_context_mask, source_ref, tag_input, RTNOTagInput, execution_state_set_impl_choice> machine;
		typedef typename machine::state state;
		typedef typename machine::state_ref state_ref;
		typedef typename machine::state_const_ref state_const_ref;

		typedef	typename machine::outgoing_epsilon_transition out_outgoing_epsilon_transition;
		typedef	typename machine::outgoing_epsilon_transition_set out_outgoing_epsilon_transition_set;
		typedef typename out_outgoing_epsilon_transition_set::iterator out_outgoing_epsilon_transition_set_iterator;
		typedef typename out_outgoing_epsilon_transition_set::const_iterator out_outgoing_epsilon_transition_set_const_iterator;

		typedef	typename machine::outgoing_consuming_transition out_outgoing_consuming_transition;
		typedef	typename machine::outgoing_consuming_transition_set out_outgoing_consuming_transition_set;
		typedef typename out_outgoing_consuming_transition_set::iterator out_outgoing_consuming_transition_set_iterator;
		typedef typename out_outgoing_consuming_transition_set::const_iterator out_outgoing_consuming_transition_set_const_iterator;

		typedef	typename machine::outgoing_call_transition out_outgoing_call_transition;
		typedef	typename machine::outgoing_call_transition_set out_outgoing_call_transition_set;
		typedef typename out_outgoing_call_transition_set::iterator out_outgoing_call_transition_set_iterator;
		typedef typename out_outgoing_call_transition_set::const_iterator out_outgoing_call_transition_set_const_iterator;

		typedef StateConstRefStackRefPool state_const_ref_stack_ref_pool;
		typedef typename ref_pool_traits<state_const_ref_stack_ref_pool>::value_type state_const_ref_stack_ref;
		typedef typename ref_pool_traits<state_const_ref_stack_ref_pool>::base_type state_const_ref_stack;
		typedef typename ref_pool_traits<state_const_ref_stack_ref_pool>::iterator state_const_ref_stack_iterator;
		typedef typename ref_pool_traits<state_const_ref_stack_ref_pool>::const_iterator state_const_ref_stack_const_iterator;
		typedef typename ref_pool_traits<state_const_ref_stack_ref_pool>::less state_const_ref_stack_less;
		typedef typename ref_pool_traits<state_const_ref_stack_ref_pool>::deref state_const_ref_stack_deref;
		typedef typename ref_pool_traits<state_const_ref_stack_ref_pool>::ptr state_const_ref_stack_ptr;

		struct execution_state
		{
			typedef execution_state* ref;
			typedef std::queue<execution_state> queue;

			state_const_ref q;
			blackboard b;
			state_const_ref_stack_ref pi;

			execution_state(state_const_ref q_, const blackboard &b_, state_const_ref_stack_ref pi_): q(q_), b(b_), pi(pi_)
			{}

			bool operator< (const execution_state& x2) const
			{
				if (q < x2.q)
					return true;
				if (x2.q < q)
					return false;
				//We don't care here about lexicographical comparison, we simply compare the object addresses in order to optimize comparison
				if (state_const_ref_stack_less()(pi, x2.pi))
					return true;
				if (state_const_ref_stack_less()(x2.pi, pi))
					return false;
				return b < x2.b;
			}

#ifdef TRACE
			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
			{
				q->serialize_fprtn_state(out << '(') << ", ";
				blackboard_serializer()(out, b) << ", ";
				if (state_const_ref_stack_deref()(pi).empty())
					out << "lambda";
				else
				{
					const state_const_ref_stack &scrs(state_const_ref_stack_deref()(pi));
					for (state_const_ref_stack_const_iterator i(scrs.begin()); i != scrs.end(); ++i)
						(*i)->serialize_fprtn_state(out);
				}
				return out << ')';
			}
#endif
		};

		typedef typename execution_state::ref execution_state_ref;
		typedef typename execution_state::queue execution_state_queue;

	protected:
		transformer gamma;
		execution_state_queue e;

		fprtn_breadth_first_expander(): gamma(), e()
		{}

		fprtn_breadth_first_expander(transformer gamma_): gamma(gamma_), e()
		{}

	private:
		void copy_traverse_consuming(out_outgoing_consuming_transition_set_const_iterator outgoing_consuming_transition_begin)
		{
//			std::wcout << L"copy traverse consuming\n";

			for (; outgoing_consuming_transition_begin != e.front().q->second.outgoing_consuming_transitions.end(); ++outgoing_consuming_transition_begin)
			{
				blackboard b_t(e.front().b);
				e.push(execution_state(outgoing_consuming_transition_begin->target, gamma(b_t, e.front().q->second.src_ref, outgoing_consuming_transition_begin->input), e.front().pi));
#ifdef TRACE
				e.front().serialize(std::wcout) << L" copy consuming" << std::endl;
#endif
			}
		}

		void copy_traverse_consuming()
		{ copy_traverse_consuming(e.front().q->outgoing_consuming_transitions.begin()); }

		void copy_traverse_epsilon(out_outgoing_epsilon_transition_set_const_iterator outgoing_epsilon_transition_begin)
		{
//			std::wcout << L"copy traverse epsilon\n";
			for (; outgoing_epsilon_transition_begin != e.front().q->second.outgoing_epsilon_transitions.end(); ++outgoing_epsilon_transition_begin)
			{
				e.push(execution_state(outgoing_epsilon_transition_begin->target, e.front().b, e.front().pi));
#ifdef TRACE
				e.front().serialize(std::wcout) << L" copy epsilon" << std::endl;
#endif
			}
		}

		void copy_traverse_epsilon()
		{ copy_traverse_epsilon(e.front().q->second.outgoing_epsilon_transitions.begin()); }

		void copy_traverse_call(out_outgoing_call_transition_set_const_iterator outgoing_call_transition_begin)
		{
//			std::wcout << L"copy traverse call\n";
			for (; outgoing_call_transition_begin != e.front().q->second.outgoing_call_transitions.end(); ++outgoing_call_transition_begin)
			{
				e.push(execution_state(outgoing_call_transition_begin->called, e.front().b, state_const_ref_stack_ptr()((state_const_ref_stack_deref()(e.front().pi) + static_cast<state_const_ref>(outgoing_call_transition_begin->target)))));
#ifdef TRACE
				e.back().serialize(std::wcout) << L" copy call" << std::endl;
#endif
			}
		}

		void copy_traverse_call()
		{ copy_traverse_call(e.front().q->second.outgoing_call_transitions.begin()); }

		void copy_traverse_pop()
		{
//			std::wcout << L"copy traverse pop\n";
			if (e.front().q->is_final() && !state_const_ref_stack_deref()(e.front().pi).empty() && e.front().q->second.src_ref == state_const_ref_stack_deref()(e.front().pi).back()->second.src_ref)
			{
				e.push(execution_state(state_const_ref_stack_deref()(e.front().pi).back(), e.front().b, state_const_ref_stack_ptr()(state_const_ref_stack_deref()(e.front().pi).prefix())));
#ifdef TRACE
				e.back().serialize(std::wcout) << L" copy pop" << std::endl;
#endif
			}
		}

		//Creates new execution states by copying the current one and developing the copies, except for
		//the execution state result of exploring the first consuming transition. This execution state
		//will be a modification of the current execution state instead of a modified copy.
		void traverse_from_consuming()
		{
//			std::wcout << L"traverse from consuming\n";
			out_outgoing_consuming_transition_set_const_iterator oct_it(e.front().q->second.outgoing_consuming_transitions.begin());
			out_outgoing_consuming_transition_set_const_iterator oct_it_aux(oct_it);
			++oct_it_aux;
			copy_traverse_consuming(oct_it_aux);
			copy_traverse_epsilon();
			copy_traverse_call();
			copy_traverse_pop();

			gamma(e.front().b, e.front().q->second.src_ref, oct_it->input);
			//Advance to target state
			e.front().q = oct_it->target;
#ifdef TRACE
			e.front().serialize(std::wcout) << L" evolve consuming" << std::endl;
#endif
		}

		void traverse_from_epsilon()
		{
//			std::wcout << L"traverse from epsilon\n";
			out_outgoing_epsilon_transition_set_const_iterator oet_it(e.front().q->second.outgoing_epsilon_transitions.begin());
			out_outgoing_epsilon_transition_set_const_iterator oet_it_aux(oet_it);
			++oet_it_aux;
			copy_traverse_epsilon(oet_it_aux);
			copy_traverse_call();
			copy_traverse_pop();
			//Advance to target state
			e.front().q = oet_it->target;
#ifdef TRACE
			e.front().serialize(std::wcout) << L" evolve epsilon" << std::endl;
#endif
		}

		void traverse_from_call()
		{
//			std::wcout << L"traverse from call\n";
			out_outgoing_call_transition_set_const_iterator oct_it(e.front().q->second.outgoing_call_transitions.begin());
			out_outgoing_call_transition_set_const_iterator oct_it_aux(oct_it);
			++oct_it_aux;
			copy_traverse_call(oct_it_aux);
			copy_traverse_pop();
			//Advance to call state
			e.front().q = oct_it->called;
			//Add return state to return state stack
			e.front().pi = state_const_ref_stack_ptr()(state_const_ref_stack_deref()(e.front().pi) + static_cast<state_const_ref>(oct_it->target));
#ifdef TRACE
			e.front().serialize(std::wcout) << L" evolve call" << std::endl;
#endif
		}

		void traverse_from_pop()
		{
//			std::wcout << L"traverse from pop\n";
			//Go to return state
			e.front().q = state_const_ref_stack_deref()(e.front().pi).back();
			//Pop return state from the return state stack
			e.front().pi = state_const_ref_stack_ptr()((state_const_ref_stack_deref()(e.front().pi).prefix()));
#ifdef TRACE
			e.front().serialize(std::wcout) << L" evolve pop" << std::endl;
#endif
		}

		//Develop first execution state of the queue of pending execution states
		void traverse(blackboard_set &result)
		{
//			std::wcout << L"traverse\n";
			//If this execution state is complete (it corresponds to a final state with no pending calls)
			//add it to the result set
			if (e.front().q->is_final() && state_const_ref_stack_deref()(e.front().pi).empty())
			{
				result.insert(e.front().b);
#ifdef TRACE
				e.front().serialize(std::wcout) << L" added to result" << std::endl;
#endif
			}
			//If its current state has at least one consuming transition, develop them
			if (!e.front().q->second.outgoing_consuming_transitions.empty())
				traverse_from_consuming();
			//If its current state has at least one epsilon transition, develop them
			else if (!e.front().q->second.outgoing_epsilon_transitions.empty())
				traverse_from_epsilon();
			//If its current state has at least one call transition, develop them
			else if (!e.front().q->second.outgoing_call_transitions.empty())
				traverse_from_call();
			//If it is possible to return from a call (its state is final and the return state stack
			//is not empty), develop the return from call
			else if (e.front().q->is_final() && !state_const_ref_stack_deref()(e.front().pi).empty() && e.front().q->second.src_ref == state_const_ref_stack_deref()(e.front().pi).back()->second.src_ref)
				traverse_from_pop();
			//Otherwise current execution state admits no more development: delete it
			else
			{
#ifdef TRACE
				e.front().serialize(std::wcout) << L" deleted" << std::endl;
#endif
				e.pop();
			}
		}

	public:
		//Computes a set of maps for every complete path within the FPRTN, where the map keys are input segment identifiers
		//and the map values are pairs of input positions (that is, they mark segments of the input containing relevant
		//information to be extracted (a phone number) with the identifier of that information (phone)).
		//We pass the FPRTN to expand, the input begin and end iterators and an empty set of segment maps to be filled
		//The algorithm represents execution states as triplets (current state, current segment map, return state stack)
		//It uses a queue to store the execution states that are still to be developed
		//It first adds to the queue the initial set of execution states as (initial state, empty segment map, empty return state stack)
		//It derives new execution states from the first execution state of the queue, and pushes them onto the queue
		//The last derived one is not pushed, but replaces the first execution state (the first one is modified)
		//If the first execution state has no possible derivations, it is popped out and the process is repeated for the next execution state
		//until there are no execution states left
		//Each time an acceptor execution state is reached, its segment map is added to the result
		//Acceptor execution states have an acceptor state and no pending returns from call (an empty stack of return states)
		blackboard_set& operator() (const machine& m, blackboard_set &result, const blackboard &empty_blackboard = blackboard())
		{
#ifdef TRACE
			std::wcout << L"Begin breadth-first expansion\n";
#endif
			//Initialize pool of state sequences
			state_const_ref_stack_ref_pool scrsp;

			//For the initial FPRTN state, build an expansion execution state (q, b, lambda) and add it to the expansion queue
			e.push(execution_state(&m.initial_state, empty_blackboard, scrsp.empty()));
#ifdef TRACE
			e.back().serialize(std::wcout) << L" initial" << std::endl;
#endif

			//While there are pending execution states to develop, pop first execution state from
			//the queue and develop it
			while (!e.empty())
				traverse(result);
#ifdef TRACE
			std::wcout << L"End of breadth-first expansion\n";
#endif
			return result;
		}
	};
}

#endif /*GRAPENLP_FPRTN_BREADTH_FIRST_EXPANDER_H*/
