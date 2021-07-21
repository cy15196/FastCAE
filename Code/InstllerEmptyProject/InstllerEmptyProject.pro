TEMPLATE = aux

INSTALLER = FastCAE_installer.exe

QT_BIN_DIR= $$(QTDIR)\bin

INPUT = $$PWD/config/config.xml $$OUT_PWD/packages
makeInstaller.input = INPUT
makeInstaller.output = $$INSTALLER

#qt
makeInstaller.commands += $$QT_BIN_DIR\windeployqt.exe --quick --quickwidgets --printsupport --webview --webengine --webenginewidgets --xml --network $$PWD/../../output/bin_d/FastCAE.exe &

CONFIG(debug,debug|release){
#vtk quazip occ python gmesh
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\..\vtk\bind\*.* $$replace(PWD,/,\\)\..\..\output\bin_d &
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\..\quazip\libd\*.* $$replace(PWD,/,\\)\..\..\output\bin_d &
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\..\OCC\win64\vc14\bind\*.* $$replace(PWD,/,\\)\..\..\output\bin_d &
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\..\OCC\win64\vc14\bin\freetype.dll $$replace(PWD,/,\\)\..\..\output\bin_d &
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\..\output\Python37 $$replace(PWD,/,\\)\..\..\output\bin_d &
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\Gmsh\gmsh454 $$replace(PWD,/,\\)\..\..\output\bin_d\gmsh &

#py files python\Py
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\python\Py $$replace(PWD,/,\\)\..\..\output\bin_d\gmsh &


#web engine
makeInstaller.commands += xcopy /y/d/s/i $$QT_BIN_DIR\QtWebEngineProcess.exe $$replace(PWD,/,\\)\..\..\output\bin &
makeInstaller.commands += xcopy /y/d/s/i $$QT_BIN_DIR\..\translations\qtwebengine_locales $$replace(PWD,/,\\)\..\..\output\bin\translations\qtwebengine_locales &
makeInstaller.commands += xcopy /y/d/s/i $$QT_BIN_DIR\..\resources $$replace(PWD,/,\\)\..\..\output\bin\resources &
}else{
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\..\vtk\bin\*.* $$replace(PWD,/,\\)\..\..\output\bin &
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\..\quazip\lib\*.* $$replace(PWD,/,\\)\..\..\output\bin &
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\..\OCC\win64\vc14\bin\*.* $$replace(PWD,/,\\)\..\..\output\bin &
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\..\OCC\win64\vc14\bin\freetype.dll $$replace(PWD,/,\\)\..\..\output\bin &
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\..\output\Python37 $$replace(PWD,/,\\)\..\..\output\bin &
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\Gmsh\gmsh454 $$replace(PWD,/,\\)\..\..\output\bin\gmsh &

#py files python\Py
makeInstaller.commands += xcopy /y/d/s/i $$replace(PWD,/,\\)\..\python\Py $$replace(PWD,/,\\)\..\..\output\bin\gmsh &


#web engine
makeInstaller.commands += xcopy /y/d/s/i $$QT_BIN_DIR\QtWebEngineProcessd.exe $$replace(PWD,/,\\)\..\..\output\bin_d &
makeInstaller.commands += xcopy /y/d/s/i $$QT_BIN_DIR\..\translations\qtwebengine_locales $$replace(PWD,/,\\)\..\..\output\bin_d\translations\qtwebengine_locales &
makeInstaller.commands += xcopy /y/d/s/i $$QT_BIN_DIR\..\resources $$replace(PWD,/,\\)\..\..\output\bin_d\resources &

}

#form a fake file
makeInstaller.commands += echo "test" > FastCAE_installer.exe &
#makeInstaller.commands += $$QT_BIN_DIR\lrelease $$PWD/../TopTest.pro
#makeInstaller.commands +=& $$QT_BIN_DIR\windeployqt.exe --serialport --sql $$OUT_PWD/../bin/TopTestApp.exe
#makeInstaller.commands +=& copy /y $$replace(PWD,/,\\)\..\*.rsf  $$replace(OUT_PWD,/,\\)\..\bin
#makeInstaller.commands +=& copy /y $$replace(PWD,/,\\)\..\*.exe  $$replace(OUT_PWD,/,\\)\..\bin
#makeInstaller.commands +=& copy /y  $$replace(OUT_PWD,/,\\)\..\bin\*.* $$replace(PWD,/,\\)\packages\cn.rsm.toptest\data
#makeInstaller.commands +=& del  $$replace(PWD,/,\\)\packages\cn.rsm.toptest\data\RSMConfigure*.*
#makeInstaller.commands +=& xcopy /y/d/s/i $$replace(OUT_PWD,/,\\)\..\bin  $$replace(PWD,/,\\)\packages\cn.rsm.toptest\data\

#makeInstaller.commands +=& copy /y $$replace(PWD,/,\\)\..\*.qm  $$replace(PWD,/,\\)\packages\cn.rsm.toptest\data\translations
#makeInstaller.commands +=& copy /y $$replace(PWD,/,\\)\..\*.qm  $$replace(OUT_PWD,/,\\)\..\bin\translations
#makeInstaller.commands +=& $$QT_BIN_DIR\windeployqt.exe $$PWD/packages/cn.rsm.toptest/data/TopTestApp.exe
##makeInstaller.commands +=& xcopy /y $$QT_BIN_DIR\Qt5PrintSupport.dll $$install_data_dir
##makeInstaller.commands +=& xcopy /y $$QT_BIN_DIR\Qt5Charts.dll $$install_data_dir
#makeInstaller.commands +=& copy /y $$QT_BIN_DIR\Qt5Network.dll $$replace(PWD,/,\\)\packages\cn.rsm.toptest\data
#makeInstaller.commands +=& $$(QTDIR)\..\..\..\QtIFW-3.0.4\bin\binarycreator.exe --offline-only -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT} -v

#make reposity
#makeInstaller.commands +=& $$(QTDIR)\..\..\..\QtIFW-3.0.4\bin\repogen.exe --update-new-components -p $$PWD/packages $$PWD/repository
#makeInstaller.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += makeInstaller

OTHER_FILES = README
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DISTFILES += \
    packages/*/meta/*.* \
    packages/*/data/*.* \
    config/config.xml \

#QT_BIN_DIR=G:\Qt\Qt5.9.3\5.9.3\msvc2017_64\bin
