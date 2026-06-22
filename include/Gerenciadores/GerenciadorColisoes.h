#pragma once

#include <vector>
#include <list>
#include <set>

#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Personagem.h"
#include "Entidades/Personagens/Inimigo.h"
#include "Entidades/Obstaculos/Obstaculo.h"
#include "Entidades/Obstaculos/Plataforma.h"
#include "Entidades/Projetil.h"
#include "Entidades/Chao.h"

#define ALCANCE_ATAQUE_X 80.0f
#define FAIXA_ATAQUE_Y 30.0f

namespace Pokerun{

    namespace Gerenciadores
    {

        class GerenciadorColisoes{
        private:
            Entidades::Personagens::Jogador* pJogador1;
            Entidades::Personagens::Jogador* pJogador2;
            std::vector<Entidades::Personagens::Inimigo*> Linimigos;
            std::list<Entidades::Obstaculos::Obstaculo*> Lobstaculos;
            std::set<Entidades::Projetil*> setProjeteis;
            Entidades::Chao* pChao;
            float limiteEsquerdo;
            float limiteDireito;

        public:
            GerenciadorColisoes();
            ~GerenciadorColisoes();

            const bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2)const;
            void tratarColisoesJogsObstacs();
            void tratarColisoesJogsInims();
            void tratarColisoesInimsObstacs();
            void tratarColisoesInimsInims();
            void tratarColisoesJogsJogs();
            void tratarColisoesPersChao();
            void tratarColisoesProjeteis();
            void tratarColisoesParedes();
            void tratarParedePersonagem(Entidades::Personagens::Personagem* pP);

            void aplicarAtaqueJog(Entidades::Personagens::Jogador* pJog);
            const bool inRange(Entidades::Personagens::Jogador* pJog, Entidades::Personagens::Inimigo* pInim)const;

            void colisaoPersonagens(Entidades::Personagens::Personagem* p1, Entidades::Personagens::Personagem* p2);
            void colisaoPersonagemEntidade(Entidades::Personagens::Personagem* pP, Entidades::Entidade* pE);

            void setJogador(Entidades::Personagens::Jogador* pJog);
            void remover(Entidades::Entidade* pE);
            void limparListas();
            void setChao(Entidades::Chao* pCh);

            void incluirInimigo(Entidades::Personagens::Inimigo* pI);
            void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pO);
            void incluirProjetil(Entidades::Projetil* pProj);

            const int getNumInimigos()const;

            void executar();
        };
    }
}