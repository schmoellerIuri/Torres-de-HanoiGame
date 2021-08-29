#include "janelas.h"
#include <QDebug>
#include <QPixmap>
#include <QFrame>
#include <QLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <torrenormal.h>
#include <torreespecial.h>


janelas::janelas(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Torres de Hanoi");                  //definindo nome e formato inicial da janela
    setGeometry(0,0,1366,720);

    modo = 'N';                                        //definindo o modo padrão de jogo "N" (normal, torres de hanói padrão)

    layoutTorres = new QHBoxLayout;                    //construindo o layout inicial das torres e o layout principal da janela

    QFrame *frame = new QFrame;                        //layout principal sendo uma caixa vertical de layouts composta de duas caixas
    layoutBotoes = new QHBoxLayout;                    //horizontais de layout(uma das torres, outra dos botões de restart e spinbox)
    layoutBotoes->addStretch();

    restart = new QPushButton("Restart",this);         //definindo layout dos botoes
    layoutBotoes->addWidget(restart);
    caixa = new QSpinBox(this);
    caixa->setRange(3,8);
    layoutBotoes->addWidget(caixa);
    layoutBotoes->addStretch();

    layoutPrincipal = new QVBoxLayout(frame);         //definindo o layout principal
    layoutPrincipal->addLayout(layoutTorres);
    layoutPrincipal->addLayout(layoutBotoes);

    setCentralWidget(frame);                          //o frame onde o layout foi construido sobre é definido como widget central da janela
    constroiLayout(modo);

    QMenuBar *barra = new QMenuBar(this);             //agora construindo a barra de menus da janela

    QMenu *menuArquivo = new QMenu("Arquivo",this);   //adicionando o menu de arquivos da janela
    barra->addMenu(menuArquivo);

    QMenu *newGame = new QMenu("Novo Jogo",this);     //adicionando subMenu de novo jogo no menu de arquivos
    menuArquivo -> addMenu(newGame);

    QAction *jogoPilha = new QAction("Normal  (Tira-se de cima e coloca-se em cima)",this); //criando botão que será utilizado para selecionar a opção de jogo
    newGame ->addAction(jogoPilha);                                                         //com torre especial, baseado em uma fila de discos na torre
                                                                                            //e adicionando no subMenu de novo jogo.

    QAction *jogoFila = new QAction("Torre inversa  (Tira-se de baixo e coloca-se em cima)",this);//criando botão que será utilizado para selecionar a opçao
    newGame ->addAction(jogoFila);                                                                //de jogo de torre de hanói normal(baseado em pilha de discos)
                                                                                                  //e adicionando no subMenu de novo jogo.

    QAction *carregar = new QAction("Carregar",this);    //criando botão para carregar um jogo passado
    menuArquivo->addAction(carregar);

    QAction *salvar = new QAction("Salvar",this);        //criando botão para salvar o jogo atual
    menuArquivo->addAction(salvar);

    QAction *sair = new QAction("Sair",this);            //criando botão para sair do jogo
    menuArquivo->addAction(sair);

    connect (carregar, SIGNAL(triggered(bool)),this, SLOT(carregar()));     //conectando o botão de carregar com a função responsável por carregar um jogo passado

    connect (salvar, SIGNAL(triggered(bool)),this, SLOT(salvar()));         //conectando o botão de salvar com a função responsável por salvar o jogo atual

    connect (sair, SIGNAL(triggered(bool)),this, SLOT(close()));            //conectando o botão de sair com a função close(fecha o jogo)

    connect (jogoFila, SIGNAL(triggered(bool)),this, SLOT(jogoFila()));     //conectando o botão de jogoFila com a funçao responsável por mudar o modo de jogo para torre Especial
    connect (jogoPilha, SIGNAL(triggered(bool)),this, SLOT(jogoPilha()));   //conectando o botão de jogoPilha com a função responsável por mudar modo de jogo para torre Normal de hanói

    connect(this,SIGNAL(mudouJogo()),this,SLOT(destroiTorres()));                   //conectando o sinal enviado quando o modo de jogo muda para destruir as torres atuais.
    connect(this,SIGNAL(podeConstruir(char)),this,SLOT(constroiLayout(char)));      //conectando o sinal enviado quando as torres podem ser construídas novamente para construir
}                                                                                   //novas torres, quando mudamos o modo de jogo.

janelas *janelas:: unicaJanela = NULL;          //ponteiro estático para o singleton

void janelas :: venceu(){                                               //slot executado quando o usuário vence
    QLabel *janelinha= new QLabel("Você venceu, deseja continuar?");    //criando janela que avisa o usuário que venceu e da duas opções: continuar ou sair
    janelinha->setGeometry(650,360,360,100);
    janelinha->setWindowTitle("https://www.youtube.com/watch?v=1Mcdh2Vf2Xk&t=32s");
    QPushButton *continuar = new QPushButton("continuar",janelinha);    //botão continuar reseta o jogo no mesmo modo
    janelinha->setAttribute(Qt::WA_DeleteOnClose);
    continuar->setGeometry(0,janelinha->height()-40,100,40);
    connect(continuar,SIGNAL(clicked(bool)),tower3,SLOT(emiteRestart())); //torre 3 vai emitir o sinal para resetar o jogo
    connect(continuar,SIGNAL(clicked(bool)),janelinha,SLOT(close()));

    QPushButton *sair = new QPushButton("sair", janelinha);             //botão sair encerra o programa
    sair->setGeometry(260,janelinha->height()-40,100,40);
    connect(sair,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(sair,SIGNAL(clicked(bool)),janelinha,SLOT(close()));
    janelinha->setStyleSheet("QLabel{font-size: 15px;font-family: Comic sans ms;color: rgb(0,0, 0);background-color: rgb(255,255,255);}");
    janelinha->show();

}

void janelas :: carregar(){                                                    //slot executado quando o usuário clica o botão de carregar no menu
   QString fileName = QFileDialog::getOpenFileName(this,"Escolha o Arquivo");

   QFile file(fileName);

   if (!file.open(QIODevice::ReadOnly))
       return;

   QDataStream in(&file);

   QString buffer;                                   //a função vai abrir o arquivo obtido em OpenFileName, vai receber o modo de jogo no buffer e muda-lo
   QString percorre;                                 //em seguida irá destruir os discos que foram criados com a função jogoFila()/JogoPilha() e em seguida
   qint32 x,y;                                       //ler a quantidade de discos de cada torre e inseri-los conforme a ordem no arquivo aberto.

   in >> buffer;

   if(buffer == "N")
   jogoPilha();
   if(buffer == "E")
   jogoFila();

   tower1->destroiDiscos();
   tower2->destroiDiscos();
   tower3->destroiDiscos();

   in >> percorre;
   in >> x;
   torres :: setTam(x);
   in >> percorre;

   in >> x;
   for(int i=0;i<x;i++){
       in >> percorre;
       in >>buffer;
       in >> percorre;
       in >> y;
       tower1->addDisco(buffer,y);
   }

   in >> percorre;
   in >> percorre;
   in >> x;
   for(int i=0;i<x;i++){
       in >> percorre;
       in >>buffer;
       in >> percorre;
       in >> y;
       tower2->addDisco(buffer,y);
   }

   in >> percorre;
   in >> percorre;
   in >> x;
   for(int i=0;i<x;i++){
       in >> percorre;
       in >>buffer;
       in >> percorre;
       in >> y;
       tower3->addDisco(buffer,y);
   }

}

void janelas :: salvar(){                                                 //este slot será chamado quando o usuário clicar no botão salvar no menu
QString fileName = QFileDialog::getSaveFileName(this,"Escolha o Local");
QFile file(fileName);
   if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
       return;

   QDataStream out(&file);                                                //a função irá criar o arquivo no diretório obtido pelo SaveFileName
   QString texto;                                                         //e em seguida irá utilizar do QDataStream para formatar e salvar os dados
   texto=modo;                                                            //que serão necessários para a função carregar(), como modo de jogo, qtde de discos
   out << texto <<" "<<(qint32)tower1->getTam() << " ";                   //em cada torre, as cores de cada disco e seus respectivos tamanhos
   out << (qint32)tower1->getSizeAtual()<< " ";
   for(int i=0;i<tower1->getSizeAtual();i++){
   out << tower1->vet[i]->getDir()<<" ";
   out << (qint32)tower1->vet[i]->getSize()<<" ";
   }
   out<<" ";
   out << (qint32)tower2->getSizeAtual()<< " ";
   for(int i=0;i<tower2->getSizeAtual();i++){
   out << tower2->vet[i]->getDir()<<" ";
   out << (qint32)tower2->vet[i]->getSize()<<" ";
   }
   out<<" ";
   out << (qint32)tower3->getSizeAtual()<< " ";
   for(int i=0;i<tower3->getSizeAtual();i++){
   out << tower3->vet[i]->getDir()<<" ";
   out << (qint32)tower3->vet[i]->getSize()<<" ";
   }
   out<<" ";
}

void janelas :: jogoFila(){                         //slot executado quando o modo de jogo selecionado for o de torre Especial(baseado em fila)
    char aux = modo;                                //emite o sinal mudouJogo caso o modo seja diferente do anterior, e mesmoJogo caso contrário
    modo = 'E';
    if(aux != modo) emit mudouJogo();
    else emit mesmoJogo();
}

void janelas :: jogoPilha(){           //slot executado quando o modo de jogo selecionado for o de torre Normal(baseado em pilha)
    char aux = modo;                   //emite o sinal mudouJogo caso o modo seja diferente do anterior, e mesmoJogo caso contrário
    modo= 'N';
    if(aux != modo) emit mudouJogo();
    else emit mesmoJogo();
}


void janelas :: constroiLayout(char x){                             //constrói todo o layout das torres na janela, e faz as conexões com o botão restart
    if(x == 'N'){                                                   //e a spinbox que adiciona ou remove discos do jogo

        tower1 = new torreNormal(1,true);                           //fazendo o polimorfismo dinâmico das torres, que podem ser normais ou especiais
        tower2 = new torreNormal(2,false);                          //de acordo com o modo de jogo
        tower3 = new torreNormal(3,false,true);
    }
    else if(x == 'E'){

        tower1 = new torreEspecial(1,true);
        tower2 = new torreEspecial(2,false);
        tower3 = new torreEspecial(3,false,true);
    }
    layoutTorres->addWidget(tower1);
    layoutTorres->addWidget(tower2);
    layoutTorres->addWidget(tower3);

    connect(restart,SIGNAL(clicked(bool)),tower1,SLOT(resetTower()));       //botão de restart reseta todas as torres para o estado inicial das mesmas
    connect(restart,SIGNAL(clicked(bool)),tower2,SLOT(resetTower()));
    connect(restart,SIGNAL(clicked(bool)),tower3,SLOT(resetTower()));

    connect(caixa,SIGNAL(valueChanged(int)),tower1,SLOT(setNewTam(int)));   //spinbox quando alterada no seu valor, muda a quantidade de discos totais do jogo e reseta as mesmas
    connect(caixa,SIGNAL(valueChanged(int)),tower2,SLOT(setNewTam(int)));
    connect(caixa,SIGNAL(valueChanged(int)),tower3,SLOT(setNewTam(int)));

    connect(tower3,SIGNAL(isOver()),this,SLOT(venceu()));                       //quando o sinal isOver é emitido o usuário vence o jogo

    connect(tower3,SIGNAL(restartGame()),tower1,SLOT(resetTower()));            //quando o sinal restartGame(emitido quando o botão continuar na janela de vencer o jogo é pressionado)
    connect(tower3,SIGNAL(restartGame()),tower2,SLOT(resetTower()));            //é emitido as torres são resetadas para seu estado inicial
    connect(tower3,SIGNAL(restartGame()),tower3,SLOT(resetTower()));

    connect(this,SIGNAL(mesmoJogo()),tower1,SLOT(resetTower()));                //se o novo jogo é do mesmo modo do anterior, as torres são resetadas
    connect(this,SIGNAL(mesmoJogo()),tower2,SLOT(resetTower()));                //para o seu estado inicial
    connect(this,SIGNAL(mesmoJogo()),tower3,SLOT(resetTower()));
}

void janelas :: destroiTorres(){                    //função que será executada quando o modo de jogo mudar
    layoutTorres->removeWidget(tower1);             //a função vai deletar o conteudo apontado pelos ponteiros das 3 torres
    layoutTorres->removeWidget(tower2);             //e remove-las do layout das torres
    layoutTorres->removeWidget(tower3);             //em seguida irá emitir o sinal para poder construir um novo layout
    delete tower1;                                  //com as novas torres e um modo de jogo diferente
    delete tower2;
    delete tower3;
    emit podeConstruir(modo);
}






