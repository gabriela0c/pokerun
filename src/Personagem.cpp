#include "Personagem.h"
namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Personagem::Personagem(const sf::Vector2f tam, const sf::Vector2f v):
            Entidade(tam), vel(v), noChao(false),gravidade(GRAVIDADE), relogio(), dt(0.0f)
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

                corpo.move({0.0f, vel.y * dt});
            }

            sf::Vector2f Personagem::getVel()const{
                return vel;
            }

            void Personagem::setVel(sf::Vector2f v){
                vel = v;
            }
        }
    }
}


