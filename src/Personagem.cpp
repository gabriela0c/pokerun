#include "Personagem.h"
namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Personagem::Personagem(const sf::Vector2f tam, const sf::Vector2f v, const ID i):
            Entidade(tam, i), vel(v), noChao(false), gravidade(GRAVIDADE), relogio(), dt(0.0f), num_vidas(-1)
            {

            }

            Personagem::~Personagem()
            {

            }

            void Personagem::aplicarGravidade()
            {
                dt = relogio.restart().asSeconds();
    
                if (dt > 0.1f) 
                    dt = 0.1f;
                
                vel.y += gravidade * dt;
                if(vel.y > VEL_TERM){vel.y = VEL_TERM;}

                pFigura->move({0.0f, vel.y * dt});
            }

            sf::Vector2f Personagem::getVel()const{
                return vel;
            }

            void Personagem::setVel(sf::Vector2f v){
                vel = v;
            }

            void Personagem::colisaoPersonagem(Personagem* p1, Personagem* p2)
            {
                sf::FloatRect personagem1 = p1->getFig().getGlobalBounds();
                sf::FloatRect personagem2 = p2->getFig().getGlobalBounds();

                float overlap_x = std::min(personagem1.position.x + personagem1.size.x, personagem2.position.x + personagem2.size.x) - std::max(personagem1.position.x, personagem2.position.x);
                float overlap_y = std::min(personagem1.position.y + personagem1.size.y, personagem2.position.y + personagem2.size.y) - std::max(personagem1.position.y, personagem2.position.y);

                if(std::abs(overlap_x) < std::abs(overlap_y)){//colisao horizontal
                    float dir = (personagem1.position.x < personagem2.position.x) ? -1.0f : 1.0f;
                    //tenho que saber quem esta mais a esquerda
                    p1->getFig().move({(dir * overlap_x) / 2, 0.0f});
                    p2->getFig().move({(-dir * overlap_x) / 2, 0.0f});
                }
                else{
                    sf::Vector2f centro1 = {personagem1.position.x + (personagem1.size.x / 2), personagem1.position.y + (personagem1.size.y / 2)};
                    sf::Vector2f centro2 = {personagem2.position.x + (personagem2.size.x / 2), personagem2.position.y + (personagem2.size.y / 2)};
                                        
                    if(centro1.y < centro2.y){ //se 1 estava acima de 2
                        p1->getFig().move({0.0f, -overlap_y});
                        if(p2->getID() != ID::JOGADOR){//verificacao para garantir que um jogador nao consiga
                            p1->pousar();              //pular quando esta em cima do outro para evitar pulo duplo
                        }                                              
                    }
                    else{
                        p2->getFig().move({0.0f, -overlap_y});
                        if(p1->getID() != ID::JOGADOR){
                            p2->pousar();
                        }
                    }
                }
            }

            void Personagem::pousar()
            {
                noChao = true;
                vel.y = 0.0f;
            }

             void Personagem::operator--()
             {
                if(num_vidas > 0){num_vidas--;}
            }

            int Personagem::getNumvidas()const
            {
                return num_vidas;
            }
        }
    }
}


