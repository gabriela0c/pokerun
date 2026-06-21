#include "Botao.h"

namespace Pokerun{

    Botao::Botao(const std::string& label, sf::Font& fonte, sf::Vector2f posicao)
    :texto(fonte), selecionado(false)
    {
        //configura a caixa
        forma.setSize({220.0f, 45.0f});
        forma.setPosition({posicao.x - 110.0f, posicao.y - 5.0f});
        forma.setFillColor(sf::Color(0, 0, 0, 120));
        forma.setOutlineThickness(2.0f);
        forma.setOutlineColor(sf::Color::Black);

        //configura o texto
        texto.setString(label);
        texto.setCharacterSize(30);
        texto.setFillColor(sf::Color::Black);

        //centraliza o texto dentro da forma
        sf::FloatRect boundsTexto = texto.getLocalBounds();
        sf::Vector2f centroForma = {forma.getPosition().x + forma.getSize().x / 2.0f, forma.getPosition().y + forma.getSize().y / 2.0f};
        texto.setPosition({centroForma.x - boundsTexto.size.x / 2.0f, centroForma.y - boundsTexto.size.y / 2.0f});
    }

    Botao::~Botao(){}

    void Botao::setSelecionado(bool s)
    {
        selecionado = s;
        if(selecionado)
        {
            forma.setOutlineColor(sf::Color::Yellow);
            texto.setFillColor(sf::Color::Yellow);
        }
        else
        {
            forma.setOutlineColor(sf::Color::Black);
            texto.setFillColor(sf::Color::Black);
        }
    }

    void Botao::desenhar(sf::RenderWindow* window)
    {
        if(window)
        {
            window->draw(forma);
            window->draw(texto);
        }
    }
}