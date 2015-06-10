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

#ifndef __CHECKWIDGETACTION_H__
#define __CHECKWIDGETACTION_H__

#include "myWidgetAction.h"

class checkWidgetAction : public myWidgetAction {
    Q_OBJECT

public:
    checkWidgetAction(QObject* parent);

    virtual void setParameters(QMap<QString, QString>& map);

public slots:
    virtual void runCommand();

private:
    QString _uncheckCommand;
};

#endif // __CHECKWIDGETACTION_H__
