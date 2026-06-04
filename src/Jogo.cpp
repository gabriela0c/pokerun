#include "jogo.h"

namespace Pokerun{

    Jogo::Jogo():
    estado(EstadoJogo::MENU), pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()),
    pJogador1(new Entidades::Personagens::Jogador(true)), pJogador2(new Entidades::Personagens::Jogador(false)), Fase1(pJogador1, pJogador2)
    {
        pEvento->setJogador1(pJogador1);
        pEvento->setJogador2(pJogador2);
        executar();
    }

    Jogo::~Jogo()
    {
        delete pJogador1;
        pJogador1 = nullptr;

        delete pJogador2;
        pJogador2 = nullptr;

        Gerenciadores::GerenciadorGrafico::destruir();
        Gerenciadores::GerenciadorEvento::destruir();
    }

    void Jogo::setEstado(EstadoJogo est)
    {
        estado = est;
    }

    EstadoJogo Jogo::getEstado()const
    {
        return estado;
    }

    void Jogo::executar()
    {
        while(pGrafico->verificaJanelaAberta()){
            pGrafico->limpaJanela();

            pEvento->executar();
            /*
            switch (estado) {
                case EstadoJogo::MENU:
                    pMenu->executar();  
                break;
                case EstadoJogo::JOGANDO:
                    if (pEvento->pausaPressionado()) 
                        estado = EstadoJogo::PAUSADO;
                    else    
                        Fase1.executar();
                        //if(pMenu->getFaseEscolhida() == 2)
                        //Fase2.executar;
                break;
                case EstadoJogo::PAUSADO:
                    pMenu->desenharPausa();
                break;
                case EstadoJogo::RANKING:
                    pMenu->desenharRanking(pPontuacao->getRanking());
                break;
                case EstadoJogo::SAINDO:
                    pGrafico->fecharJanela();
                break;
            }*/            
            Fase1.executar();

            pGrafico->mostraElementos();
        }
    }
}