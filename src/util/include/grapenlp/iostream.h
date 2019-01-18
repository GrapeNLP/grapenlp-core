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

#ifndef GRAPENLP_IOSTREAM_H
#define GRAPENLP_IOSTREAM_H

#include <vector>
#include <iostream>
#include <string>

namespace grapenlp
{
	template <typename char_type, typename traits = std::char_traits<char_type> >
	class basic_teebuf: public std::basic_streambuf<char_type, traits>
	{
	public:
		typedef typename traits::int_type int_type;

	protected:
	    std::basic_streambuf<char_type, traits> * sb1;
	    std::basic_streambuf<char_type, traits> * sb2;

	public:
	    basic_teebuf(std::basic_streambuf<char_type, traits> * sb1, std::basic_streambuf<char_type, traits> * sb2): sb1(sb1), sb2(sb2)
		{}

	protected:
		virtual int sync()
		{
			int const r1 = sb1->pubsync();
			int const r2 = sb2->pubsync();
			return r1 == 0 && r2 == 0 ? 0 : -1;
		}

		virtual int_type overflow(int_type c)
		{
			int_type const eof = traits::eof();

			if (traits::eq_int_type(c, eof))
				return traits::not_eof(c);
			else
			{
				char_type const ch = traits::to_char_type(c);
				int_type const r1 = sb1->sputc(ch);
				int_type const r2 = sb2->sputc(ch);
				return traits::eq_int_type(r1, eof) || traits::eq_int_type(r2, eof) ? eof : c;
			}
		}
	};

	typedef basic_teebuf<char> teebuf;
	typedef basic_teebuf<wchar_t> wteebuf;

	class teeostream : public std::ostream
	{
	    teebuf tbuf;
	public:
	    teeostream(std::ostream & o1, std::ostream & o2): std::ostream(&tbuf), tbuf(o1.rdbuf(), o2.rdbuf())
	    {}
	};

	class wteeostream : public std::wostream
	{
	    wteebuf wtbuf;
	public:
	    wteeostream(std::wostream &o1, std::wostream &o2): std::wostream(&wtbuf), wtbuf(o1.rdbuf(), o2.rdbuf())
	    {}
	};

	/***************/
	/* Serializers */
	/***************/

	template<typename T>
	struct serializer
	{
		typedef T elem_type;

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& operator()(std::basic_ostream<CharT, Traits> &out, const T &t) const
		{ return out << t;	}
	};

	/*********************/
	/* deref-Serializers */
	/*********************/

	template<typename T>
	struct deref_serializer
	{
		typedef T *elem_type;

		template<typename CharT, typename Traits>
		inline std::basic_ostream<CharT, Traits>& operator()(std::basic_ostream<CharT, Traits> &out, T* t) const
		{ return out << *t;	}
	};

	/*********************/
	/* const-deref-Serializers */
	/*********************/

	template<typename T>
	struct const_deref_serializer
	{
		typedef const T *elem_type;

		template<typename CharT, typename Traits>
		inline std::basic_ostream<CharT, Traits>& operator()(std::basic_ostream<CharT, Traits> &out, const T* t) const
		{ return out << *t;	}
	};

	/*********************/
	/* Serializer traits */
	/*********************/

	template<typename Serializer>
	struct serializer_traits
	{
		typedef typename Serializer::elem_type elem_type;
	};

	/*********************************/
	/* Sequence serializer functions */
	/*********************************/

	template<typename Iterator, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& serialize_sequence(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end)
	{
		for (; begin != end; ++begin)
			out << *begin;
		return out;
	}

	//...with separator

	template<typename Iterator, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& serialize_sequence(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end, CharT separator)
	{
		if (begin == end)
			return out;
		out << *begin;
		++begin;
		for (; begin != end; ++begin)
		{
			out << separator;
			out << *begin;
		}
		return out;
	}

	template<typename Iterator, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& serialize_sequence(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end, const std::basic_string<CharT> &separator)
	{
		if (begin == end)
			return out;
		out << *begin;
		++begin;
		for (; begin != end; ++begin)
		{
			out << separator;
			out << *begin;
		}
		return out;
	}

	/************************/
	/* Sequence serializers */
	/************************/

	template<typename Iterator>
	struct sequence_serializer
	{
		typedef Iterator iterator_type;
		typedef typename iterator_type::value_type elem_type;

		template<typename CharT, typename Traits>
		inline std::basic_ostream<CharT, Traits>& operator()(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end) const
		{ return serialize_sequence<Iterator, CharT, Traits>(out, begin, end); }

		template<typename CharT, typename Traits>
		inline std::basic_ostream<CharT, Traits>& operator()(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end, CharT separator) const
		{ return serialize_sequence<Iterator, CharT, Traits>(out, begin, end, separator);	}
	};

	/******************************/
	/* Sequence serializer traits */
	/******************************/

	template<typename Iterator>
	struct serializer_traits<sequence_serializer<Iterator> >
	{
		typedef typename sequence_serializer<Iterator>::iterator_type iterator_type;
		typedef typename sequence_serializer<Iterator>::elem_type elem_type;
	};

	/*************************************/
	/* ptr-Sequence serializer functions */
	/*************************************/

	template<typename Iterator, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& serialize_ptr_sequence(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end)
	{
		for (; begin != end; ++begin)
			out << **begin;
		return out;
	}

	//...with separator

	template<typename Iterator, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& serialize_ptr_sequence(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end, CharT separator)
	{
		if (begin == end)
			return out;
		out << **begin;
		++begin;
		for (; begin != end; ++begin)
		{
			out << separator;
			out << **begin;
		}
		return out;
	}

	//These are for helping the compiler to find the generic serializer
	template<typename Iterator>
	std::ostream& serialize_ptr_sequence(std::ostream &out, Iterator begin, Iterator end, char separator)
	{ return serialize_ptr_sequence<Iterator, char, std::char_traits<char> >(out, begin, end, separator); }

	template<typename Iterator>
	std::wostream& serialize_ptr_sequence(std::wostream &out, Iterator begin, Iterator end, wchar_t separator)
	{ return serialize_ptr_sequence<Iterator, wchar_t, std::char_traits<wchar_t> >(out, begin, end, separator); }

	/****************************/
	/* ptr-Sequence serializers */
	/****************************/

	template<typename Iterator>
	struct ptr_sequence_serializer
	{
		typedef Iterator iterator_type;
		typedef typename Iterator::value_type elem_type;

		template<typename CharT, typename Traits>
		inline std::basic_ostream<CharT, Traits>& operator()(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end) const
		{ return serialize_ptr_sequence<Iterator, CharT, Traits>(out, begin, end); }

		template<typename CharT, typename Traits>
		inline std::basic_ostream<CharT, Traits>& operator()(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end, CharT separator) const
		{ return serialize_ptr_sequence<Iterator, CharT, Traits>(out, begin, end, separator);	}
	};

	/**********************************/
	/* ptr-Sequence serializer traits */
	/**********************************/

	template<typename Iterator>
	struct serializer_traits<ptr_sequence_serializer<Iterator> >
	{
		typedef typename ptr_sequence_serializer<Iterator>::iterator_type iterator_type;
		typedef typename ptr_sequence_serializer<Iterator>::elem_type elem_type;
	};

	/**************************************************/
	/* Sequence or ptr sequences serializer functions */
	/**************************************************/

	template<typename Iterator, typename InnerSequenceSerializer, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& serialize_sequence_of_ptr_sequences(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end, CharT outer_separator, InnerSequenceSerializer &iss)
	{
		if (begin == end)
			return out;
		iss(out, (*begin)->begin(), (*begin)->end());
		++begin;
		for (; begin != end; ++begin)
		{
			out << outer_separator;
			iss(out, (*begin)->begin(), (*begin)->end());
		}
		return out;
	}

	//These are for helping the compiler to find the generic serializer
	template<typename Iterator, typename InnerSequenceSerializer>
	inline std::ostream& serialize_sequence_of_ptr_sequences(std::ostream &out, Iterator begin, Iterator end, wchar_t outer_separator, InnerSequenceSerializer &iss)
	{ return serialize_sequence_of_ptr_sequences<Iterator, InnerSequenceSerializer, char, std::char_traits<char> >(out, begin, end, outer_separator, iss); }

	template<typename Iterator, typename InnerSequenceSerializer>
	inline std::wostream& serialize_sequence_of_ptr_sequences(std::wostream &out, Iterator begin, Iterator end, wchar_t outer_separator, InnerSequenceSerializer &iss)
	{ return serialize_sequence_of_ptr_sequences<Iterator, InnerSequenceSerializer, wchar_t, std::char_traits<wchar_t> >(out, begin, end, outer_separator, iss); }

	/*****************************************/
	/* Sequence of ptr sequences serializers */
	/*****************************************/

	template<typename Iterator, typename InnerSequenceSerializer>
	struct sequence_of_ptr_sequences_serializer
	{
		typedef Iterator iterator_type;
		typedef InnerSequenceSerializer inner_sequence_serializer_type;
		typedef typename InnerSequenceSerializer::elem_type elem_type;

		InnerSequenceSerializer iss;

		sequence_of_ptr_sequences_serializer(): iss()
		{}
		sequence_of_ptr_sequences_serializer(InnerSequenceSerializer &iss_): iss(iss_)
		{}

		template<typename CharT, typename Traits>
		inline std::basic_ostream<CharT, Traits>& operator()(std::basic_ostream<CharT, Traits> &out, Iterator begin, Iterator end, CharT outer_separator)
		{ return serialize_sequence_of_ptr_sequences<Iterator, InnerSequenceSerializer, CharT, Traits>(out, begin, end, outer_separator, iss); }
	};

	/**********************************/
	/* Sequence of ptr sequences serializer traits */
	/**********************************/

	template<typename Iterator, typename InnerSequenceSerializer>
	struct serializer_traits<sequence_of_ptr_sequences_serializer<Iterator, InnerSequenceSerializer> >
	{
		typedef typename sequence_of_ptr_sequences_serializer<Iterator, InnerSequenceSerializer>::iterator_type iterator_type;
		typedef typename sequence_of_ptr_sequences_serializer<Iterator, InnerSequenceSerializer>::inner_sequence_serializer_type inner_sequence_serializer_type;
		typedef typename sequence_of_ptr_sequences_serializer<Iterator, InnerSequenceSerializer>::elem_type elem_type;
	};

	//Serialize a box frame composed by stars, with "header" inside and adding "line_prefix" to each box line (for instance, /* and */ for C commments)
	template<typename Iterator, typename CharT, typename Traits>
	std::basic_ostream<CharT, Traits>& serialize_starbox(std::basic_ostream<CharT, Traits> &out, Iterator header_begin, Iterator header_end, const std::basic_string<CharT, Traits> &line_prefix = std::basic_string<CharT, Traits>(), const std::basic_string<CharT, Traits> &line_suffix = std::basic_string<CharT, Traits>())
	{
		out << line_prefix << "**";
		Iterator i(header_end);
		for (; i != header_begin; --i)
			out << '*';
		out << "**" << line_suffix << std::endl << line_prefix << "* ";
		for (; i != header_end; ++i)
			out << *i;
		out << " *" << line_suffix << std::endl << line_prefix << "**";
		for (; i > header_begin; --i)
			out << '*';
		out << "**" << line_suffix << std::endl;
		return out;
	}
} //namespace grapenlp
#endif /*GRAPENLP_IOSTREAM_H*/
