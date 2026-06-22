#pragma once

#include "Fases/Fase.h"
#include "Entidades/Personagens/Wartortle.h"

namespace Pokerun{

    namespace Fases{

        class ViridianForest : public Fase{
        private:
            const int maxWartortles;
            const int maxPocas;

        public:
            ViridianForest();
            ~ViridianForest();
        
            void criarWartortles();
            void criarPocas();
        
            void criarInimigos();
            void criarObstaculos();

            std::string getNomeArquivo()const;
        };
    }
}