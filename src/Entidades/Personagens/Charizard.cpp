#include "Entidades/Personagens/Charizard.h"
#include "Entidades/Projetil.h"
 
namespace Pokerun{
 
    namespace Entidades{
 
        namespace Personagens{
 
            Charizard::Charizard():
            Inimigo(NIVEL_MALD_CHEFAO, {LARGURA_CHARIZARD, ALTURA_CHARIZARD}, N_VDS_CHEFAO, N_PTS_CHEFAO), 
            raio_ataque((int)(rand() % 201 + 100)), 
            cd_projetil(COOLDOWN_TIRO_INIM), pProjetil(nullptr)
            {
                setTextura("assets/sprites/personagens/inimigo/charizard.png", sf::IntRect({0, 0}, {(int)LARGURA_CHARIZARD, (int)ALTURA_CHARIZARD}));
            }
 
            Charizard::~Charizard()
            {
                if(pProjetil){
                    pProjetil->setCharizard(nullptr);  
                    pProjetil->setAtivo(false);         
                }
                pProjetil = nullptr;
            }
 
            void Charizard::salvarDataBuffer()
            {
                Inimigo::salvarDataBuffer();
                buffer << " " << raio_ataque;
            }

            void Charizard::carregarDataBuffer(std::istream& is)
            {
                Inimigo::carregarDataBuffer(is);
                is >> raio_ataque;
            }

            void Charizard::salvar()
            {
                buffer << "CHARIZARD "; 
                salvarDataBuffer(); 
                buffer << std::endl;
            }
 
            void Charizard::adicionarProjetil(Projetil* pProj)
            {
                if(pProj){
                    pProjetil = pProj;
                    // aplica o nivel de maldade como dano do projétil
                    pProjetil->setDano(nivel_maldade);
                }
            }
 
            void Charizard::removerProjetil()
            {
                pProjetil = nullptr;
            }
 
            void Charizard::danificar(Jogador* p)
            {
                if(!p || !pProjetil){ return; }
 
                cd_projetil.atualizar();
                if(cd_projetil.getAtivo()){ return; }
                if(pProjetil->getVoando()){ return; }
 
                if(pProjetil->disparar()){
                    cd_projetil.iniciar();
                }
            }
 
            sf::Vector2f Charizard::getDirProjetil()const
            {
                sf::Vector2f posChar = getPosition();
                Jogador* jog = jogadorMaisProximo();
                if(!jog){ return {0.0f, 0.0f}; }
                sf::Vector2f posAlvo = jog->getPosition();
                return calcularDirecao(posAlvo, posChar);
            }
 
            float Charizard::distancia(sf::Vector2f a, sf::Vector2f b) const
            {
                float dx = a.x - b.x;
                float dy = a.y - b.y;
                return std::sqrt(dx * dx + dy * dy);
            }
 
            Jogador* Charizard::jogadorMaisProximo()const
            {
                Jogador* alvo = nullptr;
                float menorDist = (float)raio_ataque;
 
                sf::Vector2f centroChar = getPosition() + getSize() / 2.0f;
 
                if(pJogador1 && pJogador1->getAtivo())
                {
                    float d = distancia(centroChar, pJogador1->getPosition() + pJogador1->getSize() / 2.0f);
                    if(d < menorDist)
                    {
                        menorDist = d;
                        alvo = pJogador1;
                    }
                }
 
                if(pJogador2 && pJogador2->getAtivo())
                {
                    float d = distancia(centroChar, pJogador2->getPosition() + pJogador2->getSize() / 2.0f);
                    if(d < menorDist)
                    {
                        menorDist = d;
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
                    danificar(alvo);
                }
            }
        }
    }
}