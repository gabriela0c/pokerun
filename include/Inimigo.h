#pragma once

#include <time.h>
#include <stdlib.h>
#include <cmath>

#include "Jogador.h"

#define VEL_INIM_X 150.0f

#define TAM_INIM_X 40.0f
#define TAM_INIM_Y 40.0f

#define RAIO_X 200.0f
#define RAIO_Y 200.0f

namespace Pokerun{

    namespace Entidades{
   
        namespace Personagens{

            class Inimigo : public Personagem{
            protected:
                const Jogador* pJogador;
                int direcao;
                float tempoMovimento;

            public:
                Inimigo();
                ~Inimigo();

                void setJogador(const Jogador* jog);
                const Jogador* getJogador()const; 

                void executar();
                void mover();
                void movimentoAleatorio();
                void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);
                void setDirecao(int dir);
                void inverterDirecao();
            };
        }
    }
}