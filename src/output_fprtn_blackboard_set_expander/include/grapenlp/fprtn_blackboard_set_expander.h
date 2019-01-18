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

#ifndef GRAPENLP_FPRTN_BLACKBOARD_SET_EXPANDER_H
#define GRAPENLP_FPRTN_BLACKBOARD_SET_EXPANDER_H

#ifdef TRACE
#include <iostream>
#include <grapenlp/tag_serializer_traits.h>
#endif

#include <algorithm>
#include <queue>

#include <grapenlp/array.h>
#include <grapenlp/output_fprtn_zpps.h>

namespace grapenlp
{
#ifdef TRACE
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, typename Blackboard, typename BlackboardSerializer, typename Transformer, typename Composer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
#else
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, typename Blackboard, typename Transformer, typename Composer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
#endif
	class fprtn_blackboard_set_expander
	{
	public:
		typedef TagInput tag_input;
		typedef SourceRef source_ref;
		typedef typename source_ref::value_type input;
		typedef Blackboard blackboard;
#ifdef TRACE
		typedef BlackboardSerializer blackboard_serializer;
		typedef typename tag_serializer<input>::type input_serializer;
		typedef typename tag_serializer<tag_input>::type tag_input_serializer;
#endif
		typedef typename set_impl_selector<output_set_impl_choice, blackboard>::type blackboard_set;
		typedef typename blackboard_set::iterator blackboard_set_iterator;
		typedef typename blackboard_set::const_iterator blackboard_set_const_iterator;
		typedef Transformer transformer;
		typedef Composer composer;

		typedef typename output_fprtn_zpps<source_ref, tag_input, RTNOTagInput, execution_state_set_impl_choice>::type machine;
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
		transformer gamma;
		composer circ;
		state_ref_queue e;

		fprtn_blackboard_set_expander(): gamma(), circ(), e()
		{}

		fprtn_blackboard_set_expander(transformer gamma_, composer circ_): gamma(gamma_), circ(circ_), e()
		{}

	public:
		blackboard_set& operator() (machine& m, std::size_t useful_state_count, blackboard_set &result, const blackboard &empty_blackboard = blackboard())
		{
#ifdef TRACE
			std::wcout << L"Begin blackboard set expansion\n";
#endif
			array<blackboard_set> bsa(useful_state_count);
			bsa[m.initial_state.second.idx].insert(empty_blackboard);
#ifdef TRACE
			blackboard_serializer()(std::wcout << L"added ", empty_blackboard) << L" to " << m.initial_state.second.wlabel() << std::endl;
#endif
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
				std::wcout << "Pop " << r_s->second.wlabel() << std::endl;
#endif
				/**************************/
				/* Blackboard composition */
				/**************************/
				//For each incoming filtered pop transition from r_f to r_s
				while (!r_s->second.incoming_filtered_pop_transitions.empty())
				{
					//For each source state r of the call completed by the pop transition
					paused_execution_state_iterator pes_begin(r_s->second.incoming_filtered_pop_transitions.front().pes_begin);
					paused_execution_state_iterator pes_end(m.the_chart[r_s->second.incoming_filtered_pop_transitions.front().target->first.i].pess.end());
					r_t = r_s->second.incoming_filtered_pop_transitions.front().target;
					source_rtno_state_const_ref q_c(pes_begin->first.q_c);
#ifdef TRACE
					std::wcout << L"processing incoming filtered pop transition (" << r_t->second.wlabel() << L", " << r_s->second.wlabel() << UP_ARROW << L", " << r_s->second.wlabel() << L')' << std::endl;
#endif
					//Forward search
					do
					{
						//For each blackboard generated up to r and up to r_f
						for (blackboard_set_const_iterator b_it(bsa[pes_begin->first.r->second.idx].begin()); b_it != bsa[pes_begin->first.r->second.idx].end(); ++b_it)
							for (blackboard_set_const_iterator b_f_it(bsa[r_t->second.idx].begin()); b_f_it != bsa[r_t->second.idx].end(); ++b_f_it)
							{
								//Add the composition of both blackboards to the set of blackboards generated up to r_s
								blackboard b_t(*b_it);
#ifdef TRACE
								std::pair<blackboard_set_iterator, bool> result(bsa[r_s->second.idx].insert(circ(b_t, *b_f_it)));
								std::wcout << L"added ";
								if (!result.second)
									std::wcout << L"again ";
								blackboard_serializer()(std::wcout, *result.first) << L" to " << r_s->second.wlabel() << std::endl;
#else
								bsa[r_s->second.idx].insert(circ(b_t, *b_f_it));
#endif
							}
						++pes_begin;
					} while (pes_begin != pes_end && pes_begin->first.q == r_s->first.q && pes_begin->first.i == r_s->first.i && pes_begin->first.q_h == r_s->first.q_h && pes_begin->first.q_c == q_c);
					//Backwards search: elements to search are in consecutive positions of the pes set, but nothing guarantees that
					//they will only be at position pes_begin and afterwards
					pes_begin = r_s->second.incoming_filtered_pop_transitions.front().pes_begin;
					pes_end = m.the_chart[r_s->second.incoming_filtered_pop_transitions.front().target->first.i].pess.begin();
					while (pes_begin != pes_end && (--pes_begin)->first.q == r_s->first.q && pes_begin->first.i == r_s->first.i && pes_begin->first.q_h == r_s->first.q_h && pes_begin->first.q_c == q_c)
					{
						//For each blackboard generated up to r and up to r_f
						for (blackboard_set_const_iterator b_it(bsa[pes_begin->first.r->second.idx].begin()); b_it != bsa[pes_begin->first.r->second.idx].end(); ++b_it)
							for (blackboard_set_const_iterator b_f_it(bsa[r_t->second.idx].begin()); b_f_it != bsa[r_t->second.idx].end(); ++b_f_it)
							{
								//Add the composition of both blackboards to the set of blackboards generated up to r_s
								blackboard b_t(*b_it);
#ifdef TRACE
								std::pair<blackboard_set_iterator, bool> result(bsa[r_s->second.idx].insert(circ(b_t, *b_f_it)));
								std::wcout << L"added ";
								if (!result.second)
									std::wcout << L"again ";
								blackboard_serializer()(std::wcout, *result.first) << L" to " << r_s->second.wlabel() << std::endl;
#else
								bsa[r_s->second.idx].insert(circ(b_t, *b_f_it));
#endif
							}
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
					for (blackboard_set_const_iterator b_it(bsa[r_s->second.idx].begin()); b_it != bsa[r_s->second.idx].end(); ++b_it)
					{
#ifdef TRACE
						std::pair<blackboard_set_iterator, bool> result(bsa[r_t->second.idx].insert(*b_it));
						std::wcout << L"added ";
						if (!result.second)
							std::wcout << L"again ";
						blackboard_serializer()(std::wcout, *result.first) << L" to " << r_t->second.wlabel() << std::endl;
#else
						bsa[r_t->second.idx].insert(*b_it);
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
					for (blackboard_set_const_iterator b_it(bsa[r_s->second.idx].begin()); b_it != bsa[r_s->second.idx].end(); ++b_it)
					{
						blackboard b_t(*b_it);
#ifdef TRACE
						std::pair<blackboard_set_iterator, bool> result(bsa[r_t->second.idx].insert(gamma(b_t, r_s->second.src_ref, r_s->second.outgoing_consuming_transitions.front().input)));
						std::wcout << L"added ";
						if (!result.second)
							std::wcout << L"again ";
						blackboard_serializer()(std::wcout, *result.first) << L" to " << r_t->second.wlabel() << std::endl;
#else
						bsa[r_t->second.idx].insert(gamma(b_t, r_s->second.src_ref, r_s->second.outgoing_consuming_transitions.front().input));
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
						if (bsa[r_c->second.idx].empty())
						{
							bsa[r_c->second.idx].insert(empty_blackboard);
#ifdef TRACE
							blackboard_serializer()(std::wcout << L"added ", empty_blackboard) << L" to " << r_c->second.wlabel() << std::endl;
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
					std::wcout << r_t->second.wlabel() << " ifptc = " << r_t->second.ifptc << std::endl;
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
			result.swap(bsa[0]);
#ifdef TRACE
			std::wcout << L"End of blackboard set expansion\n";
#endif
			return result;
		}
	};
}

#endif /*GRAPENLP_FPRTN_BLACKBOARD_SET_EXPANDER_H*/
