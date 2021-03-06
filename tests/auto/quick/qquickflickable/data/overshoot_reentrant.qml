/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
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

import QtQuick 2.9

Flickable {
    width: 200; height: 200
    contentWidth: rect.width; contentHeight: rect.height

    property real contentPosAdjustment: 0.0

    onContentXChanged: {
        var adjustment = contentPosAdjustment
        contentPosAdjustment = 0.0
        contentX += adjustment
    }

    onContentYChanged: {
        var adjustment = contentPosAdjustment
        contentPosAdjustment = 0.0
        contentY += adjustment
    }

    Rectangle {
        id: rect
        border.color: "red"
        border.width: 5
        width: 400; height: 400
    }
}
