#include "Jogador.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Jogador::Jogador():
            Personagem({TAM_JOG_X, TAM_JOG_Y}, {VEL_JOG_X, 0.0f}, ID::JOGADOR)
            {
                pFigura->setFillColor(sf::Color::White); 
            }

            Jogador::~Jogador()
            {

            }

            void Jogador::carregarTextura(const std::string& caminhoArquivo)
            {
                if(!textura.loadFromFile(caminhoArquivo)) {
                    std::cout << "ERRO: Nao foi possivel carregar a textura: " << caminhoArquivo << std::endl;
                }
                pFigura->setTexture(&textura);
                
                sf::Vector2u tamanhoImagem = textura.getSize();
                pFigura->setTextureRect(sf::IntRect({0, 0}, {(int)tamanhoImagem.x, (int)tamanhoImagem.y}));
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


