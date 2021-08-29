#ifndef TORRES_H
#define TORRES_H

#include <QWidget>
#include <disco.h>
#include <torreAbstrata.h>

class torres : public QWidget , public torreAbstrata
{
    Q_OBJECT


protected:

    bool inicial;                               //define se é a torre inicial
    bool final;                                 //define se é a torre final
    int nome;                                   //define o nome da torre
    static int tam;                             //salva a qtde total de discos
    static int lastSize;                        //salva o tamanho do ultimo disco clicado
    static torres *torreOrigem;                 //ponteiro para a ultima torre que foi clicada
    static QString lastDir;                     //salva o diretório do ultimo disco clicado
    QVector <QString> cores;                    //vetor dos diretórios das cores

public:
    QVector <Disco*> vet;
    torres(int name,bool ini,bool fim,int size,QWidget * parent=nullptr);
    void paintEvent(QPaintEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    int getName();
    int getTam();
    static void setTam(int x);
    void janelaDeErro(QString str);
    void moveDiscos();
    Disco *getLastDisco();
    int getSizeAtual();
    bool empty();

signals:
    void isOver();
    void restartGame();

public slots:
    void setNewTam(int x);
    void emiteRestart();
    void destroiDiscos();
    void addDisco(QString img,int sizeDisco);
};

#endif // TORRES_H
