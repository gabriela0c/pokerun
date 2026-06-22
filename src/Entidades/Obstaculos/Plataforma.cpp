#include "Entidades/Obstaculos/Plataforma.h"

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{            

            Plataforma::Plataforma():
            Obstaculo({TAM_PLAT_X, TAM_PLAT_Y}, false, true), dimensoes({(int)TAM_PLAT_X, (int)TAM_PLAT_Y}), 
            pode_curar((rand() % 100) < 30), cura_consumida(false)
            {
                if(pode_curar == false)
                    setTextura("assets/sprites/obstaculos/plataforma.png", sf::IntRect({0, 0}, dimensoes));
                else
                    setTextura("assets/sprites/obstaculos/plataforma-cura.png", sf::IntRect({0, 0}, dimensoes));
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
                buffer << " " << pode_curar << " " << cura_consumida << " " << dimensoes.x << " " << dimensoes.y;
            }

            void Plataforma::carregarDataBuffer(std::istream& is)
            {
                Obstaculo::carregarDataBuffer(is);
                is >> pode_curar >> cura_consumida >> dimensoes.x >> dimensoes.y;
                pFigura->setSize({(float)dimensoes.x, (float)dimensoes.y});//restaura o tamanho (importante p/ as paredes laterais)
            }

            void Plataforma::salvar()
            {
                buffer << "PLATAFORMA "; 
                salvarDataBuffer(); 
                buffer << std::endl;
            }

            void Plataforma::obstaculizar(Personagens::Jogador* pJog)
            {
                if(danoso)
                    pJog->receberDano(1);

                if(pode_curar && !cura_consumida && pJog != nullptr && pJog->getNumvidas() < N_VDS_JOG)
                {
                    cura_consumida = true;
                    
                    pJog->curarVida();

                    sf::Vector2f tam = pFigura->getSize();
                    setTextura("assets/sprites/obstaculos/plataforma.png", sf::IntRect({0, 0}, {(int)tam.x, (int)tam.y}));
                }
            }
        }
    }
}