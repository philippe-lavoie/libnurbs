#ifndef NURBY_AXIS_H
#define NURBY_AXIS_H

#include <GL/gl.h>

class Axis {
 public:
  Axis();
  ~Axis();

  void display();

 protected:
  GLuint axis_id;
};

#endif
