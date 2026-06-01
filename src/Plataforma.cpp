#include "Plataforma.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{            

            Plataforma::Plataforma():
            Obstaculo({TAM_PLAT_X, TAM_PLAT_Y}, false, ID::PLATAFORMA)
            {
                setTextura("assets/sprites/obstaculos/plataforma.png", sf::IntRect({0, 0}, {(int)TAM_PLAT_X, (int)TAM_PLAT_Y}));
            }

            Plataforma::Plataforma(sf::Vector2f pos,sf::Vector2f dim):
            Obstaculo(dim, false)
            {
                pFigura->setFillColor(sf::Color::Blue);
                pFigura->setPosition(pos);
            }

            Plataforma::~Plataforma()
            {

            }

            void Plataforma::executar()
            {
                
            }

            void Plataforma::obstaculizar(Personagens::Jogador* pJog)
            {
                if(pJog)
                    pJog->colisao_posso_pular(this);
                
            }
        }
    }
}