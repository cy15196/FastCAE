TEMPLATE	=   lib
CONFIG		+=   c++11 
CONFIG		+=  qt
TARGET		=   ConfigOptions
QT          +=  core xml widgets
DEFINES     +=  CONFIGOPTIONS_API

include(./ConfigOptions.pri)

win32{
  INCLUDEPATH	+=  ./ \
                    ../ \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
  CONFIG(release,debug|release):LIBS	+=	\
#	-L../../output/bin -lProjectTree \
#	-L../../output/bin -lModuleBase \
	-L../../output/bin -lBCBase \
	-L../../output/bin -lDataProperty \
	-L../../output/bin -lMaterial \
	-L../../output/bin -lPythonModule \
	-L../../output/bin -lSettings \
  
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
  CONFIG(debug,debug|release):LIBS +=  \
#	-L../../output/bin_d -lProjectTree \
#	-L../../output/bin_d -lModuleBase \
	-L../../output/bin_d -lBCBase \
	-L../../output/bin_d -lDataProperty \
	-L../../output/bin_d -lMaterial \
	-L../../output/bin_d -lPythonModule \
	-L../../output/bin_d -lSettings \
	
  message("Windows config options build")
                                               
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
#	-L../../output/bin -lProjectTree \
#	-L../../output/bin -lModuleBase \
	-L../../output/bin -lBCBase \
	-L../../output/bin -lDataProperty \
	-L../../output/bin -lPythonModule \
	-L../../output/bin -lSettings \
 
  message("Linux config options build")
}

#RESOURCES += ../qrc/config.qrc

