#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QtMath>
#include <QDebug>

void dda_line(QPainter *painter, double x1, double y1, double x2, double y2)
{
    double x, y, dx, dy, step;

    dx = fabs(x2-x1);
    dy = fabs(y2-y1);

    if(dx >= dy) {
        step = dx;
    } else {
        step = dy;
    }

    dx = dx / step;
    dy = dy / step;

    x = x1;
    y = y1;

    for (int i = 1; i <= step; i++)
    {
        painter->drawPoint(x, y);
        x += dx;
        y += dy;
    }
}

void bresenham_line(QPainter *painter, int x1, int y1, int x2, int y2)
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;

    int error = deltaX - deltaY;

    painter->drawPoint(x2, y2);
    while(x1 != x2 || y1 != y2)
    {
        painter->drawPoint(x1, y1);
        const int error2 = error * 2;

        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

/* Сяолинь Ву */
#define plot_(X,Y,D) do{ \
  painter->setOpacity((D)); \
  painter->drawPoint((X), (Y)); } while(0)

#define swap_(a, b) do{ __typeof__(a) tmp;  tmp = a; a = b; b = tmp; }while(0)
#define ipart_(X) ((int)(X))
#define round_(X) ((int)(((double)(X))+0.5))
#define fpart_(X) (((double)(X))-(double)ipart_(X))
#define rfpart_(X) (1.0-fpart_(X))

void xiaolin_line(QPainter *painter, int x1, int y1, int x2, int y2)
{
    bool steep = abs(y2-y1) > abs(x2-x1);

    if (steep) {
        swap_(x1, y1);
        swap_(x2, y2);
    }
    if (x1 > x2) {
        swap_(x1, x2);
        swap_(y1, y2);
    }

    double dx = x2 - x1,
           dy = y2 - y1,
           gradient = dy / dx;
    if (dx == 0.0) {
        gradient = 1.0;
    }

    double xend = round_(x1),
           yend = y1 + gradient * (xend - x1),
           xgap = rfpart_(x1 + 0.5),
           xpxl1 = xend,
           ypxl1 = ipart_(yend);

    if (steep) {
        plot_(ypxl1,   xpxl1, rfpart_(yend) * xgap);
        plot_(ypxl1+1, xpxl1,  fpart_(yend) * xgap);
    } else {
        plot_(xpxl1, ypxl1  , rfpart_(yend) * xgap);
        plot_(xpxl1, ypxl1+1,  fpart_(yend) * xgap);
    }
    double intery = yend + gradient;

    xend = round_(x2);
    yend = y2 + gradient * (xend - x2);
    xgap = fpart_(x2 + 0.5);
    double xpxl2 = xend,
           ypxl2 = ipart_(yend);

    if (steep) {
        plot_(ypxl2  , xpxl2, rfpart_(yend) * xgap);
        plot_(ypxl2+1, xpxl2,  fpart_(yend) * xgap);
    } else {
        plot_(xpxl2, ypxl2,  rfpart_(yend) * xgap);
        plot_(xpxl2, ypxl2+1, fpart_(yend) * xgap);
    }

    if (steep) {
        for (int x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
            plot_(ipart_(intery)  , x, rfpart_(intery));
            plot_(ipart_(intery)+1, x,  fpart_(intery));
            intery += gradient;
        }
    } else {
        for (int x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
            plot_(x, ipart_(intery),  rfpart_(intery));
            plot_(x, ipart_(intery)+1, fpart_(intery));
            intery += gradient;
        }
    }
}

#undef swap_
#undef plot_
#undef ipart_
#undef fpart_
#undef round_
#undef rfpart_
/******************************/

void circle_Bre(QPainter *painter, int _x, int _y, int radius){
    int x = 0, y = radius, gap = 0, delta = (2 - 2 * radius);
    while (y >= 0)
    {
        painter->drawPoint((_x + x), (_y + y));
        painter->drawPoint((_x + x), (_y - y));
        painter->drawPoint((_x - x), (_y - y));
        painter->drawPoint((_x - x), (_y + y));
        gap = 2 * (delta + y) - 1;
        if (delta < 0 && gap <= 0)
        {
            x++;
            delta += 2 * x + 1;
            continue;
        }
        if (delta > 0 && gap > 0)
        {
            y--;
            delta -= 2 * y + 1;
            continue;
        }
        x++;
        delta += 2 * (x - y);
        y--;
    }
}

#endif // ALGORITHMS_H
