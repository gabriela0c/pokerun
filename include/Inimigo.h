#pragma once

//REMOVER O COMENTARIO DPS{esse metodo executar poderia ser o mover. Fariamos o Metodo mover de personagem virtual,
//passar aquele algoritimo de movimento do personagem que so eh utilizado pelo jogador para a classe jogador}

#include <time.h>
#include <stdlib.h>
#include <cmath>

#include "Jogador.h"

#define VEL_INIM_X 150.0f
#define VEL_INIM_Y 150.0f

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
                short int moveAleatorio;
                float tempoMovimento;
                //outro clock aqui era redundante ja que personagem ja tem um relogio

            public:
                Inimigo();
                ~Inimigo();

                void setJogador(const Jogador* jog);
                const Jogador* getJogador()const; 

                void executar();
                void movimentoAleatorio();
                void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);
            };
        }
    }
}