#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Pokerun{

    class Botao{
    private:
        sf::RectangleShape forma;
        sf::Text texto;
        bool selecionado;

    public:
        Botao(const std::string& label, sf::Font& fonte, sf::Vector2f posicao);
        ~Botao();

        void setSelecionado(bool s);
        void desenhar(sf::RenderWindow* window);
    };
}