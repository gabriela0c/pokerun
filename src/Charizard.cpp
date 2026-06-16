#include "Charizard.h"
#include "Projetil.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Charizard::Charizard():
            Inimigo(NIVEL_MALD_CHEFAO, {LARGURA_CHARIZARD, ALTURA_CHARIZARD}, N_VDS_CHEFAO), raio_ataque((int)(rand() % 201 + 100)), cd_projetil(COOLDOWN_TIRO_INIM), 
            pReceptor(nullptr), lProjeteis()
            {
                lProjeteis.clear();
                setTextura("assets/sprites/personagens/inimigo/charizard.png", sf::IntRect({0, 0}, {(int)LARGURA_CHARIZARD, (int)ALTURA_CHARIZARD}));
            }

            Charizard::~Charizard()
            {
                for(int i = 0; i < (int)lProjeteis.size(); i++){
                    if(lProjeteis[i]){ 
                        lProjeteis[i]->setCharizard(nullptr); 
                    } 
                }
                lProjeteis.clear();
                pReceptor = nullptr;
            }

            void Charizard::salvarDataBuffer()
            {
                Inimigo::salvarDataBuffer();
                buffer << " " << raio_ataque;
            }

            void Charizard::salvar()
            {
                buffer.str("");
                salvarDataBuffer();
                std::ofstream arquivo("save.dat", std::ios::app);
                arquivo << "CHARIZARD " << buffer.str() << std::endl;
            }

            void Charizard::setReceptorProjeteis(ReceptorProjetil* pRec)
            {
                if(pRec){ pReceptor = pRec; }
            }

            void Charizard::adicionarProjetil(Projetil* pProj)
            {
                if(pProj){ lProjeteis.push_back(pProj);}
            }

            void Charizard::removerProjetil(Projetil* pProj)
            {
                if(!pProj){return;}

                for(int i = 0; i < (int)lProjeteis.size(); i++){
                    if(pProj == lProjeteis[i]){
                        lProjeteis.erase(lProjeteis.begin() + i);
                        pProj = nullptr;
                        return;
                    }
                }
            }

           void Charizard::danificar(Jogador* p)
            {
                if(!p || !pReceptor){ return; }

                cd_projetil.atualizar();//desativa quando a duracao passa
                if(cd_projetil.getAtivo()){ return; } //se o cd ativo nao dispara projetil

                sf::Vector2f posChar = pFigura->getPosition();
                sf::Vector2f posAlvo = p->getFig().getPosition();
                float dirX = calcularDirecao(posAlvo, posChar);

                float spawnX = posChar.x + (dirX > 0.0f ? pFigura->getSize().x : -LARGURA_PROJ);
                float spawnY = posChar.y + pFigura->getSize().y * 0.3f;

                Projetil* pProj = new Projetil(VEL_PROJETIL_X * dirX);
                pProj->getFig().setPosition(sf::Vector2f(spawnX, spawnY));
                pProj->setCharizard(this);
                adicionarProjetil(pProj);
                pReceptor->adicionarProjetil(pProj);
                cd_projetil.iniciar();
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
                Jogador* alvo = jogadorMaisProximo();
                if(alvo){ 
                    danificar(alvo); //so danifica se tiver um jogador no range dele
                }
            }
        }
    }
}