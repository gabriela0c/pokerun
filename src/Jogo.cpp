#include "jogo.h"

Pokerun::Jogo::Jogo():
pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()), Lpersonagens()
{
    Lpersonagens.clear();
    criarPersonagens();
    executar();
}

Pokerun::Jogo::~Jogo()
{
    for (int i = 0 ; i < (int)Lpersonagens.size(); i++){
        if(Lpersonagens[i]){
            delete Lpersonagens[i];
            Lpersonagens[i] = nullptr;
        }
    }

    Lpersonagens.clear();

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
    

    Lpersonagens.push_back(static_cast<Entidades::Personagens::Personagem*>(inimigo1));
    Lpersonagens.push_back(static_cast<Entidades::Personagens::Personagem*>(inimigo2));
    Lpersonagens.push_back(static_cast<Entidades::Personagens::Personagem*>(jogador));
}

void Pokerun::Jogo::executar()
{
    while(pGrafico->verificaJanelaAberta()){
        pGrafico->limpaJanela();

        pEvento->executar();
        
        for(int i = 0; i < (int)Lpersonagens.size(); i++){
            if(Lpersonagens[i]){
                Lpersonagens[i]->executar();
                pGrafico->getWindow()->draw(Lpersonagens[i]->getCorpo());
            }
        }

        pGrafico->mostraElementos();
    }
}