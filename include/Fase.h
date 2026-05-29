#pragma once

#include "Ente.h"
#include "ListaEntidades.h"
#include "GerenciadorColisoes.h"
#include "Chao.h"
#include "ObstMedio.h"
#include <vector>

#define WIN_SIZE_X 800.0f
#define WIN_SIZE_Y 600.0f

#define DIM_CHAO_X 1000.0f
#define DIM_CHAO_Y 50.0f

namespace Pokerun{

    namespace Fases{

        class Fase : public Ente{
        private:
            sf::Texture texturaFundo;
        protected:
            Listas::ListaEntidades lista_ents;
            Gerenciadores::GerenciadorColisoes GC;
            Entidades::Personagens::Jogador* pJogador;
            std::vector<sf::FloatRect> posicoesPlataformas;

        public:
            Fase(Entidades::Personagens::Jogador* pJog = nullptr, const ID i = ID::INDEFINIDO);
            ~Fase();

            virtual void criarInimigos() = 0;
            virtual void criarObstaculos() = 0;

            
            void criarChao();
            void desenhar();
            
            void criarInimFaceis();
            void criarPlataformas();

            virtual void executar(); //executa todos da lista, gerenciador de colisoes verifica se colisao, redesenha window com gerenciador grafico
            //talvez gerenciador evento em algum lugar?
        };
    }
}
