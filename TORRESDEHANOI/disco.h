#ifndef DISCO_H
#define DISCO_H

#include <QObject>
#include <QLabel>

class Disco : public QLabel
{
    Q_OBJECT
    int tam;                                    //tamanho do disco
    QPixmap color;                              //pixmap da cor do disco
    QString imageDir;                           //diretorio da imagem que representa a cor

public:
    Disco(QPixmap cor, int tamanho,QString dir,QWidget *parent = nullptr);
    int getSize();
    QString getDir();
};

#endif // DISCO_H
