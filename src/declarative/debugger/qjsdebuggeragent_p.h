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

#ifndef QJSDEBUGGERAGENT_P_H
#define QJSDEBUGGERAGENT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtScript/qscriptengineagent.h>
#include <QtCore/qset.h>

QT_BEGIN_NAMESPACE
class QScriptValue;
class QDeclarativeEngine;
QT_END_NAMESPACE

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Declarative)

class QJSDebuggerAgentPrivate;

enum JSDebuggerState
{
    NoState,
    SteppingIntoState,
    SteppingOverState,
    SteppingOutState,
    StoppedState
};

struct JSAgentWatchData
{
    QByteArray exp;
    QByteArray name;
    QByteArray value;
    QByteArray type;
    bool hasChildren;
    quint64 objectId;
};

inline QDataStream &operator<<(QDataStream &s, const JSAgentWatchData &data)
{
    return s << data.exp << data.name << data.value
             << data.type << data.hasChildren << data.objectId;
}

struct JSAgentStackData
{
    QByteArray functionName;
    QByteArray fileUrl;
    qint32 lineNumber;
};

inline QDataStream &operator<<(QDataStream &s, const JSAgentStackData &data)
{
    return s << data.functionName << data.fileUrl << data.lineNumber;
}

struct JSAgentBreakpointData
{
    QByteArray functionName;
    QByteArray fileUrl;
    qint32 lineNumber;
};

typedef QSet<JSAgentBreakpointData> JSAgentBreakpoints;

inline QDataStream &operator<<(QDataStream &s, const JSAgentBreakpointData &data)
{
    return s << data.functionName << data.fileUrl << data.lineNumber;
}

inline QDataStream &operator>>(QDataStream &s, JSAgentBreakpointData &data)
{
    return s >> data.functionName >> data.fileUrl >> data.lineNumber;
}

inline bool operator==(const JSAgentBreakpointData &b1, const JSAgentBreakpointData &b2)
{
    return b1.lineNumber == b2.lineNumber && b1.fileUrl == b2.fileUrl;
}

inline uint qHash(const JSAgentBreakpointData &b)
{
    return b.lineNumber ^ qHash(b.fileUrl);
}


class QJSDebuggerAgent : public QObject, public QScriptEngineAgent
{
    Q_OBJECT

public:
    QJSDebuggerAgent(QScriptEngine *engine, QObject *parent = 0);
    QJSDebuggerAgent(QDeclarativeEngine *engine, QObject *parent = 0);
    ~QJSDebuggerAgent();

    void setBreakpoints(const JSAgentBreakpoints &);
    void setWatchExpressions(const QStringList &);

    void stepOver();
    void stepInto();
    void stepOut();
    void continueExecution();

    JSAgentWatchData executeExpression(const QString &expr);
    QList<JSAgentWatchData> expandObjectById(quint64 objectId);
    QList<JSAgentWatchData> locals();
    QList<JSAgentWatchData> localsAtFrame(int frameId);
    QList<JSAgentStackData> backtrace();
    QList<JSAgentWatchData> watches();
    void setProperty(qint64 objectId,
                     const QString &property,
                     const QString &value);

    // reimplemented
    void scriptLoad(qint64 id, const QString &program,
                    const QString &fileName, int baseLineNumber);
    void scriptUnload(qint64 id);

    void contextPush();
    void contextPop();

    void functionEntry(qint64 scriptId);
    void functionExit(qint64 scriptId,
                      const QScriptValue &returnValue);

    void positionChange(qint64 scriptId,
                        int lineNumber, int columnNumber);

    void exceptionThrow(qint64 scriptId,
                        const QScriptValue &exception,
                        bool hasHandler);
    void exceptionCatch(qint64 scriptId,
                        const QScriptValue &exception);

    bool supportsExtension(Extension extension) const;
    QVariant extension(Extension extension,
                       const QVariant &argument = QVariant());

Q_SIGNALS:
    void stopped(bool becauseOfException,
                 const QString &exception);

private:
    friend class QJSDebuggerAgentPrivate;
    QJSDebuggerAgentPrivate *d;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QJSDEBUGGERAGENT_P_H
