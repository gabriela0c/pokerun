#include "Plataforma.h"

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            Plataforma::Plataforma():
            Obstaculo({TAM_PLAT_X, TAM_PLAT_Y}, false)
            {
                corpo.setFillColor(sf::Color::Green);
            }

            Plataforma::Plataforma(sf::Vector2f pos,sf::Vector2f dim):
            Obstaculo(dim, false)
            {
                corpo.setFillColor(sf::Color::Green);
                corpo.setPosition(pos);
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