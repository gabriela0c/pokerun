#pragma once

#include "Obstaculo.h"

#define TAM_OBST_MEDIO_X 40.0f
#define TAM_OBST_MEDIO_Y 40.0f

#define LARGURA_OBST_MEDIO 780
#define ALTURA_OBST_MEDIO 560

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{
            
            class ObstMedio : public Obstaculo{
                private:
                    static sf::Texture texturaObstMedio;
                public:
                    ObstMedio();
                    ~ObstMedio();
                
                    void executar();
                    void obstaculizar(Personagens::Jogador* pJog);
            };
        }
    }
}