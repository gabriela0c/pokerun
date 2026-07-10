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

        void ListaEntidades::desenhaMembros()
        {
            Elem* pAux = LEs.getPrimeiro();
            while(pAux!=nullptr){
                if(pAux->getInfo() && pAux->getInfo()->getAtivo()){
                    pAux->getInfo()->desenhar();
                }    
            pAux = pAux->getProx();
            }   
        }

        void ListaEntidades::deletaMembros()
        {
            Listas::Elem* pAux = LEs.getPrimeiro();
            while(pAux != nullptr){                       
                Entidades::Entidade* pE = pAux->getInfo();
                if(pE){
                    delete pE;
                    pE = nullptr;         
                }
                pAux = pAux->getProx();
            }
        }

        void ListaEntidades::executarMembros()
        {
            Elem* pAux = LEs.getPrimeiro();

            while(pAux != nullptr){
                
                if(pAux->getInfo() && pAux->getInfo()->getAtivo()){
                    (pAux->getInfo())->executar();
                    (pAux->getInfo())->sincronizarPosicao();
                }
                pAux = pAux->getProx();
            }
        }
    }
}