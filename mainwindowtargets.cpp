#include "mainwindowtargets.h"
#include "ui_mainwindowtargets.h"
#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <iostream>

MainWindowTargets::MainWindowTargets(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowTargets)
{
    ui->setupUi(this);
    target = new Target();
    startgame();
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(target, 2, 0, 7, 8);
    layout->addWidget(ui->lAttempts, 0,7,2,1);
    layout->addWidget(ui->pbShot, 0, 6, 2, 1);
    layout->addWidget(ui->lOntarget, 0,1,1,1);
    layout->addWidget(ui->lcdNOntarget, 0,0,1,1);
    layout->addWidget(ui->lMiss, 1,1,1,1);
    layout->addWidget(ui->lcdNMiss,1,0,1,1);
    layout->addWidget(ui->leX, 0,3,2,1);
    layout->addWidget(ui->leY, 0,5,2,1);
    layout->addWidget(ui->lX, 0,2,2,1);
    layout->addWidget(ui->lY, 0,4,2,1);
    ui->lX->setText("введите x:");
    ui->lY->setText("введите y:");
    ui->pbShot->setText("Выстрел!");
    ui->lMiss->setText("Количество промахов");
    ui->lOntarget->setText("Количество попаданий");
    ui->centralwidget->setLayout(layout);
    miss = 0;
    hit = 0;
}
void MainWindowTargets::startgame(){
    int r;
    bool ok = false;
    while (!ok) {
        QString rad = QInputDialog::getText(this, tr("Введите радиус!"),
                                             tr("Радиус:"), QLineEdit::Normal,
                                             "100", &ok);
        if(ok && !rad.isEmpty()){
            if(rad.toInt()){
            r = rad.toInt();
            }else{
               QMessageBox::question(this, "Ошибка!", "Радиус обязательно должен быть введен числом!", QMessageBox::Yes);
               ok = false;
            }
        }else{
            QMessageBox::question(this, "Ошибка!", "Радиус обязательно должен быть введен!", QMessageBox::Yes);
        }
    }
    ok = false;
    while(!ok){
        QString att = QInputDialog::getText(this, tr("Введите количество выстрелов!"),
                                            tr("Выстрелы:"), QLineEdit::Normal,
                                            "10", &ok);
        if(ok && att.toInt()){
            attempts = att.toInt();
        }else{
            ok = false;
            QMessageBox::question(this, "Ошибка!", "Проверьте корректность ввода!", QMessageBox::Yes);
        }
    }
    ui->lAttempts->setText("Попыок осталось: "+ QString::number(attempts));
    target->restartgame(r);
}

void MainWindowTargets::restartgame(){
    ui->lcdNMiss->display(0);
    ui->lcdNOntarget->display(0);
    ui->leX->clear();
    ui->leY->clear();
    miss = 0;
    hit = 0;
    startgame();
}

MainWindowTargets::~MainWindowTargets()
{
    delete ui;
}

void MainWindowTargets::mousePressEvent(QMouseEvent *event){
    if(target->underMouse()){
        if(target->shotbymouse()){
            hit++;
            ui->lcdNOntarget->display(hit);
        }else{
            miss++;
            ui->lcdNMiss->display(miss);
        }
        gamefinish();
    }
    Q_UNUSED(event);
}
void MainWindowTargets::gamefinish(){
    attempts--;
    ui->lAttempts->setText("Попыок осталось: "+ QString::number(attempts));
    if(attempts==0){
        if(QMessageBox::question(this, "Конец!", "Вы попали "+QString::number(hit)+" раз.Желаете попробовать снова?", QMessageBox::No|QMessageBox::Yes) == QMessageBox::No){
            QApplication::quit();
        }else{
            restartgame();
        }
    }
}

void MainWindowTargets::on_pbShot_clicked()
{
    QString x;
    QString y;
    x = ui->leX->text();
    y = ui->leY->text();
    if(!x.isEmpty() && !y.isEmpty() && y.toInt() && x.toInt()){
        if(target->shotbybutton(x.toInt(), -(y.toInt()))){
            hit++;
            ui->lcdNOntarget->display(hit);
        }else{
            miss++;
            ui->lcdNMiss->display(miss);
        }
        gamefinish();
    }else{
        QMessageBox::question(this, "Ошибка!", "Проверьте правильность ввода данных!", QMessageBox::Yes);
    }
    ui->leX->clear();
    ui->leY->clear();

}
