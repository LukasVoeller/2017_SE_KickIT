#include "../3_VirtualKicker/VirtualKickerWindow.hpp"

#include "../5_DataType/TableConfig.hpp"
#include "../5_DataType/Vec2.hpp"

VirtualKickerWindow::VirtualKickerWindow() : tc(NULL) {
	setMouseTracking(true);

	SCALE = 1;
	TABLE_MARGIN = 60;
	TABLE_HEIGHT = tconf.tableHeight * SCALE;
	TABLE_WIDTH = tconf.tableWidth * SCALE;
	GOAL_SIZE = 100;
	GOAL_TO_KEEPER = tconf.distGoalToKeeper * SCALE;
	GOAL_TO_DEFENSE = tconf.distGoalToDefense * SCALE;

	ball = new QPoint();
	topLeft = new QPoint(TABLE_MARGIN, TABLE_MARGIN);

	keeperBar = new QLine(topLeft->x() + this->GOAL_TO_KEEPER, topLeft->y() - 30,
			topLeft->x() + this->GOAL_TO_KEEPER, topLeft->y() + this->TABLE_HEIGHT + 30);
	keeper = new QPoint(keeperBar->x1(), keeperBar->y1() + keeperBar->dy() / 2);

	defenseBar = new QLine(topLeft->x() + this->GOAL_TO_DEFENSE, topLeft->y() - 30,
			topLeft->x() + this->GOAL_TO_DEFENSE, topLeft->y() + this->TABLE_HEIGHT + 30);
	defense[0] = new QPoint(defenseBar->x1(),
			defenseBar->y1() + (defenseBar->dy() / 3) * 2);
	defense[1] = new QPoint(defenseBar->x1(),
			defenseBar->y1() + defenseBar->dy() / 3);
}

void VirtualKickerWindow::newBallStatus(BallStatus bs){
	std::cout << keeperBar->dx() << std::endl;
	this->ball->setX(bs.movement.x / this->SCALE);
	std::cout << "fsdfsd" << std::endl;
	this->ball->setY(bs.movement.y / this->SCALE);
	std::cout << "fsdfsd" << std::endl;
}

void VirtualKickerWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	QPen myPen(Qt::black, 2, Qt::SolidLine);
	painter.setPen(myPen);

	//Goal
	painter.drawRect(topLeft->x() - 30,
			topLeft->y() + this->TABLE_HEIGHT / 2 - this->GOAL_SIZE / 2, 30, this->GOAL_SIZE);
	//Table
	painter.drawRect(topLeft->x(), topLeft->y(), this->TABLE_WIDTH,
			this->TABLE_HEIGHT);

	painter.drawLine(*keeperBar);
	painter.drawLine(*defenseBar);

	painter.setPen(QPen(Qt::red, 20, Qt::DashDotLine, Qt::RoundCap));
	painter.drawPoint(*keeper);
	painter.drawPoint(*defense[0]);
	painter.drawPoint(*defense[1]);

	painter.setPen(QPen(Qt::blue, 20, Qt::DashDotLine, Qt::RoundCap));
	for (long unsigned int i = 0; i < mouseTrail.size(); i++) {
		painter.drawPoint(*mouseTrail[i]);
	}

	painter.drawPoint(*ball);
}

void VirtualKickerWindow::mouseMoveEvent(QMouseEvent* e) {
	if ((abs(e->pos().x() - lastAdded.x()) + abs(e->pos().y() - lastAdded.y()))
			> 20 && (e->buttons() & Qt::LeftButton)) {
		mouseTrail.push_back(new QPoint(e->pos().x(), e->pos().y()));
		lastAdded.setX(e->pos().x());
		lastAdded.setY(e->pos().y());
		tc->setBallPos(e->pos().x(), 178 - e->pos().y());
		repaint();
	}
}

void VirtualKickerWindow::mouseReleaseEvent(QMouseEvent* e) {
	mouseTrail.clear();
}


void VirtualKickerWindow::setTableController(TableControllerInterface* t) {
	tc = t;
}
