#pragma once 
//esse modelo de gerenciador de gráfico foi inicialmente baseado no desenvolvido pelo ex monitor da disciplina
//Giovane Limas Salvi, mas só bem a base, o resto foi implementado pelos integrantes da equipe

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Pokerun{
    class Ente;
}

namespace Pokerun{

    namespace Gerenciadores{

        class GerenciadorGrafico{
        private:
            sf::RenderWindow* window;
            static GerenciadorGrafico* pGrafico;

        private:
            GerenciadorGrafico();

        public:
            ~GerenciadorGrafico();

            static void destruir();

            static GerenciadorGrafico* getGerenciadorGrafico();
            sf::RenderWindow* getWindow();

            void limpaJanela();
            void desenhaElementos(Ente* pE);
            void desenhaElementos(sf::Text& texto);
            void desenhaElementos(const sf::Drawable& desenho);
            void mostraElementos();
            void fecharJanela();
            const bool verificaJanelaAberta();

        };
    }
}