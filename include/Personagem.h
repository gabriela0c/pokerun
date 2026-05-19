#pragma once
//velocidade esta aqui pois eh comum a todos os personagens
//REMOVER ESSE COMENTARIO DPS {seria mais interessante implementar o movimento do inimigo de maneira que ele
//tambem aproveite essa funcao atualizar posicao, senao faria mais sentido criar um metodo generico
//mover e implementar esse algoritimo na mover do jogador, e a mover do inimigo faz o que ja faz}
#include "Entidade.h"

#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class Personagem : public Entidade{
            protected:
                const sf::Vector2f vel;
                sf::Vector2f direcao;
                sf::Clock relogio;
                float dt;

            public:
                Personagem(const sf::Vector2f tam = {}, const sf::Vector2f v = {});
                virtual ~Personagem();

                void setDirecao(sf::Vector2f dir);
                void atualizarPosicao();

                virtual void executar() = 0;
            };
        }
    }
}