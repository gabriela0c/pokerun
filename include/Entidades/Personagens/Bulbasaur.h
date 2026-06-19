#pragma once

#include "Entidades/Personagens/Inimigo.h"

#define LARGURA_BULBASAUR 38.0f
#define ALTURA_BULBASAUR 36.0f

#define NIVEL_MALD_FACIL 1
#define N_VDS_FACIL 1
#define N_PTS_FACIL 100

#define RAIO_CHICOTE 110.0f
#define FORCA_CHICOTE 260.0f

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{ 

            class Bulbasaur : public Inimigo{
            private:
                int chance_veneno;
                Temporizador cd_chicote;

            public:
                Bulbasaur();
                ~Bulbasaur();

                void salvarDataBuffer();
                void carregarDataBuffer(std::istream& is);
                void salvar();

                void danificar(Jogador* p);
                void executar();

                bool chicoteVinha(Jogador* pJog);
            };
        }
    }
}