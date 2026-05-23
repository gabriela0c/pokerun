#pragma once

#include "Obstaculo.h"

#define TAM_PLAT_X 400.0f
#define TAM_PLAT_Y 25.0f

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            class Plataforma : public Obstaculo{
            private:
                

            public:
                Plataforma();
                Plataforma(sf::Vector2f pos, sf::Vector2f dim); //para construir o chao
                ~Plataforma();
            
                void executar();
                void obstaculizar(Personagens::Jogador* pJog);
            };
        }
    }
}
