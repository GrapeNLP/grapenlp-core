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

#ifndef GRAPENLP_U_SET_TRIE_READER_H
#define GRAPENLP_U_SET_TRIE_READER_H

#include <grapenlp/u_set_trie.h>
#include <grapenlp/algorithm.h>

namespace grapenlp
{
	//u_set_trie string readers
	unichar u_read(FILE *f, ust_string::ref &s_ref, unichar end_mark);

	template<typename Iterator, typename Normalizer>
	unichar u_read(FILE *f, ust_string::ref &s_ref, unichar end_mark, Normalizer normalizer)
	{
		unichar next_char(u_fgetc(f));
		while (!feof(f) && next_char != end_mark)
		{
			s_ref = &((*s_ref) + normalizer(next_char));
			next_char = u_fgetc(f);
		}
		s_ref->data = true;
		return next_char;
	}

	template<typename Iterator>
	unichar u_read(FILE *f, ust_string::ref &s_ref, Iterator end_mark_begin, Iterator end_mark_end)
	{
		unichar next_char(u_fgetc(f));
		while (!feof(f) && !includes(end_mark_begin, end_mark_end, next_char))
		{
			s_ref = &((*s_ref) + next_char);
			next_char = u_fgetc(f);
		}
		s_ref->data = true;
		return next_char;
	}

	template<typename Iterator, typename Normalizer>
	unichar u_read(FILE *f, ust_string::ref &s_ref, Iterator end_mark_begin, Iterator end_mark_end, Normalizer normalizer)
	{
		unichar next_char(u_fgetc(f));
		while (!feof(f) && !includes(end_mark_begin, end_mark_end, next_char))
		{
			s_ref = &((*s_ref) + normalizer(next_char));
			next_char = u_fgetc(f);
		}
		s_ref->data = true;
		return next_char;
	}
} //namespace grapenlp

#endif /*GRAPENLP_U_SET_TRIE_READER_H*/
