/*=============================================================================
        File: image.cpp
     Purpose:
    Revision: $Id: image_.cpp,v 1.4 2003-01-13 19:41:11 philosophil Exp $
  Created by: Philippe Lavoie          (18 February 1999)
 Modified by: 

 Copyright notice:
          Copyright (C) 1996-1997 Philippe Lavoie
 
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

#ifndef _PLIB_IMAGE_IMAGEMAGICK_SOURCE
#define _PLIB_IMAGE_IMAGEMAGICK_SOURCE

#include "image.cpp"


#ifdef WITH_IMAGE_MAGICK



namespace PLib { 

  /*! @brief Sets the matrix data from the image
   * 
   * This operation is expensive as it reads from the file each time.
   * You have been warned, so it's ok now.
   */
  void IM_ImageT<Color>::setMatrix(){
    Image *image;
    ImageInfo image_info;
    ExceptionInfo exception;

    InitializeMagick((char *) NULL);
    GetExceptionInfo( &exception );
    GetImageInfo(&image_info);
    strcpy(image_info.filename,file_name.c_str());

    image = ReadImage(&image_info,&exception);
    if(image){
      SetImageType(image,TrueColorType);
      resize(image->rows,image->columns);

      const PixelPacket* pixels = AcquireImagePixels(image,0,0,cols(),rows(),&exception);

      for(int i=0;i<rows();++i)
	for(int j=0;j<cols();++j){
	  elem(i,j).r = pixels->red;
	  elem(i,j).g = pixels->green;
	  elem(i,j).b = pixels->blue;
	  ++pixels;
	}

      DestroyImage(image);
    }
    DestroyExceptionInfo(&exception);
    DestroyImageInfo(&image_info);
    DestroyMagick();
  }


  void IM_ImageT<unsigned char>::setMatrix(){
    Image *image;
    ImageInfo image_info;
    ExceptionInfo exception;

    InitializeMagick((char *) NULL);
    GetExceptionInfo( &exception );
    GetImageInfo(&image_info);
    strcpy(image_info.filename,file_name.c_str());

    image = ReadImage(&image_info,&exception);
    if(image){
      SetImageType(image,GrayscaleType);
      resize(image->rows,image->columns);

      const PixelPacket* pixels = AcquireImagePixels(image,0,0,cols(),rows(),&exception);

      for(int i=0;i<rows();++i)
	for(int j=0;j<cols();++j){
	  elem(i,j) = pixels->red;
	  ++pixels;
	}

      DestroyImage(image);
    }
    DestroyExceptionInfo(&exception);
    DestroyImageInfo(&image_info);
    DestroyMagick();
  }

 
  void IM_ImageT<Color>::setImage(){
    Image *image;
    ImageInfo image_info;
    ExceptionInfo exception;
    char size[MaxTextExtent];

    unsigned char *buffer;
    buffer = new unsigned char[cols()*rows()*3];
    for(int i=0;i<rows();++i){
      for(int j=0;j<cols();++j){
	int offset = i*cols()*3+j*3;
	buffer[offset]=elem(i,j).r;
	buffer[offset+1]=elem(i,j).g;
	buffer[offset+2]=elem(i,j).b;
      }
    }


    InitializeMagick((char *) NULL);
    GetExceptionInfo( &exception );
    GetImageInfo(&image_info);

    image = ConstituteImage(cols(),rows(),"RGB",CharPixel,buffer,&exception);
    
    if(image){
      strcpy(image->filename,file_name.c_str());
      int result = WriteImage(&image_info,image);
    }

    DestroyImage(image);
    delete []buffer;
    DestroyExceptionInfo(&exception);
    DestroyImageInfo(&image_info);
    DestroyMagick();
  }
  
  void IM_ImageT<unsigned char>::setImage(){
    Image *image;
    ImageInfo image_info;
    ExceptionInfo exception;
    char size[MaxTextExtent];

    unsigned char *buffer;
    buffer = new unsigned char[cols()*rows()];
    for(int i=0;i<rows();++i){
      for(int j=0;j<cols();++j){
	int offset = i*cols()+j;
	buffer[offset]=elem(i,j);
      }
    }


    InitializeMagick((char *) NULL);
    GetExceptionInfo( &exception );
    GetImageInfo(&image_info);

    image = ConstituteImage(cols(),rows(),"I",CharPixel,buffer,&exception);
    
    if(image){
      strcpy(image->filename,file_name.c_str());
      int result = WriteImage(&image_info,image);
    }

    DestroyImage(image);
    delete []buffer;
    DestroyExceptionInfo(&exception);
    DestroyImageInfo(&image_info);
    DestroyMagick();
  }
  
  
  int IM_ImageT<Color>::read(const std::string &filename) {
    file_name = filename;    
    setMatrix() ;
    return 1 ;
  }
  
  int IM_ImageT<unsigned char>::read(const std::string& filename) {
    file_name = filename;    
    setMatrix() ;
    return 1 ;
  }


  int IM_ImageT<Color>::write(const std::string& filename) {
    file_name = filename;    
    setImage() ;
    
    return 1;
  }
  
  int IM_ImageT<unsigned char>::write(const std::string& filename) {
    file_name = filename;
    setImage() ;
    
    return 1;
  }

#ifdef NO_IMPLICIT_TEMPLATES
  template class IM_ImageT<unsigned char> ;
  template class IM_ImageT<Color> ;

#endif

} // end namespace 

#endif // WITH_IMAGE_MAGICK

 

#endif // IMAGE_IMAGEMAGICK_SOURCE
