#include "Wartortle.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Wartortle::Wartortle():
            Inimigo(NIV_MAL_MEDIO, {LARGURA_WARTORTLE, ALTURA_WARTORTLE},ID::INIMIGO_MEDIO, N_VDS_MEDIO)
            {
                setTextura("assets/sprites/personagens/inimigo/wartortle.png", sf::IntRect({0, 0}, {(int)LARGURA_WARTORTLE, (int)ALTURA_WARTORTLE}));
            }

            Wartortle::~Wartortle()
            {

            }

            void Wartortle::danificar(Jogador* p)
            {
                std::cout<<"fazer algo aqui"<<std::endl;
                colisaoPersonagem(this, p);
                p->operator--();
                std::cout<<p->getNumvidas()<<std::endl;
            }

            void Wartortle::executar()
            {
                Inimigo::executar();
            }
        }
    }
}