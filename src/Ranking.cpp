#include "Ranking.h"

namespace Pokerun{

    Ranking::Ranking(): entradas()
    {

    }

    Ranking::~Ranking()
    {

    }

    void Ranking::carregar()
    {
        entradas.clear();

        std::ifstream arquivo("ranking.dat");
        if(!arquivo.is_open()){ return; }

        Entrada e;
        while(arquivo >> e.nome >> e.pontos){
            entradas.push_back(e);
        }
    }

    void Ranking::adicionar(const std::string nome, int pontos)
    {
        Entrada e;
        e.nome = nome;
        e.pontos = pontos;
        entradas.push_back(e);
        ordenar();
    }

    void Ranking::ordenar()
    {
        for(int i = 0; i < (int)entradas.size() - 1; i++){
            int maior = i;
            for(int j = i + 1; j < (int)entradas.size(); j++){
                if(entradas[j].pontos > entradas[maior].pontos){
                    maior = j;
                }
            }
            if(maior != i){
                Entrada temp = entradas[i];
                entradas[i] = entradas[maior];
                entradas[maior] = temp;
            }
        }
    }

    void Ranking::salvar()
    {
        std::ofstream arquivo("ranking.dat");  
        if(!arquivo.is_open()){return;}

        for(int i = 0; i < (int)entradas.size(); i++){
            arquivo << entradas[i].nome << " " << entradas[i].pontos << std::endl;
        }
    }

    int Ranking::getTam()const
    {
        return (int)entradas.size();
    }

    const std::string Ranking::getNome(int i)const
    {
        return entradas[i].nome;
    }

    int Ranking::getPontos(int i)const
    {
        return entradas[i].pontos;
    }
}
