#include "Jogador.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Jogador::Jogador(const bool ehJog1):
            Personagem((ehJog1 ? sf::Vector2f(LARGURA_PIKACHU, ALTURA_PIKACHU) : sf::Vector2f(LARGURA_RAICHU, ALTURA_RAICHU)), {VEL_JOG_X, 0.0f}, ID::JOGADOR),
            ehJogador1(ehJog1) 
            {
                num_vidas = 1000;
                if(ehJog1){
                    setTextura("assets/sprites/pikachu.png", sf::IntRect({0, 0},{LARGURA_PIKACHU, ALTURA_PIKACHU}));
                }
                else{
                    setTextura("assets/sprites/raichu.png", sf::IntRect({0, 0},{LARGURA_RAICHU, ALTURA_RAICHU}));
                } 
            }

            Jogador::~Jogador()
            {

            }

            void Jogador::carregarTextura(const std::string& caminhoArquivo)
            {
                sf::Vector2f tam = getFig().getSize();//fazer um metodo getTam acho
                
                if(!textura.loadFromFile(caminhoArquivo)) {
                    std::cout << "ERRO: Nao foi possivel carregar a textura: " << caminhoArquivo << std::endl;
                }
                pFigura->setTexture(&textura);
                
                pFigura->setTextureRect(sf::IntRect({0, 0}, {(int)tam.x, (int)tam.y}));
            }

            void Jogador::mover()
            {
                if(!noChao)
                    aplicarGravidade();
                else 
                    relogio.restart();//relogio sempre fresco quando no chao, garante que o pulo nao pareca teleporte
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

            void Jogador::setTextura(std::string caminho, sf::IntRect bounds)
            {
               if(!textura.loadFromFile(caminho)){ //sprites retiradas do site oficial da franquia Pokemon
                  std::cout << "Nao foi possivel carregar a textura do jogador" << std::endl;
               }
                
                pFigura->setTexture(&textura);
                pFigura->setFillColor(sf::Color::White); 
                pFigura->setTextureRect(bounds);
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


