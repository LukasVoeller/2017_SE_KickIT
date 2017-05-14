


#include "VirtualKickerWindow.hpp"

VirtualKickerWindow::VirtualKickerWindow(BallTrackerMock* b) {
    
//VirtualKickerWindow::VirtualKickerWindow() {
    setMouseTracking(true);
    //this->btm = b;
    topLeft = new QPoint(TABLE_MARGIN,TABLE_MARGIN);
    bottomRight = new QPoint( WINDOW_SIZE_X - TABLE_MARGIN, WINDOW_SIZE_Y - TABLE_MARGIN);
    keeperBar = new QLine(topLeft->x()+20,topLeft->y()-10,topLeft->x()+20, bottomRight->y() +10);
    keeper = new QPoint(keeperBar->x1(), keeperBar->y1() + keeperBar->dy()/2);
    
}

void VirtualKickerWindow::mouseMoveEvent(QMouseEvent* e){
    btm->mouseMove(e);
    
    if( (abs(e->pos().x() -lastAdded.x()) + abs(e->pos().y() - lastAdded.y()))  > 50 && e->buttons() & Qt::LeftButton){
        mouseTrail.push_back(new QPoint(e->pos().x(), e->pos().y()));
        lastAdded.setX(e->pos().x());
        lastAdded.setY(e->pos().y());
    }
    repaint();
}

void VirtualKickerWindow::mouseReleaseEvent(QMouseEvent* e) {
    mouseTrail.clear();
}


void VirtualKickerWindow::setKeeper(float pos){
    this->keeper->setX(pos);
    repaint();
}


void VirtualKickerWindow::paintEvent(QPaintEvent *event){
            
    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(this);
    

    //a simple line
    //painter.drawLine(1,1,100,100);

    //create a black pen that has solid line
    //and the width is 2.
    QPen myPen(Qt::black, 2, Qt::SolidLine);
    painter.setPen(myPen);
    //painter.drawLine(100,100,100,1);

    //draw a point
    //myPen.setColor(Qt::red);
    //painter.drawPoint(110,110);

    //draw a polygon
    //QPolygon polygon;
    //polygon << QPoint(130, 140) << QPoint(180, 170)
    //         << QPoint(180, 140) << QPoint(220, 110)
    //         << QPoint(140, 100);
    //painter.drawPolygon(polygon);

    //draw an ellipse
    //The setRenderHint() call enables antialiasing, telling QPainter to use different
    //color intensities on the edges to reduce the visual distortion that normally
    //occurs when the edges of a shape are converted into pixels
    //painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setPen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap));
    //painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

    //painter.drawEllipse(200, 80, 400, 240);


    painter.drawRect(topLeft->x(),topLeft->y() , WINDOW_SIZE_X-2*TABLE_MARGIN, WINDOW_SIZE_Y - 2*TABLE_MARGIN);
    painter.drawLine(*keeperBar);
    painter.setPen(QPen(Qt::blue, 20, Qt::DashDotLine, Qt::RoundCap));
    painter.drawPoint(*keeper);
    
    for(long unsigned int i = 0; i<mouseTrail.size(); i++){
        painter.drawPoint(*mouseTrail[i]);
        //std::cout << "p";
    }

}