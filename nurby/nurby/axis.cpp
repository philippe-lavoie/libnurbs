#include "axis.h"
#include "gl_util.h"

#include <iostream>

Axis::Axis(){
  axis_id = glGenLists( 1 );
  
  glNewList( axis_id, GL_COMPILE );
  
  glBegin(GL_LINES);
  
  glLineWidth( 2.0 );

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,GLUtil::black) ;
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,GLUtil::red) ;
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GLUtil::red);
  glColor4fv(GLUtil::red);
  glVertex3i(0,0,0) ;
  glVertex3i(1,0,0) ;

  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,GLUtil::green) ;
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GLUtil::green) ;  
  glColor4fv(GLUtil::green);
  glVertex3i(0,0,0) ;
  glVertex3i(0,1,0) ;

  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,GLUtil::blue) ;
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,GLUtil::blue) ;
  glColor4fv(GLUtil::blue);
  glVertex3i(0,0,0) ;
  glVertex3i(0,0,1) ;
  
  glEnd() ;
  glEndList();

}

Axis::~Axis(){
  glDeleteLists( axis_id, 1 );
}

void Axis::display(){
  glCallList( axis_id );
}
