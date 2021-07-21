TEMPLATE	=   lib
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   SelfDefObject
QT          +=  core gui widgets
DEFINES     +=  SELFDEFINEOBJ_API

include(./SelfDefObject.pri)

win32{

  INCLUDEPATH	+=  ./ \
                    ../ \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS +=  \
  -L../../output/bin -lDataProperty \
  -L../../output/bin -lSettings \
  -L../../output/bin -lPythonModule \
 
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
  CONFIG(debug,debug|release):LIBS +=  \
  -L../../output/bin_d -lDataProperty \
  -L../../output/bin_d -lSettings \
  -L../../output/bin_d -lPythonModule \
   
    message("Windows selfDefObj build")
  
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
	-L../../output/bin -lDataProperty \
    -L../../output/bin -lSettings \
	-L../../output/bin -lPythonModule \
	
  message("Linux selfDefObj build")
}

RESOURCES += ../qrc/qianfan.qrc \
             ../qrc/translations.qrc \

TRANSLATIONS     +=  ../qrc/translations/SelfDefObject_zh_CN.ts
