#include "InimFacil.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            InimFacil::InimFacil() : Inimigo({LARGURA_BULBASAUR, ALTURA_BULBASAUR},ID::INIMIGO_FACIL), raio(-1)
            {
                num_vidas = 1;
                setTextura("assets/sprites/personagens/inimigo/bulbasaur.png", sf::IntRect({0,0}, {(int)LARGURA_BULBASAUR, (int)ALTURA_BULBASAUR}));
            }

            InimFacil::~InimFacil()
            {

            }

            void InimFacil::executar()
            {
                Inimigo::executar();
            }

            void InimFacil::danificar(Jogador* p)
            {
                std::cout<<"danifiquei"<<std::endl;
                colisaoPersonagem(this, p);
                p->operator--();
                std::cout<<p->getNumvidas()<<std::endl;
            }
        }
    }
}