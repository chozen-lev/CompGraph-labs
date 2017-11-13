#include "paintarea.h"
#include <QMouseEvent>
#include <QDebug>

PaintArea::PaintArea(QWidget *parent) : QFrame(parent)
{
    setMinimumWidth(600);
    setMinimumHeight(400);
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setStyleSheet("background-color:white;");
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPen pen(Qt::red);
    QPainter painter(this);
    painter.setPen(pen);

    if (!points.empty()) {
        painter.drawPoints(points.data(), points.size());
    }

    if (points.size() >= 2) {
        painter.setRenderHint(QPainter::Antialiasing);
        pen.setWidth(1);
        pen.setColor(Qt::black);
        painter.setPen(pen);

        painter.drawPolyline(points.data(), points.size());

        if (points.size() >= 3) {
            painter.drawLine(points.back(), points.front());
        }
    }
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << event->pos();
        points.insert(points.end()--, event->pos());

        update();
    }
}
