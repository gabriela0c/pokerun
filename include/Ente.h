#pragma once
#include "GerenciadorGrafico.h"
#include "ID.h"

namespace Pokerun {

    class Ente {
    protected:
        bool ativo;    
        static Gerenciadores::GerenciadorGrafico* pGG;
        const ID id;
        sf::RectangleShape* pFigura;
        
    public:
        Ente(const sf::Vector2f tam = {0.0f, 0.0f}, const ID i = ID::INDEFINIDO);
        virtual ~Ente();

        virtual void executar() = 0;
        virtual void desenhar() = 0;

        static void setGG(Gerenciadores::GerenciadorGrafico* pG);

        ID getID()const;

        sf::RectangleShape& getFig();
        const sf::RectangleShape& getFig()const; //sobrecarga de metodo necessaria pois getFig necessita referencia const 

        bool getAtivo()const;
        void setAtivo(const bool a);
    };
}