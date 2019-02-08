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

#ifndef GRAPENLP_POOL_H
#define GRAPENLP_POOL_H

#include <grapenlp/functional.h>
#include <grapenlp/array.h>
#include <grapenlp/trie.h>
#ifdef TRACE
#include <grapenlp/iostream.h>
#endif

namespace grapenlp
{
	template<typename Pool>
	struct pool_traits
	{
		typedef Pool pool;
		typedef typename pool::char_type char_type;
		typedef typename pool::base_type base_type;
		typedef typename pool::value_type value_type;
		typedef typename pool::const_value_type const_value_type;
		typedef typename pool::concatenator concatenator;
		typedef typename pool::converse_concatenator converse_concatenator;
		typedef typename pool::concatenator2 concatenator2;
		typedef typename pool::iterator iterator;
		typedef typename pool::const_iterator const_iterator;
		typedef typename pool::less less;
		typedef typename pool::compare_3w compare_3w;
	};

	template<typename RefPool>
	struct ref_pool_traits
	{
		typedef RefPool ref_pool;
		typedef typename ref_pool::char_type char_type;
		typedef typename ref_pool::base_type base_type;
		typedef typename ref_pool::value_type value_type;
		typedef typename ref_pool::const_value_type const_value_type;
		typedef typename ref_pool::concatenator concatenator;
		typedef typename ref_pool::converse_concatenator converse_concatenator;
		typedef typename ref_pool::concatenator2 concatenator2;
		typedef typename ref_pool::iterator iterator;
		typedef typename ref_pool::const_iterator const_iterator;
		typedef typename ref_pool::less less;
		typedef typename ref_pool::compare_3w compare_3w;
		typedef typename ref_pool::deref deref;
		typedef typename ref_pool::ptr ptr;
	};

	template<typename T>
	struct array_fake_pool
	{
		typedef T char_type;
		typedef array<T> base_type;
		typedef array<T> value_type;
		typedef const array<T> const_value_type;
		typedef typename value_type::iterator iterator;
		typedef typename value_type::const_iterator const_iterator;
		typedef array_and_deref_sequence_concatenator<T, array<T> > concatenator;
		typedef array_and_deref_sequence_converse_concatenator<T, array<T> > converse_concatenator;
		typedef array_and_array_concatenator<T> concatenator2;
		typedef std::less<value_type> less;
		typedef grapenlp::compare_3w<value_type, true> compare_3w;

		value_type empty()
		{ return value_type(); }
	};

	template<typename T>
	struct array_fake_ref_pool
	{
		typedef T char_type;
		typedef array<T> base_type;
		typedef array<T> value_type;
		typedef const array<T> const_value_type;
		typedef typename value_type::iterator iterator;
		typedef typename value_type::const_iterator const_iterator;
		typedef array_and_deref_sequence_concatenator<T, array<T> > concatenator;
		typedef array_and_deref_sequence_converse_concatenator<T, array<T> > converse_concatenator;
		typedef array_and_array_concatenator<T> concatenator2;
		typedef std::less<value_type> less;
		typedef grapenlp::compare_3w<value_type, true> compare_3w;
		typedef identity<value_type> deref;
		typedef identity<value_type> ptr;


		value_type empty()
		{ return value_type(); }
	};

	template<typename T>
	struct trie_string_pool
	{
		typedef T char_type;
		typedef typename trie<T>::string base_type;
		typedef base_type& value_type;
		typedef base_type const & const_value_type;
		typedef typename base_type::iterator iterator;
		typedef typename base_type::const_iterator const_iterator;
		typedef trie_string_and_deref_sequence_concatenator<T, array<T> > concatenator;
		//The reverse of the sequence to append is inserted at the end of the trie string instead of
		//at the beginning: the latter would be rather inefficient, while the former would keep
		//efficiency but will result in a suffix tree instead of a prefix tree, which is in fact
		//more convenient for reconstructing the string since the pointer towards the trie node
		//representing the string will correspond to the beginning of the sequence instead of the end
		typedef trie_string_and_deref_reverse_sequence_concatenator<T, array<T> > converse_concatenator;
		typedef trie_string_and_trie_string_concatenator<T> concatenator2;
		typedef ref_less<base_type> less;
		typedef grapenlp::ref_compare_3w<base_type> compare_3w;

		trie<T> the_pool;

		value_type empty()
		{ return the_pool.epsilon(); }
	};

	template<typename T>
	struct trie_string_ref_pool
	{
		typedef T char_type;
		typedef typename trie<T>::string base_type;
		typedef base_type* value_type;
		typedef const base_type* const_value_type;
		typedef typename base_type::iterator iterator;
		typedef typename base_type::const_iterator const_iterator;
		typedef deref_trie_string_and_deref_sequence_concatenator<T, array<T> > concatenator;
		//The reverse of the sequence to append is inserted at the end of the trie string instead of
		//at the beginning: the latter would be rather inefficient, while the former would keep
		//efficiency but will result in a suffix tree instead of a prefix tree, which is in fact
		//more convenient for reconstructing the string since the pointer towards the trie node
		//representing the string will correspond to the beginning of the sequence instead of the end
		typedef deref_trie_string_and_deref_reverse_sequence_concatenator<T, array<T> > converse_concatenator;
		typedef deref_trie_string_and_deref_trie_string_concatenator<T> concatenator2;
		typedef std::less<value_type> less;
		typedef typename grapenlp::compare_3w<value_type> compare_3w;
		typedef grapenlp::deref<base_type> deref;
		typedef grapenlp::ref<base_type> ptr;

		trie<T> the_pool;

		value_type empty()
		{ return &the_pool.epsilon(); }
	};
} //namespace grapenlp

#endif /*GRAPENLP_POOL_H*/
