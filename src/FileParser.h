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

#ifndef __FILEPARSER_H__
#define __FILEPARSER_H__

#include <QFile>
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include "Entry.h"

namespace FileParser {
    typedef QStringList LineList;
    typedef QStringList::iterator Line;

    void parseFromFile(Entry* root, QString path);
    Line parseLines(Entry* root, Line start, Line end);
    Line parseEntry(Entry* e, Line start, Line end);

    int getLineLevel(Line line);
    Line getNextEmptyLine(Line start, Line end, bool empty = true);
    Line getNextNonEmptyLine(Line start, Line end);
    Line getNextParagraph(Line start, Line end);
}

#endif // __FILEPARSER_H__
