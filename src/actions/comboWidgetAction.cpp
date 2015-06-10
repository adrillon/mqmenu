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

#include "comboWidgetAction.h"

comboWidgetAction::comboWidgetAction(QObject *parent)
 : myWidgetAction(parent)
{
    this->_mainWidget = new QWidget();
    this->_iconLabel = new QLabel();
    this->_titleLabel = new QLabel();
    this->_titleLabel->setAlignment(Qt::AlignRight);
    this->_comboBox = new QComboBox();
    this->_layout = new QHBoxLayout();

    this->_layout->addWidget(this->_iconLabel);
    this->_layout->addWidget(this->_titleLabel);
    this->_layout->addWidget(this->_comboBox);
    this->_mainWidget->setLayout(this->_layout);
    this->setDefaultWidget(this->_mainWidget);
}

void comboWidgetAction::setParameters(QMap<QString, QString> &map) {
    myWidgetAction::setParameters(map);

    this->_comboValues = Util::getValues(map, "combo_values", "combo_values_cmd");
    this->_comboIcons = Util::getValues(map, "combo_icons", "combo_icons_cmd");
    this->_comboTexts = Util::getValues(map, "combo_texts", "combo_texts_cmd");

    for(int i = 0; i < this->_comboValues.count(); ++i) {
        QString text = (this->_comboTexts.count() <= i) ? this->_comboValues.at(i) : this->_comboTexts.at(i);

        if(this->_comboIcons.count() <= i)
            this->_comboBox->addItem(text);
        else
            this->_comboBox->addItem(QIcon(this->_comboIcons.at(i)), text);
    }

    this->_comboBox->setCurrentIndex(map.value("default_index", "0").toInt());
    if(map.contains("default_index_cmd"))
        this->_comboBox->setCurrentIndex(Util::getCommandResult(map.value("default_index_cmd")).toInt());

    if(map.value("reselect", "1") == "1")
        connect(this->_comboBox, SIGNAL(activated(int)), this, SLOT(trigger()));
    else
        connect(this->_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(trigger()));
}

void comboWidgetAction::runCommand() {
    this->_command = this->_command.replace("%s", this->_comboValues.at(this->_comboBox->currentIndex()));
    this->_command = this->_command.replace("%t", this->_comboBox->currentText());
    myWidgetAction::runCommand();
}

void comboWidgetAction::setIcon(const QIcon &icon) {
    this->_iconLabel->setPixmap(icon.pixmap(Config::iconSize, Config::iconSize));
}

void comboWidgetAction::setText(const QString &text) {
    this->_titleLabel->setText(text);
}
