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

#ifndef GRAPE_U_DELAF_READER_H
#define GRAPE_U_DELAF_READER_H

#include <grape/error.h>
#include <grape/algorithm.h>
#include <grape/u_text_delaf.h>
#include <grape/u_trie_reader.h>
#include <grape/u_set_trie_reader.h>
#include <grape/u_set_reader.h>

namespace grape
{
	const std::array<unichar, 3> lemma_end_marks = { {'\n', lemma_separator, comment_separator} };
	const std::array<unichar, 3> canonical_form_end_marks = { {'\n', canonical_form_separator, comment_separator} };
	const std::array<unichar, 4> semantic_traits_end_marks = { {'\n', semantic_traits_separator, flexional_traits_separator, comment_separator} };
	const std::array<unichar, 4> flexional_traits_end_marks = { {'\n', flexional_traits_separator, clitic_pronouns_separator, comment_separator} };
	const std::array<unichar, 3> clitic_pronouns_end_marks = { {'\n', clitic_pronouns_separator, comment_separator} };

	template<typename CaseNormalizer>
	void u_read(FILE *f, u_text_delaf<CaseNormalizer> &d);

	template<typename CaseNormalizer>
	bool u_read_entry(FILE *f, std::size_t entry_count, u_text_delaf<CaseNormalizer> &dico);

	template<typename CaseNormalizer>
	inline unichar u_read_lemma(FILE *f, typename u_text_delaf<CaseNormalizer>::u_lemma_string::ref &lemma)
	{ return u_read<typename u_text_delaf<CaseNormalizer>::u_entry_list, std::array<unichar, 3>::const_iterator, CaseNormalizer>(f, lemma, lemma_end_marks.begin(), lemma_end_marks.end(), CaseNormalizer()); }

	template<typename CaseNormalizer>
	inline unichar u_read_canonical_form(FILE *f, typename u_text_delaf<CaseNormalizer>::u_lemma_string::ref &canonical_form)
	{ return u_read<typename u_text_delaf<CaseNormalizer>::u_entry_list, std::array<unichar, 3>::const_iterator, CaseNormalizer>(f, canonical_form, canonical_form_end_marks.begin(), canonical_form_end_marks.end(), CaseNormalizer()); }

	template<typename CaseNormalizer>
	unichar u_read_semantic_traits(FILE *f, std::size_t entry_count, u_text_delaf<CaseNormalizer> &d, typename u_text_delaf<CaseNormalizer>::ust_set& semantic_traits);

	inline unichar u_read_semantic_trait(FILE *f, ust_string::ref &semantic_trait)
	{ return u_read(f, semantic_trait, semantic_traits_end_marks.begin(), semantic_traits_end_marks.end()); }

	template<typename CaseNormalizer>
	unichar u_read_possible_flexional_traits(FILE *f, std::size_t entry_count, u_text_delaf<CaseNormalizer> &d, typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list &possible_flexional_traits);

	inline unichar u_read_flexional_traits(FILE *f, u_set &flexional_traits)
	{ return u_read(f, flexional_traits, flexional_traits_end_marks.begin(), flexional_traits_end_marks.end()); }

	template<typename CaseNormalizer>
	unichar u_read_clitic_pronouns(FILE *f, std::size_t entry_count, u_text_delaf<CaseNormalizer> &d, typename u_text_delaf<CaseNormalizer>::ust_set &clitic_pronouns);

	inline unichar u_read_clitic_pronoun(FILE *f, ust_string::ref &clitic_pronoun)
	{ return u_read(f, clitic_pronoun, clitic_pronouns_end_marks.begin(), clitic_pronouns_end_marks.end()); }

	template<typename CaseNormalizer>
	void u_read(FILE *f, u_text_delaf<CaseNormalizer> &d)
	{
		std::size_t entry_count(1);
		while (u_read_entry<CaseNormalizer>(f, entry_count, d))
			++entry_count;
	}

	template<typename CaseNormalizer>
	bool u_read_entry(FILE *f, std::size_t entry_count, u_text_delaf<CaseNormalizer> &d)
	{
		//Load mandatory lemma
		//A whole DELAF entry should be present, starting with the lemma, or nothing
		//if we are already at the end of the dictionary
		typename u_text_delaf<CaseNormalizer>::u_lemma_string::ref lemma(&d.lemma_to_entry_index.epsilon());
		unichar next_char = u_read_lemma<CaseNormalizer>(f, lemma);
		//Skip comment lines and read the following DELAF entry, or return if end of dico reached
		while (lemma == &d.lemma_to_entry_index.epsilon() && next_char == comment_separator)
		{
			//Skip comment line
			u_fskip_line(f);
			//End of dico reached
			if (feof(f))
				return false;
			//Read next dico comment line or entry
			next_char = u_read_lemma<CaseNormalizer>(f, lemma);
		}
		//If the lemma is empty but this is not a comment line
		if (lemma == &d.lemma_to_entry_index.epsilon())
		{
			//We are at the end of the dico
			if (feof(f))
				return false;
			//Or we are at the end of line just before the end of the dictionary
			while (u_is_white(next_char))
				next_char = u_fgetc(f);
			//Otherwise the DELAF entry is incomplete
			if (!feof(f))
				fatal_error("DELAF entry %d truncated after lemma\n", static_cast<int>(entry_count));
			return false;
		}

		//Load mandatory canonical form
		//The canonical form is mandatory but may be empty;
		//In that case, the lemma is also the canonical form
		typename u_text_delaf<CaseNormalizer>::u_lemma_string::ref canonical_form(&d.lemma_to_entry_index.epsilon());
		next_char = u_read_canonical_form<CaseNormalizer>(f, canonical_form);
		//After the canonical form there must be the separator between it and the POS;
		//otherwise the DELAF entry is incomplete
		if (feof(f) || next_char != canonical_form_separator)
			fatal_error("DELAF entry %d truncated after canonical form\n", static_cast<int>(entry_count));
		//If the canonical form is empty, the lemma is also the canonical form
		if (canonical_form == &d.lemma_to_entry_index.epsilon())
			canonical_form = lemma;

		//Load mandatory part-of-speech, with is processed as a semantic trait
		ust_string::ref pos(&d.ppooss.epsilon());
		next_char = u_read_semantic_trait(f, pos);
		//After the POS we may find an EOL, an EOF, a semantic trait separator or a flexional trait separator
		//The semantic traits, flexional traits and clitic pronouns are optional
		//Anyway, the POS should not be empty
		if (pos == &d.ppooss.epsilon())
			fatal_error("DELAF entry %d having an empty POS\n", static_cast<int>(entry_count));

		typename u_text_delaf<CaseNormalizer>::u_entry *entry_ref(new typename u_text_delaf<CaseNormalizer>::u_entry(*lemma, *canonical_form, *pos));

		//Load optional semantic traits
		//After the POS we may find a sequence of zero, one or more semantic traits
		if (next_char == semantic_traits_separator)
			next_char = u_read_semantic_traits<CaseNormalizer>(f, entry_count, d, entry_ref->semantic_traits);

		//Load optional flexional traits
		//After the sequence of zero, one or more semantic traits, we may find a sequence of zero, one or more flexional traits
		if (next_char == flexional_traits_separator)
		{
			next_char = u_read_possible_flexional_traits<CaseNormalizer>(f, entry_count, d, entry_ref->possible_flexional_traits);
			//Load clitic pronouns
			//If there are flexional traits specified, we may found zero, one or more clitic pronouns afterwards
			if (next_char == clitic_pronouns_separator)
				next_char = u_read_clitic_pronouns<CaseNormalizer>(f, entry_count, d, entry_ref->clitic_pronouns);
		}

		if (next_char == comment_separator)
			u_fskip_line(f);

		//If the lemma string did not have already any DELAF entry, initialize its entry list
		if (!lemma->data)
			lemma->data = new typename u_text_delaf<CaseNormalizer>::u_entry_list;
		//Otherwise, check for duplicated entries and fusion the entry to a duplicate
		else
		{
			typename u_text_delaf<CaseNormalizer>::u_entry_list::iterator i(lemma->data->begin());
			for (; i != lemma->data->end(); ++i)
			{
				if ((*i)->canonical_form == entry_ref->canonical_form && (*i)->pos == entry_ref->pos && (*i)->semantic_traits == entry_ref->semantic_traits)
				{
					entry_ref->possible_flexional_traits.transfer((*i)->possible_flexional_traits);
					return true;
				}
			}
		}
		//If no duplicates found or this is the first entry for the current lemma, just add it
		lemma->data->push_back(entry_ref);
		return true;
	}

	template<typename CaseNormalizer>
	unichar u_read_semantic_traits(FILE *f, std::size_t entry_count, u_text_delaf<CaseNormalizer> &dico, typename u_text_delaf<CaseNormalizer>::ust_set &semantic_traits)
	{
		ust_string::ref semantic_trait;
		unichar next_char;
		do
		{
			semantic_trait = &dico.semantic_traits.epsilon();
			next_char = u_read_semantic_trait(f, semantic_trait);
			if (semantic_trait == &dico.semantic_traits.epsilon())
				fatal_error("DELAF entry %d having an empty semantic trait\n", static_cast<int>(entry_count));
			semantic_traits.insert(semantic_trait);
		} while (!feof(f) && next_char == semantic_traits_separator);
		return next_char;
	}

	template<typename CaseNormalizer>
	unichar u_read_possible_flexional_traits(FILE *f, std::size_t entry_count, u_text_delaf<CaseNormalizer> &dico, typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list &possible_flexional_traits)
	{
		u_set *flexional_traits_ref;
		unichar next_char;
		do
		{
			flexional_traits_ref = new u_set();
			possible_flexional_traits.push_back(flexional_traits_ref);
			next_char = u_read_flexional_traits(f, *flexional_traits_ref);
			if (flexional_traits_ref->empty())
				fatal_error("DELAF entry %d having an empty sequence of flexional traits\n", static_cast<int>(entry_count));
			dico.flexional_traits.insert(flexional_traits_ref->begin(), flexional_traits_ref->end());
		} while (!feof(f) && next_char == flexional_traits_separator);
		return next_char;
	}

	template<typename CaseNormalizer>
	unichar u_read_clitic_pronouns(FILE *f, std::size_t entry_count, u_text_delaf<CaseNormalizer> &dico, typename u_text_delaf<CaseNormalizer>::ust_set &clitic_pronouns)
	{
		ust_string::ref clitic_pronoun;
		unichar next_char;
		do
		{
			clitic_pronoun = &dico.clitic_pronouns.epsilon();
			next_char = u_read_clitic_pronoun(f, clitic_pronoun);
			if (clitic_pronoun == &dico.clitic_pronouns.epsilon())
				fatal_error("DELAF entry %d having an empty semantic trait\n", entry_count);
			clitic_pronouns.insert(clitic_pronoun);
		} while (!feof(f) && next_char == clitic_pronouns_separator);
		return next_char;
	}
} //namespace grape

#endif /*GRAPE_U_DELAF_READER_H*/
