#include "Charizard.h"
#include "Projetil.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Charizard::Charizard():
            Inimigo(NIVEL_MALD_CHEFAO, {LARGURA_CHARIZARD, ALTURA_CHARIZARD}, N_VDS_CHEFAO), raio_ataque((int)(rand() % 201 + 100)), pListaProj(nullptr), cd_projetil(COOLDOWN_TIRO_INIM)
            {
                setTextura("assets/sprites/personagens/inimigo/charizard.png", sf::IntRect({0, 0}, {(int)LARGURA_CHARIZARD, (int)ALTURA_CHARIZARD}));
            }

            Charizard::~Charizard()
            {
                pListaProj = nullptr;
            }

            void Charizard::setListaProjeteis(std::vector<Projetil*>* pLista)
            {
                if(pLista){ pListaProj = pLista; }
            }

           void Charizard::danificar(Jogador* p)
            {
                //só empurra para evitar que fiquem grudados
                aplicarKnockback(p, 50.0f);
            }

            float Charizard::distancia(sf::Vector2f a, sf::Vector2f b) const
            {
                float dx = a.x - b.x;
                float dy = a.y - b.y;
                return std::sqrt(dx * dx + dy * dy);
            }
 
            Jogador* Charizard::jogadorMaisProximo()
            {
                Jogador* alvo = nullptr;
                float menorDist = (float)raio_ataque;
 
                if(pJogador1 && pJogador1->getAtivo())
                {
                    float d = distancia(pFigura->getPosition(), pJogador1->getFig().getPosition());
                    if(d < menorDist)
                    {
                        menorDist = d;
                        alvo = pJogador1;
                    }
                }
 
                if(pJogador2 && pJogador2->getAtivo())
                {
                    float d = distancia(pFigura->getPosition(), pJogador2->getFig().getPosition());
                    if(d < menorDist)
                    {
                        alvo = pJogador2;
                    }
                }
 
                return alvo;
            }

            void Charizard::executar()
            {
                Inimigo::executar();
 
                if(!pListaProj){ return; }
 
                //cooldown entre tiros
                cd_projetil.atualizar(); //desativa quando a duracao passa
                if(cd_projetil.getAtivo()){return;} //se cd ativo retorna
 
                Jogador* alvo = jogadorMaisProximo();
                if(!alvo){ return; }
 
                sf::Vector2f posChar = pFigura->getPosition();
                sf::Vector2f posAlvo = alvo->getFig().getPosition();
                float dirX = calcularDirecao(posAlvo, posChar);
 
                float spawnX = posChar.x + (dirX > 0.0f ? pFigura->getSize().x : -LARGURA_PROJ);
                float spawnY = posChar.y + pFigura->getSize().y * 0.3f;
 
                Projetil* pProj = new Projetil(VEL_PROJETIL_X * dirX);
                pProj->getFig().setPosition(sf::Vector2f(spawnX, spawnY));
 
                pListaProj->push_back(pProj);
                cd_projetil.iniciar();
            }
        }
    }
}