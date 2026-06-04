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
                    setTextura("assets/sprites/personagens/jogador/pikachu.png", sf::IntRect({0, 0},{LARGURA_PIKACHU, ALTURA_PIKACHU}));
                }
                else{
                    setTextura(""assets/sprites/personagens/jogador/raichu.png"", sf::IntRect({0, 0},{LARGURA_RAICHU, ALTURA_RAICHU}));
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

            void Jogador::pular()
            {
                if(noChao){
                    vel_y = -400.0f;
                    noChao = false;
                } 
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

            void Jogador::envenenar()
            {
                envenenado = true;
                relogio_veneno.restart();
                std::cout << (ehJogador1 ? "Jogador 1 (Pikachu)" : "Jogador 2 (Raichu)") << " foi envenenado!" << std::endl;
            }

            bool Jogador::getEhJogador1() const
            {
                return ehJogador1;
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

            void Jogador::executar()
            {
                if (!getAtivo()) { return; }
 
                mover();
 
                //veneno: reduz velocidade
                if (envenenado)
                {
                    if (relogio_veneno.getElapsedTime().asSeconds() >= t_veneno)
                    {
                        envenenado = false;
                        std::cout << (ehJogador1 ? "Jogador 1 (Pikachu)" : "Jogador 2 (Raichu)") << " se curou do veneno!" << std::endl;
                    }
                    else
                        diminui_vel(0.4f); //40% da velocidade normal enquanto envenenado
                }
 
                modificador_velocidade = 1.0f; //modificador reseta a cada frame p/garantir que vel volte ao normal quando para de colidir com poca
                noChao = false;
                noTeto = false;
 
                //expira invencibilidade apos 1 segundo
                if (invencivel && relogio_invencibilidade.getElapsedTime().asSeconds() >= t_invenc)
                {
                    invencivel = false;
                }
 
                //verifica morte
                if (num_vidas <= 0)
                {
                    setAtivo(false);
                    std::cout << (ehJogador1 ? "Jogador 1 (Pikachu) morto!" : "Jogador 2 (Raichu) morto!") << std::endl;
                }
            }
        }
    }
}


