#include "InimMedio.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            InimMedio::InimMedio():
            Inimigo({LARGURA_SQUIRTLE, ALTURA_SQUIRTLE},ID::INIMIGO_MEDIO)
            {
                num_vidas = 2;
            }

            InimMedio::~InimMedio()
            {

            }

            void InimMedio::danificar(Jogador* p)
            {
                std::cout<<"fazer algo aqui"<<std::endl;
            }

            void InimMedio::executar()
            {
                Inimigo::executar();
            }
        }
    }
}