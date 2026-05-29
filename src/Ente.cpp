#include "Ente.h"

namespace Pokerun {

    Gerenciadores::GerenciadorGrafico* Ente::pGG = Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico();

    Ente::Ente(const sf::Vector2f tam, const ID i) : 
    ativo(true), id(i), pFigura(new sf::RectangleShape(tam)), textura()
    {
    }

    Ente::~Ente() 
    {
        if(pFigura){
            delete pFigura;
        pFigura = nullptr;
        }
    }

    void Ente::setGG(Gerenciadores::GerenciadorGrafico* pG)
    {
        pGG = pG;
    }

    bool Ente::getAtivo() const
    {
        return ativo;
    }

    void Ente::setAtivo(const bool a)
    {
        ativo = a;
    }

    ID Ente::getID()const
    {
        return id;
    }

    sf::RectangleShape& Ente::getFig()
    {
        return *pFigura;
    }

    const sf::RectangleShape& Ente::getFig()const
    {
        return *pFigura;
    }
    
    void Ente::desenhar()
    {
        if (pGG) {
            pGG->desenhaElementos(getFig());
        }
    }
}
