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

#ifndef GRAPENLP_UL_MANAGER_H
#define GRAPENLP_UL_MANAGER_H

#ifdef TRACE

#include <iostream>
#include <fstream>
#include <locale>

#endif

#include <map>
#include <set>

#include <grapenlp/disable_directives.h>
#include <grapenlp/string.h>
#include <grapenlp/u_array.h>
#include <grapenlp/u_trie.h>
#include <grapenlp/u_context_reader.h>

//Tokenization
#include <grapenlp/tokenization.h>

//Dico readers
#ifndef DISABLE_TEXT_DICO

#include <grapenlp/u_text_delaf_reader.h>

#endif
#ifndef DISABLE_COMPRESSED_DICO

#include <grapenlp/compressed_delaf_reader.h>

#endif

//Grammar readers
#ifndef DISABLE_LUA_GRAMMAR
#include <grapenlp/ulua_fst2_reader.h>
#endif
#ifndef DISABLE_LUAW_GRAMMAR
#include <grapenlp/uluaw_fst2_reader.h>
#endif
#ifndef DISABLE_LUX_GRAMMAR
#include <grapenlp/ulx_fst2_reader.h>
#endif
#ifndef DISABLE_LUXW_GRAMMAR

#include <grapenlp/ulxw_fst2_reader.h>

#endif

//RTNOs
#ifndef DISABLE_LUA_GRAMMAR
#include <grapenlp/lua_rtno.h>
#endif
#ifndef DISABLE_LUAW_GRAMMAR
#include <grapenlp/luaw_rtno.h>
#endif
#ifndef DISABLE_LUX_GRAMMAR
#include <grapenlp/lux_rtno.h>
#endif
#ifndef DISABLE_LUXW_GRAMMAR

#include <grapenlp/luxw_rtno.h>

#endif
#ifndef DISABLE_WEIGHTED_GRAMMARS

#include <grapenlp/lw_rtno_weight_tagger.h>
#include <grapenlp/weight_transformer_traits.h>

#endif

//FPRTNs
#ifndef DISABLE_LUA_GRAMMAR
#include <grapenlp/lua_output_fprtn.h>
#include <grapenlp/lua_output_fprtn_zpps.h>
#endif
#ifndef DISABLE_LUAW_GRAMMAR
#include <grapenlp/luaw_output_fprtn.h>
#include <grapenlp/luaw_output_fprtn_zpps.h>
#include <grapenlp/luaw_output_fprtn_top.h>
#endif
#ifndef DISABLE_LUX_GRAMMAR
#include <grapenlp/lux_output_fprtn.h>
#include <grapenlp/lux_output_fprtn_zpps.h>
#endif
#ifndef DISABLE_LUXW_GRAMMARS

#include <grapenlp/luxw_output_fprtn.h>
#include <grapenlp/luxw_output_fprtn_zpps.h>
#include <grapenlp/luxw_output_fprtn_top.h>

#endif

//Parsers
#include <grapenlp/parser.h>

#ifndef DISABLE_DEPTH_FIRST_PARSER
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#include <grapenlp/lua_depth_first_parser.h>
#include <grapenlp/luaw_depth_first_parser.h>
#include <grapenlp/lx_depth_first_parser.h>
#include <grapenlp/lxw_depth_first_parser.h>
#endif
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
#include <grapenlp/lua_depth_first_parser_no_output.h>
#include <grapenlp/luaw_depth_first_parser_no_output.h>
#include <grapenlp/lx_depth_first_parser_no_output.h>
#include <grapenlp/lxw_depth_first_parser_no_output.h>
#endif
#endif //DISABLE_DEPTH_FIRST_PARSER

#ifndef DISABLE_BREADTH_FIRST_PARSER
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#include <grapenlp/lua_breadth_first_parser.h>
#include <grapenlp/luaw_breadth_first_parser.h>
#include <grapenlp/lx_breadth_first_parser.h>
#include <grapenlp/lxw_breadth_first_parser.h>
#endif
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
#include <grapenlp/lua_breadth_first_parser_no_output.h>
#include <grapenlp/luaw_breadth_first_parser_no_output.h>
#include <grapenlp/lx_breadth_first_parser_no_output.h>
#include <grapenlp/lxw_breadth_first_parser_no_output.h>
#endif
#endif //DISABLE_BREADTH_FIRST_PARSER

#ifndef DISABLE_EARLEY_PARSER
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#include <grapenlp/lua_earley_parser.h>
#include <grapenlp/luaw_earley_parser.h>
#include <grapenlp/lx_earley_parser.h>
#include <grapenlp/lxw_earley_parser.h>
#endif
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
#include <grapenlp/lua_earley_parser_no_output.h>
#include <grapenlp/luaw_earley_parser_no_output.h>
#include <grapenlp/lx_earley_parser_no_output.h>
#include <grapenlp/lxw_earley_parser_no_output.h>
#endif
#endif //DISABLE_EARLEY_PARSER

#ifndef DISABLE_TO_FPRTN_PLAIN_PARSERS
#include <grapenlp/lua_to_fprtn_parser.h>
#include <grapenlp/luaw_to_fprtn_parser.h>
#include <grapenlp/lx_to_fprtn_parser.h>
#include <grapenlp/lxw_to_fprtn_parser.h>
#include <grapenlp/output_fprtn_prune.h>
#endif

#ifndef DISABLE_TO_FPRTN_ZPPS_PARSERS
#include <grapenlp/lua_to_fprtn_zpps_parser.h>
#include <grapenlp/lua_output_fprtn_zpps_prune.h>
#include <grapenlp/luaw_to_fprtn_zpps_parser.h>
#include <grapenlp/luaw_output_fprtn_zpps_prune.h>
#include <grapenlp/lx_to_fprtn_zpps_parser.h>
#include <grapenlp/lux_output_fprtn_zpps_prune.h>
#include <grapenlp/lxw_to_fprtn_zpps_parser.h>
#include <grapenlp/luxw_output_fprtn_zpps_prune.h>
#endif

#ifndef DISABLE_TO_FPRTN_TOP_PARSERS

#include <grapenlp/lua_to_fprtn_top_parser.h>
#include <grapenlp/luaw_to_fprtn_top_parser.h>
#include <grapenlp/luaw_output_fprtn_top_prune.h>
#include <grapenlp/lx_to_fprtn_top_parser.h>
#include <grapenlp/lxw_to_fprtn_top_parser.h>
#include <grapenlp/luxw_output_fprtn_top_prune.h>

#endif

#ifndef DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER
#include <grapenlp/lua_fprtn_breadth_first_expander.h>
#include <grapenlp/luaw_fprtn_breadth_first_expander.h>
#include <grapenlp/lux_fprtn_breadth_first_expander.h>
#include <grapenlp/luxw_fprtn_breadth_first_expander.h>
#endif

#ifndef DISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER
#include <grapenlp/lua_fprtn_blackboard_set_expander.h>
#include <grapenlp/lua_output_fprtn_zpps_prune.h>
#include <grapenlp/luaw_fprtn_blackboard_set_expander.h>
#include <grapenlp/luaw_output_fprtn_zpps_prune.h>
#include <grapenlp/lux_fprtn_blackboard_set_expander.h>
#include <grapenlp/lux_output_fprtn_zpps_prune.h>
#include <grapenlp/luxw_fprtn_blackboard_set_expander.h>
#include <grapenlp/luxw_output_fprtn_zpps_prune.h>
#endif

#ifndef DISABLE_TO_FPRTN_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR

#include <grapenlp/luaw_fprtn_top_blackboard_extractor.h>
#include <grapenlp/luaw_output_fprtn_top_prune.h>
#include <grapenlp/luxw_fprtn_top_blackboard_extractor.h>
#include <grapenlp/luxw_output_fprtn_top_prune.h>

#endif

#ifdef SIMPLIFIED_OUTPUT

#include <grapenlp/simple_segment_array_x_weight.h>

#endif

#ifdef SERIALIZE_OUTPUT
//Translators of extraction segments to MovistarBot commands
#ifndef DISABLE_UNWEIGHTED_GRAMMARS
#include <grapenlp/movistarbot_out_serializer.h>
#endif
#ifndef DISABLE_WEIGHTED_GRAMMARS
#include <grapenlp/movistarbot_weighted_out_serializer.h>
#endif

//Infinitive form translator for MovistarBot use case
#ifndef DISABLE_TEXT_DICO
#include <grapenlp/to_canonical_form.h>
#endif
#ifndef DISABLE_COMPRESSED_DICO
#include <grapenlp/to_decompressed_canonical_form.h>
#endif
#endif //SERIALIZE_OUTPUT

#include <grapenlp/u_manager_constants.h>

//Grammar serializers for debugging
#ifdef TRACE

#include <grapenlp/rtno_to_dot_serializer.h>

#endif

namespace grapenlp {
    template<typename InputIterator, typename WeightTransformer>
    class ul_manager {
    public:
#ifndef DISABLE_WEIGHTED_GRAMMARS
        typedef WeightTransformer weight_transformer;
        typedef weight_transformer_traits<WeightTransformer> the_weight_transformer_traits;
        typedef typename weight_transformer::result_type weight;
#endif

        //Token types
        typedef typename token<InputIterator>::ref_list::const_iterator token_iterator;

        //DELAF type
#ifndef DISABLE_TEXT_DICO
        typedef text_delaf_entry_filter<unichar, u_tolower> my_text_delaf_entry_filter;
#endif
#ifndef DISABLE_COMPRESSED_DICO
        typedef compressed_delaf_entry_filter<normalizer_iterator<u_tolower, InputIterator> > my_compressed_delaf_entry_filter;
#endif

        //Grammar types
#ifdef TRACE
#ifndef DISABLE_LUA_GRAMMAR
        typedef typename luans_rtno<InputIterator, u_context_mask>::type my_lua_rtno;
#endif
#ifndef DISABLE_LUAW_GRAMMAR
        typedef typename luawns_rtno<InputIterator, weight, u_context_mask>::type my_luaw_rtno;
#endif
#ifndef DISABLE_LUX_GRAMMAR
        typedef typename luxns_rtno<InputIterator, u_context_mask>::type my_lux_rtno;
#endif
#ifndef DISABLE_LUXW_GRAMMAR
        typedef typename luxwns_rtno<InputIterator, weight, u_context_mask>::type my_luxw_rtno;
#endif
#else
#ifndef DISABLE_LUA_GRAMMAR
        typedef typename lua_rtno<InputIterator, u_context_mask>::type my_lua_rtno;
#endif
#ifndef DISABLE_LUAW_GRAMMAR
        typedef typename luaw_rtno<InputIterator, weight, u_context_mask>::type my_luaw_rtno;
#endif
#ifndef DISABLE_LUX_GRAMMAR
        typedef typename lux_rtno<InputIterator, u_context_mask>::type my_lux_rtno;
#endif
#ifndef DISABLE_LUXW_GRAMMAR
        typedef typename luxw_rtno<InputIterator, weight, u_context_mask>::type my_luxw_rtno;
#endif
#endif

        //Grammar reader types
#ifndef DISABLE_LUA_GRAMMAR
        typedef ulua_fst2_reader<InputIterator> my_ulua_fst2_reader;
#endif
#ifndef DISABLE_LUAW_GRAMMAR
        typedef uluaw_fst2_reader<InputIterator, weight_transformer> my_uluaw_fst2_reader;
#endif
#ifndef DISABLE_LUX_GRAMMAR
        typedef ulx_fst2_reader<InputIterator> my_ulx_fst2_reader;
#endif
#ifndef DISABLE_LUXW_GRAMMAR
        typedef ulxw_fst2_reader<InputIterator, weight_transformer> my_ulxw_fst2_reader;
#endif
        typedef trie_with_ptr_data<unichar, u_array> ua_trie;

#if !defined(DISABLE_PARSERS_WITH_FINAL_OUTPUT) && !defined(DISABLE_WEIGHTED_GRAMMARS)
        //Output set element types
        typedef pool_sequence_x_weight<array_fake_pool<unichar>, weight> fake_pool_u_array_x_weight;
        typedef pool_sequence_x_weight<trie_string_ref_pool<unichar>, weight> pool_u_trie_string_x_weight;
#endif

        //Output set types
        typedef std::set<segment_map<token_iterator, unichar, STD> > segment_map_set;
        typedef lrb_tree_set<segment_map<token_iterator, unichar, LRB_TREE> > segment_lrb_tree_map_lrb_tree_set;
        typedef lrb_tree_set_3w<segment_map<token_iterator, unichar, LRB_TREE_3W> > segment_lrb_tree_map_3w_lrb_tree_set_3w;

#ifndef DISABLE_WEIGHTED_GRAMMARS
        typedef std::set<segment_map_x_weight<token_iterator, unichar, weight, STD> > segment_map_x_weight_set;
        typedef lrb_tree_set<segment_map_x_weight<token_iterator, unichar, weight, LRB_TREE> > segment_lrb_tree_map_x_weight_lrb_tree_set;
        typedef lrb_tree_set_3w<segment_map_x_weight<token_iterator, unichar, weight, LRB_TREE_3W> > segment_lrb_tree_map_3w_x_weight_lrb_tree_set_3w;
#endif

        //Parsing function reference type
        typedef std::size_t (ul_manager::*parse_func_ref)();

        typedef std::size_t (ul_manager::*parse_and_get_fprtn_stats_func_ref)(std::size_t &, std::size_t &,
                                                                              std::size_t &, std::size_t &);

    private:
        rtno_type grammar_type;

        void *grammar_ref;
        void *dico_ref;
        u_context the_context;
#if !defined(DISABLE_TEXT_DICO) && !defined(DISABLE_COMPRESSED_DICO)
        bool dico_is_in_text_format;
#endif

        typename token<InputIterator>::ref_list the_token_list;
        bool hasnt_white_at_begin;
        bool hasnt_white_at_end;
        assoc_container_impl_choice the_output_set_impl_choice;
        void *output_set_ref;
#if SIMPLIFIED_OUTPUT
        simple_segment_array_x_weight_array<InputIterator, unichar, weight> simplified_weighted_output;
#endif
#if defined(SERIALIZED_OUTPUT)
        u_array ua;
        void *v_pos_filter_ref;
#endif
        std::unique_ptr<ul_tag_input_trie<unichar, InputIterator> > ult_ref;
        std::unique_ptr<ua_trie> uat_ref;
        std::unique_ptr<u_out_bound::trie> uobt_ref;
#if defined(SERIALIZED_OUTPUT)
        std::unique_ptr<movistarbot_tag_dico> td_ref;
#endif
        parse_func_ref the_parse_func_ref;
        parse_and_get_fprtn_stats_func_ref the_parse_and_get_fprtn_stats_func_ref;

    public:
        ul_manager() :
                grammar_type(),
                grammar_ref(NULL),
                dico_ref(NULL),
#if !defined(DISABLE_TEXT_DICO) && !defined(DISABLE_COMPRESSED_DICO)
                dico_is_in_text_format(false),
#endif
                the_context(),
                the_token_list(),
                hasnt_white_at_begin(true),
                hasnt_white_at_end(true),
                the_output_set_impl_choice(LRB_TREE_3W),
                output_set_ref(NULL),
#ifdef SIMPLIFIED_OUTPUT
                simplified_weighted_output(),
#endif
#if defined(SERIALIZED_OUTPUT)
        ua(),
        v_pos_filter_ref(NULL),
#endif
                ult_ref(),
                uat_ref(),
                uobt_ref(),
#if defined(SERIALIZED_OUTPUT)
                td_ref(),
#endif
                the_parse_func_ref(NULL),
                the_parse_and_get_fprtn_stats_func_ref(NULL) {}

        ul_manager(rtno_type grammar_type_, const std::string &grammar_path_name, const std::string &dico_path_name) :
                grammar_type(),
                grammar_ref(NULL),
                dico_ref(NULL),
#if !defined(DISABLE_TEXT_DICO) && !defined(DISABLE_COMPRESSED_DICO)
                dico_is_in_text_format(false),
#endif
                the_context(),
                the_token_list(),
                hasnt_white_at_begin(true),
                hasnt_white_at_end(true),
                the_output_set_impl_choice(LRB_TREE_3W),
                output_set_ref(NULL),
#ifdef SIMPLIFIED_OUTPUT
                simplified_weighted_output(),
#endif
#if defined(SERIALIZED_OUTPUT)
        ua(),
        v_pos_filter_ref(NULL),
#endif
                ult_ref(),
                uat_ref(),
                uobt_ref(),
#if defined(SERIALIZED_OUTPUT)
                td_ref(),
#endif
                the_parse_func_ref(NULL),
                the_parse_and_get_fprtn_stats_func_ref(NULL) {
            load_grammar_and_dico(grammar_type_, grammar_path_name, dico_path_name);
        }

        assoc_container_impl_choice get_output_set_impl_choice() { return the_output_set_impl_choice; }

#ifndef DISABLE_LUA_GRAMMAR
        my_lua_rtno& get_lua_grammar()
        { return *static_cast<my_lua_rtno*>(grammar_ref); }

        void delete_lua_grammar()
        { delete static_cast<my_lua_rtno*>(grammar_ref); }
#endif
#ifndef DISABLE_LUAW_GRAMMAR
        my_luaw_rtno& get_luaw_grammar()
        { return *static_cast<my_luaw_rtno*>(grammar_ref); }

        void delete_luaw_grammar()
        { delete static_cast<my_luaw_rtno*>(grammar_ref); }
#endif
#ifndef DISABLE_LUX_GRAMMAR
        my_lux_rtno& get_lux_grammar()
        { return *static_cast<my_lux_rtno*>(grammar_ref); }

        void delete_lux_grammar()
        { delete static_cast<my_lux_rtno*>(grammar_ref); }
#endif
#ifndef DISABLE_LUXW_GRAMMAR

        my_luxw_rtno &get_luxw_grammar() { return *static_cast<my_luxw_rtno *>(grammar_ref); }

        void delete_luxw_grammar() { delete static_cast<my_luxw_rtno *>(grammar_ref); }

#endif

        void delete_grammar() {
            switch (grammar_type) {
#ifndef DISABLE_LUA_GRAMMAR
                case LEXMASK_X_LETTER_ARRAY_RTNO:
                    delete_lua_grammar();
                    break;
#endif
#ifndef DISABLE_LUAW_GRAMMAR
                case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                    delete_luaw_grammar();
                    break;
#endif
#ifndef DISABLE_LUX_GRAMMAR
                case LEXMASK_X_EXTRACTION_RTNO:
                    delete_lux_grammar();
                    break;
#endif
#ifndef DISABLE_LUXW_GRAMMAR
                case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                    delete_luxw_grammar();
                    break;
#endif
                default:
                    fatal_error("Unsupported grammar type (delete grammar)\n");
            }
        }

#ifndef DISABLE_TEXT_DICO

        tolower_u_text_delaf &get_text_delaf() { return *static_cast<tolower_u_text_delaf *>(dico_ref); }

        void delete_text_delaf() { delete static_cast<tolower_u_text_delaf *>(dico_ref); }

#if defined(SERIALIZED_OUTPUT)
        my_text_delaf_entry_filter& get_text_v_pos_filter()
        { return *static_cast<my_text_delaf_entry_filter*>(v_pos_filter_ref); }

        void delete_text_v_pos_filter()
        { delete static_cast<my_text_delaf_entry_filter*>(v_pos_filter_ref); }
#endif
#endif

#ifndef DISABLE_COMPRESSED_DICO

        compressed_delaf &get_compressed_delaf() { return *static_cast<compressed_delaf *>(dico_ref); }

        void delete_compressed_delaf() { delete static_cast<compressed_delaf *>(dico_ref); }

        u_context& get_context()
        {
            return the_context;
        }

#if defined(SERIALIZED_OUTPUT)
        my_compressed_delaf_entry_filter& get_compressed_v_pos_filter()
        { return *static_cast<my_compressed_delaf_entry_filter*>(v_pos_filter_ref); }

        void delete_compressed_v_pos_filter()
        { delete static_cast<my_compressed_delaf_entry_filter*>(v_pos_filter_ref); }
#endif
#endif

#if defined(DISABLE_TEXT_DICO)
        void delete_delaf()
        { delete_compressed_delaf();	}

#if defined(SERIALIZED_OUTPUT)
        void delete_v_pos_filter()
        { delete_compressed_v_pos_filter();	}
#endif
#elif defined(DISABLE_COMPRESSED_DICO)
        void delete_delaf()
        { delete_text_delaf();	}

#if defined(SERIALIZED_OUTPUT)
        void delete_v_pos_filter()
        { delete_text_v_pos_filter(); }
#endif
#else

        void delete_delaf() {
            if (dico_is_in_text_format)
                delete_text_delaf();
            else delete_compressed_delaf();
        }

#if defined(SERIALIZED_OUTPUT)
        void delete_v_pos_filter()
        {
            if (dico_is_in_text_format)
                delete_text_v_pos_filter();
            else delete_compressed_v_pos_filter();
        }
#endif
#endif //DISABLE_TEXT_DICO

        template<assoc_container_impl_choice acic>
        typename set_impl_selector<acic, u_array>::type &
        get_output_u_array_set() { return *static_cast<typename set_impl_selector<acic, u_array>::type *>(output_set_ref); }

        template<assoc_container_impl_choice acic>
        typename set_impl_selector<acic, segment_map<token_iterator, unichar, acic> >::type &
        get_output_segment_map_set() { return *static_cast<typename set_impl_selector<acic, segment_map<token_iterator, unichar, acic> >::type *>(output_set_ref); }

#ifndef DISABLE_WEIGHTED_GRAMMARS

        template<assoc_container_impl_choice acic>
        typename set_impl_selector<acic, segment_map_x_weight<token_iterator, unichar, weight, acic> >::type &
        get_output_segment_map_x_weight_set() { return *static_cast<typename set_impl_selector<acic, segment_map_x_weight<token_iterator, unichar, weight, acic> >::type *>(output_set_ref); }

#ifdef SIMPLIFIED_OUTPUT

        const simple_segment_array_x_weight_array<InputIterator, unichar, weight> &
        get_simplified_weighted_output() { return simplified_weighted_output; }

#endif
#endif

        template<assoc_container_impl_choice acic>
        void
        clear_output_u_array_set() { static_cast<typename set_impl_selector<acic, u_array>::type *>(output_set_ref)->clear(); }

        template<assoc_container_impl_choice acic>
        void
        clear_output_segment_map_set() { static_cast<typename set_impl_selector<acic, segment_map<token_iterator, unichar, acic> >::type *>(output_set_ref)->clear(); }

#ifndef DISABLE_WEIGHTED_GRAMMARS

        template<assoc_container_impl_choice acic>
        void
        clear_output_segment_map_x_weight_set() { static_cast<typename set_impl_selector<acic, segment_map_x_weight<token_iterator, unichar, weight, acic> >::type *>(output_set_ref)->clear(); }

#endif

        template<assoc_container_impl_choice acic>
        void
        delete_output_u_array_set() { delete static_cast<typename set_impl_selector<acic, u_array>::type *>(output_set_ref); }

        template<assoc_container_impl_choice acic>
        void
        delete_output_segment_map_set() { delete static_cast<typename set_impl_selector<acic, segment_map<token_iterator, unichar, acic> >::type *>(output_set_ref); }

#ifndef DISABLE_WEIGHTED_GRAMMARS

        template<assoc_container_impl_choice acic>
        void
        delete_output_segment_map_x_weight_set() { delete static_cast<typename set_impl_selector<acic, segment_map_x_weight<token_iterator, unichar, weight, acic> >::type *>(output_set_ref); }

#endif

        void delete_output_set() {
            switch (grammar_type) {
                case LEXMASK_X_LETTER_ARRAY_RTNO:
                case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                    switch (the_output_set_impl_choice) {
#ifndef DISABLE_STD_BS
                        case STD:
                            delete_output_u_array_set<STD>();
                            break;
#endif
#ifndef DISABLE_LRB_TREE_BS
                            case LRB_TREE: delete_output_u_array_set<LRB_TREE>(); break;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                            case LRB_TREE_3W: delete_output_u_array_set<LRB_TREE_3W>(); break;
#endif
                        default:
                            fatal_error("Unsupported output set implementation\n");
                    }
                    break;
                case LEXMASK_X_EXTRACTION_RTNO:
                    switch (the_output_set_impl_choice) {
#ifndef DISABLE_STD_BS
                        case STD:
                            delete_output_segment_map_set<STD>();
                            break;
#endif
#ifndef DISABLE_LRB_TREE_BS
                            case LRB_TREE: delete_output_segment_map_set<LRB_TREE>(); break;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                            case LRB_TREE_3W: delete_output_segment_map_set<LRB_TREE_3W>(); break;
#endif
                        default:
                            fatal_error("Unsupported output set implementation\n");
                    }
                    break;
#ifndef DISABLE_WEIGHTED_GRAMMARS
                case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                    switch (the_output_set_impl_choice) {
#ifndef DISABLE_STD_BS
                        case STD:
                            delete_output_segment_map_x_weight_set<STD>();
                            break;
#endif
#ifndef DISABLE_LRB_TREE_BS
                            case LRB_TREE: delete_output_segment_map_x_weight_set<LRB_TREE>(); break;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                            case LRB_TREE_3W: delete_output_segment_map_x_weight_set<LRB_TREE_3W>(); break;
#endif
                        default:
                            fatal_error("Unsupported output set implementation\n");
                    }
                    break;
#endif //DIABLE_WEIGHTED_GRAMMARS
                default:
                    fatal_error("Unsupported grammar type (delete output set)\n");
            }
        }

        void reset_output_set(assoc_container_impl_choice the_output_set_impl_choice) {
            if (output_set_ref) {
                if (this->the_output_set_impl_choice == the_output_set_impl_choice)
                    return;
                delete_output_set();
            }
            this->the_output_set_impl_choice = the_output_set_impl_choice;
            switch (grammar_type) {
                case LEXMASK_X_LETTER_ARRAY_RTNO:
                case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                    switch (the_output_set_impl_choice) {
#ifndef DISABLE_STD_BS
                        case STD:
                            output_set_ref = new typename set_impl_selector<STD, u_array>::type();
                            break;
#endif
#ifndef DISABLE_LRB_TREE_BS
                        case LRB_TREE:
                            output_set_ref = new typename set_impl_selector<LRB_TREE, u_array>::type();
                            break;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                        case LRB_TREE_3W:
                            output_set_ref = new typename set_impl_selector<LRB_TREE_3W, u_array>::type();
                            break;
#endif
                        default:
                            fatal_error("Unsupported output set implementation\n");
                    }
                    break;
                case LEXMASK_X_EXTRACTION_RTNO:
                    switch (the_output_set_impl_choice) {
#ifndef DISABLE_STD_BS
                        case STD:
                            output_set_ref = new segment_map_set();
                            break;
#endif
#ifndef DISABLE_LRB_TREE_BS
                        case LRB_TREE:
                            output_set_ref = new segment_lrb_tree_map_lrb_tree_set();
                            break;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                        case LRB_TREE_3W:
                            output_set_ref = new segment_lrb_tree_map_3w_lrb_tree_set_3w();
                            break;
#endif
                        default:
                            fatal_error("Unsupported output set implementation\n");
                    }
                    break;
#ifndef DISABLE_WEIGHTED_GRAMMARS
                case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                    switch (the_output_set_impl_choice) {
#ifndef DISABLE_STD_BS
                        case STD:
                            output_set_ref = new segment_map_x_weight_set();
                            break;
#endif
#ifndef DISABLE_LRB_TREE_BS
                        case LRB_TREE:
                            output_set_ref = new segment_lrb_tree_map_x_weight_lrb_tree_set();
                            break;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                        case LRB_TREE_3W:
                            output_set_ref = new segment_lrb_tree_map_3w_x_weight_lrb_tree_set_3w();
                            break;
#endif
                        default:
                            fatal_error("Unsupported output set implementation\n");
                    }
                    break;
#endif //DISABLE_WEIGHTED_GRAMMARS
                default:
                    fatal_error("Unsupported grammar type (reset output set)\n");
            }
        }

        ~ul_manager() {
            if (grammar_is_loaded())
                delete_grammar();
            if (output_set_ref)
                delete_output_set();
            if (dico_is_loaded())
                delete_delaf();
#if defined(SERIALIZED_OUTPUT)
            if (v_pos_filter_ref)
                delete_v_pos_filter();
#endif
        }

        const rtno_type &get_grammar_type() { return grammar_type; }

#if defined(SERIALIZED_OUTPUT)
        const u_array& get_output_u_array()
        { return ua; }
#endif

    private:
#ifndef DISABLE_TEXT_DICO

    void load_text_dico(const std::string &dico_path_name)
    {
            FILE *dico_file(u_fopen(dico_path_name.c_str(), U_READ));
            if (dico_file == NULL)
                fatal_error("Unable to open dico file to read\n");
#ifdef TRACE
            std::wcout << L"Loading text dico\n";
#endif
            if (dico_is_loaded())
                delete_delaf();
#if !defined(DISABLE_TEXT_DICO) && !defined(DISABLE_COMPRESSED_DICO)
            dico_is_in_text_format = true;
#endif
            dico_ref = new tolower_u_text_delaf;
            u_read<u_tolower>(dico_file, get_text_delaf());
            u_fclose(dico_file);

#if defined(SERIALIZED_OUTPUT)
            tolower_u_text_delaf::ust_string::const_ref v_pos_ref(get_text_delaf().ppooss.get('V'));
            if (!v_pos_ref)
                fatal_error("'V' POS (Verb part-of-speech) not found in DELAF\n");
            if (v_pos_filter_ref)
                delete_v_pos_filter();
            v_pos_filter_ref = new u_mandatory_pos_text_delaf_entry_filter<u_tolower>(*v_pos_ref);
#endif
        }

#endif //DISABLE_TEXT_DICO
#ifndef DISABLE_COMPRESSED_DICO

        void load_compressed_dico(const std::string &dico_bin_path_name, const std::string &dico_inf_path_name)
        {
            if (dico_is_loaded())
                delete_delaf();
#if !defined(DISABLE_TEXT_DICO) && !defined(DISABLE_COMPRESSED_DICO)
            dico_is_in_text_format = false;
#endif
            FILE *bin_delaf_file(fopen(dico_bin_path_name.c_str(), U_READ));
            if (!bin_delaf_file)
                fatal_error("Unable to open bin delaf file\n");
            FILE *inf_delaf_file(u_fopen(dico_inf_path_name.c_str(), U_READ));
            if (!inf_delaf_file)
                fatal_error("Unable to open inf delaf file\n");
#ifdef TRACE
            std::wcout << L"Loading compressed dico\n";
#endif
            dico_ref = new compressed_delaf;
            u_read(bin_delaf_file, inf_delaf_file, get_compressed_delaf());
            fclose(bin_delaf_file);
            fclose(inf_delaf_file);

#if defined(SERIALIZED_OUTPUT)
            compressed_delaf::ust_string::const_ref v_pos_ref(get_compressed_delaf().ppooss.get('V'));
            if (!v_pos_ref)
                fatal_error("'V' POS (Verb part-of-speech) not found in DELAF\n");
            if (v_pos_filter_ref)
                delete_v_pos_filter();
            v_pos_filter_ref = new mandatory_pos_compressed_delaf_entry_filter<normalizer_iterator<u_tolower, InputIterator> >(*v_pos_ref);
#endif
        }

#endif //DISABLE_COMPRESSED_DICO

    public:
        void load_grammar(rtno_type grammar_type, const std::string &grammar_path_name)
        {
            if (!grapenlp::string(grammar_path_name).ends_with(".fst2"))
                fatal_error("Unsupported grammar format (expected .fst2 file)\n");

            FILE *grammar_file = u_fopen(grammar_path_name.c_str(), U_READ);
            if (grammar_file == NULL)
                fatal_error("Unable to open grammar file to read\n");

            ult_ref.reset(new ul_tag_input_trie<unichar, InputIterator>);
            uat_ref.reset(new ua_trie);
            uobt_ref.reset(new u_out_bound::trie);
#if defined(SERIALIZED_OUTPUT)
            td_ref.reset(new movistarbot_tag_dico(uobt_ref->epsilon()));
#endif
#ifdef TRACE
            std::wcout << L"Loading grammar\n";
#endif
            if (grammar_is_loaded())
                delete_grammar();
            switch (grammar_type) {
                case LEXMASK_X_LETTER_ARRAY_RTNO:
#ifdef DISABLE_LUA_GRAMMAR
                    fatal_error("Unweighted letter grammar type has been disabled\n");
#else
                grammar_ref = new my_lua_rtno;
#ifdef DISABLE_TEXT_DICO
                my_ulua_fst2_reader()(grammar_file, get_lua_grammar(), *ult_ref, *uat_ref, get_compressed_delaf(), the_context);
#elif defined(DISABLE_COMPRESSED_DICO)
                my_ulua_fst2_reader()(grammar_file, get_lua_grammar(), *ult_ref, *uat_ref, get_text_delaf(), the_context);
#else
                if (dico_is_in_text_format)
                    my_ulua_fst2_reader()(grammar_file, get_lua_grammar(), *ult_ref, *uat_ref, get_text_delaf(), the_context);
                else my_ulua_fst2_reader()(grammar_file, get_lua_grammar(), *ult_ref, *uat_ref, get_compressed_delaf(), the_context);
#endif //DISABLE_TEXT_DICO
#endif //DISABLE_LUA_GRAMMAR
                    break;
                case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
#ifdef DISABLE_LUAW_GRAMMAR
                    fatal_error("Weighted letter grammar type has been disabled\n");
#else
                grammar_ref = new my_luaw_rtno;
#ifdef DISABLE_TEXT_DICO
                my_uluaw_fst2_reader()(grammar_file, get_luaw_grammar(), *ult_ref, *uat_ref, get_compressed_delaf(), the_context);
#elif defined(DISABLE_COMPRESSED_DICO)
                my_uluaw_fst2_reader()(grammar_file, get_luaw_grammar(), *ult_ref, *uat_ref, get_text_delaf(), the_context);
#else
                if (dico_is_in_text_format)
                    my_uluaw_fst2_reader()(grammar_file, get_luaw_grammar(), *ult_ref, *uat_ref, get_text_delaf(), the_context);
                else my_uluaw_fst2_reader()(grammar_file, get_luaw_grammar(), *ult_ref, *uat_ref, get_compressed_delaf(), the_context);
#endif //DISABLE_TEXT_DICO
#endif //DISABLE_LUAW_GRAMMAR
                    break;
                case LEXMASK_X_EXTRACTION_RTNO:
#ifdef DISABLE_LUX_GRAMMAR
                    fatal_error("Unweighted extraction grammar type has been disabled\n");
#else
                grammar_ref = new my_lux_rtno;
#ifdef DISABLE_TEXT_DICO
                my_ulx_fst2_reader()(grammar_file, get_lux_grammar(), *ult_ref, *uobt_ref, get_compressed_delaf(), the_context);
#elif defined(DISABLE_COMPRESSED_DICO)
                my_ulx_fst2_reader()(grammar_file, get_lux_grammar(), *ult_ref, *uobt_ref, get_text_delaf(), the_context);
#else
                if (dico_is_in_text_format)
                    my_ulx_fst2_reader()(grammar_file, get_lux_grammar(), *ult_ref, *uobt_ref, get_text_delaf(), the_context);
                else my_ulx_fst2_reader()(grammar_file, get_lux_grammar(), *ult_ref, *uobt_ref, get_compressed_delaf(), the_context);
#endif //DISABLE_TEXT_DICO
#endif //DISABLE_LUX_GRAMMAR
                    break;
                case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
#ifdef DISABLE_LUXW_GRAMMAR
                    fatal_error("Weighted extraction grammar type has been disabled\n");
#else
                    grammar_ref = new my_luxw_rtno;
#ifdef DISABLE_TEXT_DICO
                    my_ulxw_fst2_reader()(grammar_file, get_luxw_grammar(), *ult_ref, *uobt_ref, get_compressed_delaf(), the_context);
#elif defined(DISABLE_COMPRESSED_DICO)
                    my_ulxw_fst2_reader()(grammar_file, get_luxw_grammar(), *ult_ref, *uobt_ref, get_text_delaf(), the_context);
#else
                    if (dico_is_in_text_format)
                        my_ulxw_fst2_reader()(grammar_file, get_luxw_grammar(), *ult_ref, *uobt_ref, get_text_delaf(), the_context);
                    else
                        my_ulxw_fst2_reader()(grammar_file, get_luxw_grammar(), *ult_ref, *uobt_ref,
                                              get_compressed_delaf(), the_context);
#endif //DISABLE_TEXT_DICO
                    lw_rtno_weight_tag<InputIterator, typename my_luxw_rtno::tag_output, u_context_mask>(get_luxw_grammar());
#endif //DISABLE_LUXW_GRAMMAR
                    break;
                default:
                    fatal_error("Unknown grammar type\n");
            }
            u_fclose(grammar_file);

            if (output_set_ref && grammar_type != this->grammar_type &&
                !(grammar_type == LEXMASK_X_LETTER_ARRAY_RTNO &&
                  this->grammar_type == LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO) &&
                !(grammar_type == LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO &&
                  this->grammar_type == LEXMASK_X_LETTER_ARRAY_RTNO))
                delete_output_set();
            this->grammar_type = grammar_type;
#ifdef TRACE
            std::wcout << L"Converting grammar to dot" << std::endl;
            std::wofstream fout("../grammar.dot");
            fout.imbue(std::locale(setlocale(LC_CTYPE, NULL)));
            if (!fout)
                std::wcerr << L"Unable to open file \"grammar.dot\" for writing" << std::endl;
            std::wcout << L"Writing grammar.dot" << std::endl;
            switch (grammar_type) {
#ifndef DISABLE_LUA_GRAMMAR
                case LEXMASK_X_LETTER_ARRAY_RTNO:
                    rtno_to_dot_serialize(fout, "axioma", L'q', get_lua_grammar());
                    break;
#endif
#ifndef DISABLE_LUAW_GRAMMAR
                case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                    rtno_to_dot_serialize(fout, "axioma", L'q', get_luaw_grammar());
                    break;
#endif
#ifndef DISABLE_LUX_GRAMMAR
                case LEXMASK_X_EXTRACTION_RTNO:
                    rtno_to_dot_serialize(fout, "axioma", L'q', get_lux_grammar());
                    break;
#endif
#ifndef DISABLE_LUXW_GRAMMAR
                case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                    rtno_to_dot_serialize(fout, "axioma", L'q', get_luxw_grammar());
                    break;
#endif
                default:
                    fatal_error("Unsupported grammar type (RTNO to dot)\n");
            }
#endif //TRACE
        }

        void load_grammar_and_dico(rtno_type grammar_type, const std::string &grammar_path_name, const std::string &dico_path_name)
        {
            grapenlp::string dpn(dico_path_name);
            if (dpn.ends_with(".dic"))
#ifdef DISABLE_TEXT_DICO
                fatal_error("Text dictionary format has been disabled");
#else
                load_text_dico(dpn);
#endif
            else if (dpn.ends_with(".bin"))
#ifdef DISABLE_COMPRESSED_DICO
                fatal_error("Compressed dictionary format has been disabled");
#else
                load_compressed_dico(dpn, dpn.substr(0, dpn.size() - 3).append("inf"));
#endif
            else if (dpn.ends_with(".inf"))
#ifdef DISABLE_COMPRESSED_DICO
                fatal_error("Compressed dictionary format has been disabled");
#else
                load_compressed_dico(dico_path_name.substr(0, dpn.size() - 3).append("bin"), dpn);
#endif
            else fatal_error("Unsupported dictionary format (expected .dic, .bin or .inf file\n");
            load_grammar(grammar_type, grammar_path_name);
        }

        void load_input_context(const std::string &input_context_path_name)
        {
#ifdef TRACE
            std::wcout << L"Loading input context" << std::endl;
#endif
            the_context.clear_map();
            FILE *input_context_file(u_fopen(input_context_path_name.c_str(), U_READ));
            if (input_context_file == NULL)
                fatal_error("Unable to open input context file to read\n");
            u_read(input_context_file, the_context);
        }

        bool grammar_is_loaded() { return grammar_ref; }

        bool dico_is_loaded() { return dico_ref; }

        std::size_t grammar_state_count() {
            switch (grammar_type) {
#ifndef DISABLE_LUA_GRAMMAR
                case LEXMASK_X_LETTER_ARRAY_RTNO: return get_lua_grammar().state_count();
#endif
#ifndef DISABLE_LUAW_GRAMMAR
                case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO: return get_luaw_grammar().state_count();
#endif
#ifndef DISABLE_LUX_GRAMMAR
                case LEXMASK_X_EXTRACTION_RTNO: return get_lux_grammar().state_count();
#endif
#ifndef DISABLE_LUXW_GRAMMAR
                case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                    return get_luxw_grammar().state_count();
#endif
                default:
                    fatal_error("Unsupported grammar type (grammar state count)\n");
            }
            return 0;
        }

        std::size_t grammar_transition_count() {
            switch (grammar_type) {
#ifndef DISABLE_LUA_GRAMMAR
                case LEXMASK_X_LETTER_ARRAY_RTNO: return get_lua_grammar().transition_count();
#endif
#ifndef DISABLE_LUAW_GRAMMAR
                case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO: return get_luaw_grammar().transition_count();
#endif
#ifndef DISABLE_LUX_GRAMMAR
                case LEXMASK_X_EXTRACTION_RTNO: return get_lux_grammar().transition_count();
#endif
#ifndef DISABLE_LUXW_GRAMMAR
                case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                    return get_luxw_grammar().transition_count();
#endif
                default:
                    fatal_error("Unsupported grammar type (grammar transition count)\n");
            }
            return 0;
        }

        std::size_t tokenize(InputIterator input_begin, InputIterator input_end) {
#ifdef TRACE
            std::wcout << L"Tokenizing\n";
#endif
            the_token_list.clear();
            hasnt_white_at_begin = false;
            hasnt_white_at_end = false;
            if (input_begin != input_end) {
                grapenlp::tokenize(input_begin, input_end, the_token_list);
                if (!the_token_list.empty()) {
                    hasnt_white_at_begin = the_token_list.front()->begin == input_begin;
                    hasnt_white_at_end = the_token_list.back()->end == input_end;
                }
            }
            return the_token_list.size();
        }

//*********************
#ifndef DISABLE_PARSERS_WITH_FINAL_OUTPUT
#if !defined(DISABLE_UNWEIGHTED_GRAMMARS) && !defined(DISABLE_TRIE_STRING_PARSERS)
        template<assoc_container_impl_choice output_set_impl_choice>
        std::size_t u_trie_string_ref_set_to_output_u_array_set(const typename set_impl_selector<output_set_impl_choice, u_trie_string_ref>::type &utsrs)
        {
            for (typename set_impl_selector<output_set_impl_choice, u_trie_string_ref>::type::const_iterator it(utsrs.begin()); it != utsrs.end(); ++it)
            {
                u_array a((*it)->size());
                (*it)->to_array(a);
                get_output_u_array_set<output_set_impl_choice>().insert(a);
            }
            return get_output_u_array_set<output_set_impl_choice>().size();
        }
#endif //!defined(DISABLE_UNWEIGHTED_GRAMMARS) && !defined(DISABLE_TRIE_STRING_PARSERS)
#ifndef DISABLE_WEIGHTED_GRAMMARS
#ifndef DISABLE_TRIE_STRING_PARSERS

        template<assoc_container_impl_choice output_set_impl_choice>
        std::size_t pool_sequence_x_weight_set_to_output_u_array_set(
                const typename set_impl_selector<output_set_impl_choice, pool_u_trie_string_x_weight>::type &psxws) {
            if (psxws.empty())
                return 0;
            const pool_u_trie_string_x_weight &psxw(*(--psxws.end()));
            u_array a(psxw.ps->size());
            psxw.ps->to_array(a);
            get_output_u_array_set<output_set_impl_choice>().insert(a);
            return psxws.size();
        }

        template<assoc_container_impl_choice output_set_impl_choice>
        std::size_t pool_reverse_sequence_x_weight_set_to_output_u_array_set(
                const typename set_impl_selector<output_set_impl_choice, pool_u_trie_string_x_weight>::type &psxws) {
            if (psxws.empty())
                return 0;
            const pool_u_trie_string_x_weight &psxw(*(--psxws.end()));
            u_array a(psxw.ps->size());
            psxw.ps->to_reverse_array(a);
            get_output_u_array_set<output_set_impl_choice>().insert(a);
            return psxws.size();
        }

#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS

        template<assoc_container_impl_choice output_set_impl_choice>
        std::size_t pool_sequence_x_weight_set_to_output_u_array_set(
                const typename set_impl_selector<output_set_impl_choice, fake_pool_u_array_x_weight>::type &psxws) {
            if (!psxws.empty())
                get_output_u_array_set<output_set_impl_choice>().insert((--psxws.end())->ps);
            return psxws.size();
        }

#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_WEIGHTED_GRAMMARS
#endif //DISABLE_PARSERS_WITH_FINAL_OUTPUT
//*********************
#ifndef DISABLE_DEPTH_FIRST_PARSER
#ifndef DISABLE_LUA_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<sequence_impl_choice sic>
        std::size_t exe_my_lua_depth_first_parser_no_output()
        {
            bool accept(typename lua_depth_first_parser_no_output_impl_selector<InputIterator, token_iterator, sic>::type()(get_lua_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_depth_first_parser_with_trie_stacks_and_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            trie_string_ref_pool<unichar> tsrp;
            typename set_impl_selector<output_set_impl_choice, u_trie_string_ref>::type utsrs;
            typename lua_depth_first_parser_impl_selector<InputIterator, token_iterator, TRIE_STRINGS, output_set_impl_choice>::type()(get_lua_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, utsrs, tsrp.empty());
            return u_trie_string_ref_set_to_output_u_array_set<output_set_impl_choice>(utsrs);
        }
#endif
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_depth_first_parser_with_array_stacks_and_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_depth_first_parser_impl_selector<InputIterator, token_iterator, ARRAYS, output_set_impl_choice>::type()(get_lua_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, get_output_u_array_set<output_set_impl_choice>());
            return get_output_u_array_set<output_set_impl_choice>().size();
        }
#endif
#endif //DISABLE_PARSERS_WITH_OUTPUT
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<sequence_impl_choice sic>
        std::size_t exe_my_luaw_depth_first_parser_no_output()
        {
            bool accept(typename luaw_depth_first_parser_no_output_impl_selector<InputIterator, token_iterator, weight, sic>::type()(get_luaw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_depth_first_parser_with_trie_stacks_and_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            trie_string_ref_pool<unichar> tsrp;
            pool_u_trie_string_x_weight empty_psxw(tsrp.empty(), the_weight_transformer_traits::identity());
            typename set_impl_selector<output_set_impl_choice, pool_u_trie_string_x_weight>::type psxws;
            typename luaw_depth_first_parser_impl_selector<InputIterator, token_iterator, weight_transformer, TRIE_STRINGS, output_set_impl_choice>::type()(get_luaw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, psxws, empty_psxw);
            return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
        }
#endif
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_depth_first_parser_with_array_stacks_and_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            typename set_impl_selector<output_set_impl_choice, fake_pool_u_array_x_weight>::type psxws;
            typename luaw_depth_first_parser_impl_selector<InputIterator, token_iterator, weight_transformer, ARRAYS, output_set_impl_choice>::type()(get_luaw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, psxws);
            return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
        }
#endif
#endif //DISABLE_PARSERS_WITH_OUTPUT
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<sequence_impl_choice sic>
        std::size_t exe_my_lux_depth_first_parser_no_output()
        {
            bool accept(typename lx_depth_first_parser_no_output_impl_selector<InputIterator, token_iterator, unichar, sic>::type()(get_lux_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
        template<sequence_impl_choice sic, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lux_depth_first_parser()
        {
            clear_output_segment_map_set<output_set_impl_choice>();
            typename lx_depth_first_parser_impl_selector<InputIterator, token_iterator, unichar, sic, output_set_impl_choice>::type()(get_lux_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, get_output_segment_map_set<output_set_impl_choice>());
            return get_output_segment_map_set<output_set_impl_choice>().size();
        }
#endif
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<sequence_impl_choice sic>
        std::size_t exe_my_luxw_depth_first_parser_no_output()
        {
            bool accept(typename lxw_depth_first_parser_no_output_impl_selector<InputIterator, token_iterator, unichar, weight, sic>::type()(get_luxw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
        template<sequence_impl_choice sic, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luxw_depth_first_parser()
        {
            clear_output_segment_map_x_weight_set<output_set_impl_choice>();
            typename lxw_depth_first_parser_impl_selector<InputIterator, token_iterator, unichar, weight_transformer, sic, output_set_impl_choice>::type()(get_luxw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, get_output_segment_map_x_weight_set<output_set_impl_choice>());
            return get_output_segment_map_x_weight_set<output_set_impl_choice>().size();
        }
#endif
#endif //DISABLE_LUXW_GRAMMAR
#endif //DISABLE_DEPTH_FIRST_PARSER
//*********************
#ifndef DISABLE_BREADTH_FIRST_PARSER
#ifndef DISABLE_LUA_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lua_breadth_first_parser_no_output()
        {
            bool accept(typename lua_breadth_first_parser_no_output_impl_selector<InputIterator, token_iterator, sic, execution_state_set_impl_choice>::type()(get_lua_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_breadth_first_parser_with_trie_stacks_and_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            trie_string_ref_pool<unichar> tsrp;
            typename set_impl_selector<output_set_impl_choice, u_trie_string_ref>::type utsrs;
            typename lua_breadth_first_parser_impl_selector<InputIterator, token_iterator, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_lua_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, utsrs, tsrp.empty());
            return u_trie_string_ref_set_to_output_u_array_set<output_set_impl_choice>(utsrs);
        }
#endif
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_breadth_first_parser_with_array_stacks_and_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_breadth_first_parser_impl_selector<InputIterator, token_iterator, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_lua_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, get_output_u_array_set<output_set_impl_choice>());
            return get_output_u_array_set<output_set_impl_choice>().size();
        }
#endif
#endif //DISABLE_PARSERS_WITH_OUTPUT
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_breadth_first_parser_no_output()
        {
            bool accept(typename luaw_breadth_first_parser_no_output_impl_selector<InputIterator, token_iterator, weight, sic, execution_state_set_impl_choice>::type()(get_luaw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_breadth_first_parser_with_trie_stacks_and_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            trie_string_ref_pool<unichar> tsrp;
            pool_u_trie_string_x_weight empty_psxw(the_weight_transformer_traits::identity());
            typename set_impl_selector<output_set_impl_choice, pool_u_trie_string_x_weight>::type psxws;
            typename luaw_breadth_first_parser_impl_selector<InputIterator, token_iterator, weight_transformer, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_luaw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, psxws, empty_psxw);
            return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
        }
#endif
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_breadth_first_parser_with_array_stacks_and_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            typename set_impl_selector<output_set_impl_choice, fake_pool_u_array_x_weight>::type psxws;
            typename luaw_breadth_first_parser_impl_selector<InputIterator, token_iterator, weight_transformer, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_luaw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, psxws);
            return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
        }
#endif
#endif //DISABLE_PARSERS_WITH_OUTPUT
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lux_breadth_first_parser_no_output()
        {
            bool accept(typename lx_breadth_first_parser_no_output_impl_selector<InputIterator, token_iterator, unichar, sic, execution_state_set_impl_choice>::type()(get_lux_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lux_breadth_first_parser()
        {
            clear_output_segment_map_set<output_set_impl_choice>();
            typename lx_breadth_first_parser_impl_selector<InputIterator, token_iterator, unichar, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_lux_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, get_output_segment_map_set<output_set_impl_choice>());
            return get_output_segment_map_set<output_set_impl_choice>().size();
        }
#endif
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luxw_breadth_first_parser_no_output()
        {
            bool accept(typename lxw_breadth_first_parser_no_output_impl_selector<InputIterator, token_iterator, unichar, weight, sic, execution_state_set_impl_choice>::type()(get_luxw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luxw_breadth_first_parser()
        {
            clear_output_segment_map_x_weight_set<output_set_impl_choice>();
            typename lxw_breadth_first_parser_impl_selector<InputIterator, token_iterator, unichar, weight_transformer, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_luxw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, get_output_segment_map_x_weight_set<output_set_impl_choice>());
            return get_output_segment_map_x_weight_set<output_set_impl_choice>().size();
        }
#endif
#endif //DISABLE_LUXW_GRAMMAR
#endif //DISABLE_BREADTH_FIRST_PARSER
//*********************
#ifndef DISABLE_EARLEY_PARSER
#ifndef DISABLE_LUA_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lua_earley_parser_no_output()
        {
            bool accept(typename lua_earley_parser_no_output_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_earley_parser_with_trie_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            trie_string_ref_pool<unichar> tsrp;
            typename set_impl_selector<output_set_impl_choice, u_trie_string_ref>::type utsrs;
            typename lua_earley_parser_impl_selector<InputIterator, token_iterator, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_lua_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, utsrs, tsrp.empty());
            return u_trie_string_ref_set_to_output_u_array_set<output_set_impl_choice>(utsrs);
        }
#endif
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_earley_parser_with_array_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_earley_parser_impl_selector<InputIterator, token_iterator, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_lua_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, get_output_u_array_set<output_set_impl_choice>());
            return get_output_u_array_set<output_set_impl_choice>().size();
        }
#endif
#endif //DISABLE_PARSERS_WITH_OUTPUT
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_earley_parser_no_output()
        {
            bool accept(typename luaw_earley_parser_no_output_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_earley_parser_with_trie_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            trie_string_ref_pool<unichar> tsrp;
            pool_u_trie_string_x_weight empty_psxw(tsrp.empty(), the_weight_transformer_traits::identity());
            typename set_impl_selector<output_set_impl_choice, pool_u_trie_string_x_weight>::type psxws;
            typename luaw_earley_parser_impl_selector<InputIterator, token_iterator, weight_transformer, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_luaw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, psxws, empty_psxw);
            return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
        }
#endif
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_earley_parser_with_array_output()
        {
            clear_output_u_array_set<output_set_impl_choice>();
            typename set_impl_selector<output_set_impl_choice, fake_pool_u_array_x_weight>::type psxws;
            typename luaw_earley_parser_impl_selector<InputIterator, token_iterator, weight_transformer, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_luaw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, psxws);
            return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
        }
#endif
#endif //DISABLE_PARSERS_WITH_OUTPUT
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lux_earley_parser_no_output()
        {
            bool accept(typename lx_earley_parser_no_output_impl_selector<InputIterator, token_iterator, unichar, execution_state_set_impl_choice>::type()(get_lux_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lux_earley_parser()
        {
            clear_output_segment_map_set<output_set_impl_choice>();
            typename lx_earley_parser_impl_selector<InputIterator, token_iterator, unichar, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_lux_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, get_output_segment_map_set<output_set_impl_choice>());
            return get_output_segment_map_set<output_set_impl_choice>().size();
        }
#endif
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luxw_earley_parser_no_output()
        {
            bool accept(typename lxw_earley_parser_no_output_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context));
#ifdef SERIALIZED_OUTPUT
            accept ? ua.reset(ua_true): ua.reset(ua_false);
#endif
            return accept;
        }
#endif
#ifndef DISABLE_PARSERS_WITH_OUTPUT
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luxw_earley_parser()
        {
            clear_output_segment_map_x_weight_set<output_set_impl_choice>();
            typename lxw_earley_parser_impl_selector<InputIterator, token_iterator, unichar, weight_transformer, execution_state_set_impl_choice, output_set_impl_choice>::type()(get_luxw_grammar(), the_token_list.begin(), the_token_list.end(), hasnt_white_at_begin, hasnt_white_at_end, the_context, get_output_segment_map_x_weight_set<output_set_impl_choice>());
            return get_output_segment_map_x_weight_set<output_set_impl_choice>().size();
        }
#endif
#endif //DISABLE_LUXW_GRAMMAR
#endif //DISABLE_EARLEY_PARSER
//*********************
#ifndef DISABLE_TO_FPRTN_PARSER
#ifndef DISABLE_LUA_GRAMMAR
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_parser()
        {
#ifdef TRACE
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lua_to_fprtn_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            prune(out_fprtn);
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_stats(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
                        {
#ifdef TRACE
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lua_to_fprtn_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            state_count = out_fprtn.state_count();
            transition_count = out_fprtn.transition_count();
            prune(out_fprtn);
            pruned_state_count = out_fprtn.state_count();
            pruned_transition_count = out_fprtn.transition_count();
            return 0;
        }
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_parser()
        {
#ifdef TRACE
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename luaw_to_fprtn_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            prune(out_fprtn);
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_stats(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename luaw_to_fprtn_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            state_count = out_fprtn.state_count();
            transition_count = out_fprtn.transition_count();
            prune(out_fprtn);
            pruned_state_count = out_fprtn.state_count();
            pruned_transition_count = out_fprtn.transition_count();
            return 0;
        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lux_to_fprtn_parser()
        {
#ifdef TRACE
            typename lux_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lux_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lx_to_fprtn_parser_impl_selector<InputIterator, token_iterator, unichar, execution_state_set_impl_choice>::type()(get_lux_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            prune(out_fprtn);
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lux_to_fprtn_stats(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename lux_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lux_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lx_to_fprtn_parser_impl_selector<InputIterator, token_iterator, unichar, execution_state_set_impl_choice>::type()(get_lux_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            state_count = out_fprtn.state_count();
            transition_count = out_fprtn.transition_count();
            prune(out_fprtn);
            pruned_state_count = out_fprtn.state_count();
            pruned_transition_count = out_fprtn.transition_count();
            return 0;
        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_parser()
        {
#ifdef TRACE
            typename luxw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lxw_to_fprtn_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            prune(out_fprtn);
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_stats(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luxw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lxw_to_fprtn_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            state_count = out_fprtn.state_count();
            transition_count = out_fprtn.transition_count();
            prune(out_fprtn);
            pruned_state_count = out_fprtn.state_count();
            pruned_transition_count = out_fprtn.transition_count();
            return 0;
        }
#endif //DISABLE_LUXW_GRAMMAR
#endif //DISABLE_TO_FPRTN_PARSER
//*********************
#ifndef DISABLE_TO_FPRTN_ZPPS_PARSER
#ifndef DISABLE_LUA_GRAMMAR
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_zpps_parser()
        {
#ifdef TRACE
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lua_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            lua_prune_zpps<token_iterator, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps);
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_zpps_stats(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lua_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            state_count = out_fprtn_zpps.state_count();
            transition_count = out_fprtn_zpps.transition_count();
            lua_prune_zpps<token_iterator, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps);
            pruned_state_count = out_fprtn_zpps.state_count();
            pruned_transition_count = out_fprtn_zpps.transition_count();
            return 0;
        }
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_zpps_parser()
        {
#ifdef TRACE
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename luaw_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            luaw_prune_zpps<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps);
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_zpps_stats(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename luaw_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            state_count = out_fprtn_zpps.state_count();
            transition_count = out_fprtn_zpps.transition_count();
            luaw_prune_zpps<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps);
            pruned_state_count = out_fprtn_zpps.state_count();
            pruned_transition_count = out_fprtn_zpps.transition_count();
            return 0;
        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lux_to_fprtn_zpps_parser()
        {
#ifdef TRACE
            typename lux_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lux_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lx_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, unichar, execution_state_set_impl_choice>::type()(get_lux_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            lux_prune_zpps<token_iterator, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps);
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_lux_to_fprtn_zpps_stats(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename lux_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lux_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lx_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, unichar, execution_state_set_impl_choice>::type()(get_lux_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            state_count = out_fprtn_zpps.state_count();
            transition_count = out_fprtn_zpps.transition_count();
            lux_prune_zpps<token_iterator, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps);
            pruned_state_count = out_fprtn_zpps.state_count();
            pruned_transition_count = out_fprtn_zpps.transition_count();
            return 0;
        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_zpps_parser()
        {
#ifdef TRACE
            typename luxw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lxw_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            luxw_prune_zpps<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps);
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_zpps_stats(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luxw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lxw_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            state_count = out_fprtn_zpps.state_count();
            transition_count = out_fprtn_zpps.transition_count();
            luxw_prune_zpps<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps);
            pruned_state_count = out_fprtn_zpps.state_count();
            pruned_transition_count = out_fprtn_zpps.transition_count();
            return 0;
        }
#endif //DISABLE_LUXW_GRAMMAR
#endif //DISABLE_TO_FPRTN_ZPPS_PARSER
//*********************
#ifndef DISABLE_TO_FPRTN_TOP_PARSER
#ifndef DISABLE_LUAW_GRAMMAR
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_top_parser()
        {
#ifdef TRACE
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename luaw_to_fprtn_top_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_top, std::numeric_limits<weight>::min());
            luaw_prune_top<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_top, std::numeric_limits<weight>::min());
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_top_stats(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename luaw_to_fprtn_top_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_top, std::numeric_limits<weight>::min());
            state_count = out_fprtn_top.state_count();
            transition_count = out_fprtn_top.transition_count();
            luaw_prune_top<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_top, std::numeric_limits<weight>::min());
            pruned_state_count = out_fprtn_top.state_count();
            pruned_transition_count = out_fprtn_top.transition_count();
            return 0;
        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_top_parser()
        {
#ifdef TRACE
            typename luxw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lxw_to_fprtn_top_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_top, std::numeric_limits<weight>::min());
            luxw_prune_top<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_top, std::numeric_limits<weight>::min());
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_top_stats(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luxw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            typename lxw_to_fprtn_top_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_top, std::numeric_limits<weight>::min());
            state_count = out_fprtn_top.state_count();
            transition_count = out_fprtn_top.transition_count();
            luxw_prune_top<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_top, std::numeric_limits<weight>::min());
            pruned_state_count = out_fprtn_top.state_count();
            pruned_transition_count = out_fprtn_top.transition_count();
            return 0;
        }
#endif //DISABLE_LUXW_GRAMMAR
#endif //DISABLE_TO_FPRTN_TOP_PARSER
//*********************
#ifndef DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER
#ifndef DISABLE_LUA_GRAMMAR
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output()
        {
#ifdef TRACE
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_to_fprtn_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            if (prune(out_fprtn))
            {
                typename set_impl_selector<output_set_impl_choice, u_trie_string_ref>::type utsrs;
                trie_string_ref_pool<unichar> utsrp;
                typename lua_fprtn_breadth_first_expander_impl_selector<token_iterator, InputIterator, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, utsrs, utsrp.empty());
                return u_trie_string_ref_set_to_output_u_array_set<output_set_impl_choice>(utsrs);
            }
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_to_fprtn_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            state_count = out_fprtn.state_count();
            transition_count = out_fprtn.transition_count();
            bool accept(prune(out_fprtn));
            pruned_state_count = out_fprtn.state_count();
            pruned_transition_count = out_fprtn.transition_count();
            if (accept)
            {
                typename set_impl_selector<output_set_impl_choice, u_trie_string_ref>::type utsrs;
                trie_string_ref_pool<unichar> utsrp;
                typename lua_fprtn_breadth_first_expander_impl_selector<token_iterator, InputIterator, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, utsrs, utsrp.empty());
                return u_trie_string_ref_set_to_output_u_array_set<output_set_impl_choice>(utsrs);
            }
            return 0;
        }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output()
        {
#ifdef TRACE
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_to_fprtn_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            if (prune(out_fprtn))
            {
                typename lua_fprtn_breadth_first_expander_impl_selector<token_iterator, InputIterator, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, get_output_u_array_set<output_set_impl_choice>());
            }
            return get_output_u_array_set<output_set_impl_choice>().size();
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_to_fprtn_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            state_count = out_fprtn.state_count();
            transition_count = out_fprtn.transition_count();
            bool accept(prune(out_fprtn));
            pruned_state_count = out_fprtn.state_count();
            pruned_transition_count = out_fprtn.transition_count();
            if (accept)
            {
                typename lua_fprtn_breadth_first_expander_impl_selector<token_iterator, InputIterator, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, get_output_u_array_set<output_set_impl_choice>());
            }
            return get_output_u_array_set<output_set_impl_choice>().size();
        }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output()
        {
#ifdef TRACE
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename luaw_to_fprtn_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            if (prune(out_fprtn))
            {
                trie_string_ref_pool<unichar> tsrp;
                pool_u_trie_string_x_weight empty_psxw(tsrp.empty(), the_weight_transformer_traits::identity());
                typename set_impl_selector<output_set_impl_choice, pool_u_trie_string_x_weight>::type psxws;
                typename luaw_fprtn_breadth_first_expander_impl_selector<token_iterator, weight_transformer, InputIterator, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, psxws, empty_psxw);
                return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
            }
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename luaw_to_fprtn_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            state_count = out_fprtn.state_count();
            transition_count = out_fprtn.transition_count();
            bool accept(prune(out_fprtn));
            pruned_state_count = out_fprtn.state_count();
            pruned_transition_count = out_fprtn.transition_count();
            if (accept)
            {
                trie_string_ref_pool<unichar> tsrp;
                pool_u_trie_string_x_weight empty_psxw(tsrp.empty(), the_weight_transformer_traits::identity());
                typename set_impl_selector<output_set_impl_choice, pool_u_trie_string_x_weight>::type psxws;
                typename luaw_fprtn_breadth_first_expander_impl_selector<token_iterator, weight_transformer, InputIterator, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, psxws, empty_psxw);
                return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
            }
            return 0;
        }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output()
        {
#ifdef TRACE
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename luaw_to_fprtn_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            if (prune(out_fprtn))
            {
                typename set_impl_selector<output_set_impl_choice, fake_pool_u_array_x_weight>::type psxws;
                typename luaw_fprtn_breadth_first_expander_impl_selector<token_iterator, weight_transformer, InputIterator, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, psxws);
                return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
            }
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename luaw_to_fprtn_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            state_count = out_fprtn.state_count();
            transition_count = out_fprtn.transition_count();
            bool accept(prune(out_fprtn));
            pruned_state_count = out_fprtn.state_count();
            pruned_transition_count = out_fprtn.transition_count();
            if (accept)
            {
                typename set_impl_selector<output_set_impl_choice, fake_pool_u_array_x_weight>::type psxws;
                typename luaw_fprtn_breadth_first_expander_impl_selector<token_iterator, weight_transformer, InputIterator, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, psxws);
                return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
            }
            return 0;
        }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lux_to_fprtn_parser_and_breadth_first_expander()
        {
#ifdef TRACE
            typename lux_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lux_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_segment_map_set<output_set_impl_choice>();
            typename lx_to_fprtn_parser_impl_selector<InputIterator, token_iterator, unichar, execution_state_set_impl_choice>::type()(get_lux_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            if (prune(out_fprtn))
                typename lux_fprtn_breadth_first_expander_impl_selector<token_iterator, InputIterator, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, the_token_list.begin(), the_token_list.end(), get_output_segment_map_set<output_set_impl_choice>());
            return get_output_segment_map_set<output_set_impl_choice>().size();
        }
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lux_to_fprtn_stats_and_breadth_first_expander(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename lux_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lux_output_fprtn<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_segment_map_set<output_set_impl_choice>();
            typename lx_to_fprtn_parser_impl_selector<InputIterator, token_iterator, unichar, execution_state_set_impl_choice>::type()(get_lux_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            state_count = out_fprtn.state_count();
            transition_count = out_fprtn.transition_count();
            bool accept(prune(out_fprtn));
            pruned_state_count = out_fprtn.state_count();
            pruned_transition_count = out_fprtn.transition_count();
            if (accept)
                typename lux_fprtn_breadth_first_expander_impl_selector<token_iterator, InputIterator, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, the_token_list.begin(), the_token_list.end(), get_output_segment_map_set<output_set_impl_choice>());
            return get_output_segment_map_set<output_set_impl_choice>().size();
        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_parser_and_breadth_first_expander()
        {
#ifdef TRACE
            typename luxw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_segment_map_x_weight_set<output_set_impl_choice>();
            typename lxw_to_fprtn_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            if (prune(out_fprtn))
                typename luxw_fprtn_breadth_first_expander_impl_selector<token_iterator, weight_transformer, InputIterator, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, the_token_list.begin(), the_token_list.end(), get_output_segment_map_x_weight_set<output_set_impl_choice>());
            return get_output_segment_map_x_weight_set<output_set_impl_choice>().size();
        }
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_stats_and_breadth_first_expander(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luxw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_segment_map_x_weight_set<output_set_impl_choice>();
            typename lxw_to_fprtn_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn);
            state_count = out_fprtn.state_count();
            transition_count = out_fprtn.transition_count();
            bool accept(prune(out_fprtn));
            pruned_state_count = out_fprtn.state_count();
            pruned_transition_count = out_fprtn.transition_count();
            if (accept)
                typename luxw_fprtn_breadth_first_expander_impl_selector<token_iterator, weight_transformer, InputIterator, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn, the_token_list.begin(), the_token_list.end(), get_output_segment_map_x_weight_set<output_set_impl_choice>());
            return get_output_segment_map_x_weight_set<output_set_impl_choice>().size();
        }
#endif //DISABLE_LUXW_GRAMMAR
#endif //DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER
//*********************
#ifndef DISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER
#ifndef DISABLE_LUA_GRAMMAR
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_trie_output()
        {
#ifdef TRACE
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            std::size_t useful_state_count;
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            if ((useful_state_count = lua_prune_zpps<token_iterator, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps)))
            {
                trie_string_ref_pool<unichar> utsrp;
                typename set_impl_selector<output_set_impl_choice, u_trie_string_ref>::type utsrs;
                typename lua_fprtn_blackboard_set_expander_impl_selector<token_iterator, InputIterator, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, utsrs, utsrp.empty());
                return u_trie_string_ref_set_to_output_u_array_set<output_set_impl_choice>(utsrs);
            }
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_trie_output(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            state_count = out_fprtn_zpps.state_count();
            transition_count = out_fprtn_zpps.transition_count();
            std::size_t useful_state_count(lua_prune_zpps<token_iterator, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps));
            pruned_state_count = out_fprtn_zpps.state_count();
            pruned_transition_count = out_fprtn_zpps.transition_count();
            if (useful_state_count)
            {
                trie_string_ref_pool<unichar> utsrp;
                typename set_impl_selector<output_set_impl_choice, u_trie_string_ref>::type utsrs;
                typename lua_fprtn_blackboard_set_expander_impl_selector<token_iterator, InputIterator, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, utsrs, utsrp.empty());
                return u_trie_string_ref_set_to_output_u_array_set<output_set_impl_choice>(utsrs);
            }
            return 0;
        }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_array_output()
        {
#ifdef TRACE
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            std::size_t useful_state_count;
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            if ((useful_state_count = lua_prune_zpps<token_iterator, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps)))
                typename lua_fprtn_blackboard_set_expander_impl_selector<token_iterator, InputIterator, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, get_output_u_array_set<output_set_impl_choice>());
            return get_output_u_array_set<output_set_impl_choice>().size();
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_array_output(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lua_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename lua_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, execution_state_set_impl_choice>::type()(get_lua_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            state_count = out_fprtn_zpps.state_count();
            transition_count = out_fprtn_zpps.transition_count();
            std::size_t useful_state_count(lua_prune_zpps<token_iterator, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps));
            pruned_state_count = out_fprtn_zpps.state_count();
            pruned_transition_count = out_fprtn_zpps.transition_count();
            if (useful_state_count)
                typename lua_fprtn_blackboard_set_expander_impl_selector<token_iterator, InputIterator, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, get_output_u_array_set<output_set_impl_choice>());
            return get_output_u_array_set<output_set_impl_choice>().size();
        }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_trie_output()
        {
#ifdef TRACE
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            std::size_t useful_state_count;
            clear_output_u_array_set<output_set_impl_choice>();
            typename luaw_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            if ((useful_state_count = luaw_prune_zpps<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps)))
            {
                trie_string_ref_pool<unichar> tsrp;
                pool_u_trie_string_x_weight empty_psxw(tsrp.empty(), the_weight_transformer_traits::identity());
                typename set_impl_selector<output_set_impl_choice, pool_u_trie_string_x_weight>::type psxws;
                typename luaw_fprtn_blackboard_set_expander_impl_selector<token_iterator, weight_transformer, InputIterator, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, psxws, empty_psxw);
                return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
            }
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_trie_output(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename luaw_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            state_count = out_fprtn_zpps.state_count();
            transition_count = out_fprtn_zpps.transition_count();
            std::size_t useful_state_count(luaw_prune_zpps<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps));
            pruned_state_count = out_fprtn_zpps.state_count();
            pruned_transition_count = out_fprtn_zpps.transition_count();
            if (useful_state_count)
            {
                trie_string_ref_pool<unichar> tsrp;
                pool_u_trie_string_x_weight empty_psxw(tsrp.empty(), the_weight_transformer_traits::identity());
                typename set_impl_selector<output_set_impl_choice, pool_u_trie_string_x_weight>::type psxws;
                typename luaw_fprtn_blackboard_set_expander_impl_selector<token_iterator, weight_transformer, InputIterator, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, psxws, empty_psxw);
                return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
            }
            return 0;
        }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_array_output()
        {
#ifdef TRACE
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            std::size_t useful_state_count;
            clear_output_u_array_set<output_set_impl_choice>();
            typename luaw_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            if ((useful_state_count = luaw_prune_zpps<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps)))
            {
                typename set_impl_selector<output_set_impl_choice, fake_pool_u_array_x_weight>::type psxws;
                typename luaw_fprtn_blackboard_set_expander_impl_selector<token_iterator, weight_transformer, InputIterator, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, psxws);
                return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
            }
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_array_output(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<output_set_impl_choice>();
            typename luaw_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            state_count = out_fprtn_zpps.state_count();
            transition_count = out_fprtn_zpps.transition_count();
            std::size_t useful_state_count(luaw_prune_zpps<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps));
            pruned_state_count = out_fprtn_zpps.state_count();
            pruned_transition_count = out_fprtn_zpps.transition_count();
            if (useful_state_count)
            {
                typename set_impl_selector<output_set_impl_choice, fake_pool_u_array_x_weight>::type psxws;
                typename luaw_fprtn_blackboard_set_expander_impl_selector<token_iterator, weight_transformer, InputIterator, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, psxws);
                return pool_sequence_x_weight_set_to_output_u_array_set<output_set_impl_choice>(psxws);
            }
            return 0;
        }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lux_to_fprtn_parser_and_blackboard_set_expander()
        {
#ifdef TRACE
            typename lux_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lux_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            std::size_t useful_state_count;
            clear_output_segment_map_set<output_set_impl_choice>();
            typename lx_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, unichar, execution_state_set_impl_choice>::type()(get_lux_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            if ((useful_state_count = lux_prune_zpps<token_iterator, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps)))
                typename lux_fprtn_blackboard_set_expander_impl_selector<token_iterator, InputIterator, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, the_token_list.begin(), the_token_list.end(), get_output_segment_map_set<output_set_impl_choice>());
            return get_output_segment_map_set<output_set_impl_choice>().size();
        }
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_lux_to_fprtn_stats_and_blackboard_set_expander(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename lux_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename lux_output_fprtn_zpps<u_context_mask, token_iterator, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_segment_map_set<output_set_impl_choice>();
            typename lx_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, unichar, execution_state_set_impl_choice>::type()(get_lux_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            state_count = out_fprtn_zpps.state_count();
            transition_count = out_fprtn_zpps.transition_count();
            std::size_t useful_state_count(lux_prune_zpps<token_iterator, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps));
            pruned_state_count = out_fprtn_zpps.state_count();
            pruned_transition_count = out_fprtn_zpps.transition_count();
            if (useful_state_count)
                typename lux_fprtn_blackboard_set_expander_impl_selector<token_iterator, InputIterator, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, the_token_list.begin(), the_token_list.end(), get_output_segment_map_set<output_set_impl_choice>());
            return get_output_segment_map_set<output_set_impl_choice>().size();
        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander()
        {
#ifdef TRACE
            typename luxw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            std::size_t useful_state_count;
            clear_output_segment_map_x_weight_set<output_set_impl_choice>();
            typename lxw_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            if ((useful_state_count = luxw_prune_zpps<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps)))
                typename luxw_fprtn_blackboard_set_expander_impl_selector<token_iterator, weight_transformer, InputIterator, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, the_token_list.begin(), the_token_list.end(), get_output_segment_map_x_weight_set<output_set_impl_choice>());
            return get_output_segment_map_x_weight_set<output_set_impl_choice>().size();
        }
        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luxw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn_zpps<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_zpps(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_segment_map_x_weight_set<output_set_impl_choice>();
            typename lxw_to_fprtn_zpps_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_zpps);
            state_count = out_fprtn_zpps.state_count();
            transition_count = out_fprtn_zpps.transition_count();
            std::size_t useful_state_count(luxw_prune_zpps<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_zpps));
            pruned_state_count = out_fprtn_zpps.state_count();
            pruned_transition_count = out_fprtn_zpps.transition_count();
            if (useful_state_count)
                typename luxw_fprtn_blackboard_set_expander_impl_selector<token_iterator, weight_transformer, InputIterator, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(out_fprtn_zpps, useful_state_count, the_token_list.begin(), the_token_list.end(), get_output_segment_map_x_weight_set<output_set_impl_choice>());
            return get_output_segment_map_x_weight_set<output_set_impl_choice>().size();
        }
#endif //DISABLE_LUXW_GRAMMAR
#endif //DISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER
//*********************
#ifndef DISABLE_TO_FPRTN_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR
#ifndef DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_TRIE_STRING_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_parser_and_top_blackboard_extractor_with_trie_output()
        {
#ifdef TRACE
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<STD>();
            typename luaw_to_fprtn_top_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_top, std::numeric_limits<weight>::min());
            if (luaw_prune_top<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_top, std::numeric_limits<weight>::min()))
            {
                trie_string_ref_pool<unichar> tsrp;
                pool_u_trie_string_x_weight empty_psxw(tsrp.empty(), the_weight_transformer_traits::identity());
                typename set_impl_selector<STD, pool_u_trie_string_x_weight>::type psxws;
                psxws.insert(typename luaw_fprtn_top_blackboard_extractor_impl_selector<token_iterator, weight_transformer, InputIterator, TRIE_STRINGS, execution_state_set_impl_choice>::type()(out_fprtn_top, empty_psxw));
                return pool_reverse_sequence_x_weight_set_to_output_u_array_set<STD>(psxws);
            }
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_stats_and_top_blackboard_extractor_with_trie_output(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<STD>();
            typename luaw_to_fprtn_top_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_top, std::numeric_limits<weight>::min());
            state_count = out_fprtn_top.state_count();
            transition_count = out_fprtn_top.transition_count();
            bool accept(luaw_prune_top<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_top, std::numeric_limits<weight>::min()));
            pruned_state_count = out_fprtn_top.state_count();
            pruned_transition_count = out_fprtn_top.transition_count();
            if (accept)
            {
                trie_string_ref_pool<unichar> tsrp;
                pool_u_trie_string_x_weight empty_psxw(tsrp.empty(), the_weight_transformer_traits::identity());
                typename set_impl_selector<STD, pool_u_trie_string_x_weight>::type psxws;
                psxws.insert(typename luaw_fprtn_top_blackboard_extractor_impl_selector<token_iterator, weight_transformer, InputIterator, TRIE_STRINGS, execution_state_set_impl_choice>::type()(out_fprtn_top, empty_psxw));
                return pool_reverse_sequence_x_weight_set_to_output_u_array_set<STD>(psxws);
            }
            return 0;
        }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_parser_and_top_blackboard_extractor_with_array_output()
        {
#ifdef TRACE
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<STD>();
            typename luaw_to_fprtn_top_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_top, std::numeric_limits<weight>::min());
            if (luaw_prune_top<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_top, std::numeric_limits<weight>::min()))
            {
                typename set_impl_selector<STD, fake_pool_u_array_x_weight>::type psxws;
                psxws.insert(typename luaw_fprtn_top_blackboard_extractor_impl_selector<token_iterator, weight_transformer, InputIterator, ARRAYS, execution_state_set_impl_choice>::type()(out_fprtn_top));
                return pool_sequence_x_weight_set_to_output_u_array_set<STD>(psxws);
            }
            return 0;
        }
        template<assoc_container_impl_choice execution_state_set_impl_choice>
        std::size_t exe_my_luaw_to_fprtn_stats_and_top_blackboard_extractor_with_array_output(std::size_t &state_count, std::size_t &transition_count, std::size_t &pruned_state_count, std::size_t &pruned_transition_count)
        {
#ifdef TRACE
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top('r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luaw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_u_array_set<STD>();
            typename luaw_to_fprtn_top_parser_impl_selector<InputIterator, token_iterator, weight, execution_state_set_impl_choice>::type()(get_luaw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_top, std::numeric_limits<weight>::min());
            state_count = out_fprtn_top.state_count();
            transition_count = out_fprtn_top.transition_count();
            bool accept(luaw_prune_top<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_top, std::numeric_limits<weight>::min()));
            pruned_state_count = out_fprtn_top.state_count();
            pruned_transition_count = out_fprtn_top.transition_count();
            if (accept)
            {
                typename set_impl_selector<STD, fake_pool_u_array_x_weight>::type psxws;
                psxws.insert(typename luaw_fprtn_top_blackboard_extractor_impl_selector<token_iterator, weight_transformer, InputIterator, ARRAYS, execution_state_set_impl_choice>::type()(out_fprtn_top));
                return pool_sequence_x_weight_set_to_output_u_array_set<STD>(psxws);
            }
            return 0;
        }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR

        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor() {
#ifdef TRACE
            typename luxw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(
                    'r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_segment_map_x_weight_set<output_set_impl_choice>();
            typename lxw_to_fprtn_top_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(
                    get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_top,
                    std::numeric_limits<weight>::min());
            if (luxw_prune_top<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(out_fprtn_top,
                                                                                                       std::numeric_limits<weight>::min()))
                get_output_segment_map_x_weight_set<output_set_impl_choice>().insert(
                        typename luxw_fprtn_top_blackboard_extractor_impl_selector<token_iterator, weight_transformer, InputIterator, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(
                                out_fprtn_top, the_token_list.begin(), the_token_list.end()));
            return get_output_segment_map_x_weight_set<output_set_impl_choice>().size();
        }

        template<sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
        std::size_t
        exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor(std::size_t &state_count, std::size_t &transition_count,
                                                                std::size_t &pruned_state_count,
                                                                std::size_t &pruned_transition_count) {
#ifdef TRACE
            typename luxw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(
                    'r', 'q', the_token_list.size(), the_token_list.begin(), the_token_list.end());
#else
            typename luxw_output_fprtn_top<u_context_mask, token_iterator, weight, InputIterator, execution_state_set_impl_choice>::type out_fprtn_top(the_token_list.size(), the_token_list.begin(), the_token_list.end());
#endif
            clear_output_segment_map_x_weight_set<output_set_impl_choice>();
            typename lxw_to_fprtn_top_parser_impl_selector<InputIterator, token_iterator, unichar, weight, execution_state_set_impl_choice>::type()(
                    get_luxw_grammar(), hasnt_white_at_begin, hasnt_white_at_end, the_context, out_fprtn_top,
                    std::numeric_limits<weight>::min());
            state_count = out_fprtn_top.state_count();
            transition_count = out_fprtn_top.transition_count();
            bool accept(luxw_prune_top<token_iterator, weight, InputIterator, execution_state_set_impl_choice>(
                    out_fprtn_top, std::numeric_limits<weight>::min()));
            pruned_state_count = out_fprtn_top.state_count();
            pruned_transition_count = out_fprtn_top.transition_count();
            if (accept)
                get_output_segment_map_x_weight_set<output_set_impl_choice>().insert(
                        typename luxw_fprtn_top_blackboard_extractor_impl_selector<token_iterator, weight_transformer, InputIterator, sic, execution_state_set_impl_choice, output_set_impl_choice>::type()(
                                out_fprtn_top, the_token_list.begin(), the_token_list.end()));
            return get_output_segment_map_x_weight_set<output_set_impl_choice>().size();
        }

#endif //DISABLE_LUXW_GRAMMAR
#endif //DISABLE_TO_FPRTN_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR

//*********************
        void set_parser(rtno_parser_type the_parser_type, bool trie_strings, bool no_output,
                        assoc_container_impl_choice the_execution_state_set_impl_choice,
                        assoc_container_impl_choice the_output_set_impl_choice) {
            if (!no_output)
                reset_output_set(the_output_set_impl_choice);

            switch (the_parser_type) {
#ifndef DISABLE_DEPTH_FIRST_PARSER
                case DEPTH_FIRST_RTNO_PARSER:
                {
                    switch (grammar_type)
                    {
#ifndef DISABLE_LUA_GRAMMAR
                        case LEXMASK_X_LETTER_ARRAY_RTNO:
                        {
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                            {
#ifndef DISABLE_TRIE_STRING_PARSERS
                                if (trie_strings)
                                {
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_depth_first_parser_no_output<TRIE_STRINGS>;
                                    return;
                                }
#endif
#ifndef DISABLE_ARRAY_PARSERS
                                the_parse_func_ref = &ul_manager::template exe_my_lua_depth_first_parser_no_output<ARRAYS>;
                                return;
#endif
                            }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_depth_first_parser_with_trie_stacks_and_output<STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_depth_first_parser_with_trie_stacks_and_output<LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_depth_first_parser_with_trie_stacks_and_output<LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_output_set_impl_choice)
                            {
#ifndef DISABLE_STD_BS
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_lua_depth_first_parser_with_array_stacks_and_output<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_lua_depth_first_parser_with_array_stacks_and_output<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_lua_depth_first_parser_with_array_stacks_and_output<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported output set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                        {
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                            {
#ifndef DISABLE_TRIE_STRING_PARSERS
                                if (trie_strings)
                                {
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_depth_first_parser_no_output<TRIE_STRINGS>;
                                    return;
                                }
#endif
#ifndef DISABLE_ARRAY_PARSERS
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_depth_first_parser_no_output<ARRAYS>;
                                return;
#endif
                            }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_depth_first_parser_with_trie_stacks_and_output<STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_depth_first_parser_with_trie_stacks_and_output<LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_depth_first_parser_with_trie_stacks_and_output<LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_output_set_impl_choice)
                            {
#ifndef DISABLE_STD_BS
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_depth_first_parser_with_array_stacks_and_output<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_depth_first_parser_with_array_stacks_and_output<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_depth_first_parser_with_array_stacks_and_output<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported output set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
                        case LEXMASK_X_EXTRACTION_RTNO:
                        {
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                            {
#ifndef DISABLE_TRIE_STRING_PARSERS
                                if (trie_strings)
                                {
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_depth_first_parser_no_output<TRIE_STRINGS>;
                                    return;
                                }
#endif
#ifndef DISABLE_ARRAY_PARSERS
                                the_parse_func_ref = &ul_manager::template exe_my_lux_depth_first_parser_no_output<ARRAYS>;
                                return;
#endif
                            }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_depth_first_parser<TRIE_STRINGS, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_depth_first_parser<TRIE_STRINGS, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_depth_first_parser<TRIE_STRINGS, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_output_set_impl_choice)
                            {
#ifndef DISABLE_STD_BS
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_lux_depth_first_parser<ARRAYS, STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_lux_depth_first_parser<ARRAYS, LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_lux_depth_first_parser<ARRAYS, LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported output set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                        {
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                            {
#ifndef DISABLE_TRIE_STRING_PARSERS
                                if (trie_strings)
                                {
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_depth_first_parser_no_output<TRIE_STRINGS>;
                                    return;
                                }
#endif
#ifndef DISABLE_ARRAY_PARSERS
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_depth_first_parser_no_output<ARRAYS>;
                                return;
#endif
                            }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_depth_first_parser<TRIE_STRINGS, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_depth_first_parser<TRIE_STRINGS, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_depth_first_parser<TRIE_STRINGS, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_output_set_impl_choice)
                            {
#ifndef DISABLE_STD_BS
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_depth_first_parser<ARRAYS, STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_depth_first_parser<ARRAYS, LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_depth_first_parser<ARRAYS, LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported output set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUXW_GRAMMAR
                        default: fatal_error("Unsupported grammar type (compute depth-first parsing func)\n");
                    }
                }
#endif //DISABLE_DEPTH_FIRST_PARSER
//*********************
#ifndef DISABLE_BREADTH_FIRST_PARSER
                case BREADTH_FIRST_RTNO_PARSER:
                {
                    switch (grammar_type)
                    {
#ifndef DISABLE_LUA_GRAMMAR
                        case LEXMASK_X_LETTER_ARRAY_RTNO:
                        {
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                            {
#ifndef DISABLE_TRIE_STRING_PARSERS
                                if (trie_strings)
                                    switch (the_execution_state_set_impl_choice)
                                    {
#ifndef DISABLE_STD_SES
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_no_output<TRIE_STRINGS, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_no_output<TRIE_STRINGS, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_no_output<TRIE_STRINGS, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported execution state set implementation\n");
                                    }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_no_output<ARRAYS, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_no_output<ARRAYS, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_no_output<ARRAYS, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_ARRAY_PARSERS
                            }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_trie_stacks_and_output<STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_trie_stacks_and_output<STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_trie_stacks_and_output<STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_array_stacks_and_output<STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_array_stacks_and_output<STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_array_stacks_and_output<STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_array_stacks_and_output<LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_array_stacks_and_output<LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_array_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_array_stacks_and_output<LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_breadth_first_parser_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                        {
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                            {
#ifndef DISABLE_TRIE_STRING_PARSERS
                                if (trie_strings)
                                    switch (the_execution_state_set_impl_choice)
                                    {
#ifndef DISABLE_STD_SES
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_no_output<TRIE_STRINGS, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_no_output<TRIE_STRINGS, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_no_output<TRIE_STRINGS, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported execution state set implementation\n");
                                    }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_no_output<ARRAYS, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_no_output<ARRAYS, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_no_output<ARRAYS, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_ARRAY_PARSERS
                            }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_trie_stacks_and_output<STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_trie_stacks_and_output<STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_trie_stacks_and_output<STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_array_stacks_and_output<STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_array_stacks_and_output<STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_array_stacks_and_output<STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_array_stacks_and_output<LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_array_stacks_and_output<LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_array_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_array_stacks_and_output<LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_breadth_first_parser_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
                        case LEXMASK_X_EXTRACTION_RTNO:
                        {
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                            {
#ifndef DISABLE_TRIE_STRING_PARSERS
                                if (trie_strings)
                                    switch (the_execution_state_set_impl_choice)
                                    {
#ifndef DISABLE_STD_SES
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser_no_output<TRIE_STRINGS, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser_no_output<TRIE_STRINGS, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser_no_output<TRIE_STRINGS, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported execution state set implementation\n");
                                    }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser_no_output<ARRAYS, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser_no_output<ARRAYS, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser_no_output<ARRAYS, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_ARRAY_PARSERS
                            }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<TRIE_STRINGS, STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<TRIE_STRINGS, STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<TRIE_STRINGS, LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<ARRAYS, STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<ARRAYS, STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<ARRAYS, STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<ARRAYS, LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<ARRAYS, LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<ARRAYS, LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_breadth_first_parser<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                        {
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                            {
#ifndef DISABLE_TRIE_STRING_PARSERS
                                if (trie_strings)
                                    switch (the_execution_state_set_impl_choice)
                                    {
#ifndef DISABLE_STD_SES
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser_no_output<TRIE_STRINGS, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser_no_output<TRIE_STRINGS, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser_no_output<TRIE_STRINGS, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported execution state set implementation\n");
                                    }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser_no_output<ARRAYS, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser_no_output<ARRAYS, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser_no_output<ARRAYS, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_ARRAY_PARSERS
                            }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<TRIE_STRINGS, STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<TRIE_STRINGS, STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<TRIE_STRINGS, LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<ARRAYS, STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<ARRAYS, STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<ARRAYS, STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<ARRAYS, LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<ARRAYS, LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<ARRAYS, LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_breadth_first_parser<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUXW_GRAMMAR
                        default: fatal_error("Unsupported grammar type (compute breadth-first parsing func)\n");
                    }
                }
#endif //DISABLE_BREADTH_FIRST_PARSER
//*********************
#ifndef DISABLE_EARLEY_PARSER
                case EARLEY_RTNO_PARSER:
                {
                    switch (grammar_type)
                    {
#ifndef DISABLE_LUA_GRAMMAR
                        case LEXMASK_X_LETTER_ARRAY_RTNO:
                        {
                            //Trie string management not applicable here
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_no_output<STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_no_output<LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_no_output<LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_trie_output<STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_trie_output<STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_trie_output<STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_trie_output<LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_trie_output<LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_trie_output<LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_trie_output<LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_trie_output<LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_trie_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_array_output<STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_array_output<STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_array_output<STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_array_output<LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_array_output<LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_array_output<LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_array_output<LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_array_output<LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_earley_parser_with_array_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                        {
                            //Trie string management not applicable here
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_no_output<STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_no_output<LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_no_output<LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_trie_output<STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_trie_output<STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_trie_output<STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_trie_output<LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_trie_output<LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_trie_output<LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_trie_output<LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_trie_output<LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_trie_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_array_output<STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_array_output<STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_array_output<STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_array_output<LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_array_output<LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_array_output<LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_array_output<LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_array_output<LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_earley_parser_with_array_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
                        case LEXMASK_X_EXTRACTION_RTNO:
                        {
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser_no_output<STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser_no_output<LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser_no_output<LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser<STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser<STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser<STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser<LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser<LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser<LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser<LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser<LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_earley_parser<LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                        {
#ifndef DISABLE_PARSERS_WITHOUT_OUTPUT
                            if (no_output)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser_no_output<STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser_no_output<LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser_no_output<LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_PARSERS_WITHOUT_OUTPUT
#ifndef DISABLE_PARSERS_WITH_OUTPUT
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser<STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser<STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser<STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser<LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser<LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser<LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser<LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser<LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_earley_parser<LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_PARSERS_WITH_OUTPUT
                        }
#endif //DISABLE_LUXW_GRAMMAR
                        default: fatal_error("Unsupported grammar type (compute Earley parsing func)\n");
                    }
                }
#endif //DISABLE_EARLEY_PARSER
//*********************
#ifndef DISABLE_TO_FPRTN_PARSER
                case TO_FPRTN_RTNO_PARSER:
                {
                    switch (grammar_type)
                    {
#ifndef DISABLE_LUA_GRAMMAR
                        case LEXMASK_X_LETTER_ARRAY_RTNO:
                        {
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser<STD>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser<LRB_TREE>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser<LRB_TREE_3W>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
                        }
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                        {
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser<STD>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser<LRB_TREE>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser<LRB_TREE_3W>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
                        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
                        case LEXMASK_X_EXTRACTION_RTNO:
                        {
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser<STD>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser<LRB_TREE>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser<LRB_TREE_3W>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
                        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                        {
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser<STD>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser<LRB_TREE>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser<LRB_TREE_3W>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
                        }
#endif //DISABLE_LUXW_GRAMMAR
                        default: fatal_error("Unsupported grammar type (compute to-fprtn parsing func)\n");
                    }
                }
#endif //DISABLE_TO_FPRTN_PARSER
//*********************
#ifndef DISABLE_TO_FPRTN_ZPPS_PARSER
                case TO_FPRTN_ZPPS_RTNO_PARSER:
                {
                    switch (grammar_type)
                    {
#ifndef DISABLE_LUA_GRAMMAR
                        case LEXMASK_X_LETTER_ARRAY_RTNO:
                        {
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_zpps_parser<STD>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_zpps_stats<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_zpps_parser<LRB_TREE>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_zpps_stats<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_zpps_parser<LRB_TREE_3W>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_zpps_stats<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
                        }
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                        {
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_zpps_parser<STD>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_zpps_stats<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_zpps_parser<LRB_TREE>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_zpps_stats<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_zpps_parser<LRB_TREE_3W>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_zpps_stats<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
                        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
                        case LEXMASK_X_EXTRACTION_RTNO:
                        {
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_zpps_parser<STD>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_zpps_stats<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_zpps_parser<LRB_TREE>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_zpps_stats<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_zpps_parser<LRB_TREE_3W>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_zpps_stats<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
                        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                        {
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_zpps_parser<STD>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_zpps_stats<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_zpps_parser<LRB_TREE>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_zpps_stats<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_zpps_parser<LRB_TREE_3W>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_zpps_stats<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
                        }
#endif //DISABLE_LUXW_GRAMMAR
                        default: fatal_error("Unsupported grammar type (compute to-fprtn-zpps parsing func)\n");
                    }
                }
#endif //DISABLE_TO_FPRTN_ZPPS_PARSER
//*********************
#ifndef DISABLE_TO_FPRTN_TOP_PARSER
                case TO_FPRTN_TOP_RTNO_PARSER:
                {
                    switch (grammar_type)
                    {
#ifndef DISABLE_LUAW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                        {
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_top_parser<STD>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_top_stats<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_top_parser<LRB_TREE>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_top_stats<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_top_parser<LRB_TREE_3W>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_top_stats<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
                        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                        {
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_top_parser<STD>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_top_stats<STD>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_top_parser<LRB_TREE>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_top_stats<LRB_TREE>;
                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_top_parser<LRB_TREE_3W>;
                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_top_stats<LRB_TREE_3W>;
                                return;
#endif
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
                        }
#endif //DISABLE_LUXW_GRAMMAR
                        default: fatal_error("Unsupported grammar type (compute to-fprtn-top parsing func)\n");
                    }
                }
#endif //DISABLE_TO_FPRTN_TOP_PARSER
//*********************
#ifndef DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER
                case TO_FPRTN_AND_BREADTH_FIRST_EXPAND_RTNO_PARSER:
                {
                    switch (grammar_type)
                    {
#ifndef DISABLE_LUA_GRAMMAR
                        case LEXMASK_X_LETTER_ARRAY_RTNO:
                        {
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<STD, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<STD, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<STD, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<STD, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<STD, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<STD, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
                        }
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                        {
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<STD, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<STD, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<STD, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_trie_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<STD, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<STD, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<STD, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_breadth_first_expander_with_array_stacks_and_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
                        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
                        case LEXMASK_X_EXTRACTION_RTNO:
                        {
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, STD, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, STD, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<ARRAYS, STD, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<ARRAYS, STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<ARRAYS, STD, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<ARRAYS, STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<ARRAYS, STD, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<ARRAYS, STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
                        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                        {
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, STD, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, STD, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<ARRAYS, STD, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<ARRAYS, STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<ARRAYS, STD, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<ARRAYS, STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<ARRAYS, STD, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<ARRAYS, STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_breadth_first_expander<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
                        }
#endif //DISABLE_LUXW_GRAMMAR
                        default: fatal_error("Unsupported grammar type (compute to fprtn parser and breadth-first expand func)\n");
                    }
                }
#endif //DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER
//*********************
#ifndef DISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER
                case TO_FPRTN_AND_BLACKBOARD_SET_EXPAND_RTNO_PARSER:
                {
                    switch (grammar_type)
                    {
#ifndef DISABLE_LUA_GRAMMAR
                        case LEXMASK_X_LETTER_ARRAY_RTNO:
                        {
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<STD, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<STD, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<STD, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_array_output<STD, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_array_output<STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_array_output<STD, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_array_output<STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_array_output<STD, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_array_output<STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lua_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lua_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
                        }
#endif //DISABLE_LUA_GRAMMAR
#ifndef DISABLE_LUAW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                        {
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<STD, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<STD, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<STD, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_trie_output<LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_array_output<STD, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_array_output<STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_array_output<STD, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_array_output<STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_array_output<STD, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_array_output<STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_blackboard_set_expander_with_array_output<LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
                        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUX_GRAMMAR
                        case LEXMASK_X_EXTRACTION_RTNO:
                        {
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, STD, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, STD, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, STD, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, STD, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, STD, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_lux_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_lux_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
                        }
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                        {
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, STD, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, STD, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                            case STD:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, STD, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, STD, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, STD, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, STD, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, STD, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, STD, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                            case LRB_TREE:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                            case LRB_TREE_3W:
                                switch (the_output_set_impl_choice)
                                {
#ifndef DISABLE_STD_BS
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_blackboard_set_expander<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                    return;
#endif
                                default: fatal_error("Unsupported output set implementation\n");
                                }
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
                        }
#endif //DISABLE_LUXW_GRAMMAR
                        default: fatal_error("Unsupported grammar type (compute to fprtn parser and blackboard set expand func)\n");
                    }
                }
#endif //DISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER
//*********************
#ifndef DISABLE_TO_FPRTN_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR
                case TO_FPRTN_AND_TOP_BLACKBOARD_EXTRACT_RTNO_PARSER: {
                    switch (grammar_type) {
#ifndef DISABLE_LUAW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO:
                        {
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice)
                                {
#ifndef DISABLE_STD_SES
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_top_blackboard_extractor_with_trie_output<STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_top_blackboard_extractor_with_trie_output<STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_top_blackboard_extractor_with_trie_output<LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_top_blackboard_extractor_with_trie_output<LRB_TREE>;
                                    return;
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_top_blackboard_extractor_with_trie_output<LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_top_blackboard_extractor_with_trie_output<LRB_TREE_3W>;
                                    return;
#endif //DISABLE_LRB_TREE_3W_SES
                                default: fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice)
                            {
#ifndef DISABLE_STD_SES
                                case STD:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_top_blackboard_extractor_with_array_output<STD>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_top_blackboard_extractor_with_array_output<STD>;
                                    return;
#endif
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_top_blackboard_extractor_with_array_output<LRB_TREE>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_top_blackboard_extractor_with_array_output<LRB_TREE>;
                                    return;
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    the_parse_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_parser_and_top_blackboard_extractor_with_array_output<LRB_TREE_3W>;
                                    the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luaw_to_fprtn_stats_and_top_blackboard_extractor_with_array_output<LRB_TREE_3W>;
                                    return;
#endif //DISABLE_LRB_TREE_3W_SES
                            default: fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
                        }
#endif //DISABLE_LUAW_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
                        case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO: {
#ifndef DISABLE_TRIE_STRING_PARSERS
                            if (trie_strings)
                                switch (the_execution_state_set_impl_choice) {
#ifndef DISABLE_STD_SES
                                    case STD:
                                        switch (the_output_set_impl_choice)
                                        {
#ifndef DISABLE_STD_BS
                                        case STD:
                                            the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<TRIE_STRINGS, STD, STD>;
                                            the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<TRIE_STRINGS, STD, STD>;
                                            return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                        case LRB_TREE:
                                            the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<TRIE_STRINGS, STD, LRB_TREE>;
                                            the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<TRIE_STRINGS, STD, LRB_TREE>;
                                            return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                        case LRB_TREE_3W:
                                            the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                            the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<TRIE_STRINGS, STD, LRB_TREE_3W>;
                                            return;
#endif
                                        default: fatal_error("Unsupported output set implementation\n");
                                        }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                    case LRB_TREE:
                                        switch (the_output_set_impl_choice) {
#ifndef DISABLE_STD_BS
                                            case STD:
                                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE, STD>;
                                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE, STD>;
                                                return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                            case LRB_TREE:
                                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE, LRB_TREE>;
                                                return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                            case LRB_TREE_3W:
                                                the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                                the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE, LRB_TREE_3W>;
                                                return;
#endif
                                            default:
                                                fatal_error("Unsupported output set implementation\n");
                                        }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                    case LRB_TREE_3W:
                                        switch (the_output_set_impl_choice)
                                        {
#ifndef DISABLE_STD_BS
                                        case STD:
                                            the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                            the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE_3W, STD>;
                                            return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                        case LRB_TREE:
                                            the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                            the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE>;
                                            return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                        case LRB_TREE_3W:
                                            the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                            the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<TRIE_STRINGS, LRB_TREE_3W, LRB_TREE_3W>;
                                            return;
#endif
                                        default: fatal_error("Unsupported output set implementation\n");
                                        }
#endif //DISABLE_LRB_TREE_3W_SES
                                    default:
                                        fatal_error("Unsupported execution state set implementation\n");
                                }
#endif //DISABLE_TRIE_STRING_PARSERS
#ifndef DISABLE_ARRAY_PARSERS
                            switch (the_execution_state_set_impl_choice) {
#ifndef DISABLE_STD_SES
                                case STD:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<ARRAYS, STD, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<ARRAYS, STD, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<ARRAYS, STD, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<ARRAYS, STD, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<ARRAYS, STD, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<ARRAYS, STD, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_STD_SES
#ifndef DISABLE_LRB_TREE_SES
                                case LRB_TREE:
                                    switch (the_output_set_impl_choice) {
#ifndef DISABLE_STD_BS
                                        case STD:
                                            the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<ARRAYS, LRB_TREE, STD>;
                                            the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<ARRAYS, LRB_TREE, STD>;
                                            return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                        case LRB_TREE:
                                            the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<ARRAYS, LRB_TREE, LRB_TREE>;
                                            the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<ARRAYS, LRB_TREE, LRB_TREE>;
                                            return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                        case LRB_TREE_3W:
                                            the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                            the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<ARRAYS, LRB_TREE, LRB_TREE_3W>;
                                            return;
#endif
                                        default:
                                            fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_SES
#ifndef DISABLE_LRB_TREE_3W_SES
                                case LRB_TREE_3W:
                                    switch (the_output_set_impl_choice)
                                    {
#ifndef DISABLE_STD_BS
                                    case STD:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<ARRAYS, LRB_TREE_3W, STD>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<ARRAYS, LRB_TREE_3W, STD>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_BS
                                    case LRB_TREE:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<ARRAYS, LRB_TREE_3W, LRB_TREE>;
                                        return;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                                    case LRB_TREE_3W:
                                        the_parse_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_parser_and_top_blackboard_extractor<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                        the_parse_and_get_fprtn_stats_func_ref = &ul_manager::template exe_my_luxw_to_fprtn_stats_and_top_blackboard_extractor<ARRAYS, LRB_TREE_3W, LRB_TREE_3W>;
                                        return;
#endif
                                    default: fatal_error("Unsupported output set implementation\n");
                                    }
#endif //DISABLE_LRB_TREE_3W_SES
                                default:
                                    fatal_error("Unsupported execution state set implementation\n");
                            }
#endif //DISABLE_ARRAY_PARSERS
                        }
#endif //DISABLE_LUXW_GRAMMAR
                        default:
                            fatal_error(
                                    "Unsupported grammar type (compute to fprtn parser and breadth-first expand func)\n");
                    }
                }
#endif //DISABLE_TO_FPRTN_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR
                default:
                    fatal_error("Unsupported parser\n");
            }
        }

        std::size_t parse_and_get_fprtn_stats(std::size_t &state_count, std::size_t &transition_count,
                                              std::size_t &pruned_state_count, std::size_t &pruned_transition_count) {
#ifdef TRACE
            std::wcout << L"Parsing\n";
#endif
            return (*this.*the_parse_and_get_fprtn_stats_func_ref)(state_count, transition_count, pruned_state_count,
                                                                   pruned_transition_count);
        }

        std::size_t parse() {
#ifdef TRACE
            std::wcout << L"Parsing\n";
#endif
            return (*this.*the_parse_func_ref)();
        }

#if defined(SIMPLIFIED_OUTPUT) && !(defined(DISABLE_LUX_GRAMMAR) && defined(DISABLE_LUXW_GRAMMAR))

        void simplify(InputIterator input_begin, InputIterator input_end) {
            switch (the_output_set_impl_choice) {
#ifndef DISABLE_STD_BS
                case STD:
                    reset_simple_segment_array_x_weight_array<InputIterator, unichar, weight, STD>(
                            simplified_weighted_output, input_begin, input_end, the_token_list.begin(),
                            the_token_list.end(), get_output_segment_map_x_weight_set<STD>());
                    break;
#endif
#ifndef DISABLE_LRB_TREE_BS
                    case LRB_TREE: reset_simple_segment_array_x_weight_array<InputIterator, unichar, weight, LRB_TREE>(simplified_weighted_output, input_begin, input_end, the_token_list.begin(), the_token_list.end(), get_output_segment_map_x_weight_set<LRB_TREE>()); break;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                    case LRB_TREE_3W: reset_simple_segment_array_x_weight_array<InputIterator, unichar, weight, LRB_TREE_3W>(simplified_weighted_output, input_begin, input_end, the_token_list.begin(), the_token_list.end(), get_output_segment_map_x_weight_set<LRB_TREE_3W>()); break;
#endif
                default:
                    fatal_error("Unsupported output set implementation\n");
            }
#endif //SIMPLIFIED_OUTPUT
        }

#if defined(SERIALIZED_OUTPUT) && !(defined(DISABLE_LUX_GRAMMAR) && defined(DISABLE_LUXW_GRAMMAR))
        template<typename ToCanonicalFormMarkIterator>
        void serialize(InputIterator input_begin, InputIterator input_end, ToCanonicalFormMarkIterator to_canonical_form_mark_begin, ToCanonicalFormMarkIterator to_canonical_form_mark_end)
        {
            bool sentence_was_recognized(false);
            switch (grammar_type)
            {
#ifndef DISABLE_LUX_GRAMMAR
            case LEXMASK_X_EXTRACTION_RTNO:
                switch (the_output_set_impl_choice)
                {
#ifndef DISABLE_STD_BS
                case STD: sentence_was_recognized = movistarbot_out_serializer<InputIterator, STD>()(get_output_segment_map_set<STD>(), *td_ref, ua); break;
#endif
#ifndef DISABLE_LRB_TREE_BS
                case LRB_TREE: sentence_was_recognized = movistarbot_out_serializer<InputIterator, LRB_TREE>()(get_output_segment_map_set<LRB_TREE>(), *td_ref, ua); break;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                case LRB_TREE_3W: sentence_was_recognized = movistarbot_out_serializer<InputIterator, LRB_TREE_3W>()(get_output_segment_map_set<LRB_TREE_3W>(), *td_ref, ua); break;
#endif
                default: fatal_error("Unsupported output set implementation\n");
                }
                break;
#endif //DISABLE_LUX_GRAMMAR
#ifndef DISABLE_LUXW_GRAMMAR
            case LEXMASK_X_WEIGHTED_EXTRACTION_RTNO:
                switch (the_output_set_impl_choice)
                {
#ifndef DISABLE_STD_BS
                case STD: sentence_was_recognized = movistarbot_weighted_out_serializer<InputIterator, weight, STD>()(get_output_segment_map_x_weight_set<STD>(), *td_ref, ua); break;
#endif
#ifndef DISABLE_LRB_TREE_BS
                case LRB_TREE: sentence_was_recognized = movistarbot_weighted_out_serializer<InputIterator, weight, LRB_TREE>()(get_output_segment_map_x_weight_set<LRB_TREE>(), *td_ref, ua); break;
#endif
#ifndef DISABLE_LRB_TREE_3W_BS
                case LRB_TREE_3W: sentence_was_recognized = movistarbot_weighted_out_serializer<InputIterator, weight, LRB_TREE_3W>()(get_output_segment_map_x_weight_set<LRB_TREE_3W>(), *td_ref, ua); break;
#endif
                default: fatal_error("Unsupported output set implementation\n");
                }
                break;
#endif //DISABLE_LUXW_GRAMMAR
            default: fatal_error("Unsupported grammar type (out serializer)\n");
            }

            if (!sentence_was_recognized)
#ifdef DISABLE_TEXT_DICO
                to_decompressed_canonical_form<unichar, InputIterator, typename token<InputIterator>::ref_list::const_iterator, u_tolower, ToCanonicalFormMarkIterator>(input_begin, input_end, the_token_list.begin(), the_token_list.end(), get_compressed_delaf(), get_compressed_v_pos_filter(), to_canonical_form_mark_begin, to_canonical_form_mark_end, ua);
#elif defined(DISABLE_COMPRESSED_DICO)
                to_canonical_form(input_begin, input_end, the_token_list.begin(), the_token_list.end(), get_text_delaf(), get_text_v_pos_filter(), to_canonical_form_mark_begin, to_canonical_form_mark_end, ua);
#else
                dico_is_in_text_format ?
                        to_canonical_form(input_begin, input_end, the_token_list.begin(), the_token_list.end(), get_text_delaf(), get_text_v_pos_filter(), to_canonical_form_mark_begin, to_canonical_form_mark_end, ua) :
                        to_decompressed_canonical_form<unichar, InputIterator, typename token<InputIterator>::ref_list::const_iterator, u_tolower, ToCanonicalFormMarkIterator>(input_begin, input_end, the_token_list.begin(), the_token_list.end(), get_compressed_delaf(), get_compressed_v_pos_filter(), to_canonical_form_mark_begin, to_canonical_form_mark_end, ua);
#endif
        }

        void serialize(InputIterator input_begin, InputIterator input_end)
        { serialize(input_begin, input_end, to_canonical_form_mark.begin(), to_canonical_form_mark.end()); }
#endif //defined(SERIALIZED_OUTPUT) && !(defined(DISABLE_LUX_GRAMMAR) && defined(DISABLE_LUXW_GRAMMAR))

        template<typename ToCanonicalFormMarkIterator>
        void process(InputIterator input_begin, InputIterator input_end,
                     ToCanonicalFormMarkIterator to_canonical_form_mark_begin,
                     ToCanonicalFormMarkIterator to_canonical_form_mark_end, rtno_parser_type the_rtno_parser_type,
                     bool trie_strings, bool no_output, assoc_container_impl_choice the_execution_state_set_impl_choice,
                     assoc_container_impl_choice the_output_set_impl_choice) {
            tokenize(input_begin, input_end);
            set_parser(the_rtno_parser_type, trie_strings, no_output, the_execution_state_set_impl_choice,
                       the_output_set_impl_choice);
            parse();
#if !(defined(DISABLE_LUX_GRAMMAR) && defined(DISABLE_LUXW_GRAMMAR))
#ifdef SIMPLIFIED_OUTPUT
            if ((grammar_type == LEXMASK_X_WEIGHTED_EXTRACTION_RTNO) && the_rtno_parser_type != TO_FPRTN_RTNO_PARSER)
                simplify(input_begin, input_end);
#endif
#ifdef SERIALIZED_OUTPUT
            if ((grammar_type == LEXMASK_X_EXTRACTION_RTNO || grammar_type == LEXMASK_X_WEIGHTED_EXTRACTION_RTNO) && the_rtno_parser_type != TO_FPRTN_RTNO_PARSER)
                serialize(input_begin, input_end, to_canonical_form_mark_begin, to_canonical_form_mark_end);
#endif
#endif //!(defined(DISABLE_LUX_GRAMMAR) && defined(DISABLE_LUXW_GRAMMAR))
        }

        void process(InputIterator input_begin, InputIterator input_end, rtno_parser_type the_rtno_parser_type,
                     bool trie_strings, bool no_output, assoc_container_impl_choice the_execution_state_set_impl_choice,
                     assoc_container_impl_choice the_output_set_impl_choice) {
            process(input_begin, input_end, to_canonical_form_mark.begin(), to_canonical_form_mark.end(),
                    the_rtno_parser_type, trie_strings, no_output, the_execution_state_set_impl_choice,
                    the_output_set_impl_choice);
        }
    };
} //namespace grapenlp

#endif /*GRAPENLP_UL_MANAGER_H*/
