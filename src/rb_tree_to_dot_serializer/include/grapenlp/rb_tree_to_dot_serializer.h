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

#ifndef GRAPENLP_RB_TREE_TO_DOT_SERIALIZER_H
#define GRAPENLP_RB_TREE_TO_DOT_SERIALIZER_H
#include <ostream>
#include <string>
#include <algorithm>
#include <grapenlp/tag_serializer_traits.h>
#include <grapenlp/rb_tree.h>

namespace grapenlp
{
	template<typename Key, typename ValueSerializer, typename KeyGetter, typename Compare, typename Allocator>
	struct rb_tree_to_dot_serializer
	{
		typedef Key key_type;
		typedef ValueSerializer value_serializer;

		typedef typename serializer_traits<value_serializer>::elem_type value_type;
		typedef rb_tree<key_type, value_type, KeyGetter, Compare, Allocator> elem_type;

		typedef elem_type tree;
		typedef typename tree::base_node_const_ref base_node_const_ref;

	protected:
		value_serializer vs;

	public:
		rb_tree_to_dot_serializer(): vs()
		{}

		rb_tree_to_dot_serializer(const ValueSerializer &vs_): vs(vs_)
		{}

	private:
		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_node_label(std::basic_ostream<CharT, Traits>& out, std::size_t node_count)
		{ return out << "\"q" << node_count << '"'; }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_subtree(std::basic_ostream<CharT, Traits>& out, base_node_const_ref x, std::size_t &node_count)
		{
			serialize_node_label(out, node_count) << " [label = \"";
			vs(out, x->value()) << '\"';
			if (x->is_red)
				out << ", fillcolor = red";
			out << "];" << std::endl;

			if (x->is_leaf())
				return out;
			std::size_t my_node_count(node_count);
			if (x->has_left())
			{
				serialize_node_label(out, node_count) << " -> ";
				serialize_node_label(out, ++node_count) << "[tailport = sw, headport = ne];" << std::endl;
				serialize_subtree(out, x->left_ref, node_count);
			}
			else
			{
				serialize_node_label(out, node_count) << " -> ";
				serialize_node_label(out, ++node_count) << "[style = invis];" << std::endl;
				serialize_node_label(out, node_count) << " [style = invis];" << std::endl;
			}
			if (x->has_right())
			{
				serialize_node_label(out, my_node_count) << " -> ";
				serialize_node_label(out, ++node_count) << "[tailport = se, headport = nw];" << std::endl;
				serialize_subtree(out, x->right_ref, node_count);
			}
			else
			{
				serialize_node_label(out, my_node_count) << " -> ";
				serialize_node_label(out, ++node_count) << "[style = invis];" << std::endl;
				serialize_node_label(out, node_count) << " [style = invis];" << std::endl;
			}
			return out;
		}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize_subtree(std::basic_ostream<CharT, Traits>& out, base_node_const_ref x)
		{
			std::size_t node_count(0);
			return serialize_subtree(out, x, node_count);
		}

	public:
		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& operator() (std::basic_ostream<CharT, Traits>& out, const char *name, const elem_type &t)
		{
			out << "digraph " << name << " {" << std::endl;
//			out << "rankdir = LR;" << std::endl;
			out << "ranksep = 0.25;" << std::endl;
			out << "nodesep = 0.25;" << std::endl;
//			out << "size = \"8,5\";" << std::endl;
			out << "node [fillcolor = black, fontcolor = white, style = filled];" << std::endl;

			if (t.empty())
				return out;
			serialize_subtree(out, t.root_const_ref());
			return out << '}' << std::endl;
		}
	};

	template<typename Key, typename Value, typename KeyGetter, typename Compare, typename Allocator, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& rb_tree_to_dot_serialize(std::basic_ostream<CharT, Traits>& out, const char *name, const rb_tree<Key, Value, KeyGetter, Compare, Allocator> &t)
	{ return rb_tree_to_dot_serializer<Key, typename tag_serializer_traits<Value>::type, KeyGetter, Compare, Allocator>()(out, name, t); }

	template<typename Key, typename ValueSerializer, typename KeyGetter, typename Compare, typename Allocator, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& rb_tree_to_dot_serialize(std::basic_ostream<CharT, Traits>& out, const char *name, const rb_tree<Key, typename serializer_traits<ValueSerializer>::elem_type, KeyGetter, Compare, Allocator> &t, const ValueSerializer &vs)
	{ return rb_tree_to_dot_serializer<Key, ValueSerializer, KeyGetter, Compare, Allocator>(vs)(out, name, t); }
} //namespace grapenlp

#endif /*GRAPENLP_RB_TREE_TO_DOT_SERIALIZER_H*/
