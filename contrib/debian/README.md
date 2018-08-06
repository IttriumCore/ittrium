
Debian
====================
This directory contains files used to package ittriumd/ittrium-qt
for Debian-based Linux systems. If you compile ittriumd/ittrium-qt yourself, there are some useful files here.

## ittrium: URI support ##


ittrium-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ittrium-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ittriumqt binary to `/usr/bin`
and the `../../share/pixmaps/ittrium128.png` to `/usr/share/pixmaps`

ittrium-qt.protocol (KDE)

