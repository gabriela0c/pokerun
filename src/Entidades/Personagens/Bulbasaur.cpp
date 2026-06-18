#include "Entidades/Personagens/Bulbasaur.h"

namespace Pokerun{

    namespace Entidades{

        namespace Personagens{

            Bulbasaur::Bulbasaur() : 
            Inimigo(NIVEL_MALD_FACIL, {LARGURA_BULBASAUR, ALTURA_BULBASAUR}, N_VDS_FACIL, N_PTS_FACIL), 
            chance_veneno((rand()%10) + 1), pos_x_inicial(0.0f), ultima_pos_x(0.0f), pos_inicial_salva(false)
            {
                setTextura("assets/sprites/personagens/inimigo/bulbasaur.png", sf::IntRect({0,0}, {(int)LARGURA_BULBASAUR, (int)ALTURA_BULBASAUR}));
            }

            Bulbasaur::~Bulbasaur()
            {

            }

            void Bulbasaur::salvarDataBuffer()
            {
                Inimigo::salvarDataBuffer();
                buffer << " " << chance_veneno;
            }

            void Bulbasaur::carregarDataBuffer(std::istream& is)
            {
                Inimigo::carregarDataBuffer(is);
                is >> chance_veneno;
            }

            void Bulbasaur::salvar()
            {
                buffer << "BULBASAUR "; 
                salvarDataBuffer(); 
                buffer << std::endl;
            }

            void Bulbasaur::executar()
            {
                if (num_vidas <= 0) 
                {
                    setAtivo(false);
                    return;
                }

                aplicarGravidade();
                float pos_atual_x = pFigura->getPosition().x;

                //"patrulha" c detecção de parede 
                if (!pos_inicial_salva) 
                {
                    pos_x_inicial = pos_atual_x;
                    ultima_pos_x = pos_atual_x;
                    pos_inicial_salva = true;
                    direcao = -1; 
                } 
                else 
                {
                    //se bateu e parou ...
                    if (std::abs(pos_atual_x - ultima_pos_x) < 0.1f) 
                    {
                        direcao *= -1;               
                        pos_x_inicial = pos_atual_x; 
                    }
                }

                ultima_pos_x = pos_atual_x; 

                float limite_patrulha = 100.0f;

                if (pos_atual_x > pos_x_inicial + limite_patrulha)
                    direcao = 1;
                else if (pos_atual_x < pos_x_inicial - limite_patrulha)
                    direcao = -1;

                sf::Vector2f tam = getSize(); 
                pFigura->move({-vel_x * direcao * dt, 0.0f});
                
                if (direcao == -1)
                    pFigura->setTextureRect(sf::IntRect({0, 0}, {(int)tam.x, (int)tam.y}));

                else
                    pFigura->setTextureRect(sf::IntRect({(int)tam.x, 0}, {(int)-tam.x, (int)tam.y}));

                noChao = false;
            }

            void Bulbasaur::danificar(Jogador* p)
            {
                if (p->getInvencivel()) { return; }
 
                for(int i = 0; i < nivel_maldade; i++){
                    p->operator--();
                }
                
                aplicarKnockback(p, 200.0f);
 
                if (((rand() % 10) + 1)  < chance_veneno)
                {
                    p->envenenar();
                }
 
                p->ativarInvencibilidade();
                std::cout << "Bulbasaur danificou " << (p->getEhJogador1() ? "Pikachu" : "Raichu") << "! Vidas: " << p->getNumvidas() << std::endl;
            }
        }
    }
}