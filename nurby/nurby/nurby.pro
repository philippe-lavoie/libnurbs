SOURCES	+= GLDisplay.cpp nurby.cpp 
HEADERS	+= GLDisplay.h 
unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}
FORMS	= form1.ui 
IMAGES	= images/filenew images/fileopen images/filesave images/print images/undo images/redo images/editcut images/editcopy images/editpaste images/searchfind 
TEMPLATE	=app
CONFIG	+= qt warn_on release
DBFILE	= nurby.db
LANGUAGE	= C++
