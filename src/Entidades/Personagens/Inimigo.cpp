#include "Entidades/Personagens/Inimigo.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{
            
            Inimigo::Inimigo(int nivMal, const sf::Vector2f tam , int n_vds, int v_pts):
            Personagem(tam, {VEL_INIM_X, 0.0f}, n_vds), pJogador1(nullptr), pJogador2(nullptr),
            nivel_maldade(nivMal), direcao(-1), tempoMovimento(0.0f), valorPontos(v_pts), tempo_dano(0.0f), vidas_max(n_vds)
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
                buffer << " " << direcao;
            }

            void Inimigo::carregarDataBuffer(std::istream& is)
            {
                Personagem::carregarDataBuffer(is);
                is >> direcao;
            }

            void Inimigo::setJogador(Jogador* pJog)
            {
                if(pJog){
                    (pJog->getEhJogador1()) ? pJogador1 = pJog : pJogador2 = pJog;
                }
            }

            void Inimigo::executar()
            {
                if (num_vidas <= 0) 
                {
                    setAtivo(false);
                    return;
                }
                //pisca em vermelho se tomou dano
                if (tempo_dano > 0.0f) 
                {
                    tempo_dano -= dt; 
                    if (pFigura) 
                        pFigura->setFillColor(sf::Color::Red);
                } 
                else 
                {
                    if (pFigura) 
                        pFigura->setFillColor(sf::Color::White);
                }

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

                // usa o centro dos sprites para o raio nao depender do tamanho da entidade
                sf::Vector2f posInimigo = pFigura->getPosition() + getSize() / 2.0f;
                sf::Vector2f posJogador1 = pJogador1->getPosition() + pJogador1->getSize() / 2.0f;

                // flags para saber quem está dentro do raio de visão do inimigo
                bool j1NoRaio = (pJogador1->getAtivo() && (std::abs(posInimigo.x - posJogador1.x) <= RAIO_X && std::abs(posInimigo.y - posJogador1.y) <= RAIO_Y));
                bool j2NoRaio = false;
                sf::Vector2f posJogador2;

                // so calcula o Jogador 2 se ele realmente existir no jogo
                if (pJogador2 && pJogador2->getAtivo()) {
                    posJogador2 = pJogador2->getPosition() + pJogador2->getSize() / 2.0f;
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
                sf::Vector2f tam = getSize(); 

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

            void Inimigo::desenhar()
            {
                Ente::desenhar(); 
                desenharBarraDeVida();
            }

            void Inimigo::desenharBarraDeVida()
            {
                if (num_vidas > 0)
                {
                    float larguraMax = 40.0f;
                    float alturaBarra = 5.0f;
                    float pctVida = static_cast<float>(num_vidas) / vidas_max;

                    sf::Vector2f posInim = pFigura->getPosition();
                    sf::Vector2f tamInim = getSize();

                    sf::Vector2f posBarra(posInim.x + (tamInim.x - larguraMax) / 2.0f, posInim.y - 12.0f);

                    sf::RectangleShape fundo(sf::Vector2f(larguraMax, alturaBarra));
                    fundo.setFillColor(sf::Color::Red);
                    fundo.setPosition(posBarra);

                    sf::RectangleShape barraVida(sf::Vector2f(larguraMax * pctVida, alturaBarra));
                    barraVida.setFillColor(sf::Color::Green);
                    barraVida.setPosition(posBarra);

                    pGG->desenhaElementos(fundo);
                    pGG->desenhaElementos(barraVida);
                }
            }

            void Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
            {
                float distanciaX = posJogador.x - posInimigo.x;
                float tolerancia = 2.0f; //para evitar o inimigo ficar oscilando qdo o jogador esta em cima dele
                
                if(std::abs(distanciaX) > tolerancia){
                    sf::Vector2f tam = getSize();
                
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
                tempo_dano = 0.2f; 
            }

            void Inimigo::aplicarKnockback(Jogador* p, float forca)
            {
                sf::Vector2f sinais = calcularDirecao(p->getPosition(), getPosition());
                p->receberKnockback(sinais.x * forca);
            }
        }
    }
}