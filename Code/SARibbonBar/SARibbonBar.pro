TEMPLATE     =  lib
CONFIG		 += debug  c++11 
CONFIG		 += qt
TARGET 		 =  SARibbonBar
QT      	 += core gui widgets
DEFINES 	 += SA_RIBBON_BAR_MAKE_LIB #定义此宏将构建库
#DEFINES 	 += SA_RIBBON_DEBUG_HELP_DRAW # 此宏将绘制辅助线用于调试
RESOURCES 	 += resource.qrc
TRANSLATIONS += ../qrc/translations/SARibbonBar_zh_CN.ts
include(./SARibbonBar.pri)

win32{
  INCLUDEPATH	+=  ./ \
                    ../ \

  CONFIG(release,debug|release):DESTDIR         = ../../output/bin 
  CONFIG(release,debug|release):MOC_DIR         = ./release/moc 
  CONFIG(release,debug|release):RCC_DIR         = ./release/rcc
  CONFIG(release,debug|release):UI_DIR          = ./release/qui
  CONFIG(release,debug|release):OBJECTS_DIR     = ./release/obj
	
  CONFIG(debug,debug|release):	CONFIG  +=  console
  CONFIG(debug,debug|release):DESTDIR         = ../../output/bin_d 
  CONFIG(debug,debug|release):MOC_DIR         = ./debug/moc 
  CONFIG(debug,debug|release):RCC_DIR         = ./debug/rcc 
  CONFIG(debug,debug|release):UI_DIR          = ./debug/qui 
  CONFIG(debug,debug|release):OBJECTS_DIR     = ./debug/obj 
	
  message("Windows SARibbonBar build")                                            
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
	
  message("Linux SARibbonBar build")
}
