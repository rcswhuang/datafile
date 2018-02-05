TEMPLATE = lib
CONFIG += qt warn_on thread exceptions all
TARGET = datafile
DEFINES += DATAFILE_DLL
DESTDIR = $$(WF_ROOT)\lib\debug

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


unix{
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR	= .obj

    DEFINES += \

    LIBPATH +=	\

    LIBS += \
		
}	  

win32{
    UI_DIR = temp/ui
    MOC_DIR = temp/moc
    OBJECTS_DIR	= temp/obj

    DEFINES += \
    LIBS += \
} 

#QT += qt3support
