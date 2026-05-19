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
           //sobrecarga de metodo necessaria porque draw da sfml 3 nao aceita referencias nao const
            sf::RectangleShape& getCorpo(); 
            const sf::RectangleShape& getCorpo()const; //essa eh necessaria porque pJogador em inimigo eh const 
            
            virtual void executar() = 0; 
        };
    }
}
