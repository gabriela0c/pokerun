#pragma once

namespace Pokerun{

    namespace Listas{

        template<class TL>
        class Lista{
        public:

            template<class TE>
            class Elemento{
            private:
                Elemento<TE>* pProx;
                TE* pInfo;
            
            public:
                Elemento() : pProx(nullptr), pInfo(nullptr){}
                ~Elemento()
                {
                    pProx = nullptr;
                    pInfo = nullptr;
                }
                //setInfo
                void incluir(TE* p)
                {
                    if(p){
                        pInfo = p;
                    }
                }
                TE* getInfo()const {return pInfo;}

                void setProx(Elemento<TE>* pP)
                {
                        pProx = pP;
                }
                Elemento<TE>* getProx()const {return pProx;}
            };
        
            private:
                Elemento<TL>* pPrimeiro;
                Elemento<TL>* pUltimo;

            public:
                Lista();
                ~Lista();

                void incluir(TL* p);
                void remover(TL* p);
                void limpar();
                int getTam()const;

                Elemento<TL>* getPrimeiro()const;
        };

        template<class TL>
        Lista<TL>::Lista():
        pPrimeiro(nullptr), pUltimo(nullptr)
        {

        }

        template<class TL>
        Lista<TL>::~Lista()
        {
            limpar();
        }

        template<class TL>
        void Lista<TL>::incluir(TL* p)
        {
            if(!p){return;}

            Elemento<TL>* novo = new Elemento<TL>();
            novo->incluir(p);

            if(!pPrimeiro){
                pPrimeiro = novo;
                pUltimo = novo;
            }
            else{
                pUltimo->setProx(novo);
                pUltimo = novo;
            }
        }

        template<class TL>
        void Lista<TL>::remover(TL* p)
        {
            if(!p || !pPrimeiro){return;}
            
            Elemento<TL>* pAux = nullptr;
            pAux = pPrimeiro;

            if(pAux->getInfo() == p){
                pPrimeiro = pPrimeiro->getProx();
                if(!pPrimeiro){
                    pUltimo = nullptr;
                }
                delete pAux;
                pAux = nullptr;
                return;
            }
            
            while(pAux->getProx() != nullptr){
                if((pAux->getProx())->getInfo() == p){
                    Elemento<TL>* pDel = pAux->getProx();
                    if(pDel == pUltimo){
                        pUltimo = pAux;
                    }
                    pAux->setProx((pAux->getProx())->getProx());
                    delete pDel;
                    pDel = nullptr;
                    return;
                }
                pAux = pAux->getProx();
            }

        }

        template<class TL>
        void Lista<TL>::limpar()
        {
            Elemento<TL>* pAux = nullptr;
    
            while(pPrimeiro != nullptr){
                pAux = pPrimeiro;
                pPrimeiro = pPrimeiro->getProx();
                delete pAux;
                pAux = nullptr;
            }

            pUltimo = nullptr;
        }

        template<class TL>
        int Lista<TL>::getTam()const
        {
            Elemento<TL>* pAux = nullptr;
            pAux = pPrimeiro;

            int tam = 0;
    
            while(pAux != nullptr){
                tam++;
                pAux = pAux->getProx();
            }

            return tam;
        }

        template<class TL>
        Lista<TL>::Elemento<TL>* Lista<TL>::getPrimeiro()const
        {
            return pPrimeiro;
        }
    }
}