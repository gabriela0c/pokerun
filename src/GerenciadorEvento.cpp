#include "GerenciadorEvento.h"

Pokerun::Gerenciadores::GerenciadorEvento::GerenciadorEvento():
pGrafico(GerenciadorGrafico::getGerenciadorGrafico()), pJogador(NULL)
{

}

Pokerun::Gerenciadores::GerenciadorEvento* Pokerun::Gerenciadores::GerenciadorEvento::pEvento(nullptr);

Pokerun::Gerenciadores::GerenciadorEvento::~GerenciadorEvento()
{
    
}

void Pokerun::Gerenciadores::GerenciadorEvento::destruir()
{
    if(pEvento){
        delete pEvento;
        pEvento = nullptr;
    }
}

Pokerun::Gerenciadores::GerenciadorEvento* Pokerun::Gerenciadores::GerenciadorEvento::getGerenciadorEvento()
{
    if(!pEvento){
        pEvento = new GerenciadorEvento();
    }
    return pEvento;
}

void Pokerun::Gerenciadores::GerenciadorEvento::setJogador(Entidades::Personagens::Jogador* pjog)
{
    if(pjog){
        pJogador = pjog;
    }
}

void Pokerun::Gerenciadores::GerenciadorEvento::verificaTeclaPressionada(sf::Keyboard::Key tecla)
{
    if(pJogador){
        if(tecla == sf::Keyboard::Key::A){
            pJogador->andar(true);
        }
        else if(tecla == sf::Keyboard::Key::D){
            pJogador->andar(false);
        }
    }
    //A verificacao dos ponteiros para o gerenciador grafico e de eventos nao eh necessaria
    //pois X::getX() no padrao de projeto singleton sempre retorna um endereço de memoria valido
    if(tecla == sf::Keyboard::Key::Escape){
        pGrafico->fecharJanela();
    }
}

void Pokerun::Gerenciadores::GerenciadorEvento::verificaTeclaSolta(sf::Keyboard::Key tecla)
{
    if((tecla == sf::Keyboard::Key::A || tecla == sf::Keyboard::Key::D) && pJogador)
    {
        pJogador->parar();
    }
}

void Pokerun::Gerenciadores::GerenciadorEvento::executar()
{ 
    while (const auto event = (pGrafico->getWindow())->pollEvent()){
            if (const auto* KeyEvent = event->getIf<sf::Event::KeyPressed>()){
                verificaTeclaPressionada(KeyEvent->code);
            }
            else if(const auto* KeyEvent = event->getIf<sf::Event::KeyReleased>()){
                verificaTeclaSolta(KeyEvent->code);
            }
            else if (event->is<sf::Event::Closed>()){
                pGrafico->fecharJanela();
            }
        }
}

