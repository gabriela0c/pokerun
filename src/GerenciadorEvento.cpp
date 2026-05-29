#include "GerenciadorEvento.h"

namespace Pokerun{

    namespace Gerenciadores{

        GerenciadorEvento* GerenciadorEvento::pEvento = nullptr;

        GerenciadorEvento::GerenciadorEvento(): pGrafico(GerenciadorGrafico::getGerenciadorGrafico()), pJogador1(nullptr), pJogador2(nullptr)
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

        void GerenciadorEvento::setJogador1(Pokerun::Entidades::Personagens::Jogador* jog1) 
        {
            if(jog1){
                pJogador1 = jog1;
            }
        }

        void GerenciadorEvento::setJogador2(Pokerun::Entidades::Personagens::Jogador* jog2) 
        {
            if(jog2){
                pJogador2 = jog2;
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
    
            if (pJogador1) 
            {
                sf::Vector2f v = pJogador1->getVel();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                    pJogador1->getFig().move({-v.x, 0.0f});
                    pJogador1->getFig().setTextureRect(sf::IntRect({LARGURA_PIKACHU, 0}, {-LARGURA_PIKACHU, ALTURA_PIKACHU}));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                    pJogador1->getFig().move({v.x, 0.0f});
                    pJogador1->getFig().setTextureRect(sf::IntRect({0, 0}, {LARGURA_PIKACHU, ALTURA_PIKACHU}));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                    pJogador1->pular();
                }
            }  
            
            if (pJogador2) 
            {
                sf::Vector2f v = pJogador2->getVel();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                    pJogador2->getFig().move({-v.x, 0.0f});
                    pJogador2->getFig().setTextureRect(sf::IntRect({LARGURA_RAICHU, 0}, {-LARGURA_RAICHU, ALTURA_RAICHU}));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                    pJogador2->getFig().move({v.x, 0.0f});
                    pJogador2->getFig().setTextureRect(sf::IntRect({0, 0}, {LARGURA_RAICHU, ALTURA_RAICHU}));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                    pJogador2->pular();
                }
            }       
        }
    }
}
