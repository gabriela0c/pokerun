
#pragma once

#include "Inimigo.h"
#include "GerenciadorEvento.h"

namespace Pokerun{

    class Jogo{
    private:
        Gerenciadores::GerenciadorGrafico* pGrafico; 
        Gerenciadores::GerenciadorEvento* pEvento;
        std::vector<Entidades::Personagens::Personagem*> Lpersonagens;
    public:
        Jogo();
        ~Jogo();

        void criarPersonagens();
        
        void executar();
    };
}