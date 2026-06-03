#pragma once

#include "Personagem.h"
#include <SFML/Graphics.hpp>

#define VEL_JOG_X 0.10f

#define POS0_JOG_X 50.0f
#define POS0_JOG_Y 300.0f

#define LARGURA_PIKACHU 40
#define ALTURA_PIKACHU 38

#define LARGURA_RAICHU 48
#define ALTURA_RAICHU 46

#define N_VDS_JOG 1000

namespace Pokerun{   

    namespace Entidades{

        namespace Personagens{

            class Jogador : public Personagem{
            private:
                const bool ehJogador1;
                float modificador_velocidade;
            
            public:
                Jogador(const bool ehJog1 = false);    
                ~Jogador();

                void mover();
                void pular();

                void diminui_vel(float taxa);
                float getModVel()const;

                bool colisao_posso_pular(Entidade* pOutra);

                void executar();
            };
        }
    }
}