#include "Inimigo.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            sf::Texture Inimigo::texturaInimigo;
            
            Inimigo::Inimigo():
            Personagem({TAM_INIM_X, TAM_INIM_Y}, {VEL_INIM_X, 0.0f}, ID::INIMIGO), pJogador(nullptr), 
            direcao(-1), tempoMovimento(0.0f)
            {
                if(!texturaInimigo.loadFromFile("assets/sprites/bulbasaur.png"))
                //sprite retirada do site oficial da franquia Pokemon
                    std::cout << "ERRO: Nao foi possivel carregar a textura do inimigo!" << std::endl;
                
                pFigura->setTexture(&texturaInimigo);
                pFigura->setFillColor(sf::Color::White);
                pFigura->setTextureRect(sf::IntRect({0, 0}, {LARGURA_BULBASAUR, ALTURA_BULBASAUR}));
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
                pFigura->move({-vel.x * direcao * dt, 0.0f});
                
                if (direcao == -1) //move p direita
                    pFigura->setTextureRect(sf::IntRect({0, 0}, {LARGURA_BULBASAUR, ALTURA_BULBASAUR}));
                
                else //move p esquerda
                    pFigura->setTextureRect(sf::IntRect({LARGURA_BULBASAUR, 0}, {-LARGURA_BULBASAUR, ALTURA_BULBASAUR}));

                tempoMovimento += dt;

                if(tempoMovimento >= 0.5f){
                    tempoMovimento = 0.0f;
                    direcao = (rand()%2 == 0) ? -1 : 1;
                }
            }

            void Inimigo::pousar()
            {
                noChao = true;
                vel.y = 0.0f;
            }

            void Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
            {
                if(posJogador.x - posInimigo.x > 0.0f){
                    //indo p direita
                    pFigura->move({vel.x * dt, 0.0f});
                    pFigura->setTextureRect(sf::IntRect({0, 0}, {LARGURA_BULBASAUR, ALTURA_BULBASAUR}));
                }
                else{
                    //indo p esquerda
                    pFigura->move({-vel.x * dt, 0.0f});
                    pFigura->setTextureRect(sf::IntRect({LARGURA_BULBASAUR, 0}, {-LARGURA_BULBASAUR, ALTURA_BULBASAUR}));
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