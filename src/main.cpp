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

#include <QApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QMenu>
#include "Config.h"
#include "Entry.h"
#include "FileParser.h"
#include "Menu.h"
#include "myProxyStyle.h"

QMap<QString, QString> argumentsToMap(const QStringList& arguments) {
    QCommandLineParser clp;

    QCommandLineOption optFile({"c", "config"}, "The path to the config file", "c", Config::menuFile);
    QCommandLineOption optIconSize({"i", "iconsize"}, "The size of the icons", "i", QString::number(Config::iconSize));
    QCommandLineOption optShell({"s", "shell"}, "The shell used to run commands", "s", Config::shell);
    QCommandLineOption optTerm({"t", "term"}, "The terminal used to run commands", "t", Config::terminal);
    QCommandLineOption optHoldTerm({"T", "hold"}, "The terminal used to run commands (hold)", "T", Config::holdTerminal);
    QCommandLineOption optPosX({"x", "xpos"}, "The X position of the menu", "x", QString::number(Config::menuPosition.x()));
    QCommandLineOption optPosY({"y", "ypos"}, "The Y position of the menu", "y", QString::number(Config::menuPosition.y()));

    clp.addOption(optFile);
    clp.addOption(optIconSize);
    clp.addOption(optShell);
    clp.addOption(optTerm);
    clp.addOption(optHoldTerm);
    clp.addOption(optPosX);
    clp.addOption(optPosY);
    clp.process(arguments);

    QMap<QString, QString> map;
    map.insert("filename", clp.value(optFile));
    map.insert("iconsize", clp.value(optIconSize));
    map.insert("shell", clp.value(optShell));
    map.insert("terminal", clp.value(optTerm));
    map.insert("hold_terminal", clp.value(optHoldTerm));
    map.insert("x", clp.value(optPosX));
    map.insert("y", clp.value(optPosY));

    return map;
}

int main (int argc, char** argv) {
    QApplication app(argc, argv);
    app.setStyle(new myProxyStyle);

    Config::loadDefaults();
    Config::menuFile = argumentsToMap(app.arguments()).value("filename");

    Entry* root = new Entry();
    FileParser::parseFromFile(root, Config::menuFile);
    if(root->entries().at(0)->params().value("name") == "mqm_config") {
        Config::loadFromMap(root->entries().at(0)->params());
        root->entries().removeFirst();
    }
    Config::loadFromMap(argumentsToMap(app.arguments()));

    Menu menu;
    menu.move(Config::menuPosition);
    menu.addEntries(root);
    menu.exec();

    return 0;
}
