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

#ifndef GRAPENLP_DELAF_ENTRY_FILTER_H
#define GRAPENLP_DELAF_ENTRY_FILTER_H

#include <memory>

#include <grapenlp/delaf_entry_filter_type.h>
#include <grapenlp/text_delaf.h>

namespace grapenlp
{
/*
 * Generic DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class text_delaf_entry_filter
	{
	public:
		typedef delaf_entry_filter_type type;

		text_delaf_entry_filter()
		{}

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const = 0;
		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &dwf) const = 0;
		virtual std::ostream& serialize(std::ostream& out) const = 0;
		virtual std::wostream& wserialize(std::wostream& out) const = 0;

		virtual type get_type() const = 0;

		virtual ~text_delaf_entry_filter(){}
	};

	//Generic serialization function
	template<typename Char, typename CaseNormalizer>
	std::ostream& operator<< (std::ostream& out, const text_delaf_entry_filter<Char, CaseNormalizer> &def)
	{ return def.serialize(out); }

	template<typename Char, typename CaseNormalizer>
	std::wostream& operator<< (std::wostream& out, const text_delaf_entry_filter<Char, CaseNormalizer> &def)
	{ return def.wserialize(out); }

	//Generic less comparator
	template<typename Char, typename CaseNormalizer>
	bool operator< (const text_delaf_entry_filter<Char, CaseNormalizer>& def1, const text_delaf_entry_filter<Char, CaseNormalizer>& def2)
	{
		if (def1.get_type() < def2.get_type())
			return true;
		if (def1.get_type() > def2.get_type())
			return false;
		return def1.same_type_less(def2);
	}

/*
 * DELAF entry filter union
 */

	template<typename Char, typename CaseNormalizer>
	class union_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const union_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const union_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class union_text_delaf_entry_filter : public virtual text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const union_text_delaf_entry_filter<Char, CaseNormalizer>&, const union_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		ptr_list<text_delaf_entry_filter<Char, CaseNormalizer> > delaf_entry_filters;

	public:
		union_text_delaf_entry_filter(): base_type(), delaf_entry_filters()
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return UNION_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{
			typename ptr_list<text_delaf_entry_filter<Char, CaseNormalizer> >::const_iterator i(delaf_entry_filters.begin());
			for (; i != delaf_entry_filters.end(); ++i)
				if ((*i)->match(e))
					return true;
			return false;
		}

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const union_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{
			if (delaf_entry_filters.empty())
				return out;
			typename ptr_list<text_delaf_entry_filter<Char, CaseNormalizer> >::const_iterator i(delaf_entry_filters.begin());
			(*i)->serialize(out);
			++i;
			for (; i != delaf_entry_filters.end(); ++i)
			{
				out << '+';
				(*i)->serialize(out);
			}
			return out;
		}

		virtual std::wostream& wserialize(std::wostream& out) const
		{
			if (delaf_entry_filters.empty())
				return out;
			typename ptr_list<text_delaf_entry_filter<Char, CaseNormalizer> >::const_iterator i(delaf_entry_filters.begin());
			(*i)->wserialize(out);
			++i;
			for (; i != delaf_entry_filters.end(); ++i)
			{
				out << L'+';
				(*i)->wserialize(out);
			}
			return out;
		}
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const union_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const union_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{ return &l1.delaf_entry_filters < &l2.delaf_entry_filters;	}

/*
 * True DELAF entry filter (matches every DELAF entry)
 */

	template<typename Char, typename CaseNormalizer>
	class true_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const true_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const true_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class true_text_delaf_entry_filter : public virtual text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const true_text_delaf_entry_filter<Char, CaseNormalizer>&, const true_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef text_delaf_entry_filter<Char, CaseNormalizer> base_type;

	public:
		true_text_delaf_entry_filter(): base_type()
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return TRUE_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return true; }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const true_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "<DIC>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"<DIC>"; }
	};

	//There can only be one true DELAF entry filter; since x < x is always false this function always returns false
	template<typename Char, typename CaseNormalizer>
	bool operator< (const true_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const true_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{ return false;	}

/*
 * False DELAF entry filter (matches no DELAF entry)
 */

	template<typename Char, typename CaseNormalizer>
	class false_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const false_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const false_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class false_text_delaf_entry_filter : public virtual text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const false_text_delaf_entry_filter<Char, CaseNormalizer>&, const false_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef text_delaf_entry_filter<Char, CaseNormalizer> base_type;

	public:
		false_text_delaf_entry_filter(): base_type()
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FALSE_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return false; }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const false_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return out << "<!DIC>"; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return out << L"<!DIC>"; }
	};

	//There can only be one false DELAF entry filter; since x < x is always false this function always returns false
	template<typename Char, typename CaseNormalizer>
	bool operator< (const false_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const false_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{ return false;	}

/*
 * Canonical form DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_text_delaf_entry_filter : public virtual text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef text_delaf_entry_filter<Char, CaseNormalizer> base_type;

	protected:
		const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form;

	public:
		canonical_form_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_): base_type(), canonical_form(canonical_form_)
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form(canonical_form); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		std::ostream& serialize_canonical_form(std::ostream& out) const
		{ return static_cast<const typename trie<Char>::string &>(canonical_form).serialize(out); }

		std::wostream& wserialize_canonical_form(std::wostream& out) const
		{ return static_cast<const typename trie<Char>::string &>(canonical_form).serialize(out); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return serialize_canonical_form(out << "%<") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return wserialize_canonical_form(out << L"%<") << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{ return &l1.canonical_form < &l2.canonical_form;	}

/*
 * Negated canonical form DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_): base_type(canonical_form_)
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form(base_type::canonical_form); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::serialize_canonical_form(out << "%<!") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::wserialize_canonical_form(out << L"%<!") << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Mandatory POS DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class mandatory_pos_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class mandatory_pos_text_delaf_entry_filter : public virtual text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&, const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef text_delaf_entry_filter<Char, CaseNormalizer> base_type;

	protected:
		const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos;

	public:
		mandatory_pos_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_): base_type(), mandatory_pos(mandatory_pos_)
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return MANDATORY_POS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_mandatory_pos(mandatory_pos); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		std::ostream& serialize_mandatory_pos(std::ostream& out) const
		{ return static_cast<const typename trie<Char>::string &>(mandatory_pos).serialize(out);	}

		std::wostream& wserialize_mandatory_pos(std::wostream& out) const
		{ return static_cast<const typename trie<Char>::string &>(mandatory_pos).serialize(out);	}

		virtual std::ostream& serialize(std::ostream& out) const
		{ return serialize_mandatory_pos(out << "%<") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return wserialize_mandatory_pos(out << L"%<") << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{ return &l1.mandatory_pos < &l2.mandatory_pos; }

/*
 * Negated mandatory POS DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_mandatory_pos_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_mandatory_pos_text_delaf_entry_filter : public mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

	public:
		negated_mandatory_pos_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_): base_type(mandatory_pos_)
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_MANDATORY_POS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_mandatory_pos(base_type::mandatory_pos); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::serialize_mandatory_pos(out << "%<!") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::wserialize_mandatory_pos(out << L"%<!") << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Forbidden PPOOSS DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class forbidden_ppooss_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class forbidden_ppooss_text_delaf_entry_filter : public virtual text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&, const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef text_delaf_entry_filter<Char, CaseNormalizer> base_type;

	protected:
		std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref;

	public:
		forbidden_ppooss_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_): base_type(), forbidden_ppooss_ref(std::move(forbidden_ppooss_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FORBIDDEN_PPOOSS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_forbidden_ppooss(*forbidden_ppooss_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		std::ostream& serialize_forbidden_ppooss(std::ostream& out) const
		{
			typename text_delaf<Char, CaseNormalizer>::cst_set::const_iterator i(forbidden_ppooss_ref->begin());
			for (; i != forbidden_ppooss_ref->end(); ++i)
				static_cast<const typename trie<Char>::string &>(**i).serialize(out << '-');
			return out;
		}

		std::wostream& wserialize_forbidden_ppooss(std::wostream& out) const
		{
			typename text_delaf<Char, CaseNormalizer>::cst_set::const_iterator i(forbidden_ppooss_ref->begin());
			for (; i != forbidden_ppooss_ref->end(); ++i)
				static_cast<const typename trie<Char>::string &>(**i).serialize(out << L'-');
			return out;
		}

		virtual std::ostream& serialize(std::ostream& out) const
		{ return serialize_forbidden_ppooss(out << "%<") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return wserialize_forbidden_ppooss(out << L"%<") << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{ return *l1.forbidden_ppooss_ref < *l2.forbidden_ppooss_ref;	}

/*
 * Negated forbidden PPOOSS DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_forbidden_ppooss_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_forbidden_ppooss_text_delaf_entry_filter : public forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

	public:
		negated_forbidden_ppooss_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_): base_type(std::move(forbidden_ppooss_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_FORBIDDEN_PPOOSS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_forbidden_ppooss(*base_type::forbidden_ppooss_ref);	}

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::serialize_forbidden_ppooss(out << "%<!") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::wserialize_forbidden_ppooss(out << L"%<!") << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{ return *l1.forbidden_ppooss_ref < *l2.forbidden_ppooss_ref;	}

/*
 * Semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class semantic_traits_text_delaf_entry_filter : public virtual text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef text_delaf_entry_filter<Char, CaseNormalizer> base_type;

	protected:
		std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref;
		std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref;

	public:
		semantic_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base_type(), mandatory_semantic_traits_ref(std::move(mandatory_semantic_traits_ref_)), forbidden_semantic_traits_ref(std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_semantic_traits(*mandatory_semantic_traits_ref, *forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		inline std::ostream& serialize_forbidden_semantic_traits(std::ostream& out) const
		{
			typename text_delaf<Char, CaseNormalizer>::cst_set::const_iterator i(forbidden_semantic_traits_ref->begin());
			for (; i != forbidden_semantic_traits_ref->end(); ++i)
				static_cast<const typename trie<Char>::string &>(**i).serialize(out << '-');
			return out;
		}

		inline std::wostream& wserialize_forbidden_semantic_traits(std::wostream& out) const
		{
			typename text_delaf<Char, CaseNormalizer>::cst_set::const_iterator i(forbidden_semantic_traits_ref->begin());
			for (; i != forbidden_semantic_traits_ref->end(); ++i)
				static_cast<const typename trie<Char>::string &>(**i).serialize(out << L'-');
			return out;
		}

		std::ostream& serialize_semantic_traits(std::ostream& out) const
		{
			if (!mandatory_semantic_traits_ref->empty())
			{
				typename text_delaf<Char, CaseNormalizer>::cst_set::const_iterator i(mandatory_semantic_traits_ref->begin());
				static_cast<const typename trie<Char>::string &>(**i).serialize(out);
				++i;
				for (; i != mandatory_semantic_traits_ref->end(); ++i)
					static_cast<const typename trie<Char>::string &>(**i).serialize(out << '+');
			}
			return serialize_forbidden_semantic_traits(out);
		}

		std::wostream& wserialize_semantic_traits(std::wostream& out) const
		{
			if (!mandatory_semantic_traits_ref->empty())
			{
				typename text_delaf<Char, CaseNormalizer>::cst_set::const_iterator i(mandatory_semantic_traits_ref->begin());
				static_cast<const typename trie<Char>::string &>(**i).serialize(out);
				++i;
				for (; i != mandatory_semantic_traits_ref->end(); ++i)
					static_cast<const typename trie<Char>::string &>(**i).serialize(out << L'+');
			}
			return wserialize_forbidden_semantic_traits(out);
		}

		std::ostream& serialize_semantic_traits_with_all_signs(std::ostream& out) const
		{
			typename text_delaf<Char, CaseNormalizer>::cst_set::const_iterator i(mandatory_semantic_traits_ref->begin());
			for (; i != mandatory_semantic_traits_ref->end(); ++i)
				static_cast<const typename trie<Char>::string &>(**i).serialize(out << '+');
			return serialize_forbidden_semantic_traits(out);
		}

		std::wostream& wserialize_semantic_traits_with_all_signs(std::wostream& out) const
		{
			typename text_delaf<Char, CaseNormalizer>::cst_set::const_iterator i(mandatory_semantic_traits_ref->begin());
			for (; i != mandatory_semantic_traits_ref->end(); ++i)
				static_cast<const typename trie<Char>::string &>(**i).serialize(out << L'+');
			return wserialize_forbidden_semantic_traits(out);
		}

		virtual std::ostream& serialize(std::ostream& out) const
		{ return serialize_semantic_traits(out << "%<") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return wserialize_semantic_traits(out << L"%<") << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (*l1.mandatory_semantic_traits_ref < *l2.mandatory_semantic_traits_ref)
			return true;
		if (*l2.mandatory_semantic_traits_ref < *l1.mandatory_semantic_traits_ref)
			return false;
		return *l1.forbidden_semantic_traits_ref < *l2.forbidden_semantic_traits_ref;
	}

/*
 * Negated semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_semantic_traits_text_delaf_entry_filter : public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_semantic_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_semantic_traits(*base_type::mandatory_semantic_traits_ref, *base_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::serialize_semantic_traits(out << "%<!") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::wserialize_semantic_traits(out << L"%<!") << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class possible_flexional_traits_text_delaf_entry_filter : public virtual text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef text_delaf_entry_filter<Char, CaseNormalizer> base_type;

	protected:
		std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref;

	public:
		possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(), possible_flexional_traits_ref(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_possible_flexional_traits(*possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		std::ostream& serialize_possible_flexional_traits(std::ostream& out) const
		{
			typename text_delaf<Char, CaseNormalizer>::flexional_traits_list::const_iterator j(possible_flexional_traits_ref->begin());
			typename text_delaf<Char, CaseNormalizer>::c_set::const_iterator k;
			for (; j != possible_flexional_traits_ref->end(); ++j)
			{
				out << L':';
				for (k = (*j)->begin(); k != (*j)->end(); ++k)
					out << *k;
			}
			return out;
		}

		std::wostream& wserialize_possible_flexional_traits(std::wostream& out) const
		{
			typename text_delaf<Char, CaseNormalizer>::flexional_traits_list::const_iterator j(possible_flexional_traits_ref->begin());
			typename text_delaf<Char, CaseNormalizer>::c_set::const_iterator k;
			for (; j != possible_flexional_traits_ref->end(); ++j)
			{
				out << L':';
				for (k = (*j)->begin(); k != (*j)->end(); ++k)
					out << *k;
			}
			return out;
		}

		virtual std::ostream& serialize(std::ostream& out) const
		{ return serialize_possible_flexional_traits(out << "%<") << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return wserialize_possible_flexional_traits(out << L"%<") << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{ return *l1.possible_flexional_traits_ref < *l2.possible_flexional_traits_ref; }

/*
 * Canonical form and mandatory POS DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_mandatory_pos_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_mandatory_pos_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>, public mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;

		canonical_form_and_mandatory_pos_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_): base1_type(canonical_form_), base2_type(mandatory_pos_)
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_MANDATORY_POS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form_and_mandatory_pos(base1_type::canonical_form, base2_type::mandatory_pos); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_mandatory_pos(base1_type::serialize_canonical_form(out << "%<") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_mandatory_pos(base1_type::wserialize_canonical_form(out << L"%<") << L'.') << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		return static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated canonical form and mandatory POS DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter : public canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_): base_type(canonical_form_, mandatory_pos_)
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_MANDATORY_POS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form_and_mandatory_pos(base_type::canonical_form, base_type::mandatory_pos); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_mandatory_pos(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_mandatory_pos(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.') << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const canonical_form_and_mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Canonical form and forbidden PPOOSS DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_forbidden_ppooss_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_forbidden_ppooss_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>, public forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;

		canonical_form_and_forbidden_ppooss_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_): base1_type(canonical_form_), base2_type(std::move(forbidden_ppooss_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form_and_forbidden_ppooss(base1_type::canonical_form, *base2_type::forbidden_ppooss_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_forbidden_ppooss(base1_type::serialize_canonical_form(out << "%<") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_forbidden_ppooss(base1_type::wserialize_canonical_form(out << L"%<") << L'.') << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		return static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated canonical form and forbidden PPOOSS DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form_and_forbidden_ppooss(base_type::base1_type::canonical_form, *base_type::base2_type::forbidden_ppooss_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_forbidden_ppooss(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_forbidden_ppooss(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.') << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Canonical form and semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_semantic_traits_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>, public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;

		canonical_form_and_semantic_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base1_type(canonical_form_), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form_and_semantic_traits(base1_type::canonical_form, *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref);	}

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_semantic_traits(base1_type::serialize_canonical_form(out << "%<") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_semantic_traits(base1_type::wserialize_canonical_form(out << L"%<") << L'.') << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		return static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated canonical form and semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_semantic_traits_text_delaf_entry_filter : public canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_and_semantic_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base_type(canonical_form_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form_and_semantic_traits(base_type::base1_type::canonical_form, *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_semantic_traits(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.') << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_semantic_traits(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.') << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const canonical_form_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Canonical form and mandatory POS and semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>, public mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>, public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base3_type;

		canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base1_type(canonical_form_), base2_type(mandatory_pos_), base3_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_MANDATORY_POS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form_and_mandatory_pos_and_semantic_traits(base1_type::canonical_form, base2_type::mandatory_pos, *base3_type::mandatory_semantic_traits_ref, *base3_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_semantic_traits_with_all_signs(base2_type::serialize_mandatory_pos(base1_type::serialize_canonical_form(out << "%<") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_semantic_traits_with_all_signs(base2_type::wserialize_mandatory_pos(base1_type::wserialize_canonical_form(out << L"%<") << L'.')) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		if (static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated canonical form and mandatory POS and semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter : public canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base_type(canonical_form_, mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_MANDATORY_POS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form_and_mandatory_pos_and_semantic_traits(base_type::base1_type::canonical_form, base_type::base2_type::mandatory_pos, *base_type::base3_type::mandatory_semantic_traits_ref, *base_type::base3_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_semantic_traits_with_all_signs(base_type::base2_type::serialize_mandatory_pos(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_semantic_traits_with_all_signs(base_type::base2_type::wserialize_mandatory_pos(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.')) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Canonical form and forbidden PPOOSS and semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>, public forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>, public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base3_type;

		canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base1_type(canonical_form_), base2_type(std::move(forbidden_ppooss_ref_)), base3_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form_and_forbidden_ppooss_and_semantic_traits(base1_type::canonical_form, *base2_type::forbidden_ppooss_ref, *base3_type::mandatory_semantic_traits_ref, *base3_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_semantic_traits_with_all_signs(base2_type::serialize_forbidden_ppooss(base1_type::serialize_canonical_form(out << "%<") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_semantic_traits_with_all_signs(base2_type::wserialize_forbidden_ppooss(base1_type::wserialize_canonical_form(out << L"%<") << L'.')) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		if (static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated canonical form and forbidden PPOOSS and semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form_and_forbidden_ppooss_and_semantic_traits(base_type::base1_type::canonical_form, *base_type::base2_type::forbidden_ppooss_ref, *base_type::base3_type::mandatory_semantic_traits_ref, *base_type::base3_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_semantic_traits_with_all_signs(base_type::base2_type::serialize_forbidden_ppooss(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_semantic_traits_with_all_signs(base_type::base2_type::wserialize_forbidden_ppooss(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.')) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Canonical form and mandatory POS and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>, public mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>, public possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;
		typedef possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base3_type;

		canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base1_type(canonical_form_), base2_type(mandatory_pos_), base3_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_MANDATORY_POS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form_and_mandatory_pos_and_possible_flexional_traits(base1_type::canonical_form, base2_type::mandatory_pos, *base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_possible_flexional_traits(base2_type::serialize_mandatory_pos(base1_type::serialize_canonical_form(out << "%<") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_possible_flexional_traits(base2_type::wserialize_mandatory_pos(base1_type::wserialize_canonical_form(out << L"%<") << L'.')) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		if (static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated canonical form and mandatory POS and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, mandatory_pos_, std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_MANDATORY_POS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form_and_mandatory_pos_and_possible_flexional_traits(base_type::base1_type::canonical_form, base_type::base2_type::mandatory_pos, *base_type::base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_possible_flexional_traits(base_type::base2_type::serialize_mandatory_pos(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_possible_flexional_traits(base_type::base2_type::wserialize_mandatory_pos(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.')) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Canonical form and forbidden PPOOSS and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>, public forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>, public possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;
		typedef possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base3_type;

		canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base1_type(canonical_form_), base2_type(std::move(forbidden_ppooss_ref_)), base3_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits(base1_type::canonical_form, *base2_type::forbidden_ppooss_ref, *base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_possible_flexional_traits(base2_type::serialize_forbidden_ppooss(base1_type::serialize_canonical_form(out << "%<") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_possible_flexional_traits(base2_type::wserialize_forbidden_ppooss(base1_type::wserialize_canonical_form(out << L"%<") << L'.')) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		if (static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated canonical form and forbidden PPOOSS and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits(base_type::base1_type::canonical_form, *base_type::base2_type::forbidden_ppooss_ref, *base_type::base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_possible_flexional_traits(base_type::base2_type::serialize_forbidden_ppooss(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_possible_flexional_traits(base_type::base2_type::wserialize_forbidden_ppooss(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.')) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Canonical form and semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>, public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>, public possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;
		typedef possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base3_type;

		canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base1_type(canonical_form_), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base3_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form_and_semantic_and_possible_flexional_traits(base1_type::canonical_form, *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref, *base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_possible_flexional_traits(base2_type::serialize_semantic_traits(base1_type::serialize_canonical_form(out << "%<") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_possible_flexional_traits(base2_type::wserialize_semantic_traits(base1_type::wserialize_canonical_form(out << L"%<") << L'.')) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		if (static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		return static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated canonical form and semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form_and_semantic_and_possible_flexional_traits(base_type::base1_type::canonical_form, *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref, *base_type::base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_possible_flexional_traits(base_type::base2_type::serialize_semantic_traits(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.')) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_possible_flexional_traits(base_type::base2_type::wserialize_semantic_traits(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.')) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Canonical form and mandatory POS and semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>, public mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>, public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>, public possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base3_type;
		typedef possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base4_type;

		canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base1_type(canonical_form_), base2_type(mandatory_pos_), base3_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base4_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_MANDATORY_POS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits(base1_type::canonical_form, base2_type::mandatory_pos, *base3_type::mandatory_semantic_traits_ref, *base3_type::forbidden_semantic_traits_ref, *base4_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base4_type::serialize_possible_flexional_traits(base3_type::serialize_semantic_traits_with_all_signs(base2_type::serialize_mandatory_pos(base1_type::serialize_canonical_form(out << "%<") << '.'))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base4_type::wserialize_possible_flexional_traits(base3_type::wserialize_semantic_traits_with_all_signs(base2_type::wserialize_mandatory_pos(base1_type::wserialize_canonical_form(out << L"%<") << L'.'))) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		if (static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		if (static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated canonical form and mandatory POS and semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_MANDATORY_POS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits(base_type::base1_type::canonical_form, base_type::base2_type::mandatory_pos, *base_type::base3_type::mandatory_semantic_traits_ref, *base_type::base3_type::forbidden_semantic_traits_ref, *base_type::base4_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base4_type::serialize_possible_flexional_traits(base_type::base3_type::serialize_semantic_traits_with_all_signs(base_type::base2_type::serialize_mandatory_pos(base_type::base1_type::serialize_canonical_form(out << "%<!") << '.'))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base4_type::wserialize_possible_flexional_traits(base_type::base3_type::wserialize_semantic_traits_with_all_signs(base_type::base2_type::wserialize_mandatory_pos(base_type::base1_type::wserialize_canonical_form(out << L"%<!") << L'.'))) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Canonical form and forbidden PPOOSS and semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>, public forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>, public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>, public possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base3_type;
		typedef possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base4_type;

		canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base1_type(canonical_form_), base2_type(std::move(forbidden_ppooss_ref_)), base3_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base4_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits(base1_type::canonical_form, *base2_type::forbidden_ppooss_ref, *base3_type::mandatory_semantic_traits_ref, *base3_type::forbidden_semantic_traits_ref, *base4_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base4_type::serialize_possible_flexional_traits(base3_type::serialize_semantic_traits_with_all_signs(base2_type::serialize_forbidden_ppooss(base1_type::serialize_canonical_form(out << "%<") << '.'))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base4_type::wserialize_possible_flexional_traits(base3_type::wserialize_semantic_traits_with_all_signs(base2_type::wserialize_forbidden_ppooss(base1_type::wserialize_canonical_form(out << L"%<") << L'.'))) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const canonical_form_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		if (static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		if (static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated canonical form and forbidden PPOOSS and semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::lemma_string &canonical_form_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_CANONICAL_FORM_AND_FORBIDDEN_PPOOSS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits(base_type::base1_type::canonical_form, *base_type::base2_type::forbidden_ppooss_ref, *base_type::base3_type::mandatory_semantic_traits_ref, *base_type::base3_type::forbidden_semantic_traits_ref, *base_type::base4_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base4_type::serialize_possible_flexional_traits(base_type::base3_type::serialize_semantic_traits_with_all_signs(base_type::base2_type::serialize_forbidden_ppooss(base_type::base1_type::serialize_canonical_form(out << "%<") << '.'))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base4_type::wserialize_possible_flexional_traits(base_type::base3_type::wserialize_semantic_traits_with_all_signs(base_type::base2_type::wserialize_forbidden_ppooss(base_type::base1_type::wserialize_canonical_form(out << L"%<") << L'.'))) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Mandatory POS and semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class mandatory_pos_and_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class mandatory_pos_and_semantic_traits_text_delaf_entry_filter : public mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>, public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;

		mandatory_pos_and_semantic_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base1_type(mandatory_pos_), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return MANDATORY_POS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_mandatory_pos_and_semantic_traits(base1_type::mandatory_pos, *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_semantic_traits_with_all_signs(base1_type::serialize_mandatory_pos(out << "%<")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_semantic_traits_with_all_signs(base1_type::wserialize_mandatory_pos(out << L"%<")) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated mandatory POS and semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter : public mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base_type(mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return MANDATORY_POS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_mandatory_pos_and_semantic_traits(base_type::base1_type::mandatory_pos, *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_semantic_traits_with_all_signs(base_type::base1_type::serialize_mandatory_pos(out << "%<!")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_semantic_traits_with_all_signs(base_type::base1_type::wserialize_mandatory_pos(out << L"%<!")) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const mandatory_pos_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Mandatory POS and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter : public mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>, public possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;

		mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base1_type(mandatory_pos_), base2_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return MANDATORY_POS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_mandatory_pos_and_possible_flexional_traits(base1_type::mandatory_pos, *base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_possible_flexional_traits(base1_type::serialize_mandatory_pos(out << "%<")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_possible_flexional_traits(base1_type::wserialize_mandatory_pos(out << L"%<")) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated mandatory POS and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter : public mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(mandatory_pos_, std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_MANDATORY_POS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_mandatory_pos_and_possible_flexional_traits(base_type::base1_type::mandatory_pos, *base_type::base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_possible_flexional_traits(base_type::base1_type::serialize_mandatory_pos(out << "%<!")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_possible_flexional_traits(base_type::base1_type::wserialize_mandatory_pos(out << L"%<!")) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Mandatory POS and semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>, public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>, public possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;
		typedef possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base3_type;

		mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base1_type(mandatory_pos_), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base3_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return MANDATORY_POS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_mandatory_pos_and_semantic_and_possible_flexional_traits(base1_type::mandatory_pos, *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref, *base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_possible_flexional_traits(base2_type::serialize_semantic_traits_with_all_signs(base1_type::serialize_mandatory_pos(out << "%<"))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_possible_flexional_traits(base2_type::wserialize_semantic_traits_with_all_signs(base1_type::wserialize_mandatory_pos(out << L"%<"))) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const mandatory_pos_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		if (static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated mandatory POS and semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename text_delaf<Char, CaseNormalizer>::cst_string &mandatory_pos_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_MANDATORY_POS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_mandatory_pos_and_semantic_and_possible_flexional_traits(base_type::base1_type::mandatory_pos, *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref, *base_type::base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_possible_flexional_traits(base_type::base2_type::serialize_semantic_traits_with_all_signs(base_type::base1_type::serialize_mandatory_pos(out << "%<!"))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_possible_flexional_traits(base_type::base2_type::wserialize_semantic_traits_with_all_signs(base_type::base1_type::wserialize_mandatory_pos(out << L"%<!"))) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Forbidden PPOOSS and semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter : public forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>, public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;

		forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base1_type(std::move(forbidden_ppooss_ref_)), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FORBIDDEN_PPOOSS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_forbidden_ppooss_and_semantic_traits(*base1_type::forbidden_ppooss_ref, *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_semantic_traits_with_all_signs(base1_type::serialize_forbidden_ppooss(out << "%<")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_semantic_traits_with_all_signs(base1_type::wserialize_forbidden_ppooss(out << L"%<")) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated forbidden PPOOSS and semantic traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter : public forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FORBIDDEN_PPOOSS_AND_SEMANTIC_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_forbidden_ppooss_and_semantic_traits(*base_type::base1_type::forbidden_ppooss_ref, *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_semantic_traits_with_all_signs(base_type::base1_type::serialize_forbidden_ppooss(out << "%<!")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_semantic_traits_with_all_signs(base_type::base1_type::wserialize_forbidden_ppooss(out << L"%<!")) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Forbidden PPOOSS and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter : public forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>, public possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;

		forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(forbidden_ppooss_ref_)), base2_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FORBIDDEN_PPOOSS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_forbidden_ppooss_and_possible_flexional_traits(*base1_type::forbidden_ppooss_ref, *base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_possible_flexional_traits(base1_type::serialize_forbidden_ppooss(out << "%<")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_possible_flexional_traits(base1_type::wserialize_forbidden_ppooss(out << L"%<")) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated forbidden PPOOSS and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter : public forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_FORBIDDEN_PPOOSS_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_forbidden_ppooss_and_possible_flexional_traits(*base_type::base1_type::forbidden_ppooss_ref, *base_type::base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_possible_flexional_traits(base_type::base1_type::serialize_forbidden_ppooss(out << "%<!")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_possible_flexional_traits(base_type::base1_type::wserialize_forbidden_ppooss(out << L"%<!")) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Forbidden PPOOSS and semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>, public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>, public possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;
		typedef possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base3_type;

		forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(forbidden_ppooss_ref_)), base2_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base3_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return FORBIDDEN_PPOOSS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_forbidden_ppooss_and_semantic_and_possible_flexional_traits(*base1_type::forbidden_ppooss_ref, *base2_type::mandatory_semantic_traits_ref, *base2_type::forbidden_semantic_traits_ref, *base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base3_type::serialize_possible_flexional_traits(base2_type::serialize_semantic_traits_with_all_signs(base1_type::serialize_forbidden_ppooss(out << "%<"))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base3_type::wserialize_possible_flexional_traits(base2_type::wserialize_semantic_traits_with_all_signs(base1_type::wserialize_forbidden_ppooss(out << L"%<"))) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const forbidden_ppooss_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		if (static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return false;
		return static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated forbidden PPOOSS and semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_ppooss_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_FORBIDDEN_PPOOSS_AND_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_forbidden_ppooss_and_semantic_and_possible_flexional_traits(*base_type::base1_type::forbidden_ppooss_ref, *base_type::base2_type::mandatory_semantic_traits_ref, *base_type::base2_type::forbidden_semantic_traits_ref, *base_type::base3_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base3_type::serialize_possible_flexional_traits(base_type::base2_type::serialize_semantic_traits_with_all_signs(base_type::base1_type::serialize_forbidden_ppooss(out << "%<!"))) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base3_type::wserialize_possible_flexional_traits(base_type::base2_type::wserialize_semantic_traits_with_all_signs(base_type::base1_type::wserialize_forbidden_ppooss(out << L"%<!"))) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class semantic_and_possible_flexional_traits_text_delaf_entry_filter : public semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>, public possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer> base1_type;
		typedef possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base2_type;

		semantic_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base1_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_)), base2_type(std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return e.match_semantic_and_possible_flexional_traits(*base1_type::mandatory_semantic_traits_ref, *base1_type::forbidden_semantic_traits_ref, *base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base2_type::serialize_possible_flexional_traits(base1_type::serialize_semantic_traits(out << "%<")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base2_type::wserialize_possible_flexional_traits(base1_type::wserialize_semantic_traits(out << L"%<")) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		if (static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		    static_cast<const semantic_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2))
			return true;
		return static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}

/*
 * Negated semantic and possible flexional traits DELAF entry filter
 */

	template<typename Char, typename CaseNormalizer>
	class negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter;

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2);

	template<typename Char, typename CaseNormalizer>
	class negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>
	{
		friend bool operator< <Char, CaseNormalizer>(const negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&, const negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&);

	public:
		typedef semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> base_type;

		negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::cst_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename text_delaf<Char, CaseNormalizer>::flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}

		virtual delaf_entry_filter_type get_type() const
		{ return NEGATED_SEMANTIC_AND_POSSIBLE_FLEXIONAL_TRAITS_DELAF_ENTRY_FILTER; }

		virtual bool match(const typename text_delaf<Char, CaseNormalizer>::entry &e) const
		{ return !e.match_semantic_and_possible_flexional_traits(*base_type::base1_type::mandatory_semantic_traits_ref, *base_type::base1_type::forbidden_semantic_traits_ref, *base_type::base2_type::possible_flexional_traits_ref); }

		virtual bool same_type_less(const text_delaf_entry_filter<Char, CaseNormalizer> &l) const
		{ return *this < dynamic_cast<const negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer> &>(l); }

		virtual std::ostream& serialize(std::ostream& out) const
		{ return base_type::base2_type::serialize_possible_flexional_traits(base_type::base1_type::serialize_semantic_traits(out << "%<!")) << '>'; }

		virtual std::wostream& wserialize(std::wostream& out) const
		{ return base_type::base2_type::wserialize_possible_flexional_traits(base_type::base1_type::wserialize_semantic_traits(out << L"%<!")) << L'>'; }
	};

	template<typename Char, typename CaseNormalizer>
	bool operator< (const negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l1, const negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>& l2)
	{
		return static_cast<const semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l1) <
		       static_cast<const semantic_and_possible_flexional_traits_text_delaf_entry_filter<Char, CaseNormalizer>&>(l2);
	}
} //namespace grapenlp
#endif /*GRAPENLP_DELAF_ENTRY_FILTER_H*/
