#ifndef VIRTUALKICKERWINDOW_HPP
#define VIRTUALKICKERWINDOW_HPP

#include "../2_Control/TableControl/_TableControllerInterface.hpp"
#include <QWidget>
#include <cstdlib>
#include <vector>
#include <QtGui>
#include <QLabel>
#include <Qt>

#include "../5_DataType/BallStatus.hpp"
#include "../5_DataType/TableConfig.hpp"

class VirtualKickerWindow: public QWidget {


public:
	VirtualKickerWindow(bool showLines, bool drawBallPositionWithMouse);
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void setTableController(TableControllerInterface* t);


	int WINDOW_SIZE_X = 1024;
	int WINDOW_SIZE_Y = 768;

	//All dimension values in centimeter
	double SCALE;
	double TABLE_MARGIN;
	double TABLE_HEIGHT;
	double TABLE_WIDTH;
	double GOAL_SIZE;
	double GOAL_TO_KEEPER;
	double GOAL_TO_DEFENSE;
	double BALLDIAMETER;

public slots:
	void newBallStatus(BallStatus bs);

protected:
	TableConfig tconf;
	TableControllerInterface* tc;

	QPoint lastAdded;
	QPoint* topLeft;

	QLine* keeperBar;
	QPoint* keeper;

	QLine* defenseBar;
	QPoint* defense[2];

	QLine* ballMovementVector;

	std::vector<QPoint*> mouseTrail;
	QPoint* ball;

	QLabel* speedDisplay;


	bool showRows;
	bool drawBallPositionWithMouse;
};

#endif //VIRTUALKICKERWINDOW_HPP
