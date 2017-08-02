Eclipse IDE for C/C++ Developers
Version: Neon.3 Release (4.6.3)

OHNE QT Plugin

Motor Nr1. Klein ohne Rotation 	-> PS01
Motor Nr2. Groß mit Rotation 	-> RS01

- bauen des projektes sollte ohne weiteres funktionieren
- wenn man neue dateien erstellt, müssen diese in der KickIT@Eclipse.pro datei mit eingetragen werden
	
	# .pro datei muss ausser den einträgen für HEADERS und SOURCES noch diese einträge enthalten
		TEMPLATE = app
		QT += widgets
		TARGET = KickIT@Eclipse
		INCLUDEPATH += .
		CONFIG += qt debug
		
		CONFIG += thread
		CONFIG += warn_off
		CONFIG += C++11

	# danach wird mit dem befehl "qmake -o Makefile KickIT@Eclipse.pro" das makefile aktualisiert
	# danach kann eclipse das projekt wieder bauen
	# im makefile müssen die die zeilen:
	
	# für pylon
	
	PYLON_ROOT ?= /opt/pylon5
	CXXFLAGS      += $(shell $(PYLON_ROOT)/bin/pylon-config --cflags) -DUSE_GIGE
	LIBS	      += $(shell $(PYLON_ROOT)/bin/pylon-config --libs-rpath) $(shell $(PYLON_ROOT)/bin/pylon-config --libs)

	# für opencv
	
	CXXFLAGS      += $(shell pkg-config --cflags opencv)
	INCLUDEPATH   += /usr/local/include/opencv
	LIBS          += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui
	LIBS          += $(shell pkg-config --libs opencv)

	ergänzt werden

- um das projekt in eclipse zu starten muss evtl unter Run -> Run Configurations unter KickIT_Eclipse im reiter Main das feld C/C++ Application angepasst 	weden. 
  (ausführbare datei liegt im hauptverzeichnis also muss hier "KickIT@Eclipse" eingetragen werden)

- um in eclipse die qt klassen bekannt zu machen kann man unter den projekteigenschaften bei C/C++ General unter Paths and Symbols mit dem button Add den 
  pfad des qt hauptverzeichnisses eintragen zb "/usr/include/x86_64-linux-gnu/qt5". ich habe noch häkchen bei "add to all configurations" und "add to all languages" gemacht
