/*=============================================================================
        File: transform.h
     Purpose:       
    Revision: $Id: transform.h,v 1.1 2003-01-27 11:37:36 philosophil Exp $
  Created by: Philippe Lavoie          (18 Jan, 2003)
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

#ifndef _PLIB_TRANSFORM_HEADER
#define _PLIB_TRANSFORM_HEADER

#include "kernel.h"

namespace PLib{
  namespace Morph {
    
    template <class T>
      void unionByOffset(const PLib::Matrix<T>& imageA, int row_offset, int col_offset, PLib::Matrix<T>& imageB);
    
    template <class T>
      void binaryDilation(const PLib::Matrix<T>& image, const Kernel<T>& kernel, PLib::Matrix<T>& result);
    template <class T>
      void binaryErosion(const PLib::Matrix<T>& image, const Kernel<T>& kernel, PLib::Matrix<T>& result);
    
    template <class T>
      void grayDilation(const PLib::Matrix<T>& image, const Kernel<T>& kernel, PLib::Matrix<T>& result);
    template <class T>
      void grayErosion(const PLib::Matrix<T>& image, const Kernel<T>& kernel, PLib::Matrix<T>& result);
    
  }
}

#ifdef INCLUDE_TEMPLATE_SOURCE
#include "transform.cpp"
#endif



#endif
