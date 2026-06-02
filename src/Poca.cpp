#include "Poca.h"

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            Poca::Poca():
            Obstaculo({TAM_OBST_MEDIO_X, TAM_OBST_MEDIO_Y}, false, ID::OBST_MEDIO), profundidade((float)(rand()%41) + 40)
            {
                setTextura("assets/sprites/obstaculos/poca.png", sf::IntRect({0, 0}, {LARGURA_OBST_MEDIO, ALTURA_OBST_MEDIO}));
            }

            Poca::~Poca()
            {

            }

            void Poca::executar()
            {

            }

            void Poca::obstaculizar(Personagens::Jogador* pJog)
            {
                if(pJog){   
                    float taxa = 1 - (profundidade/100); //para fazer a vel do jogador diminuir algo entre 40 e 80%
                    pJog->diminui_vel(taxa);
               }
            }
        }
    }
}