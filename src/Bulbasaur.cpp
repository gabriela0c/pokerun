#include "Bulbasaur.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Bulbasaur::Bulbasaur() : Inimigo(NIVEL_MALD_FACIL, {LARGURA_BULBASAUR, ALTURA_BULBASAUR}, N_VDS_FACIL), raio(-1)
            {
                setTextura("assets/sprites/personagens/inimigo/bulbasaur.png", sf::IntRect({0,0}, {(int)LARGURA_BULBASAUR, (int)ALTURA_BULBASAUR}));
            }

            Bulbasaur::~Bulbasaur()
            {

            }

            void Bulbasaur::executar()
            {
                Inimigo::executar();
            }

            void Bulbasaur::danificar(Jogador* p)
            {
                //std::cout<<"danifiquei"<<std::endl;
                p->operator--();
                //std::cout<<p->getNumvidas()<<std::endl;
            }
        }
    }
}