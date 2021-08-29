#include <QApplication>
#include <janelas.h>
#include <QWidget>

int main(int argc,char *argv[]){
    QApplication app(argc, argv);
    janelas *j;                         //declaração do ponteiro para a janela principal
    j = janelas :: getUnicaJanela();    //construção da janela como singleton
    j->show();                          //inicializando o programa contido na janela principal
    return app.exec();
}
