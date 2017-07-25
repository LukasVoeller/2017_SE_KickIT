#ifndef VIRTUALKICKERWINDOW_HPP
#define VIRTUALKICKERWINDOW_HPP

#include <Qt>
#include <QtGui>
#include <vector>
#include <QWidget>
#include <cstdlib>

#include "../RowControl/InterfaceTableController.hpp"

class VirtualKickerWindow : public QWidget{

    public:
        VirtualKickerWindow();
        
        void paintEvent(QPaintEvent *event);
        void mouseMoveEvent(QMouseEvent* e);
        void mouseReleaseEvent(QMouseEvent* e);
        
        void setKeeper(float pos);
        void setDefense(float pos);
        void setTableController(InterfaceTableController* t);
        
        Vec2* getKeeperPositionalVector();
        Vec2* getDefensePositionalVector();
        float getDDist();
        
        static const int WINDOW_SIZE_X = 1024;
		static const int WINDOW_SIZE_Y = 768;

		static const int TABLE_MARGIN = 60;
		//static const int TABLE_WIDTH = WINDOW_SIZE_X - 2*TABLE_MARGIN;
		//static const int TABLE_HEIGHT = WINDOW_SIZE_Y - 2*TABLE_MARGIN;
		static const double TABLE_HEIGHT = 68 * 7;
		static const double TABLE_WIDTH = 111.5 * 7;

    private:
        InterfaceTableController* tc;

        QPoint lastAdded;
        QPoint* topLeft;
        
        QLine* keeperBar;
        QPoint* keeper;
        
        QLine* defenseBar;
        QPoint* defense[2];

        std::vector<QPoint*> mouseTrail;
};

#endif /* VIRTUALKICKERWINDOW_HPP */

