#pragma once

#include "Personagem.h"

#define VEL_JOG_X 0.10f

#define LARGURA_PIKACHU 40
#define ALTURA_PIKACHU 38

#define LARGURA_RAICHU 48
#define ALTURA_RAICHU 46

#define N_VDS_JOG 10

#define DANO_PROJETIL_JOG 1
#define COOLDOWN_TIRO_JOG 0.5f

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class Jogador : public Personagem{
            protected:
                const bool ehJogador1;
                float modificador_velocidade;
                float vel_knockback_x;
                bool invencivel;
                sf::Clock relogio_invencibilidade;
                static float temp_invenc;
                bool envenenado;
                sf::Clock relogio_veneno;
                static float temp_veneno;
                int pontos;
                    
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

                void executar();
            };
        }
    }
}
