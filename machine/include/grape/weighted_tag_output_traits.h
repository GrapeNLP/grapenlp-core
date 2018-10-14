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

#ifndef GRAPE_WEIGHTED_TAG_OUTPUT_TRAITS_H
#define GRAPE_WEIGHTED_TAG_OUTPUT_TRAITS_H

namespace grape
{
	template<typename WeightedTagOutput>
	struct weighted_tag_output_traits
	{
		typedef WeightedTagOutput weighted_tag_output;
		typedef typename weighted_tag_output::weight weight;
		typedef typename weighted_tag_output::weight_getter weight_getter;
		typedef typename weighted_tag_output::non_weight non_weight;
		typedef typename weighted_tag_output::non_weight_getter non_weight_getter;
	};
} //namespace grape

#endif /*GRAPE_WEIGHTED_TAG_OUTPUT_TRAITS_H*/
