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

            void GerenciadorColisoes::executar()
            {
                tratarColisoesJogsObstacs();
                tratarColisoesJogsInims();
                tratarColisoesInimsObstacs();
                tratarColisoesInimsInims();
               
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

            //TRANSFORMAR TUDO AQUI EM METODOS ADEQUADOS NAS CLASSES PROVAVELMENTE
            //EX: colidir_por_cima, colidir_de_baixo, colidir_horizontal
            void GerenciadorColisoes::tratarColisoesJogsInims()
            {
                if(!pJogador || Linimigos.empty()){return;}

                for(int i = 0; i < (int)Linimigos.size(); i++){
                    if(Linimigos[i]){
                        bool colisao = verificarColisao(pJogador, Linimigos[i]);
                        if(colisao){
                            sf::FloatRect jog = pJogador->getFig().getGlobalBounds();
                            sf::FloatRect inim = Linimigos[i]->getFig().getGlobalBounds();

                            float overlap_x = std::min(jog.position.x + jog.size.x, inim.position.x + inim.size.x) // menor lado direito
                                - std::max(jog.position.x, inim.position.x); //maior lado esquerdo
                            float overlap_y = std::min(jog.position.y + jog.size.y, inim.position.y + inim.size.y) // parte de baixo mais acima (geografico nao numericamente)
                                - std::max(jog.position.y, inim.position.y); // parte de cima mais abaixo (geografico nao numericamente)

                            if(std::abs(overlap_x) < std::abs(overlap_y)){//se o overlap for menor em x (colisao horizontal), a colisao eh simetrica
                                float dir = (jog.position.x < inim.position.x) ? -1.0f : 1.0f;
                                pJogador->getFig().move({dir * overlap_x / 2.0f, 0.0f}); // cada um mexe metade do overlap
                                Linimigos[i]->getFig().move({-dir * overlap_x / 2.0f, 0.0f});
                            }
                            else{
                                sf::Vector2f jogCentro = {jog.position.x + jog.size.x/2.f, jog.position.y + jog.size.y/2.f};
                                sf::Vector2f inimCentro = {inim.position.x + inim.size.x/2.f, inim.position.y + inim.size.y/2.f};

                                if(jogCentro.y < inimCentro.y){ //jogador estava acima do inimigo, colide com ele e permite pulo
                                pJogador->colisao_posso_pular(Linimigos[i]);
                            } 
                            else{//se o inimigo estava acima ele nao empurra o jogador para baixo, ele que se move para cima, senao o jogador eh empurrado para fora do mapa
                                Linimigos[i]->getFig().move({0.0f, -overlap_y});
                                Linimigos[i]->pousar();
                            }
                        }
                    }
                }
            }
        }

            void GerenciadorColisoes::tratarColisoesInimsObstacs()
            {
                if(Lobstaculos.empty() || Linimigos.empty()){return;}

                std::list<Entidades::Obstaculos::Obstaculo*>::iterator it;
                it = Lobstaculos.begin();

                for(int i = 0; i < (int)Linimigos.size(); i++){
                    if(Linimigos[i]){
                        while(it != Lobstaculos.end()){
                            if(*it){
                                bool colisao = verificarColisao(*it, Linimigos[i]);
                                if(colisao){
                                    sf::Vector2f posAntes = Linimigos[i]->getFig().getPosition();//isso podia ser um metodo da classe personagem talvez
                                    //salva a posição                                               //dai agnt so chama esse metodo antes e dps da colisao e salva em posantes e posdepois

                                    bool deCima = Linimigos[i]->colidir(*it); 
                                    if(deCima){Linimigos[i]->pousar();}

                                    sf::Vector2f posDepois = Linimigos[i]->getFig().getPosition();

                                    if(posAntes.x != posDepois.x)
                                        Linimigos[i]->inverterDirecao();
                                }//inverter posicao para evitar que o inimigo fique colidindo muito com a parede
                            }
                            it++;  
                        }
                        it = Lobstaculos.begin();
                    }
                } 
            }

            void GerenciadorColisoes::tratarColisoesInimsInims()
            {
                if (Linimigos.size() < 2) {return;}
                //para garantir que ele não vai testar a colisão com si mesmo ou testar a colisão entre dois inimigos 
                //mais de uma vez, a lógica faz com que o loop interno comece uma posição a frente do externo
                for (int i = 0; i < (int)Linimigos.size() - 1; i++) 
                //vai do primeiro ao penúltimo inimigo
                {
                    if (Linimigos[i]) 
                    {
                        for (int j = i + 1; j < (int)Linimigos.size(); j++)
                        //começa um a frente
                        {
                            if (Linimigos[j]) 
                            {
                                bool colisao = verificarColisao(Linimigos[i], Linimigos[j]);
                                if (colisao) 
                                {
                                    Linimigos[i]->colidir(Linimigos[j]);
    
                                    sf::Vector2f posI = Linimigos[i]->getFig().getPosition(); //criar esse metodo talvez pra ficar mais encapsulado
                                    sf::Vector2f posJ = Linimigos[j]->getFig().getPosition(); //que nem eu falei ali em cima

                                    //verifica se a colisão é mais horizontal ou vertical, 
                                    //para decidir a direção que cada inimigo deve seguir
                                    if (std::abs(posI.x - posJ.x) > std::abs(posI.y - posJ.y)) 
                                    {
        

                                        if (posI.x < posJ.x) 
                                        {
                                            Linimigos[i]->setDirecao(-1);
                                            Linimigos[j]->setDirecao(1);
                                        } 
                                        else 
                                        {
                                            Linimigos[i]->setDirecao(1);
                                            Linimigos[j]->setDirecao(-1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }    
            }
    
            const bool GerenciadorColisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2)const
            {
                if(!pe1 || !pe2){return false;}
                
                sf::FloatRect bounds1 = (pe1->getFig()).getGlobalBounds();
                sf::FloatRect bounds2 = (pe2->getFig()).getGlobalBounds();
                
                //getGlobalBound retorna as coordenadas do canto superior esquerdo, nao do centro(tambem retorna o tam do corpo)
                sf::Vector2f centro1 = {bounds1.position.x + (bounds1.size.x/2), bounds1.position.y + (bounds1.size.y/2)};
                sf::Vector2f centro2 = {bounds2.position.x + (bounds2.size.x/2), bounds2.position.y + (bounds2.size.y/2)};
                
                sf::Vector2f mediaTam = {(bounds1.size.x + bounds2.size.x)/2 , (bounds1.size.y + bounds2.size.y)/2};
                sf::Vector2f distCentros = {std::abs(centro1.x - centro2.x), std::abs(centro1.y - centro2.y)};
                //std::abs equivalente a fabs, so que sobrecarregado para retornar float, fabs retorna um double
                return (distCentros.x < mediaTam.x && distCentros.y < mediaTam.y);
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
