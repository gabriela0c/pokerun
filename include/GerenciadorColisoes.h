#pragma once

#include <vector>
#include <list>

#include "Entidade.h"
#include "Personagem.h"
#include "Inimigo.h" //inimigo inclui cmath
#include "Obstaculo.h"
#include "Plataforma.h"

namespace Pokerun{

    namespace Gerenciadores
    {
        class GerenciadorColisoes{
        private:
            Entidades::Personagens::Jogador* pJogador1;
            Entidades::Personagens::Jogador* pJogador2;
            std::vector<Entidades::Personagens::Inimigo*> Linimigos;
            std::list<Entidades::Obstaculos::Obstaculo*> Lobstaculos;

        public:
            GerenciadorColisoes();
            ~GerenciadorColisoes();

            const bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2)const;
            void tratarColisoesJogsObstacs();
            void tratarColisoesJogsInims();
            void tratarColisoesInimsObstacs();
            void tratarColisoesInimsInims();
            void tratarColisoesJogsJogs();

            void setJogador1(Entidades::Personagens::Jogador* pJog1);
            void setJogador2(Entidades::Personagens::Jogador* pJog2);
            void incluirInimigo(Entidades::Personagens::Inimigo* pI);
            void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pO);

            void executar();
        };
    }
}