#include "target.h"
#include <iostream>

Target::Target(int R , QWidget *parent) : QWidget(parent)
{
    rad = R;
    this->setCursor(Qt::CrossCursor);
    this->setMinimumHeight(3*rad);
    this->setMinimumWidth(3*rad);
}
bool Target::checkshot(QPointF shot){
    points.push_back(shot);
    this->repaint();
    if((shot.y()*shot.y() + (shot.x()-rad)*(shot.x()-rad)<=rad*rad && shot.y()<=0 && shot.y()>=-rad)||(((shot.y()-rad)*(shot.y()-rad) + (shot.x()+rad)*(shot.x()+rad))>=rad*rad && shot.x()>=-rad && shot.y()<=rad && shot.y()>=0 && shot.x()<=0)){
        return true;
    }else{
        return false;
    }
}
bool Target::shotbymouse(){
    QPointF shot = mapFromGlobal(QCursor().pos());
    shot.setX(shot.x() - (this->width())/2);
    shot.setY(shot.y() - (this->height())/2);
    return checkshot(shot);
}

bool Target::shotbybutton(int x, int y){
    QPointF shot;
    shot.setX(x);
    shot.setY(y);
    return checkshot(shot);
}

void Target::restartgame(int r){
    points.clear();
    rad = r;
    this->setMinimumHeight(3*rad);
    this->setMinimumWidth(3*rad);
    this->repaint();
}
