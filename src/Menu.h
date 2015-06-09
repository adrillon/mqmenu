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

#ifndef __MENU_H__
#define __MENU_H__

#include <QMenu>
#include "Entry.h"
#include "actions/widgetActions.h"

class Menu : public QMenu {
    Q_OBJECT

public:
    Menu() {}
    Menu(QMap<QString, QString>& vars);
    void addEntries(Entry* root);

    QMap<QString, QString>* variables();

protected:
    QMap<QString, QString> _variables;

    void addEntry(Entry* e);
    myWidgetAction* getAction(Entry* e);

    void addSubmenu(Entry* e);
    void addLoopSubmenu(Entry* e, bool inside = true, bool outside = false);
    void addSection(Entry* e);
    void parseSubmenuParameters(Entry* e, Menu* m);
};

#endif // __MENU_H__
