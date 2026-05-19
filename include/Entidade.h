#pragma once
//posicao e corpo sao elementos comuns a todas entidades, obstaculos tambem as terao, portanto a necessidade da classe
#include <SFML/Graphics.hpp>

namespace Pokerun{

    namespace Entidades{

        class Entidade{
        protected:
            float x;
            float y;
            sf::RectangleShape corpo;
        
        public:
            Entidade(const sf::Vector2f tam = {0.0f, 0.0f});
            virtual ~Entidade();

            const sf::RectangleShape& getCorpo()const;

            virtual void executar() = 0; //nome alterado de atualizar para executar por requisito do diagrama
        };
    }
}
