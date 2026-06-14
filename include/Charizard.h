#pragma once 

#include "Inimigo.h"
#include "Projetil.h"
#include <vector>
#include <cmath>

#define LARGURA_CHARIZARD 87.0f
#define ALTURA_CHARIZARD 77.0f

#define NIVEL_MALD_CHEFAO 3
#define N_VDS_CHEFAO 5
#define N_PTS_CHEFAO 600

#define COOLDOWN_TIRO_INIM 2.0f

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            class Charizard : public Inimigo{ //Chefao
            private:
                int raio_ataque;
                std::vector<Projetil*>* pListaProj;
                Temporizador cd_projetil;

            public:
                Charizard();
                virtual ~Charizard();

                void setListaProjeteis(std::vector<Projetil*>* listaProj);
                virtual void danificar(Jogador* p);

                void executar();

            private:
                Jogador* jogadorMaisProximo();
                float distancia(sf::Vector2f a, sf::Vector2f b) const;

            };
        }
    }
}