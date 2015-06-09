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

#include "myWidgetAction.h"

myWidgetAction::myWidgetAction(QObject *parent)
 : QWidgetAction(parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(runCommand()));
}

void myWidgetAction::setParameters(QMap<QString, QString>& map) {
    if(this->_params.empty()) replaceVariablesInParameters(map);

    for(auto key : this->_params.keys()) {
        QString value = this->_params.value(key);
        if(key == "name" || key == "title")
            this->setText(value);
        else if(key == "title_cmd")
            this->setText(Util::getCommandResult(value));
        else if(key == "icon")
            this->setIcon(QIcon(value));
        else if(key == "icon_cmd")
            this->setIcon(QIcon(Util::getCommandResult(value)));
        else if(key == "cmd")
            this->setCommand(value);
        else if(key == "term" || key == "terminal") {
            this->setRunInTerminal(true);
            this->setHoldTerminal(map.value(key) == "hold");
        }
    }
}

void myWidgetAction::replaceVariablesInParameters(QMap<QString, QString> &map) {
    if(this->_variables.count() == 0)
        this->_params.unite(map);
    else {
        for(auto key : map.keys()) {
            QString value = map.value(key);
            for(auto var : this->_variables.keys())
                value = value.replace("$" + var, this->_variables.value(var));

            this->_params.insert(key, value);
        }
    }
}

void myWidgetAction::runCommand() {
    Util::runCommand(this->_command, this->_runInTerminal, this->_holdTerminal);
}

QMap<QString, QString>* myWidgetAction::variables() {
    return &(this->_variables);
}

void myWidgetAction::setText(const QString &text) {
    QWidgetAction::setText(text);
}

void myWidgetAction::setIcon(const QIcon &icon) {
    QWidgetAction::setIcon(icon);
}

void myWidgetAction::setCommand(const QString &command) {
    this->_command = command;
}

QString& myWidgetAction::command() {
    return this->_command;
}

void myWidgetAction::setRunInTerminal(bool runInTerminal) {
    this->_runInTerminal = runInTerminal;
}

bool myWidgetAction::runInTerminal() {
    return this->_runInTerminal;
}

void myWidgetAction::setHoldTerminal(bool holdTerminal) {
    this->_holdTerminal = holdTerminal;
}

bool myWidgetAction::holdTerminal() {
    return this->_holdTerminal;
}

void myWidgetAction::trigger() {
    emit(triggered());
}
