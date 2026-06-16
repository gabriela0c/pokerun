#pragma once 

#include "Entidades/Personagens/Inimigo.h"
#include "Entidades/Projetil.h"
#include "ReceptorProjetil.h"
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
                ReceptorProjetil* pReceptor;
                std::vector<Projetil*> lProjeteis;

            public:
                Charizard();
                ~Charizard();

                void setReceptorProjeteis(ReceptorProjetil* pRec);
                void adicionarProjetil(Projetil* pProj);
                void removerProjetil(Projetil* pProj);
                void danificar(Jogador* p);

                void salvarDataBuffer();  
                void salvar();            

                void executar();

            private:
                Jogador* jogadorMaisProximo();
                float distancia(sf::Vector2f a, sf::Vector2f b) const;

            };
        }
    }
}