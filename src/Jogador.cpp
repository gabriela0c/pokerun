#include "Jogador.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Jogador::Jogador():
            Personagem({TAM_JOG_X, TAM_JOG_Y}, {VEL_JOG_X, 0.0f})
            {
            corpo.setPosition({POS0_JOG_X, POS0_JOG_Y});
            corpo.setFillColor(sf::Color::Yellow);
            }

            Jogador::~Jogador()
            {

            }

            void Jogador::mover()
            {
                aplicarGravidade();
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
                noChao = false;
            }

            void Jogador::setVel(sf::Vector2f v)
            {
                vel = v;
            }
        }
    }
}


