#pragma once 

#include "Inimigo.h"

#define LARGURA_SQUIRTLE 50
#define ALTURA_SQUIRTLE 50

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class InimMedio : public Inimigo{
            private:
                int tamanho;

            public:
                InimMedio();
                ~InimMedio();

                void danificar(Jogador* p);
                void executar();
            };
        }
    }
}