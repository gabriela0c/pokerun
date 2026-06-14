#include "FaseSegunda.h"

namespace Pokerun{

    namespace Fases{

        FaseSegunda::FaseSegunda(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2):
        Fase(pJog1, pJog2), maxCharizards(5), maxFogos(5)
        {
            setTextura("assets/sprites/fundos/fase2.png", sf::IntRect({0, 0}, {TAM_CAVERNA_X, TAM_CAVERNA_Y}));
            criarCenario();
        }

        FaseSegunda::~FaseSegunda()
        {
            for(int i = 0; i < (int)listaProjeteis.size(); i++)
            {
                delete listaProjeteis[i];
                listaProjeteis[i] = nullptr;
            }
            listaProjeteis.clear();
        }

        void FaseSegunda::criarCharizards()
        {
            Entidades::Personagens::Charizard* pInim = nullptr;
            int n = rand() % 3 + 3; //cria de 3 a 5 inimigos - tabela 1 N5
            for(int i = 0; i < n; i++){
                pInim = new Entidades::Personagens::Charizard();
                pInim->setJogador1(pJogador1);
                pInim->setJogador2(pJogador2);
                pInim->setListaProjeteis(&listaProjeteis);
                lista_ents.incluir(static_cast<Entidades::Entidade*>(pInim));
                GC.incluirInimigo(pInim);
                pInim = nullptr;
            }
        }
        
        void FaseSegunda::criarFogos()
        {
            //mínimo 3 e máximo 5 
            int n = rand() % (maxFogos - 2) + 3;

            for(int i = 0; i < n; i++)
            {
                Entidades::Obstaculos::Fogo* pObs = new Entidades::Obstaculos::Fogo();
                
                int indicePlataforma = rand() % posicoesPlataformas.size();
                sf::FloatRect base = posicoesPlataformas[indicePlataforma];
                
                float larguraObs = pObs->getFig().getSize().x;
                float alturaObs  = pObs->getFig().getSize().y;
                
                int limiteEsq = (int)base.position.x;
                int limiteDir = (int)(base.position.x + base.size.x - larguraObs);
                
                if (limiteDir <= limiteEsq) {
                    limiteDir = limiteEsq + 1;
                }

                float novoX = (float)(rand() % (limiteDir - limiteEsq + 1) + limiteEsq);
                float novoY = base.position.y - alturaObs;

                pObs->getFig().setPosition({novoX, novoY});

                lista_ents.incluir(static_cast<Entidades::Entidade*>(pObs));
                GC.incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(pObs));
            }
        }

        void FaseSegunda::criarInimigos()
        {
            criarBulbasaurs();
            criarCharizards();
        }

        void FaseSegunda::criarObstaculos()
        {
            criarPlataformas();
            criarFogos();
        }
        
        void FaseSegunda::atualizarProjeteis()
        {
            GC.limparProjeteis();
 
            sf::FloatRect tela(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WIN_SIZE_X, WIN_SIZE_Y));
 
            for(int i = (int)listaProjeteis.size() - 1; i >= 0; i--)
            {
                Entidades::Projetil* pProj = listaProjeteis[i];
 
                if(!pProj){
                    listaProjeteis.erase(listaProjeteis.begin() + i);
                    continue;
                }
 
                if(!tela.contains(pProj->getFig().getPosition())){
                    pProj->setAtivo(false);
                }
 
                if(!pProj->getAtivo()){
                    delete pProj;
                    listaProjeteis.erase(listaProjeteis.begin() + i);
                    continue;
                }
 
                GC.incluirProjetil(pProj);
                pProj->executar(); // só física, sem desenhar()
            }
        }

        void FaseSegunda::desenharProjeteis()
        {
            for(int i = 0; i < (int)listaProjeteis.size(); i++){
                if(listaProjeteis[i] && listaProjeteis[i]->getAtivo()){
                    listaProjeteis[i]->desenhar();
                }
            }
        }

        void FaseSegunda::executar()
        {
            atualizarProjeteis();
            Fase::executar(); //desenha fundo + entidades
            desenharProjeteis(); //projéteis por cima de tudo
        }

    }
}