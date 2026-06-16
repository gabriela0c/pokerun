#pragma once
#include "Gerenciadores/GerenciadorGrafico.h"

namespace Pokerun {

    class Ente {
    protected:
        static Gerenciadores::GerenciadorGrafico* pGG;
        sf::RectangleShape* pFigura;
        sf::Texture textura;
        const int id;
        static int cont_id;
        
    public:
        Ente(const sf::Vector2f tam = {0.0f, 0.0f});
        virtual ~Ente();

        virtual void executar() = 0;
        virtual void desenhar();

        const int getID()const;

        static void setGG(Gerenciadores::GerenciadorGrafico* pG);

        void setTextura(std::string caminho, sf::IntRect bounds);

        sf::RectangleShape& getFig();
        const sf::RectangleShape& getFig()const; //sobrecarga de metodo necessaria pois getFig necessita referencia const 
    };
}