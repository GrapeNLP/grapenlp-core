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

#ifndef GRAPENLP_L_RTNO_H
#define GRAPENLP_L_RTNO_H

#include <grapenlp/rtno.h>
#include <grapenlp/lexmask.h>

namespace grapenlp
{
	/**
	 * Recursive transition network with output (RTNO) having lexical masks as input tags
	 * @tparam InputIterator the type of the iterator over the RTNO input (e.g. an unichar array iterator)
	 * @tparam TagOutput the type of the RTNO output tags
	 */
	template<typename InputIterator, typename TagOutput, typename ContextMask>
	using l_rtno = rtno<typename lexmask<InputIterator>::const_ref, TagOutput, ContextMask>;

	/**
	 * Partial instantiation of the recursive transition network with output and numbered states for lexical mask input
	 * tags. This struct is not to be instantiated but it just serves for encapsulating the generic data type.
	 * @tparam InputIterator the type of the iterator over the RTNO input (e.g. an unichar array iterator)
	 * @tparam TagOutput the type of the RTNO output tags
	 */
	template<typename InputIterator, typename TagOutput, typename ContextMask>
	using lns_rtno = ns_rtno<typename lexmask<InputIterator>::const_ref, TagOutput, ContextMask>;
} //namespace grapenlp

#endif /*GRAPENLP_L_RTNO_H*/
