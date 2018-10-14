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

#ifndef GRAPE_FST_H
#define GRAPE_FST_H

#ifdef TRACE
#include <boost/lexical_cast.hpp>
#endif

#include <string>
#include <map>
#include <set>

#include <grape/list.h>

namespace grape
{
	template<typename Tag>
	class fst
	{
		public:
			typedef fst<Tag> this_type;

		class state
		{
		public:
			typedef state* ref;
			typedef const state* const_ref;
			typedef ptr_list<state> ref_list;
			typedef	std::multimap<Tag, ref > deleting_transition_list;
			typedef	std::set<ref> epsilon_transition_list;

		protected:
			size_t label_;
			bool initial_flag, final_flag;

		public:
			deleting_transition_list deleting_transitions;
			epsilon_transition_list epsilon_transitions;

			state(size_t label__, bool initial_flag_, bool final_flag_): label_(label__), initial_flag(initial_flag_), final_flag(final_flag_),
				deleting_transitions(),
				epsilon_transitions()
			{}

			//Get this state label
#ifdef TRACE
			std::string label() const
			{
				const std::string q("q");
				return q + boost::lexical_cast<std::string>((unsigned int)label_);
			}

			std::wstring wlabel() const
			{
				const std::wstring q(L"q");
				return q + boost::lexical_cast<std::wstring>((unsigned int)label_);
			}
#endif

			//Add outgoing consuming transition to this state
			void add_deleting_transition(const Tag& tag, ref target)
			{ deleting_transitions.insert(std::make_pair(tag, target)); }

			//Add outgoing epsilon transition to this state
			void add_epsilon_transition(ref target)
			{ epsilon_transitions.insert(target); }

			//Is this an initial state?
			bool is_initial() const
			{ return initial_flag; }

			//Is this a final state?
			bool is_final() const
			{ return final_flag; }
		};

	protected:
		size_t state_label_counter;

	public:
		typename state::ref_list ini_states, other_states;

		fst()
		{ state_label_counter = -1; }

		inline typename state::ref create_state(bool initial_flag, bool final_flag)
		{ return create_state(initial_flag, final_flag, ++state_label_counter); }

		typename state::ref create_state(bool initial_flag, bool final_flag, std::size_t state_number)
		{
			typename state::ref q(new state(state_number, initial_flag, final_flag));
			if (initial_flag)
				ini_states.push_back(q);
			else other_states.push_back(q);
			return q;
		}
	};

	template<typename Tag>
	bool operator== (const typename fst<Tag>::state& q1, const typename fst<Tag>::state& q2)
	{
		return &q1 == &q2;
	}

	template<typename Tag>
	bool operator< (const typename fst<Tag>::state& q1, const typename fst<Tag>::state& q2)
	{
		return &q1 < &q2;
	}
}

#endif
