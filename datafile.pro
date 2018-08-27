TEMPLATE = lib
CONFIG += qt warn_on thread exceptions all
TARGET = datafile
DEFINES += DATAFILE_DLL
DESTDIR = ../lib

debug {
   CONFIG -= release
  # win32: LIBS += $(ACE_ROOT)/ace/aced.lib
}

release {
   CONFIG -= debug
  # win32: LIBS += $(ACE_ROOT)/ace/ace.lib
   
}


INCLUDEPATH += \
                ../include
				
HEADERS += \
           data.h  \
    datafilehandle.h \
    datafile.h
		  		

SOURCES +=\
           data.cpp   \
           datafilehandle.cpp\
           datafile.cpp

      
	
FORMS	+= \

LIBS += -L../lib -lH5ConfigHelp
unix{
    UI_DIR = temp/ui
    MOC_DIR = tem/moc
    OBJECTS_DIR	= temp/obj
    LIBS += \
		
}	  

win32{
    UI_DIR = temp/ui
    MOC_DIR = temp/moc
    OBJECTS_DIR	= temp/obj
    LIBS += \
} 

#QT += qt3support
