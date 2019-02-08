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

#ifndef GRAPENLP_RTNO_TYPE_H
#define GRAPENLP_RTNO_TYPE_H

namespace grapenlp
{
    enum rtno_type
    {
        LEXMASK_X_LETTER_ARRAY_RTNO,
        LEXMASK_X_WEIGHTED_LETTER_ARRAY_RTNO,
        LEXMASK_X_EXTRACTION_RTNO,
        LEXMASK_X_WEIGHTED_EXTRACTION_RTNO,
        LEXMASK_X_BRACKETING_RTNO,
        LEXMASK_X_WEIGHTED_BRACKETING_RTNO
    };
} //namespace grapenlp

#endif //GRAPENLP_RTNO_TYPE_H
