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

#ifndef GRAPENLP_INF_DELAF_READER_H
#define GRAPENLP_INF_DELAF_READER_H

#include <grapenlp/iostream.h>
#include <grapenlp/u_delaf_constants.h>
#include <grapenlp/u_set_reader.h>
#include <grapenlp/u_set_trie_reader.h>
#include <grapenlp/inf_delaf.h>
#include <grapenlp/u_vector_reader.h>

namespace grapenlp
{
	const std::array<unichar, 4> inf_delaf_semantic_traits_end_marks = { {'\n', entry_separator, semantic_traits_separator, flexional_traits_separator} };
	const std::array<unichar, 4> inf_delaf_flexional_traits_end_marks = { {'\n', entry_separator, flexional_traits_separator, clitic_pronouns_separator} };
	const std::array<unichar, 3> inf_delaf_clitic_pronouns_end_marks = { {'\n', entry_separator, clitic_pronouns_separator} };

	void u_read(FILE *f, inf_delaf &dico);
	void u_read_inf_delaf_ambiguous_entry(FILE *f, std::size_t ambiguous_entry_count, inf_delaf &dico);
	unichar u_read_inf_delaf_entry(FILE *f, std::size_t ambiguous_entry_count, inf_delaf &dico, inf_delaf::ambiguous_entry &ae);
	unichar u_read_inf_delaf_canonical_form(FILE *f, unsigned char &inflected_form_suffix_length, u_array &canonical_form_suffix);

	unichar u_read_inf_delaf_semantic_traits(FILE *f, std::size_t ambiguous_entry_count, inf_delaf &dico, inf_delaf::ust_set &semantic_traits);

	inline unichar u_read_inf_delaf_semantic_trait(FILE *f, ust_string::ref &semantic_trait)
	{ return u_read(f, semantic_trait, inf_delaf_semantic_traits_end_marks.begin(), inf_delaf_semantic_traits_end_marks.end()); }

	unichar u_read_inf_delaf_possible_flexional_traits(FILE *f, std::size_t ambiguous_entry_count, inf_delaf &dico, inf_delaf::u_flexional_traits_list &possible_flexional_traits);

	inline unichar u_read_inf_delaf_flexional_traits(FILE *f, u_set &flexional_traits)
	{ return u_read(f, flexional_traits, inf_delaf_flexional_traits_end_marks.begin(), inf_delaf_flexional_traits_end_marks.end()); }

	unichar u_read_inf_delaf_clitic_pronouns(FILE *f, std::size_t ambiguous_entry_count, inf_delaf &dico, inf_delaf::ust_set &clitic_pronouns);

	inline unichar u_read_inf_delaf_clitic_pronoun(FILE *f, ust_string::ref &clitic_pronoun)
	{ return u_read(f, clitic_pronoun, inf_delaf_clitic_pronouns_end_marks.begin(), inf_delaf_clitic_pronouns_end_marks.end()); }

	void u_read(FILE *f, inf_delaf &dico)
	{
		//Get entry count
		std::size_t ambiguous_entry_count;
//		std::wcout << "Reading ambiguous entry count: ";
		u_fread_unsigned_int(f, ambiguous_entry_count);
//		std::wcout << ambiguous_entry_count << std::endl;
		//Reserve space for all the entries
		dico.entries.reserve(ambiguous_entry_count);

		//For each entry, load it
		std::size_t i(0);
		for (; i < ambiguous_entry_count; ++i)
		{
			u_read_inf_delaf_ambiguous_entry(f, ambiguous_entry_count, dico);
//			std::wcout << ambiguous_entry_separator;
		}
	}

	void u_read_inf_delaf_ambiguous_entry(FILE *f, std::size_t ambiguous_entry_count, inf_delaf &dico)
	{
		std::unique_ptr<inf_delaf::ambiguous_entry> ae_ref(new inf_delaf::ambiguous_entry);
		unichar next_char(u_read_inf_delaf_entry(f,  ambiguous_entry_count, dico, *ae_ref));
		while (next_char != ambiguous_entry_separator)
		{
//			std::wcout << ',';
			next_char = u_read_inf_delaf_entry(f, ambiguous_entry_count, dico, *ae_ref);
		}
		dico.entries.push_back(ae_ref.release());
	}

	unichar u_read_inf_delaf_entry(FILE *f, std::size_t ambiguous_entry_count, inf_delaf &dico, inf_delaf::ambiguous_entry &ae)
	{
		//Load mandatory canonical form
		//The canonical form is mandatory but may be empty;
		//In that case, the lemma is also the canonical form
		unsigned char inflected_form_suffix_length;
		u_array canonical_form_suffix;
		unichar next_char = u_read_inf_delaf_canonical_form(f, inflected_form_suffix_length, canonical_form_suffix);

		//After the canonical form there must be the separator between it and the POS;
		//otherwise the DELAF entry is incomplete
		if (feof(f) || next_char != canonical_form_separator)
			fatal_error("INF DELAF entry %d truncated after canonical form\n", static_cast<int>(ambiguous_entry_count));

		//Load mandatory part-of-speech, with is processed as a semantic trait
//		std::wcout << canonical_form_separator;
		ust_string::ref pos(&dico.ppooss.epsilon());
		next_char = u_read_inf_delaf_semantic_trait(f, pos);
		//After the POS we may find an EOL, an EOF, a semantic trait separator or a flexional trait separator
		//The semantic traits, flexional traits and clitic pronouns are optional
		//Anyway, the POS should not be empty
		if (pos == &dico.ppooss.epsilon())
			fatal_error("DELAF entry %d having an empty POS\n", static_cast<int>(ambiguous_entry_count));
//		std::wcout << *pos;

		std::unique_ptr<inf_delaf::entry> e_ref(new inf_delaf::entry(inflected_form_suffix_length, std::move(canonical_form_suffix), *pos));

		//Load optional semantic traits
		//After the POS we may find a sequence of zero, one or more semantic traits
		if (next_char == semantic_traits_separator)
			next_char = u_read_inf_delaf_semantic_traits(f, ambiguous_entry_count, dico, e_ref->semantic_traits);

		//Load optional flexional traits
		//After the sequence of zero, one or more semantic traits, we may find a sequence of zero, one or more flexional traits
		if (next_char == flexional_traits_separator)
		{
			next_char = u_read_inf_delaf_possible_flexional_traits(f, ambiguous_entry_count, dico, e_ref->possible_flexional_traits);
			//Load clitic pronouns
			//If there are flexional traits specified, we may found zero, one or more clitic pronouns afterwards
			if (next_char == clitic_pronouns_separator)
				next_char = u_read_inf_delaf_clitic_pronouns(f, ambiguous_entry_count, dico, e_ref->clitic_pronouns);
		}

		if (next_char == comment_separator)
			u_fskip_line(f);

		ae.push_back(e_ref.release());
		return next_char;
	}

	unichar u_read_inf_delaf_canonical_form(FILE *f, unsigned char &inflected_form_suffix_length, u_array &canonical_form_suffix)
	{
		unichar next_char(u_fread_optional_unsigned_int<unsigned char>(f, inflected_form_suffix_length));
		if (next_char != canonical_form_separator) {
            u_vector canonical_form_suffix_vector;
            canonical_form_suffix_vector.push_back(next_char);
            next_char = u_read(f, canonical_form_suffix_vector, canonical_form_separator);
            canonical_form_suffix.reset(canonical_form_suffix_vector.begin(), canonical_form_suffix_vector.end());
//   		std::wcout << canonical_form_suffix;
        }
		return next_char;
	}

	unichar u_read_inf_delaf_semantic_traits(FILE *f, std::size_t ambiguous_entry_count, inf_delaf &dico, inf_delaf::ust_set &semantic_traits)
	{
		ust_string::ref semantic_trait;
		unichar next_char;
		do
		{
//			std::wcout << semantic_traits_separator;
			semantic_trait = &dico.semantic_traits.epsilon();
			next_char = u_read_inf_delaf_semantic_trait(f, semantic_trait);
			if (semantic_trait == &dico.semantic_traits.epsilon())
				fatal_error("DELAF entry %d having an empty semantic trait\n", static_cast<int>(ambiguous_entry_count));
			semantic_traits.insert(semantic_trait);
//			std::wcout << *semantic_trait;
		} while (!feof(f) && next_char == semantic_traits_separator);
		return next_char;
	}

	unichar u_read_inf_delaf_possible_flexional_traits(FILE *f, std::size_t ambiguous_entry_count, inf_delaf &dico, inf_delaf::u_flexional_traits_list &possible_flexional_traits)
	{
		std::unique_ptr<u_set> flexional_traits_ref;
		unichar next_char;
		do
		{
//			std::wcout << flexional_traits_separator;
			flexional_traits_ref.reset(new u_set());
			next_char = u_read_inf_delaf_flexional_traits(f, *flexional_traits_ref);
			if (flexional_traits_ref->empty())
				fatal_error("DELAF entry %d having an empty sequence of flexional traits\n", static_cast<int>(ambiguous_entry_count));
			dico.flexional_traits.insert(flexional_traits_ref->begin(), flexional_traits_ref->end());
//			wserialize_sequence(std::wcout, flexional_traits_ref->begin(), flexional_traits_ref->end());
			possible_flexional_traits.push_back(flexional_traits_ref.release());
		} while (!feof(f) && next_char == flexional_traits_separator);
		return next_char;
	}

	unichar u_read_inf_delaf_clitic_pronouns(FILE *f, std::size_t ambiguous_entry_count, inf_delaf &dico, inf_delaf::ust_set &clitic_pronouns)
	{
		ust_string::ref clitic_pronoun;
		unichar next_char;
		do
		{
			clitic_pronoun = &dico.clitic_pronouns.epsilon();
			next_char = u_read_inf_delaf_clitic_pronoun(f, clitic_pronoun);
			if (clitic_pronoun == &dico.clitic_pronouns.epsilon())
				fatal_error("INF DELAF entry %d having an empty semantic trait\n", ambiguous_entry_count);
			clitic_pronouns.insert(clitic_pronoun);
		} while (!feof(f) && next_char == clitic_pronouns_separator);
		return next_char;
	}
} //namespace grapenlp
#endif /*GRAPENLP_INF_DELAF_READER_H*/
