#include "torres.h"
#include <QFrame>
#include <QtWidgets>
#include <QEvent>
#include <QDebug>
#include <QVariant>

torres::torres(int name,bool ini,bool fim,int size,QWidget *parent) : QWidget(parent)
{
        setMinimumSize(200, 200);
        setAcceptDrops(true);                       //seta o widget das torres para aceitar drops de outros widgets
        this->nome = name;                          //também setando o nome da torre, se é inicial, variavel tam que define a qtde de discos
        this->inicial = ini;                        //e também se a torre é final(a terceira da esquerda pra direita)
        tam = size;
        this->final = fim;

        if(inicial){                                    //se a torre for inicial, salva todos os diretórios das imagens das cores para os discos

        cores.push_back("Imagens/azul.png");
        cores.push_back("Imagens/rosa.png");
        cores.push_back("Imagens/roxo.png");
        cores.push_back("Imagens/amarelo.png");
        cores.push_back("Imagens/laranja.png");
        cores.push_back("Imagens/verde.png");
        cores.push_back("Imagens/azulescuro.png");
        cores.push_back("Imagens/vermelho.png");
    }

}

torres *torres:: torreOrigem;       //ponteiro estático para a torre de origem, torre de onde foi arrastado determinado disco
int torres :: lastSize;             //variável que irá salvar o tamanho do ultimo disco clicado
int torres :: tam;                  //variável que irá salvar a quatidade total de discos
QString torres :: lastDir;          //variável que irá salvar o diretório do pixmap do último disco clicado

void torres :: moveDiscos(){         //função para mover todos os discos para a posição correta, além de manter sua proporção de acordo com o
    for(int i=0; i<vet.size();i++){         //tamanho da janela
        vet[i]->resize(this->width()*vet[i]->getSize()/100,this->height()*1/20);
        vet[i]->move(this->width()*4/10+(this->width()*((40-vet[i]->getSize())/2)/100),(this->height()*6/10)-(this->height()*1/20*(i+1)));
    }
}

bool torres :: empty(){                //retorna se a torre está vazia
    if(vet.empty()) return true;
    else return false;
}

int torres :: getSizeAtual(){      //retorna o tamanho atual da torre
    return vet.size();
}

Disco *torres :: getLastDisco(){   //retorna o disco no topo da torre
    return vet.back();
}

void torres::paintEvent(QPaintEvent *event){//desenha as linhas verticais e horizontais que representam cada torre, além de escrever seus nomes
    QPainter pintor(this);
    QPen caneta(Qt::black);
    caneta.setWidth(10);
    pintor.setPen(caneta);
    pintor.drawLine(this->width()*2/5,this->height()*6/10,this->width()*8/10,this->height()*6/10);
    pintor.drawLine(this->width()*6/10,this->height()*6/10,this->width()*6/10,this->height()*2/10);
    QString texto = "TORRE ";
    QVariant v(nome);
    texto += v.toString();
    QFont f("Comic sans ms");
    pintor.setFont(f);
    pintor.drawText(this->width()*2/5,this->height()*6/10+16,texto);
    moveDiscos();                                                   //chamando a função que move todos os discos para a posição correta

}

void torres :: emiteRestart(){                                     //slot utilizado para emitir o sinal de restart quando o usuário vencer o jogo
    emit restartGame();                                            //utilizado no slot venceu em "janelas.cpp"
}

void torres :: setNewTam(int x){                                   //seta a nova quantidade de discos totais, quando a spinbox muda seu número
    tam = x;
    resetTower();
}

void torres :: destroiDiscos(){                                     //destrói todos os discos presentes na torre em questão
    for(int i=0;i<vet.size();i++)
    vet[i]->close();
vet.clear();
}

void torres :: addDisco(QString img, int sizeDisco){                //adiciona um disco a torre em questão, com seu diretório e tamanho respectivo
    Disco *d = new Disco(QPixmap(img),sizeDisco,img,this);
    d->move(this->width()*4/10+((40-d->getSize())/2),(this->height()*6/10)-(this->height()*1/20*(getSizeAtual()+1)));
    d->show();
    push(d);
}

int torres :: getName(){                                            //retorna o número respectivo da torre(o nome)
    return nome;
}

void torres::dragEnterEvent(QDragEnterEvent *event){                //evento que é chamado cada vez que um dado entra no widget quando arrastado
    event->accept();
}

void torres::dragMoveEvent(QDragMoveEvent *event){                  //evento que é chamado cada vez que um dado é arrastado sobre o widget

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {//se o dado que está sendo movido é do formato mime específicado
        if (event->source() == this) {                              //ele é aceito, e caso a fonte do evento for nesse widget ele vai continuar o evento
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();                          //caso contrário seta a ação proposta para ser o drop
        }
    } else {                                                        //se não tiver o formato o evento é ignorado
        event->ignore();
    }
}

void torres::dropEvent(QDropEvent *event){                              //evento chamado quando acontece um drop de dado no widget

    try{
    if(empty()==false and lastSize>getLastDisco()->getSize()) throw 1;  //caso a torre não esteja vazia e caso o tamanho do disco a ser dropado seja maior que o tamanho
                                                                        //do disco no topo da torre , o programa faz o throw do erro 1 e não executa o drop
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {                    //caso o dado do evento seja o mime type especificado entra na função
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);                     //em seguida faz um pop na torre de origem do disco, e constrói um novo disco
                                                                                    //baseado nos dados do disco que foi arrastado(uma cópia)
        QPixmap pixmap;                                                             // e também faz um push da cópia na torre onde esta sendo dropado
        dataStream >> pixmap;

        torreOrigem->pop();

        Disco *newDisco = new Disco(pixmap,lastSize,lastDir,this);
        newDisco->show();
        push(newDisco);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
        if(this->final == true and getSizeAtual() == this->tam) emit isOver();      //caso a torre seja a final e o tamanho atual dela for igual o total
                                                                                    //de discos, emite o sinal de jogo vencido
    } else {                                    //caso o dado no drop seja diferente do mime tipe especificado ele ignora o evento
        event->ignore();
    }

    }catch(int erro){                                           //catch do erro 1, quando um disco não pode ser inserido/dropado
        janelaDeErro("Este disco não pode ser inserido aqui");
    }
}

void torres::mousePressEvent(QMouseEvent *event)    //evento chamado a cada clique no mouse dentro do widget
{
    try{
    if(empty()) throw 2;                //se a torre estiver vazia faz o throw do erro 2 e encerra o evento
    torreOrigem = this;                 //faz o ponteiro apontar para a torre onde esta acontecendo o mousePress

    Disco *child = static_cast<Disco*>(childAt(event->pos()));      //faz um static cast para child ser igual ao disco que foi clicado

    if(child != getDiscoArrastavel())throw 1;                       //se child não for igual ao disco arrastavel faz o throw do erro 1 e encerra o evento
    else lastSize = child->getSize();                               //caso contrário o disco é arrastável então salva o tamanho do último disco clicado

    lastDir = child->getDir();                                      //também salva o diretório do disco clicado
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();                                  //nas linhas seguinte salva o pixmap do disco no itemData por meio do DataStream e define o mime type de imagens
                                                                        //além de definir o pixmap do qDrag que é a imagem que aparece do lado do cursor enquanto
    QByteArray itemData;                                                //o item for arrastado, ou seja enquanto o mouse estiver pressionado
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);



    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());


    QPixmap tempPixmap = pixmap;
    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {                             //se o mouse mover os dados fecha child
        child->close();
    } else {                                                                        //caso contrario mostra child com o pixmap do disco
        child->show();
        child->setPixmap(pixmap);
    }
    }
    catch(int erro){
        if(erro == 1){                                                                      //catch do erro 1 quando se clica em um disco não arrastavel
            janelaDeErro("Você clicou em um lugar que não contém um disco arrastável");
        }
        if(erro == 2){                                                                      //catch do erro 2 de torre vazia
            janelaDeErro("Torre vazia");
        }
    }
}

int torres ::getTam(){                          //retorna a qtde de discos totais
    return tam;
}

void torres ::setTam(int x){                   //seta uma nova quantidade de discos totais, sem dar reset na torre, ao contrario de setNewTam
    tam = x;
}

void torres :: janelaDeErro(QString str){                           //gera uma janela de aviso quando acontece alguma ação inválida, de acordo com a sring dada
    QLabel *janelinha= new QLabel(str);
    janelinha->setWindowTitle("ERRO!");
    janelinha->setGeometry(650,360,450,100);
    QPushButton *ok = new QPushButton("ok",janelinha);
    janelinha->setAttribute(Qt::WA_DeleteOnClose);
    ok->setGeometry(175,janelinha->height()-40,100,40);
    connect(ok,SIGNAL(clicked(bool)),janelinha,SLOT(close()));
    janelinha->setStyleSheet("QLabel{font-size: 15px;font-family: Comic sans ms;color: rgb(0,0, 0);background-color: rgb(255,255,255);}");
    janelinha->show();
}



