#include "ObstMedio.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

            ObstMedio::ObstMedio():
            Obstaculo({TAM_OBST_MEDIO_X, TAM_OBST_MEDIO_Y}, false, ID::OBST_MEDIO)
            {
                if(!textura.loadFromFile("assets/sprites/obstaculos/obstmedio.png")){
                //sprite gerada por IA
                    std::cout << "ERRO: Nao foi possivel carregar a textura do obstáculo!" << std::endl;
                }

                pFigura->setTexture(&textura);
                pFigura->setFillColor(sf::Color::White); 
                pFigura->setTextureRect(sf::IntRect({0, 0}, {(int)LARGURA_OBST_MEDIO, (int)ALTURA_OBST_MEDIO}));
            }

            ObstMedio::~ObstMedio()
            {

            }

            void ObstMedio::executar()
            {

            }

            void ObstMedio::obstaculizar(Personagens::Jogador* pJog)
            {
                if(pJog){
                    pJog->colisao_posso_pular(this);
                }

            }
        }
    }
}