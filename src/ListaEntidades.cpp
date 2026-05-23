#include "ListaEntidades.h"

namespace Pokerun{

    namespace Listas{

        ListaEntidades::ListaEntidades():
        LEs()
        {

        }

        ListaEntidades::~ListaEntidades()
        {
            
        }

        void ListaEntidades::incluir(Entidades::Entidade* pE)
        {
            if(pE){
                LEs.incluir(pE);
            }
        }

        Elem* ListaEntidades::getPrimeiro()const
        {
            return LEs.getPrimeiro();
        }

        int ListaEntidades::getTam()const
        {
            return LEs.getTam();
        }

        void ListaEntidades::percorrer()
        {
            Elem* pAux = LEs.getPrimeiro();

            while(pAux != nullptr){
                
                if(pAux->getInfo()){
                    (pAux->getInfo())->executar();
                }
                pAux = pAux->getProx();
            }
        }
    }
}