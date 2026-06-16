#include "Entidades/Obstaculos/Plataforma.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{            

            Plataforma::Plataforma():
            Obstaculo({TAM_PLAT_X, TAM_PLAT_Y}, false, true), dimensoes({(int)TAM_PLAT_X, (int)TAM_PLAT_Y})
            {
                setTextura("assets/sprites/obstaculos/plataforma.png", sf::IntRect({0, 0}, dimensoes));
            }

            Plataforma::Plataforma(sf::Vector2f pos,sf::Vector2f dim):
            Obstaculo(dim, false, true), dimensoes(dim)
            {
                pFigura->setFillColor(sf::Color::Blue);
                setTextura("assets/sprites/obstaculos/plataforma.png", sf::IntRect({0, 0}, dimensoes));
                pFigura->setPosition(pos);
                sincronizarPosicao();
                y_inicial = y;
            }

            Plataforma::~Plataforma()
            {

            }

            void Plataforma::executar()
            {
                aplicarGravidade();
                antiGravidade();
            }

            void Plataforma::salvarDataBuffer()
            {
                Obstaculo::salvarDataBuffer();
                buffer << " " << dimensoes.x << " " << dimensoes.y;
            }

            void Plataforma::salvar()
            {
                buffer.str("");               
                salvarDataBuffer();
                std::ofstream arquivo("save.dat", std::ios::app);
                arquivo << "PLATAFORMA " << buffer.str() << std::endl;
            }

            void Plataforma::obstaculizar(Personagens::Jogador* pJog)
            {
                if(danoso)
                    pJog->operator--();
            }
        }
    }
}