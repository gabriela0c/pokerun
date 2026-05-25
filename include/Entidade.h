#pragma once
//posicao e corpo sao elementos comuns a todas entidades, obstaculos tambem as terao, portanto a necessidade da classe
#include "Ente.h"
#include <SFML/Graphics.hpp>

namespace Pokerun{

    namespace Entidades{

        class Entidade : public Ente {
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

            bool colidir(Entidade* pOutra);
            
            void desenhar();
            virtual void executar() = 0; 
        };
    }
}
