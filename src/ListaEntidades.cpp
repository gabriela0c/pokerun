#include "ListaEntidades.h"

Pokerun::Listas::ListaEntidades::ListaEntidades():
LEs()
{

}

Pokerun::Listas::ListaEntidades::~ListaEntidades()
{
    
}

void Pokerun::Listas::ListaEntidades::incluir(Entidades::Entidade* pE)
{
    if(pE){
        LEs.incluir(pE);
    }
}

Pokerun::Listas::Elem* Pokerun::Listas::ListaEntidades::getPrimeiro()const
{
    return LEs.getPrimeiro();
}

int Pokerun::Listas::ListaEntidades::getTam()const
{
    return LEs.getTam();
}

void Pokerun::Listas::ListaEntidades::percorrer()
{
    Elem* pAux = LEs.getPrimeiro();

    while(pAux != nullptr){
        
        if(pAux->getInfo()){
            (pAux->getInfo())->executar();
        }
        pAux = pAux->getProx();
    }
}
