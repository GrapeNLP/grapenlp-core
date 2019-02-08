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

#ifndef GRAPENLP_UAW_FPRTN_H
#define GRAPENLP_UAW_FPRTN_H

#include <grapenlp/u_array_const_ref_x_weight.h>
#include <grapenlp/aw_fprtn.h>

namespace grapenlp
{
	template<typename SourceRef, typename Weight>
	struct uaw_fprtn
	{
		typedef typename aw_fprtn<SourceRef, unichar, Weight>::type type;
	};
} //namespace grapenlp

#endif /*GRAPENLP_UAW_FPRTN_H*/
