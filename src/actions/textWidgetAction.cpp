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

#include "textWidgetAction.h"

textWidgetAction::textWidgetAction(QObject* parent)
 : myWidgetAction(parent)
{
    this->_mainWidget = new QWidget();
    this->_iconLabel = new QLabel();
    this->_titleLabel = new QLabel();
    this->_lineEdit = new QLineEdit();
    this->_goButton = new QPushButton();
    this->_goButton->setVisible(false);
    this->_layout = new QHBoxLayout();

    this->_layout->addWidget(this->_iconLabel);
    this->_layout->addWidget(this->_titleLabel);
    this->_layout->addWidget(this->_lineEdit);
    this->_layout->addWidget(this->_goButton);
    this->_mainWidget->setLayout(this->_layout);
    this->setDefaultWidget(this->_mainWidget);

    connect(this->_goButton, SIGNAL(released()), this, SLOT(trigger()));
    connect(this->_lineEdit, SIGNAL(returnPressed()), this, SLOT(trigger()));
}

void textWidgetAction::setParameters(QMap<QString, QString> &map) {
    myWidgetAction::setParameters(map);

    for(auto key : this->_params.keys()) {
        QString value = this->_params.value(key);

        if(key == "text")
            this->_lineEdit->setText(value);
        else if(key == "text_cmd")
            this->_lineEdit->setText(Util::getCommandResult(value));
		else if(key == "phtxt")
			this->_lineEdit->setPlaceholderText(value);
		else if(key == "phtxt_cmd")
			this->_lineEdit->setPlaceholderText(Util::getCommandResult(value));
        else if(key == "button") {
            this->_goButton->setVisible(true);
            this->_goButton->setText(value);
        }
        else if(key == "button_cmd") {
            this->_goButton->setVisible(true);
            this->_goButton->setText(Util::getCommandResult(value));
        }
    }
}

void textWidgetAction::setText(const QString &text) {
    this->_titleLabel->setText(text);
}

void textWidgetAction::setIcon(const QIcon &icon) {
    this->_iconLabel->setPixmap(icon.pixmap(Config::iconSize, Config::iconSize));
}

void textWidgetAction::runCommand() {
    this->_command = this->_command.replace("%s", this->_lineEdit->text());
    myWidgetAction::runCommand();
}
