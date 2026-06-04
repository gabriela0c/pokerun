#include "Wartortle.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Wartortle::Wartortle():
            Inimigo(NIV_MAL_MEDIO, {LARGURA_WARTORTLE, ALTURA_WARTORTLE}, N_VDS_MEDIO)
            {
                setTextura("assets/sprites/personagens/inimigo/wartortle.png", sf::IntRect({0, 0}, {(int)LARGURA_WARTORTLE, (int)ALTURA_WARTORTLE}));
            }

            Wartortle::~Wartortle()
            {

            }

            void Wartortle::danificar(Jogador* p)
            {
                if (p->getInvencivel()) { return; }
                p->operator--();
                p->operator--();
                aplicarKnockback(p, 450.0f);
                p->ativarInvencibilidade();
                std::cout << "Wartortle danificou! Vidas: " << p->getNumvidas() << std::endl;
            }

            void Wartortle::executar()
            {
                Inimigo::executar();
            }
        }
    }
}