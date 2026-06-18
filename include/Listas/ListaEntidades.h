#pragma once

#include "Listas/Lista.h"
#include "Entidades/Entidade.h"

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
            void desenhaMembros();
            void remover(Entidades::Entidade* pE);
            void limpar();
            void deletaMembros();
            
            Elem* getPrimeiro()const;
            int getTam()const;

            void conectaBuffer(std::ostream& arquivo);

            std::vector<Entidades::Entidade*> getInativos()const;

            void percorrer();
        };
    }
}

