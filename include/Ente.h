#pragma once
#include <iostream>
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

        void setTextura(const std::string caminho, const sf::IntRect bounds);

        sf::RectangleShape& getFig();
    };
}