#include "GerenciadorGrafico.h"

Pokerun::Gerenciadores::GerenciadorGrafico::GerenciadorGrafico():
window (new sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "Pokerun"))
{

}

Pokerun::Gerenciadores::GerenciadorGrafico* Pokerun::Gerenciadores::GerenciadorGrafico::pGrafico(nullptr);

Pokerun::Gerenciadores::GerenciadorGrafico::~GerenciadorGrafico()
{
    if(window){
        delete window;
        window = nullptr;
    }
}

void Pokerun::Gerenciadores::GerenciadorGrafico::destruir()
{
    if(pGrafico){
        delete pGrafico;
        pGrafico = nullptr;
    }
}

Pokerun::Gerenciadores::GerenciadorGrafico* Pokerun::Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()
{
    if(!pGrafico){
        pGrafico = new GerenciadorGrafico();
    }
    
    return pGrafico;
}

sf::RenderWindow* Pokerun::Gerenciadores::GerenciadorGrafico::getWindow()
{
    return window;
}

void Pokerun::Gerenciadores::GerenciadorGrafico::limpaJanela()
{
    if(window){
        window->clear();
    }
}

void Pokerun::Gerenciadores::GerenciadorGrafico::desenhaElementos(sf::RectangleShape& corpo)
{
    if(window){
        window->draw(corpo);
    }
}

void Pokerun::Gerenciadores::GerenciadorGrafico::mostraElementos()
{
    if(window){
        window->display();
    }
}

void Pokerun::Gerenciadores::GerenciadorGrafico::fecharJanela()
{
    if(window){
        window->close();
    }
}

const bool Pokerun::Gerenciadores::GerenciadorGrafico::verificaJanelaAberta()
{
    if(window){
    return (window->isOpen());
    }
    std::cout<<"janela nula"<<std::endl;
    return false;
}