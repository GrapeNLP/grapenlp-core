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

#ifndef GRAPENLP_LUXW_RTNO_H
#define GRAPENLP_LUXW_RTNO_H

#include <grapenlp/u_out_bound_const_ref_x_weight.h>
#include <grapenlp/lxw_rtno.h>

namespace grapenlp
{
	//RTNO having lexical mask/unicode output bound x weight as input/output transition tags
	template<typename InputIterator, typename Weight, typename ContextKey, typename ContextValue>
	struct luxw_rtno
	{
		typedef typename lxw_rtno<InputIterator, unichar, Weight, ContextKey, ContextValue>::type type;
	private:
		luxw_rtno(){}
	};

	//RTNO having lexical mask/unicode output bound x weight as input/output transition tags
	template<typename InputIterator, typename Weight, typename ContextKey, typename ContextValue>
	struct luxwns_rtno
	{
		typedef typename lxwns_rtno<InputIterator, unichar, Weight, ContextKey, ContextValue>::type type;
	private:
		luxwns_rtno(){}
	};
} //namespace grapenlp

#endif /*GRAPENLP_LUXW_RTNO_H*/
