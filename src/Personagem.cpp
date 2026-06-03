#include "Personagem.h"
namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Personagem::Personagem(const sf::Vector2f tam, const sf::Vector2f v, int n_vds):
            Entidade(tam), vel(v), noChao(false), noTeto(false), gravidade(GRAVIDADE), relogio(), dt(0.0f), num_vidas(n_vds)
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

                pFigura->move({0.0f, vel.y*dt});
            }

            sf::Vector2f Personagem::getVel()const{
                return vel;
            }

            void Personagem::setVel(sf::Vector2f v){
                vel = v;
            }

            void Personagem::pousar()
            {
                noChao = true;
                vel.y = 0.0f;
            }

            void Personagem::setNoTeto(const bool nT)
            {
                noTeto = nT;
            }

            void Personagem::setNoChao(const bool nC)
            {
                noChao = nC;
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


