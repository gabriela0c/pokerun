#include "Fase.h"

namespace Pokerun{

    namespace Fases{

        Fase::Fase(Entidades::Personagens::Jogador* pJog):
        Ente(), lista_ents(), GC(), pJogador(pJog)
        {
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
            for(int i = 0; i < 3; i++){
                pInim = new Entidades::Personagens::Inimigo();
                pInim->setJogador(pJogador);
                lista_ents.incluir(static_cast<Entidades::Entidade*>(pInim));
                GC.incluirInimigo(pInim);
                pInim = nullptr;
            }
        }

        void Fase::criarPlataformas()
        {
            Entidades::Obstaculos::Plataforma* pPlat = nullptr;
            for(int i = 0; i < 3; i++){
                pPlat = new Entidades::Obstaculos::Plataforma();
                lista_ents.incluir(static_cast<Entidades::Entidade*>(pPlat));
                GC.incluirObstaculo(pPlat); 
                pPlat = nullptr;
            }
            //DEPOIS REMOVER ISSO E COLOCAR O CHAO COMO O PFIG DE FASE
            pPlat = new Entidades::Obstaculos::Plataforma({0.0f, WIN_SIZE_Y - 30.0f}, {WIN_SIZE_X, 30.0f}); 
            //alteração do chão para que ele apareça na tela: antes eu não estava vendo, ai mudei a forma com que ele é criado e a cor
            lista_ents.incluir(pPlat);
            GC.incluirObstaculo(pPlat);

            //parede invisível na esquerda
            Entidades::Obstaculos::Plataforma* pParedeEsq = new Entidades::Obstaculos::Plataforma({-100.0f, 0.0f}, {100.0f, WIN_SIZE_Y});
            lista_ents.incluir(pParedeEsq);
            GC.incluirObstaculo(pParedeEsq);

            //parede invisível na direita
            Entidades::Obstaculos::Plataforma* pParedeDir = new Entidades::Obstaculos::Plataforma({WIN_SIZE_X, 0.0f}, {100.0f, WIN_SIZE_Y});
            lista_ents.incluir(pParedeDir);
            GC.incluirObstaculo(pParedeDir);
            //criei as pareces pq toda hora o jogador caia/sumia da tela
        }

        void Fase::desenhar()
        {
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