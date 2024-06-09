#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>

#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FallingBall : public QGraphicsPolygonItem {
public:
    FallingBall(int xper);
    virtual void advance(int phase);
};

class SmokeFromHouse : public QGraphicsEllipseItem {
public:
    SmokeFromHouse(int x, int y);
    virtual void advance(int phase);
};

class Cloud : public QGraphicsEllipseItem {
public:
    Cloud(int x, int y);
    virtual void advance(int phase);
};

class Bird : public QGraphicsPolygonItem {
public:
    Bird(int x, int y);
    virtual void advance(int phase);
};

static bool Flag1 = false;
static int Fln = -1;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QGraphicsScene* scene;
    QPen pen;
    QTimer* animaTimer;
    QTimer* genTimer;
    QTimer* smokTimer;
    QTimer* windTimer;
    QTimer* gCloud;
    void onGenerator();
    void onSmok();
    void changing();
    void GenCloud();




public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
