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

#ifndef __TEXTWIDGETACTION_H__
#define __TEXTWIDGETACTION_H__

#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QLineEdit>
#include <QLabel>
#include "myWidgetAction.h"

class textWidgetAction : public myWidgetAction {
    Q_OBJECT

public:
    textWidgetAction(QObject* parent);

    virtual void setParameters(QMap<QString, QString>& map);

    virtual void setText(const QString& text);
    virtual void setIcon(const QIcon& icon);

public slots:
    virtual void runCommand();

private:
    QWidget* _mainWidget;
    QHBoxLayout* _layout;
    QPushButton* _goButton;
    QLabel* _iconLabel;
    QLabel* _titleLabel;
    QLineEdit* _lineEdit;
};

#endif // __TEXTWIDGETACTION_H__
