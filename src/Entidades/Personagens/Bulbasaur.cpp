#include "Entidades/Personagens/Bulbasaur.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Bulbasaur::Bulbasaur() :
            Inimigo(NIVEL_MALD_FACIL, {LARGURA_BULBASAUR, ALTURA_BULBASAUR}, N_VDS_FACIL, N_PTS_FACIL),
            chance_veneno((rand()%10) + 1), cd_chicote(2.5f)
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

            void Bulbasaur::carregarDataBuffer(std::istream& is)
            {
                Inimigo::carregarDataBuffer(is);
                is >> chance_veneno;
            }

            void Bulbasaur::salvar()
            {
                buffer << "BULBASAUR "; 
                salvarDataBuffer(); 
                buffer << std::endl;
            }

            void Bulbasaur::danificar(Jogador* p)
            {
                if (p->getInvencivel()) { return; }
 
                for(int i = 0; i < nivel_maldade; i++){
                    p->operator--();
                }
 
                if (((rand() % 10) + 1)  < chance_veneno)
                {
                    p->envenenar();
                }
 
                p->ativarInvencibilidade();
                std::cout << "Bulbasaur danificou " << (p->getEhJogador1() ? "Pikachu" : "Raichu") << "! Vidas: " << p->getNumvidas() << std::endl;
            }

            void Bulbasaur::executar()
            {
                Inimigo::executar();
                
                cd_chicote.atualizar();

                if (!cd_chicote.getAtivo()) {
                    if (chicoteVinha(pJogador1) || chicoteVinha(pJogador2))// tenta puxar o jogador mais próximo
                        cd_chicote.iniciar();
                }

            }

            bool Bulbasaur::chicoteVinha(Jogador* pJog)
            {
                if (!pJog || !pJog->getAtivo()){ 
                    return false; 
                }

                sf::Vector2f bCenter = getPosition() + getSize() / 2.0f;
                sf::Vector2f jCenter = pJog->getPosition() + pJog->getSize() / 2.0f;
                float dx = bCenter.x - jCenter.x;
                float dy = bCenter.y - jCenter.y;
                if (dx*dx + dy*dy > RAIO_CHICOTE * RAIO_CHICOTE) { 
                    return false; 
                }

                // sinal de posbulbasaur - posjogador, puxa o jogador p/o bulbasaur
                sf::Vector2f sinal = calcularDirecao(getPosition(), pJog->getPosition());
                pJog->receberKnockback(sinal.x * FORCA_CHICOTE);
                return true;
            }

        }
    }
}