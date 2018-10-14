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

#ifndef GRAPE_LTW_RTNO_H
#define GRAPE_LTW_RTNO_H

#include <grape/l_rtno.h>
#include <grape/trie_string_const_ref_x_weight.h>

namespace grape
{
	//RTNO having lexical mask/trie string const ref x weight as input/output transition tags
	template<typename InputIterator, typename Id, typename Weight>
	struct ltw_rtno
	{
		typedef typename l_rtno<InputIterator, trie_string_const_ref_x_weight<Id, Weight> >::type type;
	private:
		ltw_rtno(){}
	};

	//RTNO having lexical mask/trie string const ref x weight as input/output transition tags
	template<typename InputIterator, typename Id, typename Weight>
	struct ltwns_rtno
	{
		typedef typename lns_rtno<InputIterator, trie_string_const_ref_x_weight<Id, Weight> >::type type;
	private:
		ltwns_rtno(){}
	};
} //namespace grape

#endif /*GRAPE_LTW_RTNO_H*/
