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

#ifndef GRAPENLP_W_FST2_TAG_OUTPUT_READER_H
#define GRAPENLP_W_FST2_TAG_OUTPUT_READER_H

#ifdef TRACE
#include <iostream>
#endif

#include <grapenlp/unicode.h>
#include <grapenlp/weight_traits.h>
#include <grapenlp/int_w_fst2_tag_output_reader.h>
#include <grapenlp/float_w_fst2_tag_output_reader.h>

namespace grapenlp
{
	template<typename Weight, weight_subcategory = weight_traits<Weight>::subcategory>
	struct w_fst2_tag_output_reader
	{};

	template<typename Weight>
	struct w_fst2_tag_output_reader<Weight, INTEGRAL_WEIGHT>: public int_w_fst2_tag_output_reader<Weight>
	{};

	template<typename Weight>
	struct w_fst2_tag_output_reader<Weight, FLOATING_POINT_WEIGHT>: public float_w_fst2_tag_output_reader<Weight>
	{};
} //namespace grapenlp

#endif /*GRAPENLP_W_FST2_TAG_OUTPUT_READER*/
