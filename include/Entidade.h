#pragma once

#include "Ente.h"
#include <SFML/Graphics.hpp>

namespace Pokerun{

    namespace Entidades{

        class Entidade : public Ente {
        protected:
            float x;
            float y;
        
        public:
            Entidade(const sf::Vector2f tam = {0.0f, 0.0f});
            virtual ~Entidade();
            
            virtual void executar() = 0; 
        };
    }
}
