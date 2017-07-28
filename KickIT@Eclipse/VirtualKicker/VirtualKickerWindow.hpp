#ifndef VIRTUALKICKERWINDOW_HPP
#define VIRTUALKICKERWINDOW_HPP

#include <Qt>
#include <QtGui>
#include <vector>
#include <QWidget>
#include <cstdlib>

#include "../RowControl/Interface/TableControllerInterface.hpp"

class VirtualKickerWindow: public QWidget {

public:
	VirtualKickerWindow();

	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);

	void setKeeper(float pos);
	void setDefense(float pos);
	void setTableController(TableControllerInterface* t);

	Vec2* getKeeperPositionalVector();
	Vec2* getDefensePositionalVector();
	float getDDist();

	static const int WINDOW_SIZE_X = 1024;
	static const int WINDOW_SIZE_Y = 768;

	//All dimension values in centimeter
	static const int SCALE = 7;
	static const int TABLE_MARGIN = 60;
	static const double TABLE_HEIGHT = 68 * SCALE;
	static const double TABLE_WIDTH = 111.5 * SCALE;
	static const double GOAL_SIZE = 21 * SCALE;
	static const double GOAL_TO_KEEPER = 3.5 * SCALE;
	static const double GOAL_TO_DEFENSE = 18.5 * SCALE;

private:
	TableControllerInterface* tc;

	QPoint lastAdded;
	QPoint* topLeft;

	QLine* keeperBar;
	QPoint* keeper;

	QLine* defenseBar;
	QPoint* defense[2];

	std::vector<QPoint*> mouseTrail;
};

#endif /* VIRTUALKICKERWINDOW_HPP */

