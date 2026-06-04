#pragma once

#include "GerenciadorEvento.h"
#include "Ente.h"

namespace Pokerun{
    class Jogo;
}

namespace Pokerun{

    class Menu : public Ente
    {
    private:
        enum class TelaMenu
        {
            INICIO,
            SELECIONAR_JOGADORES,
            SELECIONAR_FASE,
            PAUSA,
            RANKING
        }; 

        TelaMenu telaAtual;
        Jogo* pJogo;
        Gerenciadores::GerenciadorEvento* pEvento;
        int opcaoSelecionada;
        int numJogadores;
        int faseEscolhida;
        sf::Font fonte;

    public:
        Menu();
        ~Menu();

        void setJogo(Jogo* pJog);

        void desenhar();
        void desenharOpcoes(std::vector<std::string>& opcoes);
        void desenharRanking();
        void irParaPausa();

        const int getFaseEScolhida()const;
        const int getNumJogadores()const;

        void executar();
    };
}


