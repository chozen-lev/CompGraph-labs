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
    void paintEvent(QPaintEvent *event);

    int cycles, algorithm, radius;
    double x1, y1, x2, y2;
    bool flag;

signals:
    void appendDebug(QString);

public slots:
    void slotPrefChanged(int, int, double, double, double, double, int);
    void slotDrawClicked();
};

#endif // PAINTAREA_H
