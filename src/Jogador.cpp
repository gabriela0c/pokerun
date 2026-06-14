#include "Jogador.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Jogador::Jogador(const bool ehJog1):
            Personagem((ehJog1 ? sf::Vector2f(LARGURA_PIKACHU, ALTURA_PIKACHU) : sf::Vector2f(LARGURA_RAICHU, ALTURA_RAICHU)), {VEL_JOG_X, 0.0f}, N_VDS_JOG),
            ehJogador1(ehJog1), modificador_velocidade(1.0f), vel_knockback_x(0.0f), invencibilidade(1.0f), veneno(3.0f), cd_ataque(0.7f), pontos(0)
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
                if (vel_knockback_x != 0.0f) //separar em outro metodo
                {
                    pFigura->move({vel_knockback_x * dt, 0.0f});
                    vel_knockback_x *= (1.0f - 8.0f * dt);
                    if (std::abs(vel_knockback_x) < 1.0f) vel_knockback_x = 0.0f;
                }

                if(noChao) {
                    relogio.restart();
                }//relogio sempre novo quando no chao, garante que o pulo nao pareca teleporte

                if(noTeto){vel_y = 0;} //senao o jogador grudava no teto antes de cair
            }

            void Jogador::pular()
            {
                if(noChao){
                    vel_y = -400.0f;
                    noChao = false;
                } 
            }

            void Jogador::operator+=(int num)
            {
                pontos += num;
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
                if (invencibilidade.getAtivo()) { return; }
                for (int i = 0; i < quantidade; i++)
                    operator--();
                invencibilidade.iniciar();
            }

            void Jogador::envenenar()
            {
                veneno.iniciar();
                std::cout << (ehJogador1 ? "Jogador 1 (Pikachu)" : "Jogador 2 (Raichu)") << " foi envenenado!" << std::endl;
            }

            bool Jogador::getEhJogador1() const
            {
                return ehJogador1;
            }

            bool Jogador::getInvencivel()const
            {
                return invencibilidade.getAtivo();
            }

            void Jogador::ativarInvencibilidade()
            {
                invencibilidade.iniciar();
            }

            void Jogador::setAtacando(const bool a)
            {
                atacando = a;
            }

            const bool Jogador::getAtacando()const
            {
                return atacando;
            }

            const bool Jogador::podeAtacar()
            {
                return (!cd_ataque.getAtivo());
            }

            void Jogador::iniciarCooldown()
            {
                cd_ataque.iniciar();
            }

            void Jogador::resetar()
            {
                num_vidas = N_VDS_JOG;
                invencibilidade.parar();
                veneno.parar();
                vel_knockback_x = 0.0f;
                modificador_velocidade = 1.0f;
                setAtivo(true);

                if(ehJogador1)
                    pFigura->setPosition({150.0f, 120.0f});
                else
                    pFigura->setPosition({500.0f, 310.0f});
            }

            void Jogador::imprimirStatus() const
            {
                std::cout << "Status do Jogador:" << std::endl;
                std::cout << "Vidas: " << num_vidas << std::endl;
                std::cout << "Pontos: " << pontos << std::endl;
            }

            void Jogador::executar()
            {
                modificador_velocidade = 1.0f;

                bool estavaEnvenenado = veneno.getAtivo();
                veneno.atualizar();
                
                if(!veneno.getAtivo() && estavaEnvenenado){
                    std::cout << (ehJogador1 ? "Jogador 1 (Pikachu)" : "Jogador 2 (Raichu)") << " se curou do veneno!" << std::endl;
                }
                else if(veneno.getAtivo()){
                    diminui_vel(0.4f);
                }

                invencibilidade.atualizar();
                cd_ataque.atualizar();   

                mover();
                noTeto = false;
                noChao = false;

                if (num_vidas <= 0)
                {
                    setAtivo(false);
                    std::cout << (ehJogador1 ? "Jogador 1 (Pikachu) morto!" : "Jogador 2 (Raichu) morto!") << std::endl;
                }
            }
        }
    }
}


