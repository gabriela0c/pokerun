#include "Entidades/Obstaculos/Fogo.h"
 
namespace Pokerun{
 
    namespace Entidades{
 
        namespace Obstaculos{
 
            Fogo::Fogo():
            Obstaculo({TAM_FOGO_X, TAM_FOGO_Y}, true, false),
            intensidade(rand() % 3 + 1)
            {
                setTextura("assets/sprites/obstaculos/fogo.png", sf::IntRect({0, 0}, {LARGURA_FOGO, ALTURA_FOGO}));
            }
 
            Fogo::~Fogo()
            {
 
            }

            void Fogo::salvarDataBuffer()
            {
                Obstaculo::salvarDataBuffer();
                buffer << " " << intensidade;
            }

            void Fogo::salvar()
            {
                buffer.str("");
                salvarDataBuffer();
                std::ofstream arquivo("save.dat", std::ios::app);
                arquivo << "FOGO " << buffer.str() << std::endl;
            }
 
            void Fogo::executar()
            {
                aplicarGravidade();
                antiGravidade();
            }
 
            void Fogo::queimar(Personagens::Jogador* pJog)
            {
                //intensidade 1: 1 de dano + knockback
                //intensidade 2: 2 de dano + knockback
                //intensidade 3: 3 de dano + knockback
                for(int i = 1; i < intensidade; i++)
                    pJog->operator--();
                
                float sinal = calcularDirecao(pJog->getFig().getPosition(), pFigura->getPosition());
                pJog->receberKnockback(sinal * 200.0f);
                pJog->ativarInvencibilidade();
 
                std::cout << "Fogo queimou " << (pJog->getEhJogador1() ? "Pikachu" : "Raichu") << "! (intensidade =" << intensidade << ") Vidas: " << pJog->getNumvidas() << std::endl;
            }
 
            void Fogo::obstaculizar(Personagens::Jogador* pJog)
            {
                if (!pJog) { return; }
                if (!pJog->getInvencivel())
                {
                    queimar(pJog);
                }
            }
        }
    }
}
 