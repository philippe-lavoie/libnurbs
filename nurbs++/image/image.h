/*=============================================================================
        File: image.h
     Purpose: To add some basic image processing capabilities to the 
              matrix class
    Revision: $Id: image.h,v 1.5 2003-01-27 11:37:35 philosophil Exp $
  Created by: Philippe Lavoie          (3 Oct, 1996)
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

#ifndef _PLIB_image_h_
#define _PLIB_image_h_

#include "matrix.h"
#include "color.h"

/*!
 */
namespace PLib {

  /*!
    \class MatrixImage image.h 
    \brief A basic templated image class

    This class allows one to draw a line or a point on a matrix 
    as if it was an image.
    
    \author Philippe Lavoie 
    \date 4 Oct. 1996
  */
  template <class T> 
    class MatrixImage : public Matrix<T> {
    public:
      MatrixImage(void) : Matrix<T>() {}
      MatrixImage(Matrix<T>& img): Matrix<T>(img) {}
      MatrixImage(MatrixImage<T>& img): Matrix<T>(img) {}
      MatrixImage(const int r, const int c): Matrix<T>(r,c) {}
      ~MatrixImage() {}
      
      void drawLine(int i1, int j1, int i2, int j2, T color) ;
      void drawPoint(int i, int j, double radius, T color) ;
      void store(Matrix<T>&) ;
    };
  
} // end namespace

typedef PLib::MatrixImage<unsigned char> Image_UBYTE ;
typedef PLib::MatrixImage<char> Image_BYTE ;
typedef PLib::MatrixImage<int> Image_INT ;
typedef PLib::MatrixImage<double> Image_DOUBLE ;
typedef PLib::MatrixImage<PLib::Color> Image_Color ;

#ifdef WITH_IMAGE_MAGICK

#include <magick/magick_config.h>
#include <stdio.h>
#include <magick/api.h>

namespace PLib{

  /*!
    \class IM_ImageT image.h matrix/image.h
    \brief A class which uses Image Magick for the reading/saving of matrices.
    
    This class enables someone to read or write all the images 
    types supported by the Image Magick library. 

    Only two types of images are supported, grayscale images and
    RGB color images.  Use \verb.IM_Image. and \verb.IM_ColorImage.
    to access these two types.

    Unfortunately, that library renames some words which are
    often used in X11, such as {\tt Opaque}. The header file of 
    this class  undefines {\tt Opaque} from Image Magick, so it 
    can link with X11 libraries. If you need the {\tt Opaque} 
    definition from Image Magick, you'll have to find a workaround.

    \author Philippe Lavoie 
    \date 4 October 1996
  */
  template <class T>
    class IM_ImageT: public MatrixImage<T> {
    public:
      IM_ImageT(const std::string &filename, int save=0);
      IM_ImageT() ;
      IM_ImageT(const int r, const int c) ;
      ~IM_ImageT() ;
      
      int read(const std::string &filename);
      int write(const std::string &filename);

      IM_ImageT<T>& operator=(const Basic2DArray<T>& image){
	((Basic2DArray<T>&)*this) = image;
	return *this;
      }

      
    protected:
      std::string file_name ;
      int autoSave ;
      
      void setImage() ;
      void setMatrix() ;
    };
  
} // end namespace

typedef PLib::IM_ImageT<unsigned char> IM_Image ;
typedef PLib::IM_ImageT<PLib::Color> IM_ColorImage ;

#ifdef INCLUDE_TEMPLATE_SOURCE
#include "image_.cpp"
#endif

#endif // WITH_IMAGE_MAGICK

#ifdef INCLUDE_TEMPLATE_SOURCE
#include "image.cpp"
#endif


#endif 
