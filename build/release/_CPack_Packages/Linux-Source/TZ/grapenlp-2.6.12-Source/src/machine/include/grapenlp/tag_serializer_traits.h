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

#ifndef GRAPENLP_TAG_SERIALIZER_TRAITS_H
#define GRAPENLP_TAG_SERIALIZER_TRAITS_H

#include <string>
#include <grapenlp/iostream.h>

namespace grapenlp
{
	template<typename Tag>
	struct tag_serializer
	{
		typedef Tag tag;
		typedef serializer<tag> type;
	};

	template<typename NoConstRefTag>
	struct tag_serializer<const NoConstRefTag*>
	{
		typedef const NoConstRefTag* tag;
		typedef const_deref_serializer<NoConstRefTag> type;
	};

	template<typename NoRefTag>
	struct tag_serializer<NoRefTag*>
	{
		typedef NoRefTag* tag;
		typedef deref_serializer<NoRefTag> type;
	};
} //namespace grapenlp

#endif /*GRAPENLP_TAG_SERIALIZER_TRAITS_H*/
