#include "GerenciadorColisoes.h"
#include "FasePrimeira.h"

namespace Pokerun{

        namespace Gerenciadores{

            GerenciadorColisoes::GerenciadorColisoes():
            pJogador1(nullptr), pJogador2(nullptr), Linimigos(), Lobstaculos(), pFase1(nullptr)
            {
                Linimigos.clear();
                Lobstaculos.clear();
            }

            GerenciadorColisoes::~GerenciadorColisoes()
            {
                Linimigos.clear();
                Lobstaculos.clear();
                pJogador1 = nullptr;
                pJogador2 = nullptr;
                pFase1 = nullptr;
            }

            void GerenciadorColisoes::executar()
            {
                tratarColisoesJogsObstacs();
                tratarColisoesJogsInims();
                tratarColisoesInimsObstacs();
                tratarColisoesInimsInims();
                tratarColisoesJogsJogs();
                tratarColisoesPersChao();
            }
            
            void GerenciadorColisoes::tratarColisoesJogsObstacs()
            {
                if(!pJogador1 || Lobstaculos.empty()){return;}

                std::list<Entidades::Obstaculos::Obstaculo*>::iterator it;
                it = Lobstaculos.begin();

                while(it != Lobstaculos.end()){
                    if(*it){
                        //cast desnecessario pois ambas herdam de entidade e o upcasting eh feito automaticamente
                        bool colisao1 = verificarColisao(pJogador1,*it);
                        if(colisao1){
                            (*it)->obstaculizar(pJogador1);
                        }
                        
                        if(pJogador2){
                            bool colisao2 = verificarColisao(pJogador2,*it);
                            if(colisao2){
                                (*it)->obstaculizar(pJogador2);
                            }
                        }
                    }
                    it++;
                }
            }

             void GerenciadorColisoes::tratarColisoesInimsObstacs()
            {
                if(Lobstaculos.empty() || Linimigos.empty()){return;}

                std::list<Entidades::Obstaculos::Obstaculo*>::iterator it;
                it = Lobstaculos.begin();

                for(int i = 0; i < (int)Linimigos.size(); i++){
                    if(Linimigos[i]){
                        while(it != Lobstaculos.end()){
                            if(*it){
                                bool colisao = verificarColisao(*it, Linimigos[i]);
                                if(colisao){
                                    bool deCima = Linimigos[i]->colidir(*it); 
                                    if(deCima){Linimigos[i]->pousar();}
                                }
                            }
                            it++;  
                        }
                        it = Lobstaculos.begin();
                    }
                } 
            }
        

            void GerenciadorColisoes::tratarColisoesJogsInims()
            {
                if(!pJogador1 || Linimigos.empty()){return;}

                for(int i = 0; i < (int)Linimigos.size(); i++){
                    if(Linimigos[i]){
                        bool colisao1 = verificarColisao(pJogador1, Linimigos[i]);
                        if(colisao1){
                            Linimigos[i]->danificar(pJogador1);
                        }

                        if(pJogador2){//existe sim a possibilidade do jogo nao ter jogador 2
                            bool colisao2 = verificarColisao(pJogador2, Linimigos[i]);
                            if(colisao2){
                                Linimigos[i]->danificar(pJogador2);
                            }
                        }
                    }
                }
            }        

            void GerenciadorColisoes::tratarColisoesInimsInims()
            {
                if (Linimigos.size() < 2) {return;}
                //para garantir que ele não vai testar a colisão com si mesmo ou testar a colisão entre dois inimigos 
                //mais de uma vez, a lógica faz com que o loop interno comece uma posição a frente do externo
                for (int i = 0; i < (int)Linimigos.size() - 1; i++) 
                //vai do primeiro ao penúltimo inimigo
                {
                    if (Linimigos[i]) 
                    {
                        for (int j = i + 1; j < (int)Linimigos.size(); j++)
                        //começa um a frente
                        {
                            if (Linimigos[j]) 
                            {
                                bool colisao = verificarColisao(Linimigos[i], Linimigos[j]);
                                if (colisao) 
                                {
                                    Entidades::Personagens::Personagem::colisaoPersonagem(Linimigos[i], Linimigos[j]);
                                }
                            }
                        }
                    }
                }    
            }

            void GerenciadorColisoes::tratarColisoesJogsJogs()
            {
                if (!pJogador1 || !pJogador2) {return;}

                bool colisao = verificarColisao(pJogador1, pJogador2);
                
                if(colisao){
                Entidades::Personagens::Personagem::colisaoPersonagem(pJogador1, pJogador2);
                }
            }

            void GerenciadorColisoes::tratarColisoesPersChao()
            {
                Entidades::Chao* pChao = pFase1->getChao();

                if(!pChao || !pJogador1){return;}
                //colisoes com o chao sempre vem de cima, entao devo chamar pousar sempre
                for(int i = 0; i < (int)Linimigos.size(); i++){
                    if(Linimigos[i]){
                        if(verificarColisao(pChao, Linimigos[i])){
                            Linimigos[i]->colidir(pChao);
                            Linimigos[i]->pousar();
                        }
                    }
                }

                if(verificarColisao(pChao, pJogador1)){
                    pJogador1->colidir(pChao);
                    pJogador1->pousar();
                }
                if(verificarColisao(pChao, pJogador2)){
                    pJogador2->colidir(pChao);
                    pJogador2->pousar();
                }
            }
        
    
            const bool GerenciadorColisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2)const
            {
                if(!pe1 || !pe2){return false;}
                
                sf::FloatRect bounds1 = (pe1->getFig()).getGlobalBounds();
                sf::FloatRect bounds2 = (pe2->getFig()).getGlobalBounds();
                
                //getGlobalBound retorna as coordenadas do canto superior esquerdo, nao do centro(tambem retorna o tam do corpo)
                sf::Vector2f centro1 = {bounds1.position.x + (bounds1.size.x/2), bounds1.position.y + (bounds1.size.y/2)};
                sf::Vector2f centro2 = {bounds2.position.x + (bounds2.size.x/2), bounds2.position.y + (bounds2.size.y/2)};
                
                sf::Vector2f mediaTam = {(bounds1.size.x + bounds2.size.x)/2 , (bounds1.size.y + bounds2.size.y)/2};
                sf::Vector2f distCentros = {std::abs(centro1.x - centro2.x), std::abs(centro1.y - centro2.y)};
                //std::abs equivalente a fabs, so que sobrecarregado para retornar float, fabs retorna um double
                return (distCentros.x < mediaTam.x && distCentros.y < mediaTam.y);
            }
            
            void GerenciadorColisoes::setJogador1(Entidades::Personagens::Jogador* pJog1)
            {
                if(pJog1){
                    pJogador1 = pJog1;
                }
            }

            void GerenciadorColisoes::setJogador2(Entidades::Personagens::Jogador* pJog2)
            {
                if(pJog2){
                    pJogador2 = pJog2;
                }
            }

            void GerenciadorColisoes::setFase1(Fases::FasePrimeira* pF1)
            {
                if(pF1){
                    pFase1 = pF1;
                }
            }

            void GerenciadorColisoes::incluirInimigo(Entidades::Personagens::Inimigo* pI)
            {
                if(pI){
                    Linimigos.push_back(pI);
                }
            }

            void GerenciadorColisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* pO)
            {
                if(pO){
                    Lobstaculos.push_back(pO);
                }
            }
    }
}
