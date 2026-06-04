
#pragma once

#include "EstadoJogo.h"
#include "FasePrimeira.h"
#include "GerenciadorEvento.h"
#include "Menu.h"

namespace Pokerun{

    class Jogo{
    private:
        EstadoJogo estado;
        Gerenciadores::GerenciadorGrafico* pGrafico; 
        Gerenciadores::GerenciadorEvento* pEvento;
        Entidades::Personagens::Jogador* pJogador1;
        Entidades::Personagens::Jogador* pJogador2;
        Fases::FasePrimeira Fase1;
        Menu menu;

    public:
        Jogo();
        ~Jogo();

        void setEstado(EstadoJogo est);
        EstadoJogo getEstado()const;
        
        void executar();
    };
}