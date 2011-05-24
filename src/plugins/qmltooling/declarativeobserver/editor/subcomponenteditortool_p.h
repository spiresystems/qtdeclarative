/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtDeclarative module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef SUBCOMPONENTEDITORTOOL_H
#define SUBCOMPONENTEDITORTOOL_H

#include "abstractliveedittool_p.h"

#include <QtCore/QStack>
#include <QtCore/QStringList>

QT_FORWARD_DECLARE_CLASS(QGraphicsObject)
QT_FORWARD_DECLARE_CLASS(QPoint)
QT_FORWARD_DECLARE_CLASS(QTimer)

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Declarative)

class SubcomponentMaskLayerItem;

class SubcomponentEditorTool : public AbstractLiveEditTool
{
    Q_OBJECT

public:
    SubcomponentEditorTool(QDeclarativeViewObserver *view);
    ~SubcomponentEditorTool();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void hoverMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *keyEvent);
    void itemsAboutToRemoved(const QList<QGraphicsItem*> &itemList);

    void clear();

    bool containsCursor(const QPoint &mousePos) const;
    bool itemIsChildOfQmlSubComponent(QGraphicsItem *item) const;

    bool isChildOfContext(QGraphicsItem *item) const;
    bool isDirectChildOfContext(QGraphicsItem *item) const;
    QGraphicsItem *firstChildOfContext(QGraphicsItem *item) const;

    void setCurrentItem(QGraphicsItem *contextObject);

    void pushContext(QGraphicsObject *contextItem);

    QGraphicsObject *currentRootItem() const;
    QGraphicsObject *setContext(int contextIndex);
    int contextIndex() const;

signals:
    void exitContextRequested();
    void cleared();
    void contextPushed(const QString &contextTitle);
    void contextPopped();
    void contextPathChanged(const QStringList &path);

protected:
    void selectedItemsChanged(const QList<QGraphicsItem*> &itemList);

private slots:
    void animate();
    void contextDestroyed(QObject *context);
    void resizeMask();

private:
    QGraphicsObject *popContext();
    void aboutToPopContext();

private:
    QStack<QGraphicsObject *> m_currentContext;
    QStringList m_path;

    qreal m_animIncrement;
    SubcomponentMaskLayerItem *m_mask;
    QTimer *m_animTimer;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // SUBCOMPONENTEDITORTOOL_H
