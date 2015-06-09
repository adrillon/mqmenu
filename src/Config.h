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

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <QCursor>
#include <QMap>
#include <QPoint>
#include <QString>
#include <cstdlib>

class Config {
public:
    static QString menuFile;
    static QPoint menuPosition;
    static QString shell;
    static QString terminal;
    static QString holdTerminal;
    static int iconSize;

    static void loadDefaults();
    static void loadFromMap(const QMap<QString, QString>& map);
private:
    Config(){}
};

#endif // __CONFIG_H__
