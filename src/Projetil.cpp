#include "Projetil.h"

namespace Pokerun {
    namespace Entidades {

        Projetil::Projetil(float velX) : Entidade({LARGURA_PROJ, ALTURA_PROJ}, 0.0f), vel_x(velX), dano(DANO_PROJETIL)
        {
            setTextura("assets/sprites/outros/fogo-charizard.png",
                sf::IntRect({0, 0}, {TAMANHO_PROJ_X, TAMANHO_PROJ_Y}));
        }

        Projetil::~Projetil() 
        {
        }

        const int Projetil::getDano()const
        {
            return dano;
        }

        void Projetil::executar()
        {
            aplicarGravidade();
            pFigura->move({vel_x * dt, 0.0f});
        }

    }
}