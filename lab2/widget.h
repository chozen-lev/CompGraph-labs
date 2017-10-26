#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    std::vector<QPointF> points;
    std::vector<QPointF> curve;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    QPointF tCurve(std::vector<QPointF> points, float t);
};

#endif // WIDGET_H
