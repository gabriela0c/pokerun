#pragma once

#include "Lista.h"
#include "Entidade.h"

namespace Pokerun{

    namespace Listas{

        using Elem = Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>;

        class ListaEntidades{
        private:
            Lista<Entidades::Entidade> LEs;
        public:
            ListaEntidades();
            ~ListaEntidades();

            void incluir(Entidades::Entidade* pE);
            Elem* getPrimeiro()const;
            int getTam()const;

            void percorrer();
        };
    }
}

