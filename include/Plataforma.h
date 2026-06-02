#pragma once

#include "Obstaculo.h"

#define TAM_PLAT_X 300.0f
#define TAM_PLAT_Y 58.0f

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            class Plataforma : public Obstaculo{
            public:
                Plataforma();
                Plataforma(sf::Vector2f pos, sf::Vector2f dim); //para construir as paredes laterais
                ~Plataforma();
            
                void executar();
                void obstaculizar(Personagens::Jogador* pJog);
            };
        }
    }
}
