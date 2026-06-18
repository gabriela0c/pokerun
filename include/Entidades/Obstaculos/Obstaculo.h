#pragma once

#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Jogador.h"

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            class Obstaculo : public Entidade{
            protected:
                bool danoso;
                bool solido;
                
            public:
                Obstaculo(const sf::Vector2f tam = {0.0f, 0.0f}, const bool d = false, const bool s = false);
                virtual ~Obstaculo();

                const bool isSolido()const;
                virtual void salvarDataBuffer();
                virtual void carregarDataBuffer(std::istream& is);
                virtual void salvar() = 0;
                
                virtual void executar() = 0;
                virtual void obstaculizar(Personagens::Jogador* pJog) = 0;
            };
        }
    }
}