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
            Entidades::Personagens::Inimigo* pWart = nullptr;
            int n = rand() % 2 + 3; //cria de 3 a 4 inimigos - tabela 1 N5
            for(int i = 0; i < n; i++){
                pWart = new Entidades::Personagens::Wartortle();
                adicionarInimigos(pWart);
                pWart = nullptr;
            }
        }
        
        void FasePrimeira::criarPocas()
        {
            //mínimo 3 e máximo 5 
            int n = rand() % (maxPocas - 2) + 3;

            for(int i = 0; i < n; i++)
            {
                Entidades::Obstaculos::Poca* pPoca = new Entidades::Obstaculos::Poca();
                
                colocaNaPlataforma(pPoca);

                adicionarObstaculos(pPoca);
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