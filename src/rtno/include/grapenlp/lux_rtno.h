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

#ifndef GRAPENLP_LUX_RTNO_H
#define GRAPENLP_LUX_RTNO_H

#include <grapenlp/u_out_bound.h>
#include <grapenlp/l_rtno.h>

namespace grapenlp
{
	//RTNO having lexical mask/unicode output bound as input/output transition tags
	template<typename InputIterator, typename ContextMask>
	struct lux_rtno
	{
		typedef typename l_rtno<InputIterator, u_out_bound::const_ref, ContextMask>::type type;
	private:
		lux_rtno(){}
	};

	//RTNO having lexical mask/unicode output bound as input/output transition tags
	template<typename InputIterator, typename ContextMask>
	struct luxns_rtno
	{
		typedef typename lns_rtno<InputIterator, u_out_bound::const_ref, ContextMask>::type type;
	private:
		luxns_rtno(){}
	};
} //namespace grapenlp

#endif /*GRAPENLP_LUX_RTNO_H*/
