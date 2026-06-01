#include "jogo.h"

Pokerun::Jogo::Jogo():
pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()),
pJogador1(new Entidades::Personagens::Jogador(true)), pJogador2(new Entidades::Personagens::Jogador(false)), Fase1(pJogador1, pJogador2)
{
    pEvento->setJogador1(pJogador1);
    pEvento->setJogador2(pJogador2);
    executar();
}

Pokerun::Jogo::~Jogo()
{
    delete pJogador1;
    pJogador1 = nullptr;

    delete pJogador2;
    pJogador2 = nullptr;

    Gerenciadores::GerenciadorGrafico::destruir();
    Gerenciadores::GerenciadorEvento::destruir();
}

void Pokerun::Jogo::executar()
{
    while(pGrafico->verificaJanelaAberta()){
        pGrafico->limpaJanela();

        pEvento->executar();
        
        Fase1.executar();

        pGrafico->mostraElementos();
    }
}