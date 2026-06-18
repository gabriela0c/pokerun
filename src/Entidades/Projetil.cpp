#include "Entidades/Projetil.h"
#include "Entidades/Personagens/Charizard.h"
 
namespace Pokerun {
    namespace Entidades {
 
        Projetil::Projetil(float velX, int danoProjt)
        : Entidade({LARGURA_PROJ, ALTURA_PROJ}, 0.0f), vel_x(velX), dano(danoProjt), pCharizard(nullptr), voando(false)
        {
            setTextura("assets/sprites/outros/fogo-charizard.png",
            sf::IntRect({0, 0}, {TAMANHO_PROJ_X, TAMANHO_PROJ_Y}));
        }
 
        Projetil::~Projetil() 
        {
            if(pCharizard){ pCharizard->removerProjetil(); }
            pCharizard = nullptr; 
        }
 
        void Projetil::salvarDataBuffer()
        {
            Entidade::salvarDataBuffer();
            buffer << " " << vel_x << " " << voando << " " << dano;
        }
 
        void Projetil::salvar()
        {
            buffer << "PROJETIL "; 
            salvarDataBuffer(); 
            buffer << std::endl;
        }
 
        void Projetil::setDano(int d)
        {
            dano = d;
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
 
        void Projetil::recarregar(sf::Vector2f dir)
        {
            sf::Vector2f posChar  = pCharizard->getPosition();
            sf::Vector2f sizeChar = pCharizard->getSize();
 
            float spawnX = posChar.x + (dir.x > 0.0f ? sizeChar.x : -LARGURA_PROJ);
            float spawnY = posChar.y + sizeChar.y * 0.3f;
 
            pFigura->setPosition({spawnX, spawnY});
            sincronizarPosicao();
            vel_x = dir.x * VEL_PROJETIL_X;
            if(dir.y < 0){
                vel_y = dir.y * VEL_PROJETIL_Y;
            }
        }
 
        void Projetil::guardar()
        {
            if(!pCharizard){
                setVoando(false);
                setAtivo(false);
                return;
            }
 
            setVoando(false);
            recarregar(pCharizard->getDirProjetil());
        }
 
        bool Projetil::disparar()
        {
            if(!pCharizard){
                setVoando(false);
                setAtivo(false);
                return false;
            }
 
            sf::Vector2f dir = pCharizard->getDirProjetil();
            if(dir.x == 0.0f && dir.y == 0.0f){ return false; }
 
            recarregar(dir);
            setVoando(true);
            return true;
        }
 
        void Projetil::desenhar()
        {
            if(getVoando()){
                Ente::desenhar();
            }
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
            if(pos.x < 0.0f || pos.x > WIN_SIZE_X || pos.y < 0.0f || pos.y > WIN_SIZE_Y - TAM_CHAO_Y)
                guardar();
        }
    }
}