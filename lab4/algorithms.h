#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#endif // ALGORITHMS_H

#include <QtMath>
#include <QImage>
#include <QPainter>

void drawSnow(QImage &image, int iter, int x1, int y1, int x5, int y5)
{
    if (iter == 0) {
        QPainter painter(&image);
        QPen pen(Qt::black);
        painter.setPen(pen);
        painter.drawLine(x1, y1, x5, y5);
        painter.end();
        return;
    }

    int deltaX, deltaY, x2, y2, x3, y3, x4, y4;

    deltaX = x5 - x1;
    deltaY = y5 - y1;

    x2 = x1 + deltaX / 3;
    y2 = y1 + deltaY / 3;

    x3 = (int) (0.5 * (x1+x5) + sqrt(3) * (y1-y5)/6);
    y3 = (int) (0.5 * (y1+y5) + sqrt(3) * (x5-x1)/6);

    x4 = x1 + 2 * deltaX / 3;
    y4 = y1 + 2 * deltaY / 3;

    drawSnow(image, iter-1, x1, y1, x2, y2);
    drawSnow(image, iter-1, x2, y2, x3, y3);
    drawSnow(image, iter-1, x3, y3, x4, y4);
    drawSnow(image, iter-1, x4, y4, x5, y5);
}

class Complex //класс комплексных чисел, необходимый для расчетов
{
private:
    double r, i;
public:
    Complex(double r, double i)
        { this->r = r; this->i = i; }
    Complex operator+(const Complex &c)
        { return Complex(r + c.r, i + c.i); }
    Complex operator*(const Complex &c)
        { return Complex(r * c.r - i * c.i, 2 * r * c.i); }
    double abs(){return r * r + i * i;}
};

void drawMandelbrot(QImage &image, int iter)
{
    for (int y = 0; y < 600; y++)
    {
        for (int x = 0; x < 800; x++)
        {
            Complex z(0, 0);
            int i = 0;
            while (i < 400 && z.abs() < iter){
                z = z * z + Complex((x - 390) / 180.0, (y - 290) / 180.0);
                i++;
            }
            double r = 0.1098+(i*0.00329)*0.45; //расчет
            double g = 0.18824+(i*0.00329)*0.78; //значений
            double b = 0.29412+(i*0.00329)*0.30; //для раскраски множества
            QPainter painter(&image);
            QColor rgbf; rgbf.setRgbF(r, g, b);
            QPen pen(rgbf);
            painter.setPen(pen);
            painter.drawPoint(x-0.65, y);

//            // закраска внутренней области
//            if(z.abs() < 2)
//            {
//                rgbf.setRgbF(0.1098,0.18824,0.29412);
//                pen.setColor(rgbf);
//                painter.setPen(pen);
//                painter.drawPoint(x-0.65, y);
//            }
            painter.end();
        }
    }
}

//void drawMandelbrot(QImage &image, int iter)
//{
//    QPainter painter(&image);
//    QPen pen(Qt::black);
//    painter.setPen(pen);
//    double MinRe = -2.0;
//    double MaxRe = 1.0;
//    double MinIm = -1.2;
//    double MaxIm = MinIm+(MaxRe-MinRe)*600/800;
//    double Re_factor = (MaxRe-MinRe)/(800-1);
//    double Im_factor = (MaxIm-MinIm)/(600-1);

//    for(unsigned y=0; y<600; ++y)
//    {
//        double c_im = MaxIm - y*Im_factor;
//        for(unsigned x=0; x<800; ++x)
//        {
//            double c_re = MinRe + x*Re_factor;

//            double Z_re = c_re, Z_im = c_im;
//            bool isInside = true;
//            for(unsigned n=0; n < iter; ++n)
//            {
//                double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
//                if(Z_re2 + Z_im2 > 4)
//                {
//                    isInside = false;
//                    break;
//                }
//                Z_im = 2*Z_re*Z_im + c_im;
//                Z_re = Z_re2 - Z_im2 + c_re;
//            }
//            if(isInside) { painter.drawPoint(x, y); }
//        }
//    }
//    painter.end();
//}

float LastX, LastY;

void drawRelative(QImage &image, float dx, float dy)
{
    QPainter painter(&image);
    QPen pen(Qt::black);
    painter.setPen(pen);
    painter.drawLine(LastX, LastY, LastX + dx, LastY + dy);
    painter.end();
    LastX = LastX + dx;
    LastY = LastY + dy;
}

void drawHilbert(QImage &image, int depth, float dx, float dy)
{
    if (depth > 1) drawHilbert(image, depth - 1, dy, dx);
    drawRelative(image, dx, dy);
    if (depth > 1) drawHilbert(image, depth - 1, dx, dy);
    drawRelative(image, dy, dx);
    if (depth > 1) drawHilbert(image, depth - 1, dx, dy);
    drawRelative(image, -dx, -dy);
    if (depth > 1) drawHilbert(image, depth - 1, -dy, -dx);
}
