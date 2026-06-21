#pragma once

#include <SFML/Graphics.hpp>

namespace Pokerun{

    class Temporizador{
    private:
        sf::Clock relogio;
        float duracao;
        bool ativo;

    public:
        Temporizador(const float d = 0.0f);
        ~Temporizador();

        void iniciar();
        void atualizar();
        void parar();
        void setDuracao(const float d);

        bool getAtivo()const;
    };
}