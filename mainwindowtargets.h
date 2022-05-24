#ifndef MAINWINDOWTARGETS_H
#define MAINWINDOWTARGETS_H

#include <QMainWindow>
#include<QPainter>
#include<QRgb>
#include<target.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowTargets; }
QT_END_NAMESPACE

class MainWindowTargets : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowTargets(QWidget *parent = nullptr);
    ~MainWindowTargets();
    void mousePressEvent(QMouseEvent *event);
    void gamefinish();
    void startgame();
    void restartgame();
private:
    Ui::MainWindowTargets *ui;
    Target *target;
    int miss, hit;
    int attempts;
private slots:
    void on_pbShot_clicked();
};
#endif // MAINWINDOWTARGETS_H
