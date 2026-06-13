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
        
        bool Temporizador::expirou()
        {
            if(ativo && relogio.getElapsedTime().asSeconds() > duracao){
                ativo = false;
                return true;
            }
            return false;
        }

        void Temporizador::parar()
        {
            ativo = false;
        }

        bool Temporizador::getAtivo()const
        {
            return ativo;
        }
}