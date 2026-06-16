#pragma once

#include "Entidades/Projetil.h"

namespace Pokerun{

    class ReceptorProjetil{
    public:
        ReceptorProjetil(){};
        virtual ~ReceptorProjetil(){};

        virtual void adicionarProjetil(Entidades::Projetil* pProj) = 0;
    };
}