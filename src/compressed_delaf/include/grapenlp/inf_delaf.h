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

#ifndef GRAPENLP_INF_DELAF_H
#define GRAPENLP_INF_DELAF_H

#include <memory>
#include <array>

#include <grapenlp/iostream.h>
#include <grapenlp/u_set.h>
#include <grapenlp/u_set_trie.h>
#include <grapenlp/list.h>
#include <grapenlp/u_delaf_constants.h>
#include <grapenlp/u_array.h>
#include <grapenlp/algorithm.h>
#include <grapenlp/vector.h>

namespace grapenlp
{
	const unichar ambiguous_entry_separator = '\n';

	class inf_delaf
	{
	public:
		//Types for semantic traits and clitic pronouns handling
		typedef std::set<u_set_trie::string::ref> ust_set;
		typedef u_set_trie::string ust_string;

		//Types for possible flexional traits handling
		typedef ptr_list<u_set> u_flexional_traits_list;

		struct entry;
		typedef ptr_vector<entry> ambiguous_entry;
		typedef const ptr_vector<entry> const_ambiguous_entry;
		typedef ptr_vector<ambiguous_entry> entry_list;

/*		template<typename UCharIterator>
		struct compressed_canonical_form
		{
			unsigned char inflected_form_suffix_length;
			UCharIterator canonical_form_suffix_begin;
			UCharIterator canonical_form_suffix_end;

			compressed_canonical_form(unsigned char inflected_form_suffix_length_, UCharIterator canonical_form_suffix_begin_, UCharIterator canonical_form_suffix_end_): inflected_form_suffix_length(inflected_form_suffix_length_), canonical_form_suffix_begin(canonical_form_suffix_begin_), canonical_form_suffix_end(canonical_form_suffix_end_)
			{}
		};*/

		struct entry
		{
//			entry* ref;
//			const entry* const_ref;
			unsigned char inflected_form_suffix_length;
			u_array canonical_form_suffix;
			ust_string &pos;
			ust_set semantic_traits;
			u_flexional_traits_list possible_flexional_traits;
			ust_set clitic_pronouns;

			entry(unsigned char inflected_form_suffix_length_, u_array &&canonical_form_suffix_, ust_string &pos_): inflected_form_suffix_length(inflected_form_suffix_length_), canonical_form_suffix(std::move(canonical_form_suffix_)), pos(pos_), semantic_traits(), possible_flexional_traits(), clitic_pronouns()
			{}

			bool is_canonical_form()
			{ return !inflected_form_suffix_length && !canonical_form_suffix.size(); }

//			compressed_canonical_form<u_array::const_iterator> get_compressed_canonical_form()
//			{ return compressed_canonical_form<u_array::const_iterator>(inflected_form_suffix_length, canonical_form_suffix.begin(), canonical_form_suffix.end()); }

			template<typename UCharIterator>
			std::size_t get_decompressed_canonical_form_size(UCharIterator inflected_form_begin, UCharIterator inflected_form_end)
			{ return std::distance(inflected_form_begin, inflected_form_end) - inflected_form_suffix_length + canonical_form_suffix.size(); }

			//Verifies that this entry has the specified canonical form
			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_begin, CanonicalFormCharIterator canonical_form_end) const
			{
				unsigned char i(inflected_form_suffix_length);
				for (; i > 0; --i)
					--lemma_end;
				return concat_equal(lemma_begin, lemma_end, canonical_form_suffix.begin(), canonical_form_suffix.end(), canonical_form_begin, canonical_form_end);
			}

			//Verifies that this entry has the specified mandatory POS
			bool match_mandatory_pos(const ust_string &mandatory_pos) const
			{ return pos == mandatory_pos; }

			//Verifies that this entry does not have any of the specified forbidden POS
			bool match_forbidden_ppooss(const ust_set &forbidden_ppooss) const
			{ return excludes(forbidden_ppooss.begin(), forbidden_ppooss.end(), &pos); }

			//Verifies that this entry has all the specified semantic traits
			bool  match_mandatory_semantic_traits(const ust_set &mandatory_semantic_traits) const
			{ return std::includes(semantic_traits.begin(), semantic_traits.end(), mandatory_semantic_traits.begin(), mandatory_semantic_traits.end()); }

			//Verifies that this entry does not have any of the specified semantic traits
			bool match_forbidden_semantic_traits(const ust_set &forbidden_semantic_traits) const
			{ return disjoint(semantic_traits.begin(), semantic_traits.end(), forbidden_semantic_traits.begin(), forbidden_semantic_traits.end()); }

			//Verifies that this entry has all the mandatory specified semantic traits and no one of the specified forbidden semantic traits
			bool match_semantic_traits(const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits) const
			{
				return match_mandatory_semantic_traits(mandatory_semantic_traits) &&
				       match_forbidden_semantic_traits(forbidden_semantic_traits);
			}

			//Verifies that this entry has at least a possible set of flexional traits including at least one of the specified sets of possible flexional traits
			bool match_possible_flexional_traits(const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				u_flexional_traits_list::const_iterator i(possible_flexional_traits_to_match.begin()), j;
				for (; i != possible_flexional_traits_to_match.end(); ++i)
					for (j = possible_flexional_traits.begin(); j != possible_flexional_traits.end(); ++j)
						if (std::includes((*j)->begin(), (*j)->end(), (*i)->begin(), (*i)->end()))
							return true;
				return false;
			}

			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form_and_mandatory_pos(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_to_match_begin, CanonicalFormCharIterator canonical_form_to_match_end, const ust_string &mandatory_pos) const
			{
				return match_canonical_form(lemma_begin, lemma_end, canonical_form_to_match_begin, canonical_form_to_match_end) &&
				       match_mandatory_pos(mandatory_pos);
			}

			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form_and_forbidden_ppooss(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_to_match_begin, CanonicalFormCharIterator canonical_form_to_match_end, const ust_set &forbidden_ppooss) const
			{
				return match_canonical_form(lemma_begin, lemma_end, canonical_form_to_match_begin, canonical_form_to_match_end) &&
				       match_forbidden_ppooss(forbidden_ppooss);
			}

			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form_and_semantic_traits(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_to_match_begin, CanonicalFormCharIterator canonical_form_to_match_end, const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits) const
			{
				return match_canonical_form(lemma_begin, lemma_end, canonical_form_to_match_begin, canonical_form_to_match_end) &&
				       match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits);
			}

			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form_and_mandatory_pos_and_semantic_traits(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_to_match_begin, CanonicalFormCharIterator canonical_form_to_match_end, const ust_string &mandatory_pos, const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits) const
			{
				return match_canonical_form_and_mandatory_pos(lemma_begin, lemma_end, canonical_form_to_match_begin, canonical_form_to_match_end, mandatory_pos) &&
				       match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits);
			}

			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form_and_forbidden_ppooss_and_semantic_traits(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_to_match_begin, CanonicalFormCharIterator canonical_form_to_match_end, const ust_set &forbidden_ppooss, const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits) const
			{
				return match_canonical_form_and_forbidden_ppooss(lemma_begin, lemma_end, canonical_form_to_match_begin, canonical_form_to_match_end, forbidden_ppooss) &&
				       match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits);
			}

			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form_and_mandatory_pos_and_possible_flexional_traits(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_to_match_begin, CanonicalFormCharIterator canonical_form_to_match_end, const ust_string &mandatory_pos, const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_canonical_form_and_mandatory_pos(lemma_begin, lemma_end, canonical_form_to_match_begin, canonical_form_to_match_end, mandatory_pos) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_to_match_begin, CanonicalFormCharIterator canonical_form_to_match_end, const ust_set &forbidden_ppooss, const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_canonical_form_and_forbidden_ppooss(lemma_begin, lemma_end, canonical_form_to_match_begin, canonical_form_to_match_end, forbidden_ppooss) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form_and_semantic_and_possible_flexional_traits(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_to_match_begin, CanonicalFormCharIterator canonical_form_to_match_end, const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits, const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_canonical_form_and_semantic_traits(lemma_begin, lemma_end, canonical_form_to_match_begin, canonical_form_to_match_end, mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_to_match_begin, CanonicalFormCharIterator canonical_form_to_match_end, const ust_string &mandatory_pos, const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits, const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_canonical_form_and_mandatory_pos_and_semantic_traits(lemma_begin, lemma_end, canonical_form_to_match_begin, canonical_form_to_match_end, mandatory_pos, mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			template<typename LemmaCharIterator, typename CanonicalFormCharIterator>
			bool match_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits(LemmaCharIterator lemma_begin, LemmaCharIterator lemma_end, CanonicalFormCharIterator canonical_form_to_match_begin, CanonicalFormCharIterator canonical_form_to_match_end, const ust_set &forbidden_ppooss, const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits, const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_canonical_form_and_forbidden_ppooss_and_semantic_traits(lemma_begin, lemma_end, canonical_form_to_match_begin, canonical_form_to_match_end, forbidden_ppooss, mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_mandatory_pos_and_semantic_traits(const ust_string &mandatory_pos, const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits) const
			{
				return match_mandatory_pos(mandatory_pos) &&
				       match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits);
			}

			bool match_forbidden_ppooss_and_semantic_traits(const ust_set &forbidden_ppooss, const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits) const
			{
				return match_forbidden_ppooss(forbidden_ppooss) &&
				       match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits);
			}

			bool match_mandatory_pos_and_possible_flexional_traits(const ust_string &mandatory_pos, const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_mandatory_pos(mandatory_pos) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_forbidden_ppooss_and_possible_flexional_traits(const ust_set &forbidden_ppooss, const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_forbidden_ppooss(forbidden_ppooss) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_mandatory_pos_and_semantic_and_possible_flexional_traits(const ust_string &mandatory_pos, const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits, const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_mandatory_pos_and_semantic_traits(mandatory_pos, mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_forbidden_ppooss_and_semantic_and_possible_flexional_traits(const ust_set &forbidden_ppooss, const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits, const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_forbidden_ppooss_and_semantic_traits(forbidden_ppooss, mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_semantic_and_possible_flexional_traits(const ust_set &mandatory_semantic_traits, const ust_set &forbidden_semantic_traits, const u_flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}
		};

		u_set_trie ppooss;
		u_set_trie semantic_traits;
		u_set flexional_traits;
		u_set_trie clitic_pronouns;
		entry_list entries;

		inf_delaf(): ppooss(), semantic_traits(), flexional_traits(), clitic_pronouns(), entries()
		{}
	};

	template<typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const inf_delaf::entry &e)
	{
		if (e.canonical_form_suffix.size())
			out << e.inflected_form_suffix_length << e.canonical_form_suffix;
		e.pos.serialize(out << '.');

		if (!e.semantic_traits.empty())
		{
			out << semantic_traits_separator;
			serialize_ptr_sequence(out, e.semantic_traits.begin(), e.semantic_traits.end(), semantic_traits_separator);
		}

		if (!e.possible_flexional_traits.empty())
		{
			out << flexional_traits_separator;

			sequence_serializer<u_set::const_iterator> u_set_serializer;

			serialize_sequence_of_ptr_sequences(out, e.possible_flexional_traits.begin(), e.possible_flexional_traits.end(), flexional_traits_separator, u_set_serializer);
			if (!e.clitic_pronouns.empty())
			{
				out << clitic_pronouns_separator;
				serialize_ptr_sequence(out, e.clitic_pronouns.begin(), e.clitic_pronouns.end(), clitic_pronouns_separator);
			}
		}
		return out;
	}

	template<typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, inf_delaf::const_ambiguous_entry &ae)
	{
		if (ae.empty())
		return out;
		inf_delaf::ambiguous_entry::const_iterator i(ae.begin());
		out << **i;
		++i;
		for (; i != ae.end(); ++i)
			out << entry_separator << **i;
		return out;
	}
} //namespace grapenlp

#endif /*GRAPENLP_INF_DELAF_H*/
