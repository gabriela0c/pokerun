#include "Poca.h"

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            Poca::Poca():
            Obstaculo({TAM_OBST_MEDIO_X, TAM_OBST_MEDIO_Y}, false, false), profundidade((float)(rand()%31) + 50)
            {
                setTextura("assets/sprites/obstaculos/poca.png", sf::IntRect({0, 0}, {LARGURA_OBST_MEDIO, ALTURA_OBST_MEDIO}));
            }

            Poca::~Poca()
            {

            }

            void Poca::salvarDataBuffer()
            {
                Obstaculo::salvarDataBuffer();
                buffer << " " << profundidade;
            }

            void Poca::salvar()
            {
                buffer.str("");
                salvarDataBuffer();
                std::ofstream arquivo("save.dat", std::ios::app);
                arquivo << "POCA " << buffer.str() << std::endl;

            }

            void Poca::executar()
            {
                aplicarGravidade();
                antiGravidade();
            }

            void Poca::obstaculizar(Personagens::Jogador* pJog)
            {
                if(pJog){   
                    float taxa = 1 - (profundidade/100); //para fazer a vel do jogador diminuir algo entre 50 e 80%
                    pJog->diminui_vel(taxa);
                }
            }
        }
    }
}