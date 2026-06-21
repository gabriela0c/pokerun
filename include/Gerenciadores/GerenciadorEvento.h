#pragma once

#include <SFML/Graphics.hpp>
#include "Entidades/Personagens/Jogador.h"
#include "Gerenciadores/GerenciadorGrafico.h"

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
            bool flagPausa;
            bool flagCima;
            bool flagBaixo;
            bool flagEnter;
            std::string textoDigitado;

            GerenciadorEvento(); //construtor privado para evitar que outra classe crie um novo
        public:
            ~GerenciadorEvento();

            static GerenciadorEvento* getGerenciadorEvento();
            static void destruir();

            const bool cimaPressionado();
            const bool baixoPressionado();
            const bool enterPressionado();
            const bool pausaPressionado();

            const std::string getTextoDigitado()const;

            void removeJogador2();
            void setJogador(Entidades::Personagens::Jogador* pJog);

            void resetFlags();
            void pollEvent();
            void eventoMovimento(Entidades::Personagens::Jogador* pJog);
            
            void executar();
        };

    }
}