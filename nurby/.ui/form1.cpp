/****************************************************************************
** Form implementation generated from reading ui file 'form1.ui'
**
** Created: Sun Oct 21 21:15:45 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "form1.h"

#include <qvariant.h>   // first for gcc 2.7.2
#include </home/plavoie/project/nurby3/nurby/GLDisplay.h>
#include <qframe.h>
#include <qmime.h>
#include <qdragobject.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include "form1.ui.h"
#include <qimage.h>
#include <qpixmap.h>

static QPixmap uic_load_pixmap_Form1( const QString &name )
{
    const QMimeSource *m = QMimeSourceFactory::defaultFactory()->data( name );
    if ( !m )
	return QPixmap();
    QPixmap pix;
    QImageDrag::decode( m, pix );
    return pix;
}
/* 
 *  Constructs a Form1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */
Form1::Form1( QWidget* parent,  const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    (void)statusBar();
    if ( !name )
	setName( "Form1" );
    resize( 965, 818 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 200, 300 ) );
    setCaption( trUtf8( "Form1" ) );
    setCentralWidget( new QWidget( this, "qt_central_widget" ) );

    QWidget* privateLayoutWidget = new QWidget( centralWidget(), "Layout1" );
    privateLayoutWidget->setGeometry( QRect( 0, 0, 570, 670 ) ); 
    Layout1 = new QVBoxLayout( privateLayoutWidget, 0, 6, "Layout1"); 

    ModelFrame = new QFrame( privateLayoutWidget, "ModelFrame" );
    ModelFrame->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, ModelFrame->sizePolicy().hasHeightForWidth() ) );
    ModelFrame->setMinimumSize( QSize( 200, 200 ) );
    ModelFrame->setFrameShape( QFrame::StyledPanel );
    ModelFrame->setFrameShadow( QFrame::Raised );

    MyCustomWidget1 = new GLDisplay( ModelFrame, "MyCustomWidget1" );
    MyCustomWidget1->setGeometry( QRect( 0, 0, 570, 560 ) ); 
    Layout1->addWidget( ModelFrame );

    InputFrame = new QFrame( privateLayoutWidget, "InputFrame" );
    InputFrame->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, InputFrame->sizePolicy().hasHeightForWidth() ) );
    InputFrame->setMinimumSize( QSize( 0, 100 ) );
    InputFrame->setFrameShape( QFrame::StyledPanel );
    InputFrame->setFrameShadow( QFrame::Raised );
    Layout1->addWidget( InputFrame );

    // actions
    fileNewAction = new QAction( this, "fileNewAction" );
    fileNewAction->setIconSet( QIconSet( uic_load_pixmap_Form1( "filenew" ) ) );
    fileNewAction->setText( trUtf8( "New" ) );
    fileNewAction->setMenuText( trUtf8( "&New" ) );
    fileNewAction->setAccel( 4194382 );
    fileOpenAction = new QAction( this, "fileOpenAction" );
    fileOpenAction->setIconSet( QIconSet( uic_load_pixmap_Form1( "fileopen" ) ) );
    fileOpenAction->setText( trUtf8( "Open" ) );
    fileOpenAction->setMenuText( trUtf8( "&Open..." ) );
    fileOpenAction->setAccel( 4194383 );
    fileSaveAction = new QAction( this, "fileSaveAction" );
    fileSaveAction->setIconSet( QIconSet( uic_load_pixmap_Form1( "filesave" ) ) );
    fileSaveAction->setText( trUtf8( "Save" ) );
    fileSaveAction->setMenuText( trUtf8( "&Save" ) );
    fileSaveAction->setAccel( 4194387 );
    fileSaveAsAction = new QAction( this, "fileSaveAsAction" );
    fileSaveAsAction->setText( trUtf8( "Save As" ) );
    fileSaveAsAction->setMenuText( trUtf8( "Save &As..." ) );
    fileSaveAsAction->setAccel( 0 );
    filePrintAction = new QAction( this, "filePrintAction" );
    filePrintAction->setIconSet( QIconSet( uic_load_pixmap_Form1( "print" ) ) );
    filePrintAction->setText( trUtf8( "Print" ) );
    filePrintAction->setMenuText( trUtf8( "&Print..." ) );
    filePrintAction->setAccel( 4194384 );
    fileExitAction = new QAction( this, "fileExitAction" );
    fileExitAction->setText( trUtf8( "Exit" ) );
    fileExitAction->setMenuText( trUtf8( "E&xit" ) );
    fileExitAction->setAccel( 0 );
    editUndoAction = new QAction( this, "editUndoAction" );
    editUndoAction->setIconSet( QIconSet( uic_load_pixmap_Form1( "undo" ) ) );
    editUndoAction->setText( trUtf8( "Undo" ) );
    editUndoAction->setMenuText( trUtf8( "&Undo" ) );
    editUndoAction->setAccel( 4194394 );
    editRedoAction = new QAction( this, "editRedoAction" );
    editRedoAction->setIconSet( QIconSet( uic_load_pixmap_Form1( "redo" ) ) );
    editRedoAction->setText( trUtf8( "Redo" ) );
    editRedoAction->setMenuText( trUtf8( "&Redo" ) );
    editRedoAction->setAccel( 4194393 );
    editCutAction = new QAction( this, "editCutAction" );
    editCutAction->setIconSet( QIconSet( uic_load_pixmap_Form1( "editcut" ) ) );
    editCutAction->setText( trUtf8( "Cut" ) );
    editCutAction->setMenuText( trUtf8( "&Cut" ) );
    editCutAction->setAccel( 4194392 );
    editCopyAction = new QAction( this, "editCopyAction" );
    editCopyAction->setIconSet( QIconSet( uic_load_pixmap_Form1( "editcopy" ) ) );
    editCopyAction->setText( trUtf8( "Copy" ) );
    editCopyAction->setMenuText( trUtf8( "C&opy" ) );
    editCopyAction->setAccel( 4194371 );
    editPasteAction = new QAction( this, "editPasteAction" );
    editPasteAction->setIconSet( QIconSet( uic_load_pixmap_Form1( "editpaste" ) ) );
    editPasteAction->setText( trUtf8( "Paste" ) );
    editPasteAction->setMenuText( trUtf8( "&Paste" ) );
    editPasteAction->setAccel( 4194390 );
    editFindAction = new QAction( this, "editFindAction" );
    editFindAction->setIconSet( QIconSet( uic_load_pixmap_Form1( "searchfind" ) ) );
    editFindAction->setText( trUtf8( "Find" ) );
    editFindAction->setMenuText( trUtf8( "&Find..." ) );
    editFindAction->setAccel( 4194374 );
    helpContentsAction = new QAction( this, "helpContentsAction" );
    helpContentsAction->setText( trUtf8( "Contents" ) );
    helpContentsAction->setMenuText( trUtf8( "&Contents..." ) );
    helpContentsAction->setAccel( 0 );
    helpIndexAction = new QAction( this, "helpIndexAction" );
    helpIndexAction->setText( trUtf8( "Index" ) );
    helpIndexAction->setMenuText( trUtf8( "&Index..." ) );
    helpIndexAction->setAccel( 0 );
    helpAboutAction = new QAction( this, "helpAboutAction" );
    helpAboutAction->setText( trUtf8( "About" ) );
    helpAboutAction->setMenuText( trUtf8( "&About..." ) );
    helpAboutAction->setAccel( 0 );
    Action = new QAction( this, "Action" );
    Action->setText( trUtf8( "Action" ) );


    // toolbars
    toolBar = new QToolBar( "", this, DockTop ); 

    toolBar->setLabel( trUtf8( "Tools" ) );
    fileNewAction->addTo( toolBar );
    fileOpenAction->addTo( toolBar );
    fileSaveAction->addTo( toolBar );


    // menubar
    menubar = new QMenuBar( this, "menubar" );

    fileMenu = new QPopupMenu( this ); 
    fileNewAction->addTo( fileMenu );
    fileOpenAction->addTo( fileMenu );
    fileSaveAction->addTo( fileMenu );
    fileSaveAsAction->addTo( fileMenu );
    fileMenu->insertSeparator();
    filePrintAction->addTo( fileMenu );
    fileMenu->insertSeparator();
    fileExitAction->addTo( fileMenu );
    menubar->insertItem( trUtf8( "&File" ), fileMenu );

    editMenu = new QPopupMenu( this ); 
    editUndoAction->addTo( editMenu );
    editRedoAction->addTo( editMenu );
    editMenu->insertSeparator();
    editCutAction->addTo( editMenu );
    editCopyAction->addTo( editMenu );
    editPasteAction->addTo( editMenu );
    editMenu->insertSeparator();
    editFindAction->addTo( editMenu );
    menubar->insertItem( trUtf8( "&Edit" ), editMenu );

    helpMenu = new QPopupMenu( this ); 
    helpContentsAction->addTo( helpMenu );
    helpIndexAction->addTo( helpMenu );
    helpMenu->insertSeparator();
    helpAboutAction->addTo( helpMenu );
    menubar->insertItem( trUtf8( "&Help" ), helpMenu );



    // signals and slots connections
    connect( fileNewAction, SIGNAL( activated() ), this, SLOT( fileNew() ) );
    connect( fileOpenAction, SIGNAL( activated() ), this, SLOT( fileOpen() ) );
    connect( fileSaveAction, SIGNAL( activated() ), this, SLOT( fileSave() ) );
    connect( fileSaveAsAction, SIGNAL( activated() ), this, SLOT( fileSaveAs() ) );
    connect( filePrintAction, SIGNAL( activated() ), this, SLOT( filePrint() ) );
    connect( fileExitAction, SIGNAL( activated() ), this, SLOT( fileExit() ) );
    connect( editUndoAction, SIGNAL( activated() ), this, SLOT( editUndo() ) );
    connect( editRedoAction, SIGNAL( activated() ), this, SLOT( editRedo() ) );
    connect( editCutAction, SIGNAL( activated() ), this, SLOT( editCut() ) );
    connect( editCopyAction, SIGNAL( activated() ), this, SLOT( editCopy() ) );
    connect( editPasteAction, SIGNAL( activated() ), this, SLOT( editPaste() ) );
    connect( editFindAction, SIGNAL( activated() ), this, SLOT( editFind() ) );
    connect( helpIndexAction, SIGNAL( activated() ), this, SLOT( helpIndex() ) );
    connect( helpContentsAction, SIGNAL( activated() ), this, SLOT( helpContents() ) );
    connect( helpAboutAction, SIGNAL( activated() ), this, SLOT( helpAbout() ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
Form1::~Form1()
{
    // no need to delete child widgets, Qt does it all for us
}

