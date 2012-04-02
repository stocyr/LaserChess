LaserChess
==========

This is a game for our programming class.
It's written in C and is a clone of the game Khet (http://www.khet.com/).

Release Notes
-------------

Release history:

* **V0.1**: *Pflichtenheft definiert, Spielregeln und Umfang klar*

* **v0.2**: *Flowchart entwickelt, Module aufgelistet, Arbeitsplan erstellt*

* **v1.0**: *Erste voll funktionstüchtige Version*


Links
-----------

* Game: http://www.khet.com/

* Game Anleitung: http://www.khet.com/rules_english.pdf

* set up *git*: http://help.github.com/win-set-up-git/

* short introduction: http://spheredev.org/wiki/Git_for_the_lazy

* the git book: http://progit.org/book/


Git
-----------

* Editor auf Notepad++ �ndern: git config --global core.editor "'C:/Program Files (x86)/Notepad++/notepad++.exe' -multiInst -notabbar -nosession -noPlugin"

* Vereinfachte schematische Darstellung des Git Version Control Systems:

![Git system 1](http://de.whygitisbetterthanx.com/images/local-remote.png)

Hier ist zu beachten: Anstatt mit `git fetch` das Repository herunter zu laden und dann mit `git merge` mit dem Arbeitsverzeichnis zu synchronisieren,
nutzen wir den Befehl `git pull`, der macht das auf einmal.

* Mit `git add .` k�nnen s�mtliche �nderungen (ausser Files l�schen und hinzuf�gen) auf einmal zur *staging area* hinzugef�gt werden.

* Mit `git commit -a -m 'bemerkung zu diesem commit'` kann direkt vom Arbeitsverzeichnis ein commit gemacht werden (ohne `git add`).