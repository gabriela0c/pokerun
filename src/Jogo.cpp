#include "jogo.h"

namespace Pokerun{

    Jogo::Jogo():
    estado(EstadoJogo::MENU), pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()),
    pJogador1(new Entidades::Personagens::Jogador(true)), pJogador2(new Entidades::Personagens::Jogador(false)), Fase1(pJogador1, pJogador2)
    {   
        pEvento->setJogador1(pJogador1);
        
        menu.setJogo(this);
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
        if(est == EstadoJogo::JOGANDO){
            if(menu.getNumJogadores() == 2){
                pEvento->setJogador2(pJogador2);  // só ativa se escolheu 2 jogadores
                Fase1.ativaJog2();
            }
            else{
                pEvento->removeJogador2();
                Fase1.desativaJog2();
            }
        }   

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

            switch (estado) {
                case EstadoJogo::MENU:{
                    menu.executar();  
                break;
                }

                case EstadoJogo::JOGANDO:{
                    if (pEvento->pausaPressionado()) {
                        setEstado(EstadoJogo::MENU);
                        menu.irParaPausa(); //seta o estado da tela do menu para pausa
                    }
                    else    
                        Fase1.executar();
                        //if(pMenu->getFaseEscolhida() == 2)
                        //Fase2.executar;
                break;
                }

                case EstadoJogo::RANKING:{
                    //menu.desenharRanking(pPontuacao->getRanking());
                    std::cout << "ainda nao implementado" << std::endl;
                break;
                }

                case EstadoJogo::SAINDO:{
                    pGrafico->fecharJanela();
                break;
                }
            }

            pGrafico->mostraElementos();
        }
    }
}