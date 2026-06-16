#pragma once

#include "Gerenciadores/GerenciadorEvento.h"
#include "Ente.h"
#include "Ranking.h"

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
            DIGITAR_NOME,
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
        Ranking ranking;
        std::string nomes[2];

    public:
        Menu();
        ~Menu();

        void setJogo(Jogo* pJog);

        void desenhar();
        void desenharOpcoes(std::vector<std::string> opcoes);
        void desenharRanking();
        void desenharTelaNomes();

        void irParaPausa();

        bool nomesPreenchidos()const;
        void capturarNome();

        const int getFaseEscolhida()const;
        const int getNumJogadores()const;
        const std::string getNomeJogador(int i)const;   

        void executar();
    };
}


