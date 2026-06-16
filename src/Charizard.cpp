#include "Charizard.h"
#include "Projetil.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Charizard::Charizard():
            Inimigo(NIVEL_MALD_CHEFAO, {LARGURA_CHARIZARD, ALTURA_CHARIZARD}, N_VDS_CHEFAO), raio_ataque((int)(rand() % 201 + 100)), 
            cd_projetil(COOLDOWN_TIRO_INIM), pProjetil(nullptr)
            {
                setTextura("assets/sprites/personagens/inimigo/charizard.png", sf::IntRect({0, 0}, {(int)LARGURA_CHARIZARD, (int)ALTURA_CHARIZARD}));
            }

            Charizard::~Charizard()
            {
                pProjetil = nullptr;
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

            void Charizard::adicionarProjetil(Projetil* pProj)
            {
                if(pProj){ pProjetil = pProj;}
            }

            void Charizard::removerProjetil()
            {
                pProjetil = nullptr;
            }

           void Charizard::danificar(Jogador* p)
            {
                if(!p){ return; }

                cd_projetil.atualizar();//desativa quando a duracao passa
                if(cd_projetil.getAtivo()){ return; } //se o cd ativo nao dispara projetil

                

                cd_projetil.iniciar();
            }

            float Charizard::getDirProjetil()
            {
                sf::Vector2f posChar = pFigura->getPosition();
                Jogador* jog = jogadorMaisProximo();
                if(!jog){return 0.0f;} // sem alvo, sem direção projetil nao eh lancado
                sf::Vector2f posAlvo = jog->getFig().getPosition();
                return calcularDirecao(posAlvo, posChar);
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