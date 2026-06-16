#pragma once
#include "Entidade.h"
#include "Jogador.h"

#define LARGURA_PROJ 15.0f
#define ALTURA_PROJ 15.0f

#define TAMANHO_PROJ_X 104
#define TAMANHO_PROJ_Y 169

#define VEL_PROJETIL_X 300.0f
#define DANO_PROJETIL 3

#define WIN_SIZE_X 800.0f
#define WIN_SIZE_Y 600.0f

namespace Pokerun {
    namespace Entidades {

        namespace Personagens{
            class Charizard;
        }

        class Projetil : public Entidade {
        private:
            float vel_x;
            const float dano;
            Personagens::Charizard* pCharizard;

        public:
            Projetil(float velX);
            ~Projetil();

            void salvarDataBuffer();  
            void salvar();            

            const int getDano()const;
            void setCharizard(Personagens::Charizard* pChar);
            
            void executar();
        };

    }
}