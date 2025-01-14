﻿/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the FOO module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    // call default implementation to actually install README.txt!
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/TopTestApp.exe", "@StartMenuDir@/Rsm炉温测试仪软件.lnk",
            "workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll",
            "iconId=2", "description=Open README file");
        component.addOperation("CreateShortcut", "@TargetDir@/TopTestApp.exe", "@HomeDir@/Desktop/Rsm炉温测试仪软件.lnk");

        component.addOperation("CreateShortcut", "@TargetDir@/maintenancetool.exe", "@StartMenuDir@/卸载Rsm炉温测试仪软件.lnk");

        var iconId = 0;
        var topTestAppPath = installer.value("TargetDir") +"\\TopTestApp.exe";
        if (installer.value("os") === "win")
        {
            component.addOperation("RegisterFileType",
                                   "rsm",
                                    topTestAppPath+ " \"%1\"",
                                   "Rsm temperture test data file type",
                                   "binary",
                                   topTestAppPath + "," + iconId,
                                   "ProgId=Rsm.TopTest." + "rsm"
                                   );

            component.addOperation("RegisterFileType",
                                   "rsf",
                                    topTestAppPath+ " \"%1\"",
                                   "Rsm configure file",
                                   "binary",
                                   topTestAppPath + "," + iconId,
                                   "ProgId=Rsm.TopTest." + "rsf"
                                   );

            component.addOperation("RegisterFileType",
                                   "rpf",
                                    topTestAppPath+ " \"%1\"",
                                   "Rsm New Version Project file",
                                   "binary",
                                   topTestAppPath + "," + iconId,
                                   "ProgId=Rsm.TopTest." + "rpf"
                                   );
        }

//        component.addOperation("Execute", installer.value("TargetDir") +"\\LoadConfigureFile.exe" , installer.value("TargetDir") + "\\PresetConfigure.rsf" );
    }
}
