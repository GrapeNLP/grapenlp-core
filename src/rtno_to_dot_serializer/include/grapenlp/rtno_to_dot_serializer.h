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

#ifndef GRAPENLP_RTNO_TO_DOT_SERIALIZER_H
#define GRAPENLP_RTNO_TO_DOT_SERIALIZER_H
#include <ostream>
#include <string>
#include <grapenlp/tag_serializer_traits.h>
#include <grapenlp/rtno.h>

namespace grapenlp
{
	template<typename TagInputSerializer, typename TagOutputSerializer, typename ContextMaskSerializer>
	struct rtno_to_dot_serializer
	{
		typedef ContextMaskSerializer context_mask_serializer;
		typedef TagInputSerializer tag_input_serializer;
		typedef TagOutputSerializer tag_output_serializer;

		typedef typename serializer_traits<context_mask_serializer>::elem_type context_mask;
		typedef typename serializer_traits<tag_input_serializer>::elem_type tag_input;
		typedef typename serializer_traits<tag_output_serializer>::elem_type tag_output;
		typedef ns_rtno<tag_input, tag_output, context_mask> elem_type;

		typedef elem_type machine;
		typedef typename machine::state state;
		typedef typename machine::state_const_ref state_const_ref;
		typedef typename machine::state_ref_list_const_iterator state_ref_list_const_iterator;
		typedef	typename machine::outgoing_epsilon_transition_set::const_iterator outgoing_epsilon_transition_set_const_iterator;
		typedef	typename machine::outgoing_inserting_transition_set::const_iterator outgoing_inserting_transition_set_const_iterator;
		typedef	typename machine::outgoing_epsilon_context_transition_set::const_iterator outgoing_epsilon_context_transition_set_const_iterator;
		typedef	typename machine::outgoing_inserting_context_transition_set::const_iterator outgoing_inserting_context_transition_set_const_iterator;
		typedef	typename machine::outgoing_deleting_transition_set::const_iterator outgoing_deleting_transition_set_const_iterator;
		typedef	typename machine::outgoing_translating_transition_set::const_iterator outgoing_translating_transition_set_const_iterator;
		typedef	typename machine::outgoing_call_transition_set::const_iterator outgoing_call_transition_set_const_iterator;

	protected:
		tag_input_serializer tis;
		tag_output_serializer tos;
		context_mask_serializer cms;

	public:
		rtno_to_dot_serializer(): tis(), tos(), cms()
		{}

		rtno_to_dot_serializer(const TagInputSerializer &tis_, const TagOutputSerializer &tos_): tis(tis_), tos(tos_)
		{}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_state_label(std::basic_ostream<CharT, Traits>& out, CharT state_letter, state_const_ref s)
		{ return s->serialize(out << '"', state_letter) << '"'; }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_state(std::basic_ostream<CharT, Traits>& out, CharT state_letter, state_const_ref s)
		{
			//Set double circle if final state
			if (s->is_final())
			{
				serialize_state_label(out, state_letter, s);
				out << "[peripheries = 2];" << std::endl;
			}
			//Serialize at least the state label when it has no outgoing transitions
			else if (s->has_no_transitions())
				return serialize_state_label(out, state_letter, s) << ';' << std::endl;

			if (s->has_no_transitions())
			{
				serialize_state_label(out, state_letter, s) << ';' << std::endl;
				return out;
			}
			//Print epsilon transitions
			outgoing_epsilon_transition_set_const_iterator oet_it;
			for (oet_it = s->outgoing_epsilon_transitions.begin(); oet_it != s->outgoing_epsilon_transitions.end(); ++oet_it)
			{
				serialize_state_label(out, state_letter, s);
				out << " -> ";
				serialize_state_label(out, state_letter, static_cast<state_const_ref>(oet_it->target));
				out << " [label = \"<E>\"];" << std::endl;
			}
			outgoing_epsilon_context_transition_set_const_iterator oect_it;
			for (oect_it = s->outgoing_epsilon_context_transitions.begin(); oect_it != s->outgoing_epsilon_context_transitions.end(); ++oect_it)
			{
				serialize_state_label(out, state_letter, s);
				out << " -> ";
				serialize_state_label(out, state_letter, static_cast<state_const_ref>(oect_it->target));
				out << " [label = \"<E>\"];" << std::endl;
			}
			outgoing_inserting_transition_set_const_iterator oit_it;
			for (oit_it = s->outgoing_inserting_transitions.begin(); oit_it != s->outgoing_inserting_transitions.end(); ++oit_it)
			{
				serialize_state_label(out, state_letter, s);
				out << " -> ";
				serialize_state_label(out, state_letter, static_cast<state_const_ref>(oit_it->target));
				out << " [label = \"<E>/";
				tos(out, oit_it->output) << "\"];" << std::endl;
			}
			for (oet_it = s->outgoing_no_blank_epsilon_transitions.begin(); oet_it != s->outgoing_no_blank_epsilon_transitions.end(); ++oet_it)
			{
				serialize_state_label(out, state_letter, s);
				out << " -> ";
				serialize_state_label(out, state_letter, static_cast<state_const_ref>(oet_it->target));
				out << " [label = \"#\"];" << std::endl;
			}
			for (oit_it = s->outgoing_no_blank_inserting_transitions.begin(); oit_it != s->outgoing_no_blank_inserting_transitions.end(); ++oit_it)
			{
				serialize_state_label(out, state_letter, s);
				out << " -> ";
				serialize_state_label(out, state_letter, static_cast<state_const_ref>(oit_it->target));
				out << " [label = \"#/";
				tos(out, oit_it->output) << "\"];" << std::endl;
			}
			for (oet_it = s->outgoing_blank_epsilon_transitions.begin(); oet_it != s->outgoing_blank_epsilon_transitions.end(); ++oet_it)
			{
				serialize_state_label(out, state_letter, s);
				out << " -> ";
				serialize_state_label(out, state_letter, static_cast<state_const_ref>(oet_it->target));
				out << " [label = \"'\\ '\"];" << std::endl;
			}
			for (oit_it = s->outgoing_blank_inserting_transitions.begin(); oit_it != s->outgoing_blank_inserting_transitions.end(); ++oit_it)
			{
				serialize_state_label(out, state_letter, s);
				out << " -> ";
				serialize_state_label(out, state_letter, static_cast<state_const_ref>(oit_it->target));
				out << " [label = \"'\\ '/";
				tos(out, oit_it->output) << "\"];" << std::endl;
			}

			//Print deleting transitions
			outgoing_deleting_transition_set_const_iterator odt_it;
			for (odt_it = s->outgoing_deleting_transitions.begin(); odt_it != s->outgoing_deleting_transitions.end(); ++odt_it)
			{
				serialize_state_label(out, state_letter, s);
				out << " -> ";
				serialize_state_label(out, state_letter, static_cast<state_const_ref>(odt_it->target));
				out << " [label = \"";
				tis(out, odt_it->input) << "\"];" << std::endl;
			}

			//Print translating transitions
			outgoing_translating_transition_set_const_iterator ott_it;
			for (ott_it = s->outgoing_translating_transitions.begin(); ott_it != s->outgoing_translating_transitions.end(); ++ott_it)
			{
				serialize_state_label(out, state_letter, s);
				out << " -> ";
				serialize_state_label(out, state_letter, static_cast<state_const_ref>(ott_it->target));
				tis(out << " [label = \"", ott_it->input) << '/';
				tos(out, ott_it->output) << "\"];" << std::endl;
			}

			//Print call transitions
			outgoing_call_transition_set_const_iterator ocallt_it;
			for (ocallt_it = s->outgoing_call_transitions.begin(); ocallt_it != s->outgoing_call_transitions.end(); ++ocallt_it)
			{
				serialize_state_label(out, state_letter, s);
				out << " -> ";
				serialize_state_label(out, state_letter, static_cast<state_const_ref>(ocallt_it->target));
				out << " [label = \"";
				out << static_cast<state_const_ref>(ocallt_it->called)->template basic_label<CharT, Traits>(state_letter) << "\", style = dashed];" << std::endl;
			}
			return out;
		}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& operator() (std::basic_ostream<CharT, Traits>& out, const char *rtno_name, CharT state_letter, const machine &m)
		{
			out << "digraph " << rtno_name << " {" << std::endl;
			out << "rankdir=LR" << std::endl;
			out << "ranksep=0" << std::endl;
			out << "nodesep=.1" << std::endl;
//			out << "size=\"8,5\"" << std::endl;
//			out << "node [shape = ellipse];" << std::endl;

			//Print initial states (states having an arrow coming from nowhere, that is, from an invisible state "ini_i")
			state_ref_list_const_iterator i(m.states.begin());
			//Print arrow towards initial state
			out << "ini" << " [style = invis];" << std::endl;
			//Print initial transition
			out << "ini" << " -> ";
			serialize_state_label(out, state_letter, m.initial_state());
			out << ';' << std::endl;
			//Print states
			for (state_ref_list_const_iterator i(m.states.begin()); i != m.states.end(); ++i)
				serialize_state(out, state_letter, static_cast<state_const_ref>(*i));
			return out << '}' << std::endl;
		}
	};

	template<typename TagInput, typename TagOutput, typename ContextMask, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& rtno_to_dot_serialize(std::basic_ostream<CharT, Traits>& out, const char *rtno_name, CharT state_letter, const ns_rtno<TagInput, TagOutput, ContextMask> &the_rtno)
	{ return rtno_to_dot_serializer<typename tag_serializer<TagInput>::type, typename tag_serializer<TagOutput>::type, tag_serializer<ContextMask> >()(out, rtno_name, state_letter, the_rtno);	}

	template<typename TagInputSerializer, typename TagOutputSerializer, typename ContextMaskSerializer, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& rtno_to_dot_serialize(std::basic_ostream<CharT, Traits>& out, const char *rtno_name, CharT state_letter, const ns_rtno<typename serializer_traits<TagInputSerializer>::elem_type, typename serializer_traits<TagOutputSerializer>::elem_type, typename serializer_traits<ContextMaskSerializer>::elem_type> &the_rtno, const TagInputSerializer &tis, const TagOutputSerializer &tos, const ContextMaskSerializer &cms)
	{ return rtno_to_dot_serializer<TagInputSerializer, TagOutputSerializer, ContextMaskSerializer>(tis, tos, cms)(out, rtno_name, state_letter, the_rtno); }
} //namespace grapenlp

#endif /*GRAPENLP_RTNO_TO_DOT_SERIALIZER_H*/
