#include "Fases/Fase.h"


namespace Pokerun{

    namespace Fases{
 
        Fase::Fase(): Ente({WIN_SIZE_X, WIN_SIZE_Y}), lista_ents(), GC(), pJogador1(nullptr), pJogador2(nullptr), 
        pChao(new Entidades::Chao()), maxBulbasaurs(4), maxPlataformas(5)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade*>(pChao));
            pFigura->setPosition({0.0f, 0.0f});
            posicoesPlataformas.push_back(pChao->getFig().getGlobalBounds());//garante que plataformas nao vao ficar em cima do chao

            GC.setChao(pChao);
        }

        Fase::~Fase()
        {            
            lista_ents.remover(pJogador1); //remover os jogadores da lista primeiro porque não quero que 
            lista_ents.remover(pJogador2); //eles sejam deletados na fase e sim no jogo

            lista_ents.deletaMembros();

            pJogador1 = nullptr;
            pJogador2 = nullptr;
            lista_ents.limpar();
        }

        void Fase::criarBulbasaurs()
        {
            Entidades::Personagens::Inimigo* pBulba = nullptr;
            int n = rand() % 2;
            for(int i = n; i < maxBulbasaurs; i++)
            {//cria de 3 a 4 bulbasaur (instâncias aleatórias)
                pBulba = new Entidades::Personagens::Bulbasaur();
                adicionarInimigos(pBulba);
                pBulba = nullptr;
            }
        }

        void Fase::criarPlataformas()
        {
            Entidades::Obstaculos::Plataforma* pPlat = nullptr;

            //5 posicoes pre definidas
            std::vector<sf::Vector2f> posicoesPossiveis;
            posicoesPossiveis.push_back(sf::Vector2f(530.0f, 430.0f));
            posicoesPossiveis.push_back(sf::Vector2f(70.0f, 180.0f));
            posicoesPossiveis.push_back(sf::Vector2f(530.0f, 180.0f));
            posicoesPossiveis.push_back(sf::Vector2f(120.0f, 430.0f));
            posicoesPossiveis.push_back(sf::Vector2f(330.0f, 300.0f));

            int n = rand() % 3; // 3 a 5 plataformas
            for (int i = n; i < maxPlataformas; i++)
            {
                pPlat = new Entidades::Obstaculos::Plataforma();
                pPlat->setPosicao(posicoesPossiveis[i]); //cada i pega uma posição única

                posicoesPlataformas.push_back(pPlat->getFig().getGlobalBounds());
                adicionarObstaculos(pPlat);
                pPlat = nullptr;
            }
        }

        void Fase::desativaEntidade(Entidades::Entidade* pE)
        {
            lista_ents.remover(pE);
            GC.remover(pE);
        }

        void Fase::setJogadores(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2)
        {
            pJogador1 = pJog1;
            pJogador2 = pJog2;

            if (pJogador1) {
                lista_ents.incluir(pJogador1);
                GC.setJogador(pJogador1);
            }
            
            if (pJogador2) {
                lista_ents.incluir(pJogador2);
                GC.setJogador(pJogador2); 
            }
        }

        void Fase::ativaJogador(Entidades::Personagens::Jogador* pJog)
        {
            lista_ents.remover(pJog); //garante que nao seja incluido 2x
            lista_ents.incluir(pJog);
            GC.setJogador(pJog);
            pJog->setAtivo(true);
        }

        //essa funcao apesar de ser mto parecida com ativa jogador é necessaria para a logica se passar de fase
        void Fase::passarJogador(Entidades::Personagens::Jogador* pJog)//porque um jogador morto em uma fase n pode reviver na proxima
        {
            if(pJog && pJog->getAtivo()){   
                lista_ents.remover(pJog);   
                lista_ents.incluir(pJog);
                GC.setJogador(pJog);
            }
        }

        void Fase::adicionarInimigos(Entidades::Personagens::Inimigo* pInim)
        {
            if(pInim){
                pInim->setJogador(pJogador1);
                pInim->setJogador(pJogador2);
                lista_ents.incluir(pInim);
                GC.incluirInimigo(pInim);
            }
        }

        void Fase::adicionarObstaculos(Entidades::Obstaculos::Obstaculo* pObs)
        {
            if(pObs){
                lista_ents.incluir(pObs);
                GC.incluirObstaculo(pObs);
            }
        }

        void Fase::adicionarProjetil(Entidades::Projetil* pProj)
        {
            GC.incluirProjetil(pProj);
            lista_ents.incluir(pProj);
        }

        void Fase::colocaNaPlataforma(Entidades::Obstaculos::Obstaculo* pObs)
        {
            int indicePlataforma = rand() % posicoesPlataformas.size();
            sf::FloatRect base = posicoesPlataformas[indicePlataforma];

            sf::Vector2f sizeObs = pObs->getSize();
                
            int limiteEsq = (int)base.position.x;
            int limiteDir = (int)(base.position.x + base.size.x - sizeObs.x);
                
            if (limiteDir <= limiteEsq) {
                limiteDir = limiteEsq + 1;
            }

            float novoX = (float)(rand() % (limiteDir - limiteEsq + 1) + limiteEsq);
            float novoY = base.position.y - sizeObs.y;

            pObs->setPosicao({novoX, novoY});
        }

        void Fase::desenhar()
        {
            Ente::desenhar(); //desenha o fundo
            
            lista_ents.desenhaMembros(); //desenha todas as entidades e seus respectivos huds
        }

        const bool Fase::semInimigos()const
        {
            return (GC.getNumInimigos() == 0);
        }

        void Fase::removerInativos()
        {
            std::vector<Entidades::Entidade*> lInativos = lista_ents.getInativos();

            for(int i = 0; i < (int)lInativos.size(); i++){
                desativaEntidade(lInativos[i]);
                //se for inimigo deleta (eles nao revivem), se jogador pode so inativar (porque tem como mudar de 2 pra 1 e 1 pra 2)
                if(lInativos[i] != pJogador1 && lInativos[i] != pJogador2){ 
                    delete lInativos[i]; //o remover da lista nao deleta info, so tira da lista e deleta o ELEMENTO
                }
            }
        }

        void Fase::gravaFase()
        {
            std::ofstream arquivo(getNomeArquivo());
            if(!arquivo.is_open()){ return; }

            int numJogs = (pJogador2 && pJogador2->getAtivo()) ? 2 : 1;
            arquivo << numJogs << std::endl;

            lista_ents.conectaBuffer(arquivo);
        }

        void Fase::limpaFase()//remove do GC, lista_ents e deleta todos menos jogadores e chao
        {
            lista_ents.remover(pJogador1);
            lista_ents.remover(pJogador2);
            lista_ents.remover(pChao);

            lista_ents.deletaMembros();
            lista_ents.limpar();
            GC.limparListas();      

            lista_ents.incluir(pJogador1);
            lista_ents.incluir(pJogador2);
            lista_ents.incluir(pChao);

            posicoesPlataformas.clear();//limpa as posicoes para nao ficarem posicoes fantasmas na proxima jogada
            posicoesPlataformas.push_back(pChao->getFig().getGlobalBounds());//readiciona o chao pq ele era adicionado em construtora

            GC.setJogador(pJogador1);  
            GC.setJogador(pJogador2);
        }

        Entidades::Entidade* Fase::criarPorTipo(const std::string tipo)
        {
            if(tipo == "BULBASAUR")  
                return new Entidades::Personagens::Bulbasaur();
            else if(tipo == "WARTORTLE")  
                return new Entidades::Personagens::Wartortle();
            else if(tipo == "CHARIZARD")  
                return new Entidades::Personagens::Charizard();
            else if(tipo == "PLATAFORMA") 
                return new Entidades::Obstaculos::Plataforma();
            else if(tipo == "POCA")       
                return new Entidades::Obstaculos::Poca();
            else if(tipo == "FOGO")       
                return new Entidades::Obstaculos::Fogo();
            else if(tipo == "PROJETIL")   
                return new Entidades::Projetil();
            else    
                return nullptr;  
        }

        int Fase::recuperaFase()
        {
            std::ifstream arquivo(getNomeArquivo());
            if(!arquivo.is_open()){ return 0; }

            std::string linhaCabecalho;
            std::getline(arquivo, linhaCabecalho);
            std::istringstream issCabec(linhaCabecalho);
            int numJogs = 1;
            issCabec >> numJogs;

            //limpa entidades atuais menos jogadores e chao
            limpaFase();

            //vetores para religar projetil e charizard 
            std::vector<Entidades::Personagens::Charizard*> lCharizards;
            std::vector<int> idsCharizards;          // id salvo de cada charizard (mesmo indice)
            std::vector<Entidades::Projetil*> lProjeteis;
            std::vector<int> idsCharDosProjeteis;    // id do charizard que cada projetil referencia

            std::string linha;
            while(std::getline(arquivo, linha)){
                std::istringstream iss(linha);
                std::string tipo;
                int idSalvo;
                iss >> tipo >> idSalvo;

                Entidades::Entidade* pE = nullptr;

                if(tipo == "JOGADOR1"){ 
                    pE = pJogador1; 
                    ativaJogador(pJogador1); 
                }
                else if(tipo == "JOGADOR2"){
                    pE = pJogador2; 
                    ativaJogador(pJogador2); 
                }
                else{
                    pE = criarPorTipo(tipo);
                    if(!pE){ continue; }   

                    if(tipo == "BULBASAUR" || tipo == "WARTORTLE" || tipo == "CHARIZARD"){//downcasts nao sao opcionais
                        adicionarInimigos(static_cast<Entidades::Personagens::Inimigo*>(pE));

                        if(tipo == "CHARIZARD"){
                            lCharizards.push_back(static_cast<Entidades::Personagens::Charizard*>(pE));
                            idsCharizards.push_back(idSalvo);
                        }
                    }
                    else if(tipo == "PLATAFORMA" || tipo == "POCA" || tipo == "FOGO"){
                        adicionarObstaculos(static_cast<Entidades::Obstaculos::Obstaculo*>(pE));
                    }
                    else if(tipo == "PROJETIL"){
                        Entidades::Projetil* pProj = static_cast<Entidades::Projetil*>(pE);
                        adicionarProjetil(pProj);
                    }
                }

                if(pE){// restaura o estado da entidade
                    pE->carregarDataBuffer(iss);   

                    if(tipo == "PROJETIL"){
                        int idChar;
                        iss >> idChar;             // le o id do charizard que sobrou na linha
                        lProjeteis.push_back(static_cast<Entidades::Projetil*>(pE));
                        idsCharDosProjeteis.push_back(idChar);
                    }
                }
            }

            //religa cada projetil ao charizard de id correspondente 
            for(int i = 0; i < (int)lProjeteis.size(); i++){
                for(int j = 0; j < (int)lCharizards.size(); j++){
                    if(idsCharizards[j] == idsCharDosProjeteis[i]){
                        lProjeteis[i]->setCharizard(lCharizards[j]);
                        lCharizards[j]->adicionarProjetil(lProjeteis[i]);
                        break;
                    }
                }
            }
            
            return numJogs; 
        }

        void Fase::criarCenario()
        {
            criarInimigos();
            criarPlataformas();
            criarObstaculos();
        }

        void Fase::executar()
        {   
            lista_ents.percorrer();//executa todos da lista polimorficamente
            GC.executar();
            removerInativos();
            desenhar();
        }
    }
}