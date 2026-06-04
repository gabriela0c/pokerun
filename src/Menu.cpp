#include "Menu.h"
#include "Jogo.h"

namespace Pokerun{

    Menu::Menu():
    Ente({WIN_SIZE_X, WIN_SIZE_Y}), telaAtual(TelaMenu::INICIO), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()), 
    opcaoSelecionada(0), numJogadores(1), faseEscolhida(1)
    {
        
    }

    Menu::~Menu()
    {
        pJogo = nullptr;
    }

    void Menu::menuInicio()
    {

    }

    void Menu::menuConfig()
    {

    }

    void Menu::menuPausa()
    {

    }

    void Menu::ranking()
    {

    }

    const int Menu::getFaseEScolhida()const
    {
        return faseEscolhida;
    }

    const int Menu::getNumJogadores()const
    {
        return numJogadores;
    }

    void Menu::desenhar()
    {
        switch(telaAtual)
        {
            case TelaMenu::INICIO:{
                std::vector<std::string> opcoes = {"Iniciar", "Ranking", "Sair"};
                desenharOpcoes(opcoes);
            break;
            }

            case TelaMenu::SELECIONAR_JOGADORES:{
                std::vector<std::string> opcoes = {"1 jogador", "2 jogadores"};
                desenharOpcoes(opcoes);
            break;
            }

            case TelaMenu::SELECIONAR_FASE:{
                std::vector<std::string> opcoes = {"Fase 1", "Fase 2"};
                desenharOpcoes(opcoes);
            break;
            }

            case TelaMenu::PAUSA:{
                std::vector<std::string> opcoes = {"Continuar", "Inicio"};
                desenharOpcoes(opcoes);
            break;
            }

            case TelaMenu::RANKING:{
                //desenharRanking();
            break;
            }
        }
    }

    void Menu::desenharOpcoes(std::vector<std::string>& opcoes)
    {
        //usa sf::text e sf::font aqui
    }

    void Menu::executar()
    {
        switch(telaAtual)
        {
            case TelaMenu::INICIO:{
                if(pEvento->cimaPressionado() && opcaoSelecionada > 0){opcaoSelecionada--;}
                if(pEvento->baixoPressionado() && opcaoSelecionada < 2){opcaoSelecionada++;}
        
                if(pEvento->enterPressionado()){
                    if(opcaoSelecionada == 0){
                        telaAtual = TelaMenu::SELECIONAR_JOGADORES;//vai para a tela de selecao no num de jogadores
                        opcaoSelecionada = 0;
                    }
                    if(opcaoSelecionada == 1){
                        telaAtual = TelaMenu::RANKING;//vai para a tela dos rankings
                        opcaoSelecionada = 0;
                    }
                    if(opcaoSelecionada == 2){
                        pJogo->setEstado(EstadoJogo::SAINDO);//sai do jogo
                    }
                }
            break;
            }
        
            case TelaMenu::SELECIONAR_JOGADORES:{
                if(pEvento->cimaPressionado() &&  opcaoSelecionada > 0) {opcaoSelecionada--;}
                if(pEvento->baixoPressionado() &&  opcaoSelecionada < 1) {opcaoSelecionada++;}

                if(pEvento->enterPressionado()){
                    numJogadores = opcaoSelecionada + 1;//guarda o numero de jogadores escolhido
                    telaAtual = TelaMenu::SELECIONAR_FASE;//vai para a tela de selecao de fase
                    opcaoSelecionada = 0;
                }
            break;
            }

            case TelaMenu::SELECIONAR_FASE:{
                if(pEvento->cimaPressionado() &&  opcaoSelecionada > 0) {opcaoSelecionada--;}
                if(pEvento->baixoPressionado() &&  opcaoSelecionada < 1) {opcaoSelecionada++;}

                if(pEvento->enterPressionado()){
                    faseEscolhida = opcaoSelecionada + 1;//guarda a fase escolhida
                    pJogo->setEstado(EstadoJogo::JOGANDO);//inicia o jogo
                    opcaoSelecionada = 0;
                }
            break;
            }

            case TelaMenu::PAUSA:{
                if(pEvento->cimaPressionado() &&  opcaoSelecionada > 0) {opcaoSelecionada--;}
                if(pEvento->baixoPressionado() &&  opcaoSelecionada < 1){opcaoSelecionada--;}

                if(pEvento->enterPressionado()){
                    if(opcaoSelecionada == 0){pJogo->setEstado(EstadoJogo::JOGANDO);}//despausa
                    if(opcaoSelecionada == 1){
                        telaAtual = TelaMenu::INICIO;//volta para o menu de inicio
                        opcaoSelecionada = 0;
                        pJogo->setEstado(EstadoJogo::MENU);//seta o estado do jogo para menu
                    }
                }
            break;
            }

            case TelaMenu::RANKING:{
                if(pEvento->enterPressionado()){
                    telaAtual = TelaMenu::INICIO;//volta para o menu de inicio
                    opcaoSelecionada = 0;
               }
            break;
            }
        }
        desenhar();
    }
}