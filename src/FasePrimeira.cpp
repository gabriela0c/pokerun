#include "FasePrimeira.h"

namespace Pokerun{

    namespace Fases{

        FasePrimeira::FasePrimeira(Entidades::Personagens::Jogador* pJog):
        Fase(pJog, ID::FASE_PRIMEIRA)
        {
            criarInimigos();
            criarObstaculos();
        }

        FasePrimeira::~FasePrimeira()
        {
            
        }

        void FasePrimeira::executar()
        {
            Fase::executar();
        }

        void FasePrimeira::criarInimigos()
        {
            criarInimFaceis();
        }

        void FasePrimeira::criarObstaculos()
        {
            criarPlataformas();
        }
    }
}