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

#ifndef GRAPE_INV_OUTPUT_FPRTN_TO_DOT_SERIALIZER_H
#define GRAPE_INV_OUTPUT_FPRTN_TO_DOT_SERIALIZER_H
#include <ostream>
#include <string>
#include <grape/tag_serializer_traits.h>
#include <grape/output_fprtn.h>

namespace grape
{
	template<typename SourceRef, typename TagInputSerializer, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	struct inv_output_fprtn_to_dot_serializer
	{
		typedef StateMappedExtraData state_mapped_extra_data;
		typedef TagInputSerializer tag_input_serializer;

		typedef typename serializer_traits<tag_input_serializer>::elem_type tag_input;
		typedef output_fprtn<SourceRef, tag_input, RTNOTagInput, execution_state_set_impl_choice, edc, state_mapped_extra_data> elem_type;

		typedef elem_type machine;
		typedef typename machine::state state;
		typedef typename machine::state_const_ref state_const_ref;
		typedef typename machine::state_const_iterator state_const_iterator;
		typedef	typename machine::outgoing_epsilon_transition_set::const_iterator outgoing_epsilon_transition_set_const_iterator;
		typedef	typename machine::outgoing_consuming_transition_set::const_iterator outgoing_consuming_transition_set_const_iterator;
		typedef	typename machine::outgoing_call_transition_set::const_iterator outgoing_call_transition_set_const_iterator;
		typedef	typename machine::incoming_filtered_pop_transition_set::const_iterator incoming_filtered_pop_transition_set_const_iterator;

		typedef typename machine::chart_const_iterator chart_const_iterator;

	protected:
		tag_input_serializer tis;

	public:
		inv_output_fprtn_to_dot_serializer(): tis()
		{}

		inv_output_fprtn_to_dot_serializer(const TagInputSerializer &tis_): tis(tis_)
		{}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_state_label(std::basic_ostream<CharT, Traits>& out, const state &s)
		{ return s.serialize_fprtn_state(out << '"') << '"'; }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_state_kappa_label(std::basic_ostream<CharT, Traits>& out, const state &s)
		{ return s.serialize_fprtn_state(out << "\"k_") << '"'; }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_state(std::basic_ostream<CharT, Traits>& out, const state &s, std::size_t i)
		{
			//Set double circle if final state
			if (s.is_final())
			{
				serialize_state_label(out, s);
				out << "[peripheries = 2];" << std::endl;
			}
			//No need here for special serialization of states without outgoing transitions since they will at least be linked to their key box
			//Print key box
			serialize_state_kappa_label(out, s) << " [shape = box, height = 0, width = 0, label = \"" << i << "\"];" << std::endl;
			serialize_state_label(out, s);
			out << " -> ";
			serialize_state_kappa_label(out, s) << " [dir = none, minlen = 0, len = 0, tailport = s, headport = n];" << std::endl;;

			//Print epsilon transitions
			for (outgoing_epsilon_transition_set_const_iterator oet_it(s.second.incoming_epsilon_transitions.begin()); oet_it != s.second.incoming_epsilon_transitions.end(); ++oet_it)
			{
				serialize_state_label(out, s);
				out << " -> ";
				serialize_state_label(out, *oet_it->target);
				out << " [label = \"<E>\"];" << std::endl;
			}

			//Print deleting transitions
			for (outgoing_consuming_transition_set_const_iterator oconst_it(s.second.incoming_consuming_transitions.begin()); oconst_it != s.second.incoming_consuming_transitions.end(); ++oconst_it)
			{
				serialize_state_label(out, s);
				out << " -> ";
				serialize_state_label(out, *oconst_it->target);
				out << " [label = \"";
				tis(out, oconst_it->input) << "\"];" << std::endl;
			}

			//Print call and push transitions
			for (outgoing_call_transition_set_const_iterator ocallt_it(s.second.incoming_call_transitions.begin()); ocallt_it != s.second.incoming_call_transitions.end(); ++ocallt_it)
			{
				//Call
				serialize_state_label(out, s);
				out << " -> ";
				serialize_state_label(out, *ocallt_it->target);
				out << " [label = \"";
				ocallt_it->called->second.serialize(out) << "\", style = dashed];" << std::endl;

				//Push
				serialize_state_label(out, *ocallt_it->called);
				out << " -> ";
				serialize_state_label(out, *ocallt_it->target);
				out << " [label = \"";
				ocallt_it->target->second.serialize(out) << "\", style = dotted];" << std::endl;
			}

			//Print pop transitions
			for (incoming_filtered_pop_transition_set_const_iterator ifpopt_it(s.second.incoming_filtered_pop_transitions.begin()); ifpopt_it != s.second.incoming_filtered_pop_transitions.end(); ++ifpopt_it)
			{
				serialize_state_label(out, s);
				out << " -> ";
				serialize_state_label(out, *ifpopt_it->target);
				out << " [style = bold];" << std::endl;
			}

			return out;
		}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& operator() (std::basic_ostream<CharT, Traits>& out, const char *output_fprtn_name, const machine &m)
		{
			out << "digraph " << output_fprtn_name << " {" << std::endl;
			out << "rankdir = LR" << std::endl;
			out << "ranksep = 0" << std::endl;
			out << "nodesep = .1" << std::endl;
//			out << "size=\"8,5\"" << std::endl;
//			out << "node [shape = ellipse];" << std::endl;

			//Print ini_i state
			out << "ini" << " [style = invis];" << std::endl;
			//Print initial transition
			out << "ini" << " -> ";
			serialize_state_label(out, m.global_acceptor_state);
			out << ';' << std::endl;
			serialize_state(out, m.initial_state, 0);
			serialize_state(out, m.global_acceptor_state, m.the_chart.size() - 1);

			//Print other states
			chart_const_iterator c_it(m.the_chart.begin());
			for (std::size_t i(0); i < m.the_chart.size(); ++i, ++c_it)
				for (state_const_iterator s_it(c_it->other_states.begin()); s_it != c_it->other_states.end(); ++s_it)
					serialize_state(out, static_cast<const state&>(*s_it), i);
			return out << '}' << std::endl;
		}
	};

	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData, typename CharT, typename Traits>
	inline std::basic_ostream<CharT, Traits>& inv_output_fprtn_to_dot_serialize(std::basic_ostream<CharT, Traits>& out, const char *output_fprtn_name, const output_fprtn<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, StateMappedExtraData> &the_output_fprtn)
	{ return inv_output_fprtn_to_dot_serializer<SourceRef, typename tag_serializer<TagInput>::type, RTNOTagInput, execution_state_set_impl_choice, edc, StateMappedExtraData>()(out, output_fprtn_name, the_output_fprtn); }

	template<typename SourceRef, typename TagInputSerializer, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData, typename CharT, typename Traits>
	inline std::basic_ostream<CharT, Traits>& inv_output_fprtn_to_dot_serialize(std::basic_ostream<CharT, Traits>& out, const char *output_fprtn_name, const output_fprtn<SourceRef, typename serializer_traits<TagInputSerializer>::elem_type, RTNOTagInput, execution_state_set_impl_choice, edc, StateMappedExtraData> &the_output_fprtn, const TagInputSerializer &tis)
	{ return inv_output_fprtn_to_dot_serializer<SourceRef, TagInputSerializer, RTNOTagInput, execution_state_set_impl_choice, edc, StateMappedExtraData>(tis)(out, output_fprtn_name, the_output_fprtn); }

#ifdef TRACE
	template<typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc, typename StateMappedExtraData>
	void write_inv_fprtn_dot(const char *inv_fprtn_name, const char *dot_inv_fprtn_pathname, output_fprtn<SourceRef, TagInput, RTNOTagInput, execution_state_set_impl_choice, edc, StateMappedExtraData> &m)
	{
		std::wofstream fout;
		fout.imbue(std::locale(setlocale(LC_CTYPE, NULL)));
		fout.open(dot_inv_fprtn_pathname);
		if (fout)
		{
			inv_output_fprtn_to_dot_serialize(fout, inv_fprtn_name, m);
			fout.close();
		}
		else std::wcerr << "Unable to open file \"" << dot_inv_fprtn_pathname << "\" for writing" << std::endl;
		std::wcout << "Written \"" << dot_inv_fprtn_pathname << "\"\n";
	}
#endif
} //namespace grape

#endif /*GRAPE_INV_OUTPUT_FPRTN_TO_DOT_SERIALIZER_H*/
