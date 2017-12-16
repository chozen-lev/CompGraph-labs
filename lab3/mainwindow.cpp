#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "algorithms.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clearFocus();

    algorithm = ALGORITHMS::FORESTFIRE;
    tool = TOOLS::LINE;

    image = QImage(795, 595, QImage::Format_RGB32);
    image.fill(Qt::white);
    scene = new QGraphicsScene(this);
    pixmapItem = scene->addPixmap(QPixmap::fromImage(image));

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();

//    for (int i = 0; i < 700; i++)
//    {
//        for (int j = 0; j < 500; j++) {
//            image.setPixel(i, j, qRgb(100, 150, 200));
//        }
//    }

    if (tool == TOOLS::LINE)
    {

        image.fill(Qt::white);
        points.push_back(event->pos());

        QPainter painter(&image);
        QPen pen(Qt::black);
        painter.setPen(pen);

        if (!points.empty()) {
            painter.drawPoints(points.data(), points.size());
        }

        if (points.size() >= 2) {
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(pen);

            painter.drawPolyline(points.data(), points.size());

            if (points.size() >= 3) {
                painter.drawLine(points.back(), points.front());
            }
        }

        painter.end();
    }
    else if (tool == TOOLS::FLOODFILL)
    {
        QPainter painter(&image);
        switch (algorithm) {
        case ALGORITHMS::FORESTFIRE:
            forestfire_floodfill(image, event->pos(), Qt::yellow);
            break;
        case ALGORITHMS::LINES:
            lines_floodfill(image, Qt::yellow);
            break;
        case ALGORITHMS::XOR:
            xor_floodfill(image, Qt::yellow, painter, points);
            break;
        default:
            break;
        }
        qDebug() << "successful";
    }

    pixmapItem->setPixmap(QPixmap::fromImage(image));
    scene->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
        tool = tool == TOOLS::LINE ? TOOLS::FLOODFILL : TOOLS::LINE;
        qDebug("tool: %s", tool == TOOLS::LINE ? "line" : "floodfill");
        break;
    case Qt::Key_1:
        algorithm = ALGORITHMS::FORESTFIRE;
        qDebug() << "alg1";
        break;
    case Qt::Key_2:
        algorithm = ALGORITHMS::LINES;
        qDebug() << "alg2";
        break;
    case Qt::Key_3:
        algorithm = ALGORITHMS::XOR;
        qDebug() << "alg3";
        break;
    }
}
