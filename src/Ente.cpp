#include "Ente.h"

namespace Pokerun {

    Gerenciadores::GerenciadorGrafico* Ente::pGG = Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico();
    int Ente::cont_id(0);

    Ente::Ente(const sf::Vector2f tam): 
    pFigura(new sf::RectangleShape(tam)), textura(), id(cont_id++)
    {
  
    }

    Ente::~Ente() 
    {
        if(pFigura){
            delete pFigura;
            pFigura = nullptr;
        }
    }

    const int Ente::getID()const
    {
        return id;
    }

    sf::RectangleShape& Ente::getFig()
    {
        return *pFigura;
    }

    const sf::RectangleShape& Ente::getFig()const
    {
        return *pFigura;
    }

    void Ente::setTextura(const std::string caminho, const sf::IntRect bounds)
    {
        if(!textura.loadFromFile(caminho)){ 
            std::cout << "Nao foi possivel carregar a textura do jogador" << std::endl;
        }
                
        pFigura->setTexture(&textura);
        pFigura->setFillColor(sf::Color::White); 
        pFigura->setTextureRect(bounds);
        }
    
    void Ente::desenhar()
    {
        if (pGG){
            pGG->desenhaElementos(this);
        }
    }
}
