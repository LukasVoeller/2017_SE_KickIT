#ifndef VIRTUALKICKERWINDOW_HPP
#define VIRTUALKICKERWINDOW_HPP

#include "../RowControl/Interface/TableControllerInterface.hpp"
#include "../DataType/BallStatus.hpp"
#include "../DataType/TableConfig.hpp"
#include <QWidget>
#include <cstdlib>
#include <vector>
#include <QtGui>
#include <Qt>

class VirtualKickerWindow: public QWidget {

public:
	VirtualKickerWindow();
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void setTableController(TableControllerInterface* t);
	void newBallStatus(BallStatus bs);

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

protected:
	TableConfig tconf;
	TableControllerInterface* tc;

	QPoint lastAdded;
	QPoint* topLeft;

	QLine* keeperBar;
	QPoint* keeper;

	QLine* defenseBar;
	QPoint* defense[2];

	std::vector<QPoint*> mouseTrail;
	QPoint* ball;
};

#endif //VIRTUALKICKERWINDOW_HPP
