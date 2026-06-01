#pragma once
#include "Entidade.h"

#define WIN_SIZE_X 800.0f
#define WIN_SIZE_Y 600.0f
#define TAM_CHAO_Y 50.0f

#define LARGURA_CHAO 4145
#define ALTURA_CHAO 137

namespace Pokerun{

    namespace Entidades{

        class Chao : public Entidade{
        private:
            

        public:
            Chao();
            ~Chao();

            void executar();
        };
    }
}