#include "prefarea.h"
#include <QBoxLayout>
#include <QRadioButton>
#include <QGroupBox>

#include <QDebug>

PrefArea::PrefArea(QWidget *parent) : QWidget(parent)
{
    // algorithm radio group
    QRadioButton *pRadio1 = new QRadioButton("Stack-based recursive 4-way");
    QRadioButton *pRadio2 = new QRadioButton("Forest Fire algorithm");
    QRadioButton *pRadio3 = new QRadioButton("XOR algorithm");
    QRadioButton *pRadio4 = new QRadioButton("XOR operation with partition");
    pRadio1->setChecked(true);

    QVBoxLayout *pVAlgLayout = new QVBoxLayout;
    pVAlgLayout->addWidget(pRadio1);
    pVAlgLayout->addWidget(pRadio2);
    pVAlgLayout->addWidget(pRadio3);
    pVAlgLayout->addWidget(pRadio4);

    QGroupBox *pAlgGroup = new QGroupBox("Algorithms");
    pAlgGroup->setLayout(pVAlgLayout);

    // Palette group
    PaletteButton *pButtonColor = new PaletteButton;
    pButtonColor->setStyleSheet("background-color: green");

    QVBoxLayout *pVColorLayout = new QVBoxLayout;
    pVColorLayout->addWidget(pButtonColor);

    QGroupBox *pPaletteGroup = new QGroupBox("Palette");
    pPaletteGroup->setLayout(pVColorLayout);

    // algorithm radio group
    QRadioButton *pLineButton = new QRadioButton("&Line");
    QRadioButton *pFillButton = new QRadioButton("&Floodfill");
    pLineButton->setChecked(true);

    QHBoxLayout *pHToolsLayout = new QHBoxLayout;
    pHToolsLayout->addWidget(pLineButton);
    pHToolsLayout->addWidget(pFillButton);

    QGroupBox *pToolsGroup = new QGroupBox("Tools");
    pToolsGroup->setLayout(pHToolsLayout);

    QHBoxLayout *pPaletteToolsLayout = new QHBoxLayout;
    pPaletteToolsLayout->addWidget(pToolsGroup, 3);
    pPaletteToolsLayout->addWidget(pPaletteGroup, 1);

    QPushButton *pButtonDraw = new QPushButton("Clea&r");

    // main layout
    QVBoxLayout *pVBoxLayout = new QVBoxLayout;
    pVBoxLayout->setMargin(0);
    pVBoxLayout->setSpacing(10);
    pVBoxLayout->addWidget(pAlgGroup);
    pVBoxLayout->addLayout(pPaletteToolsLayout);
    pVBoxLayout->addStretch(1);
    pVBoxLayout->addWidget(pButtonDraw);

    setLayout(pVBoxLayout);
}

PaletteButton::PaletteButton(QWidget *parent) : QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(onColor()));
}

void PaletteButton::onColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    setStyleSheet(QString("background-color: %1").arg(color.name()));
}
