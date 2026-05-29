#pragma once

#include "Personagem.h"
#include <SFML/Graphics.hpp>

#define VEL_JOG_X 0.10f

#define TAM_JOG_X 60.0f
#define TAM_JOG_Y 60.0f

#define POS0_JOG_X 50.0f
#define POS0_JOG_Y 300.0f

namespace Pokerun{   

    namespace Entidades{

        namespace Personagens{

            class Jogador : public Personagem{
            public:
                Jogador();    
                ~Jogador();

                void mover();
                void pular();

                bool colisao_posso_pular(Entidade* pOutra);
                void setTextura(std::string caminho, sf::IntRect bounds);
                //essa funcao so eh util para o jogador msm os objetos das outras classes vao todos ter a mesma textura
                void executar();
            };
        }
    }
}