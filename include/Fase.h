#pragma once

#include "Ente.h"
#include "Chao.h"
#include "ListaEntidades.h"
#include "GerenciadorColisoes.h"
#include "Poca.h"
#include "Bulbasaur.h"
#include <vector>

#define WIN_SIZE_X 800.0f
#define WIN_SIZE_Y 600.0f

//dim chao x eh sempre o tamanho da janela
#define DIM_CHAO_Y 50.0f

namespace Pokerun{

    namespace Fases{

        class Fase : public Ente{
        protected:
            Listas::ListaEntidades lista_ents;
            Gerenciadores::GerenciadorColisoes GC;
            Entidades::Personagens::Jogador* pJogador1;
            Entidades::Personagens::Jogador* pJogador2;
            std::vector<sf::FloatRect> posicoesPlataformas;
            Entidades::Chao* pChao;

        public:
            Fase(Entidades::Personagens::Jogador* pJog1 = nullptr, Entidades::Personagens::Jogador* pJog2 = nullptr, const ID i = ID::INDEFINIDO);
            virtual ~Fase();

            virtual void criarInimigos() = 0;
            virtual void criarObstaculos() = 0;

            void desenhar();
            
            void criarBulbasaurs();
            void criarPlataformas();

            Entidades::Chao* getChao()const;

            virtual void executar(); 
        };
    }
}
