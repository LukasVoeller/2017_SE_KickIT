#include "../3_VirtualKicker/VirtualKickerWindow.hpp"

#include "../5_DataType/TableConfig.hpp"
#include "../5_DataType/Vec2.hpp"

VirtualKickerWindow::VirtualKickerWindow(bool showRows, bool drawBallPositionWithMouse) : tc(NULL), speedDisplay(NULL) {
	setMouseTracking(true);
	this->showRows = showRows;
	this->drawBallPositionWithMouse = drawBallPositionWithMouse;
	BALLDIAMETER = 10;
	SCALE = 1;
	TABLE_MARGIN = 60;
	TABLE_HEIGHT = tconf.tableHeight * SCALE;
	TABLE_WIDTH = tconf.tableWidth * SCALE;
	GOAL_SIZE = 150;
	GOAL_TO_KEEPER = tconf.distGoalToKeeper * SCALE;
	GOAL_TO_DEFENSE = tconf.distGoalToDefense * SCALE;
	ball = new QPoint();
	topLeft = new QPoint(TABLE_MARGIN, TABLE_MARGIN);
	keeperBar = new QLine(topLeft->x() + this->GOAL_TO_KEEPER, topLeft->y() - 30,topLeft->x() + this->GOAL_TO_KEEPER, topLeft->y() + this->TABLE_HEIGHT + 30);
	keeper = new QPoint(keeperBar->x1(), keeperBar->y1() + keeperBar->dy() / 2);
	defenseBar = new QLine(topLeft->x() + this->GOAL_TO_DEFENSE, topLeft->y() - 30, topLeft->x() + this->GOAL_TO_DEFENSE, topLeft->y() + this->TABLE_HEIGHT + 30);
	defense[0] = new QPoint(defenseBar->x1(), defenseBar->y1() + (defenseBar->dy() / 3) * 2);
	defense[1] = new QPoint(defenseBar->x1(), defenseBar->y1() + defenseBar->dy() / 3);
	ballMovementVector = new QLine();
	vMax = 0;
	last_ball_update = 0;
}

void VirtualKickerWindow::newBallStatus(BallStatus bs){
	int ball_x = bs.position.x / this->SCALE + TABLE_MARGIN;
	int ball_y = bs.position.y / this->SCALE + TABLE_MARGIN;
	this->ball->setX(ball_x);
	this->ball->setY(ball_y);
	ballMovementVector->setLine(ball_x, ball_y, ball_x + bs.movement.x/5, ball_y + bs.movement.y/5 );
	clock_t up_to_date = clock();
	float v = bs.movement.length()*0.0036;
	if(abs(up_to_date-last_ball_update)>CLOCKS_PER_SEC*3 || v>vMax){
		vMax = v;
		last_ball_update = up_to_date;
		std::string text(std::to_string(v));
		text+=" km/h";
		if(speedDisplay!=NULL)speedDisplay->setText(text.c_str());
	}
	repaint();

}

void VirtualKickerWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	QPen myPen(Qt::black, 2, Qt::SolidLine);
	painter.setPen(myPen);
	//Goal
	painter.drawRect(topLeft->x() - 30, topLeft->y() + this->TABLE_HEIGHT / 2 - this->GOAL_SIZE / 2, 30, this->GOAL_SIZE);
	//Table
	painter.drawRect(topLeft->x(), topLeft->y(), this->TABLE_WIDTH, this->TABLE_HEIGHT);

	if(this->showRows){
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

	}
	painter.setPen(QPen(Qt::darkCyan, 10, Qt::DashDotLine, Qt::RoundCap));
	painter.drawLine(*ballMovementVector);
	painter.setPen(QPen(Qt::red, BALLDIAMETER, Qt::DashDotLine, Qt::RoundCap));
	painter.drawPoint(*ball);
}

void VirtualKickerWindow::mouseMoveEvent(QMouseEvent* e) {
	if(this->drawBallPositionWithMouse){
		if ((abs(e->pos().x() - lastAdded.x()) + abs(e->pos().y() - lastAdded.y()))
				> 20 && (e->buttons() & Qt::LeftButton)) {
			mouseTrail.push_back(new QPoint(e->pos().x(), e->pos().y()));
			lastAdded.setX(e->pos().x());
			lastAdded.setY(e->pos().y());
			tc->setBallPos(e->pos().x(), 178 - e->pos().y());
			repaint();
		}
	}
}

void VirtualKickerWindow::mouseReleaseEvent(QMouseEvent* e) {
	mouseTrail.clear();
}


void VirtualKickerWindow::setTableController(TableControllerInterface* t) {
	tc = t;
}

void VirtualKickerWindow::keyPressEvent(QKeyEvent * event){
	if( event->key() == Qt::Key_S ){
		if(speedDisplay!=NULL) speedDisplay->show();
	}
}
