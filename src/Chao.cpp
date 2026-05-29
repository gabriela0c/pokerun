#include "Chao.h"

namespace Pokerun {

    namespace Entidades {

        namespace Obstaculos {

            Chao::Chao(const sf::Vector2f pos, const sf::Vector2f tam) : 
            Obstaculo({TAM_CHAO_X, TAM_CHAO_Y}, false, ID::CHAO)
            {
                if(!texturaChao.loadFromFile("assets/sprites/obstaculos/chao.png")){
                //sprite gerada por IA
                    std::cout << "ERRO: Nao foi possivel carregar a textura da plataforma!" << std::endl;
                }

                pFigura->setTexture(&texturaChao);
                pFigura->setFillColor(sf::Color::White); 
                pFigura->setTextureRect(sf::IntRect({0, 0}, {(int)LARGURA_CHAO, (int)ALTURA_CHAO}));

                pFigura->setPosition(pos);
            }

            Chao::~Chao() {
            }

            void Chao::executar() 
            {
            }

            void Chao::obstaculizar(Personagens::Jogador* pJog)
            {
                if(pJog)
                    pJog->colisao_posso_pular(this);
            }
        }
    }
}