#pragma once 

#include <iostream>

#include <SFML/Graphics.hpp>

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
            void desenhaElementos(sf::RectangleShape& corpo);
            void mostraElementos();
            void fecharJanela();
            const bool verificaJanelaAberta();

        };
    }
}