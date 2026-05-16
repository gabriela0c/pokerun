#pragma once

#include "Personagem.h"

#define VEL_JOG_X 200.0f
#define VEL_JOG_Y 200.0f

#define TAM_JOG_X 50.0f
#define TAM_JOG_Y 50.0f

#define POS0_JOG_X 50.0f
#define POS0_JOG_Y 300.0f

namespace Pokerun{   

    namespace Entidades{

        namespace Personagens{

            class Jogador : public Personagem{
            protected:

            public:
                Jogador();
                ~Jogador();

                void atualizar();
            };
        }
    }
}