#pragma once

#include "Ente.h"
#include "Entidades/Chao.h"
#include "Listas/ListaEntidades.h"
#include "Gerenciadores/GerenciadorColisoes.h"
#include "Entidades/Obstaculos/Poca.h"
#include "Entidades/Obstaculos/Plataforma.h"
#include "Entidades/Obstaculos/Fogo.h"
#include "Entidades/Personagens/Bulbasaur.h"
#include "Entidades/Personagens/Wartortle.h"
#include "Entidades/Personagens/Charizard.h"
#include "Entidades/Projetil.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#define WIN_SIZE_X 800.0f
#define WIN_SIZE_Y 600.0f

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
            const int maxBulbasaurs;
            const int maxPlataformas;

        public:
            Fase(Entidades::Personagens::Jogador* pJog1 = nullptr, Entidades::Personagens::Jogador* pJog2 = nullptr);
            virtual ~Fase();

            virtual void criarInimigos() = 0;
            virtual void criarObstaculos() = 0;

            void desenhar();

            void adicionarInimigos(Entidades::Personagens::Inimigo* pInim);
            void adicionarObstaculos(Entidades::Obstaculos::Obstaculo* pObs);
            void adicionarProjetil(Entidades::Projetil* pProj);
            void colocaNaPlataforma(Entidades::Obstaculos::Obstaculo* pObs);
            
            void criarBulbasaurs();
            void criarPlataformas();
            void criarCenario();

            void ativaJogador(Entidades::Personagens::Jogador* pJog);
            void passarJogador(Entidades::Personagens::Jogador* pJog);
            void desativaEntidade(Entidades::Entidade* pE);

            void removerInativos();
            void limpaFase();

            const bool semInimigos()const;

            void gravaFase();
            int recuperaFase();
            virtual std::string getNomeArquivo()const = 0;
            Entidades::Entidade* criarPorTipo(const std::string tipo);

            virtual void executar();
        };
    }
}
