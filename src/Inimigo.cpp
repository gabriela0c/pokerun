#include "Inimigo.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{
            
            Inimigo::Inimigo(const sf::Vector2f tam ,const ID i):
            Personagem(tam, {VEL_INIM_X, 0.0f}, i), pJogador(nullptr), 
            direcao(-1), tempoMovimento(0.0f)
            {

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
                if(!noChao){aplicarGravidade();}
                mover();
                noChao = false;
            }

            void Inimigo::mover()
            {
                if(!pJogador) {
                    std::cerr<<"Jogador Nulo"<<std::endl;
                    return;
                }

                sf::Vector2f posJogador = pJogador->getFig().getPosition();//pode ser metodo do Personagem/entidade
                sf::Vector2f posInimigo = pFigura->getPosition();

                if(fabs(posInimigo.x - posJogador.x) <= RAIO_X && fabs(posInimigo.y - posJogador.y) <= RAIO_Y){
                    persegueJogador(posJogador, posInimigo);
                }
                else{
                    movimentoAleatorio();
                }
            }

            void Inimigo::movimentoAleatorio()
            {
                sf::Vector2f tam = getFig().getSize(); //talvez criar atributo tam

                pFigura->move({-vel.x * direcao * dt, 0.0f});
                
                if (direcao == -1) //move p direita
                    pFigura->setTextureRect(sf::IntRect({0, 0}, {(int)tam.x, (int)tam.y}));
                
                else //move p esquerda
                    pFigura->setTextureRect(sf::IntRect({(int)tam.x, 0}, {(int)-tam.x, (int)tam.y}));

                tempoMovimento += dt;

                if(tempoMovimento >= 0.5f){
                    tempoMovimento = 0.0f;
                    direcao = (rand()%2 == 0) ? -1 : 1;
                }
            }

            void Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
            {
                float distanciaX = posJogador.x - posInimigo.x;
                float tolerancia = 2.0f; //para evitar o inimigo ficar oscilando qdo o jogador esta em cima dele
                
                if(std::abs(distanciaX) > tolerancia){
                    sf::Vector2f tam = getFig().getSize();
                
                    if(distanciaX > 0.0f){
                        //indo p direita
                        pFigura->move({vel.x * dt, 0.0f});
                        pFigura->setTextureRect(sf::IntRect({0, 0}, {(int)tam.x, (int)tam.y}));
                    }
                    else{
                        //indo p esquerda
                        pFigura->move({-vel.x * dt, 0.0f});
                        pFigura->setTextureRect(sf::IntRect({(int)tam.x, 0}, {(int)-tam.x, (int)tam.y}));
                    }
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