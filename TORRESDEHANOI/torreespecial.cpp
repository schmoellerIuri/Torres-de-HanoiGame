#include "torreespecial.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QVariant>

torreEspecial::torreEspecial(int name,bool ini,bool fim,int size,QWidget * parent):torres(name,ini,fim,size,parent)
{
    if(inicial)                                         //se a torre for a primeira da esquerda pra direita, serão inseridos todos os discos inicialmente
    discosBuilder(tam);                                 //nela

}

void torreEspecial :: paintEvent(QPaintEvent *event){
                                                                                //desenhando todas as Linhas verticais representando cada
    QPainter pintor(this);                                                      //torre
    QPen *caneta = new QPen(Qt::black);
    caneta->setWidth(10);
    pintor.setPen(*caneta);
    pintor.drawLine(this->width()*6/10,this->height()*6/10,this->width()*6/10,this->height()*2/10);
    QString texto = "TORRE ";
    QVariant v(nome);
    texto += v.toString();
    pintor.drawText(this->width()*2/5,this->height()*6/10+16,texto);        //escrevendo a identificação de cada torre
    moveDiscos();   //move os discos para sua posição correta a cada paintEvent
}

void torreEspecial :: push(Disco *d){       //faz o push de um disco no final da torre
    vet.push_back(d);
}

void torreEspecial :: pop(){                //faz o pop no início da torre
    vet.pop_front();
}

void torreEspecial :: discosBuilder(int size){      //insere os discos na torre inicial, de acordo com variável tam que define a qtde de discos totais
                                                    //além de mover os discos para sua posição correta
    for(int i=0;i<size;i++){
        Disco *d = new Disco(QPixmap(cores[i]),32+2*i,cores[i],this);
        push(d);
        vet.back()->resize(this->width()*d->getSize()/100,this->height()*1/20);
        vet.back()->move(this->width()*4/10,(this->height()*6/10)-(this->height()*1/20*(size-i+1)));
        vet.back()->show();
     }
}

Disco *torreEspecial:: getDiscoArrastavel(){ //retorna o disco que pode ser arrastado
    return vet.front();
}

void torreEspecial :: resetTower(){           //remove todos os discos das torres, e adiciona todos novamente na torre inicial
    while(!empty()){
     vet.front()->close();
     pop();
    }
    if(inicial){
     discosBuilder(tam);
    }
    update();
}
