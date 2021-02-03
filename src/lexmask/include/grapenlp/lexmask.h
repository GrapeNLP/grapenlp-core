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

#ifndef GRAPENLP_LEXMASK_H
#define GRAPENLP_LEXMASK_H

#include <iterator>
#include <memory>

#include <grapenlp/iostream.h>
#include <grapenlp/unicode.h>
#include <grapenlp/algorithm.h>
#include <grapenlp/array.h>
#include <grapenlp/token.h>
#include <grapenlp/lexmask_type.h>
#include <grapenlp/u_lexmask_constants.h>
#include <grapenlp/text_delaf_entry_filter.h>
#include <grapenlp/compressed_delaf_entry_filter.h>
#include <grapenlp/normalizer_iterator.h>
#include <grapenlp/tag_input_traits.h>

namespace grapenlp
{
/*
 * Generic lexical mask
 */
	template<typename InputIterator>
	class lexmask
	{
	public:
		typedef lexmask_type type;
		typedef lexmask* ref;
		typedef const lexmask* const_ref;
		typedef typename std::iterator_traits<InputIterator>::value_type value_type;

		lexmask()
		{}

	public:
		virtual bool match(const token<InputIterator>& t) const = 0;
		virtual bool same_type_less(const lexmask<InputIterator> &l) const = 0;
		//Virtual methods do not accept template arguments, hence we define here one
		//serialization method for chars and one for wide chars
		virtual std::ostream& serialize(std::ostream& out) const = 0;
		virtual std::wostream& wserialize(std::wostream& out) const = 0;
		virtual void u_write(FILE *f) const = 0;

		virtual type get_type() const = 0;

		virtual ~lexmask(){}
	};

/*
 * Generic functions on lexical masks
 */

	//Generic match function
	template<typename InputIterator>
	struct deref_lexmask_deref_token_match: public std::binary_function<typename token<InputIterator>::const_ref, typename lexmask<InputIterator>::const_ref, bool>
	{
		bool operator() (typename token<InputIterator>::const_ref t_ref, typename lexmask<InputIterator>::const_ref l_ref) const
		{ return l_ref->match(*t_ref); }
	};

	template<typename InputIterator>
	struct tag_input_traits<lexmask<InputIterator>*>
	{
		typedef deref_lexmask_deref_token_match<InputIterator> match;
	};

	template<typename InputIterator>
	struct tag_input_traits<const lexmask<InputIterator>*>
	{
		typedef deref_lexmask_deref_token_match<InputIterator> match;
	};

	//Generic serialization functions on lexical masks
	template<typename InputIterator>
	std::ostream& operator<< (std::ostream& out, const lexmask<InputIterator> &l)
	{ return l.serialize(out); }

	template<typename InputIterator>
	std::wostream& operator<< (std::wostream& out, const lexmask<InputIterator> &l)
	{ return l.wserialize(out); }

	//Generic less comparator
	template<typename InputIterator>
	bool operator< (const lexmask<InputIterator>& l1, const lexmask<InputIterator>& l2)
	{
		if (l1.get_type() < l2.get_type())
			return true;
		if (l1.get_type() > l2.get_type())
			return false;
		return l1.same_type_less(l2);
	}

/*
 * Token meta mask
 */

	template<typename InputIterator>
	class token_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;

		token_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return TOKEN_META_LEXMASK; }

		virtual bool match(__attribute__((unused)) const token<InputIterator>& t) const
		{ return true; }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const token_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<TOKEN>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<TOKEN>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, token_meta_mask_code.begin(), token_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	//There can only be one token meta mask; since x < x is always false this function always returns false
	template<typename InputIterator>
	bool operator< (__attribute__((unused)) const token_meta_mask<InputIterator>& l1, __attribute__((unused)) const token_meta_mask<InputIterator>& l2)
	{ return false;	}

/*
 * Digit meta mask
 */

	template<typename InputIterator>
	class digit_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;

		digit_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return DIGIT_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return t.is_digit();	}

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const digit_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<NB>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<NB>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, digit_meta_mask_code.begin(), digit_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

/*
 * Not a digit meta mask
 */

	template<typename InputIterator>
	class no_digit_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;

		no_digit_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return NO_DIGIT_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return !t.is_digit();	}

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const no_digit_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<!NB>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<!NB>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, no_digit_meta_mask_code.begin(), no_digit_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	//There can only be one digit meta mask; since x < x is always false this function always returns false
	template<typename InputIterator>
	bool operator< (__attribute__((unused)) const digit_meta_mask<InputIterator>& l1, __attribute__((unused)) const digit_meta_mask<InputIterator>& l2)
	{ return false;	}

/*
 * Symbol mask
 */

	template<typename InputIterator>
	class symbol_mask;

	template<typename InputIterator>
	bool operator< (const symbol_mask<InputIterator> &l1, const symbol_mask<InputIterator> &l2);

	template<typename InputIterator>
	class symbol_mask : public virtual lexmask<InputIterator>
	{
		friend bool operator< <InputIterator>(const symbol_mask<InputIterator>&, const symbol_mask<InputIterator>&);

	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

	protected:
		value_type symbol;

	public:
		symbol_mask(value_type symbol_): base_type(), symbol(symbol_)
		{}

		virtual lexmask_type get_type() const
		{ return SYMBOL_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return symbol == *t.begin; }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const symbol_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << '%' << symbol; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L'%' << symbol; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(symbol, f);
		}
	};

	template<typename InputIterator>
	bool operator< (const symbol_mask<InputIterator>& l1, const symbol_mask<InputIterator>& l2)
	{ return l1.symbol < l2.symbol; }

/*
 * Case insensitive word mask
 */

	template<typename InputIterator, typename CaseNormalizer>
	class case_insensitive_word_mask;

	template<typename InputIterator, typename CaseNormalizer>
	bool operator< (const case_insensitive_word_mask<InputIterator, CaseNormalizer> &l1, const case_insensitive_word_mask<InputIterator, CaseNormalizer> &l2);

	template<typename InputIterator, typename CaseNormalizer>
	class case_insensitive_word_mask : public virtual lexmask<InputIterator>
	{
		friend bool operator< <InputIterator, CaseNormalizer> (const case_insensitive_word_mask<InputIterator, CaseNormalizer>&, const case_insensitive_word_mask<InputIterator, CaseNormalizer>&);

	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

	protected:
		array<value_type> word;

	public:
		template<typename CharConstIterator>
		case_insensitive_word_mask(CharConstIterator char_begin, CharConstIterator char_end): base_type(), word(char_begin, char_end, CaseNormalizer())
		{}

		virtual lexmask_type get_type() const
		{ return CASE_INSENSITIVE_WORD_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return equal(t.begin, t.end, word.begin(), word.end(), CaseNormalizer());	}

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const case_insensitive_word_mask<InputIterator, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << '%' << word; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L'%' << word; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			::u_write(f, word.begin(), word.end());
		}
	};

	template<typename InputIterator, typename CaseNormalizer>
	bool operator< (const case_insensitive_word_mask<InputIterator, CaseNormalizer> &l1, const case_insensitive_word_mask<InputIterator, CaseNormalizer> &l2)
	{ return l1.word < l2.word;	}

/*
 * Case sensitive word mask
 */

	template<typename InputIterator>
	class case_sensitive_word_mask;

	template<typename InputIterator>
	bool operator< (const case_sensitive_word_mask<InputIterator> &l1, const case_sensitive_word_mask<InputIterator> &l2);

	template<typename InputIterator>
	class case_sensitive_word_mask : public virtual lexmask<InputIterator>
	{
		friend bool operator< <InputIterator>(const case_sensitive_word_mask<InputIterator>&, const case_sensitive_word_mask<InputIterator>&);

	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

	protected:
		array<value_type> word;

	public:
		template<typename CharConstIterator>
		case_sensitive_word_mask(CharConstIterator char_begin, CharConstIterator char_end): base_type(), word(char_begin, char_end)
		{}

		virtual lexmask_type get_type() const
		{ return CASE_SENSITIVE_WORD_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return equal(word.begin(), word.end(), t.begin, t.end); }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const case_sensitive_word_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << '@' << word; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L'@' << word; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_sensitive_char, f);
			::u_write(f, word.begin(), word.end());
		}
	};

	template<typename InputIterator>
	bool operator< (const case_sensitive_word_mask<InputIterator>& l1, const case_sensitive_word_mask<InputIterator>& l2)
	{ return l1.word < l2.word;	}

/*
 * Word meta mask
 */

	template<typename InputIterator>
	class word_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

		word_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return WORD_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return t.is_word(); }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const word_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<MOT>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<MOT>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, word_meta_mask_code.begin(), word_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	//There can only be one word meta mask; since x < x is always false this function always returns false
	template<typename InputIterator>
	bool operator< (__attribute__((unused)) const word_meta_mask<InputIterator>& l1, __attribute__((unused)) const word_meta_mask<InputIterator>& l2)
	{ return false;	}

/*
 * No word meta mask
 */

	template<typename InputIterator>
	class no_word_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

		no_word_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return NO_WORD_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return !t.is_word(); }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const no_word_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<!MOT>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<!MOT>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, no_word_meta_mask_code.begin(), no_word_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	//There can only be one not-a-word meta mask; since x < x is always false this function always returns false
	template<typename InputIterator>
	bool operator< (__attribute__((unused)) const no_word_meta_mask<InputIterator>& l1, __attribute__((unused)) const no_word_meta_mask<InputIterator>& l2)
	{ return false;	}

/*
 * Uppercase word meta mask
 */

	template<typename InputIterator>
	class upper_word_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

		upper_word_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return UPPER_WORD_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return t.is_upper_word(); }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const upper_word_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<MAJ>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<MAJ>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, upper_word_meta_mask_code.begin(), upper_word_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	//There can only be one upper word meta mask; since x < x is always false this function always returns false
	template<typename InputIterator>
	bool operator< (__attribute__((unused)) const upper_word_meta_mask<InputIterator>& l1, __attribute__((unused)) const upper_word_meta_mask<InputIterator>& l2)
	{ return false;	}

/*
 * Not an uppercase word meta mask
 */

	template<typename InputIterator>
	class no_upper_word_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

		no_upper_word_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return NO_UPPER_WORD_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return t.is_word() && !t.is_upper_word(); }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const no_upper_word_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<!MAJ>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<!MAJ>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, no_upper_word_meta_mask_code.begin(), no_upper_word_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	//There can only be one not-an-upper word meta mask; since x < x is always false this function always returns false
	template<typename InputIterator>
	bool operator< (__attribute__((unused)) const no_upper_word_meta_mask<InputIterator>& l1, __attribute__((unused)) const no_upper_word_meta_mask<InputIterator>& l2)
	{ return false;	}

/*
 * Lowercase word meta mask
 */

	template<typename InputIterator>
	class lower_word_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

		lower_word_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return LOWER_WORD_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return t.is_lower_word(); }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const lower_word_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<MIN>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<MIN>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, lower_word_meta_mask_code.begin(), lower_word_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	//There can only be one lower word meta mask; since x < x is always false this function always returns false
	template<typename InputIterator>
	bool operator< (__attribute__((unused)) const lower_word_meta_mask<InputIterator>& l1, __attribute__((unused)) const lower_word_meta_mask<InputIterator>& l2)
	{ return false;	}

/*
 * Not a lowercase word meta mask
 */

	template<typename InputIterator>
	class no_lower_word_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

		no_lower_word_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return NO_LOWER_WORD_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return t.is_word() && !t.is_lower_word(); }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const no_lower_word_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<!MIN>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<!MIN>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, no_lower_word_meta_mask_code.begin(), no_lower_word_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	//There can only be one not-a-lower word meta mask; since x < x is always false this function always returns false
	template<typename InputIterator>
	bool operator< (__attribute__((unused)) const no_lower_word_meta_mask<InputIterator>& l1, __attribute__((unused)) const no_lower_word_meta_mask<InputIterator>& l2)
	{ return false;	}

/*
 * First-letter-uppercase word meta mask
 */

	template<typename InputIterator>
	class first_upper_word_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

		first_upper_word_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return FIRST_UPPER_WORD_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return t.is_first_upper_word(); }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const first_upper_word_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<PRE>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<PRE>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, first_upper_word_meta_mask_code.begin(), first_upper_word_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	//There can only be one first upper word meta mask; since x < x is always false this function always returns false
	template<typename InputIterator>
	bool operator< (__attribute__((unused)) const first_upper_word_meta_mask<InputIterator>& l1, __attribute__((unused)) const first_upper_word_meta_mask<InputIterator>& l2)
	{ return false;	}

/*
 * Not a first-letter-uppercase word meta mask
 */

	template<typename InputIterator>
	class no_first_upper_word_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

		no_first_upper_word_meta_mask(): base_type()
		{}

		virtual lexmask_type get_type() const
		{ return NO_FIRST_UPPER_WORD_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{
			return t.is_word() && t.is_first_upper_word();
		}

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const no_first_upper_word_meta_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%<!PRE>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%<!PRE>"; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			::u_write(f, no_first_upper_word_meta_mask_code.begin(), no_first_upper_word_meta_mask_code.end());
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	//There can only be one not-a-first-upper word meta mask; since x < x is always false this function always returns false
	template<typename InputIterator>
	bool operator< (__attribute__((unused)) const no_first_upper_word_meta_mask<InputIterator>& l1, __attribute__((unused)) const no_first_upper_word_meta_mask<InputIterator>& l2)
	{ return false;	}

/*
* Generic text dico meta mask
*/

	template<typename InputIterator, typename CaseNormalizer>
	class text_dico_meta_mask : public virtual lexmask<InputIterator>
	{
	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

	protected:
		text_delaf<value_type, CaseNormalizer> &dico;

	public:
		text_dico_meta_mask(text_delaf<value_type, CaseNormalizer> &dico_): base_type(), dico(dico_)
		{}
	};

/*
 * Constrained dico word meta mask
 */

	template<typename InputIterator, typename CaseNormalizer>
	class constrained_text_dico_word_meta_mask;

	template<typename InputIterator, typename CaseNormalizer>
	bool operator< (const constrained_text_dico_word_meta_mask<InputIterator, CaseNormalizer>& l1, const constrained_text_dico_word_meta_mask<InputIterator, CaseNormalizer>& l2);

	template<typename InputIterator, typename CaseNormalizer>
	class constrained_text_dico_word_meta_mask : public text_dico_meta_mask<InputIterator, CaseNormalizer>
	{
		friend bool operator< <InputIterator, CaseNormalizer>(const constrained_text_dico_word_meta_mask<InputIterator, CaseNormalizer>&, const constrained_text_dico_word_meta_mask<InputIterator, CaseNormalizer>&);

	public:
		typedef text_dico_meta_mask<InputIterator, CaseNormalizer> base_type;
		typedef typename base_type::value_type value_type;

	protected:
		std::unique_ptr<text_delaf_entry_filter<value_type, CaseNormalizer> > def_ref;

	public:
		constrained_text_dico_word_meta_mask(text_delaf<value_type, CaseNormalizer> &dico_, std::unique_ptr<text_delaf_entry_filter<value_type, CaseNormalizer> > def_ref_): base_type(dico_), def_ref(std::move(def_ref_))
		{}

		const text_delaf_entry_filter<value_type, CaseNormalizer>& get_filter()
		{ return *def_ref; }

		virtual lexmask_type get_type() const
		{ return CONSTRAINED_DICO_WORD_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{
			typename text_delaf<value_type, CaseNormalizer>::lemma_string::ref lsr(base_type::dico.get(t.begin, t.end));
			if (!lsr || !lsr->data)
				return false;
			typename text_delaf<value_type, CaseNormalizer>::entry_list::const_iterator i(lsr->data->begin());
			for (; i != lsr->data->end(); ++i)
				if (def_ref->match(**i))
					return true;
			return false;
		}

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const constrained_text_dico_word_meta_mask<InputIterator, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return def_ref->serialize(out); }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return def_ref->wserialize(out); }

		virtual void u_write(__attribute__((unused)) FILE *f) const
		{
			//TODO
		}
	};

	template<typename InputIterator, typename CaseNormalizer>
	bool operator< (const constrained_text_dico_word_meta_mask<InputIterator, CaseNormalizer>& l1, const constrained_text_dico_word_meta_mask<InputIterator, CaseNormalizer>& l2)
	{ return *l1.def_ref < *l2.def_ref;	}

/*
 * Generic compressed dico meta mask
 */

	template<typename InputIterator, typename CaseNormalizer>
	class compressed_dico_meta_mask : public virtual lexmask<InputIterator>
	{
	protected:
		compressed_delaf &dico;

	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

		compressed_dico_meta_mask(compressed_delaf &dico_): base_type(), dico(dico_)
		{}
	};

/*
 * Constrained compressed dico word meta mask
 * Compressed dicos use always unicode chars, so there is no need to parametrize the char type
 */

	template<typename InputIterator, typename CaseNormalizer>
	class constrained_compressed_dico_word_meta_mask;

	template<typename InputIterator, typename CaseNormalizer>
	bool operator< (const constrained_compressed_dico_word_meta_mask<InputIterator, CaseNormalizer>& l1, const constrained_compressed_dico_word_meta_mask<InputIterator, CaseNormalizer>& l2);

	template<typename InputIterator, typename CaseNormalizer>
	class constrained_compressed_dico_word_meta_mask : public compressed_dico_meta_mask<InputIterator, CaseNormalizer>
	{
		friend bool operator< <InputIterator, CaseNormalizer>(const constrained_compressed_dico_word_meta_mask<InputIterator, CaseNormalizer>&, const constrained_compressed_dico_word_meta_mask<InputIterator, CaseNormalizer>&);

	public:
		typedef compressed_dico_meta_mask<InputIterator, CaseNormalizer> base_type;
		typedef typename base_type::value_type value_type;

	protected:
		std::unique_ptr<compressed_delaf_entry_filter<normalizer_iterator<CaseNormalizer, InputIterator> > > cdef_ref;

	public:
		constrained_compressed_dico_word_meta_mask(compressed_delaf &compressed_dico_, std::unique_ptr<compressed_delaf_entry_filter<normalizer_iterator<CaseNormalizer, InputIterator> > > cdef_ref_): base_type(compressed_dico_), cdef_ref(std::move(cdef_ref_))
		{}

		const compressed_delaf_entry_filter<normalizer_iterator<CaseNormalizer, InputIterator> >& get_filter()
		{ return *cdef_ref; }

		virtual lexmask_type get_type() const
		{ return CONSTRAINED_COMPRESSED_DICO_WORD_META_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{
			const inf_delaf::ambiguous_entry* word_properties_ref(base_type::dico.get_word_properties(normalizer_iterator<CaseNormalizer, InputIterator>(t.begin), normalizer_iterator<CaseNormalizer, InputIterator>(t.end)));
			if (!word_properties_ref)
				return false;
			typename compressed_delaf::ambiguous_entry::const_iterator i(word_properties_ref->begin());
			for (; i != word_properties_ref->end(); ++i)
				if (cdef_ref->match(normalizer_iterator<CaseNormalizer, InputIterator>(t.begin), normalizer_iterator<CaseNormalizer, InputIterator>(t.end), **i))
					return true;
			return false;
		}

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const constrained_compressed_dico_word_meta_mask<InputIterator, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return cdef_ref->serialize(out); }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return cdef_ref->wserialize(out); }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(meta_left_delimiter_char, f);
			cdef_ref->u_write(f);
			u_fputc(meta_right_delimiter_char, f);
		}
	};

	template<typename InputIterator, typename CaseNormalizer>
	bool operator< (const constrained_compressed_dico_word_meta_mask<InputIterator, CaseNormalizer>& l1, const constrained_compressed_dico_word_meta_mask<InputIterator, CaseNormalizer>& l2)
	{ return *l1.cdef_ref < *l2.cdef_ref; }

/*
 * Case sensitive suffix mask
 */
	template<typename InputIterator>
	class case_sensitive_suffix_mask;

	template<typename InputIterator>
	bool operator< (const case_sensitive_suffix_mask<InputIterator> &l1, const case_sensitive_suffix_mask<InputIterator> &l2);

	template<typename InputIterator>
	class case_sensitive_suffix_mask : public virtual lexmask<InputIterator>
	{
		friend bool operator< <InputIterator>(const case_sensitive_suffix_mask<InputIterator>&, const case_sensitive_suffix_mask<InputIterator>&);

	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

	protected:
		array<value_type> suffix;

	public:
		case_sensitive_suffix_mask(value_type* suffix_ref, std::size_t length): base_type(), suffix(length)
		{ std::copy(suffix_ref, suffix_ref + length, suffix.begin()); }

		case_sensitive_suffix_mask(const array<value_type> &suffix_): base_type(), suffix(suffix_)
		{}

		template<typename CharConstIterator>
		case_sensitive_suffix_mask(CharConstIterator char_begin, CharConstIterator char_end, std::size_t length): base_type(), suffix(char_begin, char_end, length)
		{}

		virtual lexmask_type get_type() const
		{ return CASE_SENSITIVE_SUFFIX_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return ends_with(t.begin(), t.end(), suffix.begin(), suffix.end()); }

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const case_sensitive_suffix_mask<InputIterator> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "@-" << suffix; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"@-" << suffix; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_sensitive_char, f);
			u_fputc(suffix_char, f);
			::u_write(f, suffix.begin(), suffix.end());
		}
	};

	template<typename InputIterator>
	bool operator< (const case_sensitive_suffix_mask<InputIterator>& l1, const case_sensitive_suffix_mask<InputIterator>& l2)
	{ return l1.suffix < l2.suffix;	}

/*
 * Case insensitive suffix mask
 */

	template<typename InputIterator, typename CaseNormalizer>
	class case_insensitive_suffix_mask;

	template<typename InputIterator, typename CaseNormalizer>
	bool operator< (const case_insensitive_suffix_mask<InputIterator, CaseNormalizer> &l1, const case_insensitive_suffix_mask<InputIterator, CaseNormalizer> &l2);

	template<typename InputIterator, typename CaseNormalizer>
	class case_insensitive_suffix_mask : public virtual lexmask<InputIterator>
	{
		friend bool operator< <InputIterator, CaseNormalizer> (const case_insensitive_suffix_mask<InputIterator, CaseNormalizer>&, const case_insensitive_suffix_mask<InputIterator, CaseNormalizer>&);

	public:
		typedef lexmask<InputIterator> base_type;
		typedef typename base_type::value_type value_type;

	protected:
		array<value_type> suffix;

	public:
		case_insensitive_suffix_mask(value_type* suffix_ref, std::size_t length): base_type(), suffix(suffix_ref, length, CaseNormalizer())
		{}

		case_insensitive_suffix_mask(const array<value_type> &suffix_): base_type(), suffix(suffix_, CaseNormalizer())
		{}

		template<typename CharConstIterator>
		case_insensitive_suffix_mask(CharConstIterator char_begin, CharConstIterator char_end, std::size_t length): base_type(), suffix(char_begin, char_end, length, CaseNormalizer())
		{}

		virtual lexmask_type get_type() const
		{ return CASE_INSENSITIVE_SUFFIX_LEXMASK; }

		virtual bool match(const token<InputIterator>& t) const
		{ return ends_with(t.begin, t.end, suffix.begin(), suffix.end(), CaseNormalizer());	}

		virtual bool same_type_less(const lexmask<InputIterator> &l) const
		{ return *this < dynamic_cast<const case_insensitive_suffix_mask<InputIterator, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "%-" << suffix; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"%-" << suffix; }

		virtual void u_write(FILE *f) const
		{
			u_fputc(case_insensitive_char, f);
			u_fputc(suffix_char, f);
			::u_write(f, suffix.begin(), suffix.end());
		}
	};

	template<typename InputIterator, typename CaseNormalizer>
	bool operator< (const case_insensitive_suffix_mask<InputIterator, CaseNormalizer> &l1, const case_insensitive_suffix_mask<InputIterator, CaseNormalizer> &l2)
	{ return l1.suffix < l2.suffix;	}
}//namespace grapenlp

#endif /*GRAPENLP_LEXMASK_H*/
