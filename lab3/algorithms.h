#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#endif // ALGORITHMS_H

#include <QStack>
#include <QQueue>
#include <QPainter>
#include <QDebug>

void forestfire_floodfill(QImage &img, QPoint point, QColor color)
{
    QStack<QPoint> to_draw;
    to_draw.push_back(point);

    QPoint top;

    while (!to_draw.empty())
    {
        top = to_draw.pop();

        if (top.x() < 0 || top.x() >= img.width() || top.y() < 0 || top.y() >= img.height() || img.pixelColor(top.x(), top.y()) != Qt::white) {
            continue;
        }
        img.setPixelColor(top.x(), top.y(), color);
        to_draw.push({top.x(), top.y() + 1});
        to_draw.push({top.x(), top.y() - 1});
        to_draw.push({top.x() + 1, top.y()});
        to_draw.push({top.x() - 1, top.y()});
    }
}

void lines_floodfill(QImage &img, QColor color)
{
    QPoint line;
    unsigned int i = 0, j = 0;

    while (i < img.height())
    {
        j = 0;

        while (j < img.width())
        {
            if (img.pixelColor(j, i) != Qt::white)
            {
                while (j < img.width() && img.pixelColor(j, i) != Qt::white)
                {
                    j++;
                }
                line.setX(j);

                if (j >= img.width()) {
                    break;
                }

                while (j < img.width() && img.pixelColor(j, i) == Qt::white)
                {
                    j++;
                }

                if (j >= img.width()) {
                    break;
                }

                line.setY(j);
                for (int k = line.x(); k < line.y(); k++) {
                    img.setPixelColor(k, i, color);
                }
            }
            j++;
        }
        i++;
    }
}

void xor_floodfill(QImage &img, QColor color, QPainter &painter, QPolygonF poly)
{
    unsigned int i = 0, j = 0;
    bool fl;
    while (i < img.height())
    {
        fl = false;
        j = 0;
        while (j < img.width())
        {
            if (img.pixelColor(j, i) != Qt::white) {
                if (fl == false)
                {
                    do {
                        j++;
                    } while (j < img.width() && img.pixelColor(j, i) != Qt::white);
                }
                else {
                    do {
                        j++;
                    } while (j < img.width() && img.pixelColor(j, i) == Qt::white);
                }
                fl = !fl;
                j++;
            }
            if (fl)
            {
                unsigned int k = j;
                do {
                    k++;
                } while (k < img.width() && img.pixelColor(k, i) == Qt::white);
                if (k > img.width()) {
                    break;
                }
                img.setPixelColor(j, i, Qt::white);
            }
            j++;
        }
        i++;
    }
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);

    // Fill polygon
    QPainterPath path;
    path.addPolygon(poly);

    // Draw polygon
    painter.drawPolygon(poly);
    painter.fillPath(path, brush);
}
