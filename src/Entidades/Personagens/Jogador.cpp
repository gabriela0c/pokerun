#include "Entidades/Personagens/Jogador.h"
#include <iostream>

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Jogador::Jogador(const bool ehJog1):
            Personagem((ehJog1 ? sf::Vector2f(LARGURA_PIKACHU, ALTURA_PIKACHU) : sf::Vector2f(LARGURA_RAICHU, ALTURA_RAICHU)), {VEL_JOG_X, 0.0f}, N_VDS_JOG),
            ehJogador1(ehJog1), modificador_velocidade(1.0f), vel_knockback_x(0.0f), invencibilidade(1.0f), veneno(3.0f), cd_ataque(0.7f), pontos(0)
            {
                if(ehJog1){
                    setTextura("assets/sprites/personagens/jogador/pikachu.png", sf::IntRect({0, 0},{LARGURA_PIKACHU, ALTURA_PIKACHU}));
                }
                else{
                    setTextura("assets/sprites/personagens/jogador/raichu.png", sf::IntRect({0, 0},{LARGURA_RAICHU, ALTURA_RAICHU}));
                } 

                if(ehJog1){
                    pFigura->setPosition({150.0f, 120.0f}); //desaleatoriezar o spawn dos jogadores porque as vezes um nascia fora do mapa
                }
                else{
                    pFigura->setPosition({500.0f, 310.0f});
                }

                if (!fonteHUD.openFromFile("assets/fonts/PokemonSolid.ttf"))
                    std::cerr << "Erro ao carregar fonte do HUD no Jogador!" << std::endl;

                if (!texturaCoracao.loadFromFile("assets/sprites/outros/vidas.png"))
                    std::cerr << "Erro ao carregar sprite do coracao no Jogador!" << std::endl;
            }

            Jogador::~Jogador()
            {

            }

            void Jogador::mover()
            {
                aplicarGravidade();

                // aplica knockback horizontal usando o dt que aplicarGravidade() acabou de calcular
                if (vel_knockback_x != 0.0f) //separar em outro metodo
                {
                    pFigura->move({vel_knockback_x * dt, 0.0f});
                    vel_knockback_x *= (1.0f - 8.0f * dt);
                    if (std::abs(vel_knockback_x) < 1.0f) vel_knockback_x = 0.0f;
                }

                if(noChao) {
                    relogio.restart();
                }//relogio sempre novo quando no chao, garante que o pulo nao pareca teleporte
            }

            void Jogador::pular()
            {
                if(noChao){
                    vel_y = -400.0f;
                    noChao = false;
                } 
            }

            void Jogador::salvarDataBuffer()
            {
                Personagem::salvarDataBuffer();
                buffer << " " << pontos;
            }

            void Jogador::carregarDataBuffer(std::istream& is)
            {
                Personagem::carregarDataBuffer(is);
                is >> pontos;
            }

            void Jogador::salvar()
            {
                buffer << (ehJogador1 ? "JOGADOR1" : "JOGADOR2") << " "; 
                salvarDataBuffer(); 
                buffer << std::endl;
            }

            void Jogador::operator+=(int num)
            {
                pontos += num;
            }

            int Jogador::getPontos()const
            {
                return pontos;
            }

            void Jogador::curarVida()
            {
                if(num_vidas < N_VDS_JOG)
                    num_vidas++;
            }

            void Jogador::desenhar()
            {
                //desenha primeiro o personagem
                Ente::desenhar();

                //depois desenha o hud dele
                if (getAtivo())
                    desenharHUD();
            }

            void Jogador::desenharHUD()
            {
                sf::Sprite spriteCoracao(texturaCoracao);
                spriteCoracao.setScale(sf::Vector2f(0.05f, 0.05f)); 

                //define as posições base dependendo se é o jogador 1 (esquerda) ou jogador 2 (direita)
                float posX_Coracao = ehJogador1 ? 20.0f : 660.0f;
                float posX_TextoVidas = ehJogador1 ? 60.0f : 700.0f;
                float posX_TextoPontos = ehJogador1 ? 20.0f : 660.0f;

                spriteCoracao.setPosition(sf::Vector2f(posX_Coracao, 20.0f));
                pGG->desenhaElementos(spriteCoracao);

                std::ostringstream ssVidas, ssPontos;
                ssVidas << "x " << num_vidas;
                ssPontos << "Pontos: " << pontos;

                sf::Text txtVidas(fonteHUD); 
                txtVidas.setString(ssVidas.str());  
                txtVidas.setCharacterSize(20); 
                txtVidas.setFillColor(sf::Color::White); 
                txtVidas.setPosition(sf::Vector2f(posX_TextoVidas, 15.0f));
                
                sf::Text txtPts(fonteHUD);
                txtPts.setString(ssPontos.str()); 
                txtPts.setCharacterSize(16);   
                txtPts.setFillColor(sf::Color::Yellow);
                txtPts.setPosition(sf::Vector2f(posX_TextoPontos, 60.0f));

                pGG->desenhaElementos(txtVidas);
                pGG->desenhaElementos(txtPts);
            }

            void Jogador::diminui_vel(float taxa)
            {
                if(taxa < modificador_velocidade){
                    modificador_velocidade = taxa;
                }
            }

            float Jogador::getModVel()const{
                return modificador_velocidade;
            }

            void Jogador::receberKnockback(float impulso)
            {
                vel_knockback_x = impulso;
            }

            void Jogador::receberDano(int quantidade)
            {
                if (invencibilidade.getAtivo()) { return; }
                for (int i = 0; i < quantidade; i++)
                    operator--();
                invencibilidade.iniciar();
            }

            void Jogador::envenenar()
            {
                veneno.iniciar();
                std::cout << (ehJogador1 ? "Jogador 1 (Pikachu)" : "Jogador 2 (Raichu)") << " foi envenenado!" << std::endl;
            }

            bool Jogador::getEhJogador1() const
            {
                return ehJogador1;
            }

            bool Jogador::getInvencivel()const
            {
                return invencibilidade.getAtivo();
            }

            void Jogador::ativarInvencibilidade()
            {
                invencibilidade.iniciar();
            }

            void Jogador::setAtacando(const bool a)
            {
                atacando = a;
            }

            const bool Jogador::getAtacando()const
            {
                return atacando;
            }

            const bool Jogador::podeAtacar()
            {
                return (!cd_ataque.getAtivo());
            }

            void Jogador::iniciarCooldown()
            {
                cd_ataque.iniciar();
            }

            void Jogador::reposicionar()
            {
                if(ehJogador1)
                    setPosicao({150.0f, 120.0f});
                else
                    setPosicao({500.0f, 310.0f});
            }

            void Jogador::resetar()
            {
                num_vidas = N_VDS_JOG;
                pontos = 0;
                invencibilidade.parar();
                veneno.parar();
                vel_knockback_x = 0.0f;
                modificador_velocidade = 1.0f;
                setAtivo(true);

                reposicionar();
            }

            void Jogador::imprimirStatus() const
            {
                std::cout << "Status do Jogador:" << std::endl;
                std::cout << "Vidas: " << num_vidas << std::endl;
                std::cout << "Pontos: " << pontos << std::endl;
            }

            void Jogador::executar()
            {
                modificador_velocidade = 1.0f;

                bool estavaEnvenenado = veneno.getAtivo();
                veneno.atualizar();
                
                if(!veneno.getAtivo() && estavaEnvenenado){
                    std::cout << (ehJogador1 ? "Jogador 1 (Pikachu)" : "Jogador 2 (Raichu)") << " se curou do veneno!" << std::endl;
                }
                else if(veneno.getAtivo()){
                    diminui_vel(0.4f);
                }

                invencibilidade.atualizar();
                cd_ataque.atualizar();   

                mover();
                noTeto = false;
                noChao = false;

                if (num_vidas <= 0)
                {
                    setAtivo(false);
                    std::cout << (ehJogador1 ? "Jogador 1 (Pikachu) morto!" : "Jogador 2 (Raichu) morto!") << std::endl;
                }
            }
        }
    }
}


