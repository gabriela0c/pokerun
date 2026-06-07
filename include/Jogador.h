#pragma once

#include "Personagem.h"
#include <SFML/Graphics.hpp>

#define VEL_JOG_X 0.10f

#define POS0_JOG_X 50.0f
#define POS0_JOG_Y 300.0f

#define LARGURA_PIKACHU 40
#define ALTURA_PIKACHU 38

#define LARGURA_RAICHU 48
#define ALTURA_RAICHU 46

#define N_VDS_JOG 10

#define DANO_PROJETIL_JOG 1
#define COOLDOWN_TIRO_JOG 0.5f

#define LARGURA_RAIO 148
#define ALTURA_RAIO 169
#define TAMANHO_RAIO_X 15.0f
#define TAMANHO_RAIO_Y 15.0f

namespace Pokerun{
    
    namespace Fases{
                class Fase;
            };

    namespace Entidades{

        namespace Personagens{

            class Jogador : public Personagem{
            private:
                const bool ehJogador1;
                float modificador_velocidade;
                float vel_knockback_x;
                bool invencivel;
                sf::Clock relogio_invencibilidade;
                static float temp_invenc;
                bool envenenado;
                sf::Clock relogio_veneno;
                static float temp_veneno;
                Fases::Fase* pFase;
                //float tempoCooldownTiro;
                    
            public:
                Jogador(const bool ehJog1 = false);    
                ~Jogador();

                void mover();
                void pular();

                void diminui_vel(float taxa);
                float getModVel()const;
                void receberKnockback(float impulso);
                void receberDano(int quantidade);
                void envenenar();

                bool getEhJogador1() const;
                void resetar();

                bool getInvencivel()const;
                void ativarInvencibilidade();

                void setPFase(Fases::Fase* f);
                //void dispararProjetil(float direcao);

                void executar();
            };
        }
    }
}