#include "Personagem.h"

Pokerun::Entidades::Personagens::Personagem::Personagem(const sf::Vector2f tam, const sf::Vector2f v):
Entidade(tam), vel(v), direcao({0.0f, 0.0f}), relogio(), dt(0.0f)
{
    
}

Pokerun::Entidades::Personagens::Personagem::~Personagem()
{

}

void Pokerun::Entidades::Personagens::Personagem::setDirecao(sf::Vector2f dir)
{
    direcao = dir;
}

void Pokerun::Entidades::Personagens::Personagem::atualizarPosicao()
{
    dt = relogio.getElapsedTime().asSeconds();
    
    //1 é p direita, -1 p esquerda e 0 parado
    float dx = direcao.x * vel.x * dt;
    float dy = direcao.y * vel.y * dt;

    corpo.move({dx, dy});
}