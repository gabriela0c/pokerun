#include "Fases/FasePrimeira.h"

namespace Pokerun{

    namespace Fases{

        FasePrimeira::FasePrimeira(): Fase(), maxWartortles(4), maxPocas(4)
        {
            setTextura("assets/sprites/fundos/fase1.png", sf::IntRect({0, 0}, {(int)WIN_SIZE_X, (int)WIN_SIZE_Y}));
        }

        FasePrimeira::~FasePrimeira()
        {

        }

        std::string FasePrimeira::getNomeArquivo()const
        {
            return "Fase1.dat";
        }

        void FasePrimeira::criarWartortles()
        {
            Entidades::Personagens::Inimigo* pWart = nullptr;
            int n = rand() % 2;
            for(int i = n; i < maxWartortles; i++){
                pWart = new Entidades::Personagens::Wartortle();
                adicionarInimigos(pWart);
                pWart = nullptr;
            }
        }
        
        void FasePrimeira::criarPocas()
        {
            int n = rand() % 2;

            for(int i = n; i < maxPocas; i++)
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
            criarPocas();
        }
    }
}