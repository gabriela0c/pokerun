#include "Inimigo.h"

Pokerun::Entidades::Personagens::Inimigo::Inimigo():
Personagem(sf::RectangleShape({TAM_INIM_X, TAM_INIM_Y}), {VEL_INIM_X, VEL_INIM_Y}), jogador(nullptr), relogio(), moveAleatorio(rand()%4)
{
    corpo.setPosition({POS0_INIM_X, POS0_INIM_X});
    corpo.setFillColor(sf::Color::Red);
}

Pokerun::Entidades::Personagens::Inimigo::~Inimigo()
{

}

void Pokerun::Entidades::Personagens::Inimigo::setJogador(const Jogador* jog)
{
    if(jog){
        jogador = jog;
    }
}

const Pokerun::Entidades::Personagens::Jogador* Pokerun::Entidades::Personagens::Inimigo::getJogador() const
{
    return jogador;
}

void Pokerun::Entidades::Personagens::Inimigo::atualizar()
{
    if(!jogador) {
        std::cerr<<"Jogador Nulo"<<std::endl;
        return;
    }

    sf::Vector2f posJogador = jogador->getCorpo().getPosition();
    sf::Vector2f posInimigo = corpo.getPosition();

    if(fabs(posInimigo.x - posJogador.x) <= RAIO_X && fabs(posInimigo.y - posJogador.y) <= RAIO_Y){
        persegueJogador(posJogador, posInimigo);
    }
    else{
        movimentoAleatorio();
    }
}

void Pokerun::Entidades::Personagens::Inimigo::movimentoAleatorio()
{
    if(moveAleatorio == 0){
        corpo.move({vel.x, 0.0f});
    }
    else if(moveAleatorio == 1){
        corpo.move({-vel.x, 0.0f});
    }
    else if(moveAleatorio == 2){
        corpo.move({0.0f, vel.y});
    }
    else{
        corpo.move({0.0f, -vel.y});
    }

    float dt = relogio.getElapsedTime().asSeconds();

    if(dt >= 0.5){
        moveAleatorio = rand()%4;
        relogio.restart();
    }
}

void Pokerun::Entidades::Personagens::Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
{
    if(posJogador.x - posInimigo.x > 0.0f){
        corpo.move({vel.x, 0.0f});
    }
    else{
        corpo.move({-vel.x, 0.0f});
    }

    if(posJogador.y - posInimigo.y > 0.0f){
        corpo.move({0.0f, vel.y}); 
    }
    else{
        corpo.move({0.0f, -vel.y});
    }
}
