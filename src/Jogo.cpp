#include "jogo.h"

Pokerun::Jogo::Jogo():
pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()),
pJogador(new Entidades::Personagens::Jogador()), Fase1(pJogador)
{
    pEvento->setJogador(pJogador);
    executar();
}

Pokerun::Jogo::~Jogo()
{
    delete pJogador;
    pJogador = nullptr;

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