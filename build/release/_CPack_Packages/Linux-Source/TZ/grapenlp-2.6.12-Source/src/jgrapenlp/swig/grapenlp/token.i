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

/* token.i */
%module token
%include u_array.i
%include vector.i
%{
#include <grapenlp/token.h>

namespace grapenlp
{
    typedef token<u_array::const_iterator> ua_token;
    typedef std::vector<ua_token *> base_ua_token_ptr_vector;
    typedef ptr_vector<ua_token> ua_token_ptr_vector;
    typedef ua_token_ptr_vector::const_iterator ua_token_iterator;
}
%}

namespace grapenlp
{
    enum token_type
    {
        WORD_TOKEN,
        UPPER_WORD_TOKEN,
        LOWER_WORD_TOKEN,
        FIRST_UPPER_WORD_TOKEN,
        WHITE_TOKEN,
        DIGIT_TOKEN,
        SYMBOL_TOKEN
    };

    %nodefaultctor token;
    %nodefaultdtor token;
	template<typename InputIterator>
	struct token
	{
    public:
		typedef token* ref;
		typedef const token* const_ref;
		typedef ptr_vector<token> ref_list;

		InputIterator begin, end;
		token(InputIterator begin_, InputIterator end_, token_type type_) : begin(begin_), end(end_), my_type(type_);
        ~token();
	};

    typedef ::grapenlp::token<::grapenlp::u_array::const_iterator> ua_token;
    %template(ua_token) ::grapenlp::token<::grapenlp::array<unichar>::const_iterator>;

    typedef ::std::vector<::grapenlp::ua_token *> base_ua_token_ptr_vector;
    %template(base_ua_token_ptr_vector) ::std::vector<::grapenlp::token<::grapenlp::array<unichar>::const_iterator> *>;

    typedef ::grapenlp::ptr_vector<::grapenlp::ua_token> ua_token_ptr_vector;
    %template(ua_token_ptr_vector) ::grapenlp::ptr_vector<::grapenlp::token<::grapenlp::array<unichar>::const_iterator> >;

    typedef ::grapenlp::ua_token_ptr_vector::const_iterator ua_token_iterator;
}
/*
%{
namespace swig {
    template <> struct traits<grapenlp::ptr_vector<grapenlp::token<const short unsigned int*> > >
    {
        typedef pointer_category category;
        static const char* type_name()
        {
            return "grapenlp::ptr_vector<grapenlp::token<const short unsigned int*> >";
        }
    };
}
%}*/
