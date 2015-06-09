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

#include "Util.h"

void Util::runCommand(const QString &command, bool terminal, bool hold) {
    QString exec = (terminal ? (hold ? Config::holdTerminal : Config::terminal) : Config::shell);
    QString cmd = exec.split(' ').at(0);
    QStringList args = exec.split(' '); args.removeFirst();
    args.append(command);

    QProcess* p = new QProcess();
    p->start(cmd, args);
}

QString Util::getCommandResult(const QString &command, bool simplify) {
    QString cmd = Config::shell.split(' ').at(0);
    QStringList args = Config::shell.split(' '); args.removeFirst();
    args.append(command);

    QProcess* p = new QProcess();
    p->start(cmd, args);
    QString result;
    while(p->waitForFinished())
          result = p->readAllStandardOutput();

    return simplify ? result.simplified() : result;
}

/*
 * Get a list of values (split it if its a string, get each line if its a command)
 * The regex allows to split the string at each space, except when inside double quotes.
 * Stolen from http://stackoverflow.com/questions/1310473/regex-matching-spaces-but-not-in-strings
 */
QStringList Util::splitList(const QString &str, bool command) {
    QStringList values;
    if(str.isEmpty()) return values;

    if(command)
        values = Util::getCommandResult(str, false).split('\n');
    else {
        QRegExp quotedblRegex = QRegExp(" +(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");
        values = str.split(quotedblRegex);
        for(int i = 0; i < values.length(); ++i) {
            if(values[i].startsWith('"') && values[i].endsWith('"'))
                values[i] = values[i].mid(1, values[i].length() - 2);
        }
    }

    if(values.last().isEmpty())
        values.removeLast();

    return values;
}

QStringList Util::getValues(const QMap<QString, QString> &params, const QString &manualParameter, const QString &cmdParameter) {
    QStringList values;
    values.append(splitList(params.value(manualParameter), false));
    values.append(splitList(params.value(cmdParameter), true));
    return values;
}
