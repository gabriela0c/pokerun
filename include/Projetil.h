#pragma once
#include "Entidade.h"
#include "Jogador.h"

#define LARGURA_PROJ 15.0f
#define ALTURA_PROJ 15.0f

#define TAMANHO_PROJ_X 104
#define TAMANHO_PROJ_Y 169

#define VEL_PROJETIL_X 300.0f
#define DANO_PROJETIL 3

namespace Pokerun {
    namespace Entidades {

        class Projetil : public Entidade {
            private:
                float vel_x;

            public:
            Projetil(float velX);
            ~Projetil();

            int getDano() const;
            
            virtual void executar();
        };

    }
}