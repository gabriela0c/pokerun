#pragma once

#include "Entidade.h"

class Jogador;

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            class Obstaculo : public Entidade{
            protected:
                bool danoso;
                
            public:
                Obstaculo(const sf::Vector2f tam = {0.0f, 0.0f}, bool d = false);
                virtual ~Obstaculo();

                virtual void executar() = 0;
                virtual void obstaculizar(Jogador* pJog) = 0;
            };
        }
    }
}