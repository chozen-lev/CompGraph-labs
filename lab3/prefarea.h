#ifndef PREFAREA_H
#define PREFAREA_H

#include <QWidget>
#include <QPushButton>
#include <QColorDialog>

class PaletteButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PaletteButton(QWidget *parent = nullptr);

private:

signals:

public slots:
    void onColor();
};

class PrefArea : public QWidget
{
    Q_OBJECT
public:
    explicit PrefArea(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // PREFAREA_H
