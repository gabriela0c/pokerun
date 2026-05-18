#pragma once

#include <SFML/Graphics.hpp>
#include "Jogador.h"
#include "GerenciadorGrafico.h"

namespace Pokerun {

    namespace Gerenciadores {

        class GerenciadorEvento {
        private:
            static GerenciadorEvento* pEvento; 
            GerenciadorGrafico* pGrafico;
            Entidades::Personagens::Jogador* pJogador;

            GerenciadorEvento(); //construtor privado para evitar que outra classe crie um novo
        public:
            ~GerenciadorEvento();

            static GerenciadorEvento* getGerenciadorEvento();
            static void destruir();

            void setJogador(Entidades::Personagens::Jogador* jog);
            void executar();
        };

    }
}