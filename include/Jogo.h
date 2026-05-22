
#pragma once

#include "ListaEntidades.h"
#include "Inimigo.h"
#include "Obstaculo.h"
#include "plataforma.h"
#include "GerenciadorEvento.h"
#include "GerenciadorColisoes.h"

namespace Pokerun{

    class Jogo{
    private:
        Gerenciadores::GerenciadorGrafico* pGrafico; 
        Gerenciadores::GerenciadorEvento* pEvento;
        Gerenciadores::GerenciadorColisoes gColisoes;
        Listas::ListaEntidades Lentidades;
    public:
        Jogo();
        ~Jogo();

        void criarPersonagens();
        
        void executar();
    };
}