#include "Entidades/Personagens/Wartortle.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Wartortle::Wartortle():
            Inimigo(NIVEL_MALD_MEDIO, {LARGURA_WARTORTLE, ALTURA_WARTORTLE}, N_VDS_MEDIO, N_PTS_MEDIO), massa(rand() % 51 + 50)
            {
                setTextura("assets/sprites/personagens/inimigo/wartortle.png", sf::IntRect({0, 0}, {(int)LARGURA_WARTORTLE, (int)ALTURA_WARTORTLE}));
            }

            Wartortle::~Wartortle()
            {

            }

            void Wartortle::salvarDataBuffer()
            {
                Inimigo::salvarDataBuffer();
                buffer << " " << massa;
            }

            void Wartortle::salvar()
            {
                buffer.str("");
                salvarDataBuffer();
                std::ofstream arquivo("save.dat", std::ios::app);
                arquivo << "WARTORTLE " << buffer.str() << std::endl;
            }

            void Wartortle::danificar(Jogador* p)
            {
                if (p->getInvencivel()) { return; }
 
                //knockback proporcional à massa
                float forcaH = massa * 3;
 
                for(int i = 0; i < nivel_maldade; i++){
                    p->operator--();
                }

                aplicarKnockback(p, forcaH);
                p->ativarInvencibilidade();
 
                std::cout << "Wartortle danificou " << (p->getEhJogador1() ? "Pikachu" : "Raichu") << "! (massa=" << massa << ", forcaH=" << forcaH << ") Vidas: " << p->getNumvidas() << std::endl;
            }

            void Wartortle::executar()
            {
                Inimigo::executar();
            }
        }
    }
}