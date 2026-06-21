#include "Menu.h"
#include "Jogo.h"

namespace Pokerun{

    Menu::Menu():
    Ente({WIN_SIZE_X, WIN_SIZE_Y}), telaAtual(TelaMenu::INICIO), pJogo(nullptr), pEvento(Gerenciadores::GerenciadorEvento::getGerenciadorEvento()), 
    opcaoSelecionada(0), numJogadores(1), faseEscolhida(1), fonte(), ranking()
    {
        setTextura("assets/sprites/fundos/fundo_menu.jpg", {{},{1024, 765}});
        
        if(!fonte.openFromFile("assets/fonts/PokemonSolid.ttf"))
            std::cerr << "fonte nao carregada!" << std::endl;

        ranking.carregar();//le o arquivo do ranking ao abrir o menu
    }

    Menu::~Menu()
    {
        pJogo = nullptr;
    }

    const int Menu::getFaseEscolhida()const
    {
        return faseEscolhida;
    }

    const int Menu::getNumJogadores()const
    {
        return numJogadores;
    }

    const std::string Menu::getNomeJogador(int i)const
    {
        return nomes[i];
    }

    void Menu::setFaseEscolhida(int f)
    {
        faseEscolhida = f;
    }

    void Menu::setNumJogadores(int num)
    {
        numJogadores = num;
    }

    bool Menu::nomesPreenchidos()const
    {
        bool pronto = false;
        if(getNumJogadores() == 1 && !nomes[0].empty()){
            pronto = true;
        }
        else{
            if(!nomes[0].empty() && !nomes[1].empty()){
                pronto = true;
            }
        }

        return pronto;
    }

    void Menu::capturarNome()
    {
        std::string digitado = pEvento->getTextoDigitado();
        
        if(!digitado.empty()){
            char c = digitado[0];
            if(c == 8){ // backspace
                if(!nomes[opcaoSelecionada].empty()){
                    nomes[opcaoSelecionada].erase(nomes[opcaoSelecionada].size() - 1); 
                }
            }//intervalo dos caracteres ASCII que fazem sentido poder estar em um nome
            else if(c > 32 && c < 127 && (int)nomes[opcaoSelecionada].size() < 10){//tamanho maximo do nome = 10
                nomes[opcaoSelecionada] += c;
            }
        }
    }

    void Menu::irParaPausa()
    {
        telaAtual = TelaMenu::PAUSA;
    }

    void Menu::registrarRanking(int pts1, int pts2)
    {
        ranking.adicionar(nomes[0], pts1);
        if(!nomes[1].empty()){//nome 2 n vazio -> jog2 existe
            ranking.adicionar(nomes[1], pts2);
        }
        ranking.salvar();
    }

    void Menu::irParaFimJogo(const bool vitoria)
    {
        if(vitoria){
            setTextura("assets/sprites/fundos/vitoria.png", {{},{2528, 1686}});
        }
        else{
            setTextura("assets/sprites/fundos/derrota.png", {{},{2528, 1686}});
        }
        telaAtual = TelaMenu::RANKING;
    }

    void Menu::desenhar()
    {
        switch(telaAtual)
        {
            case TelaMenu::INICIO:{
                std::vector<std::string> opcoes = {"Iniciar", "Continuar", "Ranking", "Sair"};
                desenharOpcoes(opcoes);
            break;
            }

            case TelaMenu::SELECIONAR_JOGADORES:{
                std::vector<std::string> opcoes = {"1 Jogador", "2 Jogadores"};
                desenharOpcoes(opcoes);
            break;
            }

            case TelaMenu::SELECIONAR_FASE:{
                std::vector<std::string> opcoes = {"Fase 1", "Fase 2"};
                desenharOpcoes(opcoes);
            break;
            }

            case TelaMenu::PAUSA:{
                std::vector<std::string> opcoes = {"Continuar", "Salvar e Sair", "Inicio"};
                desenharOpcoes(opcoes);
            break;
            }

            case TelaMenu::RANKING:{
                desenharRanking();
            break;
            }

            case TelaMenu::DIGITAR_NOME:{
                desenharTelaNomes();
            break;
            }
        }
    }

    void Menu::desenharOpcoes(const std::vector<std::string>& opcoes)
    {
        float posY = 200.0f;

        for(int i = 0; i < (int)opcoes.size(); i++){
            Botao btn(opcoes[i], fonte, {WIN_SIZE_X / 2.0f, posY});
            btn.setSelecionado(i == opcaoSelecionada);
            btn.desenhar(pGG->getWindow());
            posY += 60.0f;
        }
    }

    void Menu::desenharRanking()
    {
        sf::Text titulo(fonte);
        titulo.setCharacterSize(40);
        titulo.setString("Ranking");
        titulo.setFillColor(sf::Color::Black);
        sf::FloatRect boundsT = titulo.getLocalBounds();
        titulo.setPosition({(WIN_SIZE_X/2) - (boundsT.size.x/2), 240.0f}); 
        pGG->desenhaElementos(titulo);

        sf::Text linha(fonte);
        linha.setCharacterSize(26);
        linha.setFillColor(sf::Color::Black);

        int total = ranking.getTam();
        if(total > MAX_RANKING){ 
            total = MAX_RANKING; 
        }

        for(int i = 0; i < total; i++)
        {
            std::string txt = std::to_string(i + 1) + ": " + ranking.getNome(i) + " - " + std::to_string(ranking.getPontos(i));
            linha.setString(txt);

            sf::FloatRect bounds = linha.getGlobalBounds();
            float posX = 0.0f;
            float posY = 0.0f;

            if (i < 5) {
                posX = (WIN_SIZE_X * 0.25f) - (bounds.size.x / 2);
                posY = 300.0f + (i * 40.0f);
            } else {
                posX = (WIN_SIZE_X * 0.75f) - (bounds.size.x / 2);
                posY = 300.0f + ((i - 5) * 40.0f);
            }

            linha.setPosition({posX, posY});
            pGG->desenhaElementos(linha);
        }

        sf::Text voltar(fonte); 
        voltar.setCharacterSize(20);
        voltar.setString("Enter para voltar");
        voltar.setFillColor(sf::Color::Black);
        sf::FloatRect boundsV = voltar.getLocalBounds();
        voltar.setPosition({WIN_SIZE_X - boundsV.size.x - 20.0f, 20.0f});
        pGG->desenhaElementos(voltar);
    }

    void Menu::desenharTelaNomes()
    {
        sf::Text prompt(fonte);
        prompt.setCharacterSize(28);
        prompt.setString(getNumJogadores() == 2 ? "Nomes:" : "Digite seu nome:");
        prompt.setFillColor(sf::Color::Black);
        sf::FloatRect bounds = prompt.getLocalBounds();
        prompt.setPosition({(WIN_SIZE_X/2) - (bounds.size.x/2), 150.0f});
        pGG->desenhaElementos(prompt);

        float posY = 230.0f;
        for(int i = 0; i < getNumJogadores(); i++){
            sf::Text linha(fonte);
            linha.setCharacterSize(32);

            std::string texto = "Jogador " + std::to_string(i + 1) + ": " + nomes[i] + "_";

            linha.setString(texto);
            linha.setFillColor(i == opcaoSelecionada ? sf::Color::Yellow : sf::Color::Black); //destaca a linha atual

            sf::FloatRect b = linha.getLocalBounds();
            linha.setPosition({(WIN_SIZE_X/2) - (b.size.x/2), posY});
            pGG->desenhaElementos(linha);

            posY += 60.0f;
        }
    }

    void Menu::setJogo(Jogo* pJog)
    {
        if(pJog){
            pJogo = pJog;
        }
    }

    void Menu::executar()
    {
        Ente::desenhar();//desenha o fundo do menu
        
        switch(telaAtual)
        {
            case TelaMenu::INICIO:{
                setTextura("assets/sprites/fundos/fundo_menu.jpg", {{},{1024, 765}});//voltar para o fundo normal do menu
                if(pEvento->cimaPressionado() && opcaoSelecionada > 0){opcaoSelecionada--;}
                if(pEvento->baixoPressionado() && opcaoSelecionada < 3){opcaoSelecionada++;}

                if(pEvento->enterPressionado()){
                    if(opcaoSelecionada == 0){
                        telaAtual = TelaMenu::SELECIONAR_JOGADORES;//vai para a tela de selecao no num de jogadores
                        opcaoSelecionada = 0;
                    }
                    else if(opcaoSelecionada == 1){
                        pJogo->continuarJogo();//recupera o jogo salvo e vai para JOGANDO
                        opcaoSelecionada = 0;
                    }
                    else if(opcaoSelecionada == 2){
                        telaAtual = TelaMenu::RANKING;//vai para a tela dos rankings
                        opcaoSelecionada = 0;
                    }
                    else if(opcaoSelecionada == 3){
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
                    telaAtual = TelaMenu::DIGITAR_NOME;//vai para a area de digitar nomes
                    opcaoSelecionada = 0;
                }
            break;
            }

            case TelaMenu::DIGITAR_NOME:{
                if(getNumJogadores() == 2){
                    if(pEvento->cimaPressionado() &&  opcaoSelecionada > 0) {opcaoSelecionada--;}
                    if(pEvento->baixoPressionado() &&  opcaoSelecionada < 1) {opcaoSelecionada++;}
                }

                capturarNome();
                bool pronto = nomesPreenchidos();

                if(pEvento->enterPressionado() && pronto){
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
                if(pEvento->baixoPressionado() &&  opcaoSelecionada < 2){opcaoSelecionada++;}

                if(pEvento->enterPressionado()){
                    if(opcaoSelecionada == 0){pJogo->setEstado(EstadoJogo::JOGANDO);}//despausa
                    else if(opcaoSelecionada == 1){//Salvar e Sair
                        pJogo->salvarJogo();
                        telaAtual = TelaMenu::INICIO;
                        opcaoSelecionada = 0;
                        pJogo->setEstado(EstadoJogo::MENU);
                    }
                    else if(opcaoSelecionada == 2){//Inicio (sem salvar)
                        telaAtual = TelaMenu::INICIO;
                        opcaoSelecionada = 0;
                        pJogo->setEstado(EstadoJogo::MENU);
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