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
                const float gravidade;
                sf::Clock relogio;
                float dt;

            public:
                Personagem(const sf::Vector2f tam = {}, const sf::Vector2f v = {}, const ID i = ID::INDEFINIDO);
                virtual ~Personagem();

                void aplicarGravidade();
                void pousar();

                sf::Vector2f getVel()const;
                void setVel(sf::Vector2f v);

                static void colisaoPersonagem(Personagem* p1, Personagem* p2);
                

                virtual void mover() = 0;
                virtual void executar() = 0;
            };
        }
    }
}