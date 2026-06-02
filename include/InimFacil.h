#pragma once

#include "Inimigo.h"

#define LARGURA_BULBASAUR 38.0f
#define ALTURA_BULBASAUR 36.0f

#define NIVEL_MALD_FACIL 1
#define N_VDS_FACIL 1

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class InimFacil : public Inimigo{
            private:
                float raio;

            public:
                InimFacil();
                ~InimFacil();

                void executar();
                void danificar(Jogador* p);
            };
        }
    }
}