#pragma once

#include "Obstaculo.h"

#define TAM_OBST_MEDIO_X 80.0f
#define TAM_OBST_MEDIO_Y 40.0f

#define LARGURA_OBST_MEDIO 841
#define ALTURA_OBST_MEDIO 340

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{
            
            class ObstMedio : public Obstaculo{
                private:
                float profundidade;
                
                public:
                    ObstMedio();
                    ~ObstMedio();
                
                    void executar();
                    void obstaculizar(Personagens::Jogador* pJog);
            };
        }
    }
}