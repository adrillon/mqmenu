# mqmenu

[**mqmenu**](http://drillon-ala.in/mqmenu) is a menu and application launcher that allows the creation of complex menus. It uses a simple-yet-powerful syntax that allows loops, nested submenus,... and can display special menu entries (with text areas, combo boxes,...).

It is inspired by jvinla's [myGtkMenu](https://sites.google.com/site/jvinla/mygtkmenu).

## Screenshots

![Screenshot 1](http://drillon-ala.in/mqmenu/mqmenu-screenshot-1.png)
![Screenshot 2](http://drillon-ala.in/mqmenu/mqmenu-screenshot-2.png)

## Download

### Source code

mqmenu is an open-source software published under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl.html). You can download it with Git by cloning `https://github.com/adrillon/mqmenu.git`. Alternatively, you can [browse the repository](http://github.com/adrillon/mqmenu). 

To build mqmenu from source, you need Qt 5. Run `qmake && make` in the `src` folder.

## Documentation

mqmenu ships with a manual page (`MQMENU(1)`). You can read it with `man` or [online](http://drillon-ala.in/mqmenu/man.html).

The file [exemple.menu](https://github.com/adrillon/mqmenu/blob/master/exemple.menu) covers the major features of mqmenu. You can read it to have a better understanding of the syntax, and see what it does by running `mqmenu -c exemple.menu`.
