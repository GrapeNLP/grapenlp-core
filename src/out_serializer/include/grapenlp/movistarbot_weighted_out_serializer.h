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

#ifndef GRAPENLP_MOVISTARBOT_WEIGHTED_OUT_SERIALIZER_H
#define GRAPENLP_MOVISTARBOT_WEIGHTED_OUT_SERIALIZER_H

#include <grapenlp/movistarbot_out_serializer.h>
#include <grapenlp/segment_map_x_weight.h>

namespace grapenlp
{
	template<typename InputIterator, typename Weight, assoc_container_impl_choice asic>
	struct movistarbot_weighted_out_serializer: public movistarbot_out_serializer<InputIterator, asic>
	{
		typedef movistarbot_out_serializer<InputIterator, asic> base_type;
		typedef typename base_type::u_token_iterator u_token_iterator;
		typedef typename base_type::u_token_segment_map u_token_segment_map;
		typedef segment_map_x_weight<u_token_iterator, unichar, Weight, asic> u_token_segment_map_x_weight;
		typedef typename set_impl_selector<asic, u_token_segment_map_x_weight>::type u_token_segment_map_x_weight_set;
		typedef typename u_token_segment_map_x_weight_set::const_iterator u_token_segment_map_x_weight_set_const_iterator;

		bool operator() (const u_token_segment_map_x_weight_set &smxws, const movistarbot_tag_dico &td, u_array &result)
		{
			//No interpretations found: return an empty result
			if (smxws.size() == 0)
				return false;
			u_token_segment_map_x_weight_set_const_iterator i(smxws.begin());
			//Do not deal with the "mms" service, just return false to proceed with the default behavior
			if (i->sm.has_key(td.mms))
			{
#ifdef TRACE
				std::wcout << L"Discard MMS requests (not treated here but by the AIML rules)" << std::endl;
#endif
				return false;
			}
			//Look for the first interpretation corresponding to a known service and serialize it
			for (; i != smxws.end(); ++i)
			{
				if (this->serialize_segment_map(i->sm, td, result))
					return true;
			}
			return false;
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_MOVISTARBOT_WEIGHTED_OUT_SERIALIZER_H*/
