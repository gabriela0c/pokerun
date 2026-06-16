#include "Entidades/Personagens/Inimigo.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{
            
            Inimigo::Inimigo(int nivMal, const sf::Vector2f tam , int n_vds, int v_pts):
            Personagem(tam, {VEL_INIM_X, 0.0f}, n_vds), pJogador1(nullptr), pJogador2(nullptr),
            nivel_maldade(nivMal), direcao(-1), tempoMovimento(0.0f), valorPontos(v_pts)
            {

            }

            Inimigo::~Inimigo()
            {
                pJogador1 = nullptr;
                pJogador2 = nullptr;
            }

            void Inimigo::salvarDataBuffer()
            {
                Personagem::salvarDataBuffer();
                buffer << " " << nivel_maldade << " " << valorPontos << " " << direcao;
            }

            void Inimigo::setJogador(Jogador* pJog)
            {
                if(pJog){
                    (pJog->getEhJogador1()) ? pJogador1 = pJog : pJogador2 = pJog;
                }
            }

            void Inimigo::executar()
            {
                aplicarGravidade();
                mover();
                noChao = false;
            }

            void Inimigo::mover()
            {
                if (!pJogador1) { //jogador 1 sempre deve estar no jogo
                    std::cerr << "Jogador 1 Nulo" << std::endl;
                    return;
                }

                sf::Vector2f posInimigo = pFigura->getPosition();
                sf::Vector2f posJogador1 = pJogador1->getFig().getPosition();

                // flags para saber quem está dentro do raio de visão do inimigo
                bool j1NoRaio = (std::abs(posInimigo.x - posJogador1.x) <= RAIO_X && std::abs(posInimigo.y - posJogador1.y) <= RAIO_Y);
                bool j2NoRaio = false;
                sf::Vector2f posJogador2;

                // so calcula o Jogador 2 se ele realmente existir no jogo
                if (pJogador2) {
                    posJogador2 = pJogador2->getFig().getPosition();
                    j2NoRaio = (std::abs(posInimigo.x - posJogador2.x) <= RAIO_X && std::abs(posInimigo.y - posJogador2.y) <= RAIO_Y);
                }

                // se ambos estao no raio inimigo persegue o mais proximo em x
                if (j1NoRaio && j2NoRaio) {
                    if (std::abs(posInimigo.x - posJogador1.x) < std::abs(posInimigo.x - posJogador2.x)) 
                        persegueJogador(posJogador1, posInimigo);
                    else
                        persegueJogador(posJogador2, posInimigo);
                } 
                else if (j1NoRaio) {
                    persegueJogador(posJogador1, posInimigo);
                } 
                else if (j2NoRaio) {
                    persegueJogador(posJogador2, posInimigo);
                } 
                else {
                    movimentoAleatorio();
                }
            }

            void Inimigo::movimentoAleatorio()
            {
                sf::Vector2f tam = getFig().getSize(); 

                pFigura->move({-vel_x * direcao * dt, 0.0f});
                
                if (direcao == -1) //move p direita
                    pFigura->setTextureRect(sf::IntRect({0, 0}, {(int)tam.x, (int)tam.y}));
                
                else //move p esquerda
                    pFigura->setTextureRect(sf::IntRect({(int)tam.x, 0}, {(int)-tam.x, (int)tam.y}));

                tempoMovimento += dt;

                if(tempoMovimento >= 0.5f){
                    tempoMovimento = 0.0f;
                    direcao = (rand()%2 == 0) ? -1 : 1;
                }
            }

            int Inimigo::getValorPontos()const
            {
                return valorPontos;
            }

            void Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
            {
                float distanciaX = posJogador.x - posInimigo.x;
                float tolerancia = 2.0f; //para evitar o inimigo ficar oscilando qdo o jogador esta em cima dele
                
                if(std::abs(distanciaX) > tolerancia){
                    sf::Vector2f tam = getFig().getSize();
                
                    if(distanciaX > 0.0f){
                        //indo p direita
                        pFigura->move({vel_x * dt, 0.0f});
                        pFigura->setTextureRect(sf::IntRect({0, 0}, {(int)tam.x, (int)tam.y}));
                    }
                    else{
                        //indo p esquerda
                        pFigura->move({-vel_x * dt, 0.0f});
                        pFigura->setTextureRect(sf::IntRect({(int)tam.x, 0}, {(int)-tam.x, (int)tam.y}));
                    }
                } 
            }

            void Inimigo::receberDano(int quantidade)
            {
                for (int i = 0; i < quantidade; i++){
                    operator--();
                }
            }

            void Inimigo::aplicarKnockback(Jogador* p, float forca)
            {
                float sinal = calcularDirecao(p->getFig().getPosition(), pFigura->getPosition());
                p->receberKnockback(sinal * forca);
            }
        }
    }
}