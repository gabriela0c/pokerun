#include "GerenciadorColisoes.h"
#include "Fase.h"

namespace Pokerun{

        namespace Gerenciadores{

            GerenciadorColisoes::GerenciadorColisoes():
            pJogador1(nullptr), pJogador2(nullptr), Linimigos(), Lobstaculos(), pFaseAtual(nullptr)
            {
                Linimigos.clear();
                Lobstaculos.clear();
            }

            GerenciadorColisoes::~GerenciadorColisoes()
            {
                Linimigos.clear();
                Lobstaculos.clear();
                pJogador1 = nullptr;
                pJogador2 = nullptr;
                pFaseAtual = nullptr;
            }

            void GerenciadorColisoes::executar()
            {
                tratarColisoesJogsObstacs();
                tratarColisoesJogsInims();
                tratarColisoesInimsObstacs();
                tratarColisoesInimsInims();
                tratarColisoesJogsJogs();
                tratarColisoesPersChao();
                //tratarColisoesProjeteis();
            }
            
            void GerenciadorColisoes::tratarColisoesJogsObstacs()
            {
                if(Lobstaculos.empty()){return;}

                std::list<Entidades::Obstaculos::Obstaculo*>::iterator it;
                it = Lobstaculos.begin();

                while(it != Lobstaculos.end()){
                    if(*it){
                        //cast desnecessario pois ambas herdam de entidade e o upcasting eh feito automaticamente
                        if(pJogador1){
                            bool colisao1 = verificarColisao(pJogador1,*it);
                            if(colisao1){
                                if((*it)->isSolido()){
                                    colisaoPersonagemEntidade(pJogador1, (*it));
                                }
                                (*it)->obstaculizar(pJogador1);        
                            }
                        }
                        
                        if(pJogador2){
                            bool colisao2 = verificarColisao(pJogador2,*it);
                            if(colisao2){
                                if((*it)->isSolido()){
                                    colisaoPersonagemEntidade(pJogador2, (*it));
                                }
                                (*it)->obstaculizar(pJogador2);
                            }
                        }
                    }
                    it++;
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
                                    colisaoPersonagemEntidade(Linimigos[i], (*it));
                                }
                            }
                            it++;  
                        }
                        it = Lobstaculos.begin();
                    }
                } 
            }
        

            void GerenciadorColisoes::tratarColisoesJogsInims()
            {
                if(Linimigos.empty()){return;}

                for(int i = 0; i < (int)Linimigos.size(); i++){
                    if(Linimigos[i]){
                        if(pJogador1){
                            bool colisao1 = verificarColisao(pJogador1, Linimigos[i]);
                            if(colisao1){
                                colisaoPersonagens(pJogador1, Linimigos[i]);
                                Linimigos[i]->danificar(pJogador1);
                            }
                        }

                        if(pJogador2){//existe sim a possibilidade do jogo nao ter jogador 2
                            bool colisao2 = verificarColisao(pJogador2, Linimigos[i]);
                            if(colisao2){
                                colisaoPersonagens(pJogador2, Linimigos[i]);
                                Linimigos[i]->danificar(pJogador2);
                            }
                        }
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
                                    colisaoPersonagens(Linimigos[i], Linimigos[j]);
                                }
                            }
                        }
                    }
                }    
            }

            void GerenciadorColisoes::tratarColisoesJogsJogs()
            {
                if (!pJogador1 || !pJogador2) {return;}

                bool colisao = verificarColisao(pJogador1, pJogador2);
                
                if(colisao){
                    colisaoPersonagens(pJogador1, pJogador2);
                }
            }

            void GerenciadorColisoes::tratarColisoesPersChao()
            {
                if(!pFaseAtual){return;}
                Entidades::Chao* pChao = pFaseAtual->getChao();

                if(!pChao){return;}//nao pode checar jogadores aqui porque tem como um morrer e dai a funcao nao roda e inimigos nao colidem com o chao

                //colisoes com o chao sempre vem de cima, entao devo chamar pousar sempre
                for(int i = 0; i < (int)Linimigos.size(); i++){
                    if(Linimigos[i]){
                        if(verificarColisao(pChao, Linimigos[i])){
                            colisaoPersonagemEntidade(Linimigos[i], pChao);
                        }
                    }
                }

                if(pJogador1){
                    if(verificarColisao(pChao, pJogador1)){
                        colisaoPersonagemEntidade(pJogador1, pChao);
                    }
                }
                if(pJogador2){
                    if(verificarColisao(pChao, pJogador2)){
                        colisaoPersonagemEntidade(pJogador2, pChao);
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

            void GerenciadorColisoes::colisaoPersonagens(Entidades::Personagens::Personagem* p1, Entidades::Personagens::Personagem* p2)
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
                        p1->pousar();              //pular quando esta em cima do outro para evitar pulo duplo                                         
                    }
                    else{
                        p2->getFig().move({0.0f, -overlap_y});
                        p2->pousar();
                    }
                }
            }
            //Pensei em fazer colidirComObstaculos, mas como chao nao eh obstaculo dai teria que haver uma funcao com essa mesma logica so que para chao
            void GerenciadorColisoes::colisaoPersonagemEntidade(Entidades::Personagens::Personagem* pP, Entidades::Entidade* pE)
            {
                sf::FloatRect pBounds = pP->getFig().getGlobalBounds(); //personagem bounds
                sf::FloatRect eBounds = pE->getFig().getGlobalBounds(); //entidade bounds

                float menor_lado_direito  = std::min(pBounds.position.x + pBounds.size.x, eBounds.position.x + eBounds.size.x);
                float maior_lado_esquerdo = std::max(pBounds.position.x, eBounds.position.x);
                //em y, maior/menor se refere a valor numerico(o eixo cresce p baixo) e superior/inferior a posicao fisica na tela

                float menor_lado_inferior = std::min(pBounds.position.y + pBounds.size.y, eBounds.position.y + eBounds.size.y);
                float maior_lado_superior = std::max(pBounds.position.y, eBounds.position.y);
                // tem que subtrair o que esta fisicamente a baixo pelo que esta fisicamente acima pois o sistema de coordenadas eh invertido

                sf::Vector2f pCentro = {pBounds.position.x + pBounds.size.x / 2.0f, pBounds.position.y + pBounds.size.y / 2.0f};
                sf::Vector2f eCentro = {eBounds.position.x + eBounds.size.x / 2.0f, eBounds.position.y + eBounds.size.y / 2.0f};
                //calculo dos centros para verificar a direcao da colisao

                sf::Vector2f overlap = {menor_lado_direito - maior_lado_esquerdo, menor_lado_inferior - maior_lado_superior};

                if(std::abs(overlap.x) < std::abs(overlap.y))
                { 
                //compara os centros no eixo X
                    if(pCentro.x < eCentro.x)
                    {
                        pP->getFig().move({-overlap.x, 0.0f}); 
                        //empurra para a esquerda
                    }
                
                    else
                    {
                        pP->getFig().move({ overlap.x, 0.0f}); 
                        //empurra para a direita
                    }
                }

                else
                {
                    //compara os centros no eixo Y
                    if(pCentro.y < eCentro.y)
                    {
                        pP->getFig().move({0.0f, -overlap.y}); //empurra para cima
                        pP->pousar();
                    } 

                    else
                    {   //empurra para baixo
                        pP->getFig().move({0.0f,  overlap.y}); 
                        pP->setNoTeto(true);
                    }
                }
            }
            
            void GerenciadorColisoes::setJogador(Entidades::Personagens::Jogador* pJog)
            {
                if(pJog){
                    if(pJog->getEhJogador1()){pJogador1 = pJog;}
                    else{pJogador2 = pJog;}
                }
            }

            void GerenciadorColisoes::setFase(Fases::Fase* pF)
            {
                if(pF){
                    pFaseAtual = pF;
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

           /*void GerenciadorColisoes::incluirProjetil(Entidades::Projetil* pProj)
            {
                if(pProj){
                    Lprojeteis.push_back(pProj);
                }
            }*/

            void GerenciadorColisoes::removeJogador(Entidades::Personagens::Jogador* pJog){
                if(pJog){
                    if(pJog->getEhJogador1()){pJogador1 = nullptr;}
                    else{pJogador2 = nullptr;}
                }
            }
    }
}
