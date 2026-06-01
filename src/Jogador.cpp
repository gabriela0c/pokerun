#include "Jogador.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Jogador::Jogador(const bool ehJog1):
            Personagem((ehJog1 ? sf::Vector2f(LARGURA_PIKACHU, ALTURA_PIKACHU) : sf::Vector2f(LARGURA_RAICHU, ALTURA_RAICHU)), {VEL_JOG_X, 0.0f}, ID::JOGADOR),
            ehJogador1(ehJog1), modificador_velocidade(1.0f)
            {
                num_vidas = 10000;
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
                if(!noChao)
                    aplicarGravidade();
                else 
                    relogio.restart();//relogio sempre fresco quando no chao, garante que o pulo nao pareca teleporte

                if(noTeto){vel.y = 0;} //senao o inimigo grudava no teto antes de cair
            }

            bool Jogador::colisao_posso_pular(Entidade* pOutra)
            { 
                bool deCima = Entidade::colidir(pOutra);
                if(deCima){
                    noChao = true;
                    vel.y = 0.0f; 
                    return true;
                }
                return false;
            }

            void Jogador::diminui_vel(float porcentagem)
            {
                if(porcentagem < modificador_velocidade){
                    modificador_velocidade = porcentagem;
                }
            }

            float Jogador::getModVel()const{
                return modificador_velocidade;
            }

            void Jogador::pular()
            {
                if(noChao){
                    vel.y = -400.0f;
                    noChao = false;
                } 
            }

            void Jogador::executar()
            {
                mover();
                modificador_velocidade = 1.0f; //modificador reseta a cada frame p/garantir que vel volte ao normal quando para de colidir com poca
                noChao = false;
                noTeto = false;
            }
        }
    }
}


