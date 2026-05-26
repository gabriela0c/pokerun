#pragma once

#include "Personagem.h"
#include <SFML/Graphics.hpp>

#define VEL_JOG_X 0.10f

#define TAM_JOG_X 40.0f
#define TAM_JOG_Y 40.0f

#define POS0_JOG_X 50.0f
#define POS0_JOG_Y 300.0f

namespace Pokerun{   

    namespace Entidades{

        namespace Personagens{

            class Jogador : public Personagem{
            private:
                sf::Texture texturaJogador;

            public:
                Jogador();    
                ~Jogador();

                void mover();
                void pular();

                bool colisao_posso_pular(Entidade* pOutra);

                void executar();
            };
        }
    }
}