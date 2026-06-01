#pragma once 

#include "Inimigo.h"

#define LARGURA_WARTORTLE 46.0f
#define ALTURA_WARTORTLE 43.0f

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