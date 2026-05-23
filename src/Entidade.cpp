#include "Entidade.h"

namespace Pokerun{

    namespace Entidades{
        
        Entidade::Entidade(const sf::Vector2f tam):
        x((float)(rand() % (int)(801 - tam.x))), y((float)(rand() % (int)(601 - tam.y))), corpo(sf::RectangleShape(tam))
        {
            corpo.setPosition({x, y});
        }

        Entidade::~Entidade()
        {

        }

        sf::RectangleShape& Entidade::getCorpo()
        {
            return corpo;
        }

        const sf::RectangleShape& Entidade::getCorpo()const
        {
            return corpo;
        }

        bool Entidade::colidir(Entidade* pOutra)
        {
            
            if(!pOutra) {return false;}

            sf::FloatRect mBounds = corpo.getGlobalBounds(); //myBounds
            sf::FloatRect oBounds = pOutra->getCorpo().getGlobalBounds(); //otherBounds

            float menor_lado_direito  = std::min(mBounds.position.x + mBounds.size.x, oBounds.position.x + oBounds.size.x);
            float maior_lado_esquerdo = std::max(mBounds.position.x, oBounds.position.x);
            //em y, maior/menor se refere a valor numerico(o eixo cresce p baixo) e superior/inferior a posicao fisica na tela
            float menor_lado_inferior = std::min(mBounds.position.y + mBounds.size.y, oBounds.position.y + oBounds.size.y);
            float maior_lado_superior = std::max(mBounds.position.y, oBounds.position.y);
            // tem que subtrair o que esta fisicamente a baixo pelo que esta fisicamente acima pois o sistema de coordenadas eh invertido
            sf::Vector2f overlap = {menor_lado_direito - maior_lado_esquerdo, menor_lado_inferior - maior_lado_superior};

            if(std::abs(overlap.x) < std::abs(overlap.y)){ //empurra pelo eixo de menor sobreposicao
                if(mBounds.position.x < oBounds.position.x){
                    corpo.move({-overlap.x, 0.0f}); //colisao nao veio de cima
                    return false;
                }
                else{
                    corpo.move({ overlap.x, 0.0f}); //tambem nao veio de cima
                    return false;
                }
            }
            else{
                if(mBounds.position.y < oBounds.position.y){//menos eh para cima porque o sistema de coordenadas eh crescente p/baixo no sfml
                    corpo.move({0.0f, -overlap.y}); 
                    return true;//veio de cima
                } 
                else{
                    corpo.move({0.0f,  overlap.y}); //nao veio de cima
                    return false;
                }
            }
        }
    }
}
