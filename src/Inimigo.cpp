#include "Inimigo.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Inimigo::Inimigo():
            Personagem({TAM_INIM_X, TAM_INIM_Y}, {VEL_INIM_X, 0.0f}), pJogador(nullptr), direcao(-1), tempoMovimento(0.0f)
            {
                if(!texturaInimigo.loadFromFile("assets/sprites/bulbasaur.png"))
                //sprite retirada do site oficial da franquia Pokemon
                    std::cout << "ERRO: Nao foi possivel carregar a textura do inimigo!" << std::endl;
                
                pFig->setTexture(&texturaInimigo);
                pFig->setFillColor(sf::Color::White);
                pFig->setTextureRect(sf::IntRect({0, 0}, {(int)TAM_INIM_X, (int)TAM_INIM_Y}));
            }

            Inimigo::~Inimigo()
            {

            }

            void Inimigo::setJogador(const Jogador* jog)
            {
                if(jog){
                    pJogador = jog;
                }
            }

            const Jogador* Inimigo::getJogador() const
            {
                return pJogador;
            }

            void Inimigo::executar()
            {
                aplicarGravidade();
                mover();
            }

            void Inimigo::mover()
            {
                if(!pJogador) {
                    std::cerr<<"Jogador Nulo"<<std::endl;
                    return;
                }

                sf::Vector2f posJogador = pJogador->getCorpo().getPosition();
                sf::Vector2f posInimigo = pFig->getPosition();

                if(fabs(posInimigo.x - posJogador.x) <= RAIO_X && fabs(posInimigo.y - posJogador.y) <= RAIO_Y){
                    persegueJogador(posJogador, posInimigo);
                }
                else{
                    movimentoAleatorio();
                }
            }

            void Inimigo::movimentoAleatorio()
            {
                pFig->move({-vel.x * direcao * dt, 0.0f});
                
                if (direcao == -1) //move p direita
                    pFig->setTextureRect(sf::IntRect({0, 0}, {(int)TAM_INIM_X, (int)TAM_INIM_Y}));
                
                else //move p esquerda
                    pFig->setTextureRect(sf::IntRect({(int)TAM_INIM_X, 0}, {-(int)TAM_INIM_X, (int)TAM_INIM_Y}));

                tempoMovimento += dt;

                if(tempoMovimento >= 0.5f){
                    tempoMovimento = 0.0f;
                    direcao = (rand()%2 == 0) ? -1 : 1;
                }
            }

            void Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
            {
                if(posJogador.x - posInimigo.x > 0.0f){
                    //indo p direita
                    pFig->move({vel.x * dt, 0.0f});
                    pFig->setTextureRect(sf::IntRect({0, 0}, {(int)TAM_INIM_X, (int)TAM_INIM_Y}));
                }
                else{
                    //indo p esquerda
                    pFig->move({-vel.x * dt, 0.0f});
                    pFig->setTextureRect(sf::IntRect({(int)TAM_INIM_X, 0}, {-(int)TAM_INIM_X, (int)TAM_INIM_Y}));
                }
            }

            void Inimigo::setDirecao(int dir)
            {
                direcao = dir;
            }

            void Inimigo::inverterDirecao()
            {
                direcao *= -1;
            }
        }
    }
}