/*=============================================================================
        File: watershed.cpp
     Purpose:
    Revision: $Id: watershed.cpp,v 1.2 2003-01-29 11:20:51 philosophil Exp $
  Created by:    Philippe Lavoie          (27 Jan, 2003)
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

#ifndef _PLIB_MORPH_WATERSHED_SOURCE
#define _PLIB_MORPH_WATERSHED_SOURCE

#include "watershed.h"
#include "../matrix/barray.h"
#include "../matrix/barray2d.h"

/*!
  \brief returns the minimum label around a point i,j
  
  This checks in an 8 connected area.

  \author Philippe Lavoie
  \date 27 Jan 2003
*/
int neighbors(const PLib::Basic2DArray<int>& labels, int i, int j, PLib::BasicArray<int>& local_labels){
  unsigned char min_value = 65500;
  local_labels.resize(0);

  for(int k=i-1;k<=i+1;++k){
    if(k>=0 && k<labels.rows()){
      for(int l=j-1;l<=l+1;++l){
	if(l>=0 && l<labels.cols()){
	  int value = labels(i,j);
	  if(value>0){
	    local_labels.push_back(value);
	    if(min_value>value){
	      min_value = value;
	    }
	  }
	}
      }
    }
  }
  if(min_value = 65500){
    min_value = 0;
  }
  return min_value;
}
  

/*!
  \brief labels an image

  Labels using 8 connectivity an image at a certain gray level.
  Also, it only labels pixels which are not resolved yet.

  This algorithm is based on a space-efficient two-pass algorithm
  written by Lumia, Shaprio and Zuniga, 1983.

  \return true if there is at least one label created for that gray level.

  \author Philippe Lavoie
  \date 27 Jan 2003
*/
bool labelImage(const PLib::Basic2DArray<unsigned char>& image, PLib::Basic2DArray<int>& labels, unsigned char value, int& last_label){
  bool pixel_found=false;
 
  PLib::BasicArray<int> eq_table(image.cols());
  PLib::BasicArray<int> local_labels(9);
  labels.resize(image.rows(),image.cols());

  // Top down pass
  for(int i=0;i<image.rows();++i){
    // 
    eq_table.reset(0);
    eq_table.resize(0);
    for(int j=0;j<image.cols();++j){
      labels(i,j) = 0;
    }

    // Process the line
    for(int j=0;j<image.cols();++j){
      if(image(i,j)==value){
	unsigned char a = neighbors(labels,i,j,local_labels);
	if(!a){	
	  ++last_label;
	  a = last_label;
	}
	labels(i,j) = a;
	for(int k=0;k<local_labels.size();++k){
	  // Use a hash?
	  //eq_table
	}
      }
    }
  }

  return pixel_found;
}

/*!
  \brief The watershed algorithm

  This is a homegrown implementation of the well known algorithm.
  I'm pretty sure somebody thaught of it before, but I don't have
  time to double check.

  It uses 8 connectivity for now.

  \author Philippe Lavoie
  \date 27 Jan 2003
*/
template <>
void PLib::Morph::watershed<unsigned char> (const PLib::Basic2DArray<unsigned char>& image, PLib::Basic2DArray<unsigned char>& result){
  PLib::Basic2DArray<unsigned char> resolved_mask(image.rows(),image.cols());
  PLib::Basic2DArray<int> labels(image.rows(),image.cols());
  result.resize(image.rows(), image.cols());

  int last_label = 1;

  int i=0;
  while(i<256){
    if(labelImage(image,labels,i,last_label)){
      break;
    }
    ++i;
  }

  if(i==256){
    return;
  }

  
}


#endif
