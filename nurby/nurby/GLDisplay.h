/****************************************************************************
** $Id:  GlDisplay.h copyright 
**

** This is the main OpenGL display widget
**
****************************************************************************/

#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <qgl.h>


class GLDisplay : public QGLWidget
{
    Q_OBJECT

public:

    GLDisplay( QWidget* parent=0, const char* name = 0);
    ~GLDisplay();

public slots:

    void		setXRotation( int degrees );
    void		setYRotation( int degrees );
    void		setZRotation( int degrees );

protected:

    void		initializeGL();
    void		paintGL();
    void		resizeGL( int w, int h );

    void mouseMoveEvent ( QMouseEvent *) ;
    void mousePressEvent ( QMouseEvent *) ;

    virtual GLuint 	makeAxis();

private:

    GLuint axis_id;
    int mouse_x, mouse_y;
    ButtonState mouse_button;
    GLfloat x_rot, y_rot, z_rot, scale;

};


#endif // GlDdisplay_H
