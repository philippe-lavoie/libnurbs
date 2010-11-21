/*=============================================================================
        File: kernel.cpp
     Purpose:
    Revision: $Id: kernel.cpp,v 1.1 2003-01-27 11:37:36 philosophil Exp $
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

#ifndef _PLIB_MORPH_KERNEL_SOURCE
#define _PLIB_MORPH_KERNEL_SOURCE

#include "kernel.h"

/*! 
  \brief Default constructor

  Creates a kernel to be used inside morphological operations. The center 
  can be anywhere within the appropriate limits.
  
  \param r
  \param c
  \param center_r
  \param center_c

  \warning center_r must be smaller or equal to r
  \warning center_c must be smaller or equal to c

  \author Philippe Lavoie
  \date 18 January 2003
*/
template <class T>
PLib::Morph::Kernel<T>::Kernel(const int r, const int c, const int center_r, const int center_c){
  if(center_r<0 || center_r>r || center_c <0 || center_c>c){
#ifdef USE_EXCEPTION
    throw WrongSize2D(r,c,center_r,center_c);
#else
    Error error("Kernel<T>::Kernel");
    error << "The center must be within bound";
    error.fatal();
#endif
  }
  this->resize(r,c);
  m_center_row = center_r;
  m_center_column = center_c;
  m_mask.resize(this->rows(),this->cols());
  m_mask.reset(255);
}

/*! 
  \brief Default 3x3 kernel constructor

  Most kernels are a 3x3 matrix centered around the (1,1) coordinate.
  This constructor allows you to easilly create such a kernel.
  
  \param k00 The kernel element at 0,0
  \param k01 The kernel element at 0,1
  \param k01 The kernel element at 0,2
  \param k10 The kernel element at 1,0
  \param k11 The kernel element at 1,1
  \param k11 The kernel element at 1,2
  \param k20 The kernel element at 2,0
  \param k21 The kernel element at 2,1
  \param k21 The kernel element at 2,2

  \author Philippe Lavoie
  \date 18 January 2003
*/
template <class T>
PLib::Morph::Kernel<T>::Kernel(const T k00, const T k01, const T k02, 
			       const T k10, const T k11, const T k12, 
			       const T k20, const T k21, const T k22){
  this->resize(3,3);
  m_mask.resize(this->rows(),this->cols());
  m_mask.reset(255);
  m_center_row = 1;
  m_center_column = 1;
  this->elem(0,0) = k00;
  this->elem(0,1) = k01;
  this->elem(0,2) = k02;
  this->elem(1,0) = k10;
  this->elem(1,1) = k11;
  this->elem(1,2) = k12;
  this->elem(2,0) = k20;
  this->elem(2,1) = k21;
  this->elem(2,2) = k22;
}


/*! 
  \brief Creates a circular kernel of radius r

  The creation is not done using the most effective mean. 
  However, it does allow other type of disk kernels
  to reuse the circle midpoint drawing algorithm.

  \param r radius of the disk

  \author Philippe Lavoie
  \date 23 Jan 2003
*/
template <class T>
void PLib::Morph::DiskKernel<T>::init(int r){
  this->resize(2*r+1,2*r+1);
  this->m_center_row = r;
  this->m_center_column = r;

  this->m_mask.resize(this->rows(),this->cols());
  this->m_mask.reset(0); 

  for(int i=0;i<=r;++i){
    circleMidpoint(i,setValueAtRadius(i));
  }
}

/*! 
  \brief Sets the kernel and the mask around the center point

  When setting a pixel to a value, you must also enable the mask
  to see that pixel. The coordinates (r,c) are translated back
  to a proper matrix notation by translating by (m_center_row,
  m_center_column).
  
  \author Philippe Lavoie
  \date 25 Jan 2003
*/
template <class T>
void PLib::Morph::DiskKernel<T>::setElement(int r, int c, T value){
  this->elem(this->m_center_row + r, this->m_center_column + c) = value;
  this->m_mask(this->m_center_row + r, this->m_center_column + c) = 255;

  if(r>1 && this->elem(this->m_center_row+r-1,this->m_center_column+c)==0){
    double radius = sqrt( (double)(r*r) + (double)(c*c) );
    setCirclePoints(r-1,c,setValueAtRadius(radius));
  }
}

/*!
  \brief Computes the value for a pixel at that radius
  
  The basic implementation is to return the value.
*/
template <class T>
T PLib::Morph::DiskKernel<T>::setValueAtRadius(double radius){
  return m_value;
}

/*! 
  \brief draws the points on the cirle using symmetry
  
  Using symmetry, only an 1/8 of the cirle needs to be specified 
  to be fully drawn.

  This is part of the general circle drawing algorithm.
*/
template <class T>
void PLib::Morph::DiskKernel<T>::setCirclePoints(int x, int y, T value){
  if(x==0){
    setElement( y,  0, value);
    setElement(-y,  0, value);
    setElement( 0,  y, value);
    setElement( 0, -y, value);
  }
  if(x==y){
    setElement(  y,  x, value);
    setElement( -y,  x, value);
    setElement(  y, -x, value);
    setElement( -y, -x, value);
  }
  if(x<y){
    setElement(  y,   x, value);
    setElement( -y,   x, value);
    setElement(  y,  -x, value);
    setElement( -y,  -x, value);    
    setElement(  x,   y, value);
    setElement( -x,   y, value);
    setElement(  x,  -y, value);
    setElement( -x,  -y, value);
  }
}

/*!
  \brief uses the midpoint algorithm to draw a circle

  This is the generel midpoint algorithm for circles. 
*/
template <class T>
void PLib::Morph::DiskKernel<T>::circleMidpoint(int radius, T value){
  int x = 0;
  int y = radius;
  int p = (5 - radius*4)/4;

  setCirclePoints(x, y, value);
  while (x < y) {
    x++;
    if (p < 0) {
      p += 2*x+1;
    } else {
      y--;
      p += 2*(x-y)+1;
    }
    setCirclePoints(x, y, value);
  }

}


/*!
  \brief Computes the value for a pixel at that radius
  
  It's simply a linear approximation between the min and max value.
*/
template <class T>
T PLib::Morph::ConicDiskKernel<T>::setValueAtRadius(double radius){
  double x = radius/m_radius;
  return (T)(m_max - ((m_max-m_min)*x) );
}

/*!
  \brief Computes the value for a pixel at that radius

  Computes the Gaussian value for the radius.
*/
template <class T>
T PLib::Morph::GaussianDiskKernel<T>::setValueAtRadius(double radius){
  // scale radius to be between 0 and 2
  radius /= m_radius;
  radius *= 2.3548;

  double gauss = exp( -(radius*radius) );
  gauss /= exp(0);

  return (T)(m_min + (m_max-m_min)*gauss);
}



#ifdef NO_IMPLICIT_TEMPLATES
namespace PLib{
  namespace Morph{
    template class Kernel<unsigned char>;
    template class N4Kernel<unsigned char>;
    template class N8Kernel<unsigned char>;
    template class DiskKernel<unsigned char>;
    template class ConicDiskKernel<unsigned char>;
    template class GaussianDiskKernel<unsigned char>;
  }
}
#endif

#endif // #ifndef _PLIB_MORPH_KERNEL_SOURCE
