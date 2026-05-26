#include "Ente.h"

namespace Pokerun {

    Gerenciadores::GerenciadorGrafico* Ente::pGG = Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico();

    Ente::Ente() : ativo(true), pFig(nullptr)
    {
    }

    Ente::~Ente() 
    {
        if (pFig)
            delete pFig;
    }
    
    void Ente::desenhar() {
        if (pGG && pFig) {
            pGG->desenhaElementos(*pFig);
        }
    }

    void Ente::setGG(Gerenciadores::GerenciadorGrafico* pG)
    {
        pGG = pG;
    }

    //const int Ente::getId() const
    //{
    //    return id;
    //}

    const bool Ente::getAtivo() const
    {
        return ativo;
    }

    void Ente::setAtivo(const bool a)
    {
        ativo = a;
    }
    
}
