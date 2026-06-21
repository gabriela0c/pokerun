#pragma once

#include "Fases/Fase.h"
#include "Entidades/Personagens/Wartortle.h"

namespace Pokerun{

    namespace Fases{

        class FasePrimeira : public Fase{
        private:
            const int maxWartortles;
            const int maxPocas;

        private:
            std::string getNomeArquivo()const;

        public:
        FasePrimeira();
        ~FasePrimeira();
        
        void criarWartortles();
        void criarPocas();
        
        void criarInimigos();
        void criarObstaculos();
        };
    }
}