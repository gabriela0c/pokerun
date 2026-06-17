#include "Listas/ListaEntidades.h"

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

        void ListaEntidades::remover(Entidades::Entidade* pE)
        {
            if(pE){
                LEs.remover(pE);
            }
        }

        void ListaEntidades::limpar()
        {
            LEs.limpar();
        }

        Elem* ListaEntidades::getPrimeiro()const
        {
            return LEs.getPrimeiro();
        }

        int ListaEntidades::getTam()const
        {
            return LEs.getTam();
        }

        std::vector<Entidades::Entidade*> ListaEntidades::getInativos()const
        {
            std::vector<Entidades::Entidade*> inativos;
            
            Elem* pAux = LEs.getPrimeiro();

            while(pAux != nullptr){
                if(pAux->getInfo() && !pAux->getInfo()->getAtivo()){//nem verifica a segunda condicao se a primeira for falsa, nao da seg fault
                    inativos.push_back(pAux->getInfo());
                }
                pAux = pAux->getProx();
            }

            return inativos;
        }

        void ListaEntidades::conectaBuffer(std::ostream& arquivo)
        {
            Elem* pAux = LEs.getPrimeiro();

            while(pAux != nullptr){
                
                if(pAux->getInfo()){
                    (pAux->getInfo())->conectarSaida(arquivo);
                    (pAux->getInfo())->salvar();
                }
                pAux = pAux->getProx();
            }
        }

        void ListaEntidades::percorrer()
        {
            Elem* pAux = LEs.getPrimeiro();

            while(pAux != nullptr){
                
                if(pAux->getInfo()){
                    (pAux->getInfo())->executar();
                    (pAux->getInfo())->sincronizarPosicao();
                }
                pAux = pAux->getProx();
            }
        }
    }
}