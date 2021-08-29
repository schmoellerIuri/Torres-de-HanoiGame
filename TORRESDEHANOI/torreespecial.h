#ifndef TORREESPECIAL_H
#define TORREESPECIAL_H

#include <QObject>
#include <torres.h>
#include <disco.h>
#include <QQueue>

class torreEspecial : public torres
{
    Q_OBJECT

public:

    torreEspecial(int name,bool ini,bool fim = false,int size=3,QWidget * parent=nullptr);
    void discosBuilder(int size);
    void push(Disco *d);
    void pop();
    Disco *getDiscoArrastavel();
    void paintEvent(QPaintEvent *event);
public slots:
    void resetTower();
};

#endif // TORREESPECIAL_H
