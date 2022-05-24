#ifndef TARGET_H
#define TARGET_H

#include <QWidget>
#include <QPainter>
#include <vector>
class Target : public QWidget
{
    Q_OBJECT
public:
    explicit Target(int R = 0, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*)
    {
        QPainter painter1(this);
        double h = this->height();
        double w = this->width();
        painter1.setPen(QPen(Qt::black, 3));
        h/=2;
        w/=2;
        painter1.translate(w,h);
        painter1.setBrush(QBrush(Qt::black, Qt::Dense4Pattern));
        painter1.drawPie(0,-rad, 2*rad, 2*rad,0,180*16);
        painter1.drawRect(-rad, 0, rad,rad);
        painter1.setBrush(QColor(240, 240, 240));
        painter1.drawPie(-2*rad,0,2*rad,2*rad, 0, 90*16);
        painter1.setPen(Qt::NoPen);
        painter1.drawEllipse(-2*rad,0,2*rad,2*rad);
        painter1.setPen(QPen(Qt::red, 3));
        for(int i = 0; i < points.size(); i++){
            painter1.drawPoint(points[i]);
        }
    }
    void restartgame(int r);
    bool checkshot(QPointF shot);
    bool shotbymouse();
    bool shotbybutton(int x, int y);
signals:
private:
    int rad;
    std::vector<QPointF> points;
};

#endif // TARGET_H
