#include "GerenciadorGrafico.h"
namespace Pokerun{

    namespace Gerenciadores{

        GerenciadorGrafico::GerenciadorGrafico():
        window (new sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "Pokerun"))
        {

        }

        GerenciadorGrafico* Pokerun::Gerenciadores::GerenciadorGrafico::pGrafico(nullptr);

        GerenciadorGrafico::~GerenciadorGrafico()
        {
            if(window){
                delete window;
                window = nullptr;
            }
        }

        void GerenciadorGrafico::destruir()
        {
            if(pGrafico){
                delete pGrafico;
                pGrafico = nullptr;
            }
        }

        GerenciadorGrafico* GerenciadorGrafico::getGerenciadorGrafico()
        {
            if(!pGrafico){
                pGrafico = new GerenciadorGrafico();
            }
                
            return pGrafico;
        }

        sf::RenderWindow* GerenciadorGrafico::getWindow()
        {
            return window;
        }

        void GerenciadorGrafico::limpaJanela()
        {
            if(window){
                window->clear();
            }
        }

        void GerenciadorGrafico::desenhaElementos(sf::RectangleShape& corpo)
        {
            if(window){
                window->draw(corpo);
            }
        }

        void GerenciadorGrafico::mostraElementos()
        {
            if(window){
                window->display();
            }
        }

        void GerenciadorGrafico::fecharJanela()
        {
            if(window){
                window->close();
            }
        }

        const bool GerenciadorGrafico::verificaJanelaAberta()
        {
            if(window){
                return (window->isOpen());
            }
            std::cout<<"janela nula"<<std::endl;
            return false;
        }
    }
} 