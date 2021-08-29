#ifndef JANELAS_H
#define JANELAS_H

#include <QMainWindow>
#include <torres.h>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPushButton>

class janelas : public QMainWindow
{
    Q_OBJECT
static janelas *unicaJanela;                        //ponteiro singleton para a janela
explicit janelas(QWidget *parent = nullptr);
torres *tower1;                                     //ponteiro para torres 1,2 e 3
torres *tower2;
torres *tower3;
QHBoxLayout *layoutTorres;                          //ponteiros para os layouts
QHBoxLayout *layoutBotoes;
QVBoxLayout *layoutPrincipal;
QSpinBox *caixa;                                    //ponteiro para a spinbox utilizada
QPushButton *restart;                               //ponteiro para o botão de restart
char modo;                                          //caractere que salva o modo de jogo "N" normal ou "E" especial

public:
static janelas *getUnicaJanela(){
    if(unicaJanela == NULL)
        unicaJanela=new janelas();
    return unicaJanela;
}


protected:

signals:
    void mudouJogo();
    void mesmoJogo();
    void podeConstruir(char);


public slots:
    void venceu();
    void carregar();
    void salvar();
    void jogoPilha();
    void jogoFila();
    void constroiLayout(char x);
    void destroiTorres();

};

#endif // JANELAS_H
