/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VirtualKicker.h
 * Author: student
 *
 * Created on 28. April 2017, 11:01
 */

#ifndef VIRTUALKICKER_H
#define VIRTUALKICKER_H

#include <QMainWindow>
#include <QtGui>
#include <QWidget>

const int WINDOW_SIZE_X = 1000;
const int WINDOW_SIZE_Y = 700;

const int TABLE_MARGIN = 60;
const int TABLE_WIDTH = WINDOW_SIZE_X - 2*TABLE_MARGIN;
const int TABLE_HEIGHT = WINDOW_SIZE_Y - 2*TABLE_MARGIN;

class VirtualKicker {
public:
    VirtualKicker();
    VirtualKicker(const VirtualKicker& orig);
    virtual ~VirtualKicker();
    
    void setKeeper(int pos);
    void paintEvent(QPaintEvent *event);
private:
    QPoint* topLeft;
    QPoint* bottomRight;
        
    QLine* keeperBar;
    QPoint* keeper;

};

#endif /* VIRTUALKICKER_H */

