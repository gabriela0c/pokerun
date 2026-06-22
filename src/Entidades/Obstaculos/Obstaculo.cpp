#include "Entidades/Obstaculos/Obstaculo.h"

namespace Pokerun{

    namespace Entidades{

        namespace Obstaculos{

           Obstaculo::Obstaculo(const sf::Vector2f tam, const bool d, const bool s):
            Entidade(tam), danoso(d), solido(s) //nao precisa passar vel_y porque é 0 por default, logo ja esta certo
            {

            }

            Obstaculo::~Obstaculo()
            {

            }

            void Obstaculo::salvarDataBuffer()
            {
                Entidade::salvarDataBuffer(); //todos atributos dessa classe são iguais para todos objetos de uma mesma classe, não preciso salvar
            }

            void Obstaculo::carregarDataBuffer(std::istream& is)
            {
                Entidade::carregarDataBuffer(is);
            }

            const bool Obstaculo::isSolido()const
            {
                return solido;
            }

            void Obstaculo::pousar()
            {
                noChao = true;
                vel_y = 0.0f;
            }
        }
    }
}