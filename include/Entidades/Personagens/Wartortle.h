#pragma once 
 
#include "Entidades/Personagens/Inimigo.h"
 
#define LARGURA_WARTORTLE 46.0f
#define ALTURA_WARTORTLE 43.0f
 
#define NIVEL_MALD_MEDIO 2
#define N_VDS_MEDIO 3
#define N_PTS_MEDIO 300
 
// constantes do ciclo de pausa
#define DURACAO_AVANCO 2.0f  //segs em movimento antes de pausar
#define DURACAO_PAUSA  0.8f  // segs parado antes de avançar
 
namespace Pokerun{
 
    namespace Entidades{
 
        namespace Personagens{
 
            class Wartortle : public Inimigo{ //Inim Medio
            private:
                int massa;
                float tempo_ciclo;
                bool em_pausa;
 
            public:
                Wartortle();
                ~Wartortle();
 
                void salvarDataBuffer();
                void salvar();
 
                void danificar(Jogador* p);
                void executar();
            };
        }
    }
}
