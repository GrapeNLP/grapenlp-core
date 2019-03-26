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

#ifndef GRAPENLP_UA_FST2_TAG_OUTPUT_READER_H
#define GRAPENLP_UA_FST2_TAG_OUTPUT_READER_H

#include <array>

#include <grapenlp/u_array.h>
#include <grapenlp/trie_with_ptr_data.h>

namespace grapenlp
{
	template<typename StopCharEvaluator>
	struct ua_fst2_tag_output_reader
	{
		typedef const u_array* tag;
		//Type for the pool of tag outputs
		typedef trie_with_ptr_data<unichar, u_array> ua_trie;
		//Type for the index of tag output pools
		typedef ua_trie::string ua_string;
		typedef ua_string::ref ua_string_ref;

		StopCharEvaluator is_stop_char;
		ua_trie &uat;

		ua_fst2_tag_output_reader(StopCharEvaluator is_stop_char_, ua_trie &uat_): is_stop_char(is_stop_char_), uat(uat_)
		{}

		//Retrieve output unicode array pointer
		tag operator() (FILE *f, unichar &c, unsigned int &line_count) const
		{
			if (is_stop_char(c))
				fatal_error("In line %u of .fst2 file: explicit empty output\n", line_count);
			ua_string_ref uas = &uat.epsilon();
			do
			{
				uas = &(*uas + c);
#ifdef TRACE
				std::wcout << c;
#endif
			}
			while (!is_stop_char(c = (unichar)u_fgetc(f)));
			if (!uas->data)
			{
				uas->data = new u_array(uas->size());
				uas->to_array(*uas->data);
			}
			return uas->data;
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_UA_FST2_TAG_OUTPUT_READER*/
