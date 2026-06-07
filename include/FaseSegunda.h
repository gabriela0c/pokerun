#pragma once

#include "Fase.h"
#include "Charizard.h"

namespace Pokerun{

    namespace Fases{

        class FaseSegunda : public Fase{
        private:
            const int maxCharizards;
            const int maxBulbasaurs;
            const int maxFogos;
        public:
        FaseSegunda(Entidades::Personagens::Jogador* pJog1 = nullptr, Entidades::Personagens::Jogador* pJog2 = nullptr);
        ~FaseSegunda();
        
        void criarCharizards();
        void criarFogos();
        
        void criarInimigos();
        void criarObstaculos();

        void executar();
        
        };
    }
}