Eclipse IDE for C/C++ Developers
Version: Neon.3 Release (4.6.3)

Motor Nr1. Klein ohne Rotation 	-> PS01
Motor Nr2. Groß mit Rotation 	-> RS01

OHNE QT Plugin

- Bauen des projektes sollte ohne weiteres funktionieren.
- Wenn man eine neue Datei erstellt, muss diese in der KickIT@Eclipse.pro Datei immer von Hand eingetragen werden.
	
	# .pro Datei muss ausser den Einträgen für HEADERS und SOURCES noch diese Einträge enthalten:
		TEMPLATE = app
		QT += widgets
		TARGET = KickIT@Eclipse
		INCLUDEPATH += .
		CONFIG += qt debug
		
		CONFIG += thread
		CONFIG += warn_off
		CONFIG += C++11

	# Mit dem Befehl "qmake -o Makefile KickIT@Eclipse.pro" wird das Makefile aktualisiert.
	# Danach kann Eclipse das Projekt wieder bauen. Im Makefile müssen desweiteren die Zeilen:
	
	# Pylon
		PYLON_ROOT ?= /opt/pylon5
		CXXFLAGS      += $(shell $(PYLON_ROOT)/bin/pylon-config --cflags) -DUSE_GIGE
		LIBS	      += $(shell $(PYLON_ROOT)/bin/pylon-config --libs-rpath) $(shell $(PYLON_ROOT)/bin/pylon-config --libs)

	# Opencv
		CXXFLAGS      += $(shell pkg-config --cflags opencv)
		INCLUDEPATH   += /usr/local/include/opencv
		LIBS          += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui
		LIBS          += $(shell pkg-config --libs opencv)

	# ergänzt werden.

- Um das Projekt in Eclipse zu starten muss evtl. in Run->Run Configurations unter KickIT_Eclipse im Reiter Main das Feld C/C++ Application angepasst werden. 
  (ausführbare Datei liegt im Hauptverzeichnis also muss hier "KickIT@Eclipse" eingetragen werden)

- Um in Eclipse die QT Klassen bekannt zu machen, kann man unter den Projekteigenschaften bei "C/C++ General" unter "Paths and Symbols" mit dem Button "Add" den 
  Pfad des QT Hauptverzeichnisses eintragen z.B. "/usr/include/x86_64-linux-gnu/qt5".
- Ich habe noch Häkchen bei "add to all configurations" und "add to all languages" gemacht.
