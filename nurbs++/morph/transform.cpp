/*=============================================================================
        File: kernel.cpp
     Purpose:
    Revision: $Id: transform.cpp,v 1.1 2003-01-27 11:37:36 philosophil Exp $
  Created by:    Philippe Lavoie          (18 Jan, 2003)
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

#ifndef _PLIB_MORPH_TRANSFORM_SOURCE
#define _PLIB_MORPH_TRANSFORM_SOURCE

#include "transform.h"
#include "matrix/matrixTool.h"

template <class T>
void PLib::Morph::unionByOffset(const PLib::Matrix<T>& imageA, int row_offset, int col_offset, PLib::Matrix<T>& imageB){
  //imageB.resizeKeep(imageA.rows(),imageB.cols());
  for(int i=imageA.rows()-1;i>=0;--i){
    if(i+row_offset<0 || i+row_offset>=imageA.rows()){
      continue;
    }
    for(int j=imageA.cols()-1;j>=0;--j){ 
      if(j+col_offset<0 || j+col_offset>=imageA.cols()){
	continue;
      }
      T e; 
      if((e=imageA(i,j))>0){
	imageB(i+row_offset,j+col_offset)++;
      }
    }
  }
}
 
template <class T>
void PLib::Morph::binaryDilation(const PLib::Matrix<T>& image, const Kernel<T>& kernel, PLib::Matrix<T>& result){
  result.resize(image.rows(),image.cols());
  result.reset(0);
  int i=0;
  int j=0;
  for(i=0;i<kernel.rows();i++){
    for(j=0;j<kernel.cols();j++){
      if(kernel(i,j)>0){
	unionByOffset(image,i-kernel.centerRow(),j-kernel.centerColumn(),result);
      }
    }
  }
  // loop over the result image and remove all points with lesser value then n_elements
  for(i=result.rows()-1;i>=0;--i){
    for(j=result.cols()-1;j>=0;--j){
      if(result(i,j)>0){
	result(i,j)=255;
      }
    }
  }
}

template <class T>
void PLib::Morph::binaryErosion(const PLib::Matrix<T>& image, const Kernel<T>& kernel, PLib::Matrix<T>& result){
  result.resize(image.rows(),image.cols());
  result.reset(0);
  int n_elements = 0;
  int i=0;
  int j=0;
  for(i=0;i<kernel.rows();i++){
    for(j=0;j<kernel.cols();j++){
      if(kernel(i,j)>0){
	unionByOffset(image,-(i-kernel.centerRow()),-(j-kernel.centerColumn()),result);
	++n_elements;
      }
    }
  }
  // loop over the result image and remove all points with lesser value then n_elements
  for(i=result.rows()-1;i>=0;--i){
    for(j=result.cols()-1;j>=0;--j){
      if(result(i,j)>0){
	if(result(i,j)<n_elements){
	  result(i,j)=0;
	}
	else{
	  result(i,j)=255;
	}
      }
    }
  }
}

template <class T>
class Extremum{
public:
  Extremum();

  static T safeAdd(T a, T b);
  static T maxValue();
  static T minValue();
};

template <class T>
T regionMinimum(const PLib::Matrix<T> &image, const PLib::Morph::Kernel<T> &kernel, int row_offset, int col_offset){
  T min_value=Extremum<T>::maxValue();
  int row = row_offset-kernel.centerRow();
  int col = col_offset-kernel.centerColumn();
  for(int i=kernel.rows()-1;i>=0;--i){
    for(int j=kernel.cols()-1;j>=0;--j){
      min_value = PLib::minimum(min_value,
				Extremum<T>::safeAdd(image(row+i,col+j),kernel(i,j)));
    }
  }
  return min_value;
}
 
template <class T>
T regionMaximum(const PLib::Matrix<T> &image, const PLib::Morph::Kernel<T> &kernel, int row_offset, int col_offset){
  T max_value=Extremum<T>::minValue();
  int row = row_offset-kernel.centerRow();
  int col = col_offset-kernel.centerColumn();
  for(int i=kernel.rows()-1;i>=0;--i){
    for(int j=kernel.cols()-1;j>=0;--j){
      max_value = PLib::maximum(max_value,
				Extremum<T>::safeAdd(image(row+i,col+j),kernel(i,j)));
    }
  }
  return max_value;
}
 
template <class T>
void PLib::Morph::grayErosion(const PLib::Matrix<T>& image, const Kernel<T>& kernel, PLib::Matrix<T>& result){
  result.resize(image.rows(),image.cols());
  result.reset(0);
  int i=0;
  int j=0;
  for(i=image.rows()-1;i>=0;--i){
    if(i-kernel.centerRow()<0 || i+(kernel.rows()-kernel.centerRow())>image.rows()){
      continue;
    }
    for(j=image.cols()-1;j>=0;--j){
      if(j-kernel.centerColumn()<0 || 
	 j+(kernel.cols()-kernel.centerColumn())>image.cols()){
	continue;
      }      
      result(i,j) = regionMinimum(image,kernel,i,j);
    }
  }
}

template <class T>
void PLib::Morph::grayDilation(const PLib::Matrix<T>& image, const Kernel<T>& kernel, PLib::Matrix<T>& result){
  result.resize(image.rows(),image.cols());
  result.reset(0);
  int i=0;
  int j=0;
  for(i=image.rows()-1;i>=0;--i){
    if(i-kernel.centerRow()<0 || i+(kernel.rows()-kernel.centerRow())>image.rows()){
      continue;
    }
    for(j=image.cols()-1;j>=0;--j){
      if(j-kernel.centerColumn()<0 || 
	 j+(kernel.cols()-kernel.centerColumn())>image.cols()){
	continue;
      }      
      result(i,j) = regionMaximum(image,kernel,i,j);
    }
  }
}


unsigned char Extremum<unsigned char>::safeAdd(unsigned char a, unsigned char b){
  int c = a;
  c += b;
  return (unsigned char)( c % 256);
}

unsigned char Extremum<unsigned char>::maxValue() 
{
  return 255;
}

unsigned char Extremum<unsigned char>::minValue() 
{
  return 0;
}




#ifdef NO_IMPLICIT_TEMPLATES

template unsigned char regionMinimum(const PLib::Matrix<unsigned char> &image, const PLib::Morph::Kernel<unsigned char> &kernel, int row_offset, int col_offset);
template unsigned char regionMaximum(const PLib::Matrix<unsigned char> &image, const PLib::Morph::Kernel<unsigned char> &kernel, int row_offset, int col_offset);    

namespace PLib{
  namespace Morph{
    template void unionByOffset(const PLib::Matrix<unsigned char>& imageA, int row_offset, int col_offset, PLib::Matrix<unsigned char>& imageB);
    template void binaryDilation(const PLib::Matrix<unsigned char>& image, const Kernel<unsigned char>& kernel, PLib::Matrix<unsigned char>& result);
    template void binaryErosion(const PLib::Matrix<unsigned char>& image, const Kernel<unsigned char>& kernel, PLib::Matrix<unsigned char>& result);
    template void grayDilation(const PLib::Matrix<unsigned char>& image, const Kernel<unsigned char>& kernel, PLib::Matrix<unsigned char>& result);
    template void grayErosion(const PLib::Matrix<unsigned char>& image, const Kernel<unsigned char>& kernel, PLib::Matrix<unsigned char>& result);



  }
}
#endif


#endif // #ifndef _PLIB_MORPH_TRANSFORM_SOURCE
