#include "Temporizador.h"

namespace Pokerun{

        Temporizador::Temporizador(const float d) : relogio(), duracao(d), ativo(false)
        {

        }
        
        Temporizador::~Temporizador()
        {

        }

        void Temporizador::iniciar()
        {
            relogio.restart();
            ativo = true;
        }
        
        void Temporizador::atualizar()
        {
            if(ativo && relogio.getElapsedTime().asSeconds() > duracao){
                ativo = false;
            }
        }

        void Temporizador::parar()
        {
            ativo = false;
        }

        void Temporizador::setDuracao(const float d)
        {
            duracao = d;
        }

        bool Temporizador::getAtivo()const
        {
            return ativo;
        }
}