#pragma once
#include "GerenciadorGrafico.h"

namespace Pokerun {

    class Ente {
    protected:
        int id;
        bool ativo;    
        static Gerenciadores::GerenciadorGrafico* pGG;
        
    public:
        Ente(const int id = 0);
        virtual ~Ente();

        virtual void executar() = 0;
        virtual void desenhar() = 0;

        static void setGG(Gerenciadores::GerenciadorGrafico* pG);

        const int getId() const;
        const bool getAtivo() const;
        void setAtivo(const bool a);
    };
}