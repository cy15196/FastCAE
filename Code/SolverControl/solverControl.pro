TEMPLATE	=   lib
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   SolverControl
QT          +=  core gui widgets
DEFINES     +=  SOLVERCONTROL_API

include(./solverControl.pri)

win32{

  INCLUDEPATH	+=  ./ \
                    ../ \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS +=  \
	-L../../output/bin -lSettings \
	-L../../output/bin -lModuleBase \
	-L../../output/bin -lModelData \
	-L../../output/bin -lDataProperty \
	-L../../output/bin -lIO \
	-L../../output/bin -lPostWidgets \
	-L../../output/bin -lConfigOptions \
	-L../../output/bin -lPythonModule \
	-L../../output/bin -lSelfDefObject \
 
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
  CONFIG(debug,debug|release):LIBS +=  \
	-L../../output/bin_d -lSettings \
	-L../../output/bin_d -lModuleBase \
    -L../../output/bin_d -lModelData \
	-L../../output/bin_d -lDataProperty \
	-L../../output/bin_d -lIO \
	-L../../output/bin_d -lPostWidgets \
	-L../../output/bin_d -lConfigOptions \
    -L../../output/bin_d -lPythonModule \
	-L../../output/bin_d -lSelfDefObject \
   
    message("Windows solverControl build")
  
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
	-L../../output/bin -lModuleBase \
	-L../../output/bin -lModelData \
	-L../../output/bin -lDataProperty \
	-L../../output/bin -lIO \
	-L../../output/bin -lPostWidgets \
    -L../../output/bin -lPythonModule \
  
  message("Linux solverControl build")
}

RESOURCES += ../qrc/qianfan.qrc

TRANSLATIONS     +=  ../qrc/translations/SolverControl_Zh_CN.ts
