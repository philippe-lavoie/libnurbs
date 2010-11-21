/*=============================================================================
        File: kernel.h
     Purpose:       
    Revision: $Id: kernel.h,v 1.1 2003-01-27 11:37:36 philosophil Exp $
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

#ifndef _PLIB_KERNEL_HEADER
#define _PLIB_KERNEL_HEADER

#include "../matrix/matrix.h"

namespace PLib{
  namespace Morph {

  /*!
    \brief A kernel is a matrix wich can be centered on any element
    
    The kernel is usually applied to an image inside a morphological
    operation. There are some basic kernels that are defined such as
    the 4 connected kernel and the 8 connected kernel. The others
    are user defined. 
    
    Becauce the 3x3 kernel is so popular, there is a constructor provided
    to create one easilly.
    
    \author Philippe Lavoie
    \date 18 Janurary 2003
  */
  template <class T>
    class Kernel : public PLib::Matrix<T> {
    public:
    Kernel(const int r, const int c, const int center_r, const int center_c);
    Kernel(const T k00, const T k01, const T k02, 
	     const T k10, const T k11, const T k12, 
	   const T k20, const T k21, const T k22);
    
    int centerRow() const { return m_center_row; }
    int centerColumn() const { return m_center_column; }

    void setMask(const Basic2DArray<unsigned char>& mask);

    bool mask(int i, int j) { return mask(i,j)>0 ; }
    
    protected:

    Kernel() { ; } // empty constructor, i.e. doesn't construct anything.

    int m_center_row;
    int m_center_column;
    Basic2DArray<unsigned char> m_mask;
  };
  
  /*!
    \brief the 4 connected kernel
  */
  template <class T>
    class N4Kernel: public Kernel<T>{
    public:
    N4Kernel() : Kernel<T>(0,1,0,1,1,1,0,1,0) { ; }
  };
  
  /*!
    \brief the 8 connected kernel
  */
  template <class T>
    class N8Kernel: public Kernel<T>{
    public:
    N8Kernel():Kernel<T>(1,1,1,1,1,1,1,1,1) { ; }
  };

  /*! 
    \brief a disk kernel

    This kernel creates a disk. It sets the mask appropriately for
    gray level operations. The values of the kernel on the
    disk are all set to value.

    \author Philippe Lavoie
    \date 23 Jan 2003
  */
  template <class T>
    class DiskKernel: public Kernel<T>
    {
    public:
      DiskKernel(int radius) { m_value = (T)255; init(radius); }
      DiskKernel(int radius, T value) { m_value = value; init(radius); }

    protected:
      DiskKernel(){;}

      void init(int radius);
      void setCirclePoints(int x, int y, T value);
      void circleMidpoint(int radius, T value);
      void setElement(int r, int c, T value);
      virtual T setValueAtRadius(double radius);

    private:
      T m_value;
    };

  /*! 
    \brief a disk kernel with values as a gaussian

    This kernel creates a disk. It sets the mask appropriately for
    gray level operations. The values inside the disk are 
    gaussian distributed from the center (max value) to 
    the radius (min value).

    \author Philippe Lavoie
    \date 23 Jan 2003
  */
  template <class T>
    class GaussianDiskKernel: public DiskKernel<T>
    {
    public:
      GaussianDiskKernel(int radius,T min, T max){
	m_min = min;
	m_max = max;
	m_radius = radius;
	this->init(radius);
      }

    protected:
      T setValueAtRadius(double radius);

      T m_min;
      T m_max;
      double m_radius;
    };

  /*! 
    \brief a disk kernel wich values as a conic

    This kernel creates a disk. It sets the mask appropriately for
    gray level operations. The values inside the disk are linearly
    distributed from the center (max value) to the radius (min value)..

    \author Philippe Lavoie
    \date 23 Jan 2003
  */
  template <class T>
    class ConicDiskKernel: public DiskKernel<T>
    {
    public:
      ConicDiskKernel(int radius, T min, T max){
	m_min = min;
	m_max = max;
	m_radius = radius;
	this->init(radius);
      }

    protected:
      T setValueAtRadius(double radius);

      T m_min;
      T m_max;
      double m_radius;
    };

}


}

#ifdef INCLUDE_TEMPLATE_SOURCE
#include "kernel.cpp"
#endif



#endif
