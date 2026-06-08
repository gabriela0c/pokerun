#include "Jogador.h"
//#include "Projetil.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            float Jogador::temp_invenc(1.0f);
            float Jogador::temp_veneno(3.0f);


            Jogador::Jogador(const bool ehJog1):
            Personagem((ehJog1 ? sf::Vector2f(LARGURA_PIKACHU, ALTURA_PIKACHU) : sf::Vector2f(LARGURA_RAICHU, ALTURA_RAICHU)), {VEL_JOG_X, 0.0f}, N_VDS_JOG),
            ehJogador1(ehJog1), modificador_velocidade(1.0f), vel_knockback_x(0.0f), invencivel(false), ativo(true)
            {
                if(ehJog1){
                    setTextura("assets/sprites/personagens/jogador/pikachu.png", sf::IntRect({0, 0},{LARGURA_PIKACHU, ALTURA_PIKACHU}));
                }
                else{
                    setTextura("assets/sprites/personagens/jogador/raichu.png", sf::IntRect({0, 0},{LARGURA_RAICHU, ALTURA_RAICHU}));
                } 

                if(ehJog1){
                    pFigura->setPosition({150.0f, 120.0f}); //desaleatoriezar o spawn dos jogadores porque as vezes um nascia fora do mapa
                }
                else{
                    pFigura->setPosition({500.0f, 310.0f});
                }
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

            void Jogador::receberDano(int quantidade)
            {
                if (invencivel) { return; }
                for (int i = 0; i < quantidade; i++)
                    --(*this);
                ativarInvencibilidade();
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

            void Jogador::resetar()
            {
                num_vidas = N_VDS_JOG;
                invencivel = false;
                envenenado = false;
                vel_knockback_x = 0.0f;
                modificador_velocidade = 1.0f;
                setAtivo(true);

                if(ehJogador1)
                    pFigura->setPosition({150.0f, 120.0f});
                else
                    pFigura->setPosition({500.0f, 310.0f});
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

            bool Jogador::getAtivo() const
            {
                return ativo;
            }  

            void Jogador::setAtivo(const bool a)
            {
                ativo = a;
            }

            void Jogador::executar()
            {
                modificador_velocidade = 1.0f;

                if (envenenado)
                {
                    if (relogio_veneno.getElapsedTime().asSeconds() >= temp_veneno)
                    {
                        envenenado = false;
                        std::cout << (ehJogador1 ? "Jogador 1 (Pikachu)" : "Jogador 2 (Raichu)") << " se curou do veneno!" << std::endl;
                    }
                    else
                        diminui_vel(0.4f);
                }

                mover();
                noTeto = false;
                noChao = false;

                if (invencivel && relogio_invencibilidade.getElapsedTime().asSeconds() >= temp_invenc)
                {
                    invencivel = false;
                }

                if (num_vidas <= 0)
                {
                    setAtivo(false);
                    std::cout << (ehJogador1 ? "Jogador 1 (Pikachu) morto!" : "Jogador 2 (Raichu) morto!") << std::endl;
                }
            }
        }
    }
}


