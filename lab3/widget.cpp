#include "widget.h"
#include "paintarea.h"
#include "prefarea.h"
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("lab3");

    QHBoxLayout *phboxLayout = new QHBoxLayout;
    PaintArea *pPaintArea = new PaintArea;
    PrefArea *pPrefArea = new PrefArea;
    phboxLayout->addWidget(pPaintArea, 3);
    phboxLayout->addWidget(pPrefArea, 1);
    setLayout(phboxLayout);
}

Widget::~Widget()
{

}
