TEMPLATE	=   lib
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   GraphicsAnalyse
QT          +=  core gui widgets opengl xml
DEFINES     +=  GRAPHICSANALYSE_LIBRARY
#DEFINES  += PATHON_SCRIPT
include(./GraphicsAnalyse.pri)
include(./../vtk.pri)

win32{

LIBS += -lOpenGL32  \

LIBS += -lGlU32  \

  INCLUDEPATH	+=  ./ \
                    ../ \
					./CTK \
					./CTK/Libs/Visualization/VTK/Widgets \
					./CTK/Libs/Widgets \
					./CTK/Libs/Visualization/VTK/Core \
					./CTK/Libs/Core \
					../HeuDataSrcIO \
					../SolutionDataIO \
					../CurveAnalyse \
					
					

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS	+=	\
  -L../../output/bin -lHeuDataSrcIO \
  -L../../output/bin -lSolutionDataIO \
  -L../../output/bin -lCurveAnalyse \
  #-L../../output/bin -lPythonModule \
  
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
  CONFIG(debug,debug|release):LIBS +=  \
  -L../../output/bin_d -lHeuDataSrcIO \
  -L../../output/bin_d -lSolutionDataIO \
  -L../../output/bin_d -lCurveAnalyse \
  #-L../../output/bin_d -lPythonModule \
	
  message("Windows GraphicsAnalyse build")
                                               
}

unix{
  INCLUDEPATH	+=   ./ \
		             ../ \
					 ../HeuDataSrcIO \
					 ../CurveAnalyse \
					 ./CTK \
					 ./CTK/Libs/Visualization/VTK/Widgets \
					 ./CTK/Libs/Visualization/VTK/Core \
					 ./CTK/Libs/Core \
					 ./CTK/Libs/Widgets \
					 ../HeuDataSrcIO \
					../SolutionDataIO \
					../CurveAnalyse \
					 
  CONFIG          += plugin
  DESTDIR         = ../../output/bin
  MOC_DIR         = ./release/moc
  UI_DIR          = ./release/qui
  RCC_DIR         = ./release/rcc
  OBJECTS_DIR     = ./release/obj
  LIBS += \
	-L../../output/bin -lHeuDataSrcIO \
	-L../../output/bin -lSolutionDataIO \
	-L../../output/bin -lCurveAnalyse \
	#-L../../output/bin -lPythonModule \
	
  message("Linux GraphicsAnalyse build")
}
RESOURCES += ./resource.qrc

TRANSLATIONS += ../translations/GraphicsAnalyse_zh_CN.ts