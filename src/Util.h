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

#ifndef __UTIL_H__
#define __UTIL_H__

#include <QProcess>
#include <QString>
#include "Entry.h"
#include "Config.h"

namespace Util {
    void runCommand(const QString& command, bool terminal = false, bool hold = false);
    QString getCommandResult(const QString& command, bool simplify = true);
    QStringList splitList(const QString& str, bool command = false);
    QStringList getValues(const QMap<QString, QString>& params, const QString& manualParameter, const QString& cmdParameter);
}

#endif // __UTIL_H__
