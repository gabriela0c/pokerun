#include "Bulbasaur.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Bulbasaur::Bulbasaur() : Inimigo(NIVEL_MALD_FACIL, {LARGURA_BULBASAUR, ALTURA_BULBASAUR}, N_VDS_FACIL), chance_veneno(0.5f)
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
                if (p->getInvencivel()) { return; }
 
                for(int i = 0; i < NIVEL_MALD_FACIL; i++){
                    p->operator--();
                }
                
                aplicarKnockback(p, 200.0f);
 
                //chance de envenenar — número aleatório entre 0.0 e 1.0
                float chance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                if (chance <= chance_veneno)
                {
                    p->envenenar();
                }
 
                p->ativarInvencibilidade();
                std::cout << "Bulbasaur danificou " << (p->getEhJogador1() ? "Pikachu" : "Raichu") << "! Vidas: " << p->getNumvidas() << std::endl;
            }
        }
    }
}