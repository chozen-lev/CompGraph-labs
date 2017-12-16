#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtMath>
#include <QPainter>

class Line
{
public:

    double x, y, length, angle; // Members

    Line(double x, double y, double length, double angle) : x(x), y(y), length(length), angle(angle) {}

    double getX2() // Getting the second x coordinate based on the angle and length
    {
        return x+cos(angle*(M_PI/180.0))*length;
    }

    double getY2() // Getting the second y coordinate based on the angle and length
    {
        return y+sin(angle*(M_PI/180.0))*length;
    }

    void draw(QImage &image)
    {
        QPainter painter(&image);
        QPen pen(QColor(100,255,100,255));
        painter.setPen(pen);
        painter.drawLine(x,y, getX2(),getY2());
        painter.end();
    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_koch_clicked();

    void on_mandelbrot_clicked();

    void on_other_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QImage image;
    QGraphicsPixmapItem *pixmapItem;

    int algorithm;

    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
