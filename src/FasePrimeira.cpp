#include "FasePrimeira.h"

namespace Pokerun{

    namespace Fases{

        FasePrimeira::FasePrimeira(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2):
        Fase(pJog1, pJog2, ID::FASE_PRIMEIRA), maxInimigosMedios(5), maxInimigosFaceis(5), maxObstaculosMedios(5)
        {
            GC.setFase1(this);
            
            setTextura("assets/sprites/fundos/fase1.png", sf::IntRect({0, 0}, {(int)WIN_SIZE_X, (int)WIN_SIZE_Y}));
            
            sf::Vector2f tam1 = pJog1->getFig().getSize();
            sf::Vector2f tam2 = pJog2->getFig().getSize();
            //o problema aqui ta sendo carregar fora da fase, mas se nao carrega fora da fase nao funciona tambem??
            
            if (pJog1 != nullptr) {
                pJog1->setTextura("assets/sprites/personagens/jogador/pikachu.png", sf::IntRect({0, 0}, {(int)tam1.x, (int)tam1.y}));
            }
            
            if (pJog2 != nullptr) {
                pJog2->setTextura("assets/sprites/personagens/jogador/raichu.png", sf::IntRect({0, 0}, {(int)tam2.x, (int)tam2.y}));
            }
            
            criarInimigos();
            criarObstaculos();
        }

        FasePrimeira::~FasePrimeira()
        {
        }

        void FasePrimeira::criarInimMedios()
        {
            Entidades::Personagens::Inimigo* pInim = nullptr;
            int n = rand() % 3 + 3; //cria de 3 a 5 inimigos - tabela 1 N5
            for(int i = 0; i < n; i++){
                pInim = new Entidades::Personagens::InimMedio();
                pInim->setJogador1(pJogador1);
                pInim->setJogador2(pJogador2);
                lista_ents.incluir(static_cast<Entidades::Entidade*>(pInim));
                GC.incluirInimigo(pInim);
                pInim = nullptr;
            }
        }
        
        void FasePrimeira::criarObstaculosMedios()
        {
            //mínimo 3 e máximo 5 
            int n = rand() % (maxObstaculosMedios - 2) + 3;

            for(int i = 0; i < n; i++)
            {
                Entidades::Obstaculos::ObstMedio* pObs = new Entidades::Obstaculos::ObstMedio();
                
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
            criarInimFaceis();
            criarInimMedios();
        }

        void FasePrimeira::criarObstaculos()
        {
            criarPlataformas();
            criarObstaculosMedios();
        }
        
        void FasePrimeira::executar()
        {
            Fase::executar();
        }
    }
}