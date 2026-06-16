#include "Entidades/Obstaculos/Obstaculo.h"

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

           Obstaculo::Obstaculo(const sf::Vector2f tam, const bool d, const bool s):
            Entidade(tam), danoso(d), solido(s) //nao precisa passar vel_y porque é 0 por default, logo ja esta certo
            {

            }

            Obstaculo::~Obstaculo()
            {

            }

            void Obstaculo::salvarDataBuffer()
            {
                Entidade::salvarDataBuffer();
                buffer << " " << danoso << " " << solido;
            }

            const bool Obstaculo::isSolido()const
            {
                return solido;
            }
        }
    }
}