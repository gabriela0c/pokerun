#include "GerenciadorEvento.h"

namespace Pokerun{

    namespace Gerenciadores{

        GerenciadorEvento* GerenciadorEvento::pEvento = nullptr;

        GerenciadorEvento::GerenciadorEvento(): pGrafico(GerenciadorGrafico::getGerenciadorGrafico()), pJogador1(nullptr), pJogador2(nullptr)
        {

        }

        GerenciadorEvento::~GerenciadorEvento()
        {
            pGrafico = nullptr;
            pJogador1 = nullptr;
            pJogador2 = nullptr;
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

        const bool GerenciadorEvento::pausaPressionado()
        {
            while (const auto event = pGrafico->getWindow()->pollEvent()){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    return true;
                else 
                    return false;
            }
            return false;
        }

        const bool GerenciadorEvento::cimaPressionado()
        {
            while (const auto event = pGrafico->getWindow()->pollEvent()){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                    return true;
                else 
                    return false;
            }
            return false;
        }

        const bool GerenciadorEvento::baixoPressionado()
        {
            while (const auto event = pGrafico->getWindow()->pollEvent()){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                    return true;
                else 
                    return false;
            }
            return false;
        }

        const bool GerenciadorEvento::enterPressionado()
        {
            while (const auto event = pGrafico->getWindow()->pollEvent()){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                    return true;
                else 
                    return false;
            }
            return false;
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
                    pGrafico->getWindow()->close();
            }
    
            if (pJogador1) 
            {
                float vX = pJogador1->getVelX();
                sf::Vector2f tam = pJogador1->getFig().getSize();
                float modificador = pJogador1->getModVel();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                    pJogador1->getFig().move({-vX * modificador, 0.0f});
                    pJogador1->getFig().setTextureRect(sf::IntRect({(int)tam.x, 0}, {(int)-tam.x, (int)tam.y}));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                    pJogador1->getFig().move({vX * modificador, 0.0f});
                    pJogador1->getFig().setTextureRect(sf::IntRect({0, 0}, {(int)tam.x, (int)tam.y}));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                    pJogador1->pular();
                }
            }  
            
            if (pJogador2) 
            {
                float vX = pJogador2->getVelX();
                sf::Vector2f tam = pJogador2->getFig().getSize();
                float modificador = pJogador2->getModVel();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                    pJogador2->getFig().move({-vX * modificador, 0.0f});
                    pJogador2->getFig().setTextureRect(sf::IntRect({(int)tam.x, 0}, {(int)-tam.x, (int)tam.y}));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                    pJogador2->getFig().move({vX * modificador, 0.0f});
                    pJogador2->getFig().setTextureRect(sf::IntRect({0, 0}, {(int)tam.x, (int)tam.y}));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                    pJogador2->pular();
                }
            }       
        }
    }
}
