#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QFrame>
#include <QPainter>

class PaintArea : public QFrame
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);

private:
    std::vector<QPointF> points;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:

public slots:
};

#endif // PAINTAREA_H
