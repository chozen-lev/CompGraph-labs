#include "paintarea.h"
#include "algorithms.h"
#include <QElapsedTimer>
#include <QtDebug>
#include <QPaintEvent>

PaintArea::PaintArea(QWidget *parent) : QFrame(parent),
    flag(false)
{
    setMinimumWidth(600);
    setMinimumHeight(400);
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setStyleSheet("background-color:white;");
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);
    if (!flag)  // костыляка
    {
        switch (algorithm)
        {
        case 1: dda_line(&p, x1, y1, x2, y2);
        break;
        case 2: bresenham_line(&p, x1, y1, x2, y2);
        break;
        case 3: xiaolin_line(&p, x1, y1, x2, y2);
        break;
        case 4: circle_Bre(&p, x1, y1, radius);
        break;
        case 5: p.drawEllipse(x1, y1, radius*2, radius*2);
        }
        return;
    }
    flag = false;

    QElapsedTimer timer;
    timer.start();

    switch (algorithm)
    {
    case 1:
    {
        for (int i = 0; i < cycles; i++) {
            dda_line(&p, x1, y1, x2, y2);
        }
        break;
    }
    case 2:
    {
        for (int i = 0; i < cycles; i++) {
            bresenham_line(&p, x1, y1, x2, y2);
        }
        break;
    }
    case 3:
    {
        for (int i = 0; i < cycles; i++) {
            xiaolin_line(&p, x1, y1, x2, y2);
        }
        break;
    }
    case 4:
    {
        for (int i = 0; i < cycles; i++) {
            circle_Bre(&p, x1, y1, radius/2);
        }
        break;
    }
    case 5:
    {
        for (int i = 0; i < cycles; i++) {
            p.drawEllipse(x1, y1, radius, radius);
        }
    }
    }

    qint64 time = timer.elapsed();
    emit appendDebug(QString::number(algorithm) + ". cycles: " + QString::number(cycles) + ". time: " + QString::number(time) + "ms");
    update(); // one more time
}

void PaintArea::slotDrawClicked()
{
    flag = true;
    update();
}

void PaintArea::slotPrefChanged(int _cycles, int _algorithm, double _x1, double _y1, double _x2, double _y2, int _radius)
{
    cycles = _cycles;
    algorithm = _algorithm;
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;
    radius = _radius;
}
