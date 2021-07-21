TEMPLATE	=   lib
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   ProjectTree
QT          +=  core gui widgets xml
DEFINES     +=  PROJECTTREE_API

include(./projectTree.pri)
include(./../vtk.pri)

win32{

  INCLUDEPATH	+=  ./ \
                    ../ \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS +=  \
    -L../../output/bin -lModuleBase \
	-L../../output/bin -lModelData \
	-L../../output/bin -lDataProperty \
	-L../../output/bin -lMeshData \
	-L../../output/bin -lGeometry \
	-L../../output/bin -lSelfDefObject \
	-L../../output/bin -lBCBase \
	-L../../output/bin -lParaClassFactory \
	-L../../output/bin -lSettings \
	-L../../output/bin -lConfigOptions \
	-L../../output/bin -lMaterial \
	-L../../output/bin -lPostWidgets \
	-L../../output/bin -lPythonModule \
 
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
  CONFIG(debug,debug|release):LIBS +=  \
   -L../../output/bin_d -lModuleBase \
   -L../../output/bin_d -lModelData \
   -L../../output/bin_d -lDataProperty \
   -L../../output/bin_d -lMeshData \
   -L../../output/bin_d -lGeometry \
   -L../../output/bin_d -lSelfDefObject \
   -L../../output/bin_d -lBCBase \
   -L../../output/bin_d -lParaClassFactory \
   -L../../output/bin_d -lSettings \
   -L../../output/bin_d -lConfigOptions \
   -L../../output/bin_d -lMaterial \
   -L../../output/bin_d -lPostWidgets \
   -L../../output/bin_d -lPythonModule \
  
  message("Windows projectTreeBase build")
  
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
	-L../../output/bin -lModuleBase \
	-L../../output/bin -lModelData \
	-L../../output/bin -lDataProperty \
	-L../../output/bin -lMeshData \
	-L../../output/bin -lGeometry \
	-L../../output/bin -lSelfDefObject \
	-L../../output/bin -lBCBase \
	-L../../output/bin -lParaClassFactory \
	-L../../output/bin -lSettings \
	-L../../output/bin -lConfigOptions \
	-L../../output/bin -lMaterial \
	-L../../output/bin -lPythonModule \
	
  message("Linux projectTreeBase build")
  
}

RESOURCES += ../qrc/qianfan.qrc
#RESOURCES += ../qrc/config.qrc

TRANSLATIONS     += ../qrc/translations/ProjectTree_zh_CN.ts

