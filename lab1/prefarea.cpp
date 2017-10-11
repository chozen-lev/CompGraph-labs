#include "prefarea.h"
#include <QBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QDoubleValidator>
#include <QTextEdit>
#include <QtDebug>

PrefArea::PrefArea(QWidget *parent) : QWidget(parent),
    psld(new QSlider(Qt::Horizontal)),
    plinex1(new QLineEdit("0.0")),
    pliney1(new QLineEdit("0.0")),
    plinex2(new QLineEdit("200.0")),
    pliney2(new QLineEdit("300.0")),
    plinex(new QLineEdit("200.0")),
    pliney(new QLineEdit("200.0")),
    plineradius(new QLineEdit("25"))
{
    // cycles slider
    psld->setRange(1, 10000);
    psld->setPageStep(100);
    psld->setValue(3000);
    psld->setTickInterval(1000);
    psld->setTickPosition(QSlider::TicksAbove);

    QLabel *lblmin = new QLabel("1");
    QLabel *lblmax = new QLabel("10000");

    QHBoxLayout *psliderLayout = new QHBoxLayout;
    psliderLayout->addWidget(lblmin);
    psliderLayout->addWidget(psld);
    psliderLayout->addWidget(lblmax);

    QGroupBox *psliderGroup = new QGroupBox("Сycles");
    psliderGroup->setLayout(psliderLayout);

    // algorithm radio group
    QRadioButton *pradio1 = new QRadioButton("DDA line");
    QRadioButton *pradio2 = new QRadioButton("Bresenham's line");
    QRadioButton *pradio3 = new QRadioButton("Xiaolin Wu's line");
    QRadioButton *pradio4 = new QRadioButton("Bresenham's circle");
    QRadioButton *pradio5 = new QRadioButton("Something else");
    pradio1->setChecked(true);
    algorithm = 1;

    QVBoxLayout *pvalgLayout = new QVBoxLayout;
    pvalgLayout->addWidget(pradio1);
    pvalgLayout->addWidget(pradio2);
    pvalgLayout->addWidget(pradio3);
    pvalgLayout->addWidget(pradio4);
    pvalgLayout->addWidget(pradio5);

    QGroupBox *palgGroup = new QGroupBox("Algorithms");
    palgGroup->setLayout(pvalgLayout);

    connect(pradio1, SIGNAL(toggled(bool)), SLOT(slotDDASelected(bool)));
    connect(pradio2, SIGNAL(toggled(bool)), SLOT(slotBresSelected(bool)));
    connect(pradio3, SIGNAL(toggled(bool)), SLOT(slotWuSelected(bool)));
    connect(pradio4, SIGNAL(toggled(bool)), SLOT(slotBres2Selected(bool)));
    connect(pradio5, SIGNAL(toggled(bool)), SLOT(slotOtherSelected(bool)));

    // line options group
    QLabel *plblx1 = new QLabel("x1");
    QLabel *plbly1 = new QLabel("y1");
    QLabel *plblx2 = new QLabel("x2");
    QLabel *plbly2 = new QLabel("y2");
    plinex1->setValidator(new QRegExpValidator(QRegExp("\\d{0,}\\.\\d{0,}"), plinex1));
    pliney1->setValidator(new QRegExpValidator(QRegExp("\\d{0,}\\.\\d{0,}"), pliney1));
    plinex2->setValidator(new QRegExpValidator(QRegExp("\\d{0,}\\.\\d{0,}"), plinex2));
    pliney2->setValidator(new QRegExpValidator(QRegExp("\\d{0,}\\.\\d{0,}"), pliney2));

    QPushButton *pbuttonVer = new QPushButton("&Vertical");
    QPushButton *pbuttonHor = new QPushButton("&Horizontal");
    QPushButton *pbutton45d = new QPushButton("45 d&egrees");
    QPushButton *pbuttonRand = new QPushButton("&Random");

    QGridLayout *plineLayout = new QGridLayout;
    plineLayout->addWidget(plblx1, 2, 0);
    plineLayout->addWidget(plbly1, 2, 2);
    plineLayout->addWidget(plblx2, 3, 0);
    plineLayout->addWidget(plbly2, 3, 2);
    plineLayout->addWidget(plinex1, 2, 1);
    plineLayout->addWidget(pliney1, 2, 3);
    plineLayout->addWidget(plinex2, 3, 1);
    plineLayout->addWidget(pliney2, 3, 3);
    plineLayout->addWidget(pbuttonVer, 0, 0, 1, 2);
    plineLayout->addWidget(pbuttonHor, 0, 2, 1, 2);
    plineLayout->addWidget(pbutton45d, 1, 0, 1, 2);
    plineLayout->addWidget(pbuttonRand, 1, 2, 1, 2);

    plineGroup = new QGroupBox("Options");
    plineGroup->setLayout(plineLayout);

    // circle options group
    QLabel *plblx = new QLabel("x");
    QLabel *plbly = new QLabel("y");
    QLabel *plblradius = new QLabel("radius");
    plinex->setValidator(new QRegExpValidator(QRegExp("\\d{0,}\\.\\d{0,}"), plinex));
    pliney->setValidator(new QRegExpValidator(QRegExp("\\d{0,}\\.\\d{0,}"), pliney));
    plineradius->setValidator(new QRegExpValidator(QRegExp("\\d{0,}"), plineradius));
    QPushButton *pbuttonRand2 = new QPushButton("&Random");

    QGridLayout *pcircleLayout = new QGridLayout;
    pcircleLayout->addWidget(plblx, 1, 0);
    pcircleLayout->addWidget(plbly, 2, 0);
    pcircleLayout->addWidget(plblradius, 1, 2);
    pcircleLayout->addWidget(plinex, 1, 1);
    pcircleLayout->addWidget(pliney, 2, 1);
    pcircleLayout->addWidget(plineradius, 1, 3);
    pcircleLayout->addWidget(pbuttonRand2, 0, 0, 1, 4);

    pcircleGroup = new QGroupBox("Options");
    pcircleGroup->setLayout(pcircleLayout);
    pcircleGroup->hide();

    // logs output area
    QTextEdit *ptext = new QTextEdit;
    ptext->setReadOnly(true);
    QFont f("unexistent", 9);
    f.setStyleHint(QFont::Monospace);
    ptext->setFont(f);
    connect(this, SIGNAL(appendDebug(QString)), ptext, SLOT(append(QString)));

    QPushButton *pbuttonDraw = new QPushButton("&Draw");
    connect(pbuttonDraw, SIGNAL(clicked()), SLOT(slotDrawClicked()));

    // main layout
    QVBoxLayout *pvboxLayout = new QVBoxLayout;
    pvboxLayout->setMargin(0);
    pvboxLayout->setSpacing(10);
    pvboxLayout->addWidget(psliderGroup);
    pvboxLayout->addWidget(palgGroup);
    pvboxLayout->addWidget(plineGroup);
    pvboxLayout->addWidget(pcircleGroup);
    pvboxLayout->addStretch(1);
    pvboxLayout->addWidget(ptext);
    pvboxLayout->addWidget(pbuttonDraw);

    setLayout(pvboxLayout);
}

void PrefArea::slotDDASelected(bool checked)
{
    if (!checked) {
        return;
    }
    pcircleGroup->hide();
    plineGroup->show();

    algorithm = 1;
}

void PrefArea::slotBresSelected(bool checked)
{
    if (!checked) {
        return;
    }
    pcircleGroup->hide();
    plineGroup->show();

    algorithm = 2;
}

void PrefArea::slotWuSelected(bool checked)
{
    if (!checked) {
        return;
    }
    pcircleGroup->hide();
    plineGroup->show();

    algorithm = 3;
}

void PrefArea::slotBres2Selected(bool checked)
{
    if (!checked) {
        return;
    }
    plineGroup->hide();
    pcircleGroup->show();

    algorithm = 4;
}

void PrefArea::slotOtherSelected(bool checked)
{
    if (!checked) {
        return;
    }
    plineGroup->hide();
    pcircleGroup->show();

    algorithm = 5;
}

void PrefArea::slotDrawClicked()
{
    // сигнал об изменении данных
    if (algorithm <= 3) {
        emit prefChanged(psld->value(), algorithm, plinex1->text().toDouble(), pliney1->text().toDouble(), \
                         plinex2->text().toDouble(), pliney2->text().toDouble(), 0);
    } else {
        emit prefChanged(psld->value(), algorithm, plinex->text().toDouble(), pliney->text().toDouble(), 0.0, 0.0, \
                         plineradius->text().toDouble());
    }
    // сигнал об очистке экрана

    // сигнал об отрисовке
    emit drawClicked();
}
