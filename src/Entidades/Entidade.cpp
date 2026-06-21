#include "Entidades/Entidade.h"

namespace Pokerun{

    namespace Entidades{
        
        Entidade::Entidade(const sf::Vector2f tam, const float vY): Ente(tam),
        x((float)(rand() % (int)(801 - tam.x))), y((float)(rand() % (int)(601 - tam.y - TAM_CHAO_Y))), y_inicial(y),
        vel_y(vY), gravidade(GRAVIDADE), relogio(), dt(0.0f), tempo_total(0.0f), ativo(true), noChao(false), buffer(nullptr)
        {
            setPosicao({x, y});
        }

        Entidade::~Entidade()
        {

        }

        void Entidade::conectarSaida(std::ostream& os)
        {
            buffer.rdbuf(os.rdbuf()); 
        }

        void Entidade::salvarDataBuffer()
        {
            buffer << id << " " << x << " " << y << " " << vel_y << " " << (ativo ? 1 : 0) ;
        }

        void Entidade::carregarDataBuffer(std::istream& is)
        {
            float Nx = 0.0f, Ny = 0.0f;
            is >> Nx >> Ny >> vel_y >> ativo;
            setPosicao({Nx, Ny});
        }

        void Entidade::aplicarGravidade()
        {
            dt = relogio.restart().asSeconds();
    
            if (dt > 0.1f) 
                dt = 0.1f;
                
            tempo_total += dt;
            
            //conceito de ensino médio: equação horária da posição (MRUV)
            //dS = V0*t + (a*t^2)/2
            float deslocamento_y = (vel_y * dt) + (0.5f * gravidade * (dt * dt));
            
            //atualiza a velocidade p/ o próximo frame: V = V0 + a*t
            vel_y += gravidade * dt;
            
            if(vel_y > VEL_TERM)
                vel_y = VEL_TERM;

            pFigura->move({0.0f, deslocamento_y});
            sincronizarPosicao();
        }

        void Entidade::sincronizarPosicao()
        {
            sf::Vector2f pos = pFigura->getPosition();
            x = pos.x;
            y = pos.y;
        }
        void Entidade::setPosicao(const sf::Vector2f pos)
        {
            pFigura->setPosition(pos);
            sincronizarPosicao();
            y_inicial = y;
        }

        sf::Vector2f Entidade::calcularDirecao(sf::Vector2f posAlvo, sf::Vector2f posFonte)
        {
            sf::Vector2f res = posAlvo - posFonte;
            return {((res.x >= 0.0f) ? 1.0f : -1.0f), ((res.y >= 0.0f) ? 1.0f : -1.0f)};
        }

        //método usado para garantir que, apesar de sofrerem gravidade, certas entidades,
        //como os obstáculos, não saem do lugar efetivamente, de modo que apenas oscilam no ar.
        //a aplicação do MHS foi uma ideia sugerida por IA e implementada pela dupla
        void Entidade::antiGravidade()
        {
            if(noChao) return;
            
            //conceito de ensino superior: movimento harmônico simples (MHS)
            float amplitude = 5.0f;          //altura do balanço em pixels
            float frequencia_angular = 2.0f;  //rapidez do balanço (rad/s)
            
            //equação da posição
            float y_desejado = y_inicial + amplitude * std::sin(frequencia_angular * tempo_total);
            
            //sobrescreve a queda livre gerada pelo aplicarGravidade() fixando a entidade na curva do MHS
            pFigura->setPosition({x, y_desejado});
            
            //equação da velocidade (derivada da Posição)
            vel_y = amplitude * frequencia_angular * std::cos(frequencia_angular * tempo_total);
            
            sincronizarPosicao(); 
        }

        sf::Vector2f Entidade::getPosition()const
        {
            return {x, y};
        }

        sf::Vector2f Entidade::getSize()const
        {
            return {pFigura->getSize()};
        }

        bool Entidade::getAtivo() const
        {
            return ativo;
        }  

        void Entidade::setAtivo(const bool a)
        {
            ativo = a;
        }
    }
}