#include "Entidades/Personagens/Wartortle.h"
 
namespace Pokerun{
 
    namespace Entidades{
 
        namespace Personagens{
 
            Wartortle::Wartortle():
            Inimigo(NIVEL_MALD_MEDIO, {LARGURA_WARTORTLE, ALTURA_WARTORTLE}, N_VDS_MEDIO, N_PTS_MEDIO), 
            massa(rand() % 51 + 50), tempo_ciclo(0.0f), em_pausa(false)
            {
                setTextura("assets/sprites/personagens/inimigo/wartortle.png", sf::IntRect({0, 0}, {(int)LARGURA_WARTORTLE, (int)ALTURA_WARTORTLE}));
            }
 
            Wartortle::~Wartortle()
            {
 
            }
 
            void Wartortle::salvarDataBuffer()
            {
                Inimigo::salvarDataBuffer();
                buffer << " " << massa;
            }
            void Wartortle::carregarDataBuffer(std::istream& is)
            {
                Inimigo::carregarDataBuffer(is);
                is >> massa;
            }

            void Wartortle::salvar()
            {
                buffer << "WARTORTLE "; 
                salvarDataBuffer(); 
                buffer << std::endl;
            }
 
            void Wartortle::danificar(Jogador* p)
            {
                if (p->getInvencivel()) { return; }
 
                float forcaH = massa * 3;
 
                for(int i = 0; i < nivel_maldade; i++){
                    p->operator--();
                }
 
                aplicarKnockback(p, forcaH);
                p->ativarInvencibilidade();
            }
 
            void Wartortle::executar()
            {
                tempo_ciclo += dt;
 
                if(!em_pausa && tempo_ciclo >= DURACAO_AVANCO)
                {
                    em_pausa = true;
                    tempo_ciclo = 0.0f;
                }
                else if(em_pausa && tempo_ciclo >= DURACAO_PAUSA)
                {
                    em_pausa = false;
                    tempo_ciclo = 0.0f;
                }
 
                if(!em_pausa || !noChao)
                {
                    Inimigo::executar(); //só move quando não esta em pausa
                }
            }
        }
    }
}