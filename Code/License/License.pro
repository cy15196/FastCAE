TEMPLATE 	= 	lib
TARGET 		= 	License
QT          +=  core gui widgets xml
CONFIG		+=   c++11 
CONFIG		+=  qt
DEFINES 	+=  LICENSE_LIB

include(License.pri)

QMAKE_CXXFLAGS_RELEASE -= -Zc:strictStrings

win32{
  INCLUDEPATH	+=  ./ \
                    ../ \
					../Setting/ \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS			  +=  \
  -L../../output/bin -lSettings \

  
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj
  CONFIG(debug,debug|release):LIBS			+=  \
  -L../../output/bin_d -lSettings \
	
  message("Windows License build")
                                               
}

unix{
  INCLUDEPATH	+=   ./ \
		             ../ \
					 
  CONFIG          += plugin
  DESTDIR         = ../../output/bin
  MOC_DIR         = ./release/moc
  UI_DIR          = ./release/qui
  RCC_DIR         = ./release/rcc
  OBJECTS_DIR     = ./release/obj
  LIBS += \
   -L../../output/bin -lMainWindow \

	
  message("Linux License build")
}