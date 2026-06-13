#include "GerenciadorColisoes.h"

namespace Pokerun{

        namespace Gerenciadores{

            GerenciadorColisoes::GerenciadorColisoes():
            pJogador1(nullptr), pJogador2(nullptr), Linimigos(), Lobstaculos(), pChao(nullptr)
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
                pChao = nullptr;
            }

            void GerenciadorColisoes::executar()
            {
                tratarColisoesJogsObstacs();
                tratarColisoesJogsInims();
                tratarColisoesInimsObstacs();
                tratarColisoesInimsInims();
                tratarColisoesJogsJogs();
                tratarColisoesPersChao();
                aplicarAtaqueJog(pJogador1);
                aplicarAtaqueJog(pJogador2);
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
                            if(verificarColisao(pJogador1, Linimigos[i])){
                                colisaoPersonagens(pJogador1, Linimigos[i]);
                                Linimigos[i]->danificar(pJogador1);
                            }
                        }
                        if(pJogador2){
                            if(verificarColisao(pJogador2, Linimigos[i])){
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
                sf::Vector2f centro1 = bounds1.getCenter();
                sf::Vector2f centro2 = bounds2.getCenter();
                
                sf::Vector2f mediaTam = {(bounds1.size.x + bounds2.size.x)/2 , (bounds1.size.y + bounds2.size.y)/2};
                sf::Vector2f distCentros = {std::abs(centro1.x - centro2.x), std::abs(centro1.y - centro2.y)};
                //std::abs equivalente a fabs, so que sobrecarregado para retornar float, fabs retorna um double
                return (distCentros.x < mediaTam.x && distCentros.y < mediaTam.y);
            }

            void GerenciadorColisoes::aplicarAtaqueJog(Entidades::Personagens::Jogador* pJog)
            {
                if(!pJog || Linimigos.empty() || !pJog->getAtacando()){return;}

                pJog->setAtacando(false); //consome o ataque

                if(!pJog->podeAtacar()){return;}//so reinicia o cooldown se ele pode atacar
                pJog->iniciarCooldown();//reinicia o cooldown ja que vai atacar
                
                for(int i = 0; i < (int)Linimigos.size();i++ ){
                    if(Linimigos[i]){
                        if(inRange(pJog, Linimigos[i])){
                            Linimigos[i]->receberDano(1);//criar um dano_jogador para passar aqui talvez
                            std::cout << "tenho " << Linimigos[i]->getNumvidas() << " vidas" <<  std::endl;
                        }
                        if(Linimigos[i]->getNumvidas() <= 0){
                            pJog->operator+=(Linimigos[i]->getValorPontos());
                            Linimigos[i]->setAtivo(false);
                        }
                    }
                }
            }

           const bool GerenciadorColisoes::inRange(Entidades::Personagens::Jogador* pJog, Entidades::Personagens::Inimigo* pInim)const
           {
                sf::FloatRect a = pJog->getFig().getGlobalBounds();
                sf::FloatRect b = pInim->getFig().getGlobalBounds();

                // bordas direita/inferior de cada um (position eh o canto superior esquerdo)
                float aMaxX = a.position.x + a.size.x;
                float aMaxY = a.position.y + a.size.y;
                float bMaxX = b.position.x + b.size.x;
                float bMaxY = b.position.y + b.size.y;

                // distancia real entre os corpos sem considerar o tamanho deles
                float gapX = std::max(0.0f, std::max(a.position.x - bMaxX, b.position.x - aMaxX));//0 eh o min caso eles se sobreponham
                float gapY = std::max(0.0f, std::max(a.position.y - bMaxY, b.position.y - aMaxY));//no eixo (p n ficar -)

                return (gapX <= ALCANCE_ATAQUE_X && gapY <= FAIXA_ATAQUE_Y); 
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
                    sf::Vector2f centro1 = personagem1.getCenter();
                    sf::Vector2f centro2 = personagem2.getCenter();
                                        
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

                sf::Vector2f pCentro = pBounds.getCenter();
                sf::Vector2f eCentro = eBounds.getCenter();
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

            void GerenciadorColisoes::setChao(Entidades::Chao* pCh)
            {
                if(pCh){
                    pChao = pCh;
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

            void GerenciadorColisoes::limparListas()
            {
                Linimigos.clear();
                Lobstaculos.clear();
                pJogador1 = nullptr;
                pJogador2 = nullptr;
            }

           /*void GerenciadorColisoes::incluirProjetil(Entidades::Projetil* pProj)
            {
                if(pProj){
                    Lprojeteis.push_back(pProj);
                }
            }*/

            void GerenciadorColisoes::remover(Entidades::Entidade* pE) //depois adicionar os projeteis aqui também
            {
                if(!pE) { return; }

                if(pJogador1 == pE){ 
                    pJogador1 = nullptr; 
                    return;
                }
                
                if(pJogador2 == pE){ 
                    pJogador2 = nullptr; 
                    return;
                }

               std::vector<Entidades::Personagens::Inimigo*>::iterator it1 = Linimigos.begin();

                while(it1 != Linimigos.end()){
                    if(*it1 == pE){
                        Linimigos.erase(it1);
                        return;
                    }
                    it1++;
                }

                std::list<Entidades::Obstaculos::Obstaculo*>::iterator it2 = Lobstaculos.begin();
                while(it2 != Lobstaculos.end()){
                    if(*it2 == pE) {
                        Lobstaculos.erase(it2);
                        return;
                    }
                    it2++;
                }
            }
    }
}
