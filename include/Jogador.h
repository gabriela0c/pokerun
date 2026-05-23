#pragma once

#include "Personagem.h"

#define VEL_JOG_X 0.15f

#define TAM_JOG_X 50.0f
#define TAM_JOG_Y 50.0f

#define POS0_JOG_X 50.0f
#define POS0_JOG_Y 300.0f

namespace Pokerun{   

    namespace Entidades{

        namespace Personagens{

            class Jogador : public Personagem{
            protected:
            

            public:
                Jogador();
                ~Jogador();

                void mover();
                void pular();

                void setVel(sf::Vector2f v);
                bool colisao_posso_pular(Entidade* pOutra);

                void executar();
            };
        }
    }
}