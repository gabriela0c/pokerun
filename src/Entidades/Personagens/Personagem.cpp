#include "Entidades/Personagens/Personagem.h"
namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Personagem::Personagem(const sf::Vector2f tam, const sf::Vector2f v, int n_vds):
            Entidade(tam, v.y), vel_x(v.x), noTeto(false), num_vidas(n_vds)
            {

            }

            Personagem::~Personagem()
            {

            }

            float Personagem::getVelX()const{
                return vel_x;
            }

            void Personagem::setVelX(const float vX){
                vel_x = vX;
            }

            void Personagem::pousar()
            {
                noChao = true;
                vel_y = 0.0f;
            }

            void Personagem::setNoTeto(const bool nT)
            {
                noTeto = nT;

                //se bater no teto, zera a velocidade vertical imediatamente
                if (noTeto && vel_y < 0.0f)
                    vel_y = 0.0f;
            }

            void Personagem::setNoChao(const bool nC)
            {
                noChao = nC;
            }

            void Personagem::operator--()
            {
                if(num_vidas > 0){num_vidas--;}
            }

            void Personagem::salvarDataBuffer()
            {
                Entidade::salvarDataBuffer();
                buffer << " " << vel_x << " " << noChao << " " << noTeto << " " << num_vidas;
            }

            void Personagem::carregarDataBuffer(std::istream& is)
            {
                Entidade::carregarDataBuffer(is);
                is >> vel_x >> noChao >> noTeto >> num_vidas;
            }

            int Personagem::getNumvidas()const
            {
                return num_vidas;
            }
        }
    }
}


