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

#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <QList>
#include <QMap>
#include <QString>

class Entry {
public:
    QList<Entry*>& entries();
    QMap<QString, QString>& params();

    Entry* parent() const;
private:
    Entry* _parent;
    QList<Entry*> _entries;
    QMap<QString, QString> _params;

    void setParent(Entry* parent);
};

#endif // __ENTRY_H__
