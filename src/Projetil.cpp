#include "Projetil.h"
#include "Charizard.h"

namespace Pokerun {
    namespace Entidades {

        Projetil::Projetil(float velX) : Entidade({LARGURA_PROJ, ALTURA_PROJ}, 0.0f), vel_x(velX), dano(DANO_PROJETIL), pCharizard(nullptr), voando(false)
        {
            setTextura("assets/sprites/outros/fogo-charizard.png",
            sf::IntRect({0, 0}, {TAMANHO_PROJ_X, TAMANHO_PROJ_Y}));
        }

        Projetil::~Projetil() 
        {
            if(pCharizard){ pCharizard->removerProjetil();}
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

        void Projetil::setVoando(const bool v)
        {
            voando = v;
        }

        bool Projetil::getVoando()const
        {
            return voando;
        }

        void Projetil::setCharizard(Personagens::Charizard* pChar)
        {
            pCharizard = pChar;
        }

        void Projetil::resetar()
        {
            if(!pCharizard){//se o charizard morreu, inativa o projetil, o que o remove da lista_ents, GC e o deleta
                setAtivo(false);
                return;
            }

            setVoando(false);
            
            sf::Vector2f posChar = pCharizard->getPosition();
            sf::Vector2f sizeChar = pCharizard->getSize();

            float dirX = pCharizard->getDirProjetil();

            float spawnX = posChar.x + (dirX > 0.0f ? sizeChar.x : -LARGURA_PROJ);
            float spawnY = posChar.y + sizeChar.y * 0.3f;

            pFigura->setPosition({spawnX, spawnY});
            vel_x = dirX * VEL_PROJETIL_X;
        }

        void Projetil::executar()
        {
            if(!voando){
                if(pCharizard){ 
                    pFigura->setPosition(pCharizard->getPosition()); 
                }
                return;
            }
            
            aplicarGravidade();
            pFigura->move({vel_x * dt, 0.0f});

            sf::Vector2f pos = pFigura->getPosition();
            if(pos.x < 0.0f || pos.x > WIN_SIZE_X || pos.y < 0.0f || pos.y > WIN_SIZE_Y)//se colide com os limites da tela
                resetar();
        }

    }
}