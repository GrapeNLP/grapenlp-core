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

#ifndef GRAPENLP_COMPRESSED_DELAF_ENTRY_FILTER_H
#define GRAPENLP_COMPRESSED_DELAF_ENTRY_FILTER_H

#include <grapenlp/compressed_delaf.h>
#include <grapenlp/delaf_entry_filter_type.h>

namespace grapenlp
{
/*
 * Generic compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class compressed_delaf_entry_filter
	{
	public:
		typedef delaf_entry_filter_type type;

		compressed_delaf_entry_filter()
		{}

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const = 0;

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &dwf) const = 0;
		virtual std::ostream& serialize(std::ostream& out) const = 0;
		virtual std::wostream& wserialize(std::wostream& out) const = 0;
		virtual void u_write(FILE *f) const = 0;

		virtual type get_type() const = 0;

		virtual ~compressed_delaf_entry_filter(){};
	};

	//Generic serialization function
	template<typename UCharIterator>
	std::ostream& operator<< (std::ostream& out, const compressed_delaf_entry_filter<UCharIterator> &def)
	{ return def.serialize(out); }

	template<typename UCharIterator>
	std::wostream& operator<< (std::wostream& out, const compressed_delaf_entry_filter<UCharIterator> &def)
	{ return def.wserialize(out); }

	//Generic less comparator
	template<typename UCharIterator>
	bool operator< (const compressed_delaf_entry_filter<UCharIterator>& def1, const compressed_delaf_entry_filter<UCharIterator>& def2)
	{
		if (def1.get_type() < def2.get_type())
			return true;
		if (def1.get_type() > def2.get_type())
			return false;
		return def1.same_type_less(def2);
	}

/*
 * compressed DELAF entry filter union
 */

	template<typename UCharIterator>
	class union_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const union_compressed_delaf_entry_filter<UCharIterator>& l1, const union_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class union_compressed_delaf_entry_filter : public virtual compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const union_compressed_delaf_entry_filter<UCharIterator>&, const union_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef compressed_delaf_entry_filter<UCharIterator> base_type;

		ptr_list<compressed_delaf_entry_filter<UCharIterator> > compressed_delaf_entry_filters;

	public:
		union_compressed_delaf_entry_filter(): base_type(), compressed_delaf_entry_filters()
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return UNION_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{
			typename ptr_list<compressed_delaf_entry_filter<UCharIterator> >::const_iterator i(compressed_delaf_entry_filters.begin());
			for (; i != compressed_delaf_entry_filters.end(); ++i)
				if ((*i)->match(lemma_begin, lemma_end, e))
					return true;
			return false;
		}

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const union_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{
			if (compressed_delaf_entry_filters.empty())
				return out;
			typename ptr_list<compressed_delaf_entry_filter<UCharIterator> >::const_iterator i(compressed_delaf_entry_filters.begin());
			(*i)->serialize(out);
			++i;
			for (; i != compressed_delaf_entry_filters.end(); ++i)
			{
				out << '+';
				(*i)->serialize(out);
			}
			return out;
		}

		virtual std::wostream& wserialize(std::wostream& out) const
		{
			if (compressed_delaf_entry_filters.empty())
				return out;
			typename ptr_list<compressed_delaf_entry_filter<UCharIterator> >::const_iterator i(compressed_delaf_entry_filters.begin());
			(*i)->wserialize(out);
			++i;
			for (; i != compressed_delaf_entry_filters.end(); ++i)
			{
				out << L'+';
				(*i)->wserialize(out);
			}
			return out;
		}

		virtual void u_write(FILE *f) const
		{
			if (compressed_delaf_entry_filters.empty())
				return;
			typename ptr_list<compressed_delaf_entry_filter<UCharIterator> >::const_iterator i(compressed_delaf_entry_filters.begin());
			(*i)->u_write(f);
			++i;
			for (; i != compressed_delaf_entry_filters.end(); ++i)
			{
				u_fputc('+', f);
				(*i)->u_write(f);
			}
		}
	};

	template<typename UCharIterator>
	bool operator< (const union_compressed_delaf_entry_filter<UCharIterator>& l1, const union_compressed_delaf_entry_filter<UCharIterator>& l2)
	{ return &l1.compressed_delaf_entry_filters < &l2.compressed_delaf_entry_filters; }

/*
 * True compressed DELAF entry filter (matches every compressed DELAF entry)
 */

	template<typename UCharIterator>
	class true_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const true_compressed_delaf_entry_filter<UCharIterator>& l1, const true_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class true_compressed_delaf_entry_filter : public virtual compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const true_compressed_delaf_entry_filter<UCharIterator>&, const true_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef compressed_delaf_entry_filter<UCharIterator> base_type;

	public:
		true_compressed_delaf_entry_filter(): base_type()
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return TRUE_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return true; }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const true_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "<DIC>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"<DIC>"; }

		virtual void u_write(FILE *f) const
		{ ::u_write(f, known_word_meta_mask_code.begin(), known_word_meta_mask_code.end()); }
	};

	//There can only be one true compressed DELAF entry filter; since x < x is always false this function always returns false
	template<typename UCharIterator>
	bool operator< (const true_compressed_delaf_entry_filter<UCharIterator>& l1, const true_compressed_delaf_entry_filter<UCharIterator>& l2)
	{ return false;	}

/*
 * False compressed DELAF entry filter (matches no compressed DELAF entry)
 */

	template<typename UCharIterator>
	class false_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const false_compressed_delaf_entry_filter<UCharIterator>& l1, const false_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class false_compressed_delaf_entry_filter : public virtual compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const false_compressed_delaf_entry_filter<UCharIterator>&, const false_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef compressed_delaf_entry_filter<UCharIterator> base_type;

	public:
		false_compressed_delaf_entry_filter(): base_type()
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FALSE_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return false; }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const false_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "<!DIC>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"<!DIC>"; }

		virtual void u_write(FILE *f) const
		{ ::u_write(f, unknown_word_meta_mask_code.begin(), unknown_word_meta_mask_code.end()); }
	};

	//There can only be one false compressed DELAF entry filter; since x < x is always false this function always returns false
	template<typename UCharIterator>
	bool operator< (const false_compressed_delaf_entry_filter<UCharIterator>& l1, const false_compressed_delaf_entry_filter<UCharIterator>& l2)
	{ return false;	}

/*
 * Canonical form compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_compressed_delaf_entry_filter : public virtual compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef compressed_delaf_entry_filter<UCharIterator> base_type;

	protected:
		const std::unique_ptr<const u_array> canonical_form_ref;

	public:
		canonical_form_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_): base_type(), canonical_form_ref(std::move(canonical_form_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form(lemma_begin, lemma_end, canonical_form_ref->begin(), canonical_form_ref->end()); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_compressed_delaf_entry_filter &>(l); }

		std::ostream& serialize_canonical_form(std::ostream& out) const
		{ return out << *canonical_form_ref; }

		std::wostream& wserialize_canonical_form(std::wostream& out) const
		{ return out << *canonical_form_ref; }

		void u_write_canonical_form(FILE *f) const
		{ ::u_write(f, canonical_form_ref->begin(), canonical_form_ref->end()); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return serialize_canonical_form(out << "%<") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return wserialize_canonical_form(out << L"%<") << L'>'; }

		virtual void u_write(FILE *f) const
		{ u_write_canonical_form(f); }
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_compressed_delaf_entry_filter<UCharIterator>& l2)
	{ return &l1.canonical_form_ref < &l2.canonical_form_ref;	}

/*
 * Negated canonical form compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_): base_type(std::move(canonical_form_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form(lemma_begin, lemma_end, base_type::canonical_form_ref->begin(), base_type::canonical_form_ref->end()); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::serialize_canonical_form(out << "%<!") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::wserialize_canonical_form(out << L"%<!") << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Mandatory POS compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class mandatory_pos_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l1, const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class mandatory_pos_compressed_delaf_entry_filter : public virtual compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&, const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef compressed_delaf_entry_filter<UCharIterator> base_type;

	protected:
		const compressed_delaf::ust_string &mandatory_pos;

	public:
		mandatory_pos_compressed_delaf_entry_filter(const compressed_delaf::ust_string &mandatory_pos_): base_type(), mandatory_pos(mandatory_pos_)
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return MANDATORY_POS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_mandatory_pos(mandatory_pos); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const mandatory_pos_compressed_delaf_entry_filter &>(l); }

		std::ostream& serialize_mandatory_pos(std::ostream& out) const
		{ return static_cast<const u_trie::string &>(mandatory_pos).serialize(out); }

		void u_write_mandatory_pos(FILE *f) const
		{ ::u_write(f, mandatory_pos.begin(), mandatory_pos.end()); }

		std::wostream& wserialize_mandatory_pos(std::wostream& out) const
		{ return static_cast<const u_trie::string &>(mandatory_pos).serialize(out); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return serialize_mandatory_pos(out << "%<") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return wserialize_mandatory_pos(out << L"%<") << L'>'; }

		virtual void u_write(FILE *f) const
		{ u_write_mandatory_pos(f); }
	};

	template<typename UCharIterator>
	bool operator< (const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l1, const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l2)
	{ return &l1.mandatory_pos < &l2.mandatory_pos; }

/*
 * Negated mandatory POS compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_mandatory_pos_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_mandatory_pos_compressed_delaf_entry_filter : public mandatory_pos_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&, const negated_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef mandatory_pos_compressed_delaf_entry_filter<UCharIterator> base_type;

	public:
		negated_mandatory_pos_compressed_delaf_entry_filter(const compressed_delaf::ust_string &mandatory_pos_): base_type(mandatory_pos_)
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_MANDATORY_POS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_mandatory_pos(base_type::mandatory_pos); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_mandatory_pos_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::serialize_mandatory_pos(out << "%<!") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::wserialize_mandatory_pos(out << L"%<!") << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Forbidden PPOOSS compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class forbidden_ppooss_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l1, const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class forbidden_ppooss_compressed_delaf_entry_filter : public virtual compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&, const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef compressed_delaf_entry_filter<UCharIterator> base_type;

	protected:
		std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref;

	public:
		forbidden_ppooss_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_): base_type(), forbidden_ppooss_ref(std::move(forbidden_ppooss_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FORBIDDEN_PPOOSS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_forbidden_ppooss(*forbidden_ppooss_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const forbidden_ppooss_compressed_delaf_entry_filter &>(l); }

		std::ostream& serialize_forbidden_ppooss(std::ostream& out) const
		{
			compressed_delaf::ust_set::const_iterator i(forbidden_ppooss_ref->begin());
			for (; i != forbidden_ppooss_ref->end(); ++i)
				static_cast<const u_trie::string &>(**i).serialize(out << '-');
			return out;
		}

		std::wostream& wserialize_forbidden_ppooss(std::wostream& out) const
		{
			compressed_delaf::ust_set::const_iterator i(forbidden_ppooss_ref->begin());
			for (; i != forbidden_ppooss_ref->end(); ++i)
				static_cast<const u_trie::string &>(**i).serialize(out << L'-');
			return out;
		}

		void u_write_forbidden_ppooss(FILE *f) const
		{
			compressed_delaf::ust_set::const_iterator i(forbidden_ppooss_ref->begin());
			for (; i != forbidden_ppooss_ref->end(); ++i)
			{
				u_fputc('-', f);
				::u_write(f, static_cast<const u_trie::string &>(**i).begin(), static_cast<const u_trie::string &>(**i).end());
			}
		}

		virtual std::ostream& serialize(std::ostream& out) const
		{ return serialize_forbidden_ppooss(out << "%<") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return wserialize_forbidden_ppooss(out << L"%<") << L'>'; }

		virtual void u_write(FILE *f) const
		{ u_write_forbidden_ppooss(f); }
	};

	template<typename UCharIterator>
	bool operator< (const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l1, const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l2)
	{ return *l1.forbidden_ppooss_ref < *l2.forbidden_ppooss_ref;	}

/*
 * Negated forbidden PPOOSS compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_forbidden_ppooss_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_forbidden_ppooss_compressed_delaf_entry_filter : public forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&, const negated_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator> base_type;

	public:
		negated_forbidden_ppooss_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_): base_type(std::move(forbidden_ppooss_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_FORBIDDEN_PPOOSS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_forbidden_ppooss(*base_type::forbidden_ppooss_ref);	}

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_forbidden_ppooss_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::serialize_forbidden_ppooss(out << "%<!") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::wserialize_forbidden_ppooss(out << L"%<!") << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write_forbidden_ppooss(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l2)
	{ return *l1.forbidden_ppooss_ref < *l2.forbidden_ppooss_ref;	}

/*
 * Semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class semantic_traits_compressed_delaf_entry_filter : public virtual compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef compressed_delaf_entry_filter<UCharIterator> base_type;

	protected:
		std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref;
		std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref;

	public:
		semantic_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base_type(), mandatory_semantic_traits_ref(std::move(mandatory_semantic_traits_ref_)), forbidden_semantic_traits_ref(std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_semantic_traits(*mandatory_semantic_traits_ref, *forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const semantic_traits_compressed_delaf_entry_filter &>(l); }

		inline std::ostream& serialize_forbidden_semantic_traits(std::ostream& out) const
		{
			compressed_delaf::ust_set::const_iterator i(forbidden_semantic_traits_ref->begin());
			for (; i != forbidden_semantic_traits_ref->end(); ++i)
				static_cast<const u_trie::string &>(**i).serialize(out << '-');
			return out;
		}

		inline std::wostream& wserialize_forbidden_semantic_traits(std::wostream& out) const
		{
			compressed_delaf::ust_set::const_iterator i(forbidden_semantic_traits_ref->begin());
			for (; i != forbidden_semantic_traits_ref->end(); ++i)
				static_cast<const u_trie::string &>(**i).serialize(out << L'-');
			return out;
		}

		inline void u_write_forbidden_semantic_traits(FILE *f) const
		{
			compressed_delaf::ust_set::const_iterator i(forbidden_semantic_traits_ref->begin());
			for (; i != forbidden_semantic_traits_ref->end(); ++i)
			{
				u_fputc('-', f);
				::u_write(f, static_cast<const u_trie::string &>(**i).begin(), static_cast<const u_trie::string &>(**i).end());
			}
		}

		std::ostream& serialize_semantic_traits(std::ostream& out) const
		{
			if (!mandatory_semantic_traits_ref->empty())
			{
				compressed_delaf::ust_set::const_iterator i(mandatory_semantic_traits_ref->begin());
				static_cast<const u_trie::string &>(**i).serialize(out);
				++i;
				for (; i != mandatory_semantic_traits_ref->end(); ++i)
					static_cast<const u_trie::string &>(**i).serialize(out << '+');
			}
			return serialize_forbidden_semantic_traits(out);
		}

		std::wostream& wserialize_semantic_traits(std::wostream& out) const
		{
			if (!mandatory_semantic_traits_ref->empty())
			{
				compressed_delaf::ust_set::const_iterator i(mandatory_semantic_traits_ref->begin());
				static_cast<const u_trie::string &>(**i).serialize(out);
				++i;
				for (; i != mandatory_semantic_traits_ref->end(); ++i)
					static_cast<const u_trie::string &>(**i).serialize(out << L'+');
			}
			return wserialize_forbidden_semantic_traits(out);
		}

		void u_write_semantic_traits(FILE *f) const
		{
			if (!mandatory_semantic_traits_ref->empty())
			{
				compressed_delaf::ust_set::const_iterator i(mandatory_semantic_traits_ref->begin());
				::u_write(f, static_cast<const u_trie::string &>(**i).begin(), static_cast<const u_trie::string &>(**i).end());
				++i;
				for (; i != mandatory_semantic_traits_ref->end(); ++i)
				{
					u_fputc('+', f);
					::u_write(f, static_cast<const u_trie::string &>(**i).begin(), static_cast<const u_trie::string &>(**i).end());
				}
			}
			u_write_forbidden_semantic_traits(f);
		}

		std::ostream& serialize_semantic_traits_with_all_signs(std::ostream& out) const
		{
			compressed_delaf::ust_set::const_iterator i(mandatory_semantic_traits_ref->begin());
			for (; i != mandatory_semantic_traits_ref->end(); ++i)
				static_cast<const u_trie::string &>(**i).serialize(out << '+');
			return serialize_forbidden_semantic_traits(out);
		}

		std::wostream& wserialize_semantic_traits_with_all_signs(std::wostream& out) const
		{
			compressed_delaf::ust_set::const_iterator i(mandatory_semantic_traits_ref->begin());
			for (; i != mandatory_semantic_traits_ref->end(); ++i)
				static_cast<const u_trie::string &>(**i).serialize(out << L'+');
			return wserialize_forbidden_semantic_traits(out);
		}

		void u_write_semantic_traits_with_all_signs(FILE *f) const
		{
			compressed_delaf::ust_set::const_iterator i(mandatory_semantic_traits_ref->begin());
			for (; i != mandatory_semantic_traits_ref->end(); ++i)
			{
				u_fputc('+', f);
				::u_write(f, static_cast<const u_trie::string &>(**i).begin(), static_cast<const u_trie::string &>(**i).end());
			}
			return u_write_forbidden_semantic_traits(f);
		}

		virtual std::ostream& serialize(std::ostream& out) const
		{ return serialize_semantic_traits(out << "%<") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return wserialize_semantic_traits(out << L"%<") << L'>'; }

		virtual void u_write(FILE *f) const
		{ return u_write_semantic_traits(f); }
	};

	template<typename UCharIterator>
	bool operator< (const semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (*l1.mandatory_semantic_traits_ref < *l2.mandatory_semantic_traits_ref)
			return true;
		if (*l2.mandatory_semantic_traits_ref < *l1.mandatory_semantic_traits_ref)
			return false;
		return *l1.forbidden_semantic_traits_ref < *l2.forbidden_semantic_traits_ref;
	}

/*
 * Negated semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_semantic_traits_compressed_delaf_entry_filter : public semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_semantic_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_semantic_traits(*base_type::mandatory_semantic_traits_ref, *base_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::serialize_semantic_traits(out << "%<!") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::wserialize_semantic_traits(out << L"%<!") << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			return base_type::u_write_semantic_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class possible_flexional_traits_compressed_delaf_entry_filter : public virtual compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef compressed_delaf_entry_filter<UCharIterator> base_type;

	protected:
		std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref;

	public:
		possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(), possible_flexional_traits_ref(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_possible_flexional_traits(*possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		std::ostream& serialize_possible_flexional_traits(std::ostream& out) const
		{
			compressed_delaf::u_flexional_traits_list::const_iterator j(possible_flexional_traits_ref->begin());
			u_set::const_iterator k;
			for (; j != possible_flexional_traits_ref->end(); ++j)
			{
				out << ':';
				for (k = (*j)->begin(); k != (*j)->end(); ++k)
					out << *k;
			}
			return out;
		}

		std::wostream& wserialize_possible_flexional_traits(std::wostream& out) const
		{
			compressed_delaf::u_flexional_traits_list::const_iterator j(possible_flexional_traits_ref->begin());
			u_set::const_iterator k;
			for (; j != possible_flexional_traits_ref->end(); ++j)
			{
				out << L':';
				for (k = (*j)->begin(); k != (*j)->end(); ++k)
					out << *k;
			}
			return out;
		}

		void u_write_possible_flexional_traits(FILE *f) const
		{
			compressed_delaf::u_flexional_traits_list::const_iterator j(possible_flexional_traits_ref->begin());
			u_set::const_iterator k;
			for (; j != possible_flexional_traits_ref->end(); ++j)
			{
				u_fputc(':', f);
				for (k = (*j)->begin(); k != (*j)->end(); ++k)
					u_fputc(*k, f);
			}
		}

		virtual std::ostream& serialize(std::ostream& out) const
		{ return serialize_possible_flexional_traits(out << "%<") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return wserialize_possible_flexional_traits(out << L"%<") << L'>'; }

		virtual void u_write(FILE *f) const
		{ return u_write_possible_flexional_traits(f); }
	};

	template<typename UCharIterator>
	bool operator< (const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{ return *l1.possible_flexional_traits_ref < *l2.possible_flexional_traits_ref; }

/*
 * Canonical form and mandatory POS compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_and_mandatory_pos_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_and_mandatory_pos_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>, public mandatory_pos_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef mandatory_pos_compressed_delaf_entry_filter<UCharIterator> base2_type;

		canonical_form_and_mandatory_pos_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, const compressed_delaf::ust_string &mandatory_pos_): base1_type(std::move(canonical_form_ref_)), base2_type(mandatory_pos_)
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_MANDATORY_POS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form_and_mandatory_pos(lemma_begin, lemma_end, base1_type::canonical_form_ref->begin(), base1_type::canonical_form_ref->end(), base2_type::mandatory_pos); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_mandatory_pos_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_mandatory_pos(base1_type::serialize_canonical_form(out << "%<") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_mandatory_pos(base1_type::wserialize_canonical_form(out << L"%<") << L'.') << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_canonical_form(f);
			u_fputc('.', f);
			base2_type::u_write_mandatory_pos(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		return static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated canonical form and mandatory POS compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_and_mandatory_pos_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_and_mandatory_pos_compressed_delaf_entry_filter : public canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_and_mandatory_pos_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, const compressed_delaf::ust_string &mandatory_pos_): base_type(std::move(canonical_form_ref_), mandatory_pos_)
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_MANDATORY_POS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form_and_mandatory_pos(lemma_begin, lemma_end, base_type::canonical_form_ref->begin(), base_type::canonical_form_ref->end(), base_type::mandatory_pos); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_mandatory_pos_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_mandatory_pos(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_mandatory_pos(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.') << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const canonical_form_and_mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Canonical form and forbidden PPOOSS compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>, public forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator> base2_type;

		canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_): base1_type(std::move(canonical_form_ref_)), base2_type(std::move(forbidden_ppooss_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form_and_forbidden_ppooss(lemma_begin, lemma_end, base1_type::canonical_form_ref->begin(), base1_type::canonical_form_ref->end(), *base2_type::forbidden_ppooss_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_forbidden_ppooss(base1_type::serialize_canonical_form(out << "%<") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_forbidden_ppooss(base1_type::wserialize_canonical_form(out << L"%<") << L'.') << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_canonical_form(f);
			u_fputc('.', f);
			base2_type::u_write_forbidden_ppooss(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		return static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated canonical form and forbidden PPOOSS compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_): base_type(std::move(canonical_form_ref_), std::move(forbidden_ppooss_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form_and_forbidden_ppooss(lemma_begin, lemma_end, base_type::base1_type::canonical_form_ref->begin(), base_type::base1_type::canonical_form_ref->end(), *base_type::base2_type::forbidden_ppooss_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_forbidden_ppooss(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_forbidden_ppooss(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.') << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const canonical_form_and_forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Canonical form and semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_and_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_and_semantic_traits_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>, public semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base2_type;

		canonical_form_and_semantic_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base1_type(std::move(canonical_form_ref_)), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form_and_semantic_traits(lemma_begin, lemma_end, base1_type::canonical_form_ref->begin(), base1_type::canonical_form_ref->end(), *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref);	}

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_semantic_traits(base1_type::serialize_canonical_form(out << "%<") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_semantic_traits(base1_type::wserialize_canonical_form(out << L"%<") << L'.') << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_canonical_form(f);
			u_fputc('.', f);
			base2_type::u_write_semantic_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		return static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated canonical form and semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_and_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_and_semantic_traits_compressed_delaf_entry_filter : public canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_and_semantic_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base_type(std::move(canonical_form_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form_and_semantic_traits(lemma_begin, lemma_end, base_type::base1_type::canonical_form_ref->begin(), base_type::base1_type::canonical_form_ref->end(), *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_semantic_traits(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_semantic_traits(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.') << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const canonical_form_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Canonical form and mandatory POS and semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>, public mandatory_pos_compressed_delaf_entry_filter<UCharIterator>, public semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef mandatory_pos_compressed_delaf_entry_filter<UCharIterator> base2_type;
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base3_type;

		canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base1_type(std::move(canonical_form_ref_)), base2_type(mandatory_pos_), base3_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_MANDATORY_POS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form_and_mandatory_pos_and_semantic_traits(lemma_begin, lemma_end, base1_type::canonical_form_ref->begin(), base1_type::canonical_form_ref->end(), base2_type::mandatory_pos, *base3_type::mandatory_semantic_traits_ref, *base3_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_semantic_traits_with_all_signs(base2_type::serialize_mandatory_pos(base1_type::serialize_canonical_form(out << "%<") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_semantic_traits_with_all_signs(base2_type::wserialize_mandatory_pos(base1_type::wserialize_canonical_form(out << L"%<") << L'.')) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_canonical_form(f);
			u_fputc('.', f);
			base2_type::u_write_mandatory_pos(f);
			base3_type::u_write_semantic_traits_with_all_signs(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		if (static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated canonical form and mandatory POS and semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter : public canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base_type(std::move(canonical_form_ref_), mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_MANDATORY_POS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form_and_mandatory_pos_and_semantic_traits(lemma_begin, lemma_end, base_type::base1_type::canonical_form_ref->begin(), base_type::base1_type::canonical_form_ref->end(), base_type::base2_type::mandatory_pos, *base_type::base3_type::mandatory_semantic_traits_ref, *base_type::base3_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_semantic_traits_with_all_signs(base_type::base2_type::serialize_mandatory_pos(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_semantic_traits_with_all_signs(base_type::base2_type::wserialize_mandatory_pos(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.')) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const canonical_form_and_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Canonical form and forbidden PPOOSS and semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>, public forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>, public semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator> base2_type;
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base3_type;

		canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base1_type(std::move(canonical_form_ref_)), base2_type(std::move(forbidden_ppooss_ref_)), base3_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form_and_forbidden_ppooss_and_semantic_traits(lemma_begin, lemma_end, base1_type::canonical_form_ref->begin(), base1_type::canonical_form_ref->end(), *base2_type::forbidden_ppooss_ref, *base3_type::mandatory_semantic_traits_ref, *base3_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_semantic_traits_with_all_signs(base2_type::serialize_forbidden_ppooss(base1_type::serialize_canonical_form(out << "%<") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_semantic_traits_with_all_signs(base2_type::wserialize_forbidden_ppooss(base1_type::wserialize_canonical_form(out << L"%<") << L'.')) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_canonical_form(f);
			u_fputc('.', f);
			base2_type::u_write_forbidden_ppooss(f);
			base3_type::u_write_semantic_traits_with_all_signs(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		if (static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated canonical form and forbidden PPOOSS and semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base_type(std::move(canonical_form_ref_), std::move(forbidden_ppooss_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form_and_forbidden_ppooss_and_semantic_traits(lemma_begin, lemma_end, base_type::base1_type::canonical_form_ref->begin(), base_type::base1_type::canonical_form_ref->end(), *base_type::base2_type::forbidden_ppooss_ref, *base_type::base3_type::mandatory_semantic_traits_ref, *base_type::base3_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_semantic_traits_with_all_signs(base_type::base2_type::serialize_forbidden_ppooss(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_semantic_traits_with_all_signs(base_type::base2_type::wserialize_forbidden_ppooss(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.')) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Canonical form and mandatory POS and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>, public mandatory_pos_compressed_delaf_entry_filter<UCharIterator>, public possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef mandatory_pos_compressed_delaf_entry_filter<UCharIterator> base2_type;
		typedef possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base3_type;

		canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(canonical_form_ref_)), base2_type(mandatory_pos_), base3_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_MANDATORY_POS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form_and_mandatory_pos_and_possible_flexional_traits(lemma_begin, lemma_end, base1_type::canonical_form_ref->begin(), base1_type::canonical_form_ref->end(), base2_type::mandatory_pos, *base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_possible_flexional_traits(base2_type::serialize_mandatory_pos(base1_type::serialize_canonical_form(out << "%<") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_possible_flexional_traits(base2_type::wserialize_mandatory_pos(base1_type::wserialize_canonical_form(out << L"%<") << L'.')) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_canonical_form(f);
			u_fputc('.', f);
			base2_type::u_write_mandatory_pos(f);
			base3_type::u_write_possible_flexional_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		if (static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated canonical form and mandatory POS and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter : public canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(canonical_form_ref_), mandatory_pos_, std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_MANDATORY_POS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form_and_mandatory_pos_and_possible_flexional_traits(lemma_begin, lemma_end, base_type::base1_type::canonical_form_ref->begin(), base_type::base1_type::canonical_form_ref->end(), base_type::base2_type::mandatory_pos, *base_type::base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_possible_flexional_traits(base_type::base2_type::serialize_mandatory_pos(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_possible_flexional_traits(base_type::base2_type::wserialize_mandatory_pos(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.')) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const canonical_form_and_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Canonical form and forbidden PPOOSS and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>, public forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>, public possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator> base2_type;
		typedef possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base3_type;

		canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(canonical_form_ref_)), base2_type(std::move(forbidden_ppooss_ref_)), base3_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits(lemma_begin, lemma_end, base1_type::canonical_form_ref->begin(), base1_type::canonical_form_ref->end(), *base2_type::forbidden_ppooss_ref, *base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_possible_flexional_traits(base2_type::serialize_forbidden_ppooss(base1_type::serialize_canonical_form(out << "%<") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_possible_flexional_traits(base2_type::wserialize_forbidden_ppooss(base1_type::wserialize_canonical_form(out << L"%<") << L'.')) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_canonical_form(f);
			u_fputc('.', f);
			base2_type::u_write_forbidden_ppooss(f);
			base3_type::u_write_possible_flexional_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		if (static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated canonical form and forbidden PPOOSS and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(canonical_form_ref_), std::move(forbidden_ppooss_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits(lemma_begin, lemma_end, base_type::base1_type::canonical_form_ref->begin(), base_type::base1_type::canonical_form_ref->end(), *base_type::base2_type::forbidden_ppooss_ref, *base_type::base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_possible_flexional_traits(base_type::base2_type::serialize_forbidden_ppooss(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_possible_flexional_traits(base_type::base2_type::wserialize_forbidden_ppooss(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.')) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Canonical form and semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>, public semantic_traits_compressed_delaf_entry_filter<UCharIterator>, public possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base2_type;
		typedef possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base3_type;

		canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(canonical_form_ref_)), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base3_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form_and_semantic_and_possible_flexional_traits(lemma_begin, lemma_end, base1_type::canonical_form_ref->begin(), base1_type::canonical_form_ref->end(), *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref, *base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_possible_flexional_traits(base2_type::serialize_semantic_traits(base1_type::serialize_canonical_form(out << "%<") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_possible_flexional_traits(base2_type::wserialize_semantic_traits(base1_type::wserialize_canonical_form(out << L"%<") << L'.')) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_canonical_form(f);
			u_fputc('.', f);
			base2_type::u_write_semantic_traits(f);
			base3_type::u_write_possible_flexional_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		if (static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		return static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated canonical form and semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(canonical_form_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form_and_semantic_and_possible_flexional_traits(lemma_begin, lemma_end, base_type::base1_type::canonical_form_ref->begin(), base_type::base1_type::canonical_form_ref->end(), *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref, *base_type::base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_possible_flexional_traits(base_type::base2_type::serialize_semantic_traits(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_possible_flexional_traits(base_type::base2_type::wserialize_semantic_traits(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.')) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const canonical_form_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Canonical form and mandatory POS and semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>, public mandatory_pos_compressed_delaf_entry_filter<UCharIterator>, public semantic_traits_compressed_delaf_entry_filter<UCharIterator>, public possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef mandatory_pos_compressed_delaf_entry_filter<UCharIterator> base2_type;
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base3_type;
		typedef possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base4_type;

		canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(canonical_form_ref_)), base2_type(mandatory_pos_), base3_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base4_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_MANDATORY_POS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits(lemma_begin, lemma_end, base1_type::canonical_form_ref->begin(), base1_type::canonical_form_ref->end(), base2_type::mandatory_pos, *base3_type::mandatory_semantic_traits_ref, *base3_type::forbidden_semantic_traits_ref, *base4_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base4_type::serialize_possible_flexional_traits(base3_type::serialize_semantic_traits_with_all_signs(base2_type::serialize_mandatory_pos(base1_type::serialize_canonical_form(out << "%<") << '.'))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base4_type::wserialize_possible_flexional_traits(base3_type::wserialize_semantic_traits_with_all_signs(base2_type::wserialize_mandatory_pos(base1_type::wserialize_canonical_form(out << L"%<") << L'.'))) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_canonical_form(f);
			u_fputc('.', f);
			base2_type::u_write_mandatory_pos(f);
			base3_type::u_write_semantic_traits_with_all_signs(f);
			base4_type::u_write_possible_flexional_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		if (static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		if (static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated canonical form and mandatory POS and semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(canonical_form_ref_), mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_MANDATORY_POS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits(lemma_begin, lemma_end, base_type::base1_type::canonical_form_ref->begin(), base_type::base1_type::canonical_form_ref->end(), base_type::base2_type::mandatory_pos, *base_type::base3_type::mandatory_semantic_traits_ref, *base_type::base3_type::forbidden_semantic_traits_ref, *base_type::base4_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base4_type::serialize_possible_flexional_traits(base_type::base3_type::serialize_semantic_traits_with_all_signs(base_type::base2_type::serialize_mandatory_pos(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.'))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base4_type::wserialize_possible_flexional_traits(base_type::base3_type::wserialize_semantic_traits_with_all_signs(base_type::base2_type::wserialize_mandatory_pos(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.'))) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Canonical form and forbidden PPOOSS and semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public canonical_form_compressed_delaf_entry_filter<UCharIterator>, public forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>, public semantic_traits_compressed_delaf_entry_filter<UCharIterator>, public possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator> base2_type;
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base3_type;
		typedef possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base4_type;

		canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(canonical_form_ref_)), base2_type(std::move(forbidden_ppooss_ref_)), base3_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base4_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits(lemma_begin, lemma_end, base1_type::canonical_form_ref->begin(), base1_type::canonical_form_ref->end(), *base2_type::forbidden_ppooss_ref, *base3_type::mandatory_semantic_traits_ref, *base3_type::forbidden_semantic_traits_ref, *base4_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base4_type::serialize_possible_flexional_traits(base3_type::serialize_semantic_traits_with_all_signs(base2_type::serialize_forbidden_ppooss(base1_type::serialize_canonical_form(out << "%<") << '.'))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base4_type::wserialize_possible_flexional_traits(base3_type::wserialize_semantic_traits_with_all_signs(base2_type::wserialize_forbidden_ppooss(base1_type::wserialize_canonical_form(out << L"%<") << L'.'))) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_canonical_form(f);
			u_fputc('.', f);
			base2_type::u_write_forbidden_ppooss(f);
			base3_type::u_write_semantic_traits_with_all_signs(f);
			base4_type::u_write_possible_flexional_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const canonical_form_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		if (static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		if (static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated canonical form and forbidden PPOOSS and semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<const u_array> canonical_form_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(canonical_form_ref_), std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits(lemma_begin, lemma_end, base_type::base1_type::canonical_form_ref->begin(), base_type::base1_type::canonical_form_ref->end(), *base_type::base2_type::forbidden_ppooss_ref, *base_type::base3_type::mandatory_semantic_traits_ref, *base_type::base3_type::forbidden_semantic_traits_ref, *base_type::base4_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base4_type::serialize_possible_flexional_traits(base_type::base3_type::serialize_semantic_traits_with_all_signs(base_type::base2_type::serialize_forbidden_ppooss(base_type::base1_type::serialize_canonical_form(out << "%<") << '.'))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base4_type::wserialize_possible_flexional_traits(base_type::base3_type::wserialize_semantic_traits_with_all_signs(base_type::base2_type::wserialize_forbidden_ppooss(base_type::base1_type::wserialize_canonical_form(out << L"%<") << L'.'))) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Mandatory POS and semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter : public mandatory_pos_compressed_delaf_entry_filter<UCharIterator>, public semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef mandatory_pos_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base2_type;

		mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter(const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base1_type(mandatory_pos_), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return MANDATORY_POS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_mandatory_pos_and_semantic_traits(base1_type::mandatory_pos, *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_semantic_traits_with_all_signs(base1_type::serialize_mandatory_pos(out << "%<")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_semantic_traits_with_all_signs(base1_type::wserialize_mandatory_pos(out << L"%<")) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_mandatory_pos(f);
			base2_type::u_write_semantic_traits_with_all_signs(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated mandatory POS and semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter : public mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter(const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base_type(mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return MANDATORY_POS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_mandatory_pos_and_semantic_traits(base_type::base1_type::mandatory_pos, *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_semantic_traits_with_all_signs(base_type::base1_type::serialize_mandatory_pos(out << "%<!")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_semantic_traits_with_all_signs(base_type::base1_type::wserialize_mandatory_pos(out << L"%<!")) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const mandatory_pos_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Mandatory POS and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter : public mandatory_pos_compressed_delaf_entry_filter<UCharIterator>, public possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef mandatory_pos_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base2_type;

		mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter(const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base1_type(mandatory_pos_), base2_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return MANDATORY_POS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_mandatory_pos_and_possible_flexional_traits(base1_type::mandatory_pos, *base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_possible_flexional_traits(base1_type::serialize_mandatory_pos(out << "%<")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_possible_flexional_traits(base1_type::wserialize_mandatory_pos(out << L"%<")) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_mandatory_pos(f);
			u_fputc('.', f);
			base2_type::u_write_possible_flexional_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated mandatory POS and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter : public mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter(const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(mandatory_pos_, std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_MANDATORY_POS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_mandatory_pos_and_possible_flexional_traits(base_type::base1_type::mandatory_pos, *base_type::base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_possible_flexional_traits(base_type::base1_type::serialize_mandatory_pos(out << "%<!")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_possible_flexional_traits(base_type::base1_type::wserialize_mandatory_pos(out << L"%<!")) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const mandatory_pos_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Mandatory POS and semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public mandatory_pos_compressed_delaf_entry_filter<UCharIterator>, public semantic_traits_compressed_delaf_entry_filter<UCharIterator>, public possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef mandatory_pos_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base2_type;
		typedef possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base3_type;

		mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base1_type(mandatory_pos_), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base3_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return MANDATORY_POS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_mandatory_pos_and_semantic_and_possible_flexional_traits(base1_type::mandatory_pos, *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref, *base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_possible_flexional_traits(base2_type::serialize_semantic_traits_with_all_signs(base1_type::serialize_mandatory_pos(out << "%<"))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_possible_flexional_traits(base2_type::wserialize_semantic_traits_with_all_signs(base1_type::wserialize_mandatory_pos(out << L"%<"))) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_mandatory_pos(f);
			u_fputc('.', f);
			base2_type::u_write_semantic_traits_with_all_signs(f);
			base3_type::u_write_possible_flexional_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const mandatory_pos_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		if (static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated mandatory POS and semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(const compressed_delaf::ust_string &mandatory_pos_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_MANDATORY_POS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_mandatory_pos_and_semantic_and_possible_flexional_traits(base_type::base1_type::mandatory_pos, *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref, *base_type::base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_possible_flexional_traits(base_type::base2_type::serialize_semantic_traits_with_all_signs(base_type::base1_type::serialize_mandatory_pos(out << "%<!"))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_possible_flexional_traits(base_type::base2_type::wserialize_semantic_traits_with_all_signs(base_type::base1_type::wserialize_mandatory_pos(out << L"%<!"))) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const mandatory_pos_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Forbidden PPOOSS and semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter : public forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>, public semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base2_type;

		forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base1_type(std::move(forbidden_ppooss_ref_)), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FORBIDDEN_PPOOSS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_forbidden_ppooss_and_semantic_traits(*base1_type::forbidden_ppooss_ref, *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_semantic_traits_with_all_signs(base1_type::serialize_forbidden_ppooss(out << "%<")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_semantic_traits_with_all_signs(base1_type::wserialize_forbidden_ppooss(out << L"%<")) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_forbidden_ppooss(f);
			base2_type::u_write_semantic_traits_with_all_signs(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated forbidden PPOOSS and semantic traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter : public forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FORBIDDEN_PPOOSS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_forbidden_ppooss_and_semantic_traits(*base_type::base1_type::forbidden_ppooss_ref, *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_semantic_traits_with_all_signs(base_type::base1_type::serialize_forbidden_ppooss(out << "%<!")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_semantic_traits_with_all_signs(base_type::base1_type::wserialize_forbidden_ppooss(out << L"%<!")) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const forbidden_ppooss_and_semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Forbidden PPOOSS and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter : public forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>, public possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base2_type;

		forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(forbidden_ppooss_ref_)), base2_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FORBIDDEN_PPOOSS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_forbidden_ppooss_and_possible_flexional_traits(*base1_type::forbidden_ppooss_ref, *base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_possible_flexional_traits(base1_type::serialize_forbidden_ppooss(out << "%<")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_possible_flexional_traits(base1_type::wserialize_forbidden_ppooss(out << L"%<")) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_forbidden_ppooss(f);
			base2_type::u_write_possible_flexional_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated forbidden PPOOSS and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter : public forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_FORBIDDEN_PPOOSS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_forbidden_ppooss_and_possible_flexional_traits(*base_type::base1_type::forbidden_ppooss_ref, *base_type::base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_possible_flexional_traits(base_type::base1_type::serialize_forbidden_ppooss(out << "%<!")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_possible_flexional_traits(base_type::base1_type::wserialize_forbidden_ppooss(out << L"%<!")) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const forbidden_ppooss_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Forbidden PPOOSS and semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>, public semantic_traits_compressed_delaf_entry_filter<UCharIterator>, public possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base2_type;
		typedef possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base3_type;

		forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(forbidden_ppooss_ref_)), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base3_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FORBIDDEN_PPOOSS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_forbidden_ppooss_and_semantic_and_possible_flexional_traits(*base1_type::forbidden_ppooss_ref, *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref, *base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_possible_flexional_traits(base2_type::serialize_semantic_traits_with_all_signs(base1_type::serialize_forbidden_ppooss(out << "%<"))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_possible_flexional_traits(base2_type::wserialize_semantic_traits_with_all_signs(base1_type::wserialize_forbidden_ppooss(out << L"%<"))) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_forbidden_ppooss(f);
			base2_type::u_write_semantic_traits_with_all_signs(f);
			base3_type::u_write_possible_flexional_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const forbidden_ppooss_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		if (static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated forbidden PPOOSS and semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> forbidden_ppooss_ref_, std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_FORBIDDEN_PPOOSS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_forbidden_ppooss_and_semantic_and_possible_flexional_traits(*base_type::base1_type::forbidden_ppooss_ref, *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref, *base_type::base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_possible_flexional_traits(base_type::base2_type::serialize_semantic_traits_with_all_signs(base_type::base1_type::serialize_forbidden_ppooss(out << "%<!"))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_possible_flexional_traits(base_type::base2_type::wserialize_semantic_traits_with_all_signs(base_type::base1_type::wserialize_forbidden_ppooss(out << L"%<!"))) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const forbidden_ppooss_and_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public semantic_traits_compressed_delaf_entry_filter<UCharIterator>, public possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef semantic_traits_compressed_delaf_entry_filter<UCharIterator> base1_type;
		typedef possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base2_type;

		semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base2_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return e.match_semantic_and_possible_flexional_traits(*base1_type::mandatory_semantic_traits_ref, *base1_type::forbidden_semantic_traits_ref, *base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_possible_flexional_traits(base1_type::serialize_semantic_traits(out << "%<")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_possible_flexional_traits(base1_type::wserialize_semantic_traits(out << L"%<")) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			base1_type::u_write_semantic_traits(f);
			base2_type::u_write_possible_flexional_traits(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		if (static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		    static_cast<const semantic_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2))
			return true;
		return static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}

/*
 * Negated semantic and possible flexional traits compressed DELAF entry filter
 */

	template<typename UCharIterator>
	class negated_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter;

	template<typename UCharIterator>
	bool operator< (const negated_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2);

	template<typename UCharIterator>
	class negated_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter : public semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>
	{
		friend bool operator< <UCharIterator>(const negated_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&, const negated_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&);

	public:
		typedef semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator> base_type;

		negated_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter(std::unique_ptr<compressed_delaf::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<compressed_delaf::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<compressed_delaf::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(UCharIterator lemma_begin, UCharIterator lemma_end, const compressed_delaf::entry &e) const
		{ return !e.match_semantic_and_possible_flexional_traits(*base_type::base1_type::mandatory_semantic_traits_ref, *base_type::base1_type::forbidden_semantic_traits_ref, *base_type::base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const compressed_delaf_entry_filter<UCharIterator> &l) const
		{ return *this < dynamic_cast<const negated_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_possible_flexional_traits(base_type::base1_type::serialize_semantic_traits(out << "%<!")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_possible_flexional_traits(base_type::base1_type::wserialize_semantic_traits(out << L"%<!")) << L'>'; }

		virtual void u_write(FILE *f) const
		{
			u_fputc('!', f);
			base_type::u_write(f);
		}
	};

	template<typename UCharIterator>
	bool operator< (const negated_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l1, const negated_semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>& l2)
	{
		return static_cast<const semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l1) <
		       static_cast<const semantic_and_possible_flexional_traits_compressed_delaf_entry_filter<UCharIterator>&>(l2);
	}
} //namespace grapenlp
#endif /*GRAPENLP_COMPRESSED_DELAF_ENTRY_FILTER_H*/
