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

#ifndef GRAPENLP_DELAF_H
#define GRAPENLP_DELAF_H

#include <grapenlp/set_trie.h>
#include <grapenlp/list.h>
#include <grapenlp/algorithm.h>

namespace grapenlp
{
	template<typename Char, typename CaseNormalizer>
	class text_delaf
	{
	public:
		struct entry;

		//Types for lemma and canonical form handling
		typedef ptr_list<entry> entry_list;
		typedef trie_with_ptr_data<Char, entry_list> lemma_trie_with_entry_data;
		typedef typename lemma_trie_with_entry_data::string lemma_string;

		//Types for semantic traits and clitic pronouns handling
		typedef set_trie<Char> c_set_trie;
		typedef std::set<typename c_set_trie::string::ref> cst_set;
		typedef typename c_set_trie::string cst_string;

		//Types for possible flexional traits handling
		typedef std::set<Char> c_set;
		typedef ptr_list<c_set> flexional_traits_list;

		struct entry
		{
			lemma_string &lemma;
			lemma_string &canonical_form;
			cst_string &pos;
			cst_set semantic_traits;
			flexional_traits_list possible_flexional_traits;
			cst_set clitic_pronouns;

			entry(lemma_string &lemma_, lemma_string &canonical_form_, cst_string &pos_): lemma(lemma_), canonical_form(canonical_form_), pos(pos_), semantic_traits(), possible_flexional_traits(), clitic_pronouns()
			{}

			//Verifies that this entry has the specified canonical form
			bool match_canonical_form(const lemma_string &canonical_form_to_match) const
			{ return canonical_form == canonical_form_to_match; }

			//Verifies that this entry has the specified mandatory POS
			bool match_mandatory_pos(const cst_string &mandatory_pos) const
			{ return pos == mandatory_pos; }

			//Verifies that this entry does not have any of the specified forbidden POS
			bool match_forbidden_ppooss(const cst_set &forbidden_ppooss) const
			{ return excludes(forbidden_ppooss.begin(), forbidden_ppooss.end(), &pos); }

			//Verifies that this entry has all the specified semantic traits
			inline bool  match_mandatory_semantic_traits(const cst_set &mandatory_semantic_traits) const
			{ return std::includes(semantic_traits.begin(), semantic_traits.end(), mandatory_semantic_traits.begin(), mandatory_semantic_traits.end()); }

			//Verifies that this entry does not have any of the specified semantic traits
			bool match_forbidden_semantic_traits(const cst_set &forbidden_semantic_traits) const
			{ return disjoint(semantic_traits.begin(), semantic_traits.end(), forbidden_semantic_traits.begin(), forbidden_semantic_traits.end()); }

			//Verifies that this entry has all the mandatory specified semantic traits and no one of the specified forbidden semantic traits
			bool match_semantic_traits(const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits) const
			{
				return match_mandatory_semantic_traits(mandatory_semantic_traits) &&
				       match_forbidden_semantic_traits(forbidden_semantic_traits);
			}

			//Verifies that this entry has at least a possible set of flexional traits including at least one of the specified sets of possible flexional traits
			bool match_possible_flexional_traits(const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				typename flexional_traits_list::const_iterator i(possible_flexional_traits_to_match.begin()), j;
				for (; i != possible_flexional_traits_to_match.end(); ++i)
					for (j = possible_flexional_traits.begin(); j != possible_flexional_traits.end(); ++j)
						if (std::includes((*j)->begin(), (*j)->end(), (*i)->begin(), (*i)->end()))
							return true;
				return false;
			}

			bool match_canonical_form_and_mandatory_pos(const lemma_string &canonical_form_to_match, const cst_string &mandatory_pos) const
			{
				return match_canonical_form(canonical_form_to_match) &&
				       match_mandatory_pos(mandatory_pos);
			}

			bool match_canonical_form_and_forbidden_ppooss(const lemma_string &canonical_form_to_match, const cst_set &forbidden_ppooss) const
			{
				return match_canonical_form(canonical_form_to_match) &&
				       match_forbidden_ppooss(forbidden_ppooss);
			}

			bool match_canonical_form_and_semantic_traits(const lemma_string &canonical_form_to_match, const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits) const
			{
				return match_canonical_form(canonical_form_to_match) &&
				       match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits);
			}

			bool match_canonical_form_and_mandatory_pos_and_semantic_traits(const lemma_string &canonical_form_to_match, const cst_string &mandatory_pos, const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits) const
			{
				return match_canonical_form_and_mandatory_pos(canonical_form_to_match, mandatory_pos) &&
				       match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits);
			}

			bool match_canonical_form_and_forbidden_ppooss_and_semantic_traits(const lemma_string &canonical_form_to_match, const cst_set &forbidden_ppooss, const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits) const
			{
				return match_canonical_form_and_forbidden_ppooss(canonical_form_to_match, forbidden_ppooss) &&
				       match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits);
			}

			bool match_canonical_form_and_mandatory_pos_and_possible_flexional_traits(const lemma_string &canonical_form_to_match, const cst_string &mandatory_pos, const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_canonical_form_and_mandatory_pos(canonical_form_to_match, mandatory_pos) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits(const lemma_string &canonical_form_to_match, const cst_set &forbidden_ppooss, const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_canonical_form_and_forbidden_ppooss(canonical_form_to_match, forbidden_ppooss) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_canonical_form_and_semantic_and_possible_flexional_traits(const lemma_string &canonical_form_to_match, const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits, const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_canonical_form_and_semantic_traits(canonical_form_to_match, mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits);
			}

			bool match_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits(const lemma_string &canonical_form_to_match, const cst_string &mandatory_pos, const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits, const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_canonical_form_and_mandatory_pos_and_semantic_traits(canonical_form_to_match, mandatory_pos, mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits);
			}

			bool match_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits(const lemma_string &canonical_form_to_match, const cst_set &forbidden_ppooss, const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits, const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_canonical_form_and_forbidden_ppooss_and_semantic_traits(canonical_form_to_match, forbidden_ppooss, mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits);
			}

			bool match_mandatory_pos_and_semantic_traits(const cst_string &mandatory_pos, const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits) const
			{
				return match_mandatory_pos(mandatory_pos) &&
				       match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits);
			}

			bool match_forbidden_ppooss_and_semantic_traits(const cst_set &forbidden_ppooss, const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits) const
			{
				return match_forbidden_ppooss(forbidden_ppooss) &&
				       match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits);
			}

			bool match_mandatory_pos_and_possible_flexional_traits(const cst_string &mandatory_pos, const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_mandatory_pos(mandatory_pos) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_forbidden_ppooss_and_possible_flexional_traits(const cst_set &forbidden_ppooss, const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_forbidden_ppooss(forbidden_ppooss) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_mandatory_pos_and_semantic_and_possible_flexional_traits(const cst_string &mandatory_pos, const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits, const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_mandatory_pos_and_semantic_traits(mandatory_pos, mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_forbidden_ppooss_and_semantic_and_possible_flexional_traits(const cst_set &forbidden_ppooss, const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits, const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_forbidden_ppooss_and_semantic_traits(forbidden_ppooss, mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}

			bool match_semantic_and_possible_flexional_traits(const cst_set &mandatory_semantic_traits, const cst_set &forbidden_semantic_traits, const flexional_traits_list &possible_flexional_traits_to_match) const
			{
				return match_semantic_traits(mandatory_semantic_traits, forbidden_semantic_traits) &&
				       match_possible_flexional_traits(possible_flexional_traits_to_match);
			}
		};

		lemma_trie_with_entry_data lemma_to_entry_index;
		c_set_trie ppooss;
		c_set_trie semantic_traits;
		c_set flexional_traits;
		c_set_trie clitic_pronouns;

		text_delaf(): lemma_to_entry_index(), ppooss(), semantic_traits(), flexional_traits(), clitic_pronouns()
		{}

		template<typename Iterator>
		inline bool includes(Iterator begin, Iterator end) const
		{
			typename lemma_string::ref ls(lemma_to_entry_index.get(begin, end, CaseNormalizer()));
			return (ls && ls->data);
		}

		inline typename lemma_string::ref get(const Char &c)
		{ return lemma_to_entry_index.get(c); }

		inline typename lemma_string::const_ref get(const Char &c) const
		{ return lemma_to_entry_index.get(c); }

		template<typename Iterator>
		inline typename lemma_string::ref get(Iterator begin, Iterator end)
		{ return lemma_to_entry_index.get(begin, end, CaseNormalizer()); }

		template<typename Iterator>
		inline typename lemma_string::const_ref get(Iterator begin, Iterator end) const
		{ return lemma_to_entry_index.get(begin, end, CaseNormalizer()); }

		inline typename lemma_trie_with_entry_data::iterator begin()
		{ return lemma_to_entry_index.begin(); }

//		inline typename lemma_trie_with_entry_data::const_iterator begin() const
//		{ return lemma_to_entry_index.begin(); }

		inline typename lemma_trie_with_entry_data::iterator end()
		{ return lemma_to_entry_index.end(); }

//		inline typename lemma_trie_with_entry_data::const_iterator end()
//		{ return lemma_to_entry_index.end(); }
	};
} //namespace grapenlp

#endif /*GRAPENLP_DELAF_H*/
