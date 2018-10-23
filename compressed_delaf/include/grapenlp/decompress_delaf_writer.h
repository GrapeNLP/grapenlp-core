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

#ifndef GRAPENLP_U_DECOMPRESS_DELAF_WRITER_H
#define GRAPENLP_U_DECOMPRESS_DELAF_WRITER_H

#include <grapenlp/error.h>
#include <grapenlp/compressed_delaf.h>

namespace grapenlp
{
	/*
	 * Method declarations
	 */

	void u_decompress_delaf_write(FILE *f, const compressed_delaf &dico);
	void u_decompress_delaf_write(FILE *f, const compressed_delaf::word &w);
	void u_decompress_delaf_write(FILE *f, compressed_delaf::word::u_const_iterator word_begin, compressed_delaf::word::u_const_iterator word_end, inf_delaf::entry &ae);
	template<typename CanonicalFormUCharIterator>
	void u_decompress_delaf_write_canonical_form(FILE *f, compressed_delaf::word::u_const_iterator word_begin, compressed_delaf::word::u_const_iterator word_end, unsigned char inflected_form_suffix_length, CanonicalFormUCharIterator canonical_form_suffix_begin, CanonicalFormUCharIterator canonical_form_suffix_end);

	/*
	 * Method implementations
	 */

	void u_decompress_delaf_write(FILE *f, const compressed_delaf &dico)
	{
		compressed_delaf::const_word_iterator word_begin(dico.const_word_begin());
		compressed_delaf::const_word_iterator word_end(dico.const_word_end());

		for (; word_begin != word_end; ++word_begin)
			u_decompress_delaf_write(f, *word_begin);
	}

	void u_decompress_delaf_write(FILE *f, const compressed_delaf::word &w)
	{
		inf_delaf::ambiguous_entry::const_iterator i(w.properties.begin());
		for (; i != w.properties.end(); ++i)
		{
			u_decompress_delaf_write(f, w.begin, w.end, **i);
			u_fputc('\n', f);
		}
	}

//The generic u_write function seems not to work for ptr_list<set<unichar> >
//So we implement here a specific u_write function for this case
	void u_decompress_delaf_write(FILE *f, const inf_delaf::u_flexional_traits_list &u_possible_flexional_traits)
	{
		inf_delaf::u_flexional_traits_list::const_iterator i(u_possible_flexional_traits.begin());
		if (i == u_possible_flexional_traits.end())
			return;
		u_write(f, (*i)->begin(), (*i)->end());
		++i;

		for (; i != u_possible_flexional_traits.end(); ++i)
		{
			u_fputc(flexional_traits_separator, f);
			u_write(f, (*i)->begin(), (*i)->end());
		}
	}

	void u_decompress_delaf_write(FILE *f, const compressed_delaf::word::u_const_iterator word_begin, compressed_delaf::word::u_const_iterator word_end, inf_delaf::entry &e)
	{
		//Write inflected form
		u_write<compressed_delaf::word::u_const_iterator>(f, word_begin, word_end);
		u_fputc(lemma_separator, f);
		//Write canonical form, if the inflected form is not already the canonical form
		if (!e.is_canonical_form())
			u_decompress_delaf_write_canonical_form(f, word_begin, word_end, e.inflected_form_suffix_length, e.canonical_form_suffix.begin(), e.canonical_form_suffix.end());
		u_fputc(canonical_form_separator, f);
		//Write Part-Of-Speech
		u_write(f, e.pos.begin(), e.pos.end());
		//Write semantic traits, if present
		if (!e.semantic_traits.empty())
		{
			u_fputc(semantic_traits_separator, f);
			u_ptr_write(f, e.semantic_traits.begin(), e.semantic_traits.end(), semantic_traits_separator);
		}
		//Write flexional traits, if present
		if (!e.possible_flexional_traits.empty())
		{
			u_fputc(flexional_traits_separator, f);
//The generic u_write function seems not to work for ptr_list<set<unichar> >
//			u_ptr_write(f, e.possible_flexional_traits.begin(), e.possible_flexional_traits.end(), flexional_traits_separator);
			u_decompress_delaf_write(f, e.possible_flexional_traits);
			//Write clitic pronouns, if present
			if (!e.clitic_pronouns.empty())
			{
				u_fputc(clitic_pronouns_separator, f);
				u_ptr_write(f, e.clitic_pronouns.begin(), e.clitic_pronouns.end(), clitic_pronouns_separator);
			}
		}
	}

	template<typename CanonicalFormUCharIterator>
	void u_decompress_delaf_write_canonical_form(FILE *f, compressed_delaf::word::u_const_iterator word_begin, compressed_delaf::word::u_const_iterator word_end, unsigned char inflected_form_suffix_length, CanonicalFormUCharIterator canonical_form_suffix_begin, CanonicalFormUCharIterator canonical_form_suffix_end)
	{
		//Skip inflected form suffix
		for (; inflected_form_suffix_length > 0; --inflected_form_suffix_length)
			--word_end;
		//Write word steam
		u_write(f, word_begin, word_end);
		//Write canonical form suffix
		u_write<CanonicalFormUCharIterator>(f, canonical_form_suffix_begin, canonical_form_suffix_end);
	}
} //namespace grapenlp

#endif /*GRAPENLP_U_DELAF_WRITER_H*/
