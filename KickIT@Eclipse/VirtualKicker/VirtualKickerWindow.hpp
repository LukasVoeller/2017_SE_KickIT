/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VirtualKicker.hpp
 * Author: student
 *
 * Created on 28. April 2017, 17:08
 */

#ifndef VIRTUALKICKERWINDOW_HPP
#define VIRTUALKICKERWINDOW_HPP

#include <Qt>
#include <QtGui>
#include <QWidget>
#include <vector>
#include <cstdlib>
#include "BallTrackerMock.hpp"

class VirtualKickerWindow : public QWidget{
    private:
        
        
        
        QPoint lastAdded;
        
        QPoint* topLeft;
        QPoint* bottomRight;
        
        QLine* keeperBar;
        QPoint* keeper;
        
        static const int WINDOW_SIZE_X = 1000;
        static const int WINDOW_SIZE_Y = 700;

        static const int TABLE_MARGIN = 60;
        static const int TABLE_WIDTH = WINDOW_SIZE_X - 2*TABLE_MARGIN;
        static const int TABLE_HEIGHT = WINDOW_SIZE_Y - 2*TABLE_MARGIN;
        
        BallTrackerMock* btm;
        std::vector<QPoint*> mouseTrail;
        
        
    public:
        VirtualKickerWindow();
        VirtualKickerWindow(BallTrackerMock* b);
        void paintEvent(QPaintEvent *event);
        void mouseMoveEvent(QMouseEvent* e);
        
        void mouseReleaseEvent(QMouseEvent* e);
        
        void setKeeper(float pos);

};

#endif /* VIRTUALKICKERWINDOW_HPP */

