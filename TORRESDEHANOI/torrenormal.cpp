#include "torrenormal.h"
#include "disco.h"
#include <QtWidgets>
#include <QFrame>
#include <QLabel>
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QPushButton>
#include <QVector>


torreNormal::torreNormal(int name,bool ini,bool fim,int size,QWidget *parent):torres(name,ini,fim,size,parent){
    if(inicial){                                //se a torre for inicial adiciona todos os discos nela inicialmente
    discosBuilder(tam);
}

}

void torreNormal :: push(Disco *d){ //faz um push no final da torre
    vet.push_back(d);
}

void torreNormal :: pop(){  //faz um pop no final da torre
    vet.pop_back();
}

void torreNormal::discosBuilder(int size){ //constroi e adiciona discos a uma torre, além de move-los para a posição correta
    for(int i=0;i<size;i++){
       addDisco(cores[i],40-2*i);
     }
}

Disco *torreNormal :: getDiscoArrastavel(){ //retorna o disco que pode ser arrastado
    return vet.back();
}

void torreNormal :: resetTower(){           //remove todos os discos das torres, e adiciona todos novamente na torre inicial
    while(!empty()){
     vet.back()->close();
     pop();
    }
    if(inicial){
     discosBuilder(tam);
    }
    update();
}



