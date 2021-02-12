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
 * Lesser General Public License for more detailm.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

/*
 *  @author Javier Sastre
 */

#ifndef GRAPENLP_MAP_IMPL_SELECTOR_H
#define GRAPENLP_MAP_IMPL_SELECTOR_H

#include <grapenlp/assoc_container_impl_choice.h>
#include <map>
#include <grapenlp/lrb_tree_map.h>
#include <grapenlp/lrb_tree_map_3w.h>

namespace grapenlp
{
	template<assoc_container_impl_choice, typename Key, typename T, typename Compare = assoc_container_default_comparator_choice, typename Allocator = std::allocator<std::pair<const Key, T> > >
	struct map_impl_selector
	{};

	template<typename Key, typename T, typename Compare, typename Allocator>
	struct map_impl_selector<STD, Key, T, Compare, Allocator>
	{
		typedef std::map<Key, T, Compare, Allocator> type;
	};

	template<typename Key, typename T, typename Allocator>
	struct map_impl_selector<STD, Key, T, assoc_container_default_comparator_choice, Allocator>
	{
		typedef std::map<Key, T, std::less<Key>, Allocator> type;
	};

	template<typename Key, typename T, typename Compare, typename Allocator>
	struct map_impl_selector<LRB_TREE, Key, T, Compare, Allocator>
	{
		typedef lrb_tree_map<Key, T, Compare, Allocator> type;
	};

	template<typename Key, typename T, typename Allocator>
	struct map_impl_selector<LRB_TREE, Key, T, assoc_container_default_comparator_choice, Allocator>
	{
		typedef lrb_tree_map<Key, T, std::less<Key>, Allocator> type;
	};

	template<typename Key, typename T, typename Compare, typename Allocator>
	struct map_impl_selector<LRB_TREE_3W, Key, T, Compare, Allocator>
	{
		typedef lrb_tree_map_3w<Key, T, Compare, Allocator> type;
	};

	template<typename Key, typename T, typename Allocator>
	struct map_impl_selector<LRB_TREE_3W, Key, T, assoc_container_default_comparator_choice, Allocator>
	{
		typedef lrb_tree_map_3w<Key, T, compare_3w<Key>, Allocator> type;
	};

	template<typename Key, typename T, typename Compare, typename Allocator>
	std::pair<typename std::map<Key, T, Compare, Allocator>::iterator, bool> insert_with_default_mapped_value(std::map<Key, T, Compare, Allocator> &m, const Key &k)
	{ return m.insert(std::make_pair(k, T())); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	std::pair<typename lrb_tree_map<Key, T, Compare, Allocator>::iterator, bool> insert_with_default_mapped_value(lrb_tree_map<Key, T, Compare, Allocator> &m, const Key &k)
	{ return m.insert(k); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	std::pair<typename lrb_tree_map_3w<Key, T, Compare, Allocator>::iterator, bool> insert_with_default_mapped_value(lrb_tree_map_3w<Key, T, Compare, Allocator> &m, const Key &k)
	{ return m.insert(k); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	std::pair<typename std::map<Key, T, Compare, Allocator>::iterator, bool> insert_and_report(std::map<Key, T, Compare, Allocator> &m, typename std::map<Key, T, Compare, Allocator>::iterator hint_it, const std::pair<const Key, T>& elem)
	{
		typedef std::map<Key, T, Compare, Allocator> map_type;
		typename map_type::size_type old_elem_count(m.size());
		typename map_type::iterator it(m.insert(hint_it, elem));
		return std::make_pair(it, old_elem_count != m.size());
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	std::pair<typename lrb_tree_map<Key, T, Compare, Allocator>::iterator, bool> insert_and_report(lrb_tree_map<Key, T, Compare, Allocator> &m, typename lrb_tree_map<Key, T, Compare, Allocator>::iterator hint_it, const std::pair<const Key, T>& elem)
	{ return m.insert_and_report(hint_it, elem); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	std::pair<typename lrb_tree_map_3w<Key, T, Compare, Allocator>::iterator, bool> insert_and_report(lrb_tree_map_3w<Key, T, Compare, Allocator> &m, typename lrb_tree_map_3w<Key, T, Compare, Allocator>::iterator hint_it, const std::pair<const Key, T>& elem)
	{ return m.insert_and_report(hint_it, elem); }

	//Normal erase since there is no unbalanced erase with std::map
	template<typename Key, typename T, typename Compare, typename Allocator>
	void unbalanced_erase(std::map<Key, T, Compare, Allocator> &m, typename std::map<Key, T, Compare, Allocator>::iterator it)
	{ m.erase(it); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	void unbalanced_erase(lrb_tree_map<Key, T, Compare, Allocator> &m, typename lrb_tree_map<Key, T, Compare, Allocator>::iterator it)
	{ return m.unbalanced_erase(it); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	void unbalanced_erase(lrb_tree_map_3w<Key, T, Compare, Allocator> &m, typename lrb_tree_map_3w<Key, T, Compare, Allocator>::iterator it)
	{ return m.unbalanced_erase(it); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	T& front(std::map<Key, T, Compare, Allocator> &m)
	{ return m.front(); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	const T& front(const std::map<Key, T, Compare, Allocator> &m)
	{ return *(m.begin()); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	T& front(lrb_tree_map<Key, T, Compare, Allocator> &m)
	{ return m.front(); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	const T& front(const lrb_tree_map<Key, T, Compare, Allocator> &m)
	{ return m.front(); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	T& front(lrb_tree_map_3w<Key, T, Compare, Allocator> &m)
	{ return m.front(); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	const T& front(const lrb_tree_map_3w<Key, T, Compare, Allocator> &m)
	{ return m.front(); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	T& back(std::map<Key, T, Compare, Allocator> &m)
	{ return *m.rbegin(); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	const T& back(const std::map<Key, T, Compare, Allocator> &m)
	{ return *m.rbegin(); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	T& back(lrb_tree_map<Key, T, Compare, Allocator> &m)
	{ return m.back(); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	const T& back(const lrb_tree_map<Key, T, Compare, Allocator> &m)
	{ return m.back(); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	T& back(lrb_tree_map_3w<Key, T, Compare, Allocator> &m)
	{ return m.back(); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	const T& back(const lrb_tree_map_3w<Key, T, Compare, Allocator> &m)
	{ return m.back(); }
} //namespace grapenlp

#endif /*GRAPENLP_MAP_IMPL_SELECTOR_H*/
