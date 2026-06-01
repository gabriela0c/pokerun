#pragma once

#include "Inimigo.h"

#define LARGURA_BULBASAUR 38.0f
#define ALTURA_BULBASAUR 36.0f

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