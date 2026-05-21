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

            }

            void GerenciadorColisoes::tratarColisoesInimsObstacs()
            {

            }

            const bool GerenciadorColisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2)const
            {
                if(!pe1 || !pe2){return false;}
                
                sf::Vector2f pos1 = ((pe1->getCorpo()).getPosition());
                sf::Vector2f pos2 = ((pe2->getCorpo()).getPosition());

                sf::Vector2f tam1 = (pe1->getCorpo()).getSize();
                sf::Vector2f tam2 = (pe2->getCorpo()).getSize();
                //getCorpo retorna a posicao do canto superior esquerdo, nao do centro
                sf::Vector2f centro1 = {pos1.x + (tam1.x/2), pos1.y + (tam1.y/2)};
                sf::Vector2f centro2 = {pos2.x + (tam2.x/2), pos2.y + (tam2.y/2)};
                
                sf::Vector2f mediaTam = {(tam1.x + tam2.x)/2 , (tam1.y + tam2.y)/2};
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