TEMPLATE	=   lib
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   IO
QT          +=  core xml widgets 
DEFINES     +=  IO_API

include(./IO.pri)
include(./../vtk.pri)
include(./../occ.pri)

win32{

  INCLUDEPATH	+=  ./ \
                    ../ \
					../../quazip/include/ \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS +=  \
  -L../../output/bin -lMeshData \
  -L../../output/bin -lDataProperty \
  -L../../output/bin -lModuleBase \
  -L../../output/bin -lGeometry \
  -L../../output/bin -lModelData \
  -L../../output/bin -lPluginManager \
  -L../../output/bin -lSettings \
  -L../../output/bin -lMaterial \
  -L../../quazip/lib -lquazip \
  -L../../output/bin -lGmshModule \
 
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
  CONFIG(debug,debug|release):LIBS +=  \
  -L../../output/bin_d -lMeshData \
  -L../../output/bin_d -lDataProperty \
  -L../../output/bin_d -lModuleBase \
  -L../../output/bin_d -lGeometry \
  -L../../output/bin_d -lModelData \
  -L../../output/bin_d -lPluginManager \
  -L../../output/bin_d -lSettings \
  -L../../output/bin_d -lMaterial \
  -L../../quazip/libd -lquazipd  \
  -L../../output/bin_d -lGmshModule \
  
  message("Windows IO build")
  
}


unix{
    INCLUDEPATH	+=   ./ \
		             ../ \
					 ../../quazip/include/quazip \
  CONFIG          += plugin
  DESTDIR         = ../../output/bin
  MOC_DIR         = ./release/moc
  UI_DIR          = ./release/qui
  RCC_DIR         = ./release/rcc
  OBJECTS_DIR     = ./release/obj
  LIBS += \
  -L../../output/bin -lMeshData \
  -L../../output/bin -lDataProperty \
  -L../../output/bin -lModuleBase \
  -L../../output/bin -lGeometry \
  -L../../output/bin -lModelData \
  -L../../output/bin -lSettings \	
  -L../../quazip/lib -lquazip \
  
  message("Linux IO build")
  
}

TRANSLATIONS     += ../qrc/translations/IO_zh_CN.ts
