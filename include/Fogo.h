#pragma once

#include "Obstaculo.h"

#define TAM_FOGO_X 40.0f
#define TAM_FOGO_Y 50.0f

#define LARGURA_FOGO 40
#define ALTURA_FOGO  50

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            class Fogo : public Obstaculo{
            private:
                int intensidade;

                void queimar(Personagens::Jogador* pJog);

            public:
                Fogo();
                ~Fogo();

                void executar();
                void obstaculizar(Personagens::Jogador* pJog);
            };
        }
    }
}