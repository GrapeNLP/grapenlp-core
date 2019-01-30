/*
 * GRAPENLP
 *
 * Copyright (C) 2011 Universidad de Alicante <javier.sastre@telefonica.net>
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

#ifndef GRAPENLP_PCFGLA_H
#define GRAPENLP_PCFGLA_H

#include <list>
#include <grapenlp/array.h>
#include <grapenlp/u_trie.h>
#include <grapenlp/lrb_tree_set.h>
#include <grapenlp/iostream.h>
#include <grapenlp/pcfgla_constants.h>

namespace grapenlp
{
	template<typename IdxType>
	struct def_pcfgla_n_term_trie_data
	{
		typedef IdxType idx_type;
		idx_type count;
	};

	template<typename IdxType>
	struct def_pcfgla_n_term_trie
	{
		typedef trie_with_data<unichar, def_pcfgla_n_term_trie_data<IdxType> > type;
	private:
		def_pcfgla_n_term_trie(){}
	};

	struct def_pcfgla_lexicon_trie_data
	{
		bool is_token;
	};

	typedef trie_with_data<unichar, def_pcfgla_lexicon_trie_data> def_pcfgla_lexicon_trie;

	template<typename Probability, typename IdxType, typename NTermTrieData = def_pcfgla_n_term_trie_data<IdxType>, typename LexiconTrieData = def_pcfgla_lexicon_trie_data>
	struct pcfgla
	{
		typedef Probability probability;
		typedef IdxType idx_type;
		typedef trie_with_data<unichar, NTermTrieData> n_term_trie;
		typedef typename n_term_trie::string::ref n_term_trie_string_ref;
		typedef typename n_term_trie::string::const_ref n_term_trie_string_const_ref;
		typedef trie_with_data<unichar, LexiconTrieData> lexicon_trie;
		typedef typename lexicon_trie::string::ref lexicon_trie_string_ref;
		typedef typename lexicon_trie::iterator lexicon_trie_iterator;

		struct n_term
		{
			n_term_trie_string_ref label;
			idx_type idx;
			bool is_pos;

			n_term(n_term_trie_string_ref label_, idx_type idx_, bool is_pos_): label(label_), idx(idx_), is_pos(is_pos_)
			{}

			n_term(const n_term &nt): label(nt.label), idx(nt.idx), is_pos(nt.is_pos)
			{}

			bool operator< (const n_term& nt) const
			{
				if (label < nt.label)
					return true;
				if (nt.label < label)
					return false;
				return idx < nt.idx;
			}

			bool operator== (const n_term &nt) const
			{ return label == nt.label && idx == nt.idx; }

			bool operator!= (const n_term &nt) const
			{ return label != nt.label || idx != nt.idx; }

			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
			{
				out << (*label);
				if (!is_pos)
					out << "^g";
				return out << "_" << idx;
			}

			static n_term min()
			{ return n_term(0, 0, false); }

			static n_term max()
			{ return n_term(reinterpret_cast<n_term_trie_string_ref>(std::numeric_limits<std::size_t>::max()), std::numeric_limits<idx_type>::max(), false); }
		};

		struct binary_rule
		{
			n_term head;
			n_term body_l;
			n_term body_r;
			probability p;

			binary_rule(const n_term &head_, const n_term &body_l_, const n_term &body_r_, probability p_): head(head_), body_l(body_l_), body_r(body_r_), p(p_)
			{}

			binary_rule(const binary_rule &bn): head(bn.head), body_l(bn.body_l), body_r(bn.body_r), p(bn.p)
			{}

			bool operator< (const binary_rule& bn) const
			{
				if (head < bn.head)
					return true;
				if (bn.head < head)
					return false;
				if (body_l < bn.body_l)
					return true;
				if (bn.body_l < body_l)
					return false;
				return body_r < bn.body_r;
				//For each head and body there is a unique probability, hence the probability field is not taken into account here
			}

			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
			{
				head.serialize(out) << " -> ";
				body_l.serialize(out) << ' ';
				return body_r.serialize(out) << ' ' << p;
			}
		};

		struct unary_rule
		{
			n_term head;
			n_term body;
			probability p;

			unary_rule(const n_term &head_, const n_term &body_, probability p_): head(head_), body(body_), p(p_)
			{}

			unary_rule(const unary_rule &un): head(un.head), body(un.body), p(un.p)
			{}

			bool operator< (const unary_rule& un) const
			{
				if (head < un.head)
					return true;
				if (un.head < head)
					return false;
				return body < un.body;
				//For each head and body there is a unique probability, hence the probability field is not taken into account here
			}

			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
			{
				head.serialize(out) << " -> ";
				return body.serialize(out) << ' ' << p;
			}

			//Returns the unary rule ---with a given non-terminal as head--- that compares the least
			static unary_rule min(const n_term &head = n_term::min())
			{ return unary_rule(head, n_term::min(), std::numeric_limits<Probability>::min()); }

			//Returns the unary rule ---with a given non-terminal as head--- that compares the greatest
			static unary_rule max(const n_term &head = n_term::max())
			{ return unary_rule(head, n_term::max(), std::numeric_limits<Probability>::max()); }
		};

		struct lexical_rule
		{
			n_term_trie_string_ref head;
			std::list<lexicon_trie_string_ref> tokens;
			array<Probability> pp;

			lexical_rule(n_term_trie_string_ref head_, std::list<lexicon_trie_string_ref> &tokens_, array<Probability> &pp_): head(head_), tokens(), pp()
			{
				tokens.swap(tokens_);
				pp.swap(pp_);
			}

			bool operator< (const lexical_rule &lr) const
			{
				if (head < lr.head)
					return true;
				if (lr.head < head)
					return false;
				return lexicographical_compare(tokens.begin(), tokens.end(), lr.tokens.begin(), lr.tokens.end());
			}

			template<typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
			{
				std::basic_string<CharT> separator;
				separator += static_cast<CharT>(',');
				separator += static_cast<CharT>(' ');
				head->serialize(out) << ' ';
				serialize_ptr_sequence(out, tokens.begin(), tokens.end());
				if (!pp.empty())
				{
					out << " [";
	                serialize_sequence(out, pp.begin(), pp.end(), separator) << ']';
				}
				return out;
			}
		};

		typedef lrb_tree_set<binary_rule> binary_rule_set;
		typedef lrb_tree_set<unary_rule> unary_rule_set;
		typedef lrb_tree_set<lexical_rule> lexical_rule_set;
		typedef typename binary_rule_set::iterator binary_rule_set_iterator;
		typedef typename unary_rule_set::iterator unary_rule_set_iterator;
		typedef typename lexical_rule_set::iterator lexical_rule_set_iterator;
		typedef typename binary_rule_set::const_iterator binary_rule_set_const_iterator;
		typedef typename unary_rule_set::const_iterator unary_rule_set_const_iterator;
		typedef typename lexical_rule_set::const_iterator lexical_rule_set_const_iterator;


		n_term_trie &n_term_dico;
		lexicon_trie &lexicon_dico;
		binary_rule_set binary_rules;
		unary_rule_set unary_rules;
		lexical_rule_set lexical_rules;
		//Axiom rules seem to be all unary... no need for iterators for axiom binary rules
		unary_rule_set_const_iterator axiom_unary_rules_first;
		unary_rule_set_const_iterator axiom_unary_rules_last;

		pcfgla(n_term_trie &n_term_dico_, lexicon_trie &lexicon_dico_): n_term_dico(n_term_dico_), lexicon_dico(lexicon_dico_), binary_rules(), unary_rules(), axiom_unary_rules_first(unary_rules.end()), axiom_unary_rules_last(unary_rules.end())
		{}

		void reset_n_term_count(const n_term &nt)
		{
			if (nt.idx >= nt.label->data.count)
				nt.label->data.count = nt.idx + 1;
		}

		bool add_binary_rule(const n_term &head, const n_term &body_l, const n_term &body_r, probability p)
		{
			reset_n_term_count(head);
			reset_n_term_count(body_l);
			reset_n_term_count(body_r);
			return binary_rules.insert(binary_rule(head, body_l, body_r, p)).second;
		}

		bool add_unary_rule(const n_term &head, const n_term &body, probability p)
		{
			reset_n_term_count(head);
			reset_n_term_count(body);
			return unary_rules.insert(unary_rule(head, body, p)).second;
		}

		std::pair<lexical_rule_set_iterator, bool> add_lexical_rule(n_term_trie_string_ref head_ref, std::list<lexicon_trie_string_ref> &token_refs, array<Probability> &pp)
		{ return lexical_rules.insert(lexical_rule(head_ref, token_refs, pp)); }

		bool has_axiom() const
		{ return axiom_unary_rules_first != unary_rules.end(); }

		n_term_trie_string_ref get_axiom_label_ref() const
		{
			if (has_axiom())
				return axiom_unary_rules_first->head.label;
			return NULL;
		}

		void set_axiom_iterators(const n_term &axiom_n_term)
		{
			axiom_unary_rules_first = unary_rules.lower_bound(unary_rule::min(axiom_n_term));
			if (axiom_unary_rules_first == unary_rules.end() || axiom_unary_rules_first->head != axiom_n_term)
			{
				axiom_unary_rules_first = axiom_unary_rules_last = unary_rules.end();
				return;
			}
			axiom_unary_rules_last = unary_rules.upper_bound(unary_rule::max(axiom_n_term));
		}

		template<typename CharT, typename Traits>
		std::basic_ostream<CharT, Traits>& serialize(std::basic_ostream<CharT, Traits>& out) const
		{
			for (typename binary_rule_set::const_iterator i(binary_rules.begin()); i != binary_rules.end(); ++i)
				i->serialize(out) << '\n';
			for (typename unary_rule_set::const_iterator i(unary_rules.begin()); i != unary_rules.end(); ++i)
				i->serialize(out) << '\n';
			for (typename lexical_rule_set::const_iterator i(lexical_rules.begin()); i != lexical_rules.end(); ++i)
				i->serialize(out) << '\n';
			return out;
		}
	};

	template<typename CharT, typename Traits, typename Probability, typename NTermTrieData>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits>& out, const typename pcfgla<Probability, NTermTrieData>::n_term &nt)
	{ return nt.serialize(out); }

	template<typename CharT, typename Traits, typename Probability, typename NTermTrieData>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits>& out, const typename pcfgla<Probability, NTermTrieData>::binary_rule &bn)
	{ return bn.serialize(out); }

	template<typename CharT, typename Traits, typename Probability, typename NTermTrieData>
	std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits>& out, const typename pcfgla<Probability, NTermTrieData>::unary_rule &un)
	{ return un.serialize(out); }

	template<typename Probability, typename NTermTrieData>
	std::ostream& operator<< (std::ostream& out, const pcfgla<Probability, NTermTrieData> &grammar)
	{ return grammar.serialize(out); }
} //namespace grapenlp

#endif /*GRAPENLP_PCFGLA_H*/
