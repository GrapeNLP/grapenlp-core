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

/* ul_manager.i */
%module ul_manager
%include std_string.i
%include assoc_container_impl_choice.i
%include rtno_type.i
%include parser.i
%include u_context_key_value_hasher.i
%include u_context.i
%include simple_segment_array_x_weight.i
%{
#include <string>
/*#include <grapenlp/ualxiw_manager.h>*/
#include <grapenlp/ul_manager.h>
namespace grapenlp
{
    typedef u_array::const_iterator ua_input_iterator;
    typedef ul_manager<ua_input_iterator, std::plus<int> > ualxiw_manager;
}
%}

namespace grapenlp
{
    typedef ::grapenlp::u_array::const_iterator ua_input_iterator;

	template<typename InputIterator, typename WeightTransformer>
	class ul_manager
    {
    public:
		typedef WeightTransformer weight_transformer;
		typedef weight_transformer_traits<WeightTransformer> the_weight_transformer_traits;
		typedef typename weight_transformer::result_type weight;
		typedef typename token<InputIterator>::ref_list::const_iterator token_iterator;

        ul_manager(rtno_type grammar_type_, const std::string &grammar_path_name, const std::string &dico_path_name);
        ~ul_manager();

        const u_context_key_value_hasher& get_context_key_value_hasher();
        const ::grapenlp::uaui_simple_segment_array_x_weight_array& get_simplified_weighted_output();
/*        const ::grapenlp::simple_segment_array_x_weight_array<InputIterator, unichar, weight>& get_simplified_weighted_output();*/

/*        const u_array& get_output_u_array();*/
        void process(ua_input_iterator input_begin, ua_input_iterator input_end, rtno_parser_type the_rtno_parser_type, bool trie_strings, bool no_output, assoc_container_impl_choice the_execution_state_set_impl_choice, assoc_container_impl_choice the_output_set_impl_choice);
        void process(ua_input_iterator input_begin, ua_input_iterator input_end, const u_context &ctx, rtno_parser_type the_rtno_parser_type, bool trie_strings, bool no_output, assoc_container_impl_choice the_execution_state_set_impl_choice, assoc_container_impl_choice the_output_set_impl_choice);
    };

    typedef ul_manager<ua_input_iterator, std::plus<int> > ualxiw_manager;
    %template(ualxiw_manager) ul_manager<ua_input_iterator, std::plus<int> >;
}
