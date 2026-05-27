#include "GerenciadorEvento.h"

namespace Pokerun{

    namespace Gerenciadores{

        GerenciadorEvento* GerenciadorEvento::pEvento = nullptr;

        GerenciadorEvento::GerenciadorEvento(): pGrafico(GerenciadorGrafico::getGerenciadorGrafico()), pJogador(nullptr)
        {

        }

        GerenciadorEvento::~GerenciadorEvento()
        {

        }

        GerenciadorEvento* GerenciadorEvento::getGerenciadorEvento() 
        {
            if(pEvento == nullptr) 
            {
                pEvento = new GerenciadorEvento();
            }
            return pEvento;
        }

        void GerenciadorEvento::destruir() 
        {
            if(pEvento) 
            {
                delete pEvento;
                pEvento = nullptr;
            }
        }

        void GerenciadorEvento::setJogador(Pokerun::Entidades::Personagens::Jogador* jog) 
        {
            if(jog){
                pJogador = jog;
            }
        }

        void GerenciadorEvento::executar() 
        {
            while (const auto event = pGrafico->getWindow()->pollEvent()) {
                if (event->getIf<sf::Event::Closed>()) 
                {
                    pGrafico->getWindow()->close();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                    pGrafico->getWindow()->close();
                }
            }
    
            if (pJogador) 
            {
                sf::Vector2f v = pJogador->getVel();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                    pJogador->getFig().move({-v.x, 0.0f});
                    pJogador->getFig().setTextureRect(sf::IntRect({LARGURA_PIKACHU, 0}, {-LARGURA_PIKACHU, ALTURA_PIKACHU}));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                    pJogador->getFig().move({v.x, 0.0f});
                    pJogador->getFig().setTextureRect(sf::IntRect({0, 0}, {LARGURA_PIKACHU, ALTURA_PIKACHU}));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    pJogador->pular();
                }
            }       
        }
    }
}
