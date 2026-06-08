#include "Fase.h"
#include <vector>

namespace Pokerun{

    namespace Fases{
 
        Fase::Fase(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2):
        Ente({WIN_SIZE_X, WIN_SIZE_Y}), lista_ents(), GC(), pJogador1(pJog1), pJogador2(pJog2), pChao(new Entidades::Chao()),
        maxBulbasaurs(5) //jog1Ativo(true), jog2Ativo(true)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade*>(pChao));
            pFigura->setPosition({0.0f, 0.0f});//poderia tirar essa linha ja que default é 0,0
            posicoesPlataformas.push_back(pChao->getFig().getGlobalBounds());//garante que plataformas nao vao ficar em cima do chao

            lista_ents.incluir(static_cast<Entidades::Entidade*>(pJogador1));
            GC.setJogador(pJog1);
            //jogador 2 so eh incluido na lista e em GC se forem selecionados 2 jogadores no menu, senao ele eh incluido 2 vezes na lista
            //e o sprite continua aparecendo apos ele morrer. Pro gerenciador de colisoes nao ocorre nenhum bug, so nao eh necessario
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

            //5 posições pré-definidas
            std::vector<sf::Vector2f> posicoesPossiveis;
            posicoesPossiveis.push_back(sf::Vector2f(100.f, 150.f));
            posicoesPossiveis.push_back(sf::Vector2f(300.f, 320.f));
            posicoesPossiveis.push_back(sf::Vector2f(500.f, 200.f));
            posicoesPossiveis.push_back(sf::Vector2f(150.f, 450.f));
            posicoesPossiveis.push_back(sf::Vector2f(400.f, 500.f));

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
                pPlat->getFig().setPosition(posicoesPossiveis[i]); //cada i pega uma posição única

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

        void Fase::desativaJogador(Entidades::Personagens::Jogador* pJog){
            lista_ents.remover(pJog);
            GC.removeJogador(pJog);
        }

        void Fase::ativaJogador(Entidades::Personagens::Jogador* pJog){
            lista_ents.incluir(pJog);
            GC.setJogador(pJog);
            pJog->setAtivo(true);
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

            if(!pJogador2->getAtivo()){
                desativaJogador(pJogador2);
            }
            if(!pJogador1->getAtivo()){
                desativaJogador(pJogador1);
            }
            lista_ents.percorrer();
            GC.executar();
            desenhar();
        }
    }
}