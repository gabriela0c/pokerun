#include "Entidades/Projetil.h"
#include "Entidades/Personagens/Charizard.h"

namespace Pokerun {
    namespace Entidades {

        Projetil::Projetil(float velX) : Entidade({LARGURA_PROJ, ALTURA_PROJ}, 0.0f), vel_x(velX), dano(DANO_PROJETIL), pCharizard(nullptr)
        {
            setTextura("assets/sprites/outros/fogo-charizard.png",
                sf::IntRect({0, 0}, {TAMANHO_PROJ_X, TAMANHO_PROJ_Y}));
        }

        Projetil::~Projetil() 
        {
            if(pCharizard){ pCharizard->removerProjetil(this);}
            pCharizard = nullptr; 
        }

        void Projetil::salvarDataBuffer()
        {
            Entidade::salvarDataBuffer();
            buffer << " " << vel_x;
        }

        void Projetil::salvar()
        {
            buffer.str("");
            salvarDataBuffer();
            std::ofstream arquivo("save.dat", std::ios::app);
            arquivo << "PROJETIL " << buffer.str() << std::endl;
        }

        const int Projetil::getDano()const
        {
            return dano;
        }

        void Projetil::setCharizard(Personagens::Charizard* pChar)
        {
            pCharizard = pChar;
        }

        void Projetil::executar()
        {
            aplicarGravidade();
            pFigura->move({vel_x * dt, 0.0f});

            sf::Vector2f pos = pFigura->getPosition();
            if(pos.x < 0.0f || pos.x > WIN_SIZE_X || pos.y < 0.0f || pos.y > WIN_SIZE_Y)//inativa se ele bate em um dos cantos
                setAtivo(false);
        }

    }
}