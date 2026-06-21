#include "jogo.h"

namespace Pokerun{

    Jogo::Jogo(): estado(EstadoJogo::MENU), pGrafico(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()), 
    pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()), pJogador1(new Entidades::Personagens::Jogador(true)), 
    pJogador2(new Entidades::Personagens::Jogador(false)), Fase1(), Fase2()
    {   
        Fase1.setJogadores(pJogador1, pJogador2);
        Fase2.setJogadores(pJogador1, pJogador2);

        Fase1.criarCenario();
        Fase2.criarCenario();

        pEvento->setJogador(pJogador1);
        
        menu.setJogo(this);
        executar();
    }

    Jogo::~Jogo()
    {
        if(pJogador1){
            delete pJogador1;
            pJogador1 = nullptr;
        }

        if(pJogador2){
            delete pJogador2;
            pJogador2 = nullptr;
        }

        Gerenciadores::GerenciadorGrafico::destruir();
        Gerenciadores::GerenciadorEvento::destruir();
    }
            
    void Jogo::salvarJogo()
    {
        //grava a fase atual e apaga a outra 
        if(menu.getFaseEscolhida() == 1){
            Fase1.gravaFase();
            std::remove("Fase2.dat");
        }
        else{
            Fase2.gravaFase();
            std::remove("Fase1.dat");
        }
    }

    void Jogo::continuarJogo()
    {
        //descobre qual fase tem save 
        int fase = 0;
        std::ifstream f1("Fase1.dat");
        
        if(f1.is_open()){ 
            fase = 1; 
            f1.close(); 
        }
        else{
            std::ifstream f2("Fase2.dat");
            if(f2.is_open()){ 
                fase = 2; 
                f2.close(); 
            }
        }

        if(fase == 0){//nao teve save 
            return; 
        }   

        int numJog = (fase == 1) ? Fase1.recuperaFase() : Fase2.recuperaFase();

        menu.setFaseEscolhida(fase);//configura o jogo conforme o save
        menu.setNumJogadores(numJog);
       
        setEstado(EstadoJogo::JOGANDO); 
    }

    //constroi a tela final do ranking com base no resultado e prepara a proxima jogada
    void Jogo::gameOver(const bool resultado)
    {
        menu.registrarRanking(pJogador1->getPontos(), pJogador2->getPontos());
        menu.irParaFimJogo(resultado);           
        setEstado(EstadoJogo::MENU);
        Fase1.limpaFase();
        Fase2.limpaFase();
        pJogador1->resetar();
        pJogador2->resetar();
        Fase1.criarCenario();
        Fase2.criarCenario();
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

            pGrafico->limpaJanela();

            pEvento->executar();

            switch (estado) {

                case EstadoJogo::MENU:{
                    menu.executar();  
                break;
                }

                case EstadoJogo::JOGANDO:{

                    if(!pJogador1->getAtivo() && !pJogador2->getAtivo()){//fecha a janela quando ambos morrem por enquanto
                        gameOver(false);//perdeu
                        break;
                    }

                    if(!pJogador1->getAtivo() && menu.getNumJogadores() == 1){//fecha janela quando jog1 morreu e so tem ele
                        gameOver(false);
                        break;
                    }
                    if (pEvento->pausaPressionado()) {
                        setEstado(EstadoJogo::MENU);
                        menu.irParaPausa(); //seta o estado da tela do menu para pausa
                    }
                    else{  
                        if(menu.getFaseEscolhida() == 1)//logica de pasar de fase
                            if(Fase1.semInimigos()){
                                menu.setFaseEscolhida(2);
                                Fase2.passarJogador(pJogador1);
                                if(menu.getNumJogadores() == 2){
                                    Fase2.passarJogador(pJogador2);
                                }
                                pJogador1->reposicionar();
                                if(pJogador2->getAtivo()){
                                    pJogador2->reposicionar();
                                }
                            }
                            else{
                                Fase1.executar();
                            }
                        else{   
                            if(Fase2.semInimigos()){
                                gameOver(true);//venceu
                                break;
                            }
                            else{
                                Fase2.executar();
                            }
                        }
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