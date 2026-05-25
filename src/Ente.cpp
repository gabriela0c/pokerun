#include "Ente.h"

namespace Pokerun {

    Gerenciadores::GerenciadorGrafico* Ente::pGG = Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico();

    Ente::Ente() : ativo(true) 
    {
    }

    Ente::~Ente() 
    {
    }
}