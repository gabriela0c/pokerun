#pragma once

#include "Obstaculo.h"

#define TAM_OBST_FACIL_X 40.0f
#define TAM_OBST_FACIL_Y 40.0f

#define LARGURA_OBST_FACIL 780
#define ALTURA_OBST_FACIL 560

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{
            
            class ObstMedio : public Obstaculo{
                public:
                    ObstMedio();
                    ~ObstMedio();
                
                    void executar();
                    void obstaculizar(Personagens::Jogador* pJog);
            };
        }
    }
}