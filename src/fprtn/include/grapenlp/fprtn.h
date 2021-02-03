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

#ifndef GRAPENLP_FPRTN_H
#define GRAPENLP_FPRTN_H

#ifdef TRACE
#include <iostream>
#include <boost/lexical_cast.hpp>
#endif

#include <string>
#include <algorithm>
#include <queue>
#include <grapenlp/list.h>
//#include <grapenlp/set.h>
#include <grapenlp/empty_class.h>

namespace grapenlp
{
	template<typename SourceRef, typename TagInput, typename StateData=empty_class, typename IncomingFilteredPopTransitionData=empty_class>
	class fprtn
	{
		public:
			typedef fprtn<SourceRef, TagInput, IncomingFilteredPopTransitionData> this_type;
			typedef SourceRef source_ref;
			typedef TagInput tag_input;
			typedef StateData state_data;
			typedef IncomingFilteredPopTransitionData incoming_filtered_pop_transition_data;

		class state;

		typedef typename state::ref state_ref;
		typedef typename state::const_ref state_const_ref;
		typedef typename state::ref_list state_ref_list;
		typedef typename state_ref_list::iterator state_ref_list_iterator;
		typedef typename state_ref_list::const_iterator state_ref_list_const_iterator;

		//Consuming transition types
		struct outgoing_consuming_transition
		{
			//We choose here a set instead of a list for optimization reasons;
			//A set would ensure no consuming transitions are added twice;
			//However, this happens in very few cases, and the overhead
			//of processing twice these transitions does not compensate
			//the overhead of managing a set instead of a list
//			typedef std::set<outgoing_consuming_transition> set;
			typedef std::list<outgoing_consuming_transition> set;
			typedef typename set::iterator iterator;

			TagInput input;
			state_ref target;
			//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
			//however, the iterator is not considered when sorting transitions and therefore can be modified
			//moreover, it must be mutable so that a transition an its reverse can be reflexively linked
			mutable iterator r_trans_it;

			outgoing_consuming_transition(const TagInput& input_, state_ref target_, iterator r_trans_it_ = iterator()): input(input_), target(target_), r_trans_it(r_trans_it_)
			{}

			bool operator< (const outgoing_consuming_transition& oct) const
			{
				if (input < oct.input)
					return true;
				if (oct.input < input)
					return false;
				return target < oct.target;
			}

			bool operator== (const outgoing_consuming_transition& oct) const
			{ return input == oct.input && target == oct.target; }

			bool operator!= (const outgoing_consuming_transition& oct) const
			{ return input != oct.input && target == oct.target; }
		};

		typedef typename outgoing_consuming_transition::set outgoing_consuming_transition_set;
		typedef typename outgoing_consuming_transition::iterator outgoing_consuming_transition_iterator;


		//Epsilon transition types
		struct outgoing_epsilon_transition
		{
			//Epsilon transitions are never added twice; a list here is the best option
			typedef std::list<outgoing_epsilon_transition> set;
			typedef typename set::iterator iterator;

			TagInput input;
			state_ref target;
			//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
			//however, the iterator is not considered when sorting transitions and therefore can be modified
			//moreover, it must be mutable so that a transition an its reverse can be reflexively linked
			mutable iterator r_trans_it;

			outgoing_epsilon_transition(state_ref target_, iterator r_trans_it_ = iterator()): target(target_), r_trans_it(r_trans_it_)
			{}

			bool operator< (const outgoing_epsilon_transition& oet) const
			{ return target < oet.target; }

			bool operator== (const outgoing_epsilon_transition& oet) const
			{ return target == oet.target; }

			bool operator!= (const outgoing_epsilon_transition& oet) const
			{ return target != oet.target; }
		};

		typedef typename outgoing_epsilon_transition::set outgoing_epsilon_transition_set;
		typedef typename outgoing_epsilon_transition::iterator outgoing_epsilon_transition_iterator;

		//Call transition types
		struct outgoing_call_transition
		{
			//The parsing algorithm already ensures that no call transition is added twice; a list here is the best option
			typedef std::list<outgoing_call_transition> set;
			typedef typename set::iterator iterator;

			state_ref called;
			state_ref target;
			//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
			//however, the iterator is not considered when sorting transitions and therefore can be modified
			//moreover, it must be mutable so that a transition an its reverse can be reflexively linked
			mutable iterator r_trans_it;

			outgoing_call_transition(state_ref called_, state_ref target_, iterator r_trans_it_ = iterator()): called(called_), target(target_), r_trans_it(r_trans_it_)
			{}

			bool operator< (const outgoing_call_transition& oct) const
			{
				if (called < oct.called)
					return true;
				if (oct.called < called)
					return false;
				return target < oct.target;
			}

			bool operator== (const outgoing_call_transition& oct) const
			{ return called == oct.called && target == oct.target; }

			bool operator!= (const outgoing_call_transition& oct) const
			{ return called != oct.called || target != oct.target; }
		};

		typedef typename outgoing_call_transition::set outgoing_call_transition_set;
		typedef typename outgoing_call_transition::iterator outgoing_call_transition_iterator;

		//Push transitions are only used for drawing the FPRTNs but not for parsing
		//Instead of explicitly defining them, we deduce them from the presence of call transitions

		//Filtered-pop transition types
		struct incoming_filtered_pop_transition;
		typedef typename incoming_filtered_pop_transition::set incoming_filtered_pop_transition_set;
		typedef typename incoming_filtered_pop_transition::iterator incoming_filtered_pop_transition_iterator;

		struct outgoing_filtered_pop_transition
		{
			typedef std::list<outgoing_filtered_pop_transition> set;
			typedef typename set::iterator iterator;

			TagInput input;
			state_ref target;
			//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
			//however, the iterator is not considered when sorting transitions and therefore can be modified
			//moreover, it must be mutable so that a transition an its reverse can be reflexively linked
			mutable incoming_filtered_pop_transition_iterator r_trans_it;

			outgoing_filtered_pop_transition(state_ref target_, incoming_filtered_pop_transition_iterator r_trans_it_ = incoming_filtered_pop_transition_iterator()): target(target_), r_trans_it(r_trans_it_)
			{}

			bool operator< (const outgoing_filtered_pop_transition& ofpt) const
			{ return target < ofpt.target; }

			bool operator== (const outgoing_filtered_pop_transition& ofpt) const
			{ return target == ofpt.target; }

			bool operator!= (const outgoing_filtered_pop_transition& ofpt) const
			{ return target != ofpt.target; }
		};

		typedef typename outgoing_filtered_pop_transition::set outgoing_filtered_pop_transition_set;
		typedef typename outgoing_filtered_pop_transition::iterator outgoing_filtered_pop_transition_iterator;

		//The incoming version contains map zeta_pps
		struct incoming_filtered_pop_transition: public incoming_filtered_pop_transition_data
		{
			typedef std::list<incoming_filtered_pop_transition> set;
			typedef typename set::iterator iterator;

			TagInput input;
			state_ref target;
			//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
			//however, the iterator is not considered when sorting transitions and therefore can be modified
			//moreover, it must be mutable so that a transition an its reverse can be reflexively linked
			mutable outgoing_filtered_pop_transition_iterator r_trans_it;
			//List of source states of call transitions completed by this filtered-pop transition

			incoming_filtered_pop_transition(state_ref target_, outgoing_filtered_pop_transition_iterator r_trans_it_ = outgoing_filtered_pop_transition_iterator()): incoming_filtered_pop_transition_data(), target(target_), r_trans_it(r_trans_it_)
			{}

			bool operator< (const incoming_filtered_pop_transition& ofpt) const
			{ return target < ofpt.target; }

			bool operator== (const incoming_filtered_pop_transition& ofpt) const
			{ return target == ofpt.target; }

			bool operator!= (const incoming_filtered_pop_transition& ofpt) const
			{ return target != ofpt.target; }
		};

		class state: public state_data
		{
		public:
			typedef state* ref;
			typedef const state* const_ref;
			typedef ptr_list<state> ref_list;
			typedef std::queue<ref> ref_queue;

#ifdef TRACE
			const char letter;
			const size_t number;
#endif
		protected:
			bool initial_flag, final_flag;//, reached_flag;

		public:
			SourceRef src_ref;
			bool reached_flag;

			outgoing_epsilon_transition_set outgoing_epsilon_transitions;
			outgoing_consuming_transition_set outgoing_consuming_transitions;
			outgoing_call_transition_set outgoing_call_transitions;
			outgoing_filtered_pop_transition_set outgoing_filtered_pop_transitions;

			outgoing_epsilon_transition_set incoming_epsilon_transitions;
			outgoing_consuming_transition_set incoming_consuming_transitions;
			outgoing_call_transition_set incoming_call_transitions;
			incoming_filtered_pop_transition_set incoming_filtered_pop_transitions;

			state(
#ifdef TRACE
					char letter_,
					size_t number_,
#endif
					bool initial_flag_, bool final_flag_, SourceRef src_ref_):
					state_data(),
#ifdef TRACE
					letter(letter_),
					number(number_),
#endif
					initial_flag(initial_flag_), final_flag(final_flag_), src_ref(src_ref_), reached_flag(false),
					outgoing_epsilon_transitions(), outgoing_consuming_transitions(), outgoing_call_transitions(),
					outgoing_filtered_pop_transitions(),
					incoming_epsilon_transitions(), incoming_consuming_transitions(), incoming_call_transitions(),
					incoming_filtered_pop_transitions()
			{}

#ifdef TRACE
			template<typename CharT, typename Traits>
			std::basic_string<CharT, Traits> basic_label() const
			{
				CharT letter_string[2];
				letter_string[0] = letter;
				letter_string[1] = '\0';
				return std::basic_string<CharT, Traits>(letter_string) + boost::lexical_cast<std::basic_string<CharT, Traits> >((unsigned int)number);
			}

			std::string label() const
			{ return basic_label<char, std::char_traits<char> >(); }

			std::wstring wlabel() const
			{ return basic_label<wchar_t, std::char_traits<wchar_t> >(); }

			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits> &out) const
			{ return out << letter << boost::lexical_cast<std::basic_string<CharT, Traits> >((unsigned int)number); }
#endif

		public:

			//Add consuming transition
/*			void add_consuming_transition(const TagInput& input, ref target)
			{
#ifdef TRACE
				std::wcout << L"add consuming transition (" << wlabel() << ", " << input << ", " << target->wlabel() << ")\n";
#endif

				std::pair<outgoing_consuming_transition_iterator, bool> result(outgoing_consuming_transitions.insert(outgoing_consuming_transition(input, target, outgoing_consuming_transitions.end())));
				if (result.second)
				{
//					std::wcout << L"add in consuming " << wlabel() << L" -> " << ref->wlabel() << L" with input " << input << std::endl;
					result.first->r_trans_it = target->incoming_consuming_transitions.insert(outgoing_consuming_transition(input, this, result.first)).first;
				}
#ifdef TRACE
				else std::wcout << L"Duplicated consuming\n";
#endif
			}*/

			//Add consuming transition
			void add_consuming_transition(const TagInput& input, ref target)
			{
#ifdef TRACE
				std::wcout << L"add consuming transition (" << wlabel() << ", " << input << ", " << target->wlabel() << ")\n";
				if (includes(outgoing_consuming_transitions.begin(), outgoing_consuming_transitions.end(), outgoing_consuming_transition(input, target)))
						std::wcout << L"Duplicated consuming transition\n";
#endif

				outgoing_consuming_transitions.push_back(outgoing_consuming_transition(input, target));
//				std::wcout << L"add in consuming " << wlabel() << L" -> " << ref->wlabel() << L" with input " << input << std::endl;
				target->incoming_consuming_transitions.push_back(outgoing_consuming_transition(input, this, --outgoing_consuming_transitions.end()));
				outgoing_consuming_transitions.back().r_trans_it = --target->incoming_consuming_transitions.end();
			}

			//Add epsilon transition
/*			void add_epsilon_transition(ref target)
			{
#ifdef TRACE
				std::wcout << L"add epsilon transition (" << wlabel() << ", <E>, " << target->wlabel() << ")\n";
#endif
				std::pair<outgoing_epsilon_transition_iterator, bool> result(outgoing_epsilon_transitions.insert(outgoing_epsilon_transition(target, outgoing_epsilon_transitions.end())));
				if (result.second)
					result.first->r_trans_it = target->incoming_epsilon_transitions.insert(outgoing_epsilon_transition(this, result.first)).first;
#ifdef TRACE
				else std::wcout << L"Duplicated epsilon\n";
#endif
			}*/

			//Add epsilon transition
			void add_epsilon_transition(ref target)
			{
#ifdef TRACE
				std::wcout << L"add epsilon transition (" << wlabel() << ", <E>, " << target->wlabel() << ")\n";
				if (includes(outgoing_epsilon_transitions.begin(), outgoing_epsilon_transitions.end(), outgoing_epsilon_transition(target)))
						std::wcout << L"Duplicated epsilon transition\n";
#endif
				outgoing_epsilon_transitions.push_back(outgoing_epsilon_transition(target));
				target->incoming_epsilon_transitions.push_back(outgoing_epsilon_transition(this, --outgoing_epsilon_transitions.end()));
				outgoing_epsilon_transitions.back().r_trans_it = --(target->incoming_epsilon_transitions.end());
			}

			//Add call transition
/*			void add_call_transition(ref called, ref target)
			{
#ifdef TRACE
				std::wcout << L"add call transition (" << wlabel() << ", {" << called->wlabel() << "}, " << target->wlabel() << ")\n";
#endif
				std::pair<outgoing_call_transition_iterator, bool> result(outgoing_call_transitions.insert(outgoing_call_transition(called, target, outgoing_call_transitions.end())));
				if (result.second)
				{ result.first->r_trans_it = target->incoming_call_transitions.insert(outgoing_call_transition(called, this, result.first)).first; }
#ifdef TRACE
				else std::wcout << L"Duplicated call\n";
#endif
			}*/

			void add_call_transition(ref called, ref target)
			{
#ifdef TRACE
				std::wcout << L"add call transition (" << wlabel() << ", {" << called->wlabel() << "}, " << target->wlabel() << ")\n";
				if (includes(outgoing_call_transitions.begin(), outgoing_call_transitions.end(), outgoing_call_transition(called, target)))
						std::wcout << L"Duplicated call transition\n";
#endif
				outgoing_call_transitions.push_back(outgoing_call_transition(called, target));
				target->incoming_call_transitions.push_back(outgoing_call_transition(called, this, --outgoing_call_transitions.end()));
				outgoing_call_transitions.back().r_trans_it = --target->incoming_call_transitions.end();
			}

			//Add filtered-pop transition
/*			void add_filtered_pop_transition(ref target)
			{
#ifdef TRACE
				const wchar_t up_arrow(0x2191);
				std::wcout << L"add filtered pop transition (" << wlabel() << ", " << target->wlabel() << up_arrow << ", " << target->wlabel() << ")\n";
#endif
				std::pair<outgoing_filtered_pop_transition_iterator, bool> result(outgoing_filtered_pop_transitions.insert(outgoing_filtered_pop_transition(target, outgoing_filtered_pop_transitions.end())));
				if (result.second)
					result.first->r_trans_it = target->incoming_filtered_pop_transitions.insert(outgoing_filtered_pop_transition(this, result.first)).first;
#ifdef TRACE
				else std::wcout << L"Duplicated filtered pop\n";
#endif
			}*/

			//Add filtered-pop transition
			void add_filtered_pop_transition(ref target)
			{
#ifdef TRACE
				const wchar_t up_arrow(0x2191);
				std::wcout << L"add filtered pop transition (" << wlabel() << ", " << target->wlabel() << up_arrow << ", " << target->wlabel() << ")\n";
				if (includes(outgoing_filtered_pop_transitions.begin(), outgoing_filtered_pop_transitions.end(), outgoing_filtered_pop_transition(target)))
						std::wcout << L"Duplicated filtered_pop transition\n";
#endif
				outgoing_filtered_pop_transitions.push_back(outgoing_filtered_pop_transition(target));
				target->incoming_filtered_pop_transitions.push_back(incoming_filtered_pop_transition(this, --outgoing_filtered_pop_transitions.end()));
				outgoing_filtered_pop_transitions.back().r_trans_it = --(target->incoming_filtered_pop_transitions.end());
			}


			void remove_foreign_consuming_transitions()
			{
				outgoing_consuming_transition_iterator oct_it;
				for (oct_it = outgoing_consuming_transitions.begin(); oct_it != outgoing_consuming_transitions.end(); ++oct_it)
				{
#ifdef TRACE
					std::wcout << L"removing out consuming " << wlabel() << L" -> " << oct_it->target->wlabel() << L" with input " << oct_it->input << std::endl;
#endif
					oct_it->target->incoming_consuming_transitions.erase(oct_it->r_trans_it);
				}
				for (oct_it = incoming_consuming_transitions.begin(); oct_it != incoming_consuming_transitions.end(); ++oct_it)
				{
#ifdef TRACE
					std::wcout << L"removing in consuming " << wlabel() << L" -> " << oct_it->target->wlabel() << L" with input " << oct_it->input << std::endl;
#endif
					oct_it->target->outgoing_consuming_transitions.erase(oct_it->r_trans_it);
				}
			}

			void remove_foreign_call_transitions()
			{
				outgoing_call_transition_iterator oct_it;
				for (oct_it = outgoing_call_transitions.begin(); oct_it != outgoing_call_transitions.end(); ++oct_it)
				{
#ifdef TRACE
					std::wcout << L"removing out call " << wlabel() << L" -> " << oct_it->target->wlabel() << L" with call to " << oct_it->called->wlabel() << std::endl;
#endif
					oct_it->target->incoming_call_transitions.erase(oct_it->r_trans_it);
				}
				for (oct_it = incoming_call_transitions.begin(); oct_it != incoming_call_transitions.end(); ++oct_it)
				{
#ifdef TRACE
					std::wcout << L"removing in call " << wlabel() << L" -> " << oct_it->target->wlabel() << L" with call to " << oct_it->called->wlabel() << std::endl;
#endif
					oct_it->target->outgoing_call_transitions.erase(oct_it->r_trans_it);
				}
			}

			void remove_foreign_epsilon_transitions()
			{
				outgoing_epsilon_transition_iterator oet_it;
				for (oet_it = outgoing_epsilon_transitions.begin(); oet_it != outgoing_epsilon_transitions.end(); ++oet_it)
				{
#ifdef TRACE
					std::wcout << L"removing out epsilon " << wlabel() << L" -> " << oet_it->target->wlabel() << std::endl;
#endif
					oet_it->target->incoming_epsilon_transitions.erase(oet_it->r_trans_it);
				}
				for (oet_it = incoming_epsilon_transitions.begin(); oet_it != incoming_epsilon_transitions.end(); ++oet_it)
				{
#ifdef TRACE
					std::wcout << L"removing in epsilon " << wlabel() << L" -> " << oet_it->target->wlabel() << std::endl;
#endif
					oet_it->target->outgoing_epsilon_transitions.erase(oet_it->r_trans_it);
				}
			}

			void remove_foreign_filtered_pop_transitions()
			{
				for (outgoing_filtered_pop_transition_iterator ofpt_it(outgoing_filtered_pop_transitions.begin()); ofpt_it != outgoing_filtered_pop_transitions.end(); ++ofpt_it)
				{
#ifdef TRACE
					std::wcout << L"removing out filtered pop " << wlabel() << L" -> " << ofpt_it->target->wlabel() << std::endl;
#endif
					ofpt_it->target->incoming_filtered_pop_transitions.erase(ofpt_it->r_trans_it);
				}
				for (incoming_filtered_pop_transition_iterator ifpt_it = incoming_filtered_pop_transitions.begin(); ifpt_it != incoming_filtered_pop_transitions.end(); ++ifpt_it)
				{
#ifdef TRACE
					std::wcout << L"removing in filtered pop " << wlabel() << L" -> " << ifpt_it->target->wlabel() << std::endl;
#endif
					ifpt_it->target->outgoing_filtered_pop_transitions.erase(ifpt_it->r_trans_it);
				}
			}

			void remove_foreign_transitions()
			{
				remove_foreign_consuming_transitions();
				remove_foreign_epsilon_transitions();
				remove_foreign_call_transitions();
				remove_foreign_filtered_pop_transitions();
			}

			bool is_initial() const
			{ return initial_flag; }

			bool is_final() const
			{ return final_flag; }
		};

		typedef typename state::ref_queue state_ref_queue;

#ifdef TRACE
	public:
		const char state_label_letter;
	protected:
		size_t state_label_counter;
#endif

	public:
		state_ref_list ini_states, other_states;

#ifdef TRACE
		fprtn(const char state_label_letter_): state_label_letter(state_label_letter_), state_label_counter(-1), ini_states(), other_states()
		{}
#else
		fprtn(): ini_states(), other_states()
		{}
#endif

		typename state::ref create_initial_state(bool final_flag, SourceRef src_ref)
		{
			ini_states.push_back(new state(
#ifdef TRACE
				state_label_letter,
				++state_label_counter,
#endif
				true, final_flag, src_ref));
			return ini_states.back();
		}

		typename state::ref create_non_initial_state(bool final_flag, SourceRef src_ref)
		{
			other_states.push_back(new state(
#ifdef TRACE
				state_label_letter,
				++state_label_counter,
#endif
				false, final_flag, src_ref));
			return other_states.back();
		}

		state_ref create_state(bool initial_flag, bool final_flag)
		{
			if (initial_flag)
				return create_initial_state(final_flag);
			return create_non_initial_state(final_flag);
		}

		void delete_state(typename state::ref s)
		{
			s->remove_foreign_transitions();
			if (s->is_initial())
				ini_states.erase(s);
			else other_states.erase(s);
		}

		void clear()
		{
			ini_states.clear();
			other_states.clear();
		}

/*		template<typename SourceRef, typename TagInput, typename Iterator>
		typename fprtn<SourceRef, TagInput>::state::ref add_non_empty_sequence(fprtn<SourceRef, TagInput>& f, typename fprtn<SourceRef, TagInput>::state::ref src_state, Iterator begin, Iterator end, bool final, SourceRef src_ref)
		{
			Iterator i;
			Iterator last = end - 1;
			typename fprtn<SourceRef, TagInput>::state::ref dest_state;
			for (i = begin; i != last; ++i)
			{
				dest_state = f.create_non_initial_state(false, src_ref);
				src_state->add_transition(*i, dest_state);
				src_state = dest_state;
			}

			dest_state = f.create_non_initial_state(final, src_ref);
			src_state->add_transition(*i, dest_state);
			return dest_state;
		}
*/
		//Add sequence path from state src_state to a new state
/*		template<typename SourceRef, typename TagInput, typename Iterator>
		typename fprtn<SourceRef, TagInput>::state::ref add_sequence(fprtn<SourceRef, TagInput>& f, typename fprtn<SourceRef, TagInput>::state::ref src_state, Iterator begin, Iterator end, bool final, SourceRef src_ref)
		{
			if (begin == end)
			{
				typename fprtn<SourceRef, TagInput>::state::ref dest_state = f.create_non_initial_state(final, src_ref);
				src_state->add_transition(dest_state);
				return dest_state;
			}
			return add_non_empty_sequence(f, src_state, begin, end, final, src_ref);
		}
*/
		//Add sequence path from state src_state to dest_src
/*		template<typename SourceRef, typename TagInput, typename Iterator>
		typename fprtn<SourceRef, TagInput>::state::ref add_sequence(fprtn<SourceRef, TagInput>& f, typename fprtn<SourceRef, TagInput>::state::ref src_state, typename fprtn<SourceRef, TagInput>::state::ref dest_state, Iterator begin, Iterator end)
		{
			if (begin == end)
			{
				src_state->add_transition(dest_state);
				return dest_state;
			}

			--end;
			if (begin != end)
				src_state = add_non_empty_sequence(f, src_state, begin, end, false, dest_state->src_ref);
			src_state->add_transition(*end, dest_state);
			return dest_state;
		}*/


		/*
		 * Given a set of states of a FPRTN, removes the ones that are marked as unreachable
		 */
		void remove_unreachable_states(state_ref_list &states)
		{
			state_ref_list_iterator n(states.begin());
			state_ref_list_iterator n_to_erase;
			while (n != states.end())
			{
				//If the state is not reachable,
				if (!(*n)->reached_flag)
				{
#ifdef TRACE
					std::wcout << L"removing state " << (*n)->wlabel() << std::endl;
#endif
					//remove every incoming transition
					(*n)->remove_foreign_transitions();
					//advance initial state iterator before deleting the current initial state!!
					n_to_erase = n;
					++n;
					//and delete current initial state
					states.erase(n_to_erase);
				}
				//If it is reachable, just go for the next initial state
				else
				{
#ifdef TRACE
					std::wcout << (*n)->wlabel() << L" is useful" << std::endl;
#endif
					++n;
				}
			}
		}

		void remove_unreachable_states()
		{
#ifdef TRACE
			std::wcout << L"remove useless initial states\n";
#endif
			remove_unreachable_states(ini_states);

#ifdef TRACE
			std::wcout << L"remove useless non-initial states\n";
#endif
			remove_unreachable_states(other_states);
		}

		//Remove all paths which do not reach the specified state from anywhere.
		//Notice that after parsing, every state in the FPRTN is derivable from an initial state except
		//the ones belonging to uncompleted calls, and that the algorithm creates a single
		//global final state, thus by specifying this final state as argument for this method
		//the FPRTN will be pruned (every useless path will be deleted)
		fprtn& output_fprtn_prune(state_ref path_target_state)
		{
#ifdef TRACE
			std::wcout << L"Begin removing unused paths\n";
#endif

			//If there are no popping transitions towards the final state,
			//the FPRTN is equivalent to an empty FPRTN, so clear it and return
			if (path_target_state->incoming_filtered_pop_transitions.empty())
			{
#ifdef TRACE
				std::wcout << L"FPRTN cleared: no interpretations found\n";
#endif
				clear();
				return *this;
			}

			state_ref_queue pending_states;
			state_ref s;
/*
			typename fprtn<SourceRef, TagInput>::outgoing_epsilon_transition_iterator oet_it;
			typename fprtn<SourceRef, TagInput>::outgoing_call_transition_iterator ocallt_it;
			typename fprtn<SourceRef, TagInput>::outgoing_filtered_pop_transition_iterator ofpt_it;
*/
			//Otherwise, begin by marking the final state as a reachable state
			path_target_state->reached_flag = true;
#ifdef TRACE
			std::wcout << L"start search of reversely reachable states from " << path_target_state->wlabel() << std::endl;
#endif
			//And add the final state to the queue of states to process
			pending_states.push(path_target_state);

			//While there are states to pending to be processed
			while (!pending_states.empty())
			{
				//Pop next state to process
				s = pending_states.front();
				pending_states.pop();
				//For every consuming transition coming to the current state,
				//mark its source state as reachable and add it to the queue
				for (outgoing_consuming_transition_iterator oconst_it(s->incoming_consuming_transitions.begin()); oconst_it != s->incoming_consuming_transitions.end(); ++oconst_it)
				{
					if (!oconst_it->target->reached_flag)
					{
#ifdef TRACE
						std::wcout << L"reached state " << oconst_it->target->wlabel() << L" from " << s->wlabel() << std::endl;
#endif
						oconst_it->target->reached_flag = true;
						pending_states.push(oconst_it->target);
					}
				}
				//For every consuming transition coming to the current state,
				//mark its source state as reachable and add it to the queue
				for (outgoing_epsilon_transition_iterator oet_it(s->incoming_epsilon_transitions.begin()); oet_it != s->incoming_epsilon_transitions.end(); ++oet_it)
				{
					if (!oet_it->target->reached_flag)
					{
#ifdef TRACE
						std::wcout << L"reached state " << oet_it->target->wlabel() << L" from " << s->wlabel() << std::endl;
#endif
						oet_it->target->reached_flag = true;
						pending_states.push(oet_it->target);
					}
				}
				//For every call transition coming to this state,
				//mark its source state as reachable and add it to the queue
				for (outgoing_call_transition_iterator ocallt_it(s->incoming_call_transitions.begin()); ocallt_it != s->incoming_call_transitions.end(); ++ocallt_it)
				{
					if (!ocallt_it->target->reached_flag)
					{
#ifdef TRACE

						std::wcout << L"reached state " << ocallt_it->target->wlabel() << L" from " << s->wlabel() << std::endl;
#endif
						ocallt_it->target->reached_flag = true;
						pending_states.push(ocallt_it->target);
					}
				}
				//For every popping transition coming to this state,
				//mark its source state as reachable and add it to the queue
				for (incoming_filtered_pop_transition_iterator ifpt_it(s->incoming_filtered_pop_transitions.begin()); ifpt_it != s->incoming_filtered_pop_transitions.end(); ++ifpt_it)
				{
					if (!ifpt_it->target->reached_flag)
					{
#ifdef TRACE

						std::wcout << L"reached state " << ifpt_it->target->wlabel() << L" from " << s->wlabel() << std::endl;
#endif
						ifpt_it->target->reached_flag = true;
						pending_states.push(ifpt_it->target);
					}
				}
			}

			remove_unreachable_states();

#ifdef TRACE
			std::wcout << L"End removing unused paths\n";
#endif
			return *this;
		}
	};

	template<typename SourceRef, typename TagInput>
	bool operator== (const typename fprtn<SourceRef, TagInput>::state& q1, const typename fprtn<SourceRef, TagInput>::state& q2)
	{
		return &q1 == &q2;
	}

	template<typename SourceRef, typename TagInput>
	bool operator< (const typename fprtn<SourceRef, TagInput>::state& q1, const typename fprtn<SourceRef, TagInput>::state& q2)
	{
		return &q1 < &q2;
	}
}

#endif /*GRAPENLP_FPRTN_H*/
