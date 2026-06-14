#pragma once

#include "Ente.h"
#include <SFML/Graphics.hpp>

#define GRAVIDADE 600.0f
#define VEL_TERM 240.0f

namespace Pokerun{

    namespace Entidades{

        class Entidade : public Ente {
        protected:
            float x;
            float y;
            float vel_y;
            const float gravidade;
            sf::Clock relogio;
            float dt;
            bool ativo;
        
        public:
            Entidade(const sf::Vector2f tam = {0.0f, 0.0f}, const float vY = 0.0f);
            virtual ~Entidade();

            void aplicarGravidade();   
            void antiGravidade();

            bool getAtivo()const;
            void setAtivo(const bool a);

            float calcularDirecao(sf::Vector2f posAlvo, sf::Vector2f posFonte);
            
            virtual void executar() = 0; 
        };
    }
}
