#pragma once

#include "Obstaculo.h"

#define TAM_CHAO_X 800.0f
#define TAM_CHAO_Y 30.0f

#define LARGURA_CHAO 4145.0f
#define ALTURA_CHAO 137.0f

namespace Pokerun {

    namespace Entidades {

        namespace Obstaculos {
            
            class Chao : public Obstaculo {
            private:
                sf::Texture texturaChao;
            public:
                Chao(const sf::Vector2f pos = {0.0f, 0.0f}, const sf::Vector2f tam = {0.0f, 0.0f});
                ~Chao();
                
                void executar();
                void obstaculizar(Personagens::Jogador* pJog);
            };

        }
    }
}