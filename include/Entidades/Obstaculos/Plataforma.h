#pragma once

#include "Entidades/Obstaculos/Obstaculo.h"

#define TAM_PLAT_X 250.0f
#define TAM_PLAT_Y 30.0f

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            class Plataforma : public Obstaculo{
            private:
                sf::Vector2i dimensoes;
                bool pode_curar;
                bool cura_consumida;

            public:
                Plataforma();
                Plataforma(sf::Vector2f pos, sf::Vector2f dim); //para construir as paredes laterais
                ~Plataforma();
            
                void executar();
                void obstaculizar(Personagens::Jogador* pJog);

                void salvarDataBuffer(); 
                void carregarDataBuffer(std::istream& is);
                void salvar();           
            };
        }
    }
}
