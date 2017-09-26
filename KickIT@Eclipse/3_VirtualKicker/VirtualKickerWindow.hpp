/**
 * @file VirtualKickerWindow.hpp
 * @brief
 */
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

/**VirtualKickerWindow class
 *
 */
class VirtualKickerWindow: public QWidget {


public:
	/**VirtualKickerWindow constructor
	 * @param (bool showLines, bool drawBallPositionWithMouse)
	 */
	VirtualKickerWindow(bool showLines, bool drawBallPositionWithMouse);

	/**paintEvent function
	 * @param (QPaintEvent *event)
	 *
	 */
	void paintEvent(QPaintEvent *event);

	/**mouseMoveEvent
	 * @param (QMouseEvent* e)
	 */
	void mouseMoveEvent(QMouseEvent* e);

	/**mouseReleaseEvent function
	 * @param (QMouseEvent* e)
	 */
	void mouseReleaseEvent(QMouseEvent* e);

	/**keyPressEvent function
	 * @param (QKeyEvent * event)
	 */
	void keyPressEvent(QKeyEvent * event);

	/**setTableController function
	 * @param (TableControllerInterface* t)
	 */
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

	QLabel* speedDisplay;

public slots:
	/**newBallStatus function
	 * @param (BallStatus bs)
	 */
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

	bool showRows;
	bool drawBallPositionWithMouse;
	float vMax;
	clock_t last_ball_update;
};

#endif //VIRTUALKICKERWINDOW_HPP
