#pragma once 

#include "Inimigo.h"

#define LARGURA_WARTORTLE 46.0f
#define ALTURA_WARTORTLE 43.0f

#define NIVEL_MALD_MEDIO 2
#define N_VDS_MEDIO 3
#define N_PTS_MEDIO 300

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class Wartortle : public Inimigo{ //Inim Medio
            private:
                int massa;

            public:
                Wartortle();
                ~Wartortle();

                void danificar(Jogador* p);
                void executar();
            };
        }
    }
}