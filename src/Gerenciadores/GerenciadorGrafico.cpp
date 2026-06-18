#include "Gerenciadores/GerenciadorGrafico.h"
#include "Ente.h"
#include <stdexcept>

namespace Pokerun{

    namespace Gerenciadores{

        GerenciadorGrafico::GerenciadorGrafico():
        window (new sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "Pokerun"))
        {
            window->setFramerateLimit(60); //para evitar travamentos
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

        void GerenciadorGrafico::desenhaElementos(Ente* pE)
        {
            if(window){
                window->draw(pE->getFig());
            }
        }

        void GerenciadorGrafico::desenhaElementos(sf::Text& texto)
        {
            if(window){
                window->draw(texto);
            }
        }

        void GerenciadorGrafico::desenhaElementos(const sf::Drawable& desenho)
        {
            if(window){
                window->draw(desenho);
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
            //try-catch
            try {
                if (!window) {
                    // mostra a exceção se a janela não existir
                    throw std::runtime_error("Erro: O ponteiro da janela grafica eh nulo!");
                }
                return (window->isOpen());
            }
            catch (const std::exception& e) {
                // pega a exceção e avisa no terminal p não crashar o jogo do nada
                std::cerr << "Excecao: " << e.what() << std::endl;
                return false;
            }
        }
    }
} 