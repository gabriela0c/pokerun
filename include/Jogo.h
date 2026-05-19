
#pragma once

#include "ListaEntidades.h"
#include "Inimigo.h"
#include "GerenciadorEvento.h"

namespace Pokerun{

    class Jogo{
    private:
        Gerenciadores::GerenciadorGrafico* pGrafico; 
        Gerenciadores::GerenciadorEvento* pEvento;
        Listas::ListaEntidades Lentidades;
    public:
        Jogo();
        ~Jogo();

        void criarPersonagens();
        
        void executar();
    };
}