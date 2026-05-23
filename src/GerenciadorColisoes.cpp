#include "GerenciadorColisoes.h"

namespace Pokerun{

        namespace Gerenciadores{

            GerenciadorColisoes::GerenciadorColisoes():
            pJogador(nullptr), Linimigos(), Lobstaculos()
            {
                Linimigos.clear();
                Lobstaculos.clear();
            }

            GerenciadorColisoes::~GerenciadorColisoes()
            {
                Linimigos.clear();
                Lobstaculos.clear();
                pJogador = nullptr;
            }

            void GerenciadorColisoes::executar()
            {
                tratarColisoesJogsObstacs();
                tratarColisoesJogsInims();
                tratarColisoesInimsObstacs();
               
            }
            
            void GerenciadorColisoes::tratarColisoesJogsObstacs()
            {
                if(!pJogador || Lobstaculos.empty()){return;}

                std::list<Entidades::Obstaculos::Obstaculo*>::iterator it;
                it = Lobstaculos.begin();

                while(it != Lobstaculos.end()){
                    if(*it){
                        //cast desnecessario pois ambas herdam de entidade e o upcasting eh feito automaticamente
                        bool colisao = verificarColisao(pJogador,*it);
                        if (colisao){
                            (*it)->obstaculizar(pJogador);
                        }
                    }
                    it++;
                }
            }


            void GerenciadorColisoes::tratarColisoesJogsInims()
            {
                if(!pJogador || Linimigos.empty()){return;}

                for(int i = 0; i < (int)Linimigos.size(); i++){
                    if(Linimigos[i]){
                        bool colisao = verificarColisao(pJogador, Linimigos[i]);
                        if(colisao){
                            Linimigos[i]->colidir(pJogador);
                            pJogador->colisao_posso_pular(Linimigos[i]);
                            
                        }
                    }
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
                                    Linimigos[i]->colidir(*it); 
                                }//a unica interacao nessecaria entre inimigo e obstaculo eh um n entrar dentro do outro
                            }
                            it++;  
                        }
                        it = Lobstaculos.begin();
                    }
                } 
            }
    
            const bool GerenciadorColisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2)const
            {
                if(!pe1 || !pe2){return false;}
                
                sf::FloatRect bounds1 = (pe1->getCorpo()).getGlobalBounds();
                sf::FloatRect bounds2 = (pe2->getCorpo()).getGlobalBounds();
                //getGlobalBound retorna as coordenadas do canto superior esquerdo, nao do centro(tambem retorna o tam do corpo)
                sf::Vector2f centro1 = {bounds1.position.x + (bounds1.size.x/2), bounds1.position.y + (bounds1.size.y/2)};
                sf::Vector2f centro2 = {bounds2.position.x + (bounds2.size.x/2), bounds2.position.y + (bounds2.size.y/2)};
                
                sf::Vector2f mediaTam = {(bounds1.size.x + bounds2.size.x)/2 , (bounds1.size.y + bounds2.size.y)/2};
                sf::Vector2f distCentros = {std::abs(centro1.x - centro2.x), std::abs(centro1.y - centro2.y)};
                //std::abs equivalente a fabs, so que sobrecarregado para retornar float, fabs retorna um double
                return (distCentros.x < mediaTam.x && distCentros.y < mediaTam.y);
            }
            
            void GerenciadorColisoes::setJogador(Entidades::Personagens::Jogador* pJ)
            {
                if(pJ){
                    pJogador = pJ;
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
