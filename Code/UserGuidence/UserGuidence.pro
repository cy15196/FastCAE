TEMPLATE	=   lib
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   UserGuidence
QT          +=  core gui widgets network 
DEFINES     +=  USERGUIDENCE_API

include(UserGuidence.pri)

win32{

  INCLUDEPATH	+=  ./ \
                    ../ \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS	+=	\
    -L../../output/bin -lSettings \
	-L../../output/bin -lPythonModule \
	
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
  CONFIG(debug,debug|release):LIBS +=  \
  -L../../output/bin_d -lSettings \
  -L../../output/bin_d -lPythonModule \

  message("Windows USER GUIDENCE build")
                                               
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
  -L../../output/bin -lSettings \
  -L../../output/bin -lPythonModule \
	
  message("Linux USER GUIDENCE build")
}

RESOURCES += ../qrc/qianfan.qrc \

TRANSLATIONS += ../qrc/translations/UserGuidence_zh_CN.ts
