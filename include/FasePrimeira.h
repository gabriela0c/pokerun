#pragma once

#include "Fase.h"

namespace Pokerun{

    namespace Fases{

        class FasePrimeira : public Fase{
        private:

        public:
        FasePrimeira(Entidades::Personagens::Jogador* pJog = nullptr);
        ~FasePrimeira();
        
        void executar();

        void criarInimigos();
        void criarObstaculos();
        //void criarInimMedios();
        //void criarObstaculosMedios();
        };
    }
}