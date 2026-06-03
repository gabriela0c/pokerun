#include "Chao.h"

namespace Pokerun{

    namespace Entidades{

        Chao::Chao():
        Entidade({WIN_SIZE_X, TAM_CHAO_Y}), posY(WIN_SIZE_Y - TAM_CHAO_Y)
        {
            pFigura->setPosition({0.0f, posY});
            setTextura("assets/sprites/obstaculos/chao.png", sf::IntRect({0, 0}, {LARGURA_CHAO, ALTURA_CHAO}));
        }

        Chao::~Chao()
        {

        }

        void Chao::executar()
        {

        }
    }
}