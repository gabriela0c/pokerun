#pragma once

#include <vector>
#include <list>

#include "Entidade.h"
#include "Personagem.h"
#include "Inimigo.h" //inimigo inclui cmath
#include "Obstaculo.h"
#include "Plataforma.h"
#include "Chao.h"

namespace Pokerun{

    namespace Gerenciadores
    {

        class GerenciadorColisoes{
        private:
            Entidades::Personagens::Jogador* pJogador1;
            Entidades::Personagens::Jogador* pJogador2;
            std::vector<Entidades::Personagens::Inimigo*> Linimigos;
            std::list<Entidades::Obstaculos::Obstaculo*> Lobstaculos;
            Entidades::Chao* pChao;

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

            void colisaoPersonagens(Entidades::Personagens::Personagem* p1, Entidades::Personagens::Personagem* p2);
            void colisaoPersonagemEntidade(Entidades::Personagens::Personagem* pP, Entidades::Entidade* pE);

            void setJogador(Entidades::Personagens::Jogador* pJog);
            void removeJogador(Entidades::Personagens::Jogador* pJog);
            void setChao(Entidades::Chao* pCh);

            void incluirInimigo(Entidades::Personagens::Inimigo* pI);
            void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pO);
            //void incluirProjetil(Entidades::Projetil* pProj);

            void executar();
        };
    }
}