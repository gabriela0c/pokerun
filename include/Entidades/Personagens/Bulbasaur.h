#pragma once

#include "Entidades/Personagens/Inimigo.h"

#define LARGURA_BULBASAUR 38.0f
#define ALTURA_BULBASAUR 36.0f

#define NIVEL_MALD_FACIL 1
#define N_VDS_FACIL 1
#define N_PTS_FACIL 100

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{ 

            class Bulbasaur : public Inimigo{
            private:
                int chance_veneno;
                float pos_x_inicial;
                float ultima_pos_x; //para evitar que ele fique travado em paredes
                bool pos_inicial_salva;

            public:
                Bulbasaur();
                ~Bulbasaur();

                void salvarDataBuffer();
                void carregarDataBuffer(std::istream& is);
                void salvar();

                void executar();
                void danificar(Jogador* p);
            };
        }
    }
}