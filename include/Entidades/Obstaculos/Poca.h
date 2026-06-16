#pragma once

#include "Entidades/Obstaculos/Obstaculo.h"

#define TAM_OBST_MEDIO_X 120.0f
#define TAM_OBST_MEDIO_Y 30.0f

#define LARGURA_OBST_MEDIO 841
#define ALTURA_OBST_MEDIO 340

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{
            
            class Poca : public Obstaculo{ //Obst Medio
                private:
                    float profundidade;
                
                public:
                    Poca();
                    ~Poca();

                    void salvarDataBuffer();
                    void salvar();
                
                    void executar();
                    void obstaculizar(Personagens::Jogador* pJog);
            };
        }
    }
}