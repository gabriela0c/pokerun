#include "Entidade.h"

namespace Pokerun{

    namespace Entidades{
        
        Entidade::Entidade(const sf::Vector2f tam): 
        Ente(tam),
        x((float)(rand() % (int)(801 - tam.x))), y((float)(rand() % (int)(601 - tam.y)))
        {
            pFigura->setPosition({x, y});
        }

        Entidade::~Entidade()
        {

        }
    }
}