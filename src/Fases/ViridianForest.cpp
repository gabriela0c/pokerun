#include "Fases/ViridianForest.h"

namespace Pokerun{

    namespace Fases{

        ViridianForest::ViridianForest(): Fase(), maxWartortles(4), maxPocas(4)
        {
            setTextura("assets/sprites/fundos/fase1.png", sf::IntRect({0, 0}, {(int)WIN_SIZE_X, (int)WIN_SIZE_Y}));
        }

        ViridianForest::~ViridianForest()
        {

        }

        std::string ViridianForest::getNomeArquivo()const
        {
            return "Fase1.dat";
        }

        void ViridianForest::criarWartortles()
        {
            Entidades::Personagens::Inimigo* pWart = nullptr;
            int n = rand() % 2;
            for(int i = n; i < maxWartortles; i++){
                pWart = new Entidades::Personagens::Wartortle();
                adicionarInimigos(pWart);
                pWart = nullptr;
            }
        }
        
        void ViridianForest::criarPocas()
        {
            int n = rand() % 2;

            for(int i = n; i < maxPocas; i++)
            {
                Entidades::Obstaculos::Poca* pPoca = new Entidades::Obstaculos::Poca();
                
                colocaNaPlataforma(pPoca);

                adicionarObstaculos(pPoca);
            }
        }

        void ViridianForest::criarInimigos()
        {
            criarBulbasaurs();
            criarWartortles();
        }

        void ViridianForest::criarObstaculos()
        {
            criarPocas();
        }
    }
}