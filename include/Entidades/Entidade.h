#pragma once

#include "Ente.h"
#include <sstream>
#include <fstream>
#include <cmath>

#define GRAVIDADE 600.0f
#define VEL_TERM 240.0f

namespace Pokerun{

    namespace Entidades{

        class Entidade : public Ente {
        protected:
            float x;
            float y;
            float y_inicial;
            float vel_y;
            const float gravidade;
            sf::Clock relogio;
            float dt;
            float tempo_total;
            bool ativo;
            std::ostringstream buffer; 

        protected:
            virtual void salvarDataBuffer();
        
        public:
            Entidade(const sf::Vector2f tam = {0.0f, 0.0f}, const float vY = 0.0f);
            virtual ~Entidade();

            void aplicarGravidade();
            void antiGravidade();
            void sincronizarPosicao();  
            void setPosicao(const sf::Vector2f pos);

            bool getAtivo()const;
            void setAtivo(const bool a);

            sf::Vector2f calcularDirecao(sf::Vector2f posAlvo, sf::Vector2f posFonte);
            sf::Vector2f getPosition()const;
            sf::Vector2f getSize()const;
            
            virtual void executar() = 0; 
            virtual void salvar() = 0;
        };
    }
}
