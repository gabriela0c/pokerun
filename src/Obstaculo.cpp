#include "Obstaculo.h"

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

           Obstaculo::Obstaculo(const sf::Vector2f tam, bool d, const ID i):
            Entidade(tam, i), danoso(d)
            {

            }

            Obstaculo::~Obstaculo()
            {

            }
        }
    }
}