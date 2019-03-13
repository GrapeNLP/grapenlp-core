/*
 * GRAPENLP
 *
 * Copyright (C) 2011-2012 Universidad de Alicante <javier.sastre@telefonica.net>
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

#ifndef GRAPENLP_LUAW_RTNO_H
#define GRAPENLP_LUAW_RTNO_H

#include <grapenlp/u_array_const_ref_x_weight.h>
#include <grapenlp/l_rtno.h>

namespace grapenlp
{
	//RTNO having lexical mask/unicode array x weight as input/output transition tags
	template<typename InputIterator, typename Weight, typename ContextMask>
	using luaw_rtno = l_rtno<InputIterator, typename u_array_const_ref_x_weight<Weight>::type, ContextMask>;

	//RTNO having lexical mask/unicode array x weight as input/output transition tags
	template<typename InputIterator, typename Weight, typename ContextMask>
	using luawns_rtno = lns_rtno<InputIterator, typename u_array_const_ref_x_weight<Weight>::type, ContextMask>;
} //namespace grapenlp

#endif /*GRAPENLP_LUAW_RTNO_H*/
