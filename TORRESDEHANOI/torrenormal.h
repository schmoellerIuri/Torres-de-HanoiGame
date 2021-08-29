#ifndef TORRENORMAL_H
#define TORRENORMAL_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
#include <torres.h>


class torreNormal : public torres
{
    Q_OBJECT


public:

    torreNormal(int name,bool ini,bool fim = false,int size=3,QWidget * parent=nullptr);
    void discosBuilder(int size);
    void push(Disco *d);
    void pop();
    Disco *getDiscoArrastavel();


public slots:
    void resetTower();

};

#endif // TORRENORMAL_H
