#include "Ente.h"
#include "Gere
#include "Lista.h"

namespace Pokerun {
    namespace Fases{

        class Fase : public Ente {
            protected:
                Lista::ListaEntidade ListaPersonagens;
                Lista::ListaEntidade ListaObstaculos;
                Gerenciador::GerenciadorColisoes* pGC;

            public:
                Fase(const int id = 0);
                virtual ~Fase();

                void executar();
                void desenhar();

            protected:
                virtual void criarInimigos()

        }
    }
}