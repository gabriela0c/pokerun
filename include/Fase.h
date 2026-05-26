#pragma once

#include "Ente.h"
#include "ListaEntidades.h"
#include "GerenciadorColisoes.h"

#define WIN_SIZE_X 800.0f
#define WIN_SIZE_Y 600.0f

namespace Pokerun{

    namespace Fases{

        class Fase : public Ente {
            protected:
                Lista::ListaEntidade ListaPersonagens;
                Lista::ListaEntidade ListaObstaculos;
                Gerenciador::GerenciadorColisoes* pGC;

        public:
            Fase(Entidades::Personagens::Jogador* pJog = nullptr);
            ~Fase();

                void executar();
                void desenhar();

            protected:
                virtual void criarInimigos()

        }
    }
}
