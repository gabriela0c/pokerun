#pragma once

#include "Lista.h"
#include "Entidade.h"

namespace Pokerun{

    namespace Listas{

        class ListaEntidades{
        private:
            Lista<Entidades::Entidade> LEs;

        public:
            ListaEntidades();
            ~ListaEntidades();

            void incluir(Entidades::Entidade* pE);

            void percorrer();
        };
    }
}

