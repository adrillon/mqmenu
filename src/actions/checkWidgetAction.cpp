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

#include "checkWidgetAction.h"

checkWidgetAction::checkWidgetAction(QObject *parent)
 : myWidgetAction(parent)
{
    this->setCheckable(true);
}

void checkWidgetAction::setParameters(QMap<QString, QString> &map) {
    myWidgetAction::setParameters(map);

    for(auto key : this->_params.keys()) {
        QString value = this->_params.value(key);

        if(key == "status") {
            this->setChecked(value != "0");
        } else if(key == "status_cmd") {
            QString result = Util::getCommandResult(value);
            this->setChecked(result.isEmpty() == false && result != "0");
        } else if(key == "check_cmd") {
            this->setCommand(value);
        } else if(key == "uncheck_cmd") {
            this->_uncheckCommand = value;
        }
    }

    if(this->isChecked()) {
        if(this->_params.contains("checked_title_cmd"))
            this->setText(Util::getCommandResult(this->_params.value("checked_title_cmd")));
        else if(this->_params.contains("checked_title"))
            this->setText(this->_params.value("checked_title"));
    }
    else {
        if(this->_params.contains("unchecked_title_cmd"))
            this->setText(Util::getCommandResult(this->_params.value("unchecked_title_cmd")));
        else if(this->_params.contains("unchecked_title"))
            this->setText(this->_params.value("unchecked_title"));
    }
}

void checkWidgetAction::runCommand() {
    if(!this->isChecked() && !this->_uncheckCommand.isEmpty())
        this->setCommand(this->_uncheckCommand);

    myWidgetAction::runCommand();
}
