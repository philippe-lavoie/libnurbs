#include <qapplication.h>
#include "GLDisplay.h"

int main( int argc, char ** argv )
{
  QApplication a( argc, argv );
  GLDisplay *gl_display = new GLDisplay;
  gl_display->show();
  return a.exec();
}

