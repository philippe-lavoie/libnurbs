/****************************************************************************
** Form1 meta object code from reading C++ file 'form1.h'
**
** Created: Sun Oct 21 21:15:52 2001
**      by: The Qt MOC ($Id: moc_form1.cpp,v 1.1.1.1 2001-10-23 03:27:16 philosophil Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../.ui/form1.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Form1::className() const
{
    return "Form1";
}

QMetaObject *Form1::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Form1;

#ifndef QT_NO_TRANSLATION
QString Form1::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Form1", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Form1::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Form1", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Form1::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"fileNew", 0, 0 };
    static const QUMethod slot_1 = {"fileOpen", 0, 0 };
    static const QUMethod slot_2 = {"fileSave", 0, 0 };
    static const QUMethod slot_3 = {"fileSaveAs", 0, 0 };
    static const QUMethod slot_4 = {"filePrint", 0, 0 };
    static const QUMethod slot_5 = {"fileExit", 0, 0 };
    static const QUMethod slot_6 = {"editUndo", 0, 0 };
    static const QUMethod slot_7 = {"editRedo", 0, 0 };
    static const QUMethod slot_8 = {"editCut", 0, 0 };
    static const QUMethod slot_9 = {"editCopy", 0, 0 };
    static const QUMethod slot_10 = {"editPaste", 0, 0 };
    static const QUMethod slot_11 = {"editFind", 0, 0 };
    static const QUMethod slot_12 = {"helpIndex", 0, 0 };
    static const QUMethod slot_13 = {"helpContents", 0, 0 };
    static const QUMethod slot_14 = {"helpAbout", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "fileNew()", &slot_0, QMetaData::Public },
	{ "fileOpen()", &slot_1, QMetaData::Public },
	{ "fileSave()", &slot_2, QMetaData::Public },
	{ "fileSaveAs()", &slot_3, QMetaData::Public },
	{ "filePrint()", &slot_4, QMetaData::Public },
	{ "fileExit()", &slot_5, QMetaData::Public },
	{ "editUndo()", &slot_6, QMetaData::Public },
	{ "editRedo()", &slot_7, QMetaData::Public },
	{ "editCut()", &slot_8, QMetaData::Public },
	{ "editCopy()", &slot_9, QMetaData::Public },
	{ "editPaste()", &slot_10, QMetaData::Public },
	{ "editFind()", &slot_11, QMetaData::Public },
	{ "helpIndex()", &slot_12, QMetaData::Public },
	{ "helpContents()", &slot_13, QMetaData::Public },
	{ "helpAbout()", &slot_14, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Form1", parentObject,
	slot_tbl, 15,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Form1.setMetaObject( metaObj );
    return metaObj;
}

void* Form1::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Form1" ) ) return (Form1*)this;
    return QMainWindow::qt_cast( clname );
}

bool Form1::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: fileNew(); break;
    case 1: fileOpen(); break;
    case 2: fileSave(); break;
    case 3: fileSaveAs(); break;
    case 4: filePrint(); break;
    case 5: fileExit(); break;
    case 6: editUndo(); break;
    case 7: editRedo(); break;
    case 8: editCut(); break;
    case 9: editCopy(); break;
    case 10: editPaste(); break;
    case 11: editFind(); break;
    case 12: helpIndex(); break;
    case 13: helpContents(); break;
    case 14: helpAbout(); break;
    default:
	return QMainWindow::qt_invoke(_id,_o);
    }
    return TRUE;
}

bool Form1::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Form1::qt_property( int _id, int _f, QVariant* _v)
{
    return QMainWindow::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
