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
                Temporizador cd_projetil;
                Projetil* pProjetil;

            public:
                Charizard();
                ~Charizard();

                void adicionarProjetil(Projetil* pProj);
                void removerProjetil();
                void danificar(Jogador* p);

                void salvarDataBuffer();  
                void salvar();     
                float getDirProjetil();       

                void executar();

            private:
                Jogador* jogadorMaisProximo();
                float distancia(sf::Vector2f a, sf::Vector2f b) const;

            };
        }
    }
}