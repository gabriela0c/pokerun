#include "Inimigo.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Inimigo::Inimigo():
            Personagem({TAM_INIM_X, TAM_INIM_Y}, {VEL_INIM_X, 0.0f}), pJogador(nullptr), direcao(-1), tempoMovimento(0.0f)
            {
                corpo.setFillColor(sf::Color::Red);
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
                sf::Vector2f posInimigo = corpo.getPosition();

                if(fabs(posInimigo.x - posJogador.x) <= RAIO_X && fabs(posInimigo.y - posJogador.y) <= RAIO_Y){
                    persegueJogador(posJogador, posInimigo);
                }
                else{
                    movimentoAleatorio();
                }
            }

            void Inimigo::movimentoAleatorio()
            {
                corpo.move({-vel.x * direcao * dt, 0.0f});
                
                tempoMovimento += dt;

                if(tempoMovimento >= 0.5f){
                    tempoMovimento = 0.0f;
                    direcao = (rand()%2 == 0) ? -1 : 1;
                }
            }

            void Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
            {
                if(posJogador.x - posInimigo.x > 0.0f){
                    corpo.move({vel.x * dt, 0.0f});
                }
                else{
                    corpo.move({-vel.x * dt, 0.0f});
                }
            }
        }
    }
}