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

#ifndef GRAPENLP_RTNO_H
#define GRAPENLP_RTNO_H

#include <ostream>
#include <boost/lexical_cast.hpp>

#include <string>

#include <grapenlp/lrb_tree_set.h>
#include <grapenlp/array.h>
#include <grapenlp/list.h>
#include <grapenlp/rtno_type.h>

namespace grapenlp
{
	template<typename TagInput, typename TagOutput>
	class rtno
	{
		public:
			typedef rtno<TagInput, TagOutput> this_type;
			typedef TagInput tag_input;
			typedef TagOutput tag_output;

		class state;

		struct outgoing_epsilon_transition
		{
			typedef	lrb_tree_set<outgoing_epsilon_transition> set;

			state* target;

			outgoing_epsilon_transition(state* target_): target(target_)
			{}

			bool operator< (const outgoing_epsilon_transition &oet) const
			{ return target < oet.target; }
		};

		typedef	typename outgoing_epsilon_transition::set outgoing_epsilon_transition_set;
		typedef	typename outgoing_epsilon_transition_set::iterator outgoing_epsilon_transition_set_iterator;
		typedef	typename outgoing_epsilon_transition_set::const_iterator outgoing_epsilon_transition_set_const_iterator;

		struct outgoing_inserting_transition
		{
			typedef	lrb_tree_set<outgoing_inserting_transition> set;

			TagOutput output;
			state* target;

			outgoing_inserting_transition(const TagOutput &output_, state* target_): output(output_), target(target_)
			{}

			bool operator< (const outgoing_inserting_transition &ogt) const
			{
				if (output < ogt.output)
					return true;
				if (ogt.output < output)
					return false;
				return target < ogt.target;
			}
		};

		typedef	typename outgoing_inserting_transition::set outgoing_inserting_transition_set;
		typedef	typename outgoing_inserting_transition_set::iterator outgoing_inserting_transition_set_iterator;
		typedef	typename outgoing_inserting_transition_set::const_iterator outgoing_inserting_transition_set_const_iterator;

		struct outgoing_deleting_transition
		{
			typedef	lrb_tree_set<outgoing_deleting_transition> set;

			TagInput input;
			state* target;

			outgoing_deleting_transition(const TagInput &input_, state* target_): input(input_), target(target_)
			{}

			bool operator< (const outgoing_deleting_transition &oct) const
			{
				if (input < oct.input)
					return true;
				if (oct.input < input)
					return false;
				return target < oct.target;
			}
		};

		typedef typename outgoing_deleting_transition::set outgoing_deleting_transition_set;
		typedef	typename outgoing_deleting_transition_set::iterator outgoing_deleting_transition_set_iterator;
		typedef	typename outgoing_deleting_transition_set::const_iterator outgoing_deleting_transition_set_const_iterator;

		struct outgoing_translating_transition
		{
			typedef	lrb_tree_set<outgoing_translating_transition> set;

			TagInput input;
			TagOutput output;
			state* target;

			outgoing_translating_transition(const TagInput &input_, const TagOutput &output_, state* target_): input(input_), output(output_), target(target_)
			{}

			bool operator< (const outgoing_translating_transition &ott) const
			{
				if (input < ott.input)
					return true;
				if (ott.input < input)
					return false;
				if (output < ott.output)
					return true;
				if (ott.output < output)
					return false;
				return target < ott.target;
			}
		};

		typedef typename outgoing_translating_transition::set outgoing_translating_transition_set;
		typedef	typename outgoing_translating_transition_set::iterator outgoing_translating_transition_set_iterator;
		typedef	typename outgoing_translating_transition_set::const_iterator outgoing_translating_transition_set_const_iterator;

		struct outgoing_call_transition
		{
			typedef	lrb_tree_set<outgoing_call_transition> set;

			state* called;
			state* target;

			outgoing_call_transition(state* called_, state* target_): called(called_), target(target_)
			{}

			bool operator< (const outgoing_call_transition &oct) const
			{
				if (called < oct.called)
					return true;
				if (oct.called < called)
					return false;
				return target < oct.target;
			}
		};

		typedef typename outgoing_call_transition::set outgoing_call_transition_set;
		typedef	typename outgoing_call_transition_set::iterator outgoing_call_transition_set_iterator;
		typedef	typename outgoing_call_transition_set::const_iterator outgoing_call_transition_set_const_iterator;

		class state
		{
		public:
			typedef state* ref;
			typedef const state* const_ref;
			typedef ptr_list<state> ref_list;
			typedef typename ref_list::const_iterator ref_list_const_iterator;

		protected:
			bool final_flag;
		public:
			outgoing_deleting_transition_set outgoing_deleting_transitions;
			outgoing_translating_transition_set outgoing_translating_transitions;

			outgoing_epsilon_transition_set outgoing_epsilon_transitions;
			outgoing_inserting_transition_set outgoing_inserting_transitions;

			outgoing_epsilon_transition_set outgoing_blank_epsilon_transitions;
			outgoing_inserting_transition_set outgoing_blank_inserting_transitions;

			outgoing_epsilon_transition_set outgoing_no_blank_epsilon_transitions;
			outgoing_inserting_transition_set outgoing_no_blank_inserting_transitions;

			outgoing_call_transition_set outgoing_call_transitions;

		public:
			state(bool final_flag_):
				final_flag(final_flag_),
				outgoing_deleting_transitions(),
				outgoing_translating_transitions(),
				outgoing_epsilon_transitions(),
				outgoing_inserting_transitions(),
				outgoing_blank_epsilon_transitions(),
				outgoing_blank_inserting_transitions(),
				outgoing_no_blank_epsilon_transitions(),
				outgoing_no_blank_inserting_transitions(),
				outgoing_call_transitions()
			{}

			//Add outgoing consuming transition to this state
			void add_deleting_transition(const TagInput &input, ref target)
			{ outgoing_deleting_transitions.insert(outgoing_deleting_transition(input, target)); }

			//Add outgoing translating transition to this state
			void add_translating_transition(const TagInput &input, const TagOutput &output, ref target)
			{ outgoing_translating_transitions.insert(outgoing_translating_transition(input, output, target)); }

			//Add outgoing epsilon transition to this state
			void add_epsilon_transition(ref target)
			{ outgoing_epsilon_transitions.insert(target); }

			//Add outgoing generating transition to this state
			void add_inserting_transition(const TagOutput& output, ref target)
			{ outgoing_inserting_transitions.insert(outgoing_inserting_transition(output, target)); }

			//Add outgoing blank epsilon transition to this state
			void add_blank_epsilon_transition(ref target)
			{ outgoing_blank_epsilon_transitions.insert(target); }

			//Add outgoing blank generating transition to this state
			void add_blank_inserting_transition(const TagOutput& output, ref target)
			{ outgoing_blank_inserting_transitions.insert(outgoing_inserting_transition(output, target)); }

			//Add outgoing no-blank epsilon transition to this state
			void add_no_blank_epsilon_transition(ref target)
			{ outgoing_no_blank_epsilon_transitions.insert(target); }

			//Add outgoing no-blank generating transition to this state
			void add_no_blank_inserting_transition(const TagOutput& output, ref target)
			{ outgoing_no_blank_inserting_transitions.insert(outgoing_inserting_transition(output, target)); }

			//Add outgoing call transition to this state
			void add_call_transition(ref call, ref target)
			{ outgoing_call_transitions.insert(outgoing_call_transition(call, target)); }

			//Is this a final state?
			bool is_final() const
			{ return final_flag; }

			std::size_t transition_count() const
			{
				return outgoing_deleting_transitions.size() +
					outgoing_translating_transitions.size() +
					outgoing_epsilon_transitions.size() +
					outgoing_inserting_transitions.size() +
					outgoing_blank_epsilon_transitions.size() +
					outgoing_blank_inserting_transitions.size() +
					outgoing_no_blank_epsilon_transitions.size() +
					outgoing_no_blank_inserting_transitions.size() +
					outgoing_call_transitions.size();
            }

			bool has_no_transitions() const
			{
				return outgoing_deleting_transitions.empty() &&
					outgoing_translating_transitions.empty() &&
					outgoing_epsilon_transitions.empty() &&
					outgoing_inserting_transitions.empty() &&
					outgoing_blank_epsilon_transitions.empty() &&
					outgoing_blank_inserting_transitions.empty() &&
					outgoing_no_blank_epsilon_transitions.empty() &&
					outgoing_no_blank_inserting_transitions.empty() &&
					outgoing_call_transitions.empty();
			}
		};

		typedef typename state::ref state_ref;
		typedef typename state::const_ref state_const_ref;
		typedef typename state::ref_list state_ref_list;
		typedef typename state_ref_list::iterator state_ref_list_iterator;
		typedef typename state_ref_list::const_iterator state_ref_list_const_iterator;

	public:
		//First state created is the initial one
		state_ref_list states;

		rtno(): states()
		{}

		state_ref create_state(bool final_flag)
		{
			states.push_back(new state(final_flag));
			return states.back();
		}

		state_ref initial_state()
		{ return *states.begin(); }

		state_const_ref initial_state() const
		{ return static_cast<state_const_ref>(*states.begin()); }

		std::size_t state_count() const
		{ return states.size(); }

		std::size_t transition_count() const
		{
			std::size_t count = 0;
			state_ref_list_const_iterator i;
			for (i = states.begin(); i != states.end(); ++i)
				count += (*i)->transition_count();
			return count;
		}
	};

	template<typename TagInput, typename TagOutput>
	bool operator== (const typename rtno<TagInput, TagOutput>::state& q1, const typename rtno<TagInput, TagOutput>::state& q2)
	{
		return &q1 == &q2;
	}

	template<typename TagInput, typename TagOutput>
	bool operator< (const typename rtno<TagInput, TagOutput>::state& q1, const typename rtno<TagInput, TagOutput>::state& q2)
	{
		return &q1 < &q2;
	}

	//RTNO with numbered states
	template<typename TagInput, typename TagOutput>
	class ns_rtno: public rtno<TagInput, TagOutput>
	{
		public:
			typedef ns_rtno<TagInput, TagOutput> this_type;
			typedef rtno<TagInput, TagOutput> base_type;
//			typedef TagInput tag_input;
//			typedef TagOutput tag_output;

		class state;

		typedef typename state::ref state_ref;
		typedef typename state::const_ref state_const_ref;
//		typedef typename state::ref_list state_ref_list;
//		typedef typename state_ref_list::iterator state_ref_list_iterator;
//		typedef typename state_ref_list::const_iterator state_ref_list_const_iterator;

/*		struct outgoing_epsilon_transition
		{
			typedef	lrb_tree_set<outgoing_epsilon_transition> set;

			state_ref target;

			outgoing_epsilon_transition(state_ref target_): target(target_)
			{}

			bool operator< (const outgoing_epsilon_transition &oet) const
			{ return target < oet.target; }
		};

		typedef	typename outgoing_epsilon_transition::set outgoing_epsilon_transition_set;
		typedef	typename outgoing_epsilon_transition_set::iterator outgoing_epsilon_transition_set_iterator;
		typedef	typename outgoing_epsilon_transition_set::const_iterator outgoing_epsilon_transition_set_const_iterator;

		struct outgoing_inserting_transition
		{
			typedef	lrb_tree_set<outgoing_inserting_transition> set;

			TagOutput output;
			state_ref target;

			outgoing_inserting_transition(const TagOutput &output_, state_ref target_): output(output_), target(target_)
			{}

			bool operator< (const outgoing_inserting_transition &ogt) const
			{
				if (output < ogt.output)
					return true;
				if (ogt.output < output)
					return false;
				return target < ogt.target;
			}
		};

		typedef	typename outgoing_inserting_transition::set outgoing_inserting_transition_set;
		typedef	typename outgoing_inserting_transition_set::iterator outgoing_inserting_transition_set_iterator;
		typedef	typename outgoing_inserting_transition_set::const_iterator outgoing_inserting_transition_set_const_iterator;

		struct outgoing_deleting_transition
		{
			typedef	lrb_tree_set<outgoing_deleting_transition> set;

			TagInput input;
			state_ref target;

			outgoing_deleting_transition(const TagInput &input_, state_ref target_): input(input_), target(target_)
			{}

			bool operator< (const outgoing_deleting_transition &oct) const
			{
				if (input < oct.input)
					return true;
				if (oct.input < input)
					return false;
				return target < oct.target;
			}
		};

		typedef typename outgoing_deleting_transition::set outgoing_deleting_transition_set;
		typedef	typename outgoing_deleting_transition_set::iterator outgoing_deleting_transition_set_iterator;
		typedef	typename outgoing_deleting_transition_set::const_iterator outgoing_deleting_transition_set_const_iterator;

		struct outgoing_translating_transition
		{
			typedef	lrb_tree_set<outgoing_translating_transition> set;

			TagInput input;
			TagOutput output;
			state_ref target;

			outgoing_translating_transition(const TagInput &input_, const TagOutput &output_, state_ref target_): input(input_), output(output_), target(target_)
			{}

			bool operator< (const outgoing_translating_transition &ott) const
			{
				if (input < ott.input)
					return true;
				if (ott.input < input)
					return false;
				if (output < ott.output)
					return true;
				if (ott.output < output)
					return false;
				return target < ott.target;
			}
		};

		typedef typename outgoing_translating_transition::set outgoing_translating_transition_set;
		typedef	typename outgoing_translating_transition_set::iterator outgoing_translating_transition_set_iterator;
		typedef	typename outgoing_translating_transition_set::const_iterator outgoing_translating_transition_set_const_iterator;

		struct outgoing_call_transition
		{
			typedef	lrb_tree_set<outgoing_call_transition> set;

			state_ref called;
			state_ref target;

			outgoing_call_transition(state_ref called_, state_ref target_): called(called_), target(target_)
			{}

			bool operator< (const outgoing_call_transition &oct) const
			{
				if (called < oct.called)
					return true;
				if (oct.called < called)
					return false;
				return target < oct.target;
			}
		};

		typedef typename outgoing_call_transition::set outgoing_call_transition_set;
		typedef	typename outgoing_call_transition_set::iterator outgoing_call_transition_set_iterator;
		typedef	typename outgoing_call_transition_set::const_iterator outgoing_call_transition_set_const_iterator;
*/
		class state: public ns_rtno::base_type::state
		{
		public:
			typedef typename ns_rtno::base_type::state base_type;
			typedef state* ref;
			typedef const state* const_ref;
			typedef ptr_list<state> ref_list;
			typedef typename ref_list::const_iterator ref_list_const_iterator;

			const std::size_t number;

		public:
			state(bool final_flag_, std::size_t number_): base_type(final_flag_), number(number_)
			{}

			//Get this state label
			template<typename CharT, typename Traits>
			std::basic_string<CharT, Traits> basic_label(CharT letter) const
			{
				CharT letter_string[2] = {letter, static_cast<CharT>('\0')};
				return std::basic_string<CharT, Traits>(letter_string) + boost::lexical_cast<std::basic_string<CharT, Traits> >((unsigned int)number);
			}

			std::string label(char letter) const
			{ return basic_label<char, std::char_traits<char> >(letter); }

			std::wstring wlabel(wchar_t letter) const
			{ return basic_label<wchar_t, std::char_traits<wchar_t> >(letter); }

			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits> &out, CharT letter) const
			{ return out << letter << boost::lexical_cast<std::basic_string<CharT, Traits> >((unsigned int)number); }

/*			//Add outgoing consuming transition to this state
			void add_deleting_transition(const TagInput &input, ref target)
			{ outgoing_deleting_transitions.insert(outgoing_deleting_transition(input, target)); }

			//Add outgoing translating transition to this state
			void add_translating_transition(const TagInput &input, const TagOutput &output, ref target)
			{ outgoing_translating_transitions.insert(outgoing_translating_transition(input, output, target)); }

			//Add outgoing epsilon transition to this state
			void add_epsilon_transition(ref target)
			{ outgoing_epsilon_transitions.insert(target); }

			//Add outgoing generating transition to this state
			void add_inserting_transition(const TagOutput& output, ref target)
			{ outgoing_inserting_transitions.insert(outgoing_inserting_transition(output, target)); }

			//Add outgoing blank epsilon transition to this state
			void add_blank_epsilon_transition(ref target)
			{ outgoing_blank_epsilon_transitions.insert(target); }

			//Add outgoing blank generating transition to this state
			void add_blank_inserting_transition(const TagOutput& output, ref target)
			{ outgoing_blank_inserting_transitions.insert(outgoing_inserting_transition(output, target)); }

			//Add outgoing no-blank epsilon transition to this state
			void add_no_blank_epsilon_transition(ref target)
			{ outgoing_no_blank_epsilon_transitions.insert(target); }

			//Add outgoing no-blank generating transition to this state
			void add_no_blank_inserting_transition(const TagOutput& output, ref target)
			{ outgoing_no_blank_inserting_transitions.insert(outgoing_inserting_transition(output, target)); }

			//Add outgoing call transition to this state
			void add_call_transition(ref call, ref target)
			{ outgoing_call_transitions.insert(outgoing_call_transition(call, target)); }

			//Is this a final state?
			bool is_final() const
			{ return final_flag; }

			std::size_t transition_count() const
			{
				return outgoing_deleting_transitions.size() +
					outgoing_translating_transitions.size() +
					outgoing_epsilon_transitions.size() +
					outgoing_inserting_transitions.size() +
					outgoing_blank_epsilon_transitions.size() +
					outgoing_blank_inserting_transitions.size() +
					outgoing_no_blank_epsilon_transitions.size() +
					outgoing_no_blank_inserting_transitions.size() +
					outgoing_call_transitions.size();
            }

			bool has_no_transitions() const
			{
				return outgoing_deleting_transitions.empty() &&
					outgoing_translating_transitions.empty() &&
					outgoing_epsilon_transitions.empty() &&
					outgoing_inserting_transitions.empty() &&
					outgoing_blank_epsilon_transitions.empty() &&
					outgoing_blank_inserting_transitions.empty() &&
					outgoing_no_blank_epsilon_transitions.empty() &&
					outgoing_no_blank_inserting_transitions.empty() &&
					outgoing_call_transitions.empty();
			}
*/		};

	protected:
		std::size_t state_label_counter;

	public:
		ns_rtno(): base_type(), state_label_counter(0)
		{}

		state_ref initial_state()
		{ return static_cast<state_ref>(base_type::initial_state()); }

		state_const_ref initial_state() const
		{ return static_cast<state_const_ref>(base_type::initial_state()); }

		state_ref create_state(bool final_flag)
		{
			base_type::states.push_back(new state(final_flag, state_label_counter));
			++state_label_counter;
			return static_cast<state_ref>(base_type::states.back());
		}
	};
/*
	template<typename TagInput, typename TagOutput>
	bool operator== (const typename ns_rtno<TagInput, TagOutput>::state& q1, const typename ns_rtno<TagInput, TagOutput>::state& q2)
	{
		return &q1 == &q2;
	}

	template<typename TagInput, typename TagOutput>
	bool operator< (const typename ns_rtno<TagInput, TagOutput>::state& q1, const typename ns_rtno<TagInput, TagOutput>::state& q2)
	{
		return &q1 < &q2;
	}
*/
} //namespace grapenlp

#endif /*GRAPENLP_RTNO_H*/
