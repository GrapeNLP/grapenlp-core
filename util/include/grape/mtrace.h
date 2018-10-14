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

#ifndef GRAPE_MTRACE_H
#define GRAPE_MTRACE_H

#ifdef MTRACE
//Memory tracing library; only needed for verifying that there are no memory leaks
//This library is not to be loaded for the release version
//Just set it as the first include of the cpp file containing the main function
//Define or not MTRACE in order to generate or not memory tracing code
#include <mcheck.h>
struct mtracer
{
	mtracer()
	{
		mtrace();
	}
	~mtracer()
	{
		muntrace();
	}
} the_memory_tracer;
#endif

#endif /*GRAPE_MTRACE_H*/
