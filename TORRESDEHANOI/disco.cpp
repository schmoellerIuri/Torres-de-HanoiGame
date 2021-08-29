#include "disco.h"

Disco::Disco(QPixmap cor, int tamanho,QString dir, QWidget *parent): QLabel(parent)
{
    imageDir = dir;                                         //salva todos os atributos de cada disco construído
    color = cor;                                            //pixmap da cor, diretório da imagem do pixmap e tamanho do disco
    tam = tamanho;
    setFrameStyle(QFrame::Box);                             //define um contorno para o disco/label
    setLineWidth(2);
    setScaledContents(true);                                //define que o disco irá ser preenchido totalmente pela imagem do pixmap
    setPixmap(color);
    setAttribute(Qt::WA_DeleteOnClose);                     //define que o disco será deletado quando fechado
}

int Disco:: getSize(){                                      //retorna o tamanho do disco
    return tam;
}

QString Disco :: getDir(){                                  //retorna o diretório da imagem, que é utilizado na função save
    return imageDir;
}
