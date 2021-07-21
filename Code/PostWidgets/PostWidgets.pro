TEMPLATE	=   lib
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   PostWidgets
QT          +=  core gui widgets printsupport
DEFINES     +=  POSTWIDGETS_API

include(./PostWidgets.pri)
include(./../vtk.pri)

win32{
  INCLUDEPATH	+=  ./ \
                    ../ \
					../HeuDataSrcIO \
					../GraphicsAnalyse \
					../CurveAnalyse \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS	+=	\
	-L../../output/bin -lHeuDataSrcIO \
	-L../../output/bin -lGraphicsAnalyse \
	-L../../output/bin -lCurveAnalyse \
	-L../../output/bin -lModuleBase \
	-L../../output/bin -lSettings \
	-L../../output/bin -lModelData \
	-L../../output/bin -lConfigOptions \
    -L../../output/bin -lPythonModule \


  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
  CONFIG(debug,debug|release):LIBS +=  \
	-L../../output/bin_d -lHeuDataSrcIO \
	-L../../output/bin_d -lGraphicsAnalyse \
	-L../../output/bin_d -lCurveAnalyse \
	-L../../output/bin_d -lModuleBase \
	-L../../output/bin_d -lSettings \
	-L../../output/bin_d -lModelData \
	-L../../output/bin_d -lConfigOptions \
    -L../../output/bin_d -lPythonModule \
	
  message("Windows post3D build")
                                               
}

unix{
  INCLUDEPATH	+=   ./ \
		             ../ \
					 ../HeuDataSrcIO \
					../GraphicsAnalyse \
					../CurveAnalyse \
					 
  CONFIG          += plugin
  DESTDIR         = ../../output/bin
  MOC_DIR         = ./release/moc
  UI_DIR          = ./release/qui
  RCC_DIR         = ./release/rcc
  OBJECTS_DIR     = ./release/obj
  LIBS += \
    -L../../output/bin -lHeuDataSrcIO \
	-L../../output/bin -lGraphicsAnalyse \
	-L../../output/bin -lCurveAnalyse \
	-L../../output/bin -lModuleBase \
	-L../../output/bin -lConfigOptions \

	
  message("Linux post3D build")
}

TRANSLATIONS += ../qrc/translations/PostWidgets_zh_CN.ts
