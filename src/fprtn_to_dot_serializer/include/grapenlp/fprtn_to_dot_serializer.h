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

#ifndef GRAPENLP_FPRTN_TO_DOT_SERIALIZER_H
#define GRAPENLP_FPRTN_TO_DOT_SERIALIZER_H
#include <ostream>
#include <string>
#include <algorithm>
#include <grapenlp/tag_serializer_traits.h>
#include <grapenlp/fprtn.h>

namespace grapenlp
{
	template<typename SourceRef, typename TagInputSerializer>
	struct fprtn_to_dot_serializer
	{
		typedef TagInputSerializer tag_input_serializer;

		typedef typename serializer_traits<tag_input_serializer>::elem_type tag_input;
		typedef fprtn<SourceRef, tag_input> elem_type;

		typedef elem_type machine;
		typedef typename machine::state state;
		typedef typename machine::state_const_ref state_const_ref;
		typedef typename machine::state_ref_list_const_iterator state_ref_list_const_iterator;
		typedef	typename machine::outgoing_epsilon_transition_set::const_iterator outgoing_epsilon_transition_set_const_iterator;
		typedef	typename machine::outgoing_consuming_transition_set::const_iterator outgoing_consuming_transition_set_const_iterator;
		typedef	typename machine::outgoing_call_transition_set::const_iterator outgoing_call_transition_set_const_iterator;
		typedef	typename machine::outgoing_filtered_pop_transition_set::const_iterator outgoing_filtered_pop_transition_set_const_iterator;

	protected:
		tag_input_serializer tis;

	public:
		fprtn_to_dot_serializer(): tis()
		{}

		fprtn_to_dot_serializer(const TagInputSerializer &tis_): tis(tis_)
		{}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_state_label(std::basic_ostream<CharT, Traits>& out, state_const_ref s)
		{ return s->serialize(out << '"') << '"'; }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_state_kappa_label(std::basic_ostream<CharT, Traits>& out, state_const_ref s)
		{ return s->serialize(out << "\"k_") << '"'; }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_state(std::basic_ostream<CharT, Traits>& out, state_const_ref s, SourceRef src_begin)
		{
			//Set double circle if final state
			if (s->is_final())
			{
				serialize_state_label(out, s);
				out << "[peripheries = 2];" << std::endl;
			}

			//Print key box
			serialize_state_kappa_label(out, s) << " [shape = box, height = 0, width = 0, label = \"" << std::distance(src_begin, s->src_ref) << "\"];" << std::endl;
			serialize_state_label(out, s);
			out << " -> ";
			serialize_state_kappa_label(out, s) << " [dir = none, minlen = 0, len = 0, tailport = s, headport = n];" << std::endl;;

			//Print epsilon transitions
			for (outgoing_epsilon_transition_set_const_iterator oet_it(s->outgoing_epsilon_transitions.begin()); oet_it != s->outgoing_epsilon_transitions.end(); ++oet_it)
			{
				serialize_state_label(out, s);
				out << " -> ";
				serialize_state_label(out, oet_it->target);
				out << " [label = \"<E>\"];" << std::endl;
			}

			//Print deleting transitions
			for (outgoing_consuming_transition_set_const_iterator oconst_it(s->outgoing_consuming_transitions.begin()); oconst_it != s->outgoing_consuming_transitions.end(); ++oconst_it)
			{
				serialize_state_label(out, s);
				out << " -> ";
				serialize_state_label(out, oconst_it->target);
				out << " [label = \"";
				tis(out, oconst_it->input) << "\"];" << std::endl;
			}

			//Print call and push transitions
			for (outgoing_call_transition_set_const_iterator ocallt_it(s->outgoing_call_transitions.begin()); ocallt_it != s->outgoing_call_transitions.end(); ++ocallt_it)
			{
				//Call
				serialize_state_label(out, s);
				out << " -> ";
				serialize_state_label(out, ocallt_it->target);
				out << " [label = \"";
				ocallt_it->called->serialize(out) << "\", style = dashed];" << std::endl;

				//Push
				serialize_state_label(out, s);
				out << " -> ";
				serialize_state_label(out, ocallt_it->called);
				out << " [label = \"";
				ocallt_it->target->serialize(out) << "\", style = dotted];" << std::endl;
			}

			//Print pop transitions
			for (outgoing_filtered_pop_transition_set_const_iterator ofpopt_it(s->outgoing_filtered_pop_transitions.begin()); ofpopt_it != s->outgoing_filtered_pop_transitions.end(); ++ofpopt_it)
			{
				serialize_state_label(out, s);
				out << " -> ";
				serialize_state_label(out, ofpopt_it->target);
				out << " [style = bold];" << std::endl;
			}

			return out;
		}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& operator() (std::basic_ostream<CharT, Traits>& out, const char *fprtn_name, const machine &m, SourceRef src_begin)
		{
			out << "digraph " << fprtn_name << " {" << std::endl;
			out << "rankdir = LR" << std::endl;
			out << "ranksep = 0" << std::endl;
			out << "nodesep = .1" << std::endl;
//			out << "size = \"8,5\"" << std::endl;
//			out << "node [shape = ellipse];" << std::endl;

			//Print initial states (states having an arrow coming from nowhere, that is, from an invisible state "ini_i")
			int ini_count;
			state_ref_list_const_iterator i;
			for (i = m.ini_states.begin(), ini_count = 0; i != m.ini_states.end(); ++i, ++ini_count)
			{
				//Print ini_i state
				out << "ini_" << ini_count << " [style = invis];" << std::endl;
				//Print initial transition
				out << "ini_" << ini_count << " -> ";
				serialize_state_label(out, *i);
				out << ';' << std::endl;
				serialize_state(out, *i, src_begin);
			}

			//Print other states
			for (i = m.other_states.begin(); i != m.other_states.end(); ++i)
				serialize_state(out, *i, src_begin);
			return out << '}' << std::endl;
		}
	};

	template<typename SourceRef, typename TagInput, typename CharT, typename Traits>
	inline std::basic_ostream<CharT, Traits>& fprtn_to_dot_serialize(std::basic_ostream<CharT, Traits>& out, const char *fprtn_name, const fprtn<SourceRef, TagInput> &the_fprtn, SourceRef source_begin)
	{
		return fprtn_to_dot_serializer<SourceRef, typename tag_serializer<TagInput>::type>()(out, fprtn_name, the_fprtn, source_begin);
	}

	template<typename SourceRef, typename TagInputSerializer, typename CharT, typename Traits>
	inline std::basic_ostream<CharT, Traits>& fprtn_to_dot_serialize(std::basic_ostream<CharT, Traits>& out, const char *fprtn_name, const fprtn<SourceRef, typename serializer_traits<TagInputSerializer>::elem_type> &the_fprtn, SourceRef source_begin, const TagInputSerializer &tis)
	{ return fprtn_to_dot_serializer<SourceRef, TagInputSerializer>(tis)(out, fprtn_name, the_fprtn, source_begin); }
} //namespace grapenlp

#endif /*GRAPENLP_FPRTN_TO_DOT_SERIALIZER_H*/
