#pragma once

#include <SFML/Graphics.hpp>
#include "Jogador.h"
#include "GerenciadorGrafico.h"

#define LARGURA_PIKACHU 40
#define ALTURA_PIKACHU 38

#define LARGURA_RAICHU 48
#define ALTURA_RAICHU 46

namespace Pokerun {

    namespace Gerenciadores {

        class GerenciadorEvento {
        private:
            static GerenciadorEvento* pEvento; 
            GerenciadorGrafico* pGrafico;
            Entidades::Personagens::Jogador* pJogador1;
            Entidades::Personagens::Jogador* pJogador2;

            GerenciadorEvento(); //construtor privado para evitar que outra classe crie um novo
        public:
            ~GerenciadorEvento();

            static GerenciadorEvento* getGerenciadorEvento();
            static void destruir();

            void setJogador1(Entidades::Personagens::Jogador* jog1);
            void setJogador2(Entidades::Personagens::Jogador* jog2);
            void executar();
        };

    }
}