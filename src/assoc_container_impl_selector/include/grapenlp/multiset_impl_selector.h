/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@univ-mlv.fr>
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

#ifndef GRAPENLP_MULTISET_IMPL_SELECTOR_H
#define GRAPENLP_MULTISET_IMPL_SELECTOR_H

#include <grapenlp/assoc_container_impl_choice.h>
#include <set>
#include <grapenlp/lrb_tree_multiset.h>
#include <grapenlp/lrb_tree_multiset_3w.h>

namespace grapenlp
{
	template<assoc_container_impl_choice, typename T, typename Compare = assoc_container_default_comparator_choice, typename Allocator = std::allocator<T> >
	struct multiset_impl_selector
	{};

	template<typename T, typename Compare, typename Allocator>
	struct multiset_impl_selector<STD, T, Compare, Allocator>
	{
		typedef std::multiset<T, Compare, Allocator> type;
	};

	template<typename T, typename Allocator>
	struct multiset_impl_selector<STD, T, assoc_container_default_comparator_choice, Allocator>
	{
		typedef std::multiset<T, std::less<T>, Allocator> type;
	};

	template<typename T, typename Compare, typename Allocator>
	struct multiset_impl_selector<LRB_TREE, T, Compare, Allocator>
	{
		typedef lrb_tree_multiset<T, Compare, Allocator> type;
	};

	template<typename T, typename Allocator>
	struct multiset_impl_selector<LRB_TREE, T, assoc_container_default_comparator_choice, Allocator>
	{
		typedef lrb_tree_multiset<T, std::less<T>, Allocator> type;
	};

	template<typename T, typename Compare, typename Allocator>
	struct multiset_impl_selector<LRB_TREE_3W, T, Compare, Allocator>
	{
		typedef lrb_tree_multiset_3w<T, Compare, Allocator> type;
	};

	template<typename T, typename Allocator>
	struct multiset_impl_selector<LRB_TREE_3W, T, assoc_container_default_comparator_choice, Allocator>
	{
		typedef lrb_tree_multiset_3w<T, compare_3w<T>, Allocator> type;
	};

	template<typename T, typename Compare, typename Allocator>
	std::pair<typename std::multiset<T, Compare, Allocator>::iterator, bool> insert_and_report(std::multiset<T, Compare, Allocator> &s, typename std::multiset<T, Compare, Allocator>::iterator hint_it, const T& elem)
	{
		typedef std::multiset<T, Compare, Allocator> multiset_type;
		typename multiset_type::size_type old_elem_count(s.size());
		typename multiset_type::iterator it(s.insert(hint_it, elem));
		return std::make_pair(it, old_elem_count != s.size());
	}

	template<typename T, typename Compare, typename Allocator>
	std::pair<typename lrb_tree_multiset<T, Compare, Allocator>::iterator, bool> insert_and_report(lrb_tree_multiset<T, Compare, Allocator> &s, typename lrb_tree_multiset<T, Compare, Allocator>::iterator hint_it, const T& elem)
	{ return s.insert_and_report(hint_it, elem); }

	template<typename T, typename Compare, typename Allocator>
	std::pair<typename lrb_tree_multiset_3w<T, Compare, Allocator>::iterator, bool> insert_and_report(lrb_tree_multiset_3w<T, Compare, Allocator> &s, typename lrb_tree_multiset_3w<T, Compare, Allocator>::iterator hint_it, const T& elem)
	{ return s.insert_and_report(hint_it, elem); }

	//Normal erase since there is no unbalanced erase with std::multiset
	template<typename T, typename Compare, typename Allocator>
	void unbalanced_erase(std::multiset<T, Compare, Allocator> &s, typename std::multiset<T, Compare, Allocator>::iterator it)
	{ s.erase(it); }

	template<typename T, typename Compare, typename Allocator>
	void unbalanced_erase(lrb_tree_multiset<T, Compare, Allocator> &s, typename lrb_tree_multiset<T, Compare, Allocator>::iterator it)
	{ return s.unbalanced_erase(it); }

	template<typename T, typename Compare, typename Allocator>
	void unbalanced_erase(lrb_tree_multiset_3w<T, Compare, Allocator> &s, typename lrb_tree_multiset_3w<T, Compare, Allocator>::iterator it)
	{ return s.unbalanced_erase(it); }

	template<typename T, typename Compare, typename Allocator>
	T& front(std::multiset<T, Compare, Allocator> &s)
	{ return s.front(); }

	template<typename T, typename Compare, typename Allocator>
	T& front(const std::multiset<T, Compare, Allocator> &s)
	{ return *(s.begin()); }

	template<typename T, typename Compare, typename Allocator>
	T& front(lrb_tree_multiset<T, Compare, Allocator> &s)
	{ return s.front(); }

	template<typename T, typename Compare, typename Allocator>
	T& front(const lrb_tree_multiset<T, Compare, Allocator> &s)
	{ return s.front(); }

	template<typename T, typename Compare, typename Allocator>
	T& front(lrb_tree_multiset_3w<T, Compare, Allocator> &s)
	{ return s.front(); }

	template<typename T, typename Compare, typename Allocator>
	T& front(const lrb_tree_multiset_3w<T, Compare, Allocator> &s)
	{ return s.front(); }

	template<typename T, typename Compare, typename Allocator>
	T& back(std::multiset<T, Compare, Allocator> &s)
	{ return *s.rbegin(); }

	template<typename T, typename Compare, typename Allocator>
	T& back(const std::multiset<T, Compare, Allocator> &s)
	{ return *s.rbegin(); }

	template<typename T, typename Compare, typename Allocator>
	T& back(lrb_tree_multiset<T, Compare, Allocator> &s)
	{ return s.back(); }

	template<typename T, typename Compare, typename Allocator>
	T& back(const lrb_tree_multiset<T, Compare, Allocator> &s)
	{ return s.back(); }

	template<typename T, typename Compare, typename Allocator>
	T& back(lrb_tree_multiset_3w<T, Compare, Allocator> &s)
	{ return s.back(); }

	template<typename T, typename Compare, typename Allocator>
	T& back(const lrb_tree_multiset_3w<T, Compare, Allocator> &s)
	{ return s.back(); }
} //namespace grapenlp

#endif /*GRAPENLP_MULTISET_IMPL_SELECTOR_H*/
