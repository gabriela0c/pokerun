#include "Plataforma.h"

Pokerun::Entidades::Obstaculos::Plataforma::Plataforma():
Obstaculo({TAM_PLAT_X, TAM_PLAT_Y}, false)
{
    corpo.setFillColor(sf::Color::Green);
}

Pokerun::Entidades::Obstaculos::Plataforma::~Plataforma()
{

}

void Pokerun::Entidades::Obstaculos::Plataforma::executar()
{

}

void Pokerun::Entidades::Obstaculos::Plataforma::obstaculizar(Personagens::Jogador* pJog)
{

}