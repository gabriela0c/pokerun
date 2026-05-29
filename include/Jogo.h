
#pragma once

#include "FasePrimeira.h"
#include "GerenciadorEvento.h"

namespace Pokerun{

    class Jogo{
    private:
        Gerenciadores::GerenciadorGrafico* pGrafico; 
        Gerenciadores::GerenciadorEvento* pEvento;
        Entidades::Personagens::Jogador* pJogador;
        Fases::FasePrimeira Fase1;
        //Entidades::Personagens::Jogador* pJogador;
    public:
        Jogo();
        ~Jogo();
        
        void executar();
    };
}