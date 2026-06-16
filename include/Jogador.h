#pragma once

#include "Personagem.h"
#include "Temporizador.h"

#define VEL_JOG_X 0.10f

#define LARGURA_PIKACHU 40
#define ALTURA_PIKACHU 38

#define LARGURA_RAICHU 48
#define ALTURA_RAICHU 46

#define N_VDS_JOG 10

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class Jogador : public Personagem{
            protected:
                const bool ehJogador1;
                float modificador_velocidade;
                float vel_knockback_x;
                Temporizador invencibilidade;
                Temporizador veneno;
                Temporizador cd_ataque;
                bool atacando;
                int pontos;
                    
            public:
                Jogador(const bool ehJog1 = false);    
                ~Jogador();

                void mover();
                void pular();

                void salvarDataBuffer(); 
                void salvar();            

                void operator+=(int num);

                void diminui_vel(float taxa);
                float getModVel()const;
                void receberKnockback(float impulso);
                void receberDano(int quantidade);
                void envenenar();

                bool getEhJogador1() const;
                void resetar();

                void setAtacando(const bool a);
                const bool getAtacando()const;
                const bool podeAtacar();
                void iniciarCooldown();

                bool getInvencivel()const;
                void ativarInvencibilidade();
                void imprimirStatus() const;
                void executar();
            };
        }
    }
}
