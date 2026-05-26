#pragma once

#include "Ente.h"
#include "ListaEntidades.h"
#include "GerenciadorColisoes.h"

#define WIN_SIZE_X 800.0f
#define WIN_SIZE_Y 600.0f

namespace Pokerun{

    namespace Fases{

        class Fase : public Ente{
        protected:
            Listas::ListaEntidades lista_ents;
            Gerenciadores::GerenciadorColisoes GC;
            Entidades::Personagens::Jogador* pJogador;

        public:
            Fase(Entidades::Personagens::Jogador* pJog = nullptr);
            ~Fase();

            virtual void criarInimigos() = 0;
            virtual void criarObstaculos() = 0;
            void desenhar();
            
            void criarInimFaceis();
            
            void criarPlataformas();

            //void criarCenario();

            virtual void executar(); //executa todos da lista, gerenciador de colisoes verifica se colisao, redesenha window com gerenciador grafico
            //talvez gerenciador evento em algum lugar?
        };
    }
}
