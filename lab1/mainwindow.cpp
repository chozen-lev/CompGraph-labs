#include "mainwindow.h"
#include "paintarea.h"
#include "prefarea.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("lab1");
    QHBoxLayout *phboxLayout = new QHBoxLayout;
    PaintArea *pPaintArea = new PaintArea;
    PrefArea *pPrefArea = new PrefArea;
    phboxLayout->addWidget(pPaintArea, 3);
    phboxLayout->addWidget(pPrefArea, 1);
    setLayout(phboxLayout);

    connect(pPrefArea, SIGNAL(drawClicked()), pPaintArea, SLOT(slotDrawClicked()));
    connect(pPrefArea, SIGNAL(prefChanged(int,int,double,double,double,double,int)), pPaintArea, SLOT(slotPrefChanged(int,int,double,double,double,double,int)));
    connect(pPaintArea, SIGNAL(appendDebug(QString)), pPrefArea, SIGNAL(appendDebug(QString)));
}

MainWindow::~MainWindow()
{

}
