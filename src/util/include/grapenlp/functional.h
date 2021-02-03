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

#ifndef GRAPENLP_FUNCTIONAL_H
#define GRAPENLP_FUNCTIONAL_H

#include <type_traits>

#include <utility>
#include <functional>
#include <grapenlp/counter.h>

namespace grapenlp
{
	struct no_op
	{
		template<typename T>
		void operator() (__attribute__((unused)) const T &t) const
		{}
	};

	template <typename Result>
	struct constant_function
	{ typedef Result result_type; };

	struct false_func: public constant_function<bool>
	{
		bool operator() () const
		{ return false; }
	};

	struct true_func: public constant_function<bool>
	{
		bool operator() () const
		{ return true; }
	};

	template<typename T>
	struct zero_func: public constant_function<T>
	{
		T operator() () const
		{ return static_cast<T>(0); }
	};

	template<typename T>
	struct one_func: public constant_function<T>
	{
		T operator() () const
		{ return static_cast<T>(1); }
	};

/*	template<typename ParamType, ParamType value>
	struct param_value_getter
	{
		typedef ParamType value_type;

		ParamType operator() () const
		{ return value; }
	};



	template<typename ValueGetter>
	struct value_getter_traits
	{};

	template<typename ParamType, ParamType value>
	struct value_getter_traits<param_value_getter<ParamType, value> >
	{ typedef ParamType value_type;	};

	typedef param_value_getter<bool, false> false_getter;
	typedef param_value_getter<bool, false> true_getter;
	typedef param_value_getter<std::size_t, 0> zero_size_t_getter;
*/
	template<typename T>
	struct identity: public std::unary_function<T, T>
	{
		T& operator()(T& a) const
		{ return a; }

		const T& operator() (const T& a) const
		{ return a; }
	};

	template<typename SizeType>
	struct counter_incrementer
	{
		counter<SizeType> the_counter;

		void operator() ()
		{ the_counter.inc(); }
	};

	//3-way comparator (returns -1 iff a < b, 1 iff b < a and 0 iff a == b); requires class T to define method "compare_3w"
	template<typename T, bool = std::is_class<T>::value>
	struct compare_3w: public std::binary_function<T, T, std::ptrdiff_t>
	{};

	//3-way comparator for class objects calls their compare_3w method by default
	template<typename T>
	struct compare_3w<T, true>: public std::binary_function<T, T, std::ptrdiff_t>
	{
		int operator() (const T& a, const T& b) const
		{ return a.compare_3w(b); }
	};

	//3-way comparator for pair objects
	template<typename T1, typename T2>
	struct compare_3w<std::pair<T1, T2>, true>: public std::binary_function<std::pair<T1, T2>, std::pair<T1, T2>, std::ptrdiff_t>
	{
		int operator() (const std::pair<T1, T2> &a, const std::pair<T1, T2> &b) const
		{
			std::ptrdiff_t result(compare_3w<T1>()(a.first, b.first));
			if (result)
				return result;
			return compare_3w<T2>()(a.second, b.second);
		}
	};

	//3-way comparator for simple data
	template<typename T>
	struct compare_3w<T, false>: public std::binary_function<T, T, std::ptrdiff_t>
	{
		int operator() (const T& a, const T& b) const
		{ return static_cast<std::ptrdiff_t>(a) - static_cast<std::ptrdiff_t>(b); }
	};

	//3-way comparator for pointers
	template<typename T>
	struct compare_3w<T*, false>: public std::binary_function<T*, T*, std::ptrdiff_t>
	{
		int operator() (const T* a, const T* b) const
		{ return reinterpret_cast<std::ptrdiff_t>(a) - reinterpret_cast<std::ptrdiff_t>(b); }
	};

	//3-way comparator for pointers to const objects
	template<typename T>
	struct compare_3w<T const *, false>: public std::binary_function<T const *, T const *, std::ptrdiff_t>
	{
		int operator() (const T* a, const T* b) const
		{ return reinterpret_cast<std::ptrdiff_t>(a) - reinterpret_cast<std::ptrdiff_t>(b); }
	};

	//3-way comparator for const pointers
	template<typename T>
	struct compare_3w<T* const, false>: public std::binary_function<T* const, T* const, std::ptrdiff_t>
	{
		int operator() (const T* a, const T* b) const
		{ return reinterpret_cast<std::ptrdiff_t>(a) - reinterpret_cast<std::ptrdiff_t>(b); }
	};

	//3-way comparator for const pointers to const objects
	template<typename T>
	struct compare_3w<T const * const, false>: public std::binary_function<T const * const, T const * const, std::ptrdiff_t>
	{
		int operator() (const T* a, const T* b) const
		{ return reinterpret_cast<std::ptrdiff_t>(a) - reinterpret_cast<std::ptrdiff_t>(b); }
	};

	//3-way comparator of object references
	template<typename T>
	struct ref_compare_3w: public std::binary_function<T, T, int>
	{
		int operator() (const T &a, const T &b) const
		{ return compare_3w<T*, false>()(&a, &b); };
	};

//Comparators of referenced objects
//Useful for containers of pointers in order to compare pointed values instead of value addresses
	template<typename reference_type>
	struct deref_less: public std::binary_function<reference_type, reference_type, bool>
	{
		bool operator() (const reference_type& a, const reference_type& b) const
		{ return *a < *b; }
	};

	template<typename reference_type>
	struct deref_less_equal: public std::binary_function<reference_type, reference_type, bool>
	{
		bool operator() (const reference_type& a, const reference_type& b) const
		{ return *a <= *b; }
	};

	template<typename reference_type>
	struct deref_equal_to: public std::binary_function<reference_type, reference_type, bool>
	{
		bool operator() (const reference_type& a, const reference_type& b) const
		{ return *a == *b; }
	};

	template<typename reference_type>
	struct deref_greater: public std::binary_function<reference_type, reference_type, bool>
	{
		bool operator() (const reference_type& a, const reference_type& b) const
		{ return *a > *b; }
	};

	template<typename reference_type>
	struct deref_greater_equal: public std::binary_function<reference_type, reference_type, bool>
	{
		bool operator() (const reference_type& a, const reference_type& b) const
		{ return *a >= *b; }
	};

	//Comparators of object references
	//Useful for object pools where each object is unique (e.g.: strings represented by a trie), thus x == y iff &x == &y
	template<typename T>
	struct ref_less: public std::binary_function<T, T, bool>
	{
		bool operator() (const T& a, const T& b) const
		{ return &a < &b; }
	};

	template<typename T>
	struct ref_less_equal: public std::binary_function<T, T, bool>
	{
		bool operator() (const T& a, const T& b) const
		{ return &a <= &b; }
	};

	template<typename T>
	struct ref_equal_to: public std::binary_function<T, T, bool>
	{
		bool operator() (const T& a, const T& b) const
		{ return &a == &b; }
	};

	template<typename T>
	struct ref_greater: public std::binary_function<T, T, bool>
	{
		bool operator() (const T& a, const T& b) const
		{ return &a > &b; }
	};

	template<typename T>
	struct ref_greater_equal: public std::binary_function<T, T, bool>
	{
		bool operator() (const T& a, const T& b) const
		{ return &a >= &b; }
	};


	template<typename T>
	struct assign: public std::binary_function<T&, const T&, T&>
	{
		T& operator() (T& a, const T& b) const
		{ return a = b; }
	};

	template<typename T>
	struct ref_assign: public std::binary_function<T*, T&, T*>
	{
		T* operator() (T* a, T& b) const
		{ return a = &b; }
	};

	template<typename T>
	struct deref: public std::unary_function<T*, T&>
	{
		T& operator() (T* a) const
		{ return *a; }
	};


	template<typename T>
	struct ref: public std::unary_function<T&, T*>
	{
		T* operator() (T &a) const
		{ return &a; }
	};

	template<typename T>
	struct deleter
	{
		void operator() (T *p) const
		{ delete p; }
	};

	template<typename First, typename Second>
	struct pair_first: public std::unary_function<std::pair<First, Second>, First>
	{
		First& operator() (std::pair<First, Second> &p) const
		{ return p.first; }

		const First& operator() (const std::pair<First, Second> &p) const
		{ return p.first; }
	};

	template<typename First, typename Second>
	struct pair_second: public std::unary_function<std::pair<First, Second>, First>
	{
		First& operator() (std::pair<First, Second> &p) const
		{ return p.second; }

		const First& operator() (const std::pair<First, Second> &p) const
		{ return p.second; }
	};
} //namespace grapenlp

#endif /*GRAPENLP_FUNCTIONAL_H*/
