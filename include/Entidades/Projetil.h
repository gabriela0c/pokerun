#pragma once
#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Jogador.h"

#define LARGURA_PROJ 15.0f
#define ALTURA_PROJ 15.0f
#define TAM_CHAO_Y 50.0f

#define TAMANHO_PROJ_X 104
#define TAMANHO_PROJ_Y 169

#define VEL_PROJETIL_X 150.0f
#define VEL_PROJETIL_Y 300.0f //aqui tem que ser maior pq age a gravidade senao nao vai p/cima
#define DANO_PROJETIL 3

#define WIN_SIZE_X 800.0f
#define WIN_SIZE_Y 600.0f

namespace Pokerun {
    namespace Entidades {

        namespace Personagens{
            class Charizard;
        }

        class Projetil : public Entidade {
        private:
            float vel_x;
            int dano; //int pq vai ser alterado pelo charizard
            Personagens::Charizard* pCharizard;
            bool voando;

        public:
            Projetil(float velX = 0, int dano = DANO_PROJETIL);
            ~Projetil();

            void salvarDataBuffer();  
            void carregarDataBuffer(std::istream& is);
            void salvar();    
            
            void setVoando(const bool v);
            bool getVoando()const;

            void setDano(int d);
            const int getDano()const;

            void setCharizard(Personagens::Charizard* pChar);
            void guardar();
            bool disparar();
            void recarregar(sf::Vector2f dir); //posiciona na borda do charizard e ajusta vel_x conforme a direcao

            void desenhar();//redefino o desenhar aqui porque quero que o GG desenhe o projéti só quando voando

            void executar();
        };
    }
}