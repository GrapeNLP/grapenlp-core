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

#ifndef GRAPE_U_DELAF_ENTRY_FILTER_H
#define GRAPE_U_DELAF_ENTRY_FILTER_H

#include <grape/u_text_delaf.h>
#include <grape/text_delaf_entry_filter.h>

namespace grape
{
/*
	template<typename CaseNormalizer>
	class u_text_delaf_entry_filter: public text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_text_delaf_entry_filter()//typename base_type::type type_): base_type(type_)
		{}
	};
*/

	template<typename CaseNormalizer>
	class u_union_text_delaf_entry_filter : public union_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef union_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_union_text_delaf_entry_filter(): base_type()
		{}
	};

	template<typename CaseNormalizer>
	class u_true_text_delaf_entry_filter : public true_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef true_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_true_text_delaf_entry_filter(): base_type()
		{}
	};

	template<typename CaseNormalizer>
	class u_false_text_delaf_entry_filter : public false_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef false_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_false_text_delaf_entry_filter(): base_type()
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_text_delaf_entry_filter : public canonical_form_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_): base_type(canonical_form_)
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_text_delaf_entry_filter : public negated_canonical_form_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_): base_type(canonical_form_)
		{}
	};

	template<typename CaseNormalizer>
	class u_mandatory_pos_text_delaf_entry_filter : public mandatory_pos_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef mandatory_pos_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_mandatory_pos_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_): base_type(mandatory_pos_)
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_mandatory_pos_text_delaf_entry_filter : public negated_mandatory_pos_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_mandatory_pos_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_mandatory_pos_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_): base_type(mandatory_pos_)
		{}
	};

	template<typename CaseNormalizer>
	class u_forbidden_ppooss_text_delaf_entry_filter : public forbidden_ppooss_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef forbidden_ppooss_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_forbidden_ppooss_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_): base_type(std::move(forbidden_ppooss_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_forbidden_ppooss_text_delaf_entry_filter : public negated_forbidden_ppooss_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_forbidden_ppooss_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_forbidden_ppooss_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_): base_type(std::move(forbidden_ppooss_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_semantic_traits_text_delaf_entry_filter : public semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_semantic_traits_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_semantic_traits_text_delaf_entry_filter : public negated_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_semantic_traits_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_and_mandatory_pos_text_delaf_entry_filter : public canonical_form_and_mandatory_pos_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_and_mandatory_pos_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_and_mandatory_pos_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_): base_type(canonical_form_, mandatory_pos_)
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter : public negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_and_mandatory_pos_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_): base_type(canonical_form_, mandatory_pos_)
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter : public negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_and_forbidden_ppooss_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_and_semantic_traits_text_delaf_entry_filter : public canonical_form_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_and_semantic_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(canonical_form_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_and_semantic_traits_text_delaf_entry_filter : public negated_canonical_form_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_and_semantic_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(canonical_form_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter : public canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(canonical_form_, mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter : public negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_and_mandatory_pos_and_semantic_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(canonical_form_, mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter : public negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_and_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, mandatory_pos_, std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter : public negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_and_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, mandatory_pos_, std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter : public negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_and_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_and_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_canonical_form_and_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::u_lemma_string &canonical_form_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(canonical_form_, std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_mandatory_pos_and_semantic_traits_text_delaf_entry_filter : public mandatory_pos_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef mandatory_pos_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_mandatory_pos_and_semantic_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter : public negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_mandatory_pos_and_semantic_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter : public mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(mandatory_pos_, std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter : public negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_mandatory_pos_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(mandatory_pos_, std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_mandatory_pos_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(const typename u_text_delaf<CaseNormalizer>::ust_string &mandatory_pos_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(mandatory_pos_, std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter : public forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter : public negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_forbidden_ppooss_and_semantic_traits_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter : public forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter : public negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_forbidden_ppooss_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_forbidden_ppooss_and_semantic_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_ppooss_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(forbidden_ppooss_ref_), std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_semantic_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};

	template<typename CaseNormalizer>
	class u_negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter : public negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer>
	{
	public:
		typedef negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter<unichar, CaseNormalizer> base_type;
		u_negated_semantic_and_possible_flexional_traits_text_delaf_entry_filter(std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> mandatory_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::ust_set> forbidden_semantic_traits_ref_, std::unique_ptr<typename u_text_delaf<CaseNormalizer>::u_flexional_traits_list> possible_flexional_traits_ref_): base_type(std::move(mandatory_semantic_traits_ref_), std::move(forbidden_semantic_traits_ref_), std::move(possible_flexional_traits_ref_))
		{}
	};
} //namespace grape

#endif /*GRAPE_U_DELAF_ENTRY_FILTER_H*/
