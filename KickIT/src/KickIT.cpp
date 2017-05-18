//============================================================================
// Name        : HelloWorld.cpp
// Author      : Voeller Baumgartner Koschmann
// Version     :
// Copyright   : Property of Hochschule Osnabrueck
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <Qt>
#include <QWidget>
#include <QtGui>

using namespace std;

int main(int argc, char** argv) {
	QApplication a(argc, argv);
	QWidget w;
	w.setWindowTitle("testq");
	w.show();

	return a.exec();
}
