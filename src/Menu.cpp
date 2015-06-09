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

#include "Menu.h"

Menu::Menu(QMap<QString, QString> &vars) {
    this->_variables.unite(vars);
}

void Menu::addEntries(Entry *root) {
    for(Entry* e : root->entries()) {
        if(e->entries().count() == 0)
            if(e->params().value("type", "normal") == "section")
                this->addSection(e);
            else addEntry(e);
        else addSubmenu(e);
    }
}

void Menu::addEntry(Entry *e) {
    myWidgetAction* action = getAction(e);
    if(action) {
        action->variables()->unite(this->_variables);
        action->setParameters(e->params());
        connect(action, SIGNAL(triggered()), this, SLOT(close()));
        this->addAction(action);
    }
}

myWidgetAction* Menu::getAction(Entry *e) {
    QString type = e->params().value("type", "normal");

    if(type == "normal")
        return new myWidgetAction(this);
    else if(type == "text")
        return new textWidgetAction(this);
    else if(type == "combo")
        return new comboWidgetAction(this);

    return NULL;
}

void Menu::addSubmenu(Entry *e) {
    QString loopMode = e->params().value("loop", "none");
    if(loopMode == "none") {
        Menu* submenu = new Menu(this->_variables);
        submenu->parseSubmenuParameters(e, submenu);
        submenu->addEntries(e);
        connect(submenu, SIGNAL(triggered(QAction*)), this, SLOT(close()));
        this->addMenu(submenu);
    }
    else if(loopMode == "inside")
        addLoopSubmenu(e, true, false);
    else if(loopMode == "outside")
        addLoopSubmenu(e, false, true);
    else if(loopMode == "inside_out")
        addLoopSubmenu(e, true, true);
}

void Menu::addLoopSubmenu(Entry *e, bool inside, bool outside) {
    Menu* submenu = (inside && outside) ? this : new Menu(this->_variables);
    QStringList loopValues = Util::getValues(e->params(), "loop_values", "loop_values_cmd");
    for(QString val : loopValues) {
        submenu->variables()->insert(e->params().value("loop_var", "x"), val);
        submenu->addEntries(e);

        if(!inside) {
            parseSubmenuParameters(e, submenu);
            this->addMenu(submenu);
            submenu = new Menu(this->_variables);
        }
    }

    if(inside && !outside) {
        parseSubmenuParameters(e, submenu);
        this->addMenu(submenu);
    }
}

void Menu::addSection(Entry *e) {
    QString name = e->params().value("name");
    QRegExp reg("^-+ ?");
    name = name.replace(reg, "");

    if(e->params().contains("title_cmd"))
        name = Util::getCommandResult(e->params().value("title_cmd"));

    QString icon = e->params().value("icon", "");
    if(e->params().contains("icon_cmd"))
        icon = Util::getCommandResult(e->params().value("icon_cmd"));

    QMenu::addSection(QIcon(icon), name);
}

void Menu::parseSubmenuParameters(Entry *e, Menu *m) {
    for(auto key : e->params().keys()) {
        QString value = e->params().value(key);
        if(m->_variables.count() > 0)
            for(auto var : m->_variables.keys())
                value = value.replace("$" + var, m->_variables.value(var));

        if(key == "name" || key == "title")
            m->setTitle(value);
        else if(key == "title_cmd")
            m->setTitle(Util::getCommandResult(value));
        else if(key == "icon")
            m->setIcon(QIcon(value));
        else if(key == "icon_cmd")
            m->setIcon(QIcon(Util::getCommandResult(value)));
    }
}

QMap<QString, QString>* Menu::variables() {
    return &(this->_variables);
}
