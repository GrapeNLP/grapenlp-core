/*
 * GRAPE
 *
 * Copyright (C) 2011-2012 Universidad de Alicante <javier.sastre@telefonica.net>
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

#ifndef GRAPE_PCFGLA_TO_RTNO_H
#define GRAPE_PCFGLA_TO_RTNO_H

#include <algorithm>

#include <grape/pcfgla.h>
#include <grape/u_text_dico_word_meta_mask_factory.h>
#include <grape/u_compressed_dico_word_meta_mask_factory.h>
#include <grape/u_lexmask_factory.h>
#include <grape/lutw_rtno.h>

namespace grape
{
	template<typename InputIterator, typename Probability, typename IdxType>
	struct def_pcfgla_to_rtno_n_term_trie_data
	{
		typedef typename lutwns_rtno<InputIterator, Probability>::type machine;
		typedef typename machine::state_ref state_ref;
		typedef IdxType idx_type;

		idx_type count;
		state_ref* subinitial_state_refs;

		~def_pcfgla_to_rtno_n_term_trie_data()
		{
			if (subinitial_state_refs)
				delete [] subinitial_state_refs;
		}
	};

	template<typename InputIterator, typename Probability, typename IdxType>
	struct def_pcfgla_to_rtno_n_term_trie
	{
		typedef trie_with_data<unichar, def_pcfgla_to_rtno_n_term_trie_data<InputIterator, Probability, IdxType> > type;
	private:
		def_pcfgla_to_rtno_n_term_trie(){}
	};

	template<typename InputIterator>
	struct def_pcfgla_to_rtno_lexicon_trie_data
	{
		bool is_token;
		typename lexmask<InputIterator>::const_ref lmask_cref;

		def_pcfgla_to_rtno_lexicon_trie_data(): is_token(false), lmask_cref(NULL)
		{}

		~def_pcfgla_to_rtno_lexicon_trie_data()
		{
			if (lmask_cref)
				delete lmask_cref;
		}
	};

	template<typename InputIterator>
	struct def_pcfgla_to_rtno_lexicon_trie
	{
		typedef trie_with_data<unichar, def_pcfgla_to_rtno_lexicon_trie_data<InputIterator> > type;
	private:
		def_pcfgla_to_rtno_lexicon_trie(){}
	};

	template<typename InputIterator, typename Probability, typename IdxType, typename NTermTrieData = def_pcfgla_to_rtno_n_term_trie_data<InputIterator, Probability, IdxType>, typename LexiconTrieData = def_pcfgla_to_rtno_lexicon_trie_data<InputIterator>, typename CaseNormalizer=u_tolower>
	class pcfgla_to_rtno
	{
	public:
		typedef pcfgla<Probability, IdxType, NTermTrieData, LexiconTrieData> algebra;
		typedef typename algebra::n_term n_term;
		typedef typename algebra::n_term_trie n_term_trie;
		typedef typename algebra::n_term_trie::iterator n_term_trie_iterator;
		typedef typename algebra::n_term_trie_string_ref n_term_trie_string_ref;
		typedef typename algebra::n_term_trie_string_const_ref n_term_trie_string_const_ref;
		typedef typename algebra::binary_rule_set binary_rule_set;
		typedef typename algebra::unary_rule_set unary_rule_set;
		typedef typename algebra::lexical_rule_set lexical_rule_set;
		typedef typename algebra::binary_rule_set_iterator binary_rule_set_iterator;
		typedef typename algebra::unary_rule_set_iterator unary_rule_set_iterator;
		typedef typename algebra::lexical_rule_set_iterator lexical_rule_set_iterator;
		typedef typename algebra::lexicon_trie lexicon_trie;
		typedef typename algebra::lexicon_trie_iterator lexicon_trie_iterator;
		typedef typename algebra::lexicon_trie_string_ref lexicon_trie_string_ref;

		typedef typename lutwns_rtno<InputIterator, Probability>::type machine;
		typedef typename machine::state_ref state_ref;
		typedef typename machine::tag_output tag_output;

	private:
		u_trie_string_ref get_out_open_tag_label_ref_for_n_term(const n_term &nt, u_trie &out_tag_trie) const
		{
			u_trie_string_ref out_open_tag_label_ref(&out_tag_trie.epsilon());
			out_open_tag_label_ref = &(out_open_tag_label_ref->concat(static_cast<unichar>('(')));
			out_open_tag_label_ref = &(out_open_tag_label_ref->concat(*nt.label));
			out_open_tag_label_ref = &(out_open_tag_label_ref->concat(static_cast<unichar>(' ')));
			return out_open_tag_label_ref;
		}

		inline state_ref get_subinitial_state_ref_for_n_term(const n_term &nt) const
		{ return nt.label->data.subinitial_state_refs[nt.idx]; }

		//Builds the RTNO structure corresponding to every binary rule having a given non-terminal for head
		void add_binary_rules_for_head(const algebra &pcfgla_grammar, machine &rtno_grammar, u_trie &out_tag_trie, binary_rule_set_iterator &br_current) const
		{
			binary_rule_set_iterator br_first(br_current);
			binary_rule_set_iterator br_body_l_first;
			state_ref subinitial_state_ref(get_subinitial_state_ref_for_n_term(br_current->head));
			state_ref before_body_l_state_ref(subinitial_state_ref);
			state_ref before_body_r_state_ref;
			state_ref before_probability_state_ref;
			state_ref acceptor_state_ref(rtno_grammar.create_state(true));
			state_ref called_state_ref;
			u_trie_string_ref out_close_tag_string_ref(&out_tag_trie.epsilon());
			if (!br_first->head.label->starts_with(bar_n_term_first_label_char))
			{
				u_trie_string_ref out_open_tag_label_ref(get_out_open_tag_label_ref_for_n_term(br_first->head, out_tag_trie));
				tag_output out_open_tag(out_open_tag_label_ref, static_cast<Probability>(1.0));
				before_body_l_state_ref = rtno_grammar.create_state(false);
				subinitial_state_ref->add_inserting_transition(out_open_tag, before_body_l_state_ref);
				out_close_tag_string_ref = &(out_close_tag_string_ref->concat(')'));
			}
			do
			{
				before_body_r_state_ref = rtno_grammar.create_state(false);
				called_state_ref = get_subinitial_state_ref_for_n_term(br_current->body_l);
				before_body_l_state_ref->add_call_transition(called_state_ref, before_body_r_state_ref);
				binary_rule_set_iterator br_body_l_first(br_current);
				do
				{
					before_probability_state_ref = rtno_grammar.create_state(false);
					called_state_ref = get_subinitial_state_ref_for_n_term(br_current->body_r);
					before_body_r_state_ref->add_call_transition(called_state_ref, before_probability_state_ref);
					before_probability_state_ref->add_inserting_transition(tag_output(out_close_tag_string_ref, br_current->p), acceptor_state_ref);
					++br_current;
				} while (br_current != pcfgla_grammar.binary_rules.end() && br_first->head == br_current->head && br_body_l_first->body_l == br_current->body_l);
			} while (br_current != pcfgla_grammar.binary_rules.end() && br_first->head == br_current->head);
		}

		//Builds the RTNO structure corresponding to every unary rule having a given non-terminal for head
		void add_unary_rules_for_head(const algebra &pcfgla_grammar, machine &rtno_grammar, u_trie &out_tag_trie, unary_rule_set_iterator &ur_current, bool is_axiom) const
		{
			unary_rule_set_iterator ur_first(ur_current);
			state_ref subinitial_state_ref(get_subinitial_state_ref_for_n_term(ur_first->head));
			state_ref before_body_state_ref(subinitial_state_ref);
			state_ref before_probability_state_ref;
			state_ref acceptor_state_ref(rtno_grammar.create_state(true));
			state_ref called_state_ref;
			u_trie_string_ref out_close_tag_string_ref(&out_tag_trie.epsilon());
			if (!is_axiom && !ur_first->head.label->starts_with(bar_n_term_first_label_char))
			{
				u_trie_string_ref out_open_tag_label_ref(get_out_open_tag_label_ref_for_n_term(ur_first->head, out_tag_trie));
				tag_output out_open_tag(out_open_tag_label_ref, static_cast<Probability>(1.0));
				before_body_state_ref = rtno_grammar.create_state(false);
				subinitial_state_ref->add_inserting_transition(out_open_tag, before_body_state_ref);
				out_close_tag_string_ref = &(out_close_tag_string_ref->concat(')'));
			}
			do
			{
				before_probability_state_ref = rtno_grammar.create_state(false);
				called_state_ref = get_subinitial_state_ref_for_n_term(ur_current->body);
				before_body_state_ref->add_call_transition(called_state_ref, before_probability_state_ref);
				before_probability_state_ref->add_inserting_transition(tag_output(out_close_tag_string_ref, ur_current->p), acceptor_state_ref);
				++ur_current;
			} while (ur_current != pcfgla_grammar.unary_rules.end() && ur_first->head == ur_current->head);
		}

		//Builds the RTNO structure corresponding to every binary rule having a given non-terminal for head
		void add_binary_and_unary_rules_for_head(const algebra &pcfgla_grammar, machine &rtno_grammar, u_trie &out_tag_trie, binary_rule_set_iterator &br_current, unary_rule_set_iterator &ur_current) const
		{
			binary_rule_set_iterator bur_first(br_current);
			binary_rule_set_iterator br_body_l_first;
			state_ref subinitial_state_ref(get_subinitial_state_ref_for_n_term(bur_first->head));
			state_ref before_body_l_state_ref(subinitial_state_ref);
			state_ref before_body_r_state_ref;
			state_ref before_probability_state_ref;
			state_ref acceptor_state_ref(rtno_grammar.create_state(true));
			state_ref called_state_ref;
			u_trie_string_ref out_close_tag_string_ref(&out_tag_trie.epsilon());
			if (!bur_first->head.label->starts_with(bar_n_term_first_label_char))
			{
				u_trie_string_ref out_open_tag_label_ref(get_out_open_tag_label_ref_for_n_term(bur_first->head, out_tag_trie));
				tag_output out_open_tag(out_open_tag_label_ref, static_cast<Probability>(1.0));
				before_body_l_state_ref = rtno_grammar.create_state(false);
				subinitial_state_ref->add_inserting_transition(out_open_tag, before_body_l_state_ref);
				out_close_tag_string_ref = &(out_close_tag_string_ref->concat(')'));
			}
			do
			{
				//No more binary rules with current head or current unary rule has a body non-terminal less than left body non-terminal of current binary rule
				if (br_current == pcfgla_grammar.binary_rules.end() || br_current->head != bur_first->head || (ur_current != pcfgla_grammar.unary_rules.end() && ur_current->head == bur_first->head && ur_current->body < br_current->body_l))
				{
					before_probability_state_ref = rtno_grammar.create_state(false);
					called_state_ref = get_subinitial_state_ref_for_n_term(ur_current->body);
					before_body_l_state_ref->add_call_transition(called_state_ref, before_probability_state_ref);
					before_probability_state_ref->add_inserting_transition(tag_output(out_close_tag_string_ref, ur_current->p), acceptor_state_ref);
					++ur_current;
				}
				//No more unary rules with current head or current binary rule has a left body non-terminal less than body non-terminal of current unary rule
				else if (ur_current == pcfgla_grammar.unary_rules.end() || ur_current->head != bur_first->head || (br_current != pcfgla_grammar.binary_rules.end() && br_current->head == bur_first->head && br_current->body_l < ur_current->body))
				{
					before_body_r_state_ref = rtno_grammar.create_state(false);
					called_state_ref = get_subinitial_state_ref_for_n_term(br_current->body_l);
					before_body_l_state_ref->add_call_transition(called_state_ref, before_body_r_state_ref);
					binary_rule_set_iterator br_body_l_first(br_current);
					do
					{
						before_probability_state_ref = rtno_grammar.create_state(false);
						called_state_ref = get_subinitial_state_ref_for_n_term(br_current->body_r);
						before_body_r_state_ref->add_call_transition(called_state_ref, before_probability_state_ref);
						before_probability_state_ref->add_inserting_transition(tag_output(out_close_tag_string_ref, br_current->p), acceptor_state_ref);
						++br_current;
					} while (br_current != pcfgla_grammar.binary_rules.end() && bur_first->head == br_current->head && br_body_l_first->body_l == br_current->body_l);
				}
				//The left body non-terminal of the current binary rule is equal to the non-terminal of the body of the current unary rule
				else
				{
					before_body_r_state_ref = rtno_grammar.create_state(false);
					called_state_ref = get_subinitial_state_ref_for_n_term(ur_current->body);
					before_body_l_state_ref->add_call_transition(called_state_ref, before_body_r_state_ref);
					before_body_r_state_ref->add_inserting_transition(tag_output(out_close_tag_string_ref, ur_current->p), acceptor_state_ref);
					++ur_current;

					binary_rule_set_iterator br_body_l_first(br_current);
					do
					{
						before_probability_state_ref = rtno_grammar.create_state(false);
						called_state_ref = get_subinitial_state_ref_for_n_term(br_current->body_r);
						before_body_r_state_ref->add_call_transition(called_state_ref, before_probability_state_ref);
						before_probability_state_ref->add_inserting_transition(tag_output(out_close_tag_string_ref, br_current->p), acceptor_state_ref);
						++br_current;
					} while (br_current != pcfgla_grammar.binary_rules.end() && bur_first->head == br_current->head && br_body_l_first->body_l == br_current->body_l);
				}
			} while ((br_current != pcfgla_grammar.binary_rules.end() && bur_first->head == br_current->head) ||
					 (ur_current != pcfgla_grammar.unary_rules.end()  && bur_first->head == ur_current->head));
		}

		u_trie_string_ref get_out_open_tag_label_ref_for_pos(n_term_trie_string_ref pos_label_ref, u_trie &out_tag_trie) const
		{
			u_trie_string_ref out_open_tag_label_ref(&out_tag_trie.epsilon());
			out_open_tag_label_ref = &(out_open_tag_label_ref->concat(static_cast<unichar>('(')));
			out_open_tag_label_ref = &(out_open_tag_label_ref->concat(*pos_label_ref));
			out_open_tag_label_ref = &(out_open_tag_label_ref->concat(static_cast<unichar>(' ')));
			return out_open_tag_label_ref;
		}

		state_ref get_subinitial_state_ref_for_pos(n_term_trie_string_ref pos_label_ref, IdxType idx) const
		{ return pos_label_ref->data.subinitial_state_refs[idx]; }

		void add_path_for_tokens(machine &rtno_grammar, state_ref start, const std::list<lexicon_trie_string_ref> &tokens, state_ref end) const
		{
			typename std::list<lexicon_trie_string_ref>::const_iterator it(tokens.begin());
			typename std::list<lexicon_trie_string_ref>::const_iterator last_it(tokens.end());
			--last_it;
			state_ref target;
			while (it != last_it)
			{
				target = rtno_grammar.create_state(false);
				start->add_deleting_transition((*it)->data.lmask_cref, target);
				start = rtno_grammar.create_state(false);
				target->add_no_blank_epsilon_transition(start);
				++it;
			}
			start->add_deleting_transition((*it)->data.lmask_cref, end);
		}

		void add_lexical_rule_for_pos(const algebra& pcfgla_grammar, machine &rtno_grammar, u_trie &out_tag_trie, lexical_rule_set_iterator &lr_current) const
		{
			IdxType count(lr_current->head->data.count);
			lexical_rule_set_iterator lr_first(lr_current);
			u_trie_string_ref out_open_tag_label_ref(get_out_open_tag_label_ref_for_pos(lr_first->head, out_tag_trie));
			u_trie_string_ref out_close_tag_string_ref(&(out_tag_trie.epsilon().concat(')')));
			tag_output out_open_tag(out_open_tag_label_ref, static_cast<Probability>(1.0));
			array<state_ref> before_word_state_refs(count);
			array<state_ref> acceptor_state_refs(count);
			IdxType idx(0);
			for (; idx < count; ++idx)
			{
				before_word_state_refs[idx] = rtno_grammar.create_state(false);
				acceptor_state_refs[idx] = rtno_grammar.create_state(true);
				get_subinitial_state_ref_for_pos(lr_first->head, idx)->add_inserting_transition(out_open_tag, before_word_state_refs[idx]);
			}
			state_ref before_probability_state_ref;
			do
			{
				for (idx = 0; idx < count; ++idx)
				{
					before_probability_state_ref = rtno_grammar.create_state(false);
					add_path_for_tokens(rtno_grammar, before_word_state_refs[idx], lr_current->tokens, before_probability_state_ref);
					before_probability_state_ref->add_inserting_transition(tag_output(out_close_tag_string_ref, lr_current->pp[idx]), acceptor_state_refs[idx]);
				}
				++lr_current;
			} while (lr_current != pcfgla_grammar.lexical_rules.end() && lr_first->head == lr_current->head);
		}

		void create_subinitial_states(const algebra &pcfgla_grammar, machine &rtno_grammar) const
		{
			rtno_grammar.create_state(false); //global initial state
			n_term_trie_string_ref axiom_label_ref(pcfgla_grammar.get_axiom_label_ref());
			IdxType idx;
			for (n_term_trie_iterator it(pcfgla_grammar.n_term_dico.begin()); it != pcfgla_grammar.n_term_dico.end(); ++it)
			{
				if (it->data.count)
				{
					it->data.subinitial_state_refs = new state_ref[it->data.count];
					idx = 0;
					do
					{
						if (&(*it) == axiom_label_ref)
							it->data.subinitial_state_refs[idx] = rtno_grammar.initial_state();
						else it->data.subinitial_state_refs[idx] = rtno_grammar.create_state(false);
						++idx;
					} while (idx < it->data.count);
				}
			}
		}

		void create_lexical_masks(const algebra &pcfgla_grammar) const
		{
			for (lexicon_trie_iterator it(pcfgla_grammar.lexicon_dico.begin()); it != pcfgla_grammar.lexicon_dico.end(); ++it)
			{
				if (it->data.is_token)
				{
					if (u_is_letter(it->back()))
						it->data.lmask_cref = new case_sensitive_word_mask<InputIterator>(it->begin(), it->end(), it->size());
					else it->data.lmask_cref = new symbol_mask<InputIterator>(it->back());
				}
			}
		}

		machine& operator() (const algebra &pcfgla_grammar, machine &rtno_grammar, u_trie &out_tag_trie, u_dico_word_meta_mask_factory<InputIterator> &dico_lexmask_factory) const
		{
			create_subinitial_states(pcfgla_grammar, rtno_grammar);
			create_lexical_masks(pcfgla_grammar);
			binary_rule_set_iterator br_it(pcfgla_grammar.binary_rules.begin());
			binary_rule_set_iterator br_it_end(pcfgla_grammar.binary_rules.end());
			unary_rule_set_iterator ur_it(pcfgla_grammar.unary_rules.begin());
			unary_rule_set_iterator ur_it_end(pcfgla_grammar.unary_rules.end());

			while (br_it != br_it_end || ur_it != ur_it_end)
			{
				//Add binary rules for head not in unary rules
				if (ur_it == ur_it_end || (br_it != br_it_end && br_it->head < ur_it->head))
					add_binary_rules_for_head(pcfgla_grammar, rtno_grammar, out_tag_trie, br_it);
				//Add unary rules with head not in binary rules
				else if (br_it == br_it_end || (ur_it != ur_it_end && ur_it->head < br_it->head))
					add_unary_rules_for_head(pcfgla_grammar, rtno_grammar, out_tag_trie, ur_it, ur_it == pcfgla_grammar.axiom_unary_rules_first);
				//Add binary & unary rules with the same head
				else add_binary_and_unary_rules_for_head(pcfgla_grammar, rtno_grammar, out_tag_trie, br_it, ur_it);
			}

			lexical_rule_set_iterator lr_it(pcfgla_grammar.lexical_rules.begin());
			lexical_rule_set_iterator lr_it_end(pcfgla_grammar.lexical_rules.end());
			while (lr_it != lr_it_end)
				add_lexical_rule_for_pos(pcfgla_grammar, rtno_grammar, out_tag_trie, lr_it);
			return rtno_grammar;
		}

	public:
		machine& operator() (const algebra &pcfgla_grammar, machine &rtno_grammar, u_trie &out_tag_trie, u_text_delaf<CaseNormalizer> &dico) const
		{
			u_text_dico_word_meta_mask_factory<InputIterator, CaseNormalizer> dico_lexmask_factory(dico);
			return operator() (pcfgla_grammar, rtno_grammar, out_tag_trie, dico_lexmask_factory);
		}

		machine& operator() (const algebra &pcfgla_grammar, machine &rtno_grammar, u_trie &out_tag_trie, compressed_delaf &dico) const
		{
			u_compressed_dico_word_meta_mask_factory<InputIterator, CaseNormalizer> dico_lexmask_factory(dico);
			return operator() (pcfgla_grammar, rtno_grammar, out_tag_trie, dico_lexmask_factory);
		}
	};
} //namespace grape

#endif /*GRAPE_PCFGLA_TO_RTNO_H*/
