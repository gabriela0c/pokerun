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
            Entidades::Personagens::Charizard* pChar = nullptr;
            int n = rand() % 2 + 3; //cria de 3 a 4 inimigos - tabela 1 N5
            for(int i = 0; i < n; i++){
                pChar = new Entidades::Personagens::Charizard();
                Entidades::Projetil* pProj = new Entidades::Projetil();
                pChar->adicionarProjetil(pProj);
                pProj->setCharizard(pChar);
                pProj->getFig().setPosition(pChar->getPosition());
                adicionarInimigos(pChar);
                adicionarProjetil(pProj);
                pChar = nullptr;
            }
        }
        
        void FaseSegunda::criarFogos()
        {
            //mínimo 3 e máximo 5 
            int n = rand() % (maxFogos - 2) + 3;

            for(int i = 0; i < n; i++)
            {
                Entidades::Obstaculos::Fogo* pFogo = new Entidades::Obstaculos::Fogo();
                
                colocaNaPlataforma(pFogo);

                adicionarObstaculos(pFogo);
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