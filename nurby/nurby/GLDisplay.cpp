#include "GLDisplay.h"

static GLfloat redGL[4] = {1.0, 0.0, 0.0, 1.0 };
static GLfloat greenGL[4] = {0.0, 1.0, 0.0, 1.0 };
static GLfloat blueGL[4] = {0.0, 0.0, 1.0, 1.0 };
static GLfloat blackGL[4] = {0.0, 0.0, 0.0, 1.0 };

GLDisplay::GLDisplay( QWidget* parent, const char* name )
    : QGLWidget( parent, name )
{
    axis_id = 0;
    x_rot=y_rot=z_rot=0;
    setFocusPolicy(QWidget::StrongFocus) ;
}

/*!
  Release allocated resources
*/

GLDisplay::~GLDisplay()
{
    makeCurrent();
    glDeleteLists( axis_id, 1 );
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
    
    glCallList( axis_id );
}


/*!
  Set up the OpenGL rendering state, and define display list
*/

void GLDisplay::initializeGL()
{
    qglClearColor( black ); 		// Let OpenGL clear to black
    axis_id = makeAxis();		// Generate an OpenGL display list
    glShadeModel( GL_FLAT );
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


/*!
  Generate an OpenGL display list for the object to be shown, i.e. the box
*/

GLuint GLDisplay::makeAxis()
{	
    GLuint list;

    list = glGenLists( 1 );

    glNewList( list, GL_COMPILE );

    //qglColor( white );		      // Shorthand for glColor3f or glIndex

    glBegin(GL_LINES);
    
    glLineWidth( 2.0 );
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,blackGL) ;
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,redGL) ;
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,redGL) ;

    //glColor3f(1,0,0) ;
    qglColor(red);

    glVertex3i(0,0,0) ;
    glVertex3i(1,0,0) ;
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,greenGL) ;
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,greenGL) ;
    
    qglColor(green);
    //glColor3f(0,1,0) ;

    glVertex3i(0,0,0) ;
    glVertex3i(0,1,0) ;
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,blueGL) ;
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,blueGL) ;

    //glColor3f(0,0,1) ;
    qglColor(blue);
    glVertex3i(0,0,0) ;
    glVertex3i(0,0,1) ;

    glEnd() ;
    glEndList();


    return list;
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
