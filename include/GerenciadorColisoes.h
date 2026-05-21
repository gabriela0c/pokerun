#pragma once

#include <vector>
#include <list>

#include "Entidade.h"
#include "Inimigo.h" //inimigo inclui cmath
#include "Obstaculo.h"
#include "Plataforma.h"

namespace Pokerun{

    namespace Gerenciadores
    {
        class GerenciadorColisoes{
        private:
            Entidades::Personagens::Jogador* pJogador;
            std::vector<Entidades::Personagens::Inimigo*> Linimigos;
            std::list<Entidades::Obstaculos::Obstaculo*> Lobstaculos;

        public:
            GerenciadorColisoes();
            ~GerenciadorColisoes();

            const bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2)const;
            void tratarColisoesJogsObstacs();
            void tratarColisoesJogsInims();
            void tratarColisoesInimsObstacs();

            void setJogador(Entidades::Personagens::Jogador* pJ);
            void incluirInimigo(Entidades::Personagens::Inimigo* pI);
            void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pO);
        };
    }
}