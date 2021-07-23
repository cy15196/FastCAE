TEMPLATE	=   app
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   FastCAE
QT          +=  core gui widgets

include(./main.pri)
include(../vtk.pri)
include(../occ.pri)

win32{

#CONFIG(release,debug|release):QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator'uiAccess='false'"

  INCLUDEPATH	+=  ./ \
					../ \
					../Licese/ \

# CONFIG(release,debug|release):CONFIG	    	+=  console
  CONFIG(release,debug|release):DESTDIR         = ../../output/bin
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS +=  \
	-L../../output/bin -lMainWindow \
	-L../../output/bin -lLicense \
	-L../../output/bin -lConfigOptions \
	-L../../output/bin -lProjectTree \
	-L../../output/bin -lSettings \
	-L../../output/bin -lPythonModule \
 

  CONFIG(debug,debug|release):CONFIG   	+=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj
  CONFIG(debug,debug|release):LIBS +=  \
	-L../../output/bin_d -lMainWindow \
	-L../../output/bin_d -lLicense \
	-L../../output/bin_d -lConfigOptions \
	-L../../output/bin_d -lProjectTree \
	-L../../output/bin_d -lSettings \
	-L../../output/bin_d -lPythonModule \
	
  message("Windows main build")
}

unix{

  include(../python.pri)

  INCLUDEPATH	+=   ./ \
		     ../ \

  CONFIG       	+=  console
  CONFIG          += plugin
  DESTDIR         = ../../output/bin
  MOC_DIR         = ./release/moc
  UI_DIR          = ./release/qui
  RCC_DIR         = ./release/rcc
  OBJECTS_DIR     = ./release/obj
  LIBS += \
	-L../../output/bin -lPythonModule \
	-L../../output/bin -lSettings \
        -L../../output/bin -lMeshData \
        -L../../output/bin -lMaterial\
        -L../../output/bin -lConfigOptions \
        -L../../output/bin -lHeuDataSrcIO \
        -L../../output/bin -lGeometry \
        -L../../output/bin -lModelData \
        -L../../output/bin -lCurveAnalyse \
        -L../../output/bin -lModuleBase \
        -L../../output/bin -lGraphicsAnalyse \
		-L../../output/bin -lPostWidgets \
		-L../../output/bin -lIO \
		-L../../output/bin -lProjectTree \
		-L../../output/bin -lSolverControl \
		-L../../output/bin -lProjectTreeExtend \
		-L../../output/bin -lMainWidgets \
		-L../../output/bin -lMainWindow \        
	
  message("Linux main build")
}

RESOURCES += ../qrc/qianfan.qrc

RC_FILE += ../qrc/qianfan.rc
