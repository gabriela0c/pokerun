#pragma once

#include <vector>

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
            void remover(Entidades::Entidade* pE);
            void desenhaMembros();
            void deletaMembros();
            void limpar();
            
            Elem* getPrimeiro()const;

            void conectaBuffer(std::ostream& arquivo);

            void executarMembros();
        };
    }
}

