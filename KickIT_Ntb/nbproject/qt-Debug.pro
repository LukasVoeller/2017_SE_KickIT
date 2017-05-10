# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = KickIT
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += BallTracking/BallTrackerImpl.cpp RowControl/MotorCommunicatorImpl.cpp RowControl/RowControllerImpl.cpp RowControl/TableControllerImpl.cpp VirtualKicker/BallTrackerMock.cpp VirtualKicker/TableControllerMock.cpp VirtualKicker/VirtualKickerWindow.cpp main.cpp
HEADERS += BallTracking/BallTrackerImpl.hpp BallTracking/BallTrackerInterface.hpp DataType/BallStatus.hpp DataType/Vec2.hpp RowControl/MotorCommunicatorImpl.hpp RowControl/MotorCommunicatorInterface.hpp RowControl/RowControllerImpl.hpp RowControl/RowControllerInterface.hpp RowControl/TableControllerImpl.hpp RowControl/TableControllerInterface.hpp VirtualKicker/BallTrackerMock.hpp VirtualKicker/TableControllerMock.hpp VirtualKicker/VirtualKicker.hpp VirtualKicker/VirtualKickerWindow.hpp
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
