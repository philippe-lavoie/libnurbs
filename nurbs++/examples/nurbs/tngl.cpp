// the code was adapted from test/glut/bigtest.c from the glut distribution
// see that file for more details.
#include <nurbsGL.hh>

#ifdef WITH_OPENGL

#include <GL/glut.h>
#include <stdio.h>

using namespace PLib ; 

#define Boolean GLboolean 
#define TRUE    GL_TRUE
#define FALSE   GL_FALSE

Boolean timerOn = FALSE;  /* timer active  */
//Boolean animation = FALSE;  /* idle func animation on  */
int animation = 0 ;
Boolean debug = FALSE;  /* dump all events  */
Boolean showKeys = FALSE;  /* dump key events  */
Boolean demoMode = FALSE;  /* run automatic demo  */
Boolean backdrop = FALSE;  /* use backdrop polygon  */
Boolean passive = FALSE;  /* report passive motions  */
Boolean leftDown = FALSE;  /* left button down ?  */
Boolean middleDown = FALSE;  /* middle button down ?  */

int editMode = 0 ; // are we editing the curve/surface ?

float rotationAngle = 0.0;      /* global rotation angle  */

#define PR     if(debug)printf

enum {
  RGBA, INDEX, SINGLE, DOUBLEBUFFER, DEPTH, ACCUM, ALPHA, STENCIL, MULTISAMPLE,
  STEREO, MODES
};
/*int glutMode[] =
{GLUT_RGBA, GLUT_INDEX, GLUT_SINGLE, GLUT_DOUBLE, GLUT_DEPTH,
  GLUT_ACCUM, GLUT_ALPHA, GLUT_STENCIL, GLUT_MULTISAMPLE, GLUT_STEREO};
int modes[MODES] =
{0}; */
GLboolean menuButton[3] =
{0, 0, 1};
enum {
  MOUSEBUTTON, MOUSEMOTION, APPLY, RESET
};

int lineWidth = 1;      /* line width  */

int shapeId = 1 ;
int winId = 0 ;

float u = 0.5 ;
float v = 0.5 ;

void trackBall(int mode, int button, int state, int x, int y);
void drawScene(void);

void
updateAll(void)
{
  if (lineWidth < 1)
    lineWidth = 1;
  glutSetWindow(winId);
  glutPostRedisplay();
}

NurbsCurveGL c ;
NurbsSurfaceGL s ;

void
gfxInit(int index)
{
  GLfloat grey10[] =
  {0.10, 0.10, 0.10, 1.0};
  GLfloat grey20[] =
  {0.2, 0.2, 0.2, 1.0};
  GLfloat black[] =
  {0.0, 0.0, 0.0, 0.0};
  GLfloat diffuse0[] =
  {1.0, 0.0, 0.0, 1.0};
  GLfloat diffuse1[] =
  {0.0, 1.0, 0.0, 1.0};
  GLfloat diffuse2[] =
  {1.0, 1.0, 0.0, 1.0};
  GLfloat diffuse3[] =
  {0.0, 1.0, 1.0, 1.0};
  GLfloat diffuse4[] =
  {1.0, 0.0, 1.0, 1.0};

#define XX  3
#define YY  3
#define ZZ  -2.5

  float vertex[][3] =
  {
    {-XX, -YY, ZZ},
    {+XX, -YY, ZZ},
    {+XX, +YY, ZZ},
    {-XX, +YY, ZZ}
  };

/* warning: This func mixes RGBA and CMAP calls in an ugly
   fashion */

  glutSetWindow(winId);
  if(glIsList(0))
      glDeleteLists(0,2) ;
  glNewList(1,GL_COMPILE);


  //  glutWireSphere(1.5, 10, 10);

  GLUnurbsObj *theNurb;

  theNurb = gluNewNurbsRenderer();
  gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
  gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);

  c.ObjectGL::read("tngl.nc") ;

  MatrixRT<float> M ;

  M.scale(0.01,0.01,0.01) ;
  c.transform(M) ;

  c.setNurbsRenderer(theNurb) ;
  
  c.setObjectColor(Color(200,100,255),Color(255,255,255),Color(255,255,255)) ;
  c.glObject() ;
    

  glEndList() ;

  glNewList(2,GL_COMPILE) ;

  s.ObjectGL::read("tngl.ns") ;

  GLUnurbsObj *theNurb2;

  theNurb2 = gluNewNurbsRenderer();
  gluNurbsProperty(theNurb2, GLU_SAMPLING_TOLERANCE, 25.0);
  gluNurbsProperty(theNurb2, GLU_DISPLAY_MODE, GLU_OUTLINE_PATCH);

  s.setNurbsRenderer(theNurb2) ;
  s.setObjectColor(Color(100,200,255),Color(255,255,255),Color(255,255,255)) ;
  s.glObject() ;

  glEndList() ;


  glNewList(3,GL_COMPILE) ;

  NurbsDisplayMode = NURBS_DISPLAY_TESSELATION ;
  theNurb2 = gluNewNurbsRenderer();
  gluNurbsProperty(theNurb2, GLU_SAMPLING_TOLERANCE, 25.0);
  gluNurbsProperty(theNurb2, GLU_DISPLAY_MODE, GLU_OUTLINE_PATCH);

  s.setNurbsRenderer(theNurb2) ;
  s.setObjectColor(Color(100,200,255),Color(255,255,255),Color(255,255,255)) ;
  s.glObject() ;

  glEndList() ;


  glutSetWindow(winId);  /* hack - redefineShapes
                                   changes glut win */

/* Shaded backdrop square (RGB or CMAP) */

  glNewList(100, GL_COMPILE);
  glPushAttrib(GL_LIGHTING);
  glDisable(GL_LIGHTING);
  glBegin(GL_POLYGON);

  glColor4fv(black);
  glIndexi(0);
  glVertex3fv(vertex[0]);

  glColor4fv(grey10);
  glIndexi(3);
  glVertex3fv(vertex[1]);

  glColor4fv(grey20);
  glIndexi(4);
  glVertex3fv(vertex[2]);

  glColor4fv(grey10);
  glIndexi(7);
  glVertex3fv(vertex[3]);

  glEnd();
  glPopAttrib();
  glIndexi(9);
  glEndList();

/* Set proj+view */

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, 1.0, -200.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.);
  glTranslatef(0.0, 0.0, -1.0);

/* Set basic material, lighting for RGB windows */

  //glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse0);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glClearColor(0.1, 0.1, 0.1, 1.0);
}

void
keyFunc(unsigned char key, int x, int y)
{
  int i, ii;

  //if (debug || showKeys)
  //    printf("Ascii key '%c' 0x%02x\n", key, key);

  switch (key) {
  case 0x1b:
    exit(0);
    break;
    
  case 'a':
    animation != animation ;
    PR("animation = %d",animation) ;
    drawScene() ;
    break ;

  case 's':
    // changing shape
    // good shapes are 1 and 2 (for now)
    ++shapeId;
    shapeId = shapeId%4 ;
    if(!shapeId) shapeId = 1 ;
    drawScene() ;
    break ;

  case 'e':
    // change mode
    if(editMode) editMode = 0 ;
    else editMode = 1 ;
    drawScene() ;
    break ;

  case 'q':
    //killWindow(idToIndex(glutGetWindow()));
    exit(0) ;
    break;

  case 'r':
    trackBall(RESET, 0, 0, 0, 0);
    drawScene() ;
    break;

  case 'd':
    shapeId = ( shapeId == 2) ? 3 : 2 ;
    drawScene();
    break ; 
  case 'D':
    debug = !debug;
    break;

  case 'l':
    lineWidth += 1;
    updateAll();
    break;

  case 'L':
    lineWidth -= 1;
    if (lineWidth < 1)
      lineWidth = 1;
    updateAll();
    break;

  default:
    ;
  }
}

/* specialFunc - Special keys callback (F keys, cursor keys
   etc. */

/* ARGSUSED1 */
/*
void
specialFunc(int key, int x, int y)
{
  if (debug || showKeys)
    printf("Special key %d\n", key);

  switch (key) {
  case GLUT_KEY_PAGE_DOWN:
    scrollLine += 10;
    updateHelp();
    updateText();
    break;

  case GLUT_KEY_PAGE_UP:
    scrollLine -= 10;
    updateHelp();
    updateText();
    break;

  case GLUT_KEY_DOWN:
    scrollLine += 1;
    updateHelp();
    updateText();
    break;

  case GLUT_KEY_UP:
    scrollLine -= 1;
    updateHelp();
    updateText();
    break;

  case GLUT_KEY_HOME:
    scrollLine = 0;
    updateHelp();
    updateText();
    break;

  case GLUT_KEY_END:
    scrollLine = 9999;
    updateHelp();
    updateText();
    break;

  case GLUT_KEY_RIGHT:
    scrollCol -= 1;
    updateHelp();
    updateText();
    break;

  case GLUT_KEY_LEFT:
    scrollCol += 1;
    updateHelp();
    updateText();
    break;
  }
}
*/

/* trackBall - A simple trackball (not with proper rotations). */

/** A simple trackball with spin = left button
                           pan  = middle button
                           zoom = left + middle
   Doesn't have proper trackball rotation, ie axes which remain fixed in
   the scene. We should use the trackball code from 4Dgifts. */

#define STARTROTATE(x, y)     \
{                             \
    startMX = x;              \
    startMY = y;              \
}

#define STOPROTATE(x, y)      \
{                             \
    steadyXangle = varXangle; \
    steadyYangle = varYangle; \
}

#define STARTPAN(x, y)        \
{                             \
    startMX = x;              \
    startMY = y;              \
}

#define STOPPAN(x, y)         \
{                             \
    steadyX = varX;           \
    steadyY = varY;           \
}

#define STARTZOOM(x, y)       \
{                             \
    startMX = x;              \
    startMY = y;              \
}

#define STOPZOOM(x, y)        \
{                             \
    steadyZ = varZ;           \
}

void
trackBall(int mode, int button, int state, int x, int y)
{
  static int startMX = 0, startMY = 0;  /* initial mouse pos  */
  static int deltaMX = 0, deltaMY = 0;  /* initial mouse pos  */
  static int startMU = 0, startMV = 0;  /* initial mouse pos  */
  static int deltaMU = 0, deltaMV = 0;  /* initial mouse pos  */
  static float steadyXangle = 0.0, steadyYangle = 0.0;
  static float varXangle = 0.0, varYangle = 0.0;
  static float steadyX = 0.0, steadyY = 0.0, steadyZ = 0.0;
  static float varX = 0.0, varY = 0.0, varZ = 0.0;

  if(editMode){
    switch(mode){
    case RESET:
      u = v = 0.5 ;
      break;
      
  case APPLY:

    if (leftDown && !middleDown) {
      glTranslatef(steadyX, steadyY, steadyZ);
      glRotatef(varXangle, 0, 1, 0);
      glRotatef(varYangle, 1, 0, 0);
    }
    /* Middle button pan  */

    else if (middleDown && !leftDown) {
      glTranslatef(varX, varY, steadyZ);
      glRotatef(steadyXangle, 0, 1, 0);
      glRotatef(steadyYangle, 1, 0, 0);
    }
    /* Left + middle zoom.  */

    else if (leftDown && middleDown) {
      glTranslatef(steadyX, steadyY, varZ);
      glRotatef(steadyXangle, 0, 1, 0);
      glRotatef(steadyYangle, 1, 0, 0);
    }
    /* Nothing down.  */

    else {
      glTranslatef(steadyX, steadyY, steadyZ);
      glRotatef(steadyXangle, 0, 1, 0);
      glRotatef(steadyYangle, 1, 0, 0);
    }
    break;

    case MOUSEBUTTON:

      if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !middleDown) {
	startMU = x ;
	startMV = y ;
	leftDown = TRUE ;
      } else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN &&
		 !leftDown) {
	startMU = x ;
	startMV = y ;
      } 
      else{
	leftDown = FALSE ;
	middleDown = FALSE ;
      }
      break;

    case MOUSEMOTION:
      
      deltaMU = x - startMU ;
      deltaMV = startMV - y;
      startMU = x ;
      startMV = y ;
      
      if (leftDown) {
	u += deltaMU/100.0 ;
	v += deltaMV/100.0 ;
	if(shapeId==1)
	  u+=deltaMV/100.0 ;
      } else {
	u += deltaMU/1000.0 ;
	v += deltaMV/1000.0 ;
	if(shapeId==1)
	  u+=deltaMV/1000.0 ;
      }
      if(u<0.0) u = 0.0 ;
      if(v<0.0) v = 0.0 ;
      if(u>1.0) u = 1.0 ;
      if(v>1.0) v = 1.0 ;
      break;
    }
  }
  else
  switch (mode) {

  case RESET:
    steadyXangle = steadyYangle = steadyX = steadyY = steadyZ = 0.0;
    break;

  case MOUSEBUTTON:

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !middleDown) {
      STARTROTATE(x, y);
      leftDown = TRUE;
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
      middleDown) {
      STOPPAN(x, y);
      STARTZOOM(x, y);
      leftDown = TRUE;
    } else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN &&
      !leftDown) {
      STARTPAN(x, y);
      middleDown = TRUE;
    } else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN &&
      leftDown) {
      STOPROTATE(x, y);
      STARTZOOM(x, y);
      middleDown = TRUE;
    } else if (state == GLUT_UP && button == GLUT_LEFT_BUTTON && !middleDown) {
      STOPROTATE(x, y);
      leftDown = FALSE;
    } else if (state == GLUT_UP && button == GLUT_LEFT_BUTTON && middleDown) {
      STOPZOOM(x, y);
      STARTROTATE(x, y);
      leftDown = FALSE;
    } else if (state == GLUT_UP && button == GLUT_MIDDLE_BUTTON && !leftDown) {
      STOPPAN(x, y);
      middleDown = FALSE;
    } else if (state == GLUT_UP && button == GLUT_MIDDLE_BUTTON && leftDown) {
      STOPZOOM(x, y);
      STARTROTATE(x, y);
      middleDown = FALSE;
    }
    break;

  case APPLY:

    if (leftDown && !middleDown) {
      glTranslatef(steadyX, steadyY, steadyZ);
      glRotatef(varXangle, 0, 1, 0);
      glRotatef(varYangle, 1, 0, 0);
    }
    /* Middle button pan  */

    else if (middleDown && !leftDown) {
      glTranslatef(varX, varY, steadyZ);
      glRotatef(steadyXangle, 0, 1, 0);
      glRotatef(steadyYangle, 1, 0, 0);
    }
    /* Left + middle zoom.  */

    else if (leftDown && middleDown) {
      glTranslatef(steadyX, steadyY, varZ);
      glRotatef(steadyXangle, 0, 1, 0);
      glRotatef(steadyYangle, 1, 0, 0);
    }
    /* Nothing down.  */

    else {
      glTranslatef(steadyX, steadyY, steadyZ);
      glRotatef(steadyXangle, 0, 1, 0);
      glRotatef(steadyYangle, 1, 0, 0);
    }
    break;

  case MOUSEMOTION:

    deltaMX = x - startMX;
    deltaMY = startMY - y;

    if (leftDown && !middleDown) {
      varXangle = steadyXangle + deltaMX;
      varYangle = steadyYangle + deltaMY;
    } else if (middleDown && !leftDown) {
      varX = steadyX + deltaMX / 100.0;
      varY = steadyY + deltaMY / 100.0;
    } else if (leftDown && middleDown) {
      varZ = steadyZ - deltaMY / 50.0;
    }
    break;
  }

}

/* mouseFunc - Mouse button callback */

void
mouseFunc(int button, int state, int x, int y)
{
  PR("Mouse button %d, state %d, at pos %d, %d\n", button, state, x, y);

  trackBall(MOUSEBUTTON, button, state, x, y);
}

/* motionFunc - Mouse movement (with a button down) callback */

void
motionFunc(int x, int y)
{
  PR("Mouse motion at %d, %d\n", x, y);

  trackBall(MOUSEMOTION, 0, 0, x, y);

  glutPostRedisplay();
}

/* passiveMotionFunc - Mouse movement (with no button down)
   callback */

void
passiveMotionFunc(int x, int y)
{
  printf("Mouse motion at %d, %y\n", x, y);
}

/* entryFunc - Window entry event callback */

void
entryFunc(int state)
{
  int winId = glutGetWindow();
  PR("Entry event: window id %d (index %d), state %d \n", winId, 0 , state);
}

void
idleFunc(void)
{
  int i;

  if (!leftDown && !middleDown)
    rotationAngle += 1;

  glutSetWindow(winId);
  glutPostRedisplay();
}

void
drawScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* printf("drawScene for index %d, id %d\n", winIndex,
     glutGetWindow());  */

  glPushMatrix();
  glLineWidth(lineWidth);
  if (backdrop)
    glCallList(100);
  
  /* Left button spinning  */

  trackBall(APPLY, 0, 0, 0, 0);
  /* Apply continuous spinning  */

  glRotatef(rotationAngle, 0, 1, 0);

  glCallList(shapeId) ;
  if(editMode){
    switch(shapeId){
    case 1: // the curve
      c.point(u,v,5,Color(255,0,0)) ;
      break ;
    default: // the surface
      s.point(u,v,5,Color(255,0,0)) ;
    }
  }

  glPopMatrix();

  glutSwapBuffers();

  if(animation)
    glutIdleFunc(idleFunc);
  else
    glutIdleFunc(NULL);
  
}


/*void
visible(int state)
{

  if (animation)
    glutIdleFunc(idleFunc);
  else
    glutIdleFunc(NULL);
}
*/
void
reshapeFunc(int width, int height)
{
  int winId;
  float aspect;

  winId = glutGetWindow();
  PR("reshape callback for window id %d \n", winId);

  glViewport(0, 0, width, height);
  aspect = (float) width / height;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, aspect, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
}

void
addCallbacks(void)
{
  glutDisplayFunc(drawScene);
  //glutVisibilityFunc(visible);
  glutReshapeFunc(reshapeFunc);
  glutKeyboardFunc(keyFunc);
  //  glutSpecialFunc(specialFunc);
  glutMouseFunc(mouseFunc);
  glutMotionFunc(motionFunc);

}


int main(int argc, char **argv){
  glutInit(&argc, argv);

  /* Set initial display mode */

  int displayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;
  glutInitDisplayMode(displayMode);

  if (!glutGet(GLUT_DISPLAY_MODE_POSSIBLE)){
    Error err("testing OpenGL for NURBS");
    err << "This display mode is not supported\n";
    err.warning() ;
  }



  int index = 0 ;

  glutInitWindowPosition(50, 150) ;
  glutInitWindowSize(400,400);
  winId = glutCreateWindow("Testing OpenGL support");
  //PR("Window %d id = %d \n", index, winId);
  gfxInit(index);

  addCallbacks();
  
  char str[99] ;

  sprintf(str, "window %d (RGB)", index);
  glutSetWindowTitle(str);
  sprintf(str, "icon %d", index);
  glutSetIconTitle(str);
  //glutSetMenu(menu1);
  //glutAttachMenu(GLUT_RIGHT_BUTTON);
 
  glutIdleFunc(idleFunc);
  
  glutMainLoop();

  return 0 ;
}

#else

#include <iostream.h>

int main(){
  cout << "This test requires OpenGL (or Mesa) support.\n" ;
  return 0 ;
}

#endif
