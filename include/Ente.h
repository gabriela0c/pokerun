#pragma once
#include "GerenciadorGrafico.h"

namespace Pokerun {

    class Ente {
    protected:
    //int id;
    bool ativo;    
    static Gerenciadores::GerenciadorGrafico* pGG;
    sf::RectangleShape* pFig; //ponteiro para a figura, para permitir polimorfismo
        
    public:
        Ente();
        virtual ~Ente();

        virtual void executar() = 0;
        virtual void desenhar();

        static void setGG(Gerenciadores::GerenciadorGrafico* pG);

        //const int getId() const;
        const bool getAtivo() const;
        void setAtivo(const bool a);
    };
}