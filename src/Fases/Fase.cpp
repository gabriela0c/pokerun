#include "Fases/Fase.h"
#include <vector>

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
            posicoesPossiveis.push_back(sf::Vector2f(100.f, 150.f));
            posicoesPossiveis.push_back(sf::Vector2f(300.f, 320.f));
            posicoesPossiveis.push_back(sf::Vector2f(500.f, 200.f));
            posicoesPossiveis.push_back(sf::Vector2f(150.f, 440.f));
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
            Ente::desenhar();
            
            auto* pAux = lista_ents.getPrimeiro();
            while(pAux!=nullptr){
                if(pAux->getInfo()){
                    pAux->getInfo()->desenhar();
                }    
            pAux = pAux->getProx();
            }   
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
            removerInativos();//aqui porque o GC.executar() que seta inativos apos a logica de ataque
            desenhar();
        }
    }
}