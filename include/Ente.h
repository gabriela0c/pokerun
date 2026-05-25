#pragma once
#include "GerenciadorGrafico.h"

namespace Pokerun {

    class Ente {
    protected:
        static Gerenciadores::GerenciadorGrafico* pGG;
        bool ativo;

    public:
        Ente();
        virtual ~Ente();

        virtual void executar() = 0;
        virtual void desenhar() = 0;

        void setAtivo(bool a) 
        { 
            ativo = a; 
        }
        bool getAtivo() const 
        { 
            return ativo; 
        }
    };
}