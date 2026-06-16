#include "Fases/FaseSegunda.h"

namespace Pokerun{

    namespace Fases{

        FaseSegunda::FaseSegunda(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2):
        Fase(pJog1, pJog2), maxCharizards(4), maxFogos(5)
        {
            setTextura("assets/sprites/fundos/fase2.png", sf::IntRect({0, 0}, {TAM_CAVERNA_X, TAM_CAVERNA_Y}));
            criarCenario();
        }

        FaseSegunda::~FaseSegunda()
        {

        }

        void FaseSegunda::criarCharizards()
        {
            Entidades::Personagens::Charizard* pInim = nullptr;
            int n = rand() % 2 + 3; //cria de 3 a 4 inimigos - tabela 1 N5
            for(int i = 0; i < n; i++){
                pInim = new Entidades::Personagens::Charizard();
                pInim->setJogador1(pJogador1);
                pInim->setJogador2(pJogador2);
                pInim->setReceptorProjeteis(this);
                //pInim->setListaProjeteis(&listaProjeteis);
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

        void FaseSegunda::adicionarProjetil(Entidades::Projetil* pProj)
        {
            GC.incluirProjetil(pProj);
            lista_ents.incluir(pProj);
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

        void FaseSegunda::executar()
        {
            Fase::executar(); //desenha fundo + entidades
        }

    }
}