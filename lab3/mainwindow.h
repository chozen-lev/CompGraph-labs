#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    enum TOOLS {
        LINE = 0,
        FLOODFILL
    };

    enum ALGORITHMS {
        NONE = 0,
        FORESTFIRE,
        LINES,
        XOR
    };

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QImage image;
    QGraphicsPixmapItem *pixmapItem;
    ALGORITHMS algorithm;
    TOOLS tool;

    QVector<QPointF> points;

    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
