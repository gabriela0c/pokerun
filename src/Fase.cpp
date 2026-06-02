#include "Fase.h"
#include <vector>

namespace Pokerun{

    namespace Fases{
 
        Fase::Fase(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2, const ID i):
        Ente({WIN_SIZE_X, WIN_SIZE_Y}, i), lista_ents(), GC(), pJogador1(pJog1), pJogador2(pJog2), pChao(new Entidades::Chao())
        {
            lista_ents.incluir(static_cast<Entidades::Entidade*>(pChao));
            pFigura->setPosition({0.0f, 0.0f});//poderia tirar essa linha ja que default é 0,0
            posicoesPlataformas.push_back(pChao->getFig().getGlobalBounds());//garante que plataformas nao vao ficar em cima do chao

            lista_ents.incluir(static_cast<Entidades::Entidade*>(pJog1));
            lista_ents.incluir(static_cast<Entidades::Entidade*>(pJog2));
            GC.setJogador1(pJog1);
            GC.setJogador2(pJog2);
        }

        Fase::~Fase()
        {
            pJogador1 = nullptr;
            pJogador2 = nullptr;
            lista_ents.limpar();
        }

        void Fase::criarBulbasaurs()
        {
            Entidades::Personagens::Inimigo* pInim = nullptr;
            int n = rand() % 3 + 3; //cria de 3 a 5 inimigos - tabela 1 N5
            for(int i = 0; i < n; i++){
                pInim = new Entidades::Personagens::Bulbasaur();
                pInim->setJogador1(pJogador1);
                pInim->setJogador2(pJogador2);
                lista_ents.incluir(static_cast<Entidades::Entidade*>(pInim));
                GC.incluirInimigo(pInim);
                pInim = nullptr;
            }
        }

        void Fase::criarPlataformas()
        {

            Entidades::Obstaculos::Plataforma* pPlat = nullptr;
    
            for(int i = 0; i < 3; i++)
            {
                pPlat = new Entidades::Obstaculos::Plataforma();
                
                bool posicaoValida = false;
                int tentativas = 0;

                while (!posicaoValida && tentativas < 100) 
                {
                    sf::FloatRect novaArea = pPlat->getFig().getGlobalBounds();
                    bool sobrepoe = false;

                    std::vector<sf::FloatRect>::iterator it;
                    //range based for e auto nao sao c++ 2003
                    for (it = posicoesPlataformas.begin(); it != posicoesPlataformas.end(); it++) 
                    {
                        if (novaArea.findIntersection(*it)) 
                        {
                            sobrepoe = true;
                            break; 
                        }
                    }
                    if (sobrepoe) 
                    {
                        int limiteX = WIN_SIZE_X + 1 - (int)pPlat->getFig().getSize().x;
                        int limiteY = WIN_SIZE_Y + 1 - (int)pPlat->getFig().getSize().y;
                        
                        if (limiteX <= 0){ 
                            limiteX = 1;
                        }
                        if (limiteY <= 0) {
                            limiteY = 1;
                        }

                        float novoX = (float)(rand() % limiteX);
                        float novoY = (float)(rand() % limiteY);
                                
                        pPlat->getFig().setPosition({novoX, novoY});

                        tentativas++;
                        } 
                        else
                            posicaoValida = true;
                }

                posicoesPlataformas.push_back(pPlat->getFig().getGlobalBounds());
                
                lista_ents.incluir(static_cast<Entidades::Entidade*>(pPlat));
                GC.incluirObstaculo(pPlat); 
                pPlat = nullptr;
            }

            // parede invisível na esquerda
            Entidades::Obstaculos::Plataforma* pParedeEsq = new Entidades::Obstaculos::Plataforma({-100.0f, 0.0f}, {100.0f, WIN_SIZE_Y});
            lista_ents.incluir(pParedeEsq);
            GC.incluirObstaculo(pParedeEsq);

            // parede invisível na direita
            Entidades::Obstaculos::Plataforma* pParedeDir = new Entidades::Obstaculos::Plataforma({WIN_SIZE_X, 0.0f}, {100.0f, WIN_SIZE_Y});
            lista_ents.incluir(pParedeDir);
            GC.incluirObstaculo(pParedeDir);
        }

        Entidades::Chao* Fase::getChao()const
        {
            return pChao;
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