#pragma once

#include "Lista.h"
#include "Entidade.h"

namespace Pokerun{

    namespace Listas{

        using Elem = Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>; //esse tipo era muito complexo e o compilador nao pegava

        class ListaEntidades{
        private:
            Lista<Entidades::Entidade> LEs;
        public:
            ListaEntidades();
            ~ListaEntidades();

            void incluir(Entidades::Entidade* pE);
            void remover(Entidades::Entidade* pE);
            void limpar();
            
            Elem* getPrimeiro()const;
            int getTam()const;

            std::vector<Entidades::Entidade*> getInativos()const;

            void percorrer();
        };
    }
}

