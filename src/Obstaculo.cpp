#include "Obstaculo.h"

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

           Obstaculo::Obstaculo(const sf::Vector2f tam, bool d):
            Entidade(tam), danoso(d)
            {

            }

            Obstaculo::~Obstaculo()
            {

            }
        }
    }
}