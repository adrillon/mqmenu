/*
 * mqmenu - a full-featured menu and application launcher
 * Copyright (C) 2015  Alain DRILLON
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MYWIDGETACTION_H__
#define __MYWIDGETACTION_H__

#include <QAction>
#include <QWidgetAction>
#include <QMap>
#include <QProcess>
#include <QString>
#include "Util.h"

class myWidgetAction : public QWidgetAction {
    Q_OBJECT

public:
    myWidgetAction(QObject* parent);

    virtual void setParameters(QMap<QString, QString>& map);
    virtual void setText(const QString& text);
    virtual void setIcon(const QIcon &icon);
    virtual void setCommand(const QString& command);
    virtual void setRunInTerminal(bool runInTerminal);
    virtual void setHoldTerminal(bool holdTerminal);

    virtual QMap<QString, QString>* variables();
    virtual QString& command();
    virtual bool runInTerminal();
    virtual bool holdTerminal();

public slots:
    virtual void runCommand();
    virtual void trigger();

protected:
    QMap<QString, QString> _variables;
    QMap<QString, QString> _params;

    bool _autoCommand = false;
    bool _runInTerminal = false;
    bool _holdTerminal = false;
    QString _command;

    virtual void replaceVariablesInParameters(QMap<QString, QString>& map);
};

#endif // __MYWIDGETACTION_H__
