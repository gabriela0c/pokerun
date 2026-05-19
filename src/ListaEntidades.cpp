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

void Pokerun::Listas::ListaEntidades::percorrer()
{
    Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>* pAux = LEs.getPrimeiro();

    while(pAux != nullptr){
        
        if(pAux->getInfo()){
            (pAux->getInfo())->executar();
        }
        pAux = pAux->getProx();
    }
}
