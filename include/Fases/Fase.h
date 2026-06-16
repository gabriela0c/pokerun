#pragma once

#include "Ente.h"
#include "Entidades/Chao.h"
#include "Listas/ListaEntidades.h"
#include "Gerenciadores/GerenciadorColisoes.h"
#include "Entidades/Obstaculos/Poca.h"
#include "Entidades/Obstaculos/Fogo.h"
#include "Entidades/Personagens/Bulbasaur.h"
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
            const int maxBulbasaurs;//ja que ele esta em ambas as fases

        public:
            Fase(Entidades::Personagens::Jogador* pJog1 = nullptr, Entidades::Personagens::Jogador* pJog2 = nullptr);
            virtual ~Fase();

            virtual void criarInimigos() = 0;
            virtual void criarObstaculos() = 0;

            void desenhar();
            
            void criarBulbasaurs();
            void criarPlataformas();
            void criarCenario();

            void ativaJogador(Entidades::Personagens::Jogador* pJog);
            void desativaEntidade(Entidades::Entidade* pE);

            Entidades::Chao* getChao()const;

            void removerInativos();

            virtual void executar(); 
        };
    }
}
