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

#include "FileParser.h"

void FileParser::parseFromFile(Entry *root, QString path) {
    QFile menuFile(path);
    menuFile.open(QIODevice::ReadOnly | QIODevice::Text);

    FileParser::LineList menuLines;
    while(!menuFile.atEnd()) {
        QString line = menuFile.readLine();
        if(!line.simplified().startsWith(('#')))
            menuLines.push_back(line);
    }
    menuFile.close();

    FileParser::parseLines(root, menuLines.begin(), menuLines.end());
}

/*
 * Recursively parse the lines of a file to generate a tree of entries.
 *
 * For each line:
 *  - if the next line has a lower or equal indentation level, an entry is
 *    created, and parsed from the current line to the next empty line, and
 *    then added to the root entry
 *  - else, the lines directly following the current line (up to the next
 *    empty line) are parsed as submenu parameters, and all entries that
 *    follow are treated as subentries, until one of them has a lower
 *    indentation level
 *
 * Then, the indentation level of the line at which the parser currently is,
 * which is the next empty line (if parsing an entry), or the next line
 * with a lower indentation level (if parsing a submenu), is calculated.
 * If the result is lower than the level of the current line, it is returned.
 * Else, the line at which the parser currently is (AFTER parsing an entry or
 * a submenu) replaces the "current" (starting) line, and the loop continues.
 *
 * Returning the line at which the parser is (resultLine) allows the parser
 * that recursively called it to resume parsing at the line where the child
 * parser finished.
 */
FileParser::Line FileParser::parseLines(Entry* root, Line start, Line end) {
    if(start == end) return end;

    Line currentLine = start;
    for(; currentLine < end; ++currentLine) {
        if(currentLine->simplified().isEmpty()) currentLine = getNextNonEmptyLine(currentLine, end);

        Line nextParagraph = getNextParagraph(currentLine, end);
        int currentLevel = getLineLevel(currentLine);
        int nextLevel = (nextParagraph < end) ? getLineLevel(nextParagraph) : -1;
        Line resultLine = end;

        if(nextLevel <= currentLevel) {
            Entry* entry = new Entry();
            resultLine = parseEntry(entry, currentLine, end);
            root->entries().push_back(entry);
        }
        else {
            Entry* subEntry = new Entry();
            parseEntry(subEntry, currentLine, nextParagraph);
            resultLine = parseLines(subEntry, nextParagraph, end);
            root->entries().push_back(subEntry);
        }

        int resultLevel = (resultLine < end - 1) ? getLineLevel(resultLine+1) : -1;
        if(resultLevel < currentLevel)
            return resultLine;

        currentLine = resultLine;
    }

    return currentLine;
}

FileParser::Line FileParser::parseEntry(Entry* e, Line start, Line end) {
    if(start->simplified().startsWith("---")) {
        e->params().insert("type", "section");
    }

    for(Line current = start; current < getNextEmptyLine(start, end); ++current) {
        QString parameter = current->simplified();
        if(parameter.contains(':')) {
            QString key = parameter.split(':')[0];
            QString val = parameter.remove(0, key.length() + 1);
            e->params().insert(key.simplified(), val.simplified());
        } else {
            e->params().insert("name", parameter.simplified());
        }
    }
    return getNextEmptyLine(start, end);
}

/*
 * The (identation) level of a line is the number of tabs at the beginning.
 */
int FileParser::getLineLevel(Line line) {
    int level = 0;
    while((*line)[level] == '\t') ++level;
    return level;
}

FileParser::Line FileParser::getNextEmptyLine(Line start, Line end, bool empty) {
    for(Line currentLine = start + 1; currentLine < end; ++currentLine) {
        if(( empty &&  currentLine->simplified().isEmpty()) ||
           (!empty && !currentLine->simplified().isEmpty()))
            return currentLine;
    }
    return end;
}

FileParser::Line FileParser::getNextNonEmptyLine(Line start, Line end) {
    return getNextEmptyLine(start, end, false);
}

FileParser::Line FileParser::getNextParagraph(Line start, Line end) {
    return getNextNonEmptyLine(getNextEmptyLine(start, end), end);
}
