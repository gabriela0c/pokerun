#include "InimFacil.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            InimFacil::InimFacil() : Inimigo({LARGURA_BULBASAUR, ALTURA_BULBASAUR},ID::INIMIGO_FACIL), raio(-1)
            {
                num_vidas = 1;

                if(!textura.loadFromFile("assets/sprites/personagens/inimigo/bulbasaur.png"))
                //sprite retirada do site oficial da franquia Pokemon
                    std::cout << "ERRO: Nao foi possivel carregar a textura do inimigo!" << std::endl;
                
                pFigura->setTexture(&textura);
                pFigura->setTextureRect(sf::IntRect({0, 0}, {LARGURA_BULBASAUR, ALTURA_BULBASAUR}));
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