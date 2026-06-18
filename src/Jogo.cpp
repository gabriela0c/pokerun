#include "jogo.h"

namespace Pokerun{

    Jogo::Jogo():
    estado(EstadoJogo::MENU), pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()),
    pJogador1(new Entidades::Personagens::Jogador(true)), pJogador2(new Entidades::Personagens::Jogador(false)), Fase1(pJogador1, pJogador2), Fase2(pJogador1, pJogador2)
    {   
        pEvento->setJogador(pJogador1);
        
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
                pEvento->setJogador(pJogador2);// só ativa se escolheu 2 jogadores
                  
                if(menu.getFaseEscolhida() == 1)
                    Fase1.ativaJogador(pJogador2);
                else
                    Fase2.ativaJogador(pJogador2);
            }
            else{
                pEvento->removeJogador2();
                pJogador2->setAtivo(false); 
                if(menu.getFaseEscolhida() == 1)
                    Fase1.desativaEntidade(pJogador2);
                else   
                    Fase2.desativaEntidade(pJogador2);
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
            if(!pJogador1->getAtivo() && !pJogador2->getAtivo()){pGrafico->fecharJanela();}//fecha a janela quando ambos morrem por enquanto

            if(!pJogador1->getAtivo() && menu.getNumJogadores() == 1){pGrafico->fecharJanela();}//fecha janela quando jog1 morreu e so tem ele
            
            pGrafico->limpaJanela();

            pEvento->executar();

            if(pEvento->QPressionado()){Fase1.gravaFase(); Fase2.gravaFase(); pGrafico->fecharJanela();}//comentar

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
                    else{  
                        //Fase1.executar();
                        if(menu.getFaseEscolhida() == 1)
                            Fase1.executar();
                        else    
                            Fase2.executar();
                    }
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