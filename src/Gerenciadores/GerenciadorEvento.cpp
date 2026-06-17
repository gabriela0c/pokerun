#include "Gerenciadores/GerenciadorEvento.h"

namespace Pokerun{

    namespace Gerenciadores{

        GerenciadorEvento* GerenciadorEvento::pEvento = nullptr;

        GerenciadorEvento::GerenciadorEvento(): pGrafico(GerenciadorGrafico::getGerenciadorGrafico()), pJogador1(nullptr), pJogador2(nullptr),
        flagPausa(false), flagCima(false), flagBaixo(false), flagEnter(false), texto_digitado("")
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
            return flagPausa;
        }

        const bool GerenciadorEvento::cimaPressionado()
        {
            return flagCima;
        }

        const bool GerenciadorEvento::baixoPressionado()
        {
            return flagBaixo;
        }

        const bool GerenciadorEvento::enterPressionado()
        {
            return flagEnter;
        }

        const std::string GerenciadorEvento::getTextoDigitado()const
        {
            return texto_digitado;
        }

        void GerenciadorEvento::setJogador(Entidades::Personagens::Jogador* pJog)
        {
            if(pJog){
                if(pJog->getEhJogador1()){pJogador1 = pJog;}
                else{pJogador2 = pJog;}
            }
        }

        void GerenciadorEvento::resetFlags()
        {
            flagCima  = false;
            flagBaixo = false;
            flagEnter = false;
            flagPausa = false;
        }

        const bool GerenciadorEvento::QPressionado()
        {
            return flagQ;
        }

        void GerenciadorEvento::pollEvent()
        {
            while (const auto event = pGrafico->getWindow()->pollEvent()) {
                if (event->getIf<sf::Event::Closed>()) 
                    pGrafico->getWindow()->close();
                else if(const auto* key = event->getIf<sf::Event::KeyPressed>()){
                    if(key->code == sf::Keyboard::Key::Up){flagCima = true;}
                    if(key->code == sf::Keyboard::Key::Down){flagBaixo = true;}
                    if(key->code == sf::Keyboard::Key::Enter){flagEnter = true;}
                    if(key->code == sf::Keyboard::Key::Escape){flagPausa = true;}
                    if(key->code == sf::Keyboard::Key::Q){flagQ = true;}//comentar
                }
                else if(const auto* text = event->getIf<sf::Event::TextEntered>()){
                    if(text->unicode < 128){ //só ASCII                 
                    texto_digitado += (char)(text->unicode);
                    }
                }
            }
        }

        void GerenciadorEvento::evento_movimento(Entidades::Personagens::Jogador* pJog)
        {
            if (pJog) 
            {
                float vX = pJog->getVelX();
                sf::Vector2f tam = pJog->getSize();
                float modificador = pJog->getModVel();

                if(pJog->getEhJogador1()){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                        pJog->getFig().move({-vX * modificador, 0.0f});
                        pJog->getFig().setTextureRect(sf::IntRect({(int)tam.x, 0}, {(int)-tam.x, (int)tam.y}));
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                        pJog->getFig().move({vX * modificador, 0.0f});
                        pJog->getFig().setTextureRect(sf::IntRect({0, 0}, {(int)tam.x, (int)tam.y}));
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                        pJog->pular();
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)){
                        pJog->setAtacando(true);
                    }
                }
                else{
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

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)){
                        pJogador2->setAtacando(true);
                    }
                }
            } 
        }

        void GerenciadorEvento::removeJogador2(){
            pJogador2 = nullptr;
        }

        void GerenciadorEvento::executar() 
        {
            resetFlags();
            texto_digitado.clear(); 
            pollEvent();

            evento_movimento(pJogador1);
            evento_movimento(pJogador2);  
        }
    }
}
