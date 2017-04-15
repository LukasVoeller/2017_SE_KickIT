PYLON_ROOT ?= /opt/pylon5
OPENCV_ROOT ?= /usr/lib/x86_64-linux-gnu
QT4_ROOT ?= /usr/include/qt4


CXXFLAGS =	-O3 -g -w -Wall -fmessage-length=0
CXXFLAGS += $(shell pkg-config --cflags opencv)
CXXFLAGS += $(shell pkg-config --cflags QtGui)
CXXFLAGS += $(shell pkg-config --cflags QtCore)
CPPFLAGS += $(shell $(PYLON_ROOT)/bin/pylon-config --cflags) -DUSE_GIGE
OBJS =		Test6Torwart.o

LIBS = $(shell $(PYLON_ROOT)/bin/pylon-config --libs-rpath) $(shell $(PYLON_ROOT)/bin/pylon-config --libs)
LIBS += $(shell &(OPENCV_ROOT)-config -- libs-rpath)
LIBS += $(shell pkg-config --libs opencv)
LIBS += $(shell pkg-config --libs QtGui)
LIBS += $(shell pkg-config --libs QtCore)

TARGET =	Test6Torwart

$(TARGET):	$(OBJS) $(USER_OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	