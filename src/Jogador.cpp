#include "Jogador.h"

Pokerun::Entidades::Personagens::Jogador::Jogador():
Personagem({TAM_JOG_X, TAM_JOG_Y}, {VEL_JOG_X, VEL_JOG_Y}), direcao({0.0f, 0.0f})
{
   corpo.setPosition({POS0_JOG_X, POS0_JOG_Y});
   corpo.setFillColor(sf::Color::Yellow);
}

Pokerun::Entidades::Personagens::Jogador::~Jogador()
{

}

void Pokerun::Entidades::Personagens::Jogador::mover()
{
    atualizarPosicao();
    relogio.restart();
}

void Pokerun::Entidades::Personagens::Jogador::executar()
{
    mover();
}

void Pokerun::Entidades::Personagens::Jogador::setDirecao(sf::Vector2f dir)
{
    direcao = dir;
}

void Pokerun::Entidades::Personagens::Jogador::atualizarPosicao()
{
    dt = relogio.getElapsedTime().asSeconds();
    
    //1 é p direita, -1 p esquerda e 0 parado
    float dx = direcao.x * vel.x * dt;
    float dy = direcao.y * vel.y * dt;

    corpo.move({dx, dy});
}


