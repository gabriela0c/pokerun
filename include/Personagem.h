#pragma once
//velocidade esta aqui pois eh comum a todos os personagens
#include "Entidade.h"

#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class Personagem : public Entidade{
            protected:
                const sf::Vector2f vel;
                sf::Clock relogio;
                float dt;

            public:
                Personagem(const sf::Vector2f tam = {}, const sf::Vector2f v = {});
                virtual ~Personagem();

                virtual void mover() = 0;
                virtual void executar() = 0;
            };
        }
    }
}