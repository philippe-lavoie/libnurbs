#include "GLDisplay.h"


GLDisplay::GLDisplay( QWidget* parent, const char* name )
    : QGLWidget( parent, name )
{
    setFocusPolicy(QWidget::StrongFocus) ;

    x_rot=y_rot=z_rot=0;
}

/*!
  Release allocated resources
*/

GLDisplay::~GLDisplay()
{
  delete axis;
  makeCurrent();
}


/*!
  Paint the box. The actual openGL commands for drawing the box are
  performed here.
*/

void GLDisplay::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glLoadIdentity();
    glTranslatef( 0.0, 0.0, -10.0 );

    //    glScalef( scale, scale, scale );

    glRotatef( x_rot, 1.0, 0.0, 0.0 ); 
    glRotatef( y_rot, 0.0, 1.0, 0.0 ); 
    glRotatef( z_rot, 0.0, 0.0, 1.0 );
    
    axis->display();
}


/*!
  Set up the OpenGL rendering state, and define display list
*/

void GLDisplay::initializeGL()
{
    qglClearColor( black ); 		// Let OpenGL clear to black
    glShadeModel( GL_FLAT );
    axis = new Axis();
}



/*!
  Set up the OpenGL view port, matrix mode, etc.
*/

void GLDisplay::resizeGL( int w, int h )
{
    glViewport( 0, 0, (GLint)w, (GLint)h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 15.0 );
    glMatrixMode( GL_MODELVIEW );
}



void GLDisplay::mousePressEvent ( QMouseEvent *mouse) {
  mouse_x = mouse->x() ;
  mouse_y = mouse->y() ;
  mouse_button = mouse->button() ;
}

void GLDisplay::mouseMoveEvent ( QMouseEvent *mouse) {
  int dX = mouse->x() - mouse_x ;
  int dY = mouse_y - mouse->y() ;
  mouse_x = mouse->x() ;
  mouse_y = mouse->y() ;
  mouse_button = mouse->state() ;

  x_rot += (GLfloat(dX) / GLfloat(width())) * (GLfloat)180;
  y_rot += (GLfloat(dY) / GLfloat(height())) * (GLfloat)180;

  std::cerr << "Moving..." << x_rot << "," << y_rot << "," << z_rot << endl;

  updateGL();
}


/*!
  Set the rotation angle of the object to \e degrees around the X axis.
*/

void GLDisplay::setXRotation( int degrees )
{
    x_rot = (GLfloat)(degrees % 360);
    updateGL();
}


/*!
  Set the rotation angle of the object to \e degrees around the Y axis.
*/

void GLDisplay::setYRotation( int degrees )
{
    y_rot = (GLfloat)(degrees % 360);
    updateGL();
}


/*!
  Set the rotation angle of the object to \e degrees around the Z axis.
*/

void GLDisplay::setZRotation( int degrees )
{
    z_rot = (GLfloat)(degrees % 360);
    updateGL();
}
