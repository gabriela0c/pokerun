#pragma once

#include "Entidades/Obstaculos/Obstaculo.h"

#define TAM_FOGO_X 40.0f
#define TAM_FOGO_Y 50.0f

#define LARGURA_FOGO 641
#define ALTURA_FOGO  720

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

                void salvarDataBuffer();
                void salvar();

                void executar();
                void obstaculizar(Personagens::Jogador* pJog);
            };
        }
    }
}