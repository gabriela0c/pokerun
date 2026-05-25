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

    pPlat = new Entidades::Obstaculos::Plataforma({0.0f, WIN_SIZE_Y - 30.0f}, {WIN_SIZE_X, 30.0f}); 
    //alteração do chão para que ele apareça na tela: antes eu não estava vendo, ai mudei a forma com que ele é criado e a cor
    Lentidades.incluir(pPlat);
    gColisoes.incluirObstaculo(pPlat);

    //parede invisível na esquerda
    Entidades::Obstaculos::Plataforma* pParedeEsq = new Entidades::Obstaculos::Plataforma({-100.0f, 0.0f}, {100.0f, WIN_SIZE_Y});
    Lentidades.incluir(pParedeEsq);
    gColisoes.incluirObstaculo(pParedeEsq);

    //parede invisível na direita
    Entidades::Obstaculos::Plataforma* pParedeDir = new Entidades::Obstaculos::Plataforma({WIN_SIZE_X, 0.0f}, {100.0f, WIN_SIZE_Y});
    Lentidades.incluir(pParedeDir);
    gColisoes.incluirObstaculo(pParedeDir);
    //criei as pareces pq toda hora o jogador caia/sumia da tela
    
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
                pAux->getInfo()->desenhar();
            } 
            pAux = pAux->getProx();
        }

        pGrafico->mostraElementos();
    }
}