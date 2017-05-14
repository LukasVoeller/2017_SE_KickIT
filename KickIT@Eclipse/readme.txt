Eclipse IDE for C/C++ Developers
Version: Neon.3 Release (4.6.3)

OHNE QT Plugin



- bauen des projektes sollte ohne weiteres funktionieren
- wenn man neue dateien erstellt, müssen diese in der KickIT@Eclipse.pro datei mit eingetragen werden
	# danach wird mit dem befehl "qmake -o Makefile KickIT@Eclipse.pro" das makefile aktualisiert
	# danach kann eclipse das projekt wieder bauen

- um das projekt in eclipse zu starten muss evtl unter Run -> Run Configurations unter KickIT_Eclipse im reiter Main das feld C/C++ Application angepasst 	weden. (ausführbare datei liegt im hauptverzeichnis also muss hier "KickIT@Eclipse" eingetragen werden)

- um in eclipse die qt klassen bekannt zu machen kann man unter den projekteigenschaften bei C/C++ General unter Paths and Symbols mit dem button Add den 
  pfad des qt hauptverzeichnisses eintragen zb "/usr/include/x86_64-linux-gnu/qt5". ich habe noch häkchen bei "add to all configurations" und "add to all languages" gemacht