/*=============================================================================
        File: watershed.cpp
     Purpose:
    Revision: $Id: watershed.cpp,v 1.3 2003-05-15 02:34:55 philosophil Exp $
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
#include <hash_map>
#include <alloc.h>

typedef std::pair <int, int> HashPair;


/*!
  \brief returns the minimum label around a point i,j
  
  This checks in an 8 connected area.

  \author Philippe Lavoie
  \date 27 Jan 2003
*/
int neighbors(const PLib::Basic2DArray<int>& labels, int i, int j, PLib::BasicArray<int>& local_labels){
  int min_value = 65500;
  local_labels.resize(0);

  for(int k=i-1;k<=i+1;++k){
    if(k>=0 && k<labels.rows()){
      for(int l=j-1;l<=j+1;++l){
	if(l>=0 && l<labels.cols()){
	  int value = labels(k,l);
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
  if(min_value == 65500){
    min_value = 0;
  }
  return min_value;
}
void setToEquivalentLabel(int i, std::hash_map<int,int>& eq_table, PLib::Basic2DArray<int>& labels){
  std::hash_map<int,int>::iterator eq_table_iterator;
  std::hash_map<int,int>::const_iterator value;
  std::hash_map<int,int>::const_iterator last_value;
  std::hash_map<int,int> eq_result;

  PLib::BasicArray<int> equivalence_stack(labels.cols());
  equivalence_stack.resize(0);
  int stack_pos = 0;
  for(eq_table_iterator=eq_table.begin();eq_table_iterator!=eq_table.end();eq_table_iterator++){
    int equivalence = eq_table_iterator -> second;
    
    cerr << "Checking for key " << eq_table_iterator->first << " " <<
      eq_table_iterator->second << " at " << i << endl;
    
    // if equivalence already found, let's skip it
    value = eq_result.find(eq_table_iterator->first);
    if(value != eq_result.end()){
      continue;
    }
    
    value = eq_table_iterator; //eq_table.find(equivalence);
    last_value = eq_table.end();
    equivalence_stack.push_back(value->first);	
    while( (value = eq_table.find(value->second)) != eq_table.end()){
      last_value = value;
      equivalence_stack.push_back(value->first);
      cerr << "Finding new value for " << value->first << endl;
    }
    // At this point last_value = the equivalence
    if(last_value != eq_table.end()){
      cerr << "Setting all to " << last_value->second << endl;
      for(int i=stack_pos;i<equivalence_stack.size();i++){
	eq_result.insert( HashPair(equivalence_stack[i],last_value->second));
      }
    }
    else{
      eq_result.insert( HashPair(eq_table_iterator->first, eq_table_iterator->second) );
    }
    stack_pos = equivalence_stack.size() - 1;
    
  }
  
  for(eq_table_iterator=eq_result.begin();eq_table_iterator!=eq_result.end();eq_table_iterator++){
    for(int j=0;j<labels.cols();++j){
      if(labels(i,j)==eq_table_iterator->first){
	labels(i,j)=eq_table_iterator->second;
      }
    }
  }
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
bool PLib::Morph::labelImage(const PLib::Basic2DArray<unsigned char>& image, PLib::Basic2DArray<int>& labels, unsigned char value, int& last_label){
  bool pixel_found=false;
 
  PLib::BasicArray<int> local_labels(9);
  labels.resize(image.rows(),image.cols());

  std::hash_map<int,int> eq_table;

  // Top down pass
  for(int i=0;i<image.rows();++i){
    // 
    eq_table.clear();

    //for(int j=0;j<image.cols();++j){
    //  labels(i,j) = 0;
    //}

    // Process the line
    for(int j=0;j<image.cols();++j){
      if(image(i,j)==value){
	int a = neighbors(labels,i,j,local_labels);
	if(!a){	
	  ++last_label;
	  a = last_label;
	}
	labels(i,j) = a;
	for(int k=0;k<local_labels.size();++k){
	  if(local_labels[k]!=a){
	    eq_table.insert( HashPair(local_labels[k],a));
	  }
	}
      }
    }

    // Find equivalences for that line
    // loop through the hash map
    setToEquivalentLabel(i, eq_table,labels);
  }

  // Down top pass
  for(int i=image.rows()-1;i>=0;--i){
    // 
    eq_table.clear();

    //for(int j=0;j<image.cols();++j){
    //  labels(i,j) = 0;
    //}

    // Process the line
    for(int j=image.cols()-1;j>=0;--j){
      if(image(i,j)==value){
	int a = neighbors(labels,i,j,local_labels);
	if(!a){	
	  ++last_label;
	  a = last_label;
	}
	labels(i,j) = a;
	for(int k=0;k<local_labels.size();++k){
	  if(local_labels[k]!=a){
	    eq_table.insert( HashPair(local_labels[k],a));
	  }
	}
      }
    }

    // Find equivalences for that line
    // loop through the hash map
    setToEquivalentLabel(i, eq_table,labels);
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

#ifdef NO_IMPLICIT_TEMPLATES

namespace std {
  template class hashtable<pair<int const, int>, int, hash<int>, _Select1st<pair<int const, int> >, equal_to<int>, allocator<int> >;
  template unsigned long const * __lower_bound<unsigned long const *, unsigned long, int>(unsigned long const *, unsigned long const *, unsigned long const &, int *);
  template _Hashtable_node<pair<int const, int> > ** fill_n<_Hashtable_node<pair<int const, int> > **, unsigned int, _Hashtable_node<pair<int const, int> > *>(_Hashtable_node<pair<int const, int> > **, unsigned int, _Hashtable_node<pair<int const, int> > * const &);
  template class allocator<int>;
  template class vector<_Hashtable_node<pair<int const, int> > *, allocator<int> >;
  template void fill<_Hashtable_node<pair<int const, int> > **, _Hashtable_node<pair<int const, int> > *>(_Hashtable_node<pair<int const, int> > **, _Hashtable_node<pair<int const, int> > **, _Hashtable_node<pair<int const, int> > * const &);
  template class _Hashtable_iterator<pair<int const, int>, int, hash<int>, _Select1st<pair<int const, int> >, equal_to<int>, allocator<int> >;
  //  template class vector<_Hashtable_node<pair<int const, int> > *, allocator<int> >::insert(_Hashtable_node<pair<int const, int> > **, unsigned int, _Hashtable_node<pair<int const, int> > *const &);
}

namespace PLib{
  namespace Morph{
  }
}
#endif




#endif
