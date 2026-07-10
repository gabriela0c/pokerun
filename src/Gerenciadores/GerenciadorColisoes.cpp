#include "Gerenciadores/GerenciadorColisoes.h"
#include <cmath>
#include <algorithm>

namespace Pokerun{
    namespace Gerenciadores{

        GerenciadorColisoes::GerenciadorColisoes():
        pJogador1(nullptr), pJogador2(nullptr), Linimigos(), Lobstaculos(), setProjeteis(), pChao(nullptr),
        limiteEsquerdo(0.0f), limiteDireito(WIN_SIZE_X)
        {
            Linimigos.clear();
            Lobstaculos.clear();
            setProjeteis.clear();
        }

        GerenciadorColisoes::~GerenciadorColisoes()
        {
            Linimigos.clear();
            Lobstaculos.clear();
            setProjeteis.clear();
            pJogador1 = nullptr;
            pJogador2 = nullptr;
            pChao = nullptr;
        }

        const bool GerenciadorColisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const
        {
            if(!pe1 || !pe2){ return false; }
            if(!pe1->getAtivo() || !pe2->getAtivo()) {return false;} //se um deles não esta ativo não quero que colidam

            sf::FloatRect b1 = pe1->getFig().getGlobalBounds();
            sf::FloatRect b2 = pe2->getFig().getGlobalBounds();

            sf::Vector2f centro1(b1.position.x + b1.size.x / 2.0f, b1.position.y + b1.size.y / 2.0f);
            sf::Vector2f centro2(b2.position.x + b2.size.x / 2.0f, b2.position.y + b2.size.y / 2.0f);

            sf::Vector2f mediaTam((b1.size.x + b2.size.x) / 2.0f, (b1.size.y + b2.size.y) / 2.0f);
            sf::Vector2f dist(std::abs(centro1.x - centro2.x), std::abs(centro1.y - centro2.y));

            return (dist.x < mediaTam.x && dist.y < mediaTam.y);
        }

        void GerenciadorColisoes::tratarColisoesJogsObstacs()
        {
            if(Lobstaculos.empty()){return;}

            std::list<Entidades::Obstaculos::Obstaculo*>::iterator it;
            it = Lobstaculos.begin();

            while(it != Lobstaculos.end()){
                if(*it){
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

                    if(pJogador2){
                        bool colisao2 = verificarColisao(pJogador2, Linimigos[i]);
                        if(colisao2){
                            colisaoPersonagens(pJogador2, Linimigos[i]);
                            Linimigos[i]->danificar(pJogador2);
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
                            if(colisao && (*it)->isSolido()){
                                colisaoPersonagemEntidade(Linimigos[i], (*it));
                            }
                        }
                        it++;  
                    }
                }
                it = Lobstaculos.begin();
            } 
        }

        void GerenciadorColisoes::tratarColisoesInimsInims()
        {
            if (Linimigos.size() < 2) {return;}
            for (int i = 0; i < (int)Linimigos.size() - 1; i++) 
            {
                if (Linimigos[i]) 
                {
                    for (int j = i + 1; j < (int)Linimigos.size(); j++)
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
            if(!pChao){return;}

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

            std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = Lobstaculos.begin();
            while (it != Lobstaculos.end())
            {
                if (*it && verificarColisao(pChao, *it))
                {
                    (*it)->pousar();
                    //reposiciona o obstaculo em cima do chao
                    sf::FloatRect b = (*it)->getFig().getGlobalBounds();
                    sf::FloatRect chao = pChao->getFig().getGlobalBounds();
                    (*it)->getFig().setPosition({b.position.x, chao.position.y - b.size.y});
                    (*it)->sincronizarPosicao();
                }
                it++;
            }
        }

        void GerenciadorColisoes::tratarColisoesProjeteis()
        {
            if(setProjeteis.empty()){ return; }

            std::set<Entidades::Projetil*>::iterator itProj;

            for(itProj = setProjeteis.begin(); itProj != setProjeteis.end(); itProj++)
            {
                Entidades::Projetil* pProj = (*itProj);
                if(!pProj || !pProj->getVoando()){ continue; }

                std::list<Entidades::Obstaculos::Obstaculo*>::const_iterator it = Lobstaculos.begin();
                while(it != Lobstaculos.end() && pProj->getVoando())
                {
                    if(*it && (*it)->isSolido() && verificarColisao(pProj, *it)){
                        pProj->guardar();
                    }
                    it++;
                }

                if(pProj->getVoando() && verificarColisao(pProj, pChao)){
                    pProj->guardar();
                }

                if(pProj->getVoando() && pJogador1 && pJogador1->getAtivo() && verificarColisao(pProj, pJogador1))
                {
                    if(!pJogador1->getInvencivel()){
                        for(int d = 0; d < pProj->getDano(); d++){
                            pJogador1->operator--();
                        }
                        pJogador1->ativarInvencibilidade();
                    }
                    pProj->guardar();
                }

                if(pProj->getVoando() && pJogador2 && pJogador2->getAtivo() && verificarColisao(pProj, pJogador2))
                {
                    if(!pJogador2->getInvencivel()){
                        for(int d = 0; d < pProj->getDano(); d++){
                            pJogador2->operator--();
                        }
                        pJogador2->ativarInvencibilidade();
                    }
                    pProj->guardar();
                }
            }
        }

        void GerenciadorColisoes::tratarColisoesParedes()
        {
            tratarParedePersonagem(pJogador1);
            tratarParedePersonagem(pJogador2);

            for (int i = 0; i < (int)Linimigos.size(); i++)
                tratarParedePersonagem(Linimigos[i]);
        }

        void GerenciadorColisoes::tratarParedePersonagem(Entidades::Personagens::Personagem* pP)
        {
            if (!pP) { return; }
            sf::FloatRect b = pP->getFig().getGlobalBounds();
            if (b.position.x < limiteEsquerdo)
                pP->getFig().setPosition(sf::Vector2f(limiteEsquerdo, b.position.y));
            else if (b.position.x + b.size.x > limiteDireito)
                pP->getFig().setPosition(sf::Vector2f(limiteDireito - b.size.x, b.position.y));
        }

        void GerenciadorColisoes::aplicarAtaqueJog(Entidades::Personagens::Jogador* pJog)
        {
            if(!pJog || Linimigos.empty() || !pJog->getAtacando()){return;}

            pJog->setAtacando(false); 

            if(!pJog->podeAtacar()){return;}
            pJog->iniciarCooldown();
            
            for(int i = 0; i < (int)Linimigos.size();i++ ){
                if(Linimigos[i]){
                    if(inRange(pJog, Linimigos[i])){
                        Linimigos[i]->receberDano(1);
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
            if(!pJog->getAtivo() || !pInim->getAtivo()) {return false;}
           
            sf::FloatRect a = pJog->getFig().getGlobalBounds();
            sf::FloatRect b = pInim->getFig().getGlobalBounds();

            float aMaxX = a.position.x + a.size.x;
            float aMaxY = a.position.y + a.size.y;
            float bMaxX = b.position.x + b.size.x;
            float bMaxY = b.position.y + b.size.y;

            float gapX = std::max(0.0f, std::max(a.position.x - bMaxX, b.position.x - aMaxX));
            float gapY = std::max(0.0f, std::max(a.position.y - bMaxY, b.position.y - aMaxY));

            return (gapX <= ALCANCE_ATAQUE_X && gapY <= FAIXA_ATAQUE_Y); 
        }

        void GerenciadorColisoes::colisaoPersonagens(Entidades::Personagens::Personagem* p1, Entidades::Personagens::Personagem* p2)
        {
            sf::FloatRect personagem1 = p1->getFig().getGlobalBounds();
            sf::FloatRect personagem2 = p2->getFig().getGlobalBounds();

            float overlap_x = std::min(personagem1.position.x + personagem1.size.x, personagem2.position.x + personagem2.size.x) - std::max(personagem1.position.x, personagem2.position.x);
            float overlap_y = std::min(personagem1.position.y + personagem1.size.y, personagem2.position.y + personagem2.size.y) - std::max(personagem1.position.y, personagem2.position.y);

            if(std::abs(overlap_x) < std::abs(overlap_y)){
                float dir = (personagem1.position.x < personagem2.position.x) ? -1.0f : 1.0f;
                p1->getFig().move({(dir * overlap_x) / 2, 0.0f});
                p2->getFig().move({(-dir * overlap_x) / 2, 0.0f});
            }
            else{
                sf::Vector2f centro1 = {personagem1.position.x + (personagem1.size.x / 2), personagem1.position.y + (personagem1.size.y / 2)};
                sf::Vector2f centro2 = {personagem2.position.x + (personagem2.size.x / 2), personagem2.position.y + (personagem2.size.y / 2)};
                                    
                if(centro1.y < centro2.y){ 
                    p1->getFig().move({0.0f, -overlap_y});
                    p1->pousar();                                                          
                }
                else{
                    p2->getFig().move({0.0f, -overlap_y});
                    p2->pousar();
                }
            }
        }

        void GerenciadorColisoes::colisaoPersonagemEntidade(Entidades::Personagens::Personagem* pP, Entidades::Entidade* pE)
        {
            sf::FloatRect pBounds = pP->getFig().getGlobalBounds(); 
            sf::FloatRect eBounds = pE->getFig().getGlobalBounds(); 

            float menor_lado_direito  = std::min(pBounds.position.x + pBounds.size.x, eBounds.position.x + eBounds.size.x);
            float maior_lado_esquerdo = std::max(pBounds.position.x, eBounds.position.x);

            float menor_lado_inferior = std::min(pBounds.position.y + pBounds.size.y, eBounds.position.y + eBounds.size.y);
            float maior_lado_superior = std::max(pBounds.position.y, eBounds.position.y);

            sf::Vector2f pCentro = {pBounds.position.x + pBounds.size.x / 2.0f, pBounds.position.y + pBounds.size.y / 2.0f};
            sf::Vector2f eCentro = {eBounds.position.x + eBounds.size.x / 2.0f, eBounds.position.y + eBounds.size.y / 2.0f};

            sf::Vector2f overlap = {menor_lado_direito - maior_lado_esquerdo, menor_lado_inferior - maior_lado_superior};

            if(std::abs(overlap.x) < std::abs(overlap.y))
            { 
                if(pCentro.x < eCentro.x)
                {
                    pP->getFig().move({-overlap.x, 0.0f}); 
                }
                else
                {
                    pP->getFig().move({ overlap.x, 0.0f}); 
                }
            }
            else
            {
                if(pCentro.y < eCentro.y)
                {
                    pP->getFig().move({0.0f, -overlap.y}); 
                    pP->pousar();
                } 
                else
                {   
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

        void GerenciadorColisoes::limparListas()
        {
            Linimigos.clear();
            Lobstaculos.clear();
            setProjeteis.clear();
            pJogador1 = nullptr;
            pJogador2 = nullptr;
        }

        bool GerenciadorColisoes::todosInimsInativos()const
        {        
            for(int i = 0; i < (int)Linimigos.size(); i++){
                if(Linimigos[i]->getAtivo()){return false;}
            }
           
            return true;
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

        void GerenciadorColisoes::incluirProjetil(Entidades::Projetil* pProj)
        {
            if(pProj){ 
                setProjeteis.insert(pProj); 
            }
        }

        void GerenciadorColisoes::executar()
        {
            tratarColisoesJogsObstacs();
            tratarColisoesJogsInims();
            tratarColisoesInimsObstacs();
            tratarColisoesInimsInims();
            tratarColisoesJogsJogs();
            tratarColisoesPersChao();
            tratarColisoesProjeteis();
            tratarColisoesParedes();
            aplicarAtaqueJog(pJogador1);
            aplicarAtaqueJog(pJogador2);
        }
    }
}