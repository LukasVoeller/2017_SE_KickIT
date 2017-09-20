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

	# Mit dem Befehl "qmake -o Makefile ../KickIT@Eclipse.pro" wird im build Ordner das Makefile aktualisiert.
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

-------------------------------------------------- CLEAN PC (Ubuntu 16.04) --------------------------------------------------
1. ECLIPSE INSTALLIEREN
	Eclipse IDE for C/C++ Developers: 
	http://www.eclipse.org/downloads/packages/release/Neon/3
	
2. JDK & JRE INSTALLIEREN
	sudo apt-get install openjdk-8-jdk
	sudo apt-get install gcj-jre
	
3. GIT INSTALLIEREN & PROJEKT KLONEN
	sudo apt-get install git
	git clone https://github.com/LukasVoeller/SWE_2017_KickIT.git
	
4. QT INSTALLIEREN
	sudo apt-get install qt5-default
	
5. OPENCV DOWNLOADEN & INSTALLIEREN
	http://opencv.org/releases.html
	sudo apt-get install build-essential
	sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
	
	Aus dem entpackten Verzeichnis in der Konsole ausführen:
 		mkdir build
		cd build
  		cmake ..
 		make -j4
  		sudo make install
	
6. PYLON INSTALLIEREN
	Aus dem Pylon Verzeichnis in der Konsole ausführen:
		sudo tar -C /opt -xzf pylonSDK*.tar.gz
		chmod -x setup-usb.sh
		./setup-usb.sh

7. MAKEFILE ANPASSEN
...
STRIP         = strip

    # Pylon
        PYLON_ROOT ?= /opt/pylon5
        CXXFLAGS      += $(shell $(PYLON_ROOT)/bin/pylon-config --cflags) -DUSE_GIGE
        LIBS          += $(shell $(PYLON_ROOT)/bin/pylon-config --libs-rpath) $(shell $(PYLON_ROOT)/bin/pylon-config --libs)

    # Opencv
        CXXFLAGS      += $(shell pkg-config --cflags opencv)
        INCLUDEPATH   += /usr/local/include/opencv
        LIBS          += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui
        LIBS          += $(shell pkg-config --libs opencv)

####### Output directory
...

8. PCAN ADAPTER EINSTLLUNGEN
	cd /etc/network
	sudo nano interfaces
	
	Hinzufügen:
		auto can0
		iface can0 inet manual
		pre-up ip link set can0 type can bitrate 500000
		up /sbin/ifconfig can0 up
		down /sbin/ifconfig can0 down

	Danach:
		Strg+O
		Strg+X
		
9. DOXYGEN IN ECLIPSE INSTALLIEREN
	Download "A binary distribution for Linux x86-64"
	unter: http://www.stack.nl/%7Edimitri/doxygen/download.html

	In Konsole ausführen:
	tar -xzvf doxygen-1.8.8.linux.bin.tar.gz
	In den erzeugten Ordner navigieren
	./configure
	make install
