#include "jogo.h"

Pokerun::Jogo::Jogo():
pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()),
gColisoes(), Lentidades()
{
    criarEntidades();
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

void Pokerun::Jogo::criarEntidades()
{
    Entidades::Personagens::Jogador* jogador = new Entidades::Personagens::Jogador();

    Entidades::Obstaculos::Plataforma* pPlat = nullptr;
    for(int i = 0; i < 3; i++){
        pPlat = new Entidades::Obstaculos::Plataforma();
        Lentidades.incluir(static_cast<Entidades::Entidade*>(pPlat));
        gColisoes.incluirObstaculo(pPlat); //upcasting automatico e seguro por poliformismo, o mesmo vale para outros derivados de entidade
        pPlat = nullptr;
    }

    pPlat = new Entidades::Obstaculos::Plataforma({0.0f, WIN_SIZE_Y},{WIN_SIZE_X, 30.0f}); //chao
    Lentidades.incluir(pPlat);
    gColisoes.incluirObstaculo(pPlat);
    
    Entidades::Personagens::Inimigo* pInim = nullptr;
    for(int i = 0; i < 3; i++){
        pInim = new Entidades::Personagens::Inimigo();
        pInim->setJogador(jogador);
        Lentidades.incluir(pInim);
        gColisoes.incluirInimigo(pInim);
        pInim = nullptr;
    }
    
    pEvento->setJogador(jogador);
    gColisoes.setJogador(jogador);
    Lentidades.incluir(jogador);
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