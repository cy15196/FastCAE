TEMPLATE	=   lib
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   ModuleBase
QT          +=  core widgets gui xml printsupport
DEFINES     +=  MODULEBASE_API

include(./moduleBase.pri)
include(./../vtk.pri)
include(./../occ.pri)

win32{

  INCLUDEPATH	+=  ./ \
                    ../ \
					../SelfDefObject/ \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS +=  \
  -L../../output/bin -lMeshData \
  -L../../output/bin -lGeometry \
 # -L../../output/bin -lGraphicsAnalyse \
  -L../../output/bin -lModelData \
  -L../../output/bin -lDataProperty \
  -L../../output/bin -lSelfDefObject \
  -L../../output/bin -lSettings \
  -L../../output/bin -lPythonModule \
#  -L../../output/bin -lXMaterial \
 
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
  CONFIG(debug,debug|release):LIBS +=  \
  -L../../output/bin_d -lMeshData \
  -L../../output/bin_d -lGeometry \
 # -L../../output/bin_d -lGraphicsAnalyse \
  -L../../output/bin_d -lModelData \
  -L../../output/bin_d -lDataProperty \
  -L../../output/bin_d -lSelfDefObject \
  -L../../output/bin_d -lSettings \
  -L../../output/bin_d -lPythonModule \
#  -L../../output/bin_d -lXMaterial \
#  -L../../output/bin_d -lMainWindow \
  
  message("Windows moduleBase build")
  
}


unix{
    INCLUDEPATH	+=   ./ \
		      ../ \
			  ../SelfDefObject/ \
					 
  CONFIG          += plugin
  DESTDIR         = ../../output/bin
  MOC_DIR         = ./release/moc
  UI_DIR          = ./release/qui
  RCC_DIR         = ./release/rcc
  OBJECTS_DIR     = ./release/obj
  LIBS += \
  -L../../output/bin -lMeshData \
  -L../../output/bin -lGeometry \
#  -L../../output/bin -lGraphicsAnalyse \
  -L../../output/bin -lModelData \
  -L../../output/bin -lDataProperty \
  -L../../output/bin -lSelfDefObject \
  -L../../output/bin -lSettings \
  -L../../output/bin -lPythonModule \
#  -L../../output/bin -lXMaterial \
	
  message("Linux moduleBase build")
  
}

RESOURCES += ../qrc/qianfan.qrc
RESOURCES += ../qrc/translations.qrc
#RESOURCES += ../qrc/config.qrc

TRANSLATIONS     += ../qrc/translations/ModuleBase_zh_CN.ts

