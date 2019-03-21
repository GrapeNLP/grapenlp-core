/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2008 Université de Marne-la-Vallée <javier.sastre@univ-mlv.fr>
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

#ifndef GRAPENLP_DISABLE_DIRECTIVES

/****************************************************************************/
/* Comment/uncomment the following lines for enabling/disabling             */
/* dictionary formats, grammar types, parsing algorithms and their variants */
/* in order to accelerate the compilation of the desired features and       */
/* omit error messages from the undesired ones                              */
/****************************************************************************/

//Disable specific dictionary formats
//#define DISABLE_TEXT_DICO
//#define DISABLE_COMPRESSED_DICO

//Disable specific grammar types
#define DISABLE_LUA_GRAMMAR
#define DISABLE_LUAW_GRAMMAR
#define DISABLE_LUT_GRAMMAR
#define DISABLE_LUTW_GRAMMAR
#define DISABLE_LUX_GRAMMAR
//#define DISABLE_LUXW_GRAMMAR

//Disable grammar types by kind of output
//#define DISABLE_LETTER_OUTPUT_GRAMMARS
//#define DISABLE_TAGGING_GRAMMARS
//#define DISABLE_EXTRACTION_GRAMMARS
//#define DISABLE_UNWEIGHTED_GRAMMARS
//#define DISABLE_WEIGHTED_GRAMMARS

//Disable parsers by parsing algorithm
#define DISABLE_DEPTH_FIRST_PARSER
#define DISABLE_BREADTH_FIRST_PARSER
#define DISABLE_EARLEY_PARSER
#define DISABLE_TO_FPRTN_PARSER
#define DISABLE_TO_FPRTN_TOP_PARSER
#define DISABLE_TO_FPRTN_ZPPS_PARSER
#define DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER
#define DISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER
//#define DISABLE_TO_FPRTN_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR

//#define DISABLE_TO_FPRTN_PLAIN_PARSERS
//#define DISABLE_TO_FPRTN_ZPPS_PARSERS
//#define DISABLE_TO_FPRTN_TOP_PARSERS
//#define DISABLE_TO_FPRTN_PARSERS

//Disable parsers by output
//#define DISABLE_PARSERS_WITH_OUTPUT
#define DISABLE_PARSERS_WITHOUT_OUTPUT

//Disable parsers by sequence implementation
//#define DISABLE_TRIE_STRING_PARSERS
//#define DISABLE_ARRAY_PARSERS

//Disable specific execution state set/map implementations
#define DISABLE_STD_SES
//#define DISABLE_LRB_TREE_SES
#define DISABLE_LRB_TREE_3W_SES

//Disable specific output set implementations
//#define DISABLE_STD_BS
#define DISABLE_LRB_TREE_BS
#define DISABLE_LRB_TREE_3W_BS

/***********************************************************************/
/* Do not edit the following lines!!                                   */
/* These lines resolve the dependencies between the different disables */
/* and compute the default options amongst the ones left enabled       */
/***********************************************************************/

#if defined(DISABLE_TEXT_DICO) && defined(DISABLE_COMPRESSED_DICO)
#error Every dictionary format has been disabled
#endif

#ifdef DISABLE_LETTER_GRAMMARS
#define DISABLE_LUA_GRAMMAR
#define DISABLE_LUAW_GRAMMAR
#elif defined(DISABLE_LUA_GRAMMAR) && defined(DISABLE_LUAW_GRAMMAR)
#define DISABLE_LETTER_GRAMMARS
#endif

#ifdef DISABLE_TAGGING_GRAMMARS
#define DISABLE_LUT_GRAMMAR
#define DISABLE_LUTW_GRAMMAR
#elif defined(DISABLE_LUT_GRAMMAR) && defined(DISABLE_LUTW_GRAMMAR)
#define DISABLE_TAGGING_GRAMMARS
#endif

#ifdef DISABLE_EXTRACTION_GRAMMARS
#define DISABLE_LUX_GRAMMAR
#define DISABLE_LUXW_GRAMMAR
#elif defined(DISABLE_LUX_GRAMMAR) && defined(DISABLE_LUXW_GRAMMAR)
#define DISABLE_EXTRACTION_GRAMMARS
#endif

#ifdef DISABLE_UNWEIGHTED_GRAMMARS
#define DISABLE_LUA_GRAMMAR
#define DISABLE_LUX_GRAMMAR
#elif defined(DISABLE_LUA_GRAMMAR) && defined(DISABLE_LUX_GRAMMAR)
#define DISABLE_UNWEIGHTED_GRAMMARS
#endif

#ifdef DISABLE_WEIGHTED_GRAMMARS
#define DISABLE_LUAW_GRAMMAR
#define DISABLE_LUXW_GRAMMAR
#elif defined(DISABLE_LUAW_GRAMMAR) && defined(DISABLE_LUXW_GRAMMAR)
#define DISABLE_WEIGHTED_GRAMMARS
#endif

#if defined(DISABLE_UNWEIGHTED_GRAMMARS) && defined(DISABLE_WEIGHTED_GRAMMARS)
#error Every grammar type has been disabled
#endif

#ifdef DISABLE_PARSERS_WITH_OUTPUT
#define DISABLE_TO_FPRTN_PARSERS
#endif

#ifdef DISABLE_TO_FPRTN_PARSERS
#define DISABLE_TO_FPRTN_PLAIN_PARSERS
#define DISABLE_TO_FPRTN_ZPPS_PARSERS
#define DISABLE_TO_FPRTN_TOP_PARSERS
#endif

#ifdef DISABLE_TO_FPRTN_PLAIN_PARSERS
#define DISABLE_TO_FPRTN_PARSER
#define DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER
#elif defined(DISABLE_TO_FPRTN_PARSER) && defined(DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER)
#define DISABLE_TO_FPRTN_PLAIN_PARSERS
#endif

#ifdef DISABLE_TO_FPRTN_ZPPS_PARSERS
#define DISABLE_TO_FPRTN_ZPPS_PARSER
#define DISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER
#elif defined(DISABLE_TO_FPRTN_ZPPS_PARSER) && defined(DISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER)
#define DISABLE_TO_FPRTN_ZPPS_PARSERS
#endif

#ifdef DISABLE_TO_FPRTN_TOP_PARSERS
#define DISABLE_TO_FPRTN_TOP_PARSER
#define DISABLE_TO_FPRTN_ZPPS_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR
#elif defined(DISABLE_TO_FPRTN_TOP_PARSER) && defined(DISABLE_TO_FPRTN_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR)
#define DISABLE_TO_FPRTN_TOP_PARSERS
#endif

#if !defined(DISABLE_TO_FPRTN_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR)
#define DEFAULT_PARSER TO_FPRTN_AND_TOP_BLACKBOARD_EXTRACT_RTNO_PARSER
#elif !defined(DISABLE_TO_FPRTN_PARSER_AND_BLACKBOAR_SET_EXPANDER)
#define DEFAULT_PARSER TO_FPRTN_AND_BLACKBOARD_SET_EXPAND_RTNO_PARSER
#elif !defined(DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER)
#define DEFAULT_PARSER TO_FPRTN_AND_BREADTH_FIRST_EXPAND_RTNO_PARSER
#elif !defined(DISABLE_EARLEY_PARSER)
#define DEFAULT_PARSER EARLEY_RTNO_PARSER
#elif !defined(DISABLE_DEPTH_FIRST_PARSER)
#define DEFAULT_PARSER DEPTH_FIRST_RTNO_PARSER
#elif !defined(DISABLE_BREADTH_FIRST_PARSER)
#define DEFAULT_PARSER BREADTH_FIRST_RTNO_PARSER
#elif !defined(DISABLE_TO_FPRTN_TOP_PARSER)
#define DEFAULT_PARSER TO_FPRTN_TOP_RTNO_PARSER
#elif !defined(DISABLE_TO_FPRTN_ZPPS_PARSER)
#define DEFAULT_PARSER TO_FPRTN_ZPPS_RTNO_PARSER
#elif !defined(DISABLE_TO_FPRTN_PARSER)
#define DEFAULT_PARSER TO_FPRTN_RTNO_PARSER
#else
#error Every parser has been disabled
#endif

#if defined(DISABLE_PARSERS_WITHOUT_OUTPUT) && defined(DISABLE_PARSERS_WITH_OUTPUT)
#error Both parsers with and without output have been disabled
#endif

#if defined(DISABLE_ARRAY_PARSERS) && defined(DISABLE_TRIE_STRING_PARSERS)
#error Both parsers with and without trie string optimization have been disabled
#endif

#ifndef DISABLE_LRB_TREE_SES
#define DEFAULT_SES_IMPL LRB_TREE
#elif !defined(DISABLE_LRB_TREE_3W_SES)
#define DEFAULT_SES_IMPL LRB_TREE_3W
#elif !defined(DISABLE_STD_SES)
#define DEFAULT_SES_IMPL STD
#else
#error Every execution state set implementation has been disabled
#endif

#ifndef DISABLE_STD_BS
#define DEFAULT_BS_IMPL STD
#elif !defined(DISABLE_LRB_TREE_BS)
#define DEFAULT_BS_IMPL LRB_TREE
#elif !defined(DISABLE_LRB_TREE_3W_BS)
#define DEFAULT_BS_IMPL LRB_TREE_3W
else
#error Every output set implementation has been disabled
#endif

#if defined(DISABLE_PARSERS_WITH_OUTPUT) || (defined(DISABLE_DEPTH_FIRST_PARSER) && defined(DISABLE_BREADTH_FIRST_PARSER) && defined(DISABLE_EARLEY_PARSER) && defined(DISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER) && defined(DISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER) && defined(DISABLE_TO_FPRTN_PARSER_AND_TOP_BLACKBOARD_EXTRACTOR))
#define DISABLE_PARSERS_WITH_FINAL_OUTPUT
#endif

#endif //GRAPENLP_DISABLE_DIRECTIVES
