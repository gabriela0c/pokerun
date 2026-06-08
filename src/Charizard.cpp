#include "Charizard.h"
//#include "Projetil.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Charizard::Charizard():
            Inimigo(NIVEL_MALD_CHEFAO, {LARGURA_CHARIZARD, ALTURA_CHARIZARD}, N_VDS_CHEFAO), raio_ataque((int)(rand() % 21 + 30)), tempoCooldownTiro(0.0f)
            {
                setTextura("assets/sprites/personagens/inimigo/charizard.png", sf::IntRect({0, 0}, {(int)LARGURA_CHARIZARD, (int)ALTURA_CHARIZARD}));
            }

            Charizard::~Charizard()
            {
            }

             void Charizard::danificar(Jogador* p)
            {
                if (p->getInvencivel()) { return; }
 
                
                //knockback proporcional à massa
                float forcaH = raio_ataque * 2.0f;
 
                for(int i = 0; i < nivel_maldade; i++){
                    p->operator--();
                }

                aplicarKnockback(p, forcaH);
                p->ativarInvencibilidade();
 
                std::cout << "Charizard danificou " << (p->getEhJogador1() ? "Pikachu" : "Raichu") << "! raio_ataque=" << raio_ataque << ", Vidas: " << p->getNumvidas() << std::endl;
            }

            /*void Charizard::dispararProjetil(float direcao)
            {
                if(!pFase){ return; }

                sf::Vector2f pos = pFigura->getPosition();
                pos.y += pFigura->getSize().y / 2.0f;
                if(direcao > 0.0f)
                    pos.x += pFigura->getSize().x;

                Entidades::Projetil* pProj = new Entidades::Projetil(
                    sf::Vector2f(LARGURA_PROJ, ALTURA_PROJ),
                    VEL_PROJETIL_X * direcao,
                    NIVEL_MALD_CHEFAO, // dano referente ao nivel de maldade
                    false
                );
                pProj->getFig().setPosition(pos);
                pProj->setTextura("assets/sprites/outros/fogo.png",
                    sf::IntRect({0, 0}, {LARGURA_PROJ, ALTURA_PROJ}));

                pFase->adicionarProjetil(pProj);
            }*/

            void Charizard::executar()
            {
                Inimigo::executar();
            }
        }
    }
}