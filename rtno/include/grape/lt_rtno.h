/*
 * GRAPE
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

#ifndef GRAPE_LT_RTNO_H
#define GRAPE_LT_RTNO_H

#include <grape/l_rtno.h>

namespace grape
{
	//RTNO having lexical mask/trie string ref as input/output transition tags
	template<typename InputIterator, typename Id>
	struct lt_rtno
	{
		typedef typename l_rtno<InputIterator, typename trie<Id>::string::const_ref>::type type;
	private:
		lt_rtno(){}
	};

	//RTNO having lexical mask/trie string ref as input/output transition tags
	template<typename InputIterator, typename Id>
	struct ltns_rtno
	{
		typedef typename lns_rtno<InputIterator, typename trie<Id>::string::const_ref>::type type;
	private:
		ltns_rtno(){}
	};
} //namespace grape

#endif /*GRAPE_LT_RTNO_H*/
