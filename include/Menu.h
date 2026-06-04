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

    public:
        Menu();
        ~Menu();

        void menuInicio();
        void menuPausa();
        void menuConfig();
        void ranking();

        void desenhar();
        void desenharOpcoes(std::vector<std::string>& opcoes);
        void desenharRanking();

        const int getFaseEScolhida()const;
        const int getNumJogadores()const;

        void executar();
    };
}