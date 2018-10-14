/*
 * GRAPE
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

#ifndef GRAPE_OUTPUT_FPRTN_H
#define GRAPE_OUTPUT_FPRTN_H

#ifdef TRACE
#include <iostream>
#include <boost/lexical_cast.hpp>
#endif

#include <string>
#include <algorithm>
#include <queue>
#include <limits>
#include <grape/array.h>
#include <grape/list.h>
#include <grape/empty_class.h>
#include <grape/map_impl_selector.h>
#include <grape/earley_parser_no_output.h>

#define UP_ARROW static_cast<wchar_t>(0x2191)

namespace grape
{
	enum output_fprtn_incoming_filtered_pop_transition_extra_data_choice {NO_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, ZPPS_ITERATOR_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	class output_fprtn_state;

	//Consuming transition types
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_outgoing_consuming_transition
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef output_fprtn_outgoing_consuming_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> this_type;
		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>* state_ref;

		//We choose here a list instead of a set for optimization reasons;
		//A set would ensure no consuming transitions are added twice;
		//However, this happens in very few cases, and the overhead
		//of processing twice these transitions is less than the overhead
		//of managing a set instead of a list
//			typedef std::set<this_type> set;
		typedef std::list<this_type> set;
		typedef typename set::iterator iterator;

		TagInput input;
		state_ref target;
		//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
		//however, the iterator is not considered when sorting transitions within a set (but not a list) and therefore can be modified
		//moreover, it must be mutable so that a transition an its reverse can be reflexively linked (but not for lists)
		/*mutable*/ iterator r_trans_it;

		output_fprtn_outgoing_consuming_transition(const TagInput& input_, state_ref target_, iterator r_trans_it_ = iterator()): input(input_), target(target_), r_trans_it(r_trans_it_)
		{}

/*		bool operator< (const output_fprtn_outgoing_consuming_transition& oct) const
		{
			if (input < oct.input)
				return true;
			if (oct.input < input)
				return false;
			return target < oct.target;
		}
*/	};

	//Epsilon transition types
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_outgoing_epsilon_transition
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef output_fprtn_outgoing_epsilon_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> this_type;
		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>* state_ref;

		//Epsilon transitions are never added twice; a list here is the best option
		typedef std::list<this_type> set;
		typedef typename set::iterator iterator;

		TagInput input;
		state_ref target;
		//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
		//however, the iterator is not considered when sorting transitions within a set (but not a list) and therefore can be modified
		//moreover, it must be mutable so that a transition an its reverse can be reflexively linked (but not for lists)
		/*mutable*/ iterator r_trans_it;

		output_fprtn_outgoing_epsilon_transition(state_ref target_, iterator r_trans_it_ = iterator()): target(target_), r_trans_it(r_trans_it_)
		{}

//		bool operator< (const output_fprtn_outgoing_epsilon_transition& oet) const
//		{ return target < oet.target; }
	};

	//Call transition types
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_outgoing_call_transition
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef output_fprtn_outgoing_call_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> this_type;
		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>* state_ref;

		//The parsing algorithm already ensures that no call transition is added twice; a list here is the best option
		typedef std::list<this_type> set;
		typedef typename set::iterator iterator;

		state_ref called;
		state_ref target;
		//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
		//however, the iterator is not considered when sorting transitions within a set (but not a list) and therefore can be modified
		//moreover, it must be mutable so that a transition an its reverse can be reflexively linked (but not for lists)
		/*mutable*/ iterator r_trans_it;

		output_fprtn_outgoing_call_transition(state_ref called_, state_ref target_, iterator r_trans_it_ = iterator()): called(called_), target(target_), r_trans_it(r_trans_it_)
		{}

/*		bool operator< (const output_fprtn_outgoing_call_transition& oct) const
		{
			if (called < oct.called)
				return true;
			if (oct.called < called)
				return false;
			return target < oct.target;
		}*/
	};

	//Push transitions are only used for drawing the OUTPUT_FPRTNs but not for parsing
	//Instead of explicitly defining them, we deduce them from the presence of call transitions

	//Filtered-pop transition types
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_incoming_filtered_pop_transition;

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_outgoing_filtered_pop_transition
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef output_fprtn_outgoing_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> this_type;
		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>* state_ref;
		typedef output_fprtn_incoming_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> incoming_filtered_pop_transition;
		typedef typename incoming_filtered_pop_transition::iterator incoming_filtered_pop_transition_iterator;
		typedef std::list<this_type> set;
		typedef typename set::iterator iterator;

		TagInput input;
		state_ref target;
		//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
		//however, the iterator is not considered when sorting transitions within a set (but not a list) and therefore can be modified
		//moreover, it must be mutable so that a transition an its reverse can be reflexively linked (but not for lists)
		/*mutable*/ incoming_filtered_pop_transition_iterator r_trans_it;

		output_fprtn_outgoing_filtered_pop_transition(state_ref target_): target(target_)
		{}

//		bool operator< (const output_fprtn_outgoing_filtered_pop_transition& ofpt) const
//		{ return target < ofpt.target; }
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_incoming_filtered_pop_transition
	{};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, typename StateMappedExtraData>
	struct output_fprtn_incoming_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, NO_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, StateMappedExtraData>
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef output_fprtn_incoming_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, NO_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, state_mapped_extra_data> this_type;
		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, NO_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, state_mapped_extra_data>* state_ref;
		typedef output_fprtn_outgoing_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, NO_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, state_mapped_extra_data> outgoing_filtered_pop_transition;
//		typedef typename outgoing_filtered_pop_transition::iterator outgoing_filtered_pop_transition_iterator;
		typedef typename std::list<outgoing_filtered_pop_transition>::iterator outgoing_filtered_pop_transition_iterator;
		typedef std::list<this_type> set;
		typedef typename set::iterator iterator;

		TagInput input;
		state_ref target;
		//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
		//however, the iterator is not considered when sorting transitions within a set (but not a list) and therefore can be modified
		//moreover, it must be mutable so that a transition an its reverse can be reflexively linked (but not for lists)
		/*mutable*/ outgoing_filtered_pop_transition_iterator r_trans_it;

		output_fprtn_incoming_filtered_pop_transition(state_ref target_, outgoing_filtered_pop_transition_iterator r_trans_it_): target(target_), r_trans_it(r_trans_it_)
		{}

//		bool operator< (const output_fprtn_incoming_filtered_pop_transition& ofpt) const
//		{ return target < ofpt.target; }
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_paused_execution_state_key;

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_paused_execution_state_mapped;

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_paused_execution_state;

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, typename StateMappedExtraData>
	struct output_fprtn_incoming_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, ZPPS_ITERATOR_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, StateMappedExtraData>
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef output_fprtn_incoming_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, ZPPS_ITERATOR_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, state_mapped_extra_data> this_type;
		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, ZPPS_ITERATOR_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, state_mapped_extra_data>* state_ref;
		typedef output_fprtn_outgoing_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, ZPPS_ITERATOR_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, state_mapped_extra_data> outgoing_filtered_pop_transition;
//		typedef typename outgoing_filtered_pop_transition::iterator outgoing_filtered_pop_transition_iterator;
		typedef typename std::list<outgoing_filtered_pop_transition>::iterator outgoing_filtered_pop_transition_iterator;
		typedef std::list<this_type> set;
		typedef typename set::iterator iterator;

		typedef output_fprtn_paused_execution_state_key<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, ZPPS_ITERATOR_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, state_mapped_extra_data> paused_execution_state_key;
		typedef output_fprtn_paused_execution_state_mapped<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, ZPPS_ITERATOR_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, state_mapped_extra_data> paused_execution_state_mapped;
		typedef typename map_impl_selector<execution_state_set_impl_choice, paused_execution_state_key, paused_execution_state_mapped>::type::iterator paused_execution_state_iterator;

		TagInput input;
		state_ref target;
		//reverse transition iterator is stored with the own transition structure so that the reverse of a transition can be directly accessed
		//however, the iterator is not considered when sorting transitions within a set (but not a list) and therefore can be modified
		//moreover, it must be mutable so that a transition an its reverse can be reflexively linked (but not for lists)
		/*mutable*/ outgoing_filtered_pop_transition_iterator r_trans_it;
		//Iterator towards the first paused execution state whose r is the first source state of the call transitions completed by this filtered-pop transition
		//The paused execution states of further source states, if more than one, follow the paused execution state pointed by the iterator
		//up to the paused execution state whose key does no longer match, without counting fields q and r
		paused_execution_state_iterator pes_begin;

		output_fprtn_incoming_filtered_pop_transition(state_ref target_, outgoing_filtered_pop_transition_iterator r_trans_it_, paused_execution_state_iterator pes_begin_): target(target_), r_trans_it(r_trans_it_), pes_begin(pes_begin_)
		{}

//		bool operator< (const output_fprtn_incoming_filtered_pop_transition& ofpt) const
//		{ return target < ofpt.target; }
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	struct output_fprtn_state_key: public earley_parser_no_output<RTNOTagInput, TagInput, SourceRef, execution_state_set_impl_choice>::active_execution_state
	{
		typedef typename earley_parser_no_output<RTNOTagInput, TagInput, SourceRef, execution_state_set_impl_choice>::active_execution_state base_type;
#ifdef TRACE
		typedef typename ns_rtno<RTNOTagInput, TagInput>::state::const_ref source_rtno_state_const_ref;
#else
		typedef typename rtno<RTNOTagInput, TagInput>::state::const_ref source_rtno_state_const_ref;
#endif

		output_fprtn_state_key(): base_type()
		{}

		output_fprtn_state_key(
				source_rtno_state_const_ref q_,
				source_rtno_state_const_ref q_h_,
				std::size_t i_):

				base_type(q_, q_h_, i_)
		{}

		output_fprtn_state_key(const output_fprtn_state_key &sk): base_type(sk.q, sk.q_h, sk.i)
		{}

		bool is_final() const
		{ return base_type::q->is_final(); }
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_state_mapped: public StateMappedExtraData
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef state_mapped_extra_data base_type;
		typedef typename output_fprtn_outgoing_consuming_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>::set outgoing_consuming_transition_set;
		typedef typename output_fprtn_outgoing_consuming_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>::iterator outgoing_consuming_transition_iterator;
		typedef typename output_fprtn_outgoing_epsilon_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>::set outgoing_epsilon_transition_set;
		typedef typename output_fprtn_outgoing_epsilon_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>::iterator outgoing_epsilon_transition_iterator;
		typedef typename output_fprtn_outgoing_call_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>::set outgoing_call_transition_set;
		typedef typename output_fprtn_outgoing_call_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>::iterator outgoing_call_transition_iterator;
		typedef typename output_fprtn_outgoing_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>::set outgoing_filtered_pop_transition_set;
		typedef typename output_fprtn_outgoing_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>::iterator outgoing_filtered_pop_transition_iterator;
		typedef typename output_fprtn_incoming_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>::set incoming_filtered_pop_transition_set;
		typedef typename output_fprtn_incoming_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>::iterator incoming_filtered_pop_transition_iterator;

#ifdef TRACE
		char letter;
		std::size_t number;
#endif
		SourceRef src_ref;
		bool useless_flag;

		outgoing_epsilon_transition_set outgoing_epsilon_transitions;
		outgoing_consuming_transition_set outgoing_consuming_transitions;
		outgoing_call_transition_set outgoing_call_transitions;
		outgoing_filtered_pop_transition_set outgoing_filtered_pop_transitions;

		outgoing_epsilon_transition_set incoming_epsilon_transitions;
		outgoing_consuming_transition_set incoming_consuming_transitions;
		outgoing_call_transition_set incoming_call_transitions;
		incoming_filtered_pop_transition_set incoming_filtered_pop_transitions;

		output_fprtn_state_mapped(): base_type(),
			outgoing_epsilon_transitions(), outgoing_consuming_transitions(), outgoing_call_transitions(),
			outgoing_filtered_pop_transitions(),
			incoming_epsilon_transitions(), incoming_consuming_transitions(), incoming_call_transitions(),
			incoming_filtered_pop_transitions()
		{}

		output_fprtn_state_mapped(
#ifdef TRACE
				char letter_,
				std::size_t number_,
#endif
				SourceRef src_ref_
				):
				base_type(),
#ifdef TRACE
				letter(letter_),
				number(number_),
#endif
				src_ref(src_ref_)
				//Avoid wasting time initializing here this field; Initialize it in the copy, since the original
				//object will be destroyed without using this field but it will only be used in the copy
//				useless_flag(true),
/*				outgoing_epsilon_transitions(), outgoing_consuming_transitions(), outgoing_call_transitions(),
				outgoing_filtered_pop_transitions(),
				incoming_epsilon_transitions(), incoming_consuming_transitions(), incoming_call_transitions(),
				incoming_filtered_pop_transitions()*/
		{}

		output_fprtn_state_mapped(const output_fprtn_state_mapped &sm):
				state_mapped_extra_data(static_cast<const state_mapped_extra_data&>(*this)),
#ifdef TRACE
				letter(sm.letter),
				number(sm.number),
#endif
				src_ref(sm.src_ref),
				useless_flag(true),
				outgoing_epsilon_transitions(), outgoing_consuming_transitions(), outgoing_call_transitions(),
				outgoing_filtered_pop_transitions(),
				incoming_epsilon_transitions(), incoming_consuming_transitions(), incoming_call_transitions(),
				incoming_filtered_pop_transitions()
		{}

		std::size_t transition_count() const
		{
			return outgoing_epsilon_transitions.size() +
					outgoing_consuming_transitions.size() +
					outgoing_call_transitions.size() +
					outgoing_filtered_pop_transitions.size();
		}

		bool has_no_outgoing_transitions() const
		{
			return outgoing_epsilon_transitions.empty() &&
					outgoing_consuming_transitions.empty() &&
					outgoing_call_transitions.empty() &&
					outgoing_filtered_pop_transitions.empty();
		}

		bool has_no_incoming_transitions() const
		{
			return incoming_epsilon_transitions.empty() &&
					incoming_consuming_transitions.empty() &&
					incoming_call_transitions.empty() &&
					incoming_filtered_pop_transitions.empty();
		}

#ifdef TRACE
		template<typename CharT, typename Traits>
		std::basic_string<CharT, Traits> basic_label() const
		{
			CharT letter_string[2];
			letter_string[0] = letter;
			letter_string[1] = '\0';
			return std::basic_string<CharT, Traits>(letter_string) + boost::lexical_cast<std::basic_string<CharT, Traits> >((unsigned int)number);
		}

		inline std::string label() const
		{ return basic_label<char, std::char_traits<char> >(); }

		inline std::wstring wlabel() const
		{ return basic_label<wchar_t, std::char_traits<wchar_t> >(); }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits> &out) const
		{ return out << letter << boost::lexical_cast<std::basic_string<CharT, Traits> >((unsigned int)number); }
#endif
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	class output_fprtn_state: public std::pair<const output_fprtn_state_key<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice>, output_fprtn_state_mapped<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, StateMappedExtraData> >
	{
	public:
		typedef TagInput tag_input;
		typedef StateMappedExtraData state_mapped_extra_data;
#ifdef TRACE
		typedef typename tag_serializer<tag_input>::type tag_input_serializer;
#endif

		typedef output_fprtn_outgoing_consuming_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> outgoing_consuming_transition;
		typedef typename outgoing_consuming_transition::iterator outgoing_consuming_transition_iterator;
		typedef output_fprtn_outgoing_epsilon_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> outgoing_epsilon_transition;
		typedef typename outgoing_epsilon_transition::iterator outgoing_epsilon_transition_iterator;
		typedef output_fprtn_outgoing_call_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> outgoing_call_transition;
		typedef typename outgoing_call_transition::iterator outgoing_call_transition_iterator;
		typedef output_fprtn_outgoing_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> outgoing_filtered_pop_transition;
		typedef typename outgoing_filtered_pop_transition::iterator outgoing_filtered_pop_transition_iterator;
		typedef output_fprtn_incoming_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> incoming_filtered_pop_transition;
		typedef typename incoming_filtered_pop_transition::iterator incoming_filtered_pop_transition_iterator;

#ifdef TRACE
		typedef typename ns_rtno<RTNOTagInput, TagInput>::state::const_ref source_rtno_state_const_ref;
#else
		typedef typename rtno<RTNOTagInput, TagInput>::state::const_ref source_rtno_state_const_ref;
#endif
		typedef output_fprtn_state* ref;
		typedef const output_fprtn_state* const_ref;
		typedef output_fprtn_state_key<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice> key;
		typedef output_fprtn_state_mapped<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> mapped;
		typedef std::pair<const key, mapped> base_type;
		typedef typename map_impl_selector<execution_state_set_impl_choice, key, mapped>::type map;

		typedef output_fprtn_paused_execution_state_key<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> paused_execution_state_key;
		typedef output_fprtn_paused_execution_state_mapped<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> paused_execution_state_mapped;
		typedef output_fprtn_paused_execution_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> paused_execution_state;
		typedef typename map_impl_selector<execution_state_set_impl_choice, paused_execution_state_key, paused_execution_state_mapped>::type::iterator paused_execution_state_iterator;

		output_fprtn_state(
			source_rtno_state_const_ref q_,
			source_rtno_state_const_ref q_h_,
			std::size_t i_,
#ifdef TRACE
			char letter_,
			std::size_t number_,
#endif
			SourceRef src_ref_): base_type()
		{
			const_cast<key&>(base_type::first).q = q_;
			const_cast<key&>(base_type::first).q_h = q_h_;
			const_cast<key&>(base_type::first).i = i_;
#ifdef TRACE
			base_type::second.letter = letter_;
			base_type::second.number = number_;
#endif
			base_type::second.src_ref = src_ref_;
			base_type::second.useless_flag = true;
		}

/*			inline void set_mapped(SourceRef src_ref_)
		{
			base_type::second.src_ref = src_ref_;
			base_type::second.useless_flag = true;
		}
*/
		//Add consuming transition
		void add_consuming_transition(const TagInput& input, ref target)
		{
#ifdef TRACE
			std::wcout << "add consuming transition (" << base_type::second.wlabel() << ", ";
			tag_input_serializer()(std::wcout, input) << ", " << target->second.wlabel() << ")\n";
//				if (includes(outgoing_consuming_transitions.begin(), outgoing_consuming_transitions.end(), outgoing_consuming_transition(input, target)))
//						std::wcout << "Duplicated consuming transition\n";
#endif

			base_type::second.outgoing_consuming_transitions.push_back(outgoing_consuming_transition(input, target));
			target->second.incoming_consuming_transitions.push_back(outgoing_consuming_transition(input, this, --base_type::second.outgoing_consuming_transitions.end()));
			base_type::second.outgoing_consuming_transitions.back().r_trans_it = --target->second.incoming_consuming_transitions.end();
		}

		//Add epsilon transition
/*			void add_epsilon_transition(ref target)
		{
#ifdef TRACE
			std::wcout << "add epsilon transition (" << base_type::second.wlabel() << ", <E>, " << target->second.wlabel() << ")\n";
#endif
			std::pair<outgoing_epsilon_transition_iterator, bool> result(outgoing_epsilon_transitions.insert(outgoing_epsilon_transition(target, outgoing_epsilon_transitions.end())));
			if (result.second)
				result.first->r_trans_it = target->second.incoming_epsilon_transitions.insert(outgoing_epsilon_transition(this, result.first)).first;
#ifdef TRACE
			else std::wcout << "Duplicated epsilon\n";
#endif
		}*/

		//Add epsilon transition
		void add_epsilon_transition(ref target)
		{
#ifdef TRACE
			std::wcout << "add epsilon transition (" << base_type::second.wlabel() << ", <E>, " << target->second.wlabel() << ")\n";
//				if (includes(outgoing_epsilon_transitions.begin(), outgoing_epsilon_transitions.end(), outgoing_epsilon_transition(target)))
//						std::wcout << "Duplicated epsilon transition\n";
#endif
			base_type::second.outgoing_epsilon_transitions.push_back(outgoing_epsilon_transition(target));
			target->second.incoming_epsilon_transitions.push_back(outgoing_epsilon_transition(this, --base_type::second.outgoing_epsilon_transitions.end()));
			base_type::second.outgoing_epsilon_transitions.back().r_trans_it = --(target->second.incoming_epsilon_transitions.end());
		}

		//Add call transition
/*			void add_call_transition(ref called, ref target)
		{
#ifdef TRACE
			std::wcout << "add call transition (" << base_type::second.wlabel() << ", {" << called->second.wlabel() << "}, " << target->second.wlabel() << ")\n";
#endif
			std::pair<outgoing_call_transition_iterator, bool> result(outgoing_call_transitions.insert(outgoing_call_transition(called, target, outgoing_call_transitions.end())));
			if (result.second)
			{ result.first->r_trans_it = target->second.incoming_call_transitions.insert(outgoing_call_transition(called, this, result.first)).first; }
#ifdef TRACE
			else std::wcout << "Duplicated call\n";
#endif
		}*/

		void add_call_transition(ref called, ref target)
		{
#ifdef TRACE
			std::wcout << "add call transition (" << base_type::second.wlabel() << ", {" << called->second.wlabel() << "}, " << target->second.wlabel() << ")\n";
//				if (includes(outgoing_call_transitions.begin(), outgoing_call_transitions.end(), outgoing_call_transition(called, target)))
//						std::wcout << "Duplicated call transition\n";
#endif
			base_type::second.outgoing_call_transitions.push_back(outgoing_call_transition(called, target));
			target->second.incoming_call_transitions.push_back(outgoing_call_transition(called, this, --base_type::second.outgoing_call_transitions.end()));
			base_type::second.outgoing_call_transitions.back().r_trans_it = --target->second.incoming_call_transitions.end();
		}

		//Add filtered-pop transition
/*			void add_filtered_pop_transition(ref target)
		{
#ifdef TRACE
			std::wcout << "add filtered pop transition (" << base_type::second.wlabel() << ", " << target->second.wlabel() << UP_ARROW << ", " << target->second.wlabel() << ")\n";
#endif
			std::pair<outgoing_filtered_pop_transition_iterator, bool> result(outgoing_filtered_pop_transitions.insert(outgoing_filtered_pop_transition(target, outgoing_filtered_pop_transitions.end())));
			if (result.second)
				result.first->r_trans_it = target->second.incoming_filtered_pop_transitions.insert(outgoing_filtered_pop_transition(this, result.first)).first;
#ifdef TRACE
			else std::wcout << "Duplicated filtered pop\n";
#endif
		}*/

		//Add filtered-pop transition
		void add_filtered_pop_transition(ref target)
		{
#ifdef TRACE
			std::wcout << "add filtered pop transition (" << base_type::second.wlabel() << ", " << target->second.wlabel() << UP_ARROW << ", " << target->second.wlabel() << ")\n";
//				if (includes(outgoing_filtered_pop_transitions.begin(), outgoing_filtered_pop_transitions.end(), outgoing_filtered_pop_transition(target)))
//						std::wcout << "Duplicated filtered_pop transition\n";
#endif
			base_type::second.outgoing_filtered_pop_transitions.push_back(outgoing_filtered_pop_transition(target));
			target->second.incoming_filtered_pop_transitions.push_back(incoming_filtered_pop_transition(this, --base_type::second.outgoing_filtered_pop_transitions.end()));
			base_type::second.outgoing_filtered_pop_transitions.back().r_trans_it = --(target->second.incoming_filtered_pop_transitions.end());
		}

		//Add filtered-pop transition with zpps map iterator
		void add_filtered_pop_transition(ref target, paused_execution_state_iterator pes_begin)
		{
#ifdef TRACE
			std::wcout << "add filtered pop transition (" << base_type::second.wlabel() << ", " << target->second.wlabel() << UP_ARROW << ", " << target->second.wlabel() << ") with pes_begin = ";
			if (pes_begin->first.q)
				static_cast<paused_execution_state&>(*pes_begin).serialize(std::wcout) << std::endl;
			else std::wcout << "initial" << std::endl;
//				if (includes(outgoing_filtered_pop_transitions.begin(), outgoing_filtered_pop_transitions.end(), outgoing_filtered_pop_transition(target)))
//						std::wcout << "Duplicated filtered_pop transition\n";
#endif
			base_type::second.outgoing_filtered_pop_transitions.push_back(outgoing_filtered_pop_transition(target));
			target->second.incoming_filtered_pop_transitions.push_back(incoming_filtered_pop_transition(this, --base_type::second.outgoing_filtered_pop_transitions.end(), pes_begin));
			base_type::second.outgoing_filtered_pop_transitions.back().r_trans_it = --(target->second.incoming_filtered_pop_transitions.end());
		}

		void remove_foreign_consuming_transitions()
		{
			outgoing_consuming_transition_iterator oct_it;
			for (oct_it = base_type::second.outgoing_consuming_transitions.begin(); oct_it != base_type::second.outgoing_consuming_transitions.end(); ++oct_it)
			{
#ifdef TRACE
				std::wcout << "remove consuming transition (" << base_type::second.wlabel() << ", ";
				tag_input_serializer()(std::wcout, oct_it->input) << ", " << oct_it->target->second.wlabel() << ')' << std::endl;
#endif
				oct_it->target->second.incoming_consuming_transitions.erase(oct_it->r_trans_it);
			}
			for (oct_it = base_type::second.incoming_consuming_transitions.begin(); oct_it != base_type::second.incoming_consuming_transitions.end(); ++oct_it)
			{
#ifdef TRACE
				std::wcout << "remove consuming transition (" << oct_it->target->second.wlabel() << ", ";
				tag_input_serializer()(std::wcout, oct_it->input) << ", " << base_type::second.wlabel() << ')' << std::endl;
#endif
				oct_it->target->second.outgoing_consuming_transitions.erase(oct_it->r_trans_it);
			}
		}

		void remove_foreign_call_transitions()
		{
			outgoing_call_transition_iterator oct_it;
			for (oct_it = base_type::second.outgoing_call_transitions.begin(); oct_it != base_type::second.outgoing_call_transitions.end(); ++oct_it)
			{
#ifdef TRACE
				std::wcout << "remove call transition (" << base_type::second.wlabel() << ", " << oct_it->called->second.wlabel() << ", " << oct_it->target->second.wlabel() << ')' << std::endl;
#endif
				oct_it->target->second.incoming_call_transitions.erase(oct_it->r_trans_it);
			}
			for (oct_it = base_type::second.incoming_call_transitions.begin(); oct_it != base_type::second.incoming_call_transitions.end(); ++oct_it)
			{
#ifdef TRACE
				std::wcout << "remove call transition (" << oct_it->target->second.wlabel() << ", " << oct_it->called->second.wlabel() << ", " << base_type::second.wlabel() << ')' << std::endl;
#endif
				oct_it->target->second.outgoing_call_transitions.erase(oct_it->r_trans_it);
			}
		}

		void remove_foreign_epsilon_transitions()
		{
			outgoing_epsilon_transition_iterator oet_it;
			for (oet_it = base_type::second.outgoing_epsilon_transitions.begin(); oet_it != base_type::second.outgoing_epsilon_transitions.end(); ++oet_it)
			{
#ifdef TRACE
				std::wcout << "remove epsilon transition (" << base_type::second.wlabel() << ", <E>, " << oet_it->target->second.wlabel() << ')' << std::endl;
#endif
				oet_it->target->second.incoming_epsilon_transitions.erase(oet_it->r_trans_it);
			}
			for (oet_it = base_type::second.incoming_epsilon_transitions.begin(); oet_it != base_type::second.incoming_epsilon_transitions.end(); ++oet_it)
			{
#ifdef TRACE
				std::wcout << "remove epsilon transition (" << oet_it->target->second.wlabel() << ", <E>, " << base_type::second.wlabel() << ')' << std::endl;
#endif
				oet_it->target->second.outgoing_epsilon_transitions.erase(oet_it->r_trans_it);
			}
		}

		void remove_foreign_filtered_pop_transitions()
		{
			for (outgoing_filtered_pop_transition_iterator ofpt_it(base_type::second.outgoing_filtered_pop_transitions.begin()); ofpt_it != base_type::second.outgoing_filtered_pop_transitions.end(); ++ofpt_it)
			{
#ifdef TRACE
				std::wcout << "remove filtered pop transition (" << base_type::second.wlabel() << ", " << ofpt_it->target->second.wlabel() << UP_ARROW << ", " << ofpt_it->target->second.wlabel() << ')' << std::endl;
#endif
				ofpt_it->target->second.incoming_filtered_pop_transitions.erase(ofpt_it->r_trans_it);
			}
			for (incoming_filtered_pop_transition_iterator ifpt_it(base_type::second.incoming_filtered_pop_transitions.begin()); ifpt_it != base_type::second.incoming_filtered_pop_transitions.end(); ++ifpt_it)
			{
#ifdef TRACE
				std::wcout << "remove filtered pop transition (" << ifpt_it->target->second.wlabel() << ", " << base_type::second.wlabel() << UP_ARROW << ", " << base_type::second.wlabel() << ')' << std::endl;
#endif
				ifpt_it->target->second.outgoing_filtered_pop_transitions.erase(ifpt_it->r_trans_it);
			}
		}

		void remove_foreign_transitions()
		{
			remove_foreign_consuming_transitions();
			remove_foreign_epsilon_transitions();
			remove_foreign_call_transitions();
			remove_foreign_filtered_pop_transitions();
		}

		bool is_final() const
		{ return base_type::first.is_final(); }

		inline std::size_t transition_count() const
		{ return base_type::second.transition_count(); }

		inline bool has_no_outgoing_transitions() const
		{ return base_type::second.has_no_outgoing_transitions(); }

		inline bool has_no_incoming_transitions() const
		{ return base_type::second.has_no_incoming_transitions(); }

#ifdef TRACE
		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_earley_exe_state(std::basic_ostream<CharT, Traits> &out) const
		{ return base_type::first.serialize(out); }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_fprtn_state(std::basic_ostream<CharT, Traits> &out) const
		{ return base_type::second.serialize(out); }
#endif
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_paused_execution_state_key: public earley_parser_no_output<RTNOTagInput, TagInput, SourceRef, execution_state_set_impl_choice>::paused_execution_state
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef typename earley_parser_no_output<RTNOTagInput, TagInput, SourceRef, execution_state_set_impl_choice>::paused_execution_state base_type;
		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>* state_ref;
#ifdef TRACE
		typedef typename ns_rtno<RTNOTagInput, TagInput>::state::const_ref source_rtno_state_const_ref;
#else
		typedef typename rtno<RTNOTagInput, TagInput>::state::const_ref source_rtno_state_const_ref;
#endif

		state_ref r;

		output_fprtn_paused_execution_state_key()
		{}

		//Constructs an active execution state by joining up the 5-tuple (in fact 4-tuple since field q_c is constant) elements
		output_fprtn_paused_execution_state_key(source_rtno_state_const_ref q_, state_ref r_, source_rtno_state_const_ref q_c_, source_rtno_state_const_ref q_h_, std::size_t i_):
			base_type(q_, q_c_, q_h_, i_), r(r_)
		{}

		bool operator< (const output_fprtn_paused_execution_state_key& x2) const
		{
			//Paused execution states depending on a called state q_c are resumed once a sub-execution state starting from that q_c is completed
			//We set input state q_c as the first sorting criterion in order to sequentially access every paused execution state to be completed
			//due to a call to q_c, and to sequentially access the corresponding output source states of the call for the addition of the
			//corresponding call transitions from each r;
			//We set q and r as the last sorting criteria in order to sequentially access every paused execution state completed by a given
			//filtered pop transition, and to extract the corresponding source states r of the completed calls
			if (this->q_c < x2.q_c)
				return true;
			if (x2.q_c < this->q_c)
				return false;
			if (this->q_h < x2.q_h)
				return true;
			if (x2.q_h < this->q_h)
				return false;
			if (this->i < x2.i)
				return true;
			if (x2.i < this->i)
				return false;
			if (this->q < x2.q)
				return true;
			if (x2.q < this->q)
				return false;
			return this->r < x2.r;
		}

		std::ptrdiff_t compare_3w(const output_fprtn_paused_execution_state_key& x2) const
		{
			//Paused execution states depending on a called state q_c are resumed once a sub-execution state starting from that q_c is completed
			//We set input state q_c as the first sorting criterion in order to sequentially access every paused execution state to be completed
			//due to a call to q_c, and to sequentially access the corresponding output source states of the call for the addition of the
			//corresponding call transitions from each r;
			//We set q and r as the last sorting criteria in order to sequentially access every paused execution state completed by a given
			//filtered pop transition, and to extract the corresponding source states r of the completed calls
			std::ptrdiff_t result(reinterpret_cast<std::ptrdiff_t>(this->q_c) - reinterpret_cast<std::ptrdiff_t>(x2.q_c));
			if (result)
				return result;
			if ((result = reinterpret_cast<std::ptrdiff_t>(this->q_h) - reinterpret_cast<std::ptrdiff_t>(x2.q_h)))
				return result;
			if ((result = static_cast<std::ptrdiff_t>(this->i) - static_cast<std::ptrdiff_t>(x2.i)))
				return result;
			if ((result = reinterpret_cast<std::ptrdiff_t>(this->q) - reinterpret_cast<std::ptrdiff_t>(x2.q)))
				return result;
			return reinterpret_cast<std::ptrdiff_t>(this->r) - reinterpret_cast<std::ptrdiff_t>(x2.r);
		}
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_paused_execution_state_mapped
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>* state_ref;

		state_ref r_c;
		std::size_t last_resumed_index;
		bool is_filtered_popping_transition_creator;

		output_fprtn_paused_execution_state_mapped()
		{}

		//Constructs an active execution state by joining up the 5-tuple (in fact 4-tuple since field q_c is constant) elements
		output_fprtn_paused_execution_state_mapped(state_ref r_c_, std::size_t last_resumed_index_): r_c(r_c_), last_resumed_index(last_resumed_index_)
		{}
	};

	//7-tuple (q, r, q_c, r_c, q_h, i, last_resumed_index) in (Q X Q^prime X Q X Q^prime X Q X N X N)
	//Earley_execution_state having a non-constant q_c field
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_paused_execution_state: public std::pair<const output_fprtn_paused_execution_state_key<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, StateMappedExtraData>, output_fprtn_paused_execution_state_mapped<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, StateMappedExtraData> >
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data>* state_ref;
#ifdef TRACE
		typedef typename ns_rtno<RTNOTagInput, TagInput>::state::const_ref source_rtno_state_const_ref;
#else
		typedef typename rtno<RTNOTagInput, TagInput>::state::const_ref source_rtno_state_const_ref;
#endif
		typedef output_fprtn_paused_execution_state_key<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> key;
		typedef output_fprtn_paused_execution_state_mapped<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> mapped;
		typedef typename map_impl_selector<execution_state_set_impl_choice, key, mapped>::type map;
		typedef std::pair<const key, mapped> base_type;
		typedef output_fprtn_paused_execution_state* ref;

		//Constructs an active execution state by joining up the 5-tuple (in fact 4-tuple since field q_c is constant) elements
		output_fprtn_paused_execution_state(source_rtno_state_const_ref q_, state_ref r_, source_rtno_state_const_ref q_c_, source_rtno_state_const_ref q_h_, std::size_t i_):
			base_type()
		{
			const_cast<key&>(base_type::first).q = q_;
			const_cast<key&>(base_type::first).r = r_;
			const_cast<key&>(base_type::first).q_c = q_c_;
			const_cast<key&>(base_type::first).q_h = q_h_;
			const_cast<key&>(base_type::first).i = i_;
			base_type::second.last_resumed_index = std::numeric_limits<std::size_t>::max();
		}


#ifdef TRACE
		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
		{
			out << '(';
			base_type::first.q->serialize(out, static_cast<CharT>('q'))	<< ", ";
			base_type::first.r->serialize_fprtn_state(out) << ", ";
			base_type::first.q_c->serialize(out, static_cast<CharT>('q')) << ", ";
			base_type::second.r_c->serialize_fprtn_state(out) << ", ";
			base_type::first.q_h->serialize(out, static_cast<CharT>('q')) << ", ";
			return out << static_cast<int>(base_type::first.i) << ", " << base_type::second.is_filtered_popping_transition_creator << ')';
		}
#endif
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct output_fprtn_chart_item
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> state;
		typedef typename state::map state_map;
		typedef typename state_map::iterator state_iterator;
		typedef typename state_map::const_iterator state_const_iterator;
		typedef output_fprtn_paused_execution_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> paused_execution_state;
		typedef typename paused_execution_state::map paused_execution_state_map;
#ifdef TRACE
		typedef typename ns_rtno<RTNOTagInput, TagInput>::state::const_ref source_rtno_state_const_ref;
#else
		typedef typename rtno<RTNOTagInput, TagInput>::state::const_ref source_rtno_state_const_ref;
#endif

		state_map other_states;
		paused_execution_state_map pess;
#ifdef TRACE
		char state_label_letter;
		std::size_t *state_label_counter;

		output_fprtn_chart_item(): other_states(), pess(), state_label_letter(0), state_label_counter(NULL)
		{}

		output_fprtn_chart_item(char state_label_letter_, std::size_t *state_label_counter_): other_states(), pess(), state_label_letter(state_label_letter_), state_label_counter(state_label_counter_)
		{}
#else
		output_fprtn_chart_item(): other_states(), pess()
		{}
#endif

		output_fprtn_chart_item& operator= (const output_fprtn_chart_item &ci)
		{
			other_states = ci.other_states;
			pess = ci.pess;
#ifdef TRACE
			state_label_letter = ci.state_label_letter;
			state_label_counter = ci.state_label_counter;
#endif
			return *this;
		}

		//Insertion with non-default mapped value
		inline std::pair<state_iterator, bool> create_other_state(source_rtno_state_const_ref q, source_rtno_state_const_ref q_h, std::size_t j, SourceRef src_ref)
		{
#ifdef TRACE
			std::pair<state_iterator, bool> result(other_states.insert(state(q, q_h, j,	state_label_letter,	*state_label_counter, src_ref)));
			if (result.second)
				++(*state_label_counter);
			return result;
#else
			return other_states.insert(state(q, q_h, j, src_ref));
#endif
		}

		//Insertion with default mapped value; if insertion succeeds, mapped value must be initialized afterwards
/*			inline std::pair<state_iterator, bool> create_other_state(source_rtno_state_const_ref q, source_rtno_state_const_ref q_h, std::size_t j)
		{
#ifdef TRACE
			std::pair<state_iterator, bool> result(insert_with_default_mapped_value(other_states, state_key(q, q_h, j)));
			if (result.second)
			{
				result.first->second.letter = state_label_letter;
				result.first->second.number = ++(*state_label_counter);
			}
			return result;
#else
			return insert_with_default_mapped_value(other_states, state_key(q, q_h, j));
#endif
*/
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc = NO_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, typename StateMappedExtraData = empty_class>
	class output_fprtn
	{
	public:
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef output_fprtn<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc> this_type;
		typedef SourceRef source_ref;
		typedef typename source_ref::value_type input;
		typedef TagInput tag_input;

#ifdef TRACE
		typedef typename tag_serializer<input>::type input_serializer;
		typedef typename tag_serializer<tag_input>::type tag_input_serializer;
		typedef ns_rtno<RTNOTagInput, TagInput> source_rtno;
#else
		typedef rtno<RTNOTagInput, TagInput> source_rtno;
#endif
		typedef typename source_rtno::state source_rtno_state;
		typedef typename source_rtno_state::const_ref source_rtno_state_const_ref;

		typedef output_fprtn_outgoing_consuming_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> outgoing_consuming_transition;
		typedef typename outgoing_consuming_transition::set outgoing_consuming_transition_set;
		typedef typename outgoing_consuming_transition::iterator outgoing_consuming_transition_iterator;
		typedef output_fprtn_outgoing_epsilon_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> outgoing_epsilon_transition;
		typedef typename outgoing_epsilon_transition::set outgoing_epsilon_transition_set;
		typedef typename outgoing_epsilon_transition::iterator outgoing_epsilon_transition_iterator;
		typedef output_fprtn_outgoing_call_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> outgoing_call_transition;
		typedef typename outgoing_call_transition::set outgoing_call_transition_set;
		typedef typename outgoing_call_transition::iterator outgoing_call_transition_iterator;
		typedef output_fprtn_outgoing_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> outgoing_filtered_pop_transition;
		typedef typename outgoing_filtered_pop_transition::set outgoing_filtered_pop_transition_set;
		typedef typename outgoing_filtered_pop_transition::iterator outgoing_filtered_pop_transition_iterator;
		typedef output_fprtn_incoming_filtered_pop_transition<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> incoming_filtered_pop_transition;
		typedef typename incoming_filtered_pop_transition::set incoming_filtered_pop_transition_set;
		typedef typename incoming_filtered_pop_transition::iterator incoming_filtered_pop_transition_iterator;

		typedef output_fprtn_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> state;
		typedef typename state::key state_key;
		typedef typename state::mapped state_mapped;
		typedef typename state::ref state_ref;
		typedef typename state::const_ref state_const_ref;
		typedef std::queue<state_ref> state_ref_queue;
		typedef std::queue<state_const_ref> state_const_ref_queue;
		typedef typename state::map state_map;
		typedef typename state_map::iterator state_iterator;
		typedef typename state_map::const_iterator state_const_iterator;

		typedef output_fprtn_paused_execution_state<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> paused_execution_state;
		typedef typename paused_execution_state::key paused_execution_state_key;
		typedef typename paused_execution_state::mapped paused_execution_state_mapped;
		typedef typename paused_execution_state::map paused_execution_state_map;
		typedef typename paused_execution_state_map::iterator paused_execution_state_iterator;
		typedef typename paused_execution_state_map::const_iterator paused_execution_state_const_iterator;

		typedef output_fprtn_chart_item<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> chart_item;

		typedef array<chart_item> chart;
		typedef typename chart::iterator chart_iterator;
		typedef typename chart::const_iterator chart_const_iterator;

#ifdef TRACE
	public:
		const char state_label_letter;
	protected:
		std::size_t state_label_counter;
#endif

	public:
		source_rtno_state dummy_rtno_initial_state, dummy_rtno_global_acceptor_state;
		state initial_state, global_acceptor_state;
		chart the_chart;

		output_fprtn(
#ifdef TRACE
				char state_label_letter_,
				char source_rtno_state_label_letter,
#endif
				std::size_t input_length,
				SourceRef input_begin,
				SourceRef input_end):
#ifdef TRACE
				state_label_letter(state_label_letter_),
				state_label_counter(2),
				dummy_rtno_initial_state(-2, false),
				dummy_rtno_global_acceptor_state(-1, true),
				initial_state(&dummy_rtno_initial_state, NULL, 0, state_label_letter, 0, input_begin),
				global_acceptor_state(&dummy_rtno_global_acceptor_state, NULL, 0, state_label_letter, 1, input_end),
				the_chart(chart_item('r', &state_label_counter), input_length+1)
#else
				dummy_rtno_initial_state(false),
				dummy_rtno_global_acceptor_state(true),
				initial_state(&dummy_rtno_initial_state, NULL, 0, input_begin),
				global_acceptor_state(&dummy_rtno_global_acceptor_state, NULL, 0, input_end),
				the_chart(input_length+1)
#endif
		{}

		inline std::pair<state_iterator, bool> create_other_state(source_rtno_state_const_ref q, source_rtno_state_const_ref q_h, std::size_t j, std::size_t k, SourceRef src_ref)
		{ return the_chart[k].create_other_state(q, q_h, j, src_ref); }

//		inline std::pair<state_iterator, bool> create_other_state(source_rtno_state_const_ref q, source_rtno_state_const_ref q_h, std::size_t j, std::size_t k)
//		{ return the_chart[k].create_other_state(q, q_h, j); }

		inline std::size_t state_count() const
		{
			std::size_t count = 2; //Initial and global acceptor states
			for (chart_const_iterator c_it(the_chart.begin()); c_it != the_chart.end(); ++c_it)
				count += c_it->other_states.size();
			return count;
		}

		std::size_t transition_count() const
		{
			std::size_t count (initial_state.transition_count());
			state_iterator s_it;
			for (chart_const_iterator c_it(the_chart.begin()); c_it != the_chart.end(); ++c_it)
				for (state_const_iterator s_it(c_it->other_states.begin()); s_it != c_it->other_states.end(); ++s_it)
					count += s_it->second.transition_count();
			return count;
		}

		inline void clear()
		{
			for (chart_iterator c_it(the_chart.begin()); c_it != the_chart.end(); ++c_it)
			{
				c_it->other_states.clear();
				c_it->pess.clear();
				initial_state.second.outgoing_call_transitions.clear();
				global_acceptor_state.second.incoming_call_transitions.clear();
			}
		}

/*		template<typename SourceRef, typename TagInput, typename Iterator>
		typename output_fprtn<SourceRef, TagInput>::state::ref add_non_empty_sequence(output_fprtn<SourceRef, TagInput>& f, typename output_fprtn<SourceRef, TagInput>::state::ref src_state, Iterator begin, Iterator end, bool final, SourceRef src_ref)
		{
			Iterator i;
			Iterator last = end - 1;
			typename output_fprtn<SourceRef, TagInput>::state::ref dest_state;
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
		typename output_fprtn<SourceRef, TagInput>::state::ref add_sequence(output_fprtn<SourceRef, TagInput>& f, typename output_fprtn<SourceRef, TagInput>::state::ref src_state, Iterator begin, Iterator end, bool final, SourceRef src_ref)
		{
			if (begin == end)
			{
				typename output_fprtn<SourceRef, TagInput>::state::ref dest_state = f.create_non_initial_state(final, src_ref);
				src_state->add_transition(dest_state);
				return dest_state;
			}
			return add_non_empty_sequence(f, src_state, begin, end, final, src_ref);
		}
*/
		//Add sequence path from state src_state to dest_src
/*		template<typename SourceRef, typename TagInput, typename Iterator>
		typename output_fprtn<SourceRef, TagInput>::state::ref add_sequence(output_fprtn<SourceRef, TagInput>& f, typename output_fprtn<SourceRef, TagInput>::state::ref src_state, typename output_fprtn<SourceRef, TagInput>::state::ref dest_state, Iterator begin, Iterator end)
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
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	inline bool operator== (const typename output_fprtn<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice>::state& q1, const typename output_fprtn<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice>::state& q2)
	{ return &q1 == &q2; }

/*	bool operator< (const typename output_fprtn<SourceRef, TagInput, RTNOTagInput>::state& q1, const typename output_fprtn<SourceRef, TagInput, RTNOTagInput>::state& q2)
	{
		return &q1 < &q2;
	}*/
}

#endif /*GRAPE_OUTPUT_FPRTN_H*/
