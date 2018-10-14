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

#ifndef GRAPE_LEXMASK_DEFAULT_WEIGHT_H
#define GRAPE_LEXMASK_DEFAULT_WEIGHT_H

#include <grape/error.h>
#include <grape/lexmask.h>
#include <grape/delaf_entry_filter_default_weight.h>

namespace grape
{

	/*
 	 * This is the list of lexical mask types, ordered following the enumeration
 	 *
 	 * TOKEN_META_LEXMASK
 	 * DIGIT_META_LEXMASK
 	 * NO_DIGIT_META_LEXMASK,
 	 * WORD_META_LEXMASK,
 	 * NO_WORD_META_LEXMASK,
 	 * UPPER_WORD_META_LEXMASK,
 	 * NO_UPPER_WORD_META_LEXMASK,
 	 * LOWER_WORD_META_LEXMASK,
 	 * NO_LOWER_WORD_META_LEXMASK,
 	 * FIRST_UPPER_WORD_META_LEXMASK,
 	 * NO_FIRST_UPPER_WORD_META_LEXMASK,
 	 * CONSTRAINED_DICO_WORD_META_LEXMASK,
 	 * CONSTRAINED_COMPRESSED_DICO_WORD_META_LEXMASK,
 	 * SYMBOL_LEXMASK,
 	 * CASE_SENSITIVE_WORD_LEXMASK,
 	 * CASE_INSENSITIVE_WORD_LEXMASK
	 *
	 * This is the list of lexical mask types, ordered from the less restrictive to the most one:
	 *
	 * TOKEN_META_LEXMASK (whatever, the less restrictive, infinite possibilities)
	 * NO_DIGIT_META_LEXMASK (lowercase words + uppercase-words + first-uppercase words + non-upper-lower-first-upper words + puntuation symbols, infinite possibilities)
	 * WORD_META_LEXMASK (lowercase words + uppercase-words + first-uppercase words + other non-uppercase words, infinite possibilities)
 	 * NO_FIRST_UPPER_WORD_META_LEXMASK (lowercase words + uppercase words + other non-first-upper words + puctuation symbols + digits, infinite possibilities)
 	 * NO_UPPER_WORD_META_LEXMASK (lowercase words + first-uppercase words + other non-uppercase words + puntuation symbols + digits, infinite possibilities)
 	 * NO_LOWER_WORD_META_LEXMASK (uppercase words + first-uppercase words + other non-lowercase words + puntuation symbols + digits, infinite possibilities)
 	 * LOWER_WORD_META_LEXMASK (any lowercase word, infinite possibilities)
 	 * UPPER_WORD_META_LEXMASK (any uppercase word, infinite possibilities)
 	 * FIRST_UPPER_WORD_META_LEXMASK (any first-upper word, infinite possibilities)
 	 * CONSTRAINED_DICO_WORD_META_LEXMASK (depends on the dico word filter, from 0 to infinite possibilities)
 	 * CONSTRAINED_COMPRESSED_DICO_WORD_META_LEXMASK (depends on the dico word filter, from 0 to infinite possibilities)
	 * NO_WORD_META_LEXMASK (any symbol: punctuation symbols + digits)
	 * DIGIT_META_LEXMASK (any digit, 10 possibilities)
 	 * CASE_INSENSITIVE_WORD_LEXMASK (the specified word, not taking into account the case variations, us much possibilities as case variations)
 	 * SYMBOL_LEXMASK (the specified symbol, 1 possibility)
 	 * CASE_SENSITIVE_WORD_LEXMASK (the specified word, 1 possibility)
 	 */

	template<typename InputIterator, typename Weight>
	struct lexmask_default_weight
	{
		Weight operator() (const lexmask<InputIterator> &l) const
		{
			switch (l.get_type())
			{
				case TOKEN_META_LEXMASK: return 0;
				case NO_DIGIT_META_LEXMASK: return 1;
				case WORD_META_LEXMASK: return 2;
				case NO_FIRST_UPPER_WORD_META_LEXMASK: return 3;
				case NO_UPPER_WORD_META_LEXMASK: return 4;
				case NO_LOWER_WORD_META_LEXMASK: return 5;
				case LOWER_WORD_META_LEXMASK: return 6;
				case UPPER_WORD_META_LEXMASK: return 7;
				case FIRST_UPPER_WORD_META_LEXMASK: return 8;
/*				case CONSTRAINED_DICO_WORD_META_LEXMASK: return delaf_entry_filter_default_weight(dynamic_cast<const constrained_dico_word_meta_mask<InputIterator, CaseNormalizer> &>(l).get_filter()) + 9;
				case CONSTRAINED_COMPRESSED_DICO_WORD_META_LEXMASK: return compressed_delaf_entry_filter_default_weight(dynamic_cast<const constrained_compressed_dico_word_meta_mask<InputIterator, CaseNormalizer> &>(l).get_filter()) + 9;
				case NO_WORD_META_LEXMASK: return 10 + delaf_entry_filter_default_weight<Weight>.max();
				case DIGIT_META_LEXMASK: return 11 + delaf_entry_filter_default_weight<Weight>.max();
				case CASE_SENSITIVE_META_LEXMASK: return 12 + delaf_entry_filter_default_weight<Weight>.max();
				case SYMBOL_LEXMASK: 13 + delaf_entry_filter_default_weight<Weight>.max();
				case CASE_INSENSITIVE_META_LEXMASK: return 14 + delaf_entry_filter_default_weight<Weight>.max();
*/
				case CONSTRAINED_DICO_WORD_META_LEXMASK: return 9;
				case CONSTRAINED_COMPRESSED_DICO_WORD_META_LEXMASK: return 9;
				case NO_WORD_META_LEXMASK: return 10;
				case DIGIT_META_LEXMASK: return 11;
				case CASE_SENSITIVE_WORD_LEXMASK: return 12;
				case SYMBOL_LEXMASK: return 13;
				case CASE_INSENSITIVE_WORD_LEXMASK: return 14;

				default: fatal_error("Unknown lexmask type: %d\n", l.get_type());
			}
			//Flow control should not arrive here!!
			//This return has the solely purpose of avoiding a warning
			return -1;
		}
	};
} //namespace grape

#endif /*GRAPE_LEXMASK_DEFAULT_WEIGHT_H*/
