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

            const bool GerenciadorColisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2)const
            {

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