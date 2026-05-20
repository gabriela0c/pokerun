#pragma once

#include "Obstaculo.h"

#define TAM_PLAT_X 400.0f
#define TAM_PLAT_Y 25.0f

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            class Plataforma : public Obstaculo{
            private:
                sf::Vector2f dimensao;

            public:
                Plataforma();
                ~Plataforma();
            
                void executar();
                void obstaculizar(Jogador* pJog);
            };
        }
    }
}
