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

#ifndef GRAPENLP_SEGMENT_H
#define GRAPENLP_SEGMENT_H

#include <map>

#include <grapenlp/functional.h>
#include <grapenlp/algorithm.h>
#include <grapenlp/map_impl_selector.h>
#include <grapenlp/set_impl_selector.h>
#include <grapenlp/trie.h>
#include <grapenlp/out_bound.h>
#include <grapenlp/token.h>
namespace grapenlp
{
	template<typename SourceRef>
	class segment
	{
#ifdef TRACE
		SourceRef input_begin;
#endif
		SourceRef begin;
		bool begin_defined_flag;
		SourceRef end;
		bool end_defined_flag;

	public:
#ifdef TRACE
		segment(): input_begin(), begin(), begin_defined_flag(), end(), end_defined_flag()
		{}
		segment(SourceRef input_begin_, SourceRef begin_, bool begin_defined_flag_, SourceRef end_, bool end_defined_flag_): input_begin(input_begin_), begin(begin_), begin_defined_flag(begin_defined_flag_), end(end_), end_defined_flag(end_defined_flag_)
		{}
		segment(const segment &s): input_begin(s.input_begin), begin(s.begin), begin_defined_flag(s.begin_defined_flag), end(s.end), end_defined_flag(s.end_defined_flag)
		{}
#else
		segment(): begin(), begin_defined_flag(), end(), end_defined_flag()
		{}
		segment(SourceRef begin_, bool begin_defined_flag_, SourceRef end_, bool end_defined_flag_): begin(begin_), begin_defined_flag(begin_defined_flag_), end(end_), end_defined_flag(end_defined_flag_)
		{}
		segment(const segment &s): begin(s.begin), begin_defined_flag(s.begin_defined_flag), end(s.end), end_defined_flag(s.end_defined_flag)
		{}
#endif
#ifdef TRACE
		SourceRef get_input_begin() const
		{ return input_begin; }

		void set_input_begin(SourceRef input_begin_)
		{ input_begin = input_begin_; }
#endif
		SourceRef get_begin() const
		{ return begin; }

		void set_begin(SourceRef begin_)
		{
			begin = begin_;
			begin_defined_flag = true;
		}

		SourceRef get_end() const
		{ return end; }

		void set_end(SourceRef end_)
		{
			end = end_;
			end_defined_flag = true;
		}

		bool is_begin_defined() const
		{ return begin_defined_flag; }

		bool is_end_defined() const
		{ return end_defined_flag; }

		bool is_fully_defined() const
		{ return begin_defined_flag && end_defined_flag; }

		bool operator< (const segment<SourceRef> &s) const
		{
			if (begin_defined_flag < s.begin_defined_flag)
				return true;
			if (s.begin_defined_flag < begin_defined_flag)
				return false;
			if (end_defined_flag < s.end_defined_flag)
				return true;
			if (s.end_defined_flag < end_defined_flag)
				return false;
			if (begin < s.begin)
				return true;
			if (s.begin < begin)
				return false;
			return end < s.end;
		}

		std::ptrdiff_t compare_3w(const segment<SourceRef> &s) const
		{
			std::ptrdiff_t result(static_cast<std::ptrdiff_t>(this->begin_defined_flag) - static_cast<std::ptrdiff_t>(s.begin_defined_flag));
			if (result)
				return result;
			if ((result = static_cast<std::ptrdiff_t>(this->end_defined_flag) - static_cast<std::ptrdiff_t>(s.end_defined_flag)))
				return result;
			if ((result = static_cast<std::ptrdiff_t>(this->begin -  s.begin)))
				return result;
			return static_cast<std::ptrdiff_t>(this->end -  s.end);
		}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
		{
			if (is_begin_defined())
				out << '[';
			else out << '(';
#ifdef TRACE
			out << std::distance(get_input_begin(), get_begin()) << ", " << std::distance(get_input_begin(), get_end());
#else
			out << *get_begin() << ", " << *get_end();
#endif
			if (is_end_defined())
				return out << ']';
			else return out << ')';
			return out;
		}
	};

	template<typename SourceRef, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits>& out, const segment<SourceRef> &s)
	{ return s.serialize(out); }

	template<typename SourceRef, typename Id, assoc_container_impl_choice acic>
	class segment_map: public map_impl_selector<acic, typename out_bound<Id>::name_string_const_ref, segment<SourceRef> >::type
	{
	public:
		typedef typename map_impl_selector<acic, typename out_bound<Id>::name_string_const_ref, segment<SourceRef> >::type base_type;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::iterator iterator;
		typedef typename base_type::const_iterator const_iterator;

		segment_map(): base_type()
		{}

		bool has_key(typename out_bound<Id>::name_string_const_ref key) const
		{ return this->find(key) != this->end(); }

		segment_map& insert(SourceRef src_ref, SourceRef begin_src_ref, SourceRef end_src_ref, const out_bound<Id> &ob)
		{
//#ifdef TRACE
//			std::wcout << L"Inserting out_bound " << ob << std::endl;
//#endif
			iterator i(this->lower_bound(ob.name));
			//If there is no other bound with the same name
			if (i == this->end() || i->first != ob.name)
			{
				//Insert left-open/right-closed segment
				if (!ob.left)
#ifdef TRACE
					base_type::insert(i, value_type(ob.name, segment<SourceRef>(begin_src_ref, begin_src_ref, false, src_ref, true)));
#else
					base_type::insert(i, value_type(ob.name, segment<SourceRef>(begin_src_ref, false, src_ref, true)));
#endif
				//Insert closed empty segment
				else if (ob.right)
#ifdef TRACE
					base_type::insert(i, value_type(ob.name, segment<SourceRef>(begin_src_ref, src_ref, true, src_ref, true)));
#else
					base_type::insert(i, value_type(ob.name, segment<SourceRef>(src_ref, true, src_ref, true)));
#endif
				//Insert left-closed/right-open segment
#ifdef TRACE
				else base_type::insert(i, value_type(ob.name, segment<SourceRef>(begin_src_ref, src_ref, true, end_src_ref, false)));
#else
				else base_type::insert(i, value_type(ob.name, segment<SourceRef>(src_ref, true, end_src_ref, false)));
#endif
				return *this;
			}
			//If segment's right bound is undefined and new bound is a right bound, close segment's right bound
			if (!i->second.is_end_defined() && !ob.left)
				i->second.set_end(src_ref);
			return *this;
		}

		segment_map& converse_insert(SourceRef src_ref, SourceRef begin_src_ref, SourceRef end_src_ref, const out_bound<Id> &ob)
		{
//#ifdef TRACE
//			std::wcout << L"Inserting out_bound " << ob << std::endl;
//#endif
			iterator i(this->lower_bound(ob.name));
			//If there is no other bound with the same name
			if (i == this->end() || i->first != ob.name)
			{
				//Insert left-closed/right-open segment
				if (!ob.right)
#ifdef TRACE
					base_type::insert(i, value_type(ob.name, segment<SourceRef>(begin_src_ref, src_ref, true, end_src_ref, false)));
#else
					base_type::insert(i, value_type(ob.name, segment<SourceRef>(src_ref, true, end_src_ref, false)));
#endif
				//Insert closed empty segment
				else if (ob.left)
#ifdef TRACE
					base_type::insert(i, value_type(ob.name, segment<SourceRef>(begin_src_ref, src_ref, true, src_ref, true)));
#else
					base_type::insert(i, value_type(ob.name, segment<SourceRef>(src_ref, true, src_ref, true)));
#endif
				//Insert left-open/right-closed segment
#ifdef TRACE
				else base_type::insert(i, value_type(ob.name, segment<SourceRef>(begin_src_ref, begin_src_ref, false, src_ref, true)));
#else
				else base_type::insert(i, value_type(ob.name, segment<SourceRef>(begin_src_ref, false, src_ref, true)));
#endif
				return *this;
			}
			//If segment's left bound is undefined and new bound is a left bound, close segment's left bound
			if (!i->second.is_begin_defined() && !ob.right)
				i->second.set_begin(src_ref);
			return *this;
		}

		//This is for the composer; no need for an unweighted converse version, for now
		segment_map& insert(const segment_map &sm)
		{
			if (sm.empty())
				return *this;
			//Set sm's position to the first segment
			const_iterator j(sm.begin());
			//Search insertion point in *this for first sm's segment
			iterator i = base_type::lower_bound(j->first);

			//If insertion point is not yet at the end
			while (i != this->end())
			{
				//If sm's segment is not present in *this
				if (i->first != j->first)
					base_type::insert(i, value_type(j->first, segment<SourceRef>(j->second)));
				//Else if *this segment is right open and sm segment is right closed, close also *this segment's right bound
				else if (!i->second.is_end_defined() && !j->second.is_begin_defined())
					i->second.set_end(j->second.get_end());
				//Advance to next sm's segment
				++j;
				//If there are no more segments to insert, return
				if (j == sm.end())
					return *this;
				//Else search for new corresponding insertion point in *this
				i = base_type::lower_bound(j->first);
			}
			//Insert remaining sm segments at the end of *this
			do
			{ base_type::insert(this->end(), value_type(j->first, segment<SourceRef>(j->second))); }
			while (++j != sm.end());
			return *this;
		}

		bool operator< (const segment_map &sm) const
		{
			const_iterator i1(this->begin());
			const_iterator i2(sm.begin());

			while (true)
			{
				if (i1 == this->end())
				{
					//Equal
					if (i2 == sm.end())
						return false;
					//Less: this segment_map has less segments than sm
					return true;
				}
				if (i2 == sm.end())
					//Greater: this segment_map has more segments than sm
					return false;
				//Current segment name of this segment_map is different than the one of sm: return this_segment_name less_than sm_segment_name
				if (i1->first < i2->first)
					return true;
				if (i2->first < i1->first)
					return false;
				if (i1->second < i2->second)
					//Less: current segment bounds of this segment_map are less than the ones of sm
					return true;
				if (i2->second < i1->second)
					//Greater: current segment bounds of this segment_map are greater than the ones of sm
					return false;
				//Advance to next pair of segments
				++i1;
				++i2;
			}
		}

		std::ptrdiff_t compare_3w(const segment_map &sm) const
		{ return lexicographical_compare_3way(this->begin(), this->end(), sm.begin(), sm.end()); }

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
		{
			if (this->empty())
				return out << "{}";
			typename segment_map<SourceRef, Id, acic>::const_iterator i(this->begin());
			out << '{';
			i->first->serialize(out);
			out << i->second;
			for (++i; i != this->end(); ++i)
			{
				out << ", ";
				i->first->serialize(out);
				out << i->second;
			}
			return out << '}';
		}
	};

	template<typename SourceRef, typename Id, assoc_container_impl_choice acsic, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits>& out, const segment_map<SourceRef, Id, acsic> &sm)
	{ return sm.serialize(out); }

	template<typename SourceRef, typename Id, assoc_container_impl_choice acsic>
	struct segment_map_transformer
	{
		typedef segment_map<SourceRef, Id, acsic> blackboard;
		typedef typename out_bound<Id>::const_ref tag_output;

		SourceRef begin_src_ref;
		SourceRef end_src_ref;

		segment_map_transformer(): begin_src_ref(), end_src_ref()
		{}

		segment_map_transformer(SourceRef begin_src_ref_, SourceRef end_src_ref_): begin_src_ref(begin_src_ref_), end_src_ref(end_src_ref_)
		{}

		void set(SourceRef begin_src_ref_, SourceRef end_src_ref_)
		{
			begin_src_ref = begin_src_ref_;
			end_src_ref = end_src_ref_;
		}

		blackboard& operator() (blackboard &sm, SourceRef src_ref, tag_output ob_cref) const
		{ return sm.insert(src_ref, begin_src_ref, end_src_ref, *ob_cref); }
	};

	template<typename SourceRef, typename Id, assoc_container_impl_choice acsic>
	struct segment_map_composer
	{
		typedef segment_map<SourceRef, Id, acsic> blackboard;

		blackboard& operator() (blackboard &sm1, const blackboard &sm2) const
		{ return sm1.insert(sm2); }
	};

	template<typename SourceRef, typename Id, assoc_container_impl_choice acsic>
	struct segment_map_converse_transformer
	{
		typedef segment_map<SourceRef, Id, acsic> blackboard;
		typedef typename out_bound<Id>::const_ref tag_output;

		SourceRef begin_src_ref;
		SourceRef end_src_ref;

		segment_map_converse_transformer(): begin_src_ref(), end_src_ref()
		{}

		segment_map_converse_transformer(SourceRef begin_src_ref_, SourceRef end_src_ref_): begin_src_ref(begin_src_ref_), end_src_ref(end_src_ref_)
		{}

		void set(SourceRef begin_src_ref_, SourceRef end_src_ref_)
		{
			begin_src_ref = begin_src_ref_;
			end_src_ref = end_src_ref_;
		}

		blackboard& operator() (blackboard &sm, SourceRef src_ref, tag_output ob_cref) const
		{ return sm.converse_insert(src_ref, begin_src_ref, end_src_ref, *ob_cref); }
	};
} //namespace grapenlp

#endif /*GRAPENLP_SEGMENT_H*/
