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
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * KeyCompareer General Public License for more details.
 *
 * You should have received a copy of the GNU KeyCompareer General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

/*
 *  @author Javier Sastre
 */

#ifndef GRAPENLP_RB_TREE_H
#define GRAPENLP_RB_TREE_H

#include <iostream>
#include <stack>
#include <grapenlp/functional.h>
#include <grapenlp/memory.h>

namespace grapenlp
{
	template<typename Key, typename ValueSerializer, typename KeyGetter, typename Compare, typename Allocator>
	struct rb_tree_to_dot_serializer;

	template<typename Key, typename Value, typename KeyGetter, typename KeyCompare = std::less<Key>, typename Allocator = std::allocator<Value> >
	class rb_tree
	{
		template<typename A, typename B, typename C, typename D, typename E>
		friend struct rb_tree_to_dot_serializer;

	public:
		typedef Key key_type;
		typedef Value value_type;
		typedef KeyCompare key_compare;
		typedef KeyCompare value_compare;
		typedef Allocator allocator_type;

        typedef value_type& reference;
        typedef const value_type& const_reference;
		typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;

	private:
        class node;

		class base_node
		{
			friend class rb_tree;
			friend class node;
			template<typename A, typename B, typename C, typename D, typename E>
			friend struct rb_tree_to_dot_serializer;

			typedef base_node* ref;
			typedef const base_node* const_ref;

			ref parent_ref, left_ref, right_ref;
			bool is_red;

			base_node(): parent_ref(NULL), left_ref(NULL), right_ref(NULL), is_red(false)
			{}

			value_type& value()
			{ return static_cast<node*>(this)->v; }

			const value_type& value() const
			{ return static_cast<const node*>(this)->v; }

			bool has_left() const
			{ return left_ref; }

			bool has_no_left() const
			{ return !left_ref; }

			bool has_right() const
			{ return right_ref; }

			bool has_no_right() const
			{ return !right_ref; }

			bool has_missing_child() const
			{ return has_no_left() || has_no_right(); }

			bool has_both_children() const
			{ return has_left() && has_right(); }

			bool is_leaf() const
			{ return has_no_left() && has_no_right(); }

			bool is_inner() const
			{ return has_left() || has_right(); }

			bool is_left_child() const
			{ return this == parent_ref->left_ref; }

			bool is_right_child() const
			{ return this == parent_ref->right_ref; }

/*			bool is_nil_or_root()
			{ return parent_ref->parent_ref == this; }

			bool is_nil()
			{ return is_red && is_nil_or_root(); }

			base_node_ref previous_ref()
			{
				if (is_nil_ref())
					return right_ref;
				if (has_left())
				{
					ref x = left_ref;
					while (x->has_right())
						x = x->right_ref;
					return x;
				}
				ref x(this);
				ref y(parent_ref);
				while (x == y->left_ref)
				{
					x = y;
					y = y->parent_ref;
				}
				return y;
			}
*/
			ref previous_ref()
			{
				if (has_left())
				{
					ref x(left_ref);
					while (x->has_right())
						x = x->right_ref;
					return x;
				}
				ref x(this);
				ref y(parent_ref);
				while (x == y->left_ref)
				{
					x = y;
					y = y->parent_ref;
				}
				if (x->left_ref != y)
					return y;
				return x;
			}

			const_ref previous_const_ref() const
			{
				if (has_left())
				{
					ref x(left_ref);
					while (x->has_right())
						x = x->right_ref;
					return x;
				}
				const_ref x(this);
				const_ref y(parent_ref);
				while (x == y->left_ref)
				{
					x = y;
					y = y->parent_ref;
				}
				if (x->left_ref != y)
					return y;
				return x;
			}

			ref next_ref()
			{
				if (has_right())
				{
					ref x(right_ref);
					while (x->has_left())
						x = x->left_ref;
					return x;
				}
				ref x(this);
				ref y(parent_ref);
				while (x == y->right_ref)
				{
					x = y;
					y = y->parent_ref;
				}
				if (x->right_ref != y)
					return y;
				return x;
			}

			const_ref next_const_ref() const
			{
				if (has_right())
				{
					const_ref x(right_ref);
					while (x->has_left())
						x = x->left_ref;
					return x;
				}
				const_ref x(this);
				const_ref y(parent_ref);
				while (x == y->right_ref)
				{
					x = y;
					y = y->parent_ref;
				}
				if (x->right_ref != y)
					return y;
				return x;
			}
		};

		typedef typename base_node::ref base_node_ref;
		typedef typename base_node::const_ref base_node_const_ref;

		class node: public base_node
		{
			friend class rb_tree;

			typedef node* ref;
			typedef const node* const_ref;

		private:
			value_type v;

			node(const value_type &v_): base_node(), v(v_)
			{}

			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits> &out) const
			{
				if (base_node::left_ref)
					base_node::left_ref->serialize(out);
				out << v << ' ';
				if (base_node::right_ref)
					base_node::right_ref->serialize(out);
				return out;
			}
		};

        typedef typename node::ref node_ref;
        typedef typename node::const_ref node_const_ref;
        typedef typename allocator_type::template rebind<node>::other node_allocator;

		node_allocator& get_node_allocator()
		{ return *static_cast<node_allocator*>(&this->d); }

		const node_allocator& get_node_allocator() const
		{ return *static_cast<const node_allocator*>(&this->d); }

		allocator_type get_allocator() const
		{ return allocator_type(get_node_allocator()); }

	protected:
		node_ref allocate_node()
		{ return d.node_allocator::allocate(1); }

		void deallocate_node(node_ref x)
		{ d.node_allocator::deallocate(x, 1); }

		node_ref create_node(const value_type& v)
		{
			node_ref x = allocate_node();
			try
			{ get_allocator().construct(&x->v, v); }
			catch(...)
			{
				deallocate_node(x);
				throw;
			}
			return x;
		}

		node_ref create_node(base_node_ref parent_ref, base_node_ref left_ref, base_node_ref right_ref, bool is_red, const value_type &v)
		{
			node_ref x(allocate_node());
			try
			{ get_allocator().construct(&x->v, v); }
			catch(...)
			{
				deallocate_node(x);
				throw;
			}
			x->parent_ref = parent_ref;
			x->left_ref = left_ref;
			x->right_ref = right_ref;
			x->is_red = is_red;
			return x;
		}

		//t is supposed to be a non-empty tree
		void copy_tree(const rb_tree &t)
		{
			root_ref() = create_node(nil_ref(), NULL, NULL, t.root_const_ref()->is_red, t.root_const_ref()->value());
			if (t.root_const_ref()->has_left())
			{
				root_ref()->left_ref = create_node(root_ref(), NULL, NULL, t.root_const_ref()->left_ref->is_red, t.root_const_ref()->left_ref->value());
				copy_leftmost_subtree(t.root_const_ref()->left_ref, root_ref()->left_ref);
			}
			else first_base_node_ref() = root_ref();
			if (t.root_const_ref()->has_right())
			{
				root_ref()->right_ref = create_node(root_ref(), NULL, NULL, t.root_const_ref()->right_ref->is_red, t.root_const_ref()->right_ref->value());
				copy_rightmost_subtree(t.root_const_ref()->right_ref, root_ref()->right_ref);
			}
			else last_base_node_ref() = root_ref();
		}

		void copy_leftmost_subtree(base_node_const_ref tsubroot_ref, base_node_ref subroot_ref)
		{
			if (tsubroot_ref->has_left())
			{
				subroot_ref->left_ref = create_node(subroot_ref, NULL, NULL, tsubroot_ref->left_ref->is_red, tsubroot_ref->left_ref->value());
				copy_leftmost_subtree(tsubroot_ref->left_ref, subroot_ref->left_ref);
			}
			else first_base_node_ref() = subroot_ref;
			if (tsubroot_ref->has_right())
			{
				subroot_ref->right_ref = create_node(subroot_ref, NULL, NULL, tsubroot_ref->right_ref->is_red, tsubroot_ref->right_ref->value());
				copy_subtree(tsubroot_ref->right_ref, subroot_ref->right_ref);
			}
		}

		void copy_rightmost_subtree(base_node_const_ref tsubroot_ref, base_node_ref subroot_ref)
		{
			if (tsubroot_ref->has_left())
			{
				subroot_ref->left_ref = create_node(subroot_ref, NULL, NULL, tsubroot_ref->left_ref->is_red, tsubroot_ref->left_ref->value());
				copy_subtree(tsubroot_ref->left_ref, subroot_ref->left_ref);
			}
			if (tsubroot_ref->has_right())
			{
				subroot_ref->right_ref = create_node(subroot_ref, NULL, NULL, tsubroot_ref->right_ref->is_red, tsubroot_ref->right_ref->value());
				copy_rightmost_subtree(tsubroot_ref->right_ref, subroot_ref->right_ref);
			}
			else last_base_node_ref() = subroot_ref;
		}

		void copy_subtree(base_node_const_ref tsubroot_ref, base_node_ref subroot_ref)
		{
			if (tsubroot_ref->has_left())
			{
				subroot_ref->left_ref = create_node(subroot_ref, NULL, NULL, tsubroot_ref->left_ref->is_red, tsubroot_ref->left_ref->value());
				copy_subtree(tsubroot_ref->left_ref, subroot_ref->left_ref);
			}
			if (tsubroot_ref->has_right())
			{
				subroot_ref->right_ref = create_node(subroot_ref, NULL, NULL, tsubroot_ref->right_ref->is_red, tsubroot_ref->right_ref->value());
				copy_subtree(tsubroot_ref->right_ref, subroot_ref->right_ref);
			}
		}

		void destroy_node(node_ref x)
		{
			get_allocator().destroy(&x->v);
			deallocate_node(x);
		}

	public:
		class const_iterator;

		class iterator: public std::iterator<std::bidirectional_iterator_tag, value_type, std::size_t, value_type*, value_type&>
		{
			friend class rb_tree;

			base_node_ref x;

			explicit iterator(base_node_ref x_): x(x_)
			{}

		public:
			iterator(): x(NULL)
			{}

			iterator(const iterator &it): x(it.x)
			{}

			value_type& operator*() const
			{ return x->value(); }

			value_type* operator->() const
			{ return &x->value(); }

			iterator& operator++ ()
			{
				x = x->next_ref();
				return *this;
			}

			iterator& operator++ (int)
			{
				iterator it(x);
				x = x->next_ref();
				return it;
			}

			iterator& operator-- ()
			{
				x = x->previous_ref();
				return *this;
			}

			iterator& operator-- (int i)
			{
				iterator it(x);
				x = x->previous_ref;
				return it;
			}

			bool operator== (const iterator &it) const
			{ return x == it.x; }

			bool operator!= (const iterator &it) const
			{ return x != it.x; }

			bool operator== (const const_iterator &it) const
			{ return x == it.x; }

			bool operator!= (const const_iterator &it) const
			{ return x != it.x; }
		};

		class const_iterator: public std::iterator<std::bidirectional_iterator_tag, value_type, std::size_t, const value_type*, const value_type&>
		{
			friend class rb_tree;

			base_node_const_ref x;

			explicit const_iterator(base_node_const_ref x_): x(x_)
			{}

		public:
			const_iterator(): x(NULL)
			{}

			const_iterator(const const_iterator &it): x(it.x)
			{}

			const_iterator(const iterator &it): x(it.x)
			{}

			const value_type& operator*() const
			{ return x->value(); }

			const value_type* operator->() const
			{ return &x->value(); }

			const_iterator& operator++ ()
			{
				x = x->next_const_ref();
				return *this;
			}

			const_iterator& operator++ (int i)
			{
				const_iterator it(x);
				x = x->next_const_ref();
				return it;
			}

			const_iterator& operator-- ()
			{
				x = x->previous_const_ref();
				return *this;
			}

			const_iterator& operator-- (int i)
			{
				const_iterator it(x);
				x = x->previous_const_ref();
				return it;
			}

			bool operator== (const const_iterator &it) const
			{ return x == it.x; }

			bool operator!= (const const_iterator &it) const
			{ return x != it.x; }

			bool operator== (const iterator &it) const
			{ return x == it.x; }

			bool operator!= (const iterator &it) const
			{ return x != it.x; }
		};

        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		struct data: public node_allocator
		{
			KeyCompare comp;
			base_node_ref nil_ref;
			std::size_t node_count;

			data(const KeyCompare & comp_, const node_allocator &n_alloc_): node_allocator(n_alloc_), comp(comp_), nil_ref(new base_node()), node_count(0)
			{ nil_ref->left_ref = nil_ref->right_ref = nil_ref; }

			~data()
			{ delete nil_ref; }
		};

		data d;

	public:
		rb_tree(const KeyCompare& comp_ = KeyCompare(), const allocator_type& alloc_ = allocator_type()): d(comp_, alloc_)
		{}

		rb_tree(const rb_tree &t): d(t.d.comp, t.get_node_allocator())
		{
			if (!t.empty())
			{
				copy_tree(t);
				d.node_count = t.d.node_count;
			}
		}

		rb_tree& operator= (const rb_tree& t)
		{
			if (this != &t)
			{
				clear();
				d.comp = t.d.comp;
				if (!t.empty())
			    {
					copy_tree(t);
					d.node_count = t.d.node_count;
			    }
			}
			return *this;
		}

	public:
		key_compare key_comp() const
		{ return d.comp; }

	private:
		bool compare(const value_type &v1, const value_type &v2) const
		{ return d.comp(KeyGetter()(v1), KeyGetter()(v2)); }

		bool compare(const key_type &k, base_node_const_ref x) const
		{ return d.comp(k, KeyGetter()(x->value())); }

		bool compare(base_node_const_ref x, const key_type &k) const
		{ return d.comp(KeyGetter()(x->value()), k); }

		base_node_ref& nil_ref()
		{ return d.nil_ref; }

		base_node_const_ref nil_const_ref() const
		{ return d.nil_ref; }

		base_node_ref& root_ref()
		{ return nil_ref()->parent_ref; }

		base_node_const_ref root_const_ref() const
		{ return nil_const_ref()->parent_ref; }

		base_node_ref& first_base_node_ref()
		{ return nil_ref()->right_ref; }

		base_node_const_ref first_base_node_const_ref() const
		{ return nil_const_ref()->right_ref; }

		base_node_ref& last_base_node_ref()
		{ return nil_ref()->left_ref; }

		base_node_const_ref last_base_node_const_ref() const
		{ return nil_const_ref()->left_ref; }

		bool is_root(base_node_const_ref x) const
		{ return x->parent_ref == nil_const_ref(); }

		bool is_nil(base_node_const_ref x) const
		{ return !x; }

		bool is_not_nil(base_node_const_ref x) const
		{ return x; }

		void destroy_subtree(base_node_ref x)
		{
			if (x->has_left())
				destroy_subtree(x->left_ref);
			if (x->has_right())
				destroy_subtree(x->right_ref);
			destroy_node(static_cast<node_ref>(x));
		}

	public:
		void clear()
		{
			if (empty())
				return;
			destroy_subtree(root_ref());
			last_base_node_ref() = first_base_node_ref() = nil_ref();
			root_ref() = NULL;
			d.node_count = 0;
		}

		~rb_tree()
		{
			if (root_ref())
				destroy_subtree(root_ref());
		}

		void swap(rb_tree &t)
		{
			std::swap(nil_ref(), t.nil_ref());
			std::swap(d.node_count, t.d.node_count);
			std::swap(d.comp, t.d.comp);
			//This is compiled as no-code if allocators are empty classes
			allocator_swapper<node_allocator>()(get_node_allocator(), t.get_node_allocator());
		}

	public:
		iterator begin()
		{ return iterator(first_base_node_ref()); }

		iterator end()
		{ return iterator(nil_ref()); }

		reverse_iterator rbegin()
		{ return reverse_iterator(end()); }

		reverse_iterator rend()
		{ return reverse_iterator(begin()); }

		const_iterator begin() const
		{ return const_iterator(first_base_node_const_ref()); }

		const_iterator end() const
		{ return const_iterator(nil_const_ref()); }

		const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(end()); }

		const_reverse_iterator rend() const
		{ return const_reverse_iterator(begin()); }

/*		const_preorder_iterator preorder_begin() const
		{ return const_preorder_iterator(root_ref()); }

		const_preorder_iterator preorder_end() const
		{ return const_preorder_iterator(d.nil_ref); }
*/
		bool empty() const
		{ return is_nil(root_const_ref()); }

		std::size_t size() const
		{ return d.node_count; }

		size_type max_size() const
		{ return get_allocator().max_size(); }

	private:
		void left_rotate(base_node_ref x)
		{
			base_node_ref y(x->right_ref);
			x->right_ref = y->left_ref;
			if (y->has_left())
				y->left_ref->parent_ref = x;
			y->parent_ref = x->parent_ref;
			if (is_root(x))
				root_ref() = y;
			else if (x == x->parent_ref->left_ref)
				x->parent_ref->left_ref = y;
			else x->parent_ref->right_ref = y;
			y->left_ref = x;
			x->parent_ref = y;
		}

		void right_rotate(base_node_ref x)
		{
			base_node_ref y(x->left_ref);
			x->left_ref = y->right_ref;
			if (y->has_right())
				y->right_ref->parent_ref = x;
			y->parent_ref = x->parent_ref;
			if (is_root(x))
				root_ref() = y;
			else if (x == x->parent_ref->right_ref)
				x->parent_ref->right_ref = y;
			else x->parent_ref->left_ref = y;
			y->right_ref = x;
			x->parent_ref = y;
		}

		void insert_fixup(base_node_ref z)
		{
			while (z->parent_ref->is_red)
			{
				if (z->parent_ref == z->parent_ref->parent_ref->left_ref)
				{
					base_node_ref y(z->parent_ref->parent_ref->right_ref);
					if (y && y->is_red)
					{
						z->parent_ref->is_red = false;
						y->is_red = false;
						z->parent_ref->parent_ref->is_red = true;
						z = z->parent_ref->parent_ref;
					}
					else
					{
						if (z == z->parent_ref->right_ref)
						{
							z = z->parent_ref;
							left_rotate(z);
						}
						z->parent_ref->is_red = false;
						z->parent_ref->parent_ref->is_red = true;
						right_rotate(z->parent_ref->parent_ref);
					}
				}
				else
				{
					base_node_ref y(z->parent_ref->parent_ref->left_ref);
					if (y && y->is_red)
					{
						z->parent_ref->is_red = false;
						y->is_red = false;
						z->parent_ref->parent_ref->is_red = true;
						z = z->parent_ref->parent_ref;
					}
					else
					{
						if (z == z->parent_ref->left_ref)
						{
							z = z->parent_ref;
							right_rotate(z);
						}
						z->parent_ref->is_red = false;
						z->parent_ref->parent_ref->is_red = true;
						left_rotate(z->parent_ref->parent_ref);
					}
				}
			}
			root_ref()->is_red = false;
		}

		base_node_ref insert_as_root(const value_type &value)
		{
			base_node_ref z(create_node(nil_ref(), NULL, NULL, true, value));
			last_base_node_ref() = first_base_node_ref() = root_ref() = z;
			insert_fixup(z);
			++d.node_count;
			return z;
		}

		base_node_ref insert_as_left_child_of(base_node_ref x, const value_type &value)
		{
			base_node_ref z(create_node(x, NULL, NULL, true, value));
			x->left_ref = z;
			insert_fixup(z);
			++d.node_count;
			return z;
		}

		base_node_ref insert_as_leftmost_child_of(base_node_ref x, const value_type &value)
		{ return first_base_node_ref() = insert_as_left_child_of(x, value);	}

		base_node_ref insert_as_right_child_of(base_node_ref x, const value_type &value)
		{
			base_node_ref z(create_node(x, NULL, NULL, true, value));
			x->right_ref = z;
			insert_fixup(z);
			++d.node_count;
			return z;
		}

		base_node_ref insert_as_rightmost_child_of(base_node_ref x, const value_type &value)
		{ return last_base_node_ref() = insert_as_right_child_of(x, value);	}

		//Insertion without duplicates (uses "less than" comparator)
		std::pair<base_node_ref, bool> insert_to_intermediate_base_node_ref(base_node_ref x, const value_type &value)
		{
			while (true)
			{
				if (compare(value, x->value()))
				{
					if (x->has_no_left())
						return std::make_pair(insert_as_left_child_of(x, value), true);
					x = x->left_ref;
					continue;
				}
				if (compare(x->value(), value))
				{
					if (x->has_no_right())
						return std::make_pair(insert_as_right_child_of(x, value), true);
					x = x->right_ref;
					continue;
				}
				return std::make_pair(x, false);
			}
		}

		//Insertion without duplicates (uses "less than" comparator)
		std::pair<base_node_ref, bool> insert_to_base_node_ref(const value_type &value)
		{
			if (empty())
				return std::make_pair(insert_as_root(value), true);
			base_node_ref x(root_ref());

			if (compare(value, x->value()))
			{
				while (true)
				{
					if (x->has_no_left())
						return std::make_pair(insert_as_leftmost_child_of(x, value), true);
					x = x->left_ref;
					if (compare(value, x->value()))
						continue;
					if (compare(x->value(), value))
					{
						if (x->has_no_right())
							return std::make_pair(insert_as_right_child_of(x, value), true);
						return insert_to_intermediate_base_node_ref(x->right_ref, value);
					}
				}
			}
			if (compare(x->value(), value))
			{
				while (true)
				{
					if (x->has_no_right())
						return std::make_pair(insert_as_rightmost_child_of(x, value), true);
					x = x->right_ref;
					if (compare(x->value(), value))
						continue;
					if (compare(value, x->value()))
					{
						if (x->has_no_left())
							return std::make_pair(insert_as_left_child_of(x, value), true);
						return insert_to_intermediate_base_node_ref(x->left_ref, value);
					}
				}
			}
			return std::make_pair(x, false);
		}

		//Insertion with duplicates (uses "greater or equal than" comparator)
		base_node_ref multi_insert_to_base_node_ref(const value_type &value)
		{
			if (empty())
				return insert_as_root(value);
			base_node_ref x(root_ref());

			while (true)
			{
				if (compare(value, x->value()))
				{
					if (x->has_no_left())
						return insert_as_left_child_of(x, value);
					x = x->left_ref;
					continue;
				}
				if (x->has_no_right())
					return insert_as_right_child_of(x, value);
				x = x->right_ref;
			}
		}

	public:
		//Insertion without duplicates (uses "less than" comparator)
		std::pair<iterator, bool> insert(const value_type &value)
		{
			std::pair<base_node_ref, bool> result(insert_to_base_node_ref(value));
			return std::make_pair(iterator(result.first), result.second);
		}

		//Insertion with duplicates (uses "greater or equal than" comparator)
		iterator multi_insert(const value_type &value)
		{ return iterator(multi_insert_to_base_node_ref(value)); }

	private:
		//Insert with hint: start search for insertion position from p instead of root
		std::pair<base_node_ref, bool> insert(base_node_const_ref p, const value_type& v)
		{
			//p == nil
			if (is_nil(p))
			{
				//last < v: insert as last's right child
				if (!empty() && compare(last_base_node_const_ref(),	KeyGetter()(v)))
					return std::make_pair(insert_as_right_child_of(last_base_node_ref(), v), true);
				//empty || v < last: normal insert
				return insert_to_base_node_ref(v);
			}
			//p < v
			if (compare(p, KeyGetter()(v)))
			{
				//p == last: insert as last's right child
				if (p == last_base_node_const_ref())
					return std::make_pair(insert_as_right_child_of(last_base_node_ref(), v), true);
				//p < v < ++p
				base_node_ref next(const_cast<base_node_ref>(p)->next_ref());
				if (compare(KeyGetter()(v), next))
				{
					//p has no right child: p under left of ++p, p has no right child, insert as p right child
					if (p->has_no_right())
						return std::make_pair(insert_as_right_child_of(const_cast<base_node_ref>(p), v), true);
					//p has right child: ++p under right p, ++p has no left child, insert as ++p left child
					return std::make_pair(insert_as_left_child_of(next, v), true);
				}
				//p < ++p < v: normal insert
				return insert_to_base_node_ref(v);
			}
			//v < p
			if (compare(KeyGetter()(v), p))
			{
				//p == first: insert as first's left child
				if (p == first_base_node_const_ref())
					return std::make_pair(insert_as_left_child_of(first_base_node_ref(), v), true);
				//--p < v < p
				base_node_ref previous(const_cast<base_node_ref>(p)->previous_ref());
				if (compare(previous, KeyGetter()(v)))
			    {
					//--p has no right child: --p under left of p, --p has no right child, insert as --p right child
					if (previous->has_no_right())
						return std::make_pair(insert_as_right_child_of(previous, v), true);
					//--p has right child: p under right of --p, p has no left child, insert as p left child
					return std::make_pair(insert_as_left_child_of(const_cast<base_node_ref>(p), v), true);
			    }
				//v < --p < p: normal insert
				return insert_to_base_node_ref(v);
			}
			//p == v
			return std::make_pair(const_cast<base_node_ref>(p), false);
		}

		//Insertion with duplicates and hint: use "greater or equal than" comparator and
		//start search for insertion position from p instead of root
		base_node_ref multi_insert(base_node_const_ref p, const value_type& v)
		{
			//p == nil
			if (is_nil(p))
			{
				//last < v: insert as last's right child
				if (!empty() && compare(last_base_node_const_ref(),	KeyGetter()(v)))
					return insert_as_right_child_of(last_base_node_ref(), v);
				//empty || v < last: normal insert
				return multi_insert_to_base_node_ref(v);
			}
			//v < p
			if (compare(KeyGetter()(v), p))
			{
				//p == first: insert as first's left child
				if (p == first_base_node_const_ref())
					return insert_as_left_child_of(first_base_node_ref(), v);
				//--p < v < p
				base_node_ref previous(const_cast<base_node_ref>(p)->previous_ref());
				if (compare(previous, KeyGetter()(v)))
			    {
					//--p has no right child: --p under left of p, --p has no right child, insert as --p right child
					if (previous->has_no_right())
						insert_as_right_child_of(previous, v);
					//--p has right child: p under right of --p, p has no left child, insert as p left child
					return insert_as_left_child_of(const_cast<base_node_ref>(p), v);
			    }
				//v < --p <= p: normal insert
				return multi_insert_to_base_node_ref(v);
			}
			//p <= v
			//p == last: insert as last's right child
			if (p == last_base_node_const_ref())
				return insert_as_right_child_of(last_base_node_ref(), v);
			//p <= v < ++p
			base_node_ref next(const_cast<base_node_ref>(p)->next_ref());
			if (compare(KeyGetter()(v), next))
			{
				//p has no right child: p under left of ++p, p has no right child, insert as p right child
				if (p->has_no_right())
					return insert_as_right_child_of(const_cast<base_node_ref>(p), v);
				//p has right child: ++p under right p, ++p has no left child, insert as ++p left child
				return insert_as_left_child_of(next, v);
			}
			//p <= ++p <= v: normal insert
			return multi_insert_to_base_node_ref(v);
		}

		template<typename Iterator>
		void insert(Iterator first, Iterator last)
		{
			if (first == last)
				return;
			base_node_ref p(insert(*first).first);
			for (++first; first != last; ++first)
				p = insert(p, *first);
		}

	public:
		std::pair<iterator, bool> insert(const_iterator position, const value_type& v)
		{
			std::pair<base_node_ref, bool> result(insert(position.x, v));
			return std::make_pair(iterator(result.first), result.second);
		}

		iterator multi_insert(const_iterator position, const value_type& v)
		{ return iterator(multi_insert(position.x, v)); }

	private:
		void unbalanced_leftmost_erase(base_node_ref x)
		{
			first_base_node_ref() = x->next_ref();
			destroy_node(static_cast<node_ref>(x));
		}

		void unbalanced_rightmost_erase(base_node_ref x)
		{
			last_base_node_ref() = x->previous_ref();
			destroy_node(static_cast<node_ref>(x));
		}

		void unbalanced_intermediate_erase(base_node_ref x)
		{ destroy_node(static_cast<node_ref>(x)); }

		void unbalanced_erase(base_node_ref x)
		{
			if (first_base_node_ref() == x)
				unbalanced_leftmost_erase(x);
			else if (last_base_node_ref() == x)
				unbalanced_rightmost_erase(x);
			else unbalanced_intermediate_erase(x);
		}

		void erase_fixup(base_node_ref x)
		{
			while (x != root_ref() && !x->is_red)
			{
				if (x == x->parent_ref->left_ref)
				{
					base_node_ref w(x->parent_ref->right_ref);
					if (w->is_red)
					{
						w->is_red = false;
						x->parent_ref->is_red = true;
						left_rotate(x->parent_ref);
						w = x->parent_ref->right_ref;
					}
					if (!w->left_ref->is_red && !w->right_ref->is_red)
					{
						w->is_red = true;
						x = x->parent_ref;
					}
					else
					{
						if (!w->right_ref->is_red)
						{
							w->left_ref->is_red = false;
							w->is_red = true;
							right_rotate(w);
							w = x->parent_ref->right_ref;
						}
						w->is_red = x->parent_ref->is_red;
						x->parent_ref->is_red = false;
						w->right_ref->is_red = false;
						left_rotate(x->parent_ref);
						x = root_ref();
					}
				}
				else
				{
					if (x == x->parent_ref->right_ref)
					{
						base_node_ref w(x->parent_ref->left_ref);
						if (w->is_red)
						{
							w->is_red = false;
							x->parent_ref->is_red = true;
							right_rotate(x->parent_ref);
							w = x->parent_ref->left_ref;
						}
						if (!w->right_ref->is_red && !w->left_ref->is_red)
						{
							w->is_red = true;
							x = x->parent_ref;
						}
						else
						{
							if (!w->left_ref->is_red)
							{
								w->right_ref->is_red = false;
								w->is_red = true;
								left_rotate(w);
								w = x->parent_ref->left_ref;
							}
							w->is_red = x->parent_ref->is_red;
							x->parent_ref->is_red = false;
							w->left_ref->is_red = false;
							right_rotate(x->parent_ref);
							x = root_ref();
						}
					}
				}
			}
			x->is_red = false;
		}

		void erase(base_node_ref z)
		{
			base_node_ref y(z->has_missing_child() ? z : z->next_ref());
			base_node_ref x;
			if (y->has_left())
			{
				x = y->left_ref;
				x->parent_ref = y->parent_ref;
			}
			else if (y->has_right())
			{
				x = y->right_ref;
				x->parent_ref = y->parent_ref;
			}
			else x = NULL;
			if (is_root(y))
				root_ref() = x;
			else if (y->is_left_child())
				y->parent_ref->left_ref = x;
			else y->parent_ref->right_ref = x;

			bool y_was_red(y->is_red);
			if (y != z)
			{
//				Instead of exchanging the keys, exchange the pointers in order to really erase z
//				This way iterators to y will not be invalidated, though this operation might be
//				more expensive if the data is smaller than de set of pointers to modify
//				As well, this allows the keys to be constant
//				z->key() = y->key();
				y->parent_ref = z->parent_ref;
				if (z->is_left_child())
					z->parent_ref->left_ref = y;
				else z->parent_ref->right_ref = y;
				y->left_ref = z->left_ref;
				z->left_ref->parent_ref = y;
				y->right_ref = z->right_ref;
				z->right_ref->parent_ref = y;
				y->is_red = z->is_red;
				if (is_root(z))
					root_ref() = y;
			}
			if (!y_was_red)
				erase_fixup(x);
			--d.node_count;
			unbalanced_erase(static_cast<node_ref>(z));
		}

	public:
		void erase(iterator it)
		{ erase(it.x); }

		void erase(const_iterator it)
		{ erase(const_cast<base_node_ref>(it.x)); }

		void erase(iterator first, iterator last)
		{
			if (first.x == first_base_node_ref() && last.x == last_base_node_ref())
			{
				clear();
				return;
			}
			for (; first != last; ++first)
				erase(first.x);
		}

		void erase(const_iterator first, const_iterator last)
		{
			if (first.x == first_base_node_ref() && last.x == last_base_node_ref())
			{
				clear();
				return;
			}
			for (; first != last; ++first)
				erase(const_cast<base_node_ref>(first.x));
		}

		std::size_t erase(const key_type &k)
		{
			base_node_ref x(find_base_node_ref(k));
			if (is_not_nil(x))
			{
				erase(x);
				return 1;
			}
			return 0;
		}

		size_type multi_erase(const key_type &k)
		{
			std::pair<base_node_ref, base_node_ref> bounds(equal_range(k));
			const size_type previous_size(size());
			erase(bounds.first, bounds.second);
			return previous_size - size();
		}

	public:
		void unbalanced_erase(iterator it)
		{ unbalanced_erase(it.x); }

		void unbalanced_erase(const_iterator it)
		{ unbalanced_erase(const_cast<base_node_ref>(it.x)); }

		void erase_if(std::unary_function<const key_type&, bool> &discriminator)
		{
			for (base_node_ref x(first_base_node_ref()); x != last_base_node_ref(); ++x)
				if (discriminator(x->key()))
					erase(x);
		}

		void unbalanced_erase_if(std::unary_function<const key_type&, bool> &discriminator)
		{
			for (base_node_ref x(first_base_node_ref()); x != last_base_node_ref(); ++x)
				if (discriminator(x->key()))
					unbalanced_erase(x);
		}

	private:
		base_node_ref lower_bound_base_node_ref(const key_type &key)
		{
			base_node_ref lb(nil_ref());
			base_node_ref x(root_ref());
			while (is_not_nil(x))
			{
				if (compare(key, x))
				{
					lb = x;
					x = x->left_ref;
				}
				else if (compare(x, key))
					x = x->right_ref;
				else return x;
			}
			return lb;
		}

		base_node_const_ref lower_bound_base_node_const_ref(const key_type &key) const
		{
			base_node_const_ref lb(nil_const_ref());
			base_node_const_ref x(root_ref());
			while (is_not_nil(x))
			{
				if (compare(key, x))
				{
					lb = x;
					x = x->left_ref;
				}
				else if (compare(x, key))
					x = x->right_ref;
				else return x;
			}
			return lb;
		}

		base_node_ref multi_lower_bound_base_node_ref(const key_type &key)
		{
			base_node_ref lb(nil_ref());
			base_node_ref x(root_ref());
			while (is_not_nil(x))
			{
				//If (k > value of x) then search x's right child
				if (compare(x, key))
					x = x->right_ref;
				//Else (value of x <= k) register x as new lower bound and search x's left child
				else
				{
					lb = x;
					x = x->left_ref;
				}
			}
			return lb;
		}

		base_node_const_ref multi_lower_bound_base_node_const_ref(const key_type &key) const
		{
			base_node_const_ref lb(nil_const_ref());
			base_node_const_ref x(root_ref());
			while (is_not_nil(x))
			{
				//If (k > value of x) then search x's right child
				if (compare(x, key))
					x = x->right_ref;
				//Else (value of x <= k) register x as new lower bound and search x's left child
				else
				{
					lb = x;
					x = x->left_ref;
				}
			}
			return lb;
		}

	public:
		iterator lower_bound(const key_type &key)
		{ return iterator(lower_bound_base_node_ref(key)); }

		const_iterator lower_bound(const key_type &key) const
		{ return const_iterator(lower_bound_base_node_const_ref(key)); }

		iterator multi_lower_bound(const key_type &key)
		{ return iterator(multi_lower_bound_base_node_ref(key)); }

		const_iterator multi_lower_bound(const key_type &key) const
		{ return const_iterator(multi_lower_bound_base_node_const_ref(key)); }

	private:
		base_node_ref upper_bound_base_node_ref(const key_type &key)
		{
			base_node_ref ub(nil_ref());
			base_node_ref x(root_ref());
			while (is_not_nil(x))
			{
				if (compare(key, x))
				{
					ub = x;
					x = x->left_ref;
				}
				else if (compare(x, key))
					x = x->right_ref;
				else return x->next_ref();
			}
			return ub;
		}

		base_node_const_ref upper_bound_base_node_const_ref(const key_type &key)
		{
			base_node_const_ref ub(nil_const_ref());
			base_node_const_ref x(root_const_ref());
			while (is_not_nil(x))
			{
				if (compare(key, x))
				{
					ub = x;
					x = x->left_ref;
				}
				else if (compare(x, key))
					x = x->right_ref;
				else return x->next_ref;
			}
			return ub;
		}

		base_node_ref multi_upper_bound_base_node_ref(const key_type &key, base_node_ref ub, base_node_ref x)
		{
			while (is_not_nil(x))
			{
				if (compare(key, x))
				{
					ub = x;
					x = x->left_ref;
				}
				else x = x->right_ref;
			}
			return ub;
		}

		base_node_ref multi_upper_bound_base_node_ref(const key_type &key)
		{ return multi_upper_bound_base_node_ref(key, nil_ref(), root_ref()); }

		base_node_const_ref multi_upper_bound_base_node_const_ref(const key_type &key, base_node_const_ref ub, base_node_const_ref x)
		{
			while (is_not_nil(x))
			{
				if (compare(key, x))
				{
					ub = x;
					x = x->left_ref;
				}
				else x = x->right_ref;
			}
			return ub;
		}

		base_node_const_ref multi_upper_bound_base_node_const_ref(const key_type &key) const
		{ return multi_upper_bound_base_node_const_ref(key, nil_const_ref(), root_const_ref()); }

	public:
		iterator upper_bound(const key_type &key)
		{ return iterator(upper_bound_base_node_ref(key)); }

		const_iterator upper_bound(const key_type &key) const
		{ return const_iterator(upper_bound_base_node_const_ref(key)); }

		iterator multi_upper_bound(const key_type &key)
		{ return iterator(multi_upper_bound_base_node_ref(key)); }

		const_iterator multi_upper_bound(const key_type &key) const
		{ return const_iterator(multi_upper_bound_base_node_const_ref(key)); }

		base_node_ref find_base_node_ref(const key_type &key)
		{
			if (empty())
				return nil_ref();
			base_node_ref x(root_ref());
			while (true)
			{
				if (compare(key, x))
				{
					if (x->has_no_left())
						return nil_ref();
					x = x->left_ref;
					continue;
				}
				if (compare(x, key))
				{
					if (x->has_no_right())
						return nil_ref();
					x = x->right_ref;
					continue;
				}
				return x;
			}
		}

		base_node_const_ref find_base_node_const_ref(const key_type &key) const
		{
			if (empty())
				return nil_const_ref();
			base_node_const_ref x(root_const_ref());
			while (true)
			{
				if (compare(key, x))
				{
					if (x->has_no_left())
						return nil_const_ref();
					x = x->left_ref;
					continue;
				}
				if (compare(x, key))
				{
					if (x->has_no_right())
						return nil_const_ref();
					x = x->right_ref;
					continue;
				}
				return x;
			}
		}

		iterator find(const key_type &key)
		{ return iterator(find_base_node_ref(key)); }

		const_iterator find(const key_type &key) const
		{ return const_iterator(find_base_node_const_ref(key)); }

		size_type count(const key_type &key) const
		{
			if (is_nil(find_base_node_const_ref(key)))
				return 0;
			return 1;
		}

		size_type multi_count(const key_type &key) const
		{
			std::pair<const_iterator, const_iterator> bounds(equal_range(key));
			return std::distance(bounds.first, bounds.second);
		}

	private:
		std::pair<base_node_ref, base_node_ref> equal_range_to_base_node_ref(const key_type &key)
		{
			base_node_ref lb(nil_ref());
			base_node_ref x(root_ref());
			while (is_not_nil(x))
			{
				if (compare(key, x))
				{
					lb = x;
					x = x->left_ref;
				}
				else if (compare(x, key))
					x = x->right_ref;
				else return make_pair(x, x->next_ref());
			}
			return std::make_pair(lb, lb);
		}

		std::pair<base_node_const_ref, base_node_const_ref> equal_range_to_base_node_ref(const key_type &key) const
		{
			base_node_const_ref lb(nil_ref());
			base_node_const_ref x(root_ref());
			while (is_not_nil(x))
			{
				if (compare(key, x))
				{
					lb = x;
					x = x->left_ref;
				}
				else if (compare(x, key))
					x = x->right_ref;
				else return make_pair(x, x->next_ref());
			}
			return std::make_pair(lb, lb);
		}

	public:
		std::pair<iterator, iterator> equal_range(const key_type &key)
		{
			std::pair<base_node_ref, base_node_ref> result(equal_range_to_base_node_ref(key));
			return std::make_pair(iterator(result.first), iterator(result.second));
		}

		std::pair<const_iterator, const_iterator> equal_range(const key_type &key) const
		{
			std::pair<base_node_const_ref, base_node_const_ref> result(equal_range_to_base_node_const_ref(key));
			return std::make_pair(const_iterator(result.first), const_iterator(result.second));
		}

	private:
		std::pair<base_node_ref, base_node_ref> multi_equal_range_to_base_node_ref(const key_type &key)
		{
			base_node_ref lb(nil_ref());
			base_node_ref x(root_ref());
			while (is_not_nil(x))
			{
				if (compare(key, x))
				{
					lb = x;
					x = x->left_ref;
				}
				else if (compare(x, key))
					x = x->right_ref;
				else return make_pair(x, multi_upper_bound_base_node_ref(key, lb, x->right_ref));
			}
			return std::make_pair(lb, lb);
		}

		std::pair<base_node_const_ref, base_node_const_ref> multi_equal_range_to_base_node_const_ref(const key_type &key) const
		{
			base_node_const_ref lb(nil_ref());
			base_node_const_ref x(root_ref());
			while (is_not_nil(x))
			{
				if (compare(key, x))
				{
					lb = x;
					x = x->left_ref;
				}
				else if (compare(x, key))
					x = x->right_ref;
				else return make_pair(x, multi_upper_bound_base_node_const_ref(key, lb, x->right_ref));
			}
			return std::make_pair(lb, lb);
		}

	public:
		std::pair<iterator, iterator> multi_equal_range(const key_type &key)
		{
			std::pair<base_node_ref, bool> result(multi_equal_range_to_base_node_ref(key));
			return std::make_pair(iterator(result.first), result.second);
		}

		std::pair<const_iterator, const_iterator> multi_equal_range(const key_type &key) const
		{
			std::pair<base_node_const_ref, bool> result(multi_equal_range_to_base_node_const_ref(key));
			return std::make_pair(const_iterator(result.first), result.second);
		}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits> &out) const
		{
			for (const_iterator it(begin()); it != end(); ++it)
				out << *it << ' ';
			return out;
		}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& reverse_serialize(std::basic_ostream<CharT, Traits> &out) const
		{
			for (const_reverse_iterator it(rbegin()); it != rend(); ++it)
				out << *it << ' ';
			return out;
		}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& subtree_serialize(std::basic_ostream<CharT, Traits> &out, base_node_const_ref subroot_ref) const
		{
			if (is_nil(subroot_ref))
				return  out;
			subtree_serialize(out, subroot_ref->left_ref);
			out << subroot_ref->key() << ' ';
			subtree_serialize(out, subroot_ref->right_ref);
			return out;
		}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& subtree_serialize(std::basic_ostream<CharT, Traits> &out) const
		{ return subtree_serialize(out, root_ref()); }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& subtree_serialize(std::basic_ostream<CharT, Traits> &out, const_iterator subroot_it) const
		{ return subtree_serialize(out, subroot_it.x); }

		base_node_ref minimum(base_node_ref x)
		{
			while (is_not_nil(x->left_ref))
				x = x->left_ref;
			return x;
		}

		base_node_const_ref minimum(base_node_const_ref x) const
		{
			while (is_not_nil(x->left_ref))
				x = x->left_ref;
			return x;
		}

		base_node_ref maximum(base_node_ref x)
		{
			while (is_not_nil(x->right_ref))
				x = x->right_ref;
			return x;
		}

		base_node_const_ref maximum(base_node_const_ref x) const
		{
			while (is_not_nil(x->right_ref))
				x = x->right_ref;
			return x;
		}

		bool operator== (const rb_tree& t) const
		{ return size() == t.size() && std::equal(begin(), end(), t.begin()); }

		bool operator< (const rb_tree& t) const
		{ return std::lexicographical_compare(begin(), end(), t.begin(), t.end()); }

		bool operator!= (const rb_tree& t) const
		{ return !operator== (t); }

		bool operator> (const rb_tree& t) const
		{ return t.operator< (*this); }

		bool operator<= (const rb_tree& t) const
		{ return !t.operator< (*this); }

		bool operator>= (const rb_tree& t) const
		{ return !operator< (t); }
	};

	template<typename Key, typename Value, typename KeyGetter, typename KeyCompare>
	void swap(rb_tree<Key, Value, KeyGetter, KeyCompare>& x, rb_tree<Key, Value, KeyGetter, KeyCompare>& y)
	{ x.swap(y); }
} //namespace grapenlp

#endif /*GRAPENLP_RB_TREE_H*/
