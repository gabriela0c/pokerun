#include "FasePrimeira.h"

namespace Pokerun{

    namespace Fases{

        FasePrimeira::FasePrimeira(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2):
        Fase(pJog1, pJog2, ID::FASE_PRIMEIRA), maxInimigosMedios(5), maxInimigosFaceis(5), maxObstaculosMedios(5)
        {
            if (!textura.loadFromFile("assets/sprites/fundos/fase1.png"))
                std::cout << "ERRO: Nao foi possivel carregar a imagem de fundo!" << std::endl;
            pFigura->setTexture(&textura);
            
            if (pJog1 != nullptr) {
                pJog1->carregarTextura("assets/sprites/personagens/jogador/pikachu.png");
            }
            
            if (pJog2 != nullptr) {
                pJog2->carregarTextura("assets/sprites/personagens/jogador/raichu.png"); 
            }
            
            criarInimigos();
            criarObstaculos();
        }

        FasePrimeira::~FasePrimeira()
        {
        }

        void FasePrimeira::criarInimMedios()
        {

        }
        
        void FasePrimeira::criarObstaculosFaceis()
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
            criarChao();
            criarPlataformas();
            criarObstaculosFaceis();
        }
        
        void FasePrimeira::executar()
        {
            Fase::executar();
        }
    }
}