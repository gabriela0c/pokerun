#pragma once
//velocidade esta aqui pois eh comum a todos os personagens
#include "Entidade.h"

#include <iostream>

#define GRAVIDADE 600.0f
#define VEL_TERM 240.0f

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class Personagem : public Entidade{
            protected:
                sf::Vector2f vel;
                bool noChao;
                bool noTeto;
                const float gravidade;
                sf::Clock relogio;
                float dt;
                int num_vidas;

            public:
                Personagem(const sf::Vector2f tam = {}, const sf::Vector2f v = {}, int n_vds = -1);
                virtual ~Personagem();

                void aplicarGravidade();
                void pousar();
                void setNoTeto(const bool nT);
                void setNoChao(const bool nC);

                sf::Vector2f getVel()const;
                void setVel(sf::Vector2f v);

                void operator--();
                int getNumvidas()const;
                
                virtual void mover() = 0;
                virtual void executar() = 0;
            };
        }
    }
}