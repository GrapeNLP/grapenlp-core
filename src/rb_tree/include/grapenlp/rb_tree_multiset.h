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

#ifndef GRAPENLP_RB_TREE_MULTISET_H
#define GRAPENLP_RB_TREE_MULTISET_H

#include <grapenlp/rb_tree.h>

namespace grapenlp
{
	template<typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key> >
	class rb_tree_multiset
	{
    public:
/*      typedef typename Key_alloc_type::pointer             pointer;
      typedef typename Key_alloc_type::const_pointer       const_pointer;
      typedef typename Key_alloc_type::reference           reference;
      typedef typename Key_alloc_type::const_reference     const_reference;
*/
		typedef Key key_type;
		typedef Key value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

    private:
    	typedef typename Allocator::template rebind<Key>::other key_allocator_type;
    	typedef rb_tree<key_type, value_type, identity<value_type>, key_compare, key_allocator_type> rb_tree_type;

    public:
    	typedef typename rb_tree_type::const_iterator iterator;
		typedef typename rb_tree_type::const_iterator const_iterator;
		typedef typename rb_tree_type::const_reverse_iterator reverse_iterator;
		typedef typename rb_tree_type::const_reverse_iterator const_reverse_iterator;
		typedef typename rb_tree_type::size_type size_type;
		typedef typename rb_tree_type::difference_type difference_type;

	    rb_tree_type the_tree;

		rb_tree_multiset(): the_tree()
		{}

		explicit rb_tree_multiset(const Compare& comp_, const allocator_type& alloc_ = allocator_type()): the_tree(comp_, alloc_)
		{}

		template<typename Iterator>
		rb_tree_multiset(Iterator first, Iterator last): the_tree()
		{ the_tree.multi_insert(first, last); }

		template<typename Iterator>
		rb_tree_multiset(Iterator first, Iterator last, const Compare& comp_, const allocator_type& alloc_ = allocator_type()): the_tree(comp_, alloc_)
		{ the_tree.multi_insert(first, last); }

		rb_tree_multiset(const rb_tree_multiset& s): the_tree(s.the_tree)
		{}

		rb_tree_multiset& operator=(const rb_tree_multiset& s)
		{
			the_tree = s.the_tree;
			return *this;
		}

		key_compare key_comp() const
		{ return the_tree.key_comp(); }

		value_compare value_comp() const
		{ return the_tree.key_comp(); }

		allocator_type get_allocator() const
		{ return the_tree.get_allocator(); }

		const rb_tree_type& get_tree()
		{ return the_tree; }

		iterator begin() const
		{ return the_tree.begin(); }

		iterator end() const
		{ return the_tree.end(); }

		reverse_iterator rbegin() const
		{ return the_tree.rbegin(); }

		reverse_iterator rend() const
		{ return the_tree.rend(); }

		bool empty() const
		{ return the_tree.empty(); }

		size_type size() const
		{ return the_tree.size(); }

		size_type max_size() const
		{ return the_tree.max_size(); }

		void swap(rb_tree_multiset& s)
		{ the_tree.swap(s.the_tree); }

		iterator insert(const value_type& v)
		{ return the_tree.multi_insert(v); }

		iterator insert(iterator position, const value_type& v)
		{ return the_tree.multi_insert(position, v); }

	    template<typename Iterator>
		void insert(Iterator first, Iterator last)
		{ the_tree.multi_insert(first, last); }

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
		{ return the_tree.multi_erase(k); }

		void erase(iterator first, iterator last)
		{ the_tree.erase(first, last); }

		void erase_if(std::unary_function<const key_type&, bool> &discriminator)
		{ the_tree.erase_if(discriminator); }

		void clear()
		{ the_tree.clear(); }

		size_type count(const key_type& k) const
		{ return multi_count(k); }

		iterator find(const key_type& k)
		{ return the_tree.find(k); }

		const_iterator find(const key_type& k) const
		{ return the_tree.find(k); }

		iterator lower_bound(const key_type& k)
		{ return the_tree.multi_lower_bound(k); }

		const_iterator lower_bound(const key_type& k) const
		{ return the_tree.multi_lower_bound(k); }

		iterator upper_bound(const key_type& k)
		{ return the_tree.multi_upper_bound(k); }

		const_iterator upper_bound(const key_type& k) const
		{ return the_tree.multi_upper_bound(k); }

		std::pair<iterator, iterator> equal_range(const key_type& k)
		{ return the_tree.multi_equal_range(k); }

		std::pair<const_iterator, const_iterator>
		equal_range(const key_type& k) const
		{ return the_tree.multi_equal_range(k); }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits> &out) const
		{ return the_tree.serialize(out); }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& reverse_serialize(std::basic_ostream<CharT, Traits> &out) const
		{ return the_tree.reverse_serialize(out); }

		template<typename A, typename B, typename C>
		friend bool operator== (const rb_tree_multiset<A, B, C>&, const rb_tree_multiset<A, B, C>&);

		template<typename A, typename B, typename C>
		friend bool operator< (const rb_tree_multiset<A, B, C>&, const rb_tree_multiset<A, B, C>&);
	};

	template<typename Key, typename Compare, typename Allocator>
	bool operator==(const rb_tree_multiset<Key, Compare, Allocator>& s1, const rb_tree_multiset<Key, Compare, Allocator>& s2)
	{ return s1.the_tree == s2.the_tree; }

	template<typename Key, typename Compare, typename Allocator>
	bool operator<(const rb_tree_multiset<Key, Compare, Allocator>& s1, const rb_tree_multiset<Key, Compare, Allocator>& s2)
	{ return s1.the_tree < s2.the_tree; }

	template<typename Key, typename Compare, typename Allocator>
	bool operator!=(const rb_tree_multiset<Key, Compare, Allocator>& s1, const rb_tree_multiset<Key, Compare, Allocator>& s2)
	{ return !(s1 == s2); }

	template<typename Key, typename Compare, typename Allocator>
	bool operator>(const rb_tree_multiset<Key, Compare, Allocator>& s1, const rb_tree_multiset<Key, Compare, Allocator>& s2)
	{ return s2 < s1; }

	template<typename Key, typename Compare, typename Allocator>
    bool operator<=(const rb_tree_multiset<Key, Compare, Allocator>& s1, const rb_tree_multiset<Key, Compare, Allocator>& s2)
    { return !(s2 < s1); }

	template<typename Key, typename Compare, typename Allocator>
	bool operator>=(const rb_tree_multiset<Key, Compare, Allocator>& s1, const rb_tree_multiset<Key, Compare, Allocator>& s2)
    { return !(s1 < s2); }

	template<typename Key, typename Compare, typename Allocator>
	void swap(rb_tree_multiset<Key, Compare, Allocator>& s1, rb_tree_multiset<Key, Compare, Allocator>& s2)
    { s1.swap(s2); }
} //namespace grapenlp

#endif /*GRAPENLP_RB_TREE_MULTISET_H*/
