/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the the_treeied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Compareer General Public License for more details.
 *
 * You should have received a copy of the GNU Compareer General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

/*
 *  @author Javier Sastre
 */

#ifndef GRAPENLP_LRB_TREE_MAP_3W_H
#define GRAPENLP_LRB_TREE_MAP_3W_H

#include <stdexcept>
#include <grapenlp/lrb_tree_3w.h>

namespace grapenlp
{
	template<typename Key, typename T, typename Compare = compare_3w<Key>, typename Allocator = std::allocator<std::pair<const Key, T> > >
	class lrb_tree_map_3w
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;

    public:
    	class value_compare: public std::binary_function<value_type, value_type, bool>
    	{
    		friend class lrb_tree_map_3w<Key, T, Compare, Allocator>;
    	protected:
    		Compare comp;

    		value_compare(Compare comp_): comp(comp_)
    		{}

    	public:
    		bool operator()(const value_type& v1, const value_type& v2) const
    		{ return comp(v1.first, v2.first); }
    	};

    private:
    	typedef typename Allocator::template rebind<value_type>::other value_allocator_type;
		typedef lrb_tree_3w<key_type, value_type, pair_first<const Key, T>, key_compare, value_allocator_type> lrb_tree_type;

    public:
    	typedef typename value_allocator_type::pointer pointer;
    	typedef typename value_allocator_type::const_pointer const_pointer;
    	typedef typename value_allocator_type::reference reference;
    	typedef typename value_allocator_type::const_reference const_reference;
    	typedef typename lrb_tree_type::iterator iterator;
    	typedef typename lrb_tree_type::const_iterator const_iterator;
    	typedef typename lrb_tree_type::size_type size_type;
    	typedef typename lrb_tree_type::difference_type difference_type;
    	typedef typename lrb_tree_type::reverse_iterator reverse_iterator;
    	typedef typename lrb_tree_type::const_reverse_iterator const_reverse_iterator;

    private:
    	lrb_tree_type the_tree;

    public:
    	lrb_tree_map_3w(): the_tree()
		{}

		explicit lrb_tree_map_3w(const Compare& comp_, const allocator_type& alloc_ = allocator_type()): the_tree(comp_, alloc_)
		{}

		template<typename Iterator>
		lrb_tree_map_3w(Iterator first, Iterator last): the_tree()
		{ the_tree.insert(first, last); }

		template<typename Iterator>
		lrb_tree_map_3w(Iterator first, Iterator last, const Compare& comp_, const allocator_type& alloc_ = allocator_type()): the_tree(comp_, alloc_)
		{ the_tree.insert(first, last); }

		lrb_tree_map_3w(const lrb_tree_map_3w& s): the_tree(s.the_tree)
		{}

		lrb_tree_map_3w& operator=(const lrb_tree_map_3w& s)
		{
			the_tree = s.the_tree;
			return *this;
		}

		key_compare key_comp() const
		{ return the_tree.key_comp(); }

		value_compare value_comp() const
		{ return value_compare(the_tree.key_comp()); }

		allocator_type get_allocator() const
		{ return the_tree.get_allocator(); }

		const lrb_tree_type& get_tree()
		{ return the_tree; }

		iterator begin()
		{ return the_tree.begin(); }

		const_iterator begin() const
		{ return the_tree.begin(); }

		iterator end()
		{ return the_tree.end(); }

		const_iterator end() const
		{ return the_tree.end(); }

		reverse_iterator rbegin()
		{ return the_tree.rbegin(); }

		const_reverse_iterator rbegin() const
		{ return the_tree.rbegin(); }

		reverse_iterator rend()
		{ return the_tree.rend(); }

		const_reverse_iterator rend() const
		{ return the_tree.rend(); }

		value_type& front()
		{ return the_tree.front(); }

		value_type& front() const
		{ return the_tree.front(); }

		value_type& back()
		{ return the_tree.back(); }

		value_type& back() const
		{ return the_tree.back(); }

		mapped_type& operator[](const key_type& k)
		{ return the_tree.insert_with_default_mapped_value(k).first->second; }

		mapped_type& at(const key_type& k)
		{
			iterator it(lower_bound(k));
			if (it == end() || key_comp()(k, it->first))
				throw std::out_of_range("lrb_tree_map_3w::at");
			return it->second;
		}

		const mapped_type& at(const key_type& k) const
		{
			const_iterator it(lower_bound(k));
			if (it == end() || key_comp()(k, it->first))
				throw std::out_of_range("lrb_tree_map_3w::at");
			return it->second;
		}

		bool empty() const
		{ return the_tree.empty(); }

		size_type size() const
		{ return the_tree.size(); }

		size_type max_size() const
		{ return the_tree.max_size(); }

		void swap(lrb_tree_map_3w& m)
		{ the_tree.swap(m.the_tree); }

		std::pair<iterator, bool> insert(const value_type& v)
		{ return the_tree.insert(v); }

		//Insert with default mapped type
		std::pair<iterator, bool> insert(const key_type& k)
		{ return the_tree.insert_with_default_mapped_value(k); }

		iterator insert(iterator position, const value_type& v)
		{ return the_tree.insert(position, v).first; }

		//Insert with default mapped type
		iterator insert(iterator position, const key_type& k)
		{ return the_tree.insert_with_default_mapped_value(position, k).first; }

		std::pair<iterator, bool> insert_and_report(iterator position, const value_type& v)
		{ return the_tree.insert(position, v); }

		//Insert with default mapped type
		std::pair<iterator, bool> insert_and_report(iterator position, const key_type& k)
		{ return the_tree.insert_with_default_mapped_value(position, k); }

		template<typename Iterator>
		void insert(Iterator first, Iterator last)
		{ the_tree.insert(first, last); }

		void unbalanced_erase(iterator it)
		{ the_tree.unbalanced_erase(it); }

		size_type unbalanced_erase(const key_type& k)
		{ return the_tree.unbalanced_erase(k); }

		void unbalanced_erase(iterator first, iterator last)
		{ the_tree.unbalanced_erase(first, last); }

		void unbalanced_erase_if(std::unary_function<const key_type&, bool> &discriminator)
		{ the_tree.unbalanced_erase_if(discriminator); }

		void erase(iterator position)
		{ the_tree.erase(position); }

		size_type erase(const key_type& k)
		{ return the_tree.erase(k); }

		void erase(iterator first, iterator last)
		{ the_tree.erase(first, last); }

		void erase_if(std::unary_function<const key_type&, bool> &discriminator)
		{ the_tree.erase_if(discriminator); }

		void clear()
		{ the_tree.clear(); }

		iterator find(const key_type& k)
		{ return the_tree.find(k); }

		const_iterator find(const key_type& k) const
		{ return the_tree.find(k); }

		size_type count(const key_type& k) const
		{ return count(k); }

		iterator lower_bound(const key_type& k)
		{ return the_tree.lower_bound(k); }

		const_iterator lower_bound(const key_type& k) const
		{ return the_tree.lower_bound(k); }

		iterator upper_bound(const key_type& k)
		{ return the_tree.upper_bound(k); }

		const_iterator upper_bound(const key_type& k) const
		{ return the_tree.upper_bound(k); }

		std::pair<iterator, iterator> equal_range(const key_type& k)
		{ return the_tree.equal_range(k); }

		std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{ return the_tree.equal_range(k); }
#ifdef TRACE
		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits> &out) const
		{ return the_tree.serialize(out); }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& reverse_serialize(std::basic_ostream<CharT, Traits> &out) const
		{ return the_tree.reverse_serialize(out); }
#endif
		template<typename A, typename B, typename C, typename D>
		friend bool operator== (const lrb_tree_map_3w<A, B, C, D>&, const lrb_tree_map_3w<A, B, C, D>&);

		template<typename A, typename B, typename C, typename D>
		friend bool operator< (const lrb_tree_map_3w<A, B, C, D>&, const lrb_tree_map_3w<A, B, C, D>&);
	};

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator==(const lrb_tree_map_3w<Key, T, Compare, Allocator>& m1, const lrb_tree_map_3w<Key, T, Compare, Allocator>& m2)
	{ return m1.the_tree == m2.the_tree; }

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator<(const lrb_tree_map_3w<Key, T, Compare, Allocator>& m1, const lrb_tree_map_3w<Key, T, Compare, Allocator>& m2)
	{ return m1.the_tree < m2.the_tree; }

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator!=(const lrb_tree_map_3w<Key, T, Compare, Allocator>& m1, const lrb_tree_map_3w<Key, T, Compare, Allocator>& m2)
	{ return !(m1 == m2); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator>(const lrb_tree_map_3w<Key, T, Compare, Allocator>& m1, const lrb_tree_map_3w<Key, T, Compare, Allocator>& m2)
	{ return m2 < m1; }

	template<typename Key, typename T, typename Compare, typename Allocator>
    bool operator<=(const lrb_tree_map_3w<Key, T, Compare, Allocator>& m1, const lrb_tree_map_3w<Key, T, Compare, Allocator>& m2)
    { return !(m2 < m1); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator>=(const lrb_tree_map_3w<Key, T, Compare, Allocator>& m1, const lrb_tree_map_3w<Key, T, Compare, Allocator>& m2)
    { return !(m1 < m2); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	void swap(lrb_tree_map_3w<Key, T, Compare, Allocator>& m1, lrb_tree_map_3w<Key, T, Compare, Allocator>& m2)
    { m1.swap(m2); }
} //namespace grapenlp

#endif /*GRAPENLP_LRB_TREE_MAP_3W_H*/
