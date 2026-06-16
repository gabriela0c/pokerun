#include "Fases/FasePrimeira.h"

namespace Pokerun{

    namespace Fases{

        FasePrimeira::FasePrimeira(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2):
        Fase(pJog1, pJog2), maxWartortles(4), maxPocas(5)
        {
            setTextura("assets/sprites/fundos/fase1.png", sf::IntRect({0, 0}, {(int)WIN_SIZE_X, (int)WIN_SIZE_Y}));
            criarCenario();
        }

        FasePrimeira::~FasePrimeira()
        {
        }

        void FasePrimeira::criarWartortles()
        {
            Entidades::Personagens::Inimigo* pInim = nullptr;
            int n = rand() % 2 + 3; //cria de 3 a 4 inimigos - tabela 1 N5
            for(int i = 0; i < n; i++){
                pInim = new Entidades::Personagens::Wartortle();
                pInim->setJogador1(pJogador1);
                pInim->setJogador2(pJogador2);
                lista_ents.incluir(static_cast<Entidades::Entidade*>(pInim));
                GC.incluirInimigo(pInim);
                pInim = nullptr;
            }
        }
        
        void FasePrimeira::criarPocas()
        {
            //mínimo 3 e máximo 5 
            int n = rand() % (maxPocas - 2) + 3;

            for(int i = 0; i < n; i++)
            {
                Entidades::Obstaculos::Poca* pObs = new Entidades::Obstaculos::Poca();
                
                int indicePlataforma = rand() % posicoesPlataformas.size();
                sf::FloatRect base = posicoesPlataformas[indicePlataforma];
                
                float larguraObs = pObs->getFig().getSize().x;
                float alturaObs  = pObs->getFig().getSize().y;
                
                int limiteEsq = (int)base.position.x;
                int limiteDir = (int)(base.position.x + base.size.x - larguraObs);
                
                if (limiteDir <= limiteEsq) {
                    limiteDir = limiteEsq + 1;
                }

                float novoX = (float)(rand() % (limiteDir - limiteEsq + 1) + limiteEsq);
                float novoY = base.position.y - alturaObs;

                pObs->getFig().setPosition({novoX, novoY});

                lista_ents.incluir(static_cast<Entidades::Entidade*>(pObs));
                GC.incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(pObs));
            }
        }

        void FasePrimeira::criarInimigos()
        {
            criarBulbasaurs();
            criarWartortles();
        }

        void FasePrimeira::criarObstaculos()
        {
            criarPlataformas();
            criarPocas();
        }
        
        void FasePrimeira::executar()
        {
            Fase::executar();
        }
    }
}