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

#ifndef __MYPROXYSTYLE_H__
#define __MYPROXYSTYLE_H__

#include <QProxyStyle>
#include "Config.h"

/*
 * This style is used to change the icon size in the menus.
 * Code stolen from here : http://qt-project.org/forums/viewthread/31492/#138819
 */
class myProxyStyle : public QProxyStyle
{
    public:
        int pixelMetric(PixelMetric metric, const QStyleOption * option = 0, const QWidget * widget = 0 ) const {
            if (metric == QStyle::PM_SmallIconSize)
                return Config::iconSize;
            else
                return QProxyStyle::pixelMetric(metric, option, widget);
        }
};

#endif // __MYPROXYSTYLE_H__
