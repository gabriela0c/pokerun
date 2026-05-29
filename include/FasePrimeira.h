#pragma once

#include "Fase.h"

namespace Pokerun{

    namespace Fases{

        class FasePrimeira : public Fase{
        private:
            const int maxInimigosMedios;
            const int maxInimigosFaceis;
            const int maxObstaculosMedios;

        public:
       FasePrimeira(Entidades::Personagens::Jogador* pJog1 = nullptr, Entidades::Personagens::Jogador* pJog2 = nullptr);
        ~FasePrimeira();
        
        void criarInimMedios();
        void criarObstaculosMedios();
        
        void criarInimigos();
        void criarObstaculos();

        void executar();
        
        };
    }
}