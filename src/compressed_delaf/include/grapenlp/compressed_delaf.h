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

#ifndef GRAPENLP_COMPRESSED_DELAF_H
#define GRAPENLP_COMPRESSED_DELAF_H

#include <grapenlp/bin_delaf.h>
#include <grapenlp/inf_delaf.h>

namespace grapenlp
{
	class compressed_delaf: public bin_delaf, public inf_delaf
	{
	public:
//		friend void u_read(FILE *, FILE *, compressed_delaf);

		compressed_delaf(): bin_delaf(), inf_delaf()
		{}

		template<typename UCharIterator>
		inf_delaf::const_ambiguous_entry* get_word_properties(UCharIterator word_begin, UCharIterator word_end) const
		{
			std::size_t last_state_offset(get_state_offset(word_begin, word_end));
			if (last_state_offset == std::numeric_limits<std::size_t>::max())
				return NULL;
			const bin_delaf::state& last_state(bin_delaf::offset_to_state(last_state_offset));
			if (last_state.is_final())
				return entries[last_state.get_word_properties_index()];
			return NULL;
		}

		struct word
		{
			typedef bin_delaf::const_depth_first_iterator::const_last_path_char_iterator u_const_iterator;

			u_const_iterator begin;
			u_const_iterator end;
			inf_delaf::const_ambiguous_entry &properties;

			word(u_const_iterator begin_, u_const_iterator end_, inf_delaf::const_ambiguous_entry &properties_): begin(begin_), end(end_), properties(properties_)
			{}
		};

		class const_word_iterator: protected const_depth_first_final_state_iterator
		{
			friend class compressed_delaf;
		public:
				typedef bin_delaf::const_depth_first_final_state_iterator base_type;

		protected:
			const compressed_delaf& dico;

			//End iterator constructor
			const_word_iterator(const compressed_delaf &dico_): base_type(static_cast<const bin_delaf&>(dico_)), dico(dico_)
			{}

			//Begin iterator constructor
			const_word_iterator(const compressed_delaf &dico_, const bin_delaf::state &initial_state): base_type(static_cast<const bin_delaf&>(dico_), initial_state), dico(dico_)
			{}

		public:
			//Increment iterator
			const_word_iterator& operator++()
			{ return static_cast<const_word_iterator&>(base_type::operator++ ()); }

			bool operator==(const const_word_iterator &ci) const
			{ return base_type::operator== (ci); }

			bool operator!=(const const_word_iterator &ci) const
			{ return !(*this == ci); }

			const word operator*() const
			{ return word(const_last_path_char_iterator_begin(), const_last_path_char_iterator_end(), *dico.entries[dico.offset_to_state(bs.back().first->get_target_state_offset()).get_word_properties_index()]); }
		};

		const_word_iterator const_word_begin() const
		{ return const_word_iterator(*this, get_initial_state()); }

		const_word_iterator const_word_end() const
		{ return const_word_iterator(*this); }
	};

} //namespace grapenlp

#endif /*GRAPENLP_COMPRESSED_DELAF_H*/
