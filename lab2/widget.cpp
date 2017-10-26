#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QtMath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    clearFocus();
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    QPen pen(Qt::red);
    pen.setWidth(4);

    painter.setPen(pen);

    if (!points.empty()) {
        painter.drawPoints(points.data(), points.size());
        curve.clear();
        for (float t = 0.f ; t <= 1.f ; t += 0.01f)
            curve.push_back(tCurve(points, t));
    }

    if (curve.size() >= 2) {
        painter.setRenderHint(QPainter::Antialiasing);
        pen.setWidth(1);
        pen.setColor(Qt::black);
        painter.setPen(pen);

        painter.drawPolyline(curve.data(), curve.size());
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << event->pos();
        points.insert(points.end()--, event->pos());

        update();
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        for (std::size_t i = 0 ; i < points.size() ; i++) {
            points[i].ry()--;
        }
        break;
    case Qt::Key_Down:
        for (std::size_t i = 0 ; i < points.size() ; i++) {
            points[i].ry()++;
        }
        break;
    case Qt::Key_Left:
        for (std::size_t i = 0 ; i < points.size() ; i++) {
            points[i].rx()--;
        }
        break;
    case Qt::Key_Right:
        for (std::size_t i = 0 ; i < points.size() ; i++) {
            points[i].rx()++;
        }
        break;
    case Qt::Key_Escape:
        points.clear();
        curve.clear();
        break;
    case Qt::Key_Plus:
        for (std::size_t i = 0 ; i < points.size() ; i++) {
            points[i].rx() *= 4.0/3.0;
            points[i].ry() *= 4.0/3.0;
        }
        break;
    case Qt::Key_Minus:
        for (std::size_t i = 0 ; i < points.size() ; i++) {
            points[i].rx() *= 3.0/4.0;
            points[i].ry() *= 3.0/4.0;
        }
        break;
    case Qt::Key_Space:
        for (std::size_t i = 0 ; i < points.size() ; i++) {
            QPoint old(points[i].x(), points[i].y());
            points[i].rx() = width()/2 + (old.x() - width()/2)*qCos(0.0174533) + (height()/2 - old.y())*qSin(0.0174533);
            points[i].ry() = height()/2 + (old.x() - width()/2)*qSin(0.0174533) + (old.y() - height()/2)*qCos(0.0174533);
        }
        break;
    case Qt::Key_R:
        for (std::size_t i = 0 ; i < points.size() ; i++) {
            points[i].rx() = -points[i].x() + width();
            points[i].ry() = -points[i].y() + height();
        }
        break;
    }
    update();
}

QPointF Widget::tCurve(std::vector<QPointF> points, float t)
{
    std::vector<QPointF> npoints;
    std::size_t size = points.size();

    if (size == 1)
        return points[0];
    else {
        for (std::size_t i = 0 ; i < size - 1 ; i++)
            npoints.push_back((points[i+1] - points[i]) * t + points[i]);

        return tCurve(npoints, t);
    }
}
