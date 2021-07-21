TEMPLATE	=   lib
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   PluginMeshDataExchange
QT          +=  core xml gui widgets printsupport
DEFINES     +=  MESHDATAEXCHANGEPLUGIN_API

include(./meshDataExchangePlugin.pri)
include(./../vtk.pri)
include(./../cgns.pri)

win32{

  INCLUDEPATH	+=  ./ \
                    ../ \
					../SelfDefObject \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin/plugins 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS +=  \
	-L../../output/bin -lMainWindow \
	-L../../output/bin -lSelfDefObject \
	-L../../output/bin -lDataProperty \
	-L../../output/bin -lGeometry \
	-L../../output/bin -lGeometryWidgets \
	-L../../output/bin -lGeometryCommand \
	-L../../output/bin -lModuleBase \
	-L../../output/bin -lModelData \
	-L../../output/bin -lMainWidgets \
	-L../../output/bin -lPythonModule \
	-L../../output/bin -lPluginManager \
	-L../../output/bin -lMeshData \
	-L../../output/bin -lIO \
	-L../../output/bin -lBCBase \
	-L../../output/bin -lMaterial \
	-L../../output/bin -lConfigOptions \
	
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d/plugins
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
  CONFIG(debug,debug|release):LIBS +=  \
	-L../../output/bin_d -lMainWindow \
	-L../../output/bin_d -lSettings \
	-L../../output/bin_d -lSelfDefObject \
	-L../../output/bin_d -lDataProperty \
	-L../../output/bin_d -lGeometry \
	-L../../output/bin_d -lGeometryWidgets \
	-L../../output/bin_d -lGeometryCommand \
	-L../../output/bin_d -lModuleBase \
	-L../../output/bin_d -lModelData \
	-L../../output/bin_d -lMainWidgets \
	-L../../output/bin_d -lPythonModule \
	-L../../output/bin_d -lPluginManager \
	-L../../output/bin_d -lMeshData \
	-L../../output/bin_d -lIO \
    -L../../output/bin_d -lBCBase \
	-L../../output/bin_d -lMaterial \
	-L../../output/bin_d -lConfigOptions \
	
  message("Windows MeshDataExchangePlugin build")
  
}


unix{

    INCLUDEPATH	+=   ./ \
		      ../ \
                     ../SelfDefObject \
					 
  CONFIG          += plugin
  DESTDIR         = ../../output/bin/plugins 
  MOC_DIR         = ./release/moc
  UI_DIR          = ./release/qui
  RCC_DIR         = ./release/rcc
  OBJECTS_DIR     = ./release/obj
  LIBS += \
    -L../../output/bin -lMainWindow \
	-L../../output/bin -lSelfDefObject \
	-L../../output/bin -lDataProperty \
	-L../../output/bin -lGeometry \
	-L../../output/bin -lGeometryWidgets \
	-L../../output/bin -lGeometryCommand \
	-L../../output/bin -lModuleBase \
	-L../../output/bin -lModelData \
	-L../../output/bin -lMainWidgets \
	-L../../output/bin -lPythonModule \
	-L../../output/bin -lPluginManager \
	-L../../output/bin -lMeshData \
	-L../../output/bin -lIO \
	-L../../output/bin -lBCBase \
	-L../../output/bin -lMaterial \
	
  message("Linux MeshDataExchangePlugin build")
  
}
#RESOURCES += ./qrc/ETSResource.qrc \

#TRANSLATIONS += ./resource/translation/transtrations_zh_CN.ts



