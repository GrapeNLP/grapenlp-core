/*
 * GRAPE
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

#ifndef GRAPE_ALGORITHM_H
#define GRAPE_ALGORITHM_H

#include <iterator>
#include <string>
#include <algorithm>
#include <set>
#include <grape/functional.h>

namespace grape
{
	//Generalization of function strcmp
	//Performs lexicographical comparison between two ranges r1 and r2 and returns -1 if r1 < r2, 0 if r1 == r2 and 1 if r1 > r2
	template <typename InputIterator1, typename InputIterator2, typename Compare3W = compare_3w<typename std::iterator_traits<InputIterator1>::value_type> >
	struct lexicographical_comparator_3way
	{
		std::ptrdiff_t operator() (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
		{
			std::ptrdiff_t result;
			while (first1 != last1 && first2 != last2)
			{
				if ((result = Compare3W()(*first1, *first2)))
					return result;
				++first1;
				++first2;
			}
			return static_cast<std::ptrdiff_t>(first2 == last2) - static_cast<std::ptrdiff_t>(first1 == last1);
		}
	};

	template <typename InputIterator1, typename InputIterator2>
	inline std::ptrdiff_t lexicographical_compare_3way(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{ return lexicographical_comparator_3way<InputIterator1, InputIterator2>()(first1, last1, first2, last2); }

	template<typename InputIterator1, typename InputIterator2>
	std::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2 && *first1 == *first2)
		{
			++first1;
			++first2;
		}
		return std::make_pair(first1, first2);
	}

	template<typename InputIterator1, typename InputIterator2, typename UnaryPredicate>
	std::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, UnaryPredicate unary_pred)
	{
		while (first1 != last1 && first2 != last2 && unary_pred(*first1) == *first2)
		{
			++first1;
			++first2;
		}
		return std::make_pair(first1, first2);
	}

	template<typename InputIterator1, typename InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (true)
		{
			if (first1 == last1)
				return first2 == last2;
			if (first2 == last2)
				return false;
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
	}

	template<typename InputIterator1, typename InputIterator2, typename UnaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, UnaryPredicate unary_pred)
	{
		while (true)
		{
			if (first1 == last1)
				return first2 == last2;
			if (first2 == last2)
				return false;
			if (unary_pred(*first1) != *first2)
				return false;
			++first1;
			++first2;
		}
	}

	//Return whether the concatenation of the first and second ranges is equal to the third range
	template<typename InputIterator1, typename InputIterator2, typename InputIterator3>
	inline bool concat_equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, InputIterator3 first3, InputIterator3 last3)
	{
		while (true)
		{
			//If first range empty, return whether the second and third ranges are equal or not
			if (first1 == last1)
				return equal(first2, last2, first3, last3);
			//If third range is empty, it is not equal since the first range is not empty
			if (first3 == last3)
				return false;
			//If the first chars of the first and third ranges are not equal, then return false
			if (*first1 != *first3)
				return false;
			//Skip first chars of first and third ranges
			++first1;
			++first3;
		}
	}

	//Removes the sorted range [begin, end) from set s1
	template<typename T, typename Iterator>
	std::set<T>& set_substraction(std::set<T> &s, Iterator begin, Iterator end)
	{
		typename std::set<T>::iterator i(s.begin());
		do
		{
			//If there are no more elements to substract, return
			if (begin == end)
				return s;
			//Advance set iterator to the next element to substract, or the less element greater than the element to substract
			i = std::lower_bound(i, s.end(), *begin);
			//If end of set reached (every element to substract is greater than the elements of the set), return
			if (i == s.end())
				return s;
			//If the set iterator points to the current element to substract, erase it from the set
			if (*i == *begin)
				s.erase(i);
			//Go for the next element to substract
			++begin;
		} while (true);
	}

	template<typename T, typename Iterator>
	inline bool includes(Iterator begin, Iterator end, T elem)
	{ return std::find(begin, end, elem) != end; }

	inline bool includes(const std::string &s1, const char *s2)
	{ return s1.find(s2) != std::string::npos; }

	inline bool includes(const std::string &s1, const std::string &s2)
	{ return s1.find(s2) != std::string::npos; }

	inline bool includes(const char* elems, char elem)
	{
		while (*elems != '\0' && *elems != elem)
			++elems;
		return *elems == elem;
	}

	inline bool includes(const wchar_t* elems, wchar_t elem)
	{
		while (*elems != L'\0' && *elems != elem)
			++elems;
		return *elems == elem;
	}

	template<typename T, typename Iterator>
	inline bool excludes(Iterator begin, Iterator end, T elem)
	{ return !includes(begin, end, elem); }

	//Test whether two sorted ranges are disjoint (do not have any common element)
	template<typename Iterator1, typename Iterator2>
	bool disjoint(Iterator1 begin1, Iterator1 end1, Iterator2 begin2, Iterator2 end2)
	{
		while (begin2 != end2 && begin1 != end1)
		{
			//Advance iterator begin1 up to the lowest element being equal or greater than the element pointed by iterator begin2
			begin1 = std::lower_bound(begin1, end1, *begin2);
			//If both elements are equal, the first range does not exclude the second one: return false
			if (*begin1 == *begin2)
				return false;
			//Element pointed by begin2 is excluded from first range: check next element
			++begin2;
		}
		//All elements in range2 have been checked to be excluded from range1: return true
		return true;
	}

	template<typename Iterator1, typename Iterator2>
	bool starts_with(Iterator1 lemma_begin, Iterator1 lemma_end, Iterator2 prefix_begin, Iterator2 prefix_end)
	{
		while (lemma_begin != lemma_end && prefix_begin != prefix_end && *lemma_begin == *prefix_begin)
		{
			++lemma_begin;
			++prefix_begin;
		}
		return prefix_begin == prefix_end;
	}

	template<typename CharT, std::size_t N, typename Iterator>
	inline bool starts_with(CharT lemma[N], Iterator suffix_begin, Iterator suffix_end)
	{ return starts_with(lemma, lemma + N, suffix_begin, suffix_end); }

	template<typename Iterator, typename CharT, typename std::size_t N>
	bool starts_with(Iterator lemma_begin, Iterator lemma_end, const CharT suffix[N])
	{ return starts_with(lemma_begin, lemma_end, suffix, suffix + N); }

	template<typename CharT1, std::size_t M, typename CharT2, std::size_t N>
	inline bool starts_with(const CharT1 lemma[M], const CharT2 suffix[N])
	{ return starts_with(lemma, lemma + M, suffix, suffix + N); }

	template<typename CharT, typename Traits>
	inline bool starts_with(const std::basic_string<CharT, Traits> &s1, const std::basic_string<CharT, Traits> &s2)
	{ return starts_with<typename std::basic_string<CharT, Traits>::const_iterator, typename std::basic_string<CharT, Traits>::const_iterator>(s1.begin(), s1.end(), s2.begin(), s2.end()); }

	template<typename CharT, typename Traits, typename std::size_t N>
	inline bool starts_with(const std::basic_string<CharT, Traits> &s, const CharT suffix[N])
	{ return starts_with<std::basic_string<CharT, Traits>::const_iterator, CharT, N>(s.begin(), s.end(), suffix); }

	template<typename std::size_t N>
	inline bool starts_with(const std::string &s, const char suffix[N])
	{ return starts_with<char, std::char_traits<char>, N>(s.begin(), s.end(), suffix); }

	template<typename std::size_t N>
	inline bool starts_with(const std::wstring &s, const char suffix[N])
	{ return starts_with<wchar_t, std::char_traits<wchar_t>, N>(s.begin(), s.end(), suffix); }

	//Computes if a sequence has another sequence as suffix;
	//Comparisons are computed in reverse order, thus end iterators must accept the operator --
	//The end iterator of the first sequence is passed by reference so after the call
	//it will point to the last compared element (the first element to differ
	//or the element corresponding to the first element of the suffix)
	template<typename Iterator1, typename Iterator2>
	bool ends_with(Iterator1 lemma_begin, Iterator1 lemma_end, Iterator2 suffix_begin, Iterator2 suffix_end)
	{
		//If empty suffix, return true (every string has an empty suffix)
		if (suffix_begin == suffix_end)
			return true;
		//If empty lemma but non-empty suffix, return false (empty strings contain no other suffix than the empty suffix)
		if (lemma_begin == lemma_end)
			return false;
		--lemma_end;
		--suffix_end;
		//Compare non-empty lemma and suffix
		while (*lemma_end == *suffix_end && suffix_end != suffix_begin && lemma_end != lemma_begin)
		{
			--lemma_end;
			--suffix_end;
		}
		//Return true iff last compared chars match and every suffix char has been matched
		return *lemma_end == *suffix_end && suffix_end == suffix_begin;
	}

	template<typename CharT, std::size_t N, typename Iterator>
	inline bool ends_with(CharT lemma[N], Iterator suffix_begin, Iterator suffix_end)
	{ return ends_with(lemma, lemma + N, suffix_begin, suffix_end); }

	template<typename Iterator, typename CharT, typename std::size_t N>
	bool ends_with(Iterator lemma_begin, Iterator lemma_end, const CharT suffix[N])
	{ return ends_with(lemma_begin, lemma_end, suffix, suffix + N); }

	template<typename CharT1, std::size_t M, typename CharT2, std::size_t N>
	inline bool ends_with(const CharT1 lemma[M], const CharT2 suffix[N])
	{ return ends_with(lemma, lemma + M, suffix, suffix + N); }

	//Appends to a container an "encapsulated" copy of a sequence, that is,
	//the resulting copy will start with a left delimiter, end with a right delimiter and
	//every char inside the sequence equal to either the left or right delimited
	//will be preceded by the escape char
	//For instance, let ` and ' be the left and right delimiters and \ the escape char:
	//abc`def'ghi is copied as `abc\`def\'ghi'
	template<typename InputIterator, typename OutputContainer>
	void encapsulate(InputIterator input_begin, InputIterator input_end, OutputContainer &output_container, typename std::iterator_traits<InputIterator>::value_type left_delimiter, typename std::iterator_traits<InputIterator>::value_type right_delimiter, typename std::iterator_traits<InputIterator>::value_type escape_char)
	{
		typename std::iterator_traits<InputIterator>::value_type c;
		for (; input_begin != input_end; ++input_begin)
		{
			if (*input_begin == right_delimiter || *input_begin == escape_char)
				output_container.pushback(escape_char);
			output_container.pushback(*input_begin);
		}
		output_container.pushback(right_delimiter);
	}

	//Appends to a container a escaped copy of a sequence, that is, every special char will be preceded by the escape char
	template<typename InputIterator, typename OutputContainer, typename SpecialCharIterator>
	void escape_special_chars(InputIterator input_begin, InputIterator input_end, OutputContainer &output_container, SpecialCharIterator special_char_begin, SpecialCharIterator special_char_end, typename std::iterator_traits<InputIterator>::value_type escape_char)
	{
		//Reserve at least twice the size of the original input sequence: the worst case resulting size
		output_container.reserve(2*std::distance(input_begin, input_end));
		for (; input_begin != input_end; ++input_begin)
		{
			//If the current char is special, append escape char
			if (contains(special_char_begin, special_char_end, *input_begin))
				output_container.pushback(escape_char);
			//Append current char
			output_container.pushback(*input_begin);
		}
		//Free the unused space
		output_container.reserve(output_container.size());
	}
} //namespace grape

#endif /*GRAPE_ALGORITHM_H*/
