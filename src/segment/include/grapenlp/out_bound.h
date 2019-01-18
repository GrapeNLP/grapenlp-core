/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2018 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
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

#ifndef GRAPENLP_OUT_BOUND_H
#define GRAPENLP_OUT_BOUND_H

#include <memory>

#include <grapenlp/iostream.h>
#include <grapenlp/trie.h>

namespace grapenlp
{
	template<typename T>
	struct out_bound_const_ref_triplet;

	template<typename T>
	struct out_bound
	{
		typedef out_bound* ref;
		typedef out_bound const * const_ref;
		typedef array<T> t_array;
		typedef trie_with_ptr_data<T, out_bound_const_ref_triplet<T> > trie;
		typedef typename trie::string name_string;
		typedef typename trie::string::const_ref name_string_const_ref;

		name_string_const_ref name;
		bool left;
		bool right;

		out_bound(name_string_const_ref name_, bool left_, bool right_): name(name_), left(left_), right(right_)
		{}

		out_bound(const out_bound &ob): name(ob.name), left(ob.left), right(ob.right)
		{}

		bool operator< (const out_bound &ob) const
		{
			if (name < ob.name)
				return true;
			if (ob.name < name)
				return false;
			if (left < ob.left)
				return true;
			if (ob.left < left)
				return false;
			return right < ob.right;
		}

		std::ptrdiff_t compare_3w(const out_bound &ob) const
		{
			std::ptrdiff_t result(static_cast<std::ptrdiff_t>(this->name) - static_cast<std::ptrdiff_t>(ob.name));
			if (result)
				return result;
			if ((result = static_cast<std::ptrdiff_t>(this->left) - static_cast<std::ptrdiff_t>(ob.left)))
				return result;
			return (static_cast<std::ptrdiff_t>(this->right) - static_cast<std::ptrdiff_t>(ob.right));
		}

		out_bound& operator= (const out_bound &ob)
		{
			name = ob.name;
			left = ob.left;
			right = ob.right;
			return *this;
		}

		bool operator== (const out_bound &ob)
		{ return name == ob.name && left == ob.left && right == ob.right; }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
		{
			if (left)
			{
				//Empty bound
				if (right)
					return name->serialize(out << '<') << "/>";
				return name->serialize(out << '<') << '>';
			}
			return name->serialize(out << "</") << '>';
		}
	};

	//Possible out bounds for a given name: left, right and both
	//Initially it does not build the bounds but contains 3 NULL smart pointers
	//When asked for a bound, it builds it if not already done and returns it
	//Upon destruction, smart pointers destroy the constructed out bounds
	template<typename T>
	struct out_bound_const_ref_triplet
	{
		typedef typename out_bound<T>::name_string_const_ref name_string_const_ref;
		std::unique_ptr<const out_bound<T> > left_ref, right_ref, both_ref;

		out_bound_const_ref_triplet(): left_ref(), right_ref(), both_ref()
		{}

		typename out_bound<T>::const_ref get(name_string_const_ref name, bool left, bool right)
		{
			if (left)
			{
				if (right)
				{
					if (!both_ref.get())
						both_ref.reset(new out_bound<T>(name, true, true));
					return both_ref.get();
				}
				if (!left_ref.get())
					left_ref.reset(new out_bound<T>(name, true, false));
				return left_ref.get();
			}
			if (!right_ref.get())
				right_ref.reset(new out_bound<T>(name, false, true));
			return right_ref.get();
		}
	};

	template<typename T, typename CharT, typename Traits>
	inline std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits>& out, const out_bound<T> &ob)
	{ return ob.serialize(out); }
} //namespace grapenlp

#endif /*GRAPENLP_OUT_BOUND*/
