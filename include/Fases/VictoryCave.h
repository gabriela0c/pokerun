#pragma once

#include "Fases/Fase.h"

#define TAM_CAVERNA_X 1406 //esse é o tamanho dos sprites nao o que ele tem na tela
#define TAM_CAVERNA_Y 913

namespace Pokerun{

    namespace Fases{

        class VictoryCave : public Fase{
        private:
            const int maxCharizards;
            const int maxFogos;

        public:
            VictoryCave();
            ~VictoryCave();
            
            void criarCharizards();
            void criarFogos();
            
            void criarInimigos();
            void criarObstaculos();

            std::string getNomeArquivo()const;
        };
    }
}