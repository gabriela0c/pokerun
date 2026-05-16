#include "Personagem.h"

Pokerun::Entidades::Personagens::Personagem::Personagem(const sf::RectangleShape crp, const sf::Vector2f v):
corpo(crp), vel(v), podeAndar(false), paraEsquerda(false), relogio(), dt(0.0f)
{

}

Pokerun::Entidades::Personagens::Personagem::~Personagem()
{

}

const sf::RectangleShape& Pokerun::Entidades::Personagens::Personagem::getCorpo() const
{
    return corpo;
}

void Pokerun::Entidades::Personagens::Personagem::andar(const bool pEsquerda)
{
    podeAndar = true;
    paraEsquerda = pEsquerda;
}

void Pokerun::Entidades::Personagens::Personagem::parar()
{
    podeAndar = false;
}

void Pokerun::Entidades::Personagens::Personagem::atualizarPosicao()
{
    dt = relogio.getElapsedTime().asSeconds();
    float ds = (vel.x)*dt;
    
    if(paraEsquerda){
        ds *= -1;
    }

    corpo.move({ds, 0.0f});
}
