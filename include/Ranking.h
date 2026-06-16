#pragma once

#include <fstream>
#include <string>
#include <vector>

#define ARQ_RANKING "ranking.dat"
#define MAX_RANKING 10   

namespace Pokerun{

    class Ranking{
    private:
        struct Entrada{
            std::string nome;
            int pontos;
        };
        std::vector<Entrada> entradas;  

    public:
        Ranking();
        ~Ranking();

        void carregar();// le ranking.dat
        void adicionar(const std::string nome, int pontos);
        void salvar();// grava ranking.dat
        
        void ordenar(); 

        int getTam()const;
        const std::string getNome(int i)const;
        int getPontos(int i)const;
    };
}
