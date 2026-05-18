#include "GerenciadorEvento.h"

using namespace Pokerun::Gerenciadores;

GerenciadorEvento* GerenciadorEvento::pEvento = nullptr;

GerenciadorEvento::GerenciadorEvento(): pGrafico(GerenciadorGrafico::getGerenciadorGrafico()), pJogador(nullptr)
{

}

GerenciadorEvento::~GerenciadorEvento()
{

}

GerenciadorEvento* GerenciadorEvento::getGerenciadorEvento() 
{
    if (pEvento == nullptr) 
    {
        pEvento = new GerenciadorEvento();
    }
    return pEvento;
}

void GerenciadorEvento::destruir() 
{
    if (pEvento) 
    {
        delete pEvento;
        pEvento = nullptr;
    }
}

void GerenciadorEvento::setJogador(Pokerun::Entidades::Personagens::Jogador* jog) 
{
    pJogador = jog;
}

void GerenciadorEvento::executar() {
    
    while (const auto event = pGrafico->getWindow()->pollEvent()) 
    {
        if (event->getIf<sf::Event::Closed>()) 
        {
            pGrafico->getWindow()->close();
        }
    }
    
    if (pJogador) 
    {
        sf::Vector2f novaDirecao(0.0f, 0.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            novaDirecao.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            novaDirecao.x += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            novaDirecao.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            novaDirecao.y += 1.0f;
        }

        pJogador->setDirecao(novaDirecao);
    }
}