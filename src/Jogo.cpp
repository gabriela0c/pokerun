#include "jogo.h"

Pokerun::Jogo::Jogo():
pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()),
gColisoes(), Lentidades()
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

    Entidades::Obstaculos::Plataforma* pPlat = nullptr;
    for(int i = 0; i < 3; i++){
        pPlat = new Entidades::Obstaculos::Plataforma();
        Lentidades.incluir(static_cast<Entidades::Entidade*>(pPlat));
        gColisoes.incluirObstaculo(pPlat); //upcasting automatico e seguro
        pPlat = nullptr;
    }

    Entidades::Personagens::Inimigo* pInim = nullptr;
    for(int i = 0; i < 3; i++){
        pInim = new Entidades::Personagens::Inimigo();
        pInim->setJogador(jogador);
        Lentidades.incluir(static_cast<Entidades::Entidade*>(pInim));
        gColisoes.incluirInimigo(pInim);
        pInim = nullptr;
    }
    
    pEvento->setJogador(jogador);
    gColisoes.setJogador(jogador);
    Lentidades.incluir(static_cast<Entidades::Entidade*>(jogador));
}

void Pokerun::Jogo::executar()
{
    while(pGrafico->verificaJanelaAberta()){
        pGrafico->limpaJanela();

        pEvento->executar();
        Lentidades.percorrer();
        gColisoes.executar();

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