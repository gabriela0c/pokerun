#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class Personagem{
            protected:
                sf::RectangleShape corpo;
                const sf::Vector2f vel;
                bool podeAndar;
                bool paraEsquerda;
                sf::Clock relogio;
                float dt;

            public:
                Personagem(const sf::RectangleShape crp = sf::RectangleShape(), const sf::Vector2f v = {});
                virtual ~Personagem();

                const sf::RectangleShape& getCorpo() const;

                void andar(const bool pEsquerda);
                void parar();
                void atualizarPosicao();

                virtual void atualizar() = 0;
            };
        }
    }
}