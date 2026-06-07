#pragma once

#include "Fase.h"
#include "Wartortle.h"

namespace Pokerun{

    namespace Fases{

        class FasePrimeira : public Fase{
        private:
            const int maxWartortles;
            const int maxPocas;
        public:
        FasePrimeira(Entidades::Personagens::Jogador* pJog1 = nullptr, Entidades::Personagens::Jogador* pJog2 = nullptr);
        ~FasePrimeira();
        
        void criarWartortles();
        void criarPocas();
        
        void criarInimigos();
        void criarObstaculos();

        void executar();
        
        };
    }
}