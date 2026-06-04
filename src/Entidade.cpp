#include "Entidade.h"

namespace Pokerun{

    namespace Entidades{
        
        Entidade::Entidade(const sf::Vector2f tam, const float vY): 
        Ente(tam),
        x((float)(rand() % (int)(801 - tam.x))), y((float)(rand() % (int)(601 - tam.y))), vel_y(vY), gravidade(GRAVIDADE), relogio(), dt(0.0f)
        {
            pFigura->setPosition({x, y});
        }

        Entidade::~Entidade()
        {

        }

         void Entidade::aplicarGravidade()
         {
            dt = relogio.restart().asSeconds();
    
            if (dt > 0.1f) 
                dt = 0.1f;
                
            vel_y += gravidade * dt;
            if(vel_y > VEL_TERM){vel_y = VEL_TERM;}

            pFigura->move({0.0f, vel_y*dt});
         }

         void Entidade::antiGravidade()
         {//nao tem um clock.restart pq senao ia ser quase 0 o dt, tem que usar o mesmo dt do aplicarGravidade
            pFigura->move({0.0f, - vel_y*dt});//desfaz o movimento p/baixo que a gravidade causou
        
            vel_y = 0; //zera velocidade para ela nao acumular
         }

         float Entidade::calcularDirecaoKnockback(sf::Vector2f posAlvo, sf::Vector2f posFonte)
         {
            float dirX = posAlvo.x - posFonte.x;
            return (dirX >= 0.0f) ? 1.0f : -1.0f;
         }
    }
}