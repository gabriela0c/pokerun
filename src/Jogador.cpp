#include "Jogador.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Jogador::Jogador(const bool ehJog1):
            Personagem((ehJog1 ? sf::Vector2f(LARGURA_PIKACHU, ALTURA_PIKACHU) : sf::Vector2f(LARGURA_RAICHU, ALTURA_RAICHU)), {VEL_JOG_X, 0.0f}, N_VDS_JOG),
            ehJogador1(ehJog1), modificador_velocidade(1.0f), vel_knockback_x(0.0f), invencivel(false)
            {
                /*if(ehJog1){
                    setTextura("assets/sprites/pikachu.png", sf::IntRect({0, 0},{LARGURA_PIKACHU, ALTURA_PIKACHU}));
                }
                else{
                    setTextura("assets/sprites/raichu.png", sf::IntRect({0, 0},{LARGURA_RAICHU, ALTURA_RAICHU}));
                } */
            }

            Jogador::~Jogador()
            {

            }

            void Jogador::mover()
            {
                aplicarGravidade();

                // aplica knockback horizontal usando o dt que aplicarGravidade() acabou de calcular
                if (vel_knockback_x != 0.0f) 
                {
                    pFigura->move({vel_knockback_x * dt, 0.0f});
                    vel_knockback_x *= (1.0f - 8.0f * dt);
                    if (std::abs(vel_knockback_x) < 1.0f) vel_knockback_x = 0.0f;
                }

                if(noChao) {
                    relogio.restart();
                }//relogio sempre fresco quando no chao, garante que o pulo nao pareca teleporte

                if(noTeto){vel_y = 0;} //senao o jogador grudava no teto antes de cair
            }

            void Jogador::diminui_vel(float taxa)
            {
                if(taxa < modificador_velocidade){
                    modificador_velocidade = taxa;
                }
            }

            float Jogador::getModVel()const{
                return modificador_velocidade;
            }

            void Jogador::receberKnockback(float impulso)
            {
                vel_knockback_x = impulso;
            }

            bool Jogador::getInvencivel() const
            {
                return invencivel;
            }

            void Jogador::ativarInvencibilidade()
            {
                invencivel = true;
                relogio_invencibilidade.restart();
            }

            void Jogador::pular()
            {
                if(noChao){
                    vel_y = -400.0f;
                    noChao = false;
                } 
            }

            void Jogador::executar()
            {
                mover();
                modificador_velocidade = 1.0f; //modificador reseta a cada frame p/garantir que vel volte ao normal quando para de colidir com poca
                noChao = false;
                noTeto = false;

                if (invencivel && relogio_invencibilidade.getElapsedTime().asSeconds() >= t_invenc)
                    invencivel = false;
            }
        }
    }
}


