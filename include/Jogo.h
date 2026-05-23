
#pragma once

#include "ListaEntidades.h"
#include "Inimigo.h"
#include "Obstaculo.h"
#include "plataforma.h"
#include "GerenciadorEvento.h"
#include "GerenciadorColisoes.h"

#define WIN_SIZE_X 800.0f
#define WIN_SIZE_Y 600.0f

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

        void criarEntidades();
        
        void executar();
    };
}