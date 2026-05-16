#pragma once

#include "GerenciadorGrafico.h"
#include "Jogador.h"

namespace Pokerun{
    
    namespace Gerenciadores{

        class GerenciadorEvento{
        private:
            GerenciadorGrafico* pGrafico;
            Entidades::Personagens::Jogador* pJogador;

            static GerenciadorEvento* pEvento;

        private:
            GerenciadorEvento();

        public:
            ~GerenciadorEvento();
            static void destruir();

            static GerenciadorEvento* getGerenciadorEvento();

            void setJogador(Entidades::Personagens::Jogador* pjog);
            void verificaTeclaPressionada(sf::Keyboard::Key tecla);
            void verificaTeclaSolta(sf::Keyboard::Key tecla);
            void executar();
        };
    }
}