/*=============================================================================
        File: image.cpp
     Purpose:
    Revision: $Id: image_.cpp,v 1.3 2002-05-31 17:39:34 philosophil Exp $
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

#include "image.cpp"

namespace PLib {

#ifdef WITH_IMAGE_MAGICK

  void IM_ImageT<Color>::setMatrix(){
    if (image.rows() != rows() || image.columns() != cols()){
      resize(image.rows(),image.columns());
    }
    for(int i=0;i<rows();++i)
      for(int j=0;j<cols();++j){
	Magick::Color color = image.pixelColor(i,j);	
	elem(i,j).r = color.redQuantum();
	elem(i,j).g = color.greenQuantum();
	elem(i,j).b = color.blueQuantum();
      }
  }
  
  void IM_ImageT<unsigned char>::setMatrix(){
    if (image.rows() != rows() || image.columns() != cols()){
      resize(image.rows(),image.columns());
    }
    for(int i=0;i<rows();++i)
      for(int j=0;j<cols();++j){
	Magick::Color color = image.pixelColor(i,j);	
	elem(i,j) = color.redQuantum();
      }
  }

 
  void IM_ImageT<Color>::setImage(){
    if (image.rows() != rows() || image.columns() != cols()){
      Magick::Geometry geometry(cols(),rows());
      image.size(geometry);
    }

    Magick::PixelPacket *pixels = image.setPixels(0,0,cols(),rows());

    for(int i=0;i<rows();++i)
      for(int j=0;j<cols();++j){
	Color in_color = elem(i,j);
	Magick::Color color(in_color.r,in_color.b,in_color.g);
	Magick::PixelPacket *pixel = pixels+i*cols()*sizeof(Magick::PixelPacket)+j;
	*pixel = color;
      }

    image.syncPixels();
  }
  
  void IM_ImageT<unsigned char>::setImage(){
    if (image.rows() != rows() || image.columns() != cols()){
      Magick::Geometry geometry(cols(),rows());
      image.size(geometry);
    }

    Magick::PixelPacket *pixels = image.setPixels(0,0,cols(),rows());

    for(int i=0;i<rows();++i)
      for(int j=0;j<cols();++j){
	Color in_color = elem(i,j);
	Magick::Color color(in_color.r,in_color.b,in_color.g);
	Magick::PixelPacket *pixel = pixels+i*cols()*sizeof(Magick::PixelPacket)+j;
	*pixel = color;
      }

    image.syncPixels();
  }
  
  
  
  int IM_ImageT<Color>::read(const std::string &filename) {
    image.read(filename);
    if(image.rows()==0 || image.columns() == 0){
      return 0;
    }
    setMatrix() ;
    
    return 1 ;
  }
  
  int IM_ImageT<unsigned char>::read(const std::string& filename) {
    image.read(filename);
    if(image.rows()==0 || image.columns() == 0){
      return 0;
    }
    setMatrix() ;
    
    return 1 ;
  }
  
  int IM_ImageT<Color>::write(const std::string& filename) {
    
    setImage() ;
    image.write(filename);
    
    return 1;
  }
  
  int IM_ImageT<unsigned char>::write(const std::string& filename) {
    setImage() ;
    image.type(Magick::GrayscaleType );
    image.write(filename);
    
    return 1;
  }


#ifdef NO_IMPLICIT_TEMPLATES
  template class IM_ImageT<unsigned char> ;
  template class IM_ImageT<Color> ;
#endif


#endif


#ifdef NO_IMPLICIT_TEMPLATES
  template class MatrixImage<int> ;
  template class MatrixImage<float> ;
  template class MatrixImage<double> ;
  template class MatrixImage<char> ;
  template class MatrixImage<unsigned char> ;
  template class MatrixImage<Color> ;
#endif
  
}
