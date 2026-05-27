#include "Jogador.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            sf::Texture Jogador::texturaJogador;

            Jogador::Jogador():
            Personagem({TAM_JOG_X, TAM_JOG_Y}, {VEL_JOG_X, 0.0f}, ID::JOGADOR)
            {
                pFigura->setPosition({POS0_JOG_X, POS0_JOG_Y});
                if(!texturaJogador.loadFromFile("assets/sprites/pikachu.png"))
                //sprite retirada do site oficial da franquia Pokemon
                    std::cout << "ERRO: Nao foi possivel carregar a textura do jogador!" << std::endl;

                pFigura->setTexture(&texturaJogador);
                pFigura->setFillColor(sf::Color::White); 
                pFigura->setTextureRect(sf::IntRect({0, 0}, {LARGURA_PIKACHU, ALTURA_PIKACHU}));
            }

            Jogador::~Jogador()
            {

            }

            void Jogador::mover()
            {
                if(!noChao){aplicarGravidade();}
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
        }
    }
}


