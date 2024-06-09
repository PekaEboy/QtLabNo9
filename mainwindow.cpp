#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPolygonF tria;
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 800, 600, this);
    ui->gvScene->setScene(scene);
    scene->setBackgroundBrush(QColor(0x0C3B66));
    scene->addRect(scene->sceneRect());
    animaTimer = new QTimer(this);
    connect(animaTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    animaTimer->start(1000/60);

    tria.append(QPoint(ui->gvScene->width()-230, ui->gvScene->height()-125));
    tria.append(QPoint(ui->gvScene->width()-120, ui->gvScene->height()-125));
    tria.append(QPoint(ui->gvScene->width()-175, ui->gvScene->height()-150));
    scene->addEllipse(0,ui->gvScene->height()-100,800,200, pen, Qt::white);
    scene->addRect(ui->gvScene->width()-200, ui->gvScene->height()-125, 50, 50, pen, Qt::black);
    scene->addPolygon(tria, pen, Qt::black);
    scene->addRect(ui->gvScene->width()-160, ui->gvScene->height()-150, 10, 20, pen, Qt::black);
    smokTimer = new QTimer(this);
    connect(smokTimer, &smokTimer->timeout, this, &MainWindow::onSmok);
    smokTimer->start(1200);
    genTimer = new QTimer(this);
    connect(genTimer, &genTimer->timeout, this, &MainWindow::onGenerator);
    genTimer->start(1000);
    windTimer = new QTimer(this);
    connect(windTimer, &windTimer->timeout, this, &MainWindow::changing);
    windTimer->start(5000);
    gCloud = new QTimer(this);
    connect(gCloud, &gCloud->timeout, this, &MainWindow::GenCloud);
    gCloud->start(6000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changing() {
    Flag1=!Flag1;
    if(Flag1){
        Fln*=-1;
    }
}

FallingBall::FallingBall(int xper) : QGraphicsPolygonItem(0) {
    //QColor color = QColor(rand()%255, rand()%255, rand()%255);
    QPolygonF snowF;
    QPen snowpe;
    snowpe.setColor(Qt::white);
    snowF.append(QPoint(4, 0));
    snowF.append(QPoint(6, 0));
    snowF.append(QPoint(6, 4));
    snowF.append(QPoint(8, 2));
    snowF.append(QPoint(10, 4));
    snowF.append(QPoint(7, 5));
    snowF.append(QPoint(10, 7));
    snowF.append(QPoint(8, 9));
    snowF.append(QPoint(6, 6));
    snowF.append(QPoint(6, 10));
    snowF.append(QPoint(4, 10));
    snowF.append(QPoint(4, 6));
    snowF.append(QPoint(2, 9));
    snowF.append(QPoint(0, 7));
    snowF.append(QPoint(3, 5));
    snowF.append(QPoint(0, 4));
    snowF.append(QPoint(2, 2));
    snowF.append(QPoint(4, 4));
    setBrush(Qt::white);
    setPolygon(snowF);
    setPen(snowpe);
    setScale(1.8);
    setPos(rand()%(xper-10), 0);
}

SmokeFromHouse::SmokeFromHouse(int x, int y) : QGraphicsEllipseItem(0) {
    setBrush(QColor(0x302c28));
    setRect(0, 0, 10, 10);
    setPos(x, y);
    setPen(Qt::NoPen);
}

void SmokeFromHouse::advance(int phase) {
    if(phase) {
        moveBy(-0.05*(this->scale()-1), -1.f);
        setScale(this->scale()+0.05f);
        setBrush(QColor(this->brush().color().red(), this->brush().color().green(), this->brush().color().blue(), this->brush().color().alpha()-2));
        if(Flag1) {
            moveBy(Fln*0.5, 0);
        }
    }
}

void FallingBall::advance(int phase) {
    if(phase) {
        moveBy(0, 1);

        setRotation(this->rotation()+1);
        if(Flag1) {
            moveBy(Fln*0.5f, 0);
        }
    }
}

void MainWindow::onGenerator() {
    scene->addItem(new FallingBall(ui->gvScene->width()));
    scene->addItem(new FallingBall(ui->gvScene->width()));
    scene->addItem(new FallingBall(ui->gvScene->width()));
}

void MainWindow::onSmok() {
    scene->addItem(new SmokeFromHouse(ui->gvScene->width()-160, ui->gvScene->height()-150));
}

Cloud::Cloud(int x, int y) : QGraphicsEllipseItem(0) {
    setRect(0, 0, 60, 30);
    setPos(x,y);
    setPen(Qt::NoPen);
    setBrush(QColor("#87889C"));
}

void Cloud::advance(int phase) {
    moveBy(0.1f, 0);
    if(Flag1) {
        moveBy(Fln*0.05f,  0);
    }
}

void MainWindow::GenCloud() {
    int n = 3+rand()%6;
    for(int i = 3; i<n;i++) scene->addItem(new Cloud((-1)*rand()%240, rand()%90));
}

Bird::Bird(int x, int y) : QGraphicsPolygonItem() {
    QPolygonF birdf;
    birdf.append(QPoint(5,0));
    birdf.append(QPoint(8,2));
    birdf.append(QPoint(5,10));
    birdf.append(QPoint(0,10));
    birdf.append(QPoint(5,4));
    setBrush(Qt::black);
    setPolygon(birdf);
    setScale(2);
    setPos(x, y);
}

void Bird::advance(int phase) {
    polygon()[1] = QPointF(polygon()[1].x()+10, polygon()[1].y());
}
