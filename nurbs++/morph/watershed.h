/*=============================================================================
        File: kernel.h
     Purpose:       
    Revision: $Id: watershed.h,v 1.2 2003-01-27 11:44:55 philosophil Exp $
  Created by: Philippe Lavoie          (27 Jan, 2003)
 Modified by: 

 Copyright notice:
          Copyright (C) 1996-1998 Philippe Lavoie
 
	  This library is free software; you can redistribute it and/or
	  modify it under the terms of the GNU Library General Public
	  License as published by the Free Software Foundation; either
	  version 2 of the License, or (at your option) any later version.
 
	  This library is distributed in the hope that it will be useful,
	  but WITHOUT ANY WARRANTY; without even the implied warranty of
	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	  Library General Public License for more details.
 
	  You should have received a copy of the GNU Library General Public
	  License along with this library; if not, write to the Free
	  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
=============================================================================*/

#ifndef _PLIB_WATERSHED_HEADER
#define _PLIB_WATERSHED_HEADER

#include "../matrix/barray2d.h"

namespace PLib {
  namespace Morph {
    template <class T>
      void watershed(const Basic2DArray<T>& image, Basic2DArray<T>& result);
  }
}

#ifdef INCLUDE_TEMPLATE_SOURCE
#include "watershed.cpp"
#endif

#endif // #ifndef  _PLIB_WATERSHED_HEADER
