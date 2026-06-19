#pragma once

#include <time.h>
#include <stdlib.h>
#include <cmath>

#include "Entidades/Personagens/Jogador.h"
#include <SFML/Graphics.hpp>

#define VEL_INIM_X 40.0f

#define TAM_INIM_X 60.0f
#define TAM_INIM_Y 60.0f

#define RAIO_X 100.0f
#define RAIO_Y 100.0f


namespace Pokerun{

    namespace Entidades{
   
        namespace Personagens{

            class Inimigo : public Personagem{
            protected:
                Jogador* pJogador1;
                Jogador* pJogador2;
                int nivel_maldade;
                int direcao;
                float tempoMovimento;
                int valorPontos;
                float tempo_dano;
                int vidas_max;

            public:
                Inimigo(int nivMal = -1,const sf::Vector2f tam = {}, int n_vds = -1, int v_pts = -1);
                virtual ~Inimigo();

                void setJogador(Jogador* pJog);

                void executar();
                void mover();
                void movimentoAleatorio();

                void salvarDataBuffer();        
                virtual void carregarDataBuffer(std::istream& is);
                virtual void salvar() = 0;            

                int getValorPontos()const;

                virtual void desenhar();
                void desenharHuds();
                
                void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);
                void receberDano(int quantidade);

                virtual void danificar(Jogador* p) = 0;

                void aplicarKnockback(Jogador* p, float forca);
            };
        }
    }
}