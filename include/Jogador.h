#pragma once

#include "Personagem.h"
#include <SFML/Graphics.hpp>

#define VEL_JOG_X 0.10f

#define POS0_JOG_X 50.0f
#define POS0_JOG_Y 300.0f

#define LARGURA_PIKACHU 40
#define ALTURA_PIKACHU 38

#define LARGURA_RAICHU 48
#define ALTURA_RAICHU 46

namespace Pokerun{   

    namespace Entidades{

        namespace Personagens{

            class Jogador : public Personagem{
            private:
                const bool ehJogador1;
            
            public:
                Jogador(const bool ehJog1 = false);    
                ~Jogador();

                void carregarTextura(const std::string& caminhoArquivo);

                void mover();
                void pular();

                bool colisao_posso_pular(Entidade* pOutra);
                void setTextura(std::string caminho, sf::IntRect bounds);
                //essa funcao so eh util para o jogador msm os objetos das outras classes vao todos ter a mesma textura
                void executar();
            };
        }
    }
}