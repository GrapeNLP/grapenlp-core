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

#ifndef GRAPENLP_U_DELAF_WRITER_H
#define GRAPENLP_U_DELAF_WRITER_H

#include <grapenlp/error.h>
#include <grapenlp/u_text_delaf.h>

namespace grapenlp
{
	template<typename CaseNormalizer>
	void u_write(FILE *f, const u_text_delaf<CaseNormalizer> &dico);

	template<typename CaseNormalizer>
	void u_write(FILE *f, const typename u_text_delaf<CaseNormalizer>::u_entry_list &udel);

	template<typename CaseNormalizer>
	void u_write(FILE *f, const typename u_text_delaf<CaseNormalizer>::u_entry &ude);

	template<typename CaseNormalizer>
	void u_write(FILE *f, const u_text_delaf<CaseNormalizer> &dico)
	{
		typename u_text_delaf<CaseNormalizer>::u_lemma_trie_with_entry_data::const_iterator i(dico.lemma_to_entry_index.begin());

		//While there are lemma trie nodes to process
		while (i != dico.lemma_to_entry_index.end())
		{
			//If this node represents a complete word, write it
			//Otherwise, just skip it
			if (i->data)
				u_write<CaseNormalizer>(f, *i->data);
			//Go for the next trie node
			++i;
		}
	}

//The generic u_write function seems not to work for ptr_list<set<unichar> >
//So we implement here a specific u_write function for this case
	template<typename CaseNormalizer>
	void u_write(FILE *f, const typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list &u_possible_flexional_traits)
	{
		typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list::const_iterator i(u_possible_flexional_traits.begin());
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

	template<typename CaseNormalizer>
	void u_write(FILE *f, const typename u_text_delaf<CaseNormalizer>::u_entry_list &udel)
	{
		typename u_text_delaf<CaseNormalizer>::u_entry_list::const_iterator i(udel.begin());
		for (; i != udel.end(); ++i)
		{
			u_write<CaseNormalizer>(f, **i);
			u_fputc('\n', f);
		}
	}

	template<typename CaseNormalizer>
	void u_write(FILE *f, const typename u_text_delaf<CaseNormalizer>::u_entry &ude)
	{
		u_write(f, ude.lemma.begin(), ude.lemma.end());
		u_fputc(lemma_separator, f);
		if (ude.lemma != ude.canonical_form)
			u_write(f, ude.canonical_form.begin(), ude.canonical_form.end());
		u_fputc(canonical_form_separator, f);
		u_write(f, ude.pos.begin(), ude.pos.end());
		if (!ude.semantic_traits.empty())
		{
			u_fputc(semantic_traits_separator, f);
			u_ptr_write(f, ude.semantic_traits.begin(), ude.semantic_traits.end(), semantic_traits_separator);
		}
		if (!ude.possible_flexional_traits.empty())
		{
			u_fputc(flexional_traits_separator, f);
//The generic u_write function seems not to work for ptr_list<set<unichar> >
//			u_ptr_write(f, ude.possible_flexional_traits->begin(), ude.possible_flexional_traits->end(), flexional_traits_separator);
			u_write<CaseNormalizer>(f, ude.possible_flexional_traits);
			if (!ude.clitic_pronouns.empty())
			{
				u_fputc(clitic_pronouns_separator, f);
				u_ptr_write(f, ude.clitic_pronouns.begin(), ude.clitic_pronouns.end(), clitic_pronouns_separator);
			}
		}
	}
} //namespace grapenlp

#endif /*GRAPENLP_U_DELAF_WRITER_H*/
