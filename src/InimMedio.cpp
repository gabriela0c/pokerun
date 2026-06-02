#include "InimMedio.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            InimMedio::InimMedio():
            Inimigo(NIV_MAL_MEDIO, {LARGURA_WARTORTLE, ALTURA_WARTORTLE},ID::INIMIGO_MEDIO, N_VDS_MEDIO)
            {
                setTextura("assets/sprites/personagens/inimigo/wartortle.png", sf::IntRect({0, 0}, {(int)LARGURA_WARTORTLE, (int)ALTURA_WARTORTLE}));
            }

            InimMedio::~InimMedio()
            {

            }

            void InimMedio::danificar(Jogador* p)
            {
                std::cout<<"fazer algo aqui"<<std::endl;
                colisaoPersonagem(this, p);
                p->operator--();
                std::cout<<p->getNumvidas()<<std::endl;
            }

            void InimMedio::executar()
            {
                Inimigo::executar();
            }
        }
    }
}