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
                sf::Vector2f direcao;
                sf::Clock relogio;
                float dt;

            public:
                Personagem(const sf::RectangleShape crp = sf::RectangleShape(), const sf::Vector2f v = {});
                virtual ~Personagem();

                const sf::RectangleShape& getCorpo() const;

                void setDirecao(sf::Vector2f dir);
                void atualizarPosicao();

                virtual void atualizar() = 0;
            };
        }
    }
}