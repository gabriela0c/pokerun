#include "Obstaculo.h"

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

           Obstaculo::Obstaculo(const sf::Vector2f tam, bool d, bool s):
            Entidade(tam), danoso(d), solido(s)
            {

            }

            Obstaculo::~Obstaculo()
            {

            }

            const bool Obstaculo::isSolido()const
            {
                return solido;
            }
        }
    }
}