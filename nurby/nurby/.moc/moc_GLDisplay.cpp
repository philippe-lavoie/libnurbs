/****************************************************************************
** GLDisplay meta object code from reading C++ file 'GLDisplay.h'
**
** Created: Sun Oct 21 22:18:20 2001
**      by: The Qt MOC ($Id: moc_GLDisplay.cpp,v 1.1.1.1 2001-10-23 03:27:14 philosophil Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../GLDisplay.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GLDisplay::className() const
{
    return "GLDisplay";
}

QMetaObject *GLDisplay::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GLDisplay;

#ifndef QT_NO_TRANSLATION
QString GLDisplay::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLDisplay", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GLDisplay::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLDisplay", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GLDisplay::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "degrees", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"setXRotation", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "degrees", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"setYRotation", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "degrees", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"setZRotation", 1, param_slot_2 };
    static const QMetaData slot_tbl[] = {
	{ "setXRotation(int)", &slot_0, QMetaData::Public },
	{ "setYRotation(int)", &slot_1, QMetaData::Public },
	{ "setZRotation(int)", &slot_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"GLDisplay", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GLDisplay.setMetaObject( metaObj );
    return metaObj;
}

void* GLDisplay::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GLDisplay" ) ) return (GLDisplay*)this;
    return QGLWidget::qt_cast( clname );
}

bool GLDisplay::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setXRotation(static_QUType_int.get(_o+1)); break;
    case 1: setYRotation(static_QUType_int.get(_o+1)); break;
    case 2: setZRotation(static_QUType_int.get(_o+1)); break;
    default:
	return QGLWidget::qt_invoke(_id,_o);
    }
    return TRUE;
}

bool GLDisplay::qt_emit( int _id, QUObject* _o )
{
    return QGLWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool GLDisplay::qt_property( int _id, int _f, QVariant* _v)
{
    return QGLWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
