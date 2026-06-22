#pragma once

#include <fstream>
#include <cstdio>

#include "EstadoJogo.h"
#include "Fases/ViridianForest.h"
#include "Fases/VictoryCave.h"
#include "Gerenciadores/GerenciadorEvento.h"
#include "Menu.h"

namespace Pokerun{

    class Jogo{
    private:
        EstadoJogo estado;
        Gerenciadores::GerenciadorGrafico* pGrafico; 
        Gerenciadores::GerenciadorEvento* pEvento;
        Entidades::Personagens::Jogador* pJogador1;
        Entidades::Personagens::Jogador* pJogador2;
        Fases::ViridianForest Fase1;
        Fases::VictoryCave Fase2;
        Menu menu;

    public:
        Jogo();
        ~Jogo();

        void salvarJogo();
        void continuarJogo();

        void gameOver(const bool resultado);

        void setEstado(EstadoJogo est);
        EstadoJogo getEstado()const;
        
        void executar();
    };
}