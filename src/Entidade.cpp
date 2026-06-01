#include "Entidade.h"

namespace Pokerun{

    namespace Entidades{
        
        Entidade::Entidade(const sf::Vector2f tam, const ID i): 
        Ente(tam, i),
        x((float)(rand() % (int)(801 - tam.x))), y((float)(rand() % (int)(601 - tam.y))), noTeto(false)
        {
            pFigura->setPosition({x, y});
        }

        Entidade::~Entidade()
        {

        }

        bool Entidade::colidir(Entidade* pOutra){
            sf::FloatRect mBounds = getFig().getGlobalBounds();
            sf::FloatRect oBounds = pOutra->getFig().getGlobalBounds();

            float menor_lado_direito  = std::min(mBounds.position.x + mBounds.size.x, oBounds.position.x + oBounds.size.x);
            float maior_lado_esquerdo = std::max(mBounds.position.x, oBounds.position.x);
            //em y, maior/menor se refere a valor numerico(o eixo cresce p baixo) e superior/inferior a posicao fisica na tela

            float menor_lado_inferior = std::min(mBounds.position.y + mBounds.size.y, oBounds.position.y + oBounds.size.y);
            float maior_lado_superior = std::max(mBounds.position.y, oBounds.position.y);
            // tem que subtrair o que esta fisicamente a baixo pelo que esta fisicamente acima pois o sistema de coordenadas eh invertido

            sf::Vector2f mCentro = {mBounds.position.x + mBounds.size.x / 2.0f, mBounds.position.y + mBounds.size.y / 2.0f};
            sf::Vector2f oCentro = {oBounds.position.x + oBounds.size.x / 2.0f, oBounds.position.y + oBounds.size.y / 2.0f};
            //calculo dos centros para verificar a direcao da colisao

            sf::Vector2f overlap = {menor_lado_direito - maior_lado_esquerdo, menor_lado_inferior - maior_lado_superior};

            if(std::abs(overlap.x) < std::abs(overlap.y))
            { 
            //compara os centros no eixo X
                if(mCentro.x < oCentro.x)
                {
                    pFigura->move({-overlap.x, 0.0f}); 
                    //empurra para a esquerda
                    return false;
                }
                
                else
                {
                    pFigura->move({ overlap.x, 0.0f}); 
                    //empurra para a direita
                  return false;
                }
            }

            else
            {
                //compara os centros no eixo Y
                if(mCentro.y < oCentro.y)
                {
                    pFigura->move({0.0f, -overlap.y}); 
                    //empurra para cima
                    return true;
                } 

                else
                {
                    pFigura->move({0.0f,  overlap.y}); 
                    //empurra para baixo
                    noTeto = true;
                    return false;
                }
            }
        }
    }
}