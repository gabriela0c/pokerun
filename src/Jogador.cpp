#include "Jogador.h"

Pokerun::Entidades::Personagens::Jogador::Jogador():
Personagem({TAM_JOG_X, TAM_JOG_Y}, {VEL_JOG_X, VEL_JOG_Y})
{
   corpo.setPosition({POS0_JOG_X, POS0_JOG_Y});
   corpo.setFillColor(sf::Color::Yellow);
}

Pokerun::Entidades::Personagens::Jogador::~Jogador()
{

}

void Pokerun::Entidades::Personagens::Jogador::executar()
{
    atualizarPosicao();
    relogio.restart();
}
