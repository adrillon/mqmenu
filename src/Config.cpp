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

#include "Config.h"

QString Config::menuFile = "";
QPoint Config::menuPosition = QPoint(0,0);
QString Config::shell = "";
QString Config::terminal = "";
QString Config::holdTerminal = "";
int Config::iconSize = 0;

void Config::loadDefaults() {
    menuFile = QString(
                (QString(getenv("XDG_CONFIG_HOME")).isEmpty() ? getenv("HOME")
                                                              : getenv("XDG_CONFIG_HOME")))
               + "/.mqmenu";
    menuPosition = QCursor::pos();
    shell = "bash -c";
    terminal = "xterm -e";
    holdTerminal = "xterm -hold -e";
    iconSize = 24;
}

void Config::loadFromMap(const QMap<QString, QString> &map) {
    for(QString key : map.keys()) {
        if(key == "x")
            menuPosition.setX((map.value(key).startsWith("m") ? QCursor::pos().x() : map.value(key).toUInt()));
        else if(key == "y")
            menuPosition.setY((map.value(key).startsWith("m") ? QCursor::pos().y() : map.value(key).toUInt()));
        else if(key == "shell")
            shell = map.value(key);
        else if(key == "term" || key == "terminal")
            terminal = map.value(key);
        else if(key == "term_hold" || key == "hold_term" || key == "hold_terminal")
            holdTerminal = map.value(key);
        else if(key == "iconsize")
            iconSize = map.value(key).toInt();
    }
}
