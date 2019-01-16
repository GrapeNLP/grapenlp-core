/*
 * GRAPENLP
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

#ifndef GRAPENLP_BAD_ALIGNED_CORPUS_FORMAT_H
#define GRAPENLP_BAD_ALIGNED_CORPUS_FORMAT_H

#include <grapenlp/bad_file_format_exception.h>

namespace grapenlp
{
	struct bad_aligned_corpus_file_format_exception: public bad_file_format_exception
	{
		bad_aligned_corpus_file_format_exception(const std::string &reason):bad_file_format_exception(reason)
		{}
	};
} //namespace grapenlp

#endif /*GRAPENLP_BAD_ALIGNED_CORPUS_FORMAT_H*/
