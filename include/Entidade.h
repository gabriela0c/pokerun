#pragma once

#include "Ente.h"
#include <SFML/Graphics.hpp>

namespace Pokerun{

    namespace Entidades{

        class Entidade : public Ente {
        protected:
            float x;
            float y;
            bool noTeto;
        
        public:
            Entidade(const sf::Vector2f tam = {0.0f, 0.0f}, const ID i = ID::INDEFINIDO);
            virtual ~Entidade();
            
            bool colidir(Entidade* pOutra);
            
            virtual void executar() = 0; 
        };
    }
}
