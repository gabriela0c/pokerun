#include "Fase.h"
#include <vector>

namespace Pokerun{

    namespace Fases{

        Fase::Fase(Entidades::Personagens::Jogador* pJog, const ID i):
        Ente({DIM_CHAO_X, DIM_CHAO_Y}, i), lista_ents(), GC(), pJogador(pJog)
        {
            pFigura->setPosition({0.0f, WIN_SIZE_Y - DIM_CHAO_Y});
            pFigura = new sf::RectangleShape();

            if (!texturaFundo.loadFromFile("assets/sprites/fundos/fase1.png"))
                std::cout << "ERRO: Nao foi possivel carregar a imagem de fundo!" << std::endl;
            
            pFigura->setSize(sf::Vector2f(WIN_SIZE_X, WIN_SIZE_Y));
            pFigura->setTexture(&texturaFundo);

            lista_ents.incluir(static_cast<Entidades::Entidade*>(pJog));
            GC.setJogador(pJog);
        }

        Fase::~Fase()
        {
            pJogador = nullptr;
            lista_ents.limpar();
        }

        void Fase::criarInimFaceis()
        {
            Entidades::Personagens::Inimigo* pInim = nullptr;
            int n = rand() % 3 + 3; //cria de 3 a 5 inimigos - tabela 1 N5
            for(int i = 0; i < n; i++){
                pInim = new Entidades::Personagens::Inimigo();
                pInim->setJogador(pJogador);
                lista_ents.incluir(static_cast<Entidades::Entidade*>(pInim));
                GC.incluirInimigo(pInim);
                pInim = nullptr;
            }
        }

        void Fase::criarPlataformas()
        {
            //lista p guardar as áreas já ocupadas
            std::vector<sf::FloatRect> areasOcupadas;
            
            Entidades::Obstaculos::Plataforma* pPlat = nullptr;
            
            for(int i = 0; i < 3; i++){
                pPlat = new Entidades::Obstaculos::Plataforma();
                
                bool posicaoValida = false;
                int tentativas = 0;

                while (!posicaoValida && tentativas < 100) 
                {
                    sf::FloatRect novaArea = pPlat->getFig().getGlobalBounds();
                    bool sobrepoe = false;

                    for (const auto& area : areasOcupadas) 
                    {
                        if (novaArea.findIntersection(area)) 
                        {
                            sobrepoe = true;
                            break; 
                        }
                    }

                    if (sobrepoe) 
                    {
                        int limiteX = 801 - (int)pPlat->getFig().getSize().x;
                        int limiteY = 601 - (int)pPlat->getFig().getSize().y;
                        
                        if (limiteX <= 0) limiteX = 1;
                        if (limiteY <= 0) limiteY = 1;

                        float novoX = (float)(rand() % limiteX);
                        float novoY = (float)(rand() % limiteY);
                        
                        pPlat->getFig().setPosition({novoX, novoY});

                        tentativas++;
                    } 
                    else
                        posicaoValida = true;
                }

                areasOcupadas.push_back(pPlat->getFig().getGlobalBounds());
                
                lista_ents.incluir(static_cast<Entidades::Entidade*>(pPlat));
                GC.incluirObstaculo(pPlat); 
                pPlat = nullptr;
            }
            
            // chão
            pPlat = new Entidades::Obstaculos::Plataforma({0.0f, WIN_SIZE_Y - 30.0f}, {WIN_SIZE_X, 30.0f}); 
            lista_ents.incluir(pPlat);
            GC.incluirObstaculo(pPlat);

            // parede invisível na esquerda
            Entidades::Obstaculos::Plataforma* pParedeEsq = new Entidades::Obstaculos::Plataforma({-100.0f, 0.0f}, {100.0f, WIN_SIZE_Y});
            lista_ents.incluir(pParedeEsq);
            GC.incluirObstaculo(pParedeEsq);

            // parede invisível na direita
            Entidades::Obstaculos::Plataforma* pParedeDir = new Entidades::Obstaculos::Plataforma({WIN_SIZE_X, 0.0f}, {100.0f, WIN_SIZE_Y});
            lista_ents.incluir(pParedeDir);
            GC.incluirObstaculo(pParedeDir);
        }

        void Fase::desenhar()
        {
            Ente::desenhar();
            
            auto* pAux = lista_ents.getPrimeiro();
            while(pAux!=nullptr){
                if(pAux->getInfo()){
                    pAux->getInfo()->desenhar();
                }    
            pAux = pAux->getProx();
            }   
        }

        void Fase::executar()
        {
            lista_ents.percorrer();
            GC.executar();
            desenhar();
        }
    }
}