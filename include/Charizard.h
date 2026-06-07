#pragma once 

#include "Inimigo.h"

#define LARGURA_CHARIZARD 87.0f
#define ALTURA_CHARIZARD 77.0f

#define NIVEL_MALD_CHEFAO 3
#define N_VDS_CHEFAO 5

#define LARGURA_PROJ 104
#define ALTURA_PROJ 169
#define COOLDOWN_TIRO_INIM 0.5f

namespace Pokerun{
    
    namespace Fases{
                class Fase;
            };

    namespace Entidades{

        namespace Personagens{

            class Charizard : public Inimigo{ //Chefao
            private:
                int raio_ataque;
                Fases::Fase* pFase;
                float tempoCooldownTiro;

            public:
                Charizard();
                ~Charizard();

                void danificar(Jogador* p);

                void setPFase(Pokerun::Fases::Fase* f);
                void dispararProjetil(float direcao);

                void executar();
            };
        }
    }
}