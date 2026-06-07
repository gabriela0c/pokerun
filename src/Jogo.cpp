#include "jogo.h"

namespace Pokerun{

    Jogo::Jogo():
    estado(EstadoJogo::MENU), pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()),
    pJogador1(new Entidades::Personagens::Jogador(true)), pJogador2(new Entidades::Personagens::Jogador(false)), pFase(nullptr), pausado(false)
    {   
        pEvento->setJogador1(pJogador1);
        
        menu.setJogo(this);
        executar();
    }

    Jogo::~Jogo()
    {
        delete pFase;
        pFase = nullptr;
        
        delete pJogador1;
        pJogador1 = nullptr;

        delete pJogador2;
        pJogador2 = nullptr;

        Gerenciadores::GerenciadorGrafico::destruir();
        Gerenciadores::GerenciadorEvento::destruir();
    }

    void Jogo::setEstado(EstadoJogo est)
    {
        if(est == EstadoJogo::JOGANDO)
        {
            if(!pausado)
            {
                pJogador1->resetar();
                delete pFase;
                pFase = nullptr;
                
                if(menu.getNumJogadores() == 2){
                    if(menu.getFaseEScolhida() == 2)
                        pFase = new Fases::FaseSegunda(pJogador1, pJogador2);
                    else
                        pFase = new Fases::FasePrimeira(pJogador1, pJogador2);
                    
                    pEvento->setJogador2(pJogador2);
                    pJogador2->resetar();
                    pFase->ativaJogador(pJogador2);
                }
                else{
                    if(menu.getFaseEScolhida() == 2)
                        pFase = new Fases::FaseSegunda(pJogador1, nullptr); // passa nullptr
                    else
                        pFase = new Fases::FasePrimeira(pJogador1, nullptr); // passa nullptr
                    
                    pEvento->removeJogador2();
                }
            }
            pausado = false;
        }

        if(est == EstadoJogo::MENU && estado == EstadoJogo::JOGANDO)
        {
            pausado = true;
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
                    else if(pFase != nullptr){
                        pFase->executar();  // executa só a fase criada
                    }
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