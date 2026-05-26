#include "Ente.h"

namespace Pokerun {

    Gerenciadores::GerenciadorGrafico* Ente::pGG = Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico();

    Ente::Ente(const int id) : 
        id(id), ativo(true) 
    {
    }

    Ente::~Ente() 
    {
    }

    void Ente::setGG(Gerenciadores::GerenciadorGrafico* pG)
    {
        pGG = pG;
    }

    const int Ente::getId() const
    {
        return id;
    }

    const bool Ente::getAtivo() const
    {
        return ativo;
    }

    void Ente::setAtivo(const bool a)
    {
        ativo = a;
    }
}
