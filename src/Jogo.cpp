#include "jogo.h"

Pokerun::Jogo::Jogo():
pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()), Lentidades()
{
    criarPersonagens();
    executar();
}

Pokerun::Jogo::~Jogo()
{
    auto* pAux = Lentidades.getPrimeiro();

    while(pAux != nullptr){
        if(pAux->getInfo()){
            delete pAux->getInfo();
        }
        pAux = pAux->getProx();
    }

    Gerenciadores::GerenciadorGrafico::destruir();
    Gerenciadores::GerenciadorEvento::destruir();
}

void Pokerun::Jogo::criarPersonagens()
{
    Entidades::Personagens::Jogador* jogador = new Entidades::Personagens::Jogador();
    Entidades::Personagens::Inimigo* inimigo1 = new Entidades::Personagens::Inimigo();
    Entidades::Personagens::Inimigo* inimigo2 = new Entidades::Personagens::Inimigo();
    
    pEvento->setJogador(jogador);
    
    inimigo1->setJogador(jogador);
    inimigo2->setJogador(jogador);
    

    Lentidades.incluir(static_cast<Entidades::Entidade*>(inimigo1));
    Lentidades.incluir(static_cast<Entidades::Entidade*>(inimigo2));
    Lentidades.incluir(static_cast<Entidades::Entidade*>(jogador));
}

void Pokerun::Jogo::executar()
{
    while(pGrafico->verificaJanelaAberta()){
        pGrafico->limpaJanela();

        pEvento->executar();
        Lentidades.percorrer();

        auto* pAux = Lentidades.getPrimeiro();
        while(pAux!=nullptr){
            if(pAux->getInfo()){
                pGrafico->desenhaElementos((pAux->getInfo())->getCorpo());
            }
            pAux = pAux->getProx();
        }

        pGrafico->mostraElementos();
    }
}