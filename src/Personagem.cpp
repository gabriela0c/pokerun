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
                    //quetão de segurança em relação a travamentos 
    
                vel.y += gravidade * dt;

                corpo.move({0.0f, vel.y * dt});
            }

            sf::Vector2f Personagem::getVel()const{
                return vel;
            }
        }
    }
}


