#include "Personagem.h"

Pokerun::Entidades::Personagens::Personagem::Personagem(const sf::Vector2f tam, const sf::Vector2f v):
Entidade(tam), vel(v), relogio(), dt(0.0f)
{
    
}

Pokerun::Entidades::Personagens::Personagem::~Personagem()
{

}

