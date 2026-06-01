#pragma once

#include <time.h>
#include <stdlib.h>
#include <cmath>

#include "Jogador.h"
#include <SFML/Graphics.hpp>

#define VEL_INIM_X 60.0f

#define TAM_INIM_X 60.0f
#define TAM_INIM_Y 60.0f

#define RAIO_X 200.0f
#define RAIO_Y 200.0f


namespace Pokerun{

    namespace Entidades{
   
        namespace Personagens{

            class Inimigo : public Personagem{
            protected:
                const Jogador* pJogador1;
                const Jogador* pJogador2;

                int direcao;
                float tempoMovimento;

            public:
                Inimigo(const sf::Vector2f tam = {}, const ID i = ID::INDEFINIDO);
                ~Inimigo();

                void setJogador1(const Jogador* jog1);
                void setJogador2(const Jogador* jog2);

                void executar();
                void mover();
                void movimentoAleatorio();
             
                void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);
                void setDirecao(int dir);
                void inverterDirecao();

                virtual void danificar(Jogador* p) = 0;
            };
        }
    }
}