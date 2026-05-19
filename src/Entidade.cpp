#include "Entidade.h"

Pokerun::Entidades::Entidade::Entidade(const sf::Vector2f tam):
x((float)(rand() % (int)(801 - tam.x))), y((float)(rand() % (int)(601 - tam.y))), corpo(sf::RectangleShape(tam))
{
    corpo.setPosition({x, y});
}

Pokerun::Entidades::Entidade::~Entidade()
{

}

const sf::RectangleShape& Pokerun::Entidades::Entidade::getCorpo()const
{
    return corpo;
}

