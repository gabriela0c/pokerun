#include "Fases/Fase.h"


namespace Pokerun{

    namespace Fases{
 
        Fase::Fase(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2):
        Ente({WIN_SIZE_X, WIN_SIZE_Y}), lista_ents(), GC(), pJogador1(pJog1), pJogador2(pJog2), pChao(new Entidades::Chao()),
        maxBulbasaurs(4)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade*>(pChao));
            pFigura->setPosition({0.0f, 0.0f});
            posicoesPlataformas.push_back(pChao->getFig().getGlobalBounds());//garante que plataformas nao vao ficar em cima do chao

            lista_ents.incluir(static_cast<Entidades::Entidade*>(pJogador1));
            GC.setJogador(pJog1);
            //jogador 2 so eh incluido na lista e em GC se forem selecionados 2 jogadores no menu, senao ele eh incluido 2 vezes na lista
            //e o sprite continua aparecendo apos ele morrer. Pro gerenciador de colisoes nao ocorre nenhum bug, so nao eh necessario
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

            //5 posições pré-definidas
            std::vector<sf::Vector2f> posicoesPossiveis;
            posicoesPossiveis.push_back(sf::Vector2f(100.f, 120.f));
            posicoesPossiveis.push_back(sf::Vector2f(500.f, 190.f));
            posicoesPossiveis.push_back(sf::Vector2f(300.f, 280.f));
            posicoesPossiveis.push_back(sf::Vector2f(150.f, 370.f));
            posicoesPossiveis.push_back(sf::Vector2f(400.f, 440.f));

            for (int i = 4; i > 0; i--)
            {
                int j = rand() % (i + 1);
                sf::Vector2f temp = posicoesPossiveis[i];
                posicoesPossiveis[i] = posicoesPossiveis[j];
                posicoesPossiveis[j] = temp;
            }

            int n = rand() % 3 + 3; // 3 a 5 plataformas
            for (int i = 0; i < n; i++)
            {
                pPlat = new Entidades::Obstaculos::Plataforma();
                pPlat->setPosicao(posicoesPossiveis[i]); //cada i pega uma posição única

                posicoesPlataformas.push_back(pPlat->getFig().getGlobalBounds());
                adicionarObstaculos(pPlat);
                pPlat = nullptr;
            }

            // parede invisível na esquerda
            Entidades::Obstaculos::Plataforma* pParedeEsq = new Entidades::Obstaculos::Plataforma({-100.0f, 0.0f}, {100.0f, WIN_SIZE_Y});
            adicionarObstaculos(pParedeEsq);

            // parede invisível na direita
            Entidades::Obstaculos::Plataforma* pParedeDir = new Entidades::Obstaculos::Plataforma({WIN_SIZE_X, 0.0f}, {100.0f, WIN_SIZE_Y});
            adicionarObstaculos(pParedeDir);
        }

        Entidades::Chao* Fase::getChao()const
        {
            return pChao;
        }

        void Fase::desativaEntidade(Entidades::Entidade* pE)
        {
            lista_ents.remover(pE);
            GC.remover(pE);
        }

        void Fase::ativaJogador(Entidades::Personagens::Jogador* pJog)
        {
            lista_ents.remover(pJog); //garante que nao seja incluido 2x
            lista_ents.incluir(pJog);
            GC.setJogador(pJog);
            pJog->setAtivo(true);
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
            Ente::desenhar();//desenha o fundo da fase
            lista_ents.desenhaMembros();
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

            lista_ents.conectaBuffer(arquivo);
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

        void Fase::recuperaFase()
        {
            std::ifstream arquivo(getNomeArquivo());
            if(!arquivo.is_open()){ return; }

            //limpa entidades atuais menos jogadores e chao
            std::vector<Entidades::Entidade*> lRemover;
            Listas::Elem* pAux = lista_ents.getPrimeiro();
            while(pAux != nullptr){
                Entidades::Entidade* pE = pAux->getInfo();
                if(pE){
                    if(pE != pJogador1 && pE != pJogador2 && pE != pChao){
                    lRemover.push_back(pE);
                    }
                }
                pAux = pAux->getProx();
            }

            for(int i = 0; i < (int)lRemover.size(); i++){
                desativaEntidade(lRemover[i]);   // tira da lista_ents e GC
                delete lRemover[i];
            }

            //le o arquivo e recria
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

                if(tipo == "JOGADOR1"){ pE = pJogador1; ativaJogador(pJogador1); }
                else if(tipo == "JOGADOR2"){ pE = pJogador2; ativaJogador(pJogador2); }
                else{
                    pE = criarPorTipo(tipo);
                    if(!pE){ continue; }   

                    if(tipo == "BULBASAUR" || tipo == "WARTORTLE" || tipo == "CHARIZARD"){
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
                        GC.incluirProjetil(pProj);
                        lista_ents.incluir(pProj);
                    }
                }

                if(pE){
                    pE->carregarDataBuffer(iss);   // restaura o estado proprio

                    if(tipo == "PROJETIL"){
                        int idChar;
                        iss >> idChar;             // le o id do charizard que sobrou na linha
                        lProjeteis.push_back(static_cast<Entidades::Projetil*>(pE));
                        idsCharDosProjeteis.push_back(idChar);
                    }
                }
            }

            // 3) religa cada projetil ao charizard de id correspondente (busca linear)
            for(int i = 0; i < (int)lProjeteis.size(); i++){
                for(int j = 0; j < (int)lCharizards.size(); j++){
                    if(idsCharizards[j] == idsCharDosProjeteis[i]){
                        lProjeteis[i]->setCharizard(lCharizards[j]);
                        lCharizards[j]->adicionarProjetil(lProjeteis[i]);
                        break;
                    }
                }
            }
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
            removerInativos();//aqui porque o GC.executar() seta inativos apos a logica de ataque
            desenhar();
        }
    }
}