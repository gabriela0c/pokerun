#include "Entidades/Personagens/Bulbasaur.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Bulbasaur::Bulbasaur() : Inimigo(NIVEL_MALD_FACIL, {LARGURA_BULBASAUR, ALTURA_BULBASAUR}, N_VDS_FACIL, N_PTS_FACIL), chance_veneno((rand()%10) + 1)
            {
                setTextura("assets/sprites/personagens/inimigo/bulbasaur.png", sf::IntRect({0,0}, {(int)LARGURA_BULBASAUR, (int)ALTURA_BULBASAUR}));
            }

            Bulbasaur::~Bulbasaur()
            {

            }

            void Bulbasaur::salvarDataBuffer()
            {
                Inimigo::salvarDataBuffer();
                buffer << " " << chance_veneno;
            }

            void Bulbasaur::salvar()
            {
                buffer.str("");
                salvarDataBuffer();
                std::ofstream arquivo("save.dat", std::ios::app);
                arquivo << "BULBASAUR " << buffer.str() << std::endl;
            }

            void Bulbasaur::executar()
            {
                Inimigo::executar();
            }

            void Bulbasaur::danificar(Jogador* p)
            {
                if (p->getInvencivel()) { return; }
 
                for(int i = 0; i < nivel_maldade; i++){
                    p->operator--();
                }
                
                aplicarKnockback(p, 200.0f);
 
                //chance de envenenar — número aleatório entre 1 e 10
                if (((rand() % 10) + 1)  < chance_veneno)
                {
                    p->envenenar();
                }
 
                p->ativarInvencibilidade();
                std::cout << "Bulbasaur danificou " << (p->getEhJogador1() ? "Pikachu" : "Raichu") << "! Vidas: " << p->getNumvidas() << std::endl;
            }
        }
    }
}