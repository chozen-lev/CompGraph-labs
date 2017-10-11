#ifndef PREFAREA_H
#define PREFAREA_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QSlider>
#include <QLineEdit>

class PrefArea : public QWidget
{
    Q_OBJECT
public:
    explicit PrefArea(QWidget *parent = nullptr);

private:
    QGroupBox *plineGroup;
    QGroupBox *pcircleGroup;
    QSlider *psld;
    int algorithm;
    QLineEdit *plinex1, *pliney1, *plinex2, *pliney2, *plinex, *pliney, *plineradius;

signals:
    void prefChanged(int, int, double, double, double, double, int);
    void drawClicked();
    void appendDebug(QString);

private slots:
    void slotDDASelected(bool);
    void slotBresSelected(bool);
    void slotWuSelected(bool);
    void slotBres2Selected(bool);
    void slotOtherSelected(bool);
    void slotDrawClicked();
};

#endif // PREFAREA_H
