#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDebug>

#include "algorithms.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    clearFocus();

    image = QImage(width()-16, height()-32, QImage::Format_RGB32);
    image.fill(Qt::white);
    scene = new QGraphicsScene(this);
    pixmapItem = scene->addPixmap(QPixmap::fromImage(image));

    ui->graphicsView->setScene(scene);
    ui->koch->setChecked(true);
    ui->spinBox->setFocus();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_D) {
        image.fill(Qt::white);
        qDebug() << "draw alg " << algorithm;
        qDebug() << "n = " << ui->spinBox->value();

        switch (algorithm) {
        case 0:
            drawSnow(image, ui->spinBox->value(), 270, 380, 530, 380);
            drawSnow(image, ui->spinBox->value(), 530, 380, 400, 120);
            drawSnow(image, ui->spinBox->value(), 400, 120, 270, 380);
            break;
        case 1:
            drawMandelbrot(image, ui->spinBox->value());
            break;
        case 2:
            float total_length, start_x, start_y, start_length;

            // See how big we can make the curve.
            if (image.height() < image.width())
            {
                total_length = (float)(0.9 * image.height());
            }
            else
            {
                total_length = (float)(0.9 * image.width());
            }

            start_x = (image.width() - total_length) / 2;
            start_y = (image.height() - total_length) / 2;

            start_length = (float)(total_length / (pow(2, ui->spinBox->value()) - 1));

            LastX = (int)start_x;
            LastY = (int)start_y;

            drawHilbert(image, ui->spinBox->value(), start_length, 0);
            break;
        }
    }
    else if (event->key() == Qt::Key_Escape) {
        qDebug() << "clear";
        image.fill(Qt::white);
    }
    else return;

    pixmapItem->setPixmap(QPixmap::fromImage(image));
    scene->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_koch_clicked()
{
    algorithm = 0;
}

void MainWindow::on_mandelbrot_clicked()
{
    algorithm = 1;
}

void MainWindow::on_other_clicked()
{
    algorithm = 2;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "kek";
    QKeyEvent event = QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier);
    keyPressEvent(&event);
}
