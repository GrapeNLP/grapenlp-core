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

#ifndef GRAPENLP_PCFGLA_READER_H
#define GRAPENLP_PCFGLA_READER_H

#include<iostream>

#include<grapenlp/pcfgla.h>

namespace grapenlp
{
	template<typename Probability, typename IdxType, typename NTermTrieData = def_pcfgla_n_term_trie_data<IdxType>, typename LexiconTrieData = def_pcfgla_lexicon_trie_data>
	class pcfgla_reader
	{
		typedef Probability probability;
		typedef IdxType idx_type;
		typedef pcfgla<probability, IdxType, NTermTrieData, LexiconTrieData> algebra;
		typedef typename algebra::n_term n_term;
		typedef typename algebra::n_term_trie n_term_trie;
		typedef typename algebra::n_term_trie_string_ref n_term_trie_string_ref;
		typedef typename algebra::n_term_trie_string_const_ref n_term_trie_string_const_ref;

		typedef typename algebra::lexicon_trie lexicon_trie;
		typedef typename algebra::lexicon_trie_string_ref lexicon_trie_string_ref;

		typedef typename algebra::unary_rule unary_rule;
		typedef typename algebra::binary_rule binary_rule;
		typedef typename algebra::lexical_rule lexical_rule;
		typedef typename algebra::unary_rule_set unary_rule_set;
		typedef typename algebra::binary_rule_set binary_rule_set;
		typedef typename algebra::lexical_rule_set lexical_rule_set;
		typedef typename algebra::unary_rule_set_iterator unary_rule_set_iterator;
		typedef typename algebra::binary_rule_set_iterator binary_rule_set_iterator;
		typedef typename algebra::lexical_rule_set_iterator lexical_rule_set_iterator;
		typedef typename algebra::unary_rule_set_const_iterator unary_rule_set_const_iterator;
		typedef typename algebra::binary_rule_set_const_iterator binary_rule_set_const_iterator;
		typedef typename algebra::lexical_rule_set_const_iterator lexical_rule_set_const_iterator;

		n_term read_n_term_in_grammar(FILE *grammar_file, n_term_trie_string_ref label_ref)
		{
			unichar c(u_fgetc(grammar_file));
			while (!feof(grammar_file) && c != '\n' && c != '^' && c != '_')
			{
				label_ref = &(*label_ref + c);
				c = u_fgetc(grammar_file);
			}
			if (feof(grammar_file))
				fatal_error("Unexpected EOF while reading non-terminal\n");
			if (c == '\n')
				fatal_error("Unexpected EOL while reading non-terminal\n");
			bool is_pos = (c == '_');
			if (!is_pos)
			{
				//Skip 'g'
				c = u_fgetc(grammar_file);
				if (c != 'g')
					fatal_error("Expected 'g' but got '%c' while reading non-terminal\n", c);
				//Skip '_'
				c = u_fgetc(grammar_file);
				if (c != '_')
					fatal_error("Expected '_' but got '%c' while reading non-terminal\n", c);
			}
			idx_type idx;
			u_fread_unsigned_int(grammar_file, idx);
			return n_term(label_ref, idx, is_pos);
		}

		//Read next n_term taking into account the first char that has already been read
		n_term read_n_term_in_grammar(FILE *grammar_file, n_term_trie &n_term_dico, unichar c)
		{
			n_term_trie_string_ref label_ref = &(n_term_dico.epsilon() + c);
			return read_n_term_in_grammar(grammar_file, label_ref);
		}

		//Read next n_term
		n_term read_n_term_in_grammar(FILE *grammar_file, n_term_trie &n_term_dico)
		{ return read_n_term_in_grammar(grammar_file, &n_term_dico.epsilon()); }

		void read_grammar_rule(FILE *grammar_file, algebra &grammar, unichar &c)
		{
			n_term head(read_n_term_in_grammar(grammar_file, grammar.n_term_dico, c));
			//Skip '-'
			u_fgetc(grammar_file);
			//Skip '>'
			u_fgetc(grammar_file);
			//Skip ' '
			u_fgetc(grammar_file);
			n_term body_l(read_n_term_in_grammar(grammar_file, grammar.n_term_dico));
			c = u_fgetc(grammar_file);
			if (u_is_digit(c))
			{
				probability p;
				//Also skips EOL
				c = u_fread_float(grammar_file, p, c);
				unary_rule un(head, body_l, p);
				if (head != body_l)
				{
					if (!grammar.add_unary_rule(head, body_l, p))
					{
						std::wcerr << "Repeated unary rule ";
						un.serialize(std::wcerr) << std::endl;
						exit(1);
					}
				}
				else
				{
					std::wcerr << "Warning: unitary rule \"";
					un.serialize(std::wcerr) << "\" omitted\n";
				}
				return;
			}
			n_term body_r(read_n_term_in_grammar(grammar_file, grammar.n_term_dico, c));
			probability p;
			//Also skips EOL
			c = u_fgetc(grammar_file);
			c = u_fread_float(grammar_file, p, c);
			binary_rule bn(head, body_l, body_r, p);
			if (!grammar.add_binary_rule(head, body_l, body_r, p))
			{
				std::wcerr << "Repeated binary rule ";
				bn.serialize(std::wcerr) << std::endl;
				exit(1);
			}
		}

		void read_grammar_file(FILE *grammar_file, algebra &grammar)
		{
			unichar c(u_fgetc(grammar_file));
			while (!feof(grammar_file) && (u_is_white(c) || c == 0))
				c = u_fgetc(grammar_file);
			while (!feof(grammar_file))
			{
				read_grammar_rule(grammar_file, grammar, c);
				while (!feof(grammar_file) && (u_is_white(c) || c == 0))
					c = u_fgetc(grammar_file);
			}
		}

		n_term_trie_string_ref read_n_term_in_lexicon(FILE *lexicon_file, n_term_trie_string_ref label_ref)
		{
			unichar c(u_fgetc(lexicon_file));
			while (!feof(lexicon_file) && c != '\n' && c != ' ')
			{
				label_ref = &(*label_ref + c);
				c = u_fgetc(lexicon_file);
			}
			if (feof(lexicon_file))
				fatal_error("Unexpected EOF while reading non-terminal in lexicon\n");
			if (c == '\n')
				fatal_error("Unexpected EOL while reading non-terminal in lexicon\n");
			return label_ref;
		}

		//Read next n_term taking into account the first char that has already been read
		n_term_trie_string_ref read_n_term_in_lexicon(FILE *lexicon_file, n_term_trie &n_term_dico, unichar c)
		{
			n_term_trie_string_ref label_ref = &(n_term_dico.epsilon() + c);
			return read_n_term_in_lexicon(lexicon_file, label_ref);
		}

		void read_tokens(FILE *lexicon_file, lexicon_trie_string_ref epsilon, std::list<lexicon_trie_string_ref> &tokens)
		{
			unichar c(u_fgetc(lexicon_file));
			lexicon_trie_string_ref s_ref;
			while (!feof(lexicon_file) && c != ' ' && c != '\n')
			{
				if (u_is_letter(c))
				{
					s_ref = epsilon;
					do s_ref = &(s_ref->concat(c));
					while (!feof(lexicon_file) && u_is_letter(c = u_fgetc(lexicon_file)));
					s_ref->data.is_token = true;
					tokens.push_back(s_ref);
				}
				else
				{
					s_ref = &(epsilon->concat(c));
					s_ref->data.is_token = true;
					tokens.push_back(s_ref);
					c = u_fgetc(lexicon_file);
				}
			}
			if (feof(lexicon_file))
				fatal_error("Unexpected EOF while reading term\n");
			if (c == '\n')
				fatal_error("Unexpected EOL while reading term\n");
		}

		void read_lexicon_probabilities(FILE *lexicon_file, array<Probability> &pp, unichar &c)
		{
			//Skip '['
			c = u_fgetc(lexicon_file);
			if (c != '[')
				fatal_error("Expected '[' but got %c\n", c);
			c = u_fgetc(lexicon_file);
			if (!u_is_float_first(c))
				fatal_error("Expected first character of of first lexical probability but got '%c'\n", c);

			typename array<Probability>::iterator it(pp.begin());
			c = u_fread_float(lexicon_file, *it, c);
			for (++it; it != pp.end(); ++it)
			{
				if (c != ',')
					fatal_error("Expected ',' after lexical probability but got '%c'\n", c);
				c = u_fgetc(lexicon_file);
				if (c != ' ')
					fatal_error("Expected space after comma after lexical probability but got '%c'\n", c);
				c = u_fgetc(lexicon_file);
				if (!u_is_float_first(c))
					fatal_error("Expected first digit of lexical probability but got '%c'\n", c);
				c = u_fread_float(lexicon_file, *it, c);
				if (feof(lexicon_file))
					fatal_error("Unexpected EOF while reading lexical probabilities\n");
			}
			if (c != ']')
				fatal_error("Expected ']' closing the list of lexical probabilities but got %c\n", c);
		}

		void read_lexical_rule(FILE *lexicon_file, algebra &grammar, lexicon_trie_string_ref unk_prefix_ref, unichar &c)
		{
			n_term_trie_string_ref head_ref(read_n_term_in_lexicon(lexicon_file, grammar.n_term_dico, c));
			std::list<lexicon_trie_string_ref> token_refs;
			read_tokens(lexicon_file, &grammar.lexicon_dico.epsilon(), token_refs);
			array<Probability> pp(head_ref->data.count);
			read_lexicon_probabilities(lexicon_file, pp, c);
			//Ignore unknown word rules
			if (token_refs.front() != unk_prefix_ref)
			{
				std::pair<lexical_rule_set_iterator, bool> result(grammar.add_lexical_rule(head_ref, token_refs, pp));
				if (!result.second)
				{
					result.first->serialize(std::wcerr << "Repeated lexicon rule: ");
					exit(1);
				}
			}
		}

		void read_lexicon_file(FILE *lexicon_file, algebra &grammar)
		{
			unichar c(u_fgetc(lexicon_file));
			lexicon_trie_string_ref unk_prefix(&(grammar.lexicon_dico.epsilon().concat('U').concat('N').concat('K')));
			while (!feof(lexicon_file) && (u_is_white(c) || c == 0))
				c = u_fgetc(lexicon_file);
			while (!feof(lexicon_file))
			{
				read_lexical_rule(lexicon_file, grammar, unk_prefix, c);
				c = u_fgetc(lexicon_file);
				while (!feof(lexicon_file) && (u_is_white(c) || c == 0))
					c = u_fgetc(lexicon_file);
			}
		}
	public:
		void operator() (FILE *grammar_file, FILE *lexicon_file, algebra &grammar)
		{
			read_grammar_file(grammar_file, grammar);
			n_term_trie_string_ref axiom_n_term_label_ref(grammar.n_term_dico.get(default_axiom_label.begin(), default_axiom_label.end()));
			n_term axiom_n_term(axiom_n_term_label_ref, default_axiom_idx, default_axiom_is_pos);
			grammar.set_axiom_iterators(axiom_n_term);
			read_lexicon_file(lexicon_file, grammar);
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_PCFGLA_READER_H*/
