#pragma once

#include "Fase.h"
//#include "Charizard.h"
#include "Fogo.h"

#define TAM_CAVERNA_X 639 //esse é o tamanho dos sprites nao o que ele tem na tela
#define TAM_CAVERNA_Y 360

namespace Pokerun{

    namespace Fases{

        class FaseSegunda : public Fase{
        private:
            const int maxCharizards;
            const int maxFogos;
        public:
        FaseSegunda(Entidades::Personagens::Jogador* pJog1 = nullptr, Entidades::Personagens::Jogador* pJog2 = nullptr);
        ~FaseSegunda();
        
        //void criarCharizards();
        void criarFogos();
        
        void criarInimigos();
        void criarObstaculos();

        void executar();
        
        };
    }
}