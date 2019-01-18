/*
 * GRAPENLP
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

#ifndef GRAPENLP_X_FPRTN_H
#define GRAPENLP_X_FPRTN_H

#include <grapenlp/out_bound.h>
#include <grapenlp/fprtn.h>

namespace grapenlp
{
	template<typename SourceRef, typename Id>
	struct x_fprtn
	{
		typedef fprtn<SourceRef, typename out_bound<Id>::const_ref> type;
	};
} //namespace grapenlp

#endif /*GRAPENLP_X_FPRTN_H*/
