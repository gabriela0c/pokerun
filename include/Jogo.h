
#pragma once

#include "FasePrimeira.h"
#include "GerenciadorEvento.h"

namespace Pokerun{

    class Jogo{
    private:
        Gerenciadores::GerenciadorGrafico* pGrafico; 
        Gerenciadores::GerenciadorEvento* pEvento;
        Entidades::Personagens::Jogador* pJogador1;
        Entidades::Personagens::Jogador* pJogador2;
        Fases::FasePrimeira Fase1;

    public:
        Jogo();
        ~Jogo();
        
        void executar();
    };
}