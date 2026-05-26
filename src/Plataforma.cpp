#include "Plataforma.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            Plataforma::Plataforma():
            Obstaculo({TAM_PLAT_X, TAM_PLAT_Y}, false)
            {
                if(!texturaPlataforma.loadFromFile("assets/sprites/plataforma.png"))
                //sprite gerada por IA
                    std::cout << "ERRO: Nao foi possivel carregar a textura da plataforma!" << std::endl;

                pFig->setTexture(&texturaPlataforma);
                pFig->setFillColor(sf::Color::White); 
                pFig->setTextureRect(sf::IntRect({0, 0}, {(int)TAM_PLAT_X, (int)TAM_PLAT_Y}));
            }

            Plataforma::Plataforma(sf::Vector2f pos,sf::Vector2f dim):
            Obstaculo(dim, false)
            {
                pFig->setFillColor(sf::Color::Blue);
                pFig->setPosition(pos);
            }

            Plataforma::~Plataforma()
            {

            }

            void Plataforma::executar()
            {
                
            }

            void Plataforma::obstaculizar(Personagens::Jogador* pJog)
            {
                if(pJog){
                    pJog->colisao_posso_pular(this);
                }
                
            }
        }
    }
}