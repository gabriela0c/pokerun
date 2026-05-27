#pragma once

#include "Obstaculo.h"

#define TAM_PLAT_X 300.0f
#define TAM_PLAT_Y 70.0f

#define LARGURA_PLATAFORMA 427
#define ALTURA_PLATAFORMA 106

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            class Plataforma : public Obstaculo{
            private:
                static sf::Texture texturaPlataforma;
            public:
                Plataforma();
                Plataforma(sf::Vector2f pos, sf::Vector2f dim); //para construir o chao
                ~Plataforma();
            
                void executar();
                void obstaculizar(Personagens::Jogador* pJog);
            };
        }
    }
}
