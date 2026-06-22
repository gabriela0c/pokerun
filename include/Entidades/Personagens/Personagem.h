#pragma once
//velocidade esta aqui pois eh comum a todos os personagens
#include "Entidades/Entidade.h"

#include <iostream>

#define GRAVIDADE 600.0f
#define VEL_TERM 240.0f

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class Personagem : public Entidade{
            protected:
                float vel_x;
                bool noTeto;
                int num_vidas;

            public:
                Personagem(const sf::Vector2f tam = {}, const sf::Vector2f v = {}, int n_vds = -1);
                virtual ~Personagem();

                void pousar();
                void setNoTeto(const bool nT);
                void setNoChao(const bool nC);

                float getVelX()const;
                void setVelX(const float vX);

                void operator--();
                int getNumvidas()const;

                void desenhar();

                virtual void salvarDataBuffer();
                virtual void carregarDataBuffer(std::istream& is);
                virtual void salvar() = 0;

                virtual void receberDano(int quantidade) = 0;
                virtual void mover() = 0;
                virtual void executar() = 0;
                virtual void desenharHuds() = 0;
            };
        }
    }
}