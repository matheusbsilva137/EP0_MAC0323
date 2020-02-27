#include<string>
#include<iostream>
#include <iomanip>
#ifndef QUEUE_H
#define QUEUE_H
#define QUANT_AEROP 31
#define QUANT_COMP 5

std::string comp[] = {
    "JJ - LATAM",
    "G3 - GOL",
    "AD - AZUL",
    "AF - AIR FRANCE",
    "AA - AMERICAN AIRLINES"
};

std::string aerop[] = {
    "BSB - Aeroporto Internacional de Brasília",
    "CNF - Aeroporto Internacional de Belo Horizonte - Confins",
    "PLU - Aeroporto Carlos Drummond de Andrade",
    "VCP - Aeroporto Internacional de Viracopos",
    "CWB - Aeroporto Internacional Afonso Pena",
    "FLN - Aeroporto Internacional Hercílio Luz",
    "GRU - Aeroporto Internacional de São Paulo-Guarulhos",
    "JOI - Aeroporto de Joinville",
    "MCP - Aeroporto Internacional de Macapá-Alberto Alcolumbre",
    "MAO - Aeroporto Internacional de Manaus",
    "NAT - Aeroporto Internacional de Natal",
    "SDU - Aeroporto Santos Dumont",
    "GIG - Aeroporto Internacional do Rio de Janeiro-Galeão",
    "QSC - Aeroporto Internacional de São Carlos",
    "THE - Aeroporto de Teresina",
    "ATL - Aeroporto Internacional de Atlanta",
    "PEK - Aeroporto Internacional de Pequim",
    "DXB - Aeroporto Internacional de Dubai",
    "LAX - Aeroporto Internacional de Los Angeles",
    "HND - Aeroporto Internacional Haneda",
    "LHR - Aeroporto Internacional Heathrow",
    "HKG - Aeroporto Internacional de Hong Kong",
    "CDG - Aeroporto Internacional Charles de Gaulle",
    "FRA - Aeroporto Internacional de Frankfurt",
    "MAD - Aeroporto Internacional de Barajas",
    "MEX - Aeroporto Internacional da Cidade do México",
    "YYZ - Aeroporto Internacional Pearson de Toronto",
    "BOM - Aeroporto Internacional de Chhatrapati Shivaji",
    "SHA - Aeroporto Internacional de Xangai Hongqiao",
    "ICN - Aeroporto Internacional de Incheon",
    "MEL - Aeroporto de Melbourne"
};

void listarAeroportos(){
    for (int i = 0; i < QUANT_AEROP; i++)
        std::cout << "\t" << std::setw(2) << std::setfill('0') << i+1 << " - " << aerop[i] << std::endl;
};

void listarCompanhias(){
    for (int i = 0; i < QUANT_COMP; i++)
        std::cout << "\t" << std::setw(2) << std::setfill('0') << i+1 << " - " << comp[i] << std::endl;
};

/*MÉTODOS E CLASSES PARA AVIÕES*/

class Aviao{
    private:
        std::string idAviao, companhia;
        int tempoCombustivel;

    public:
        Aviao(std::string id, int tempoComb);
        ~Aviao();
        std::string getid();
        std::string getCompanhia();
        int getCombustivel();
        void setId(std::string id);
        void setCombustivel(int tempoComb);    
};

Aviao::Aviao(std::string id, int tempoComb){
    idAviao = id;
    tempoCombustivel = tempoComb;
};

int Aviao::getCombustivel(){
    return tempoCombustivel;
};

void Aviao::setId(std::string id){
    idAviao = id;
};

void Aviao::setCombustivel(int tempoComb){
    tempoCombustivel = tempoComb;
};

/*MÉTODOS E CLASSES PARA VÔOS*/
class Voo{
    private:
        Aviao *a;
        std::string aeropPartida, aeropDestino;
        int tempoVoo, instanteContato;
        bool emergencia, pouso;
    public:
        Voo(Aviao* av, std::string part, std::string dest, int tmpV, bool emerg, bool ps);
        void setViagem(std::string part, std::string dest);
        void setEmergencia(bool emg);
        std::string getPartida();
        std::string getDestino();
        Aviao* getAviao();
        bool isEmergencia();
        bool isPouso();
        int getInstateContato();
};

Voo::Voo(Aviao* av, std::string part, std::string dest, int tmpV, bool emerg, bool ps): 
        a(av), aeropPartida(part), aeropDestino(dest), tempoVoo(tmpV), emergencia(emerg), pouso(ps) {};


std::string Voo::getPartida(){
    return aeropPartida;
};

std::string Voo::getDestino(){
    return aeropDestino;
};

void Voo::setViagem(std::string part, std::string dest){
    aeropPartida = part;
    aeropDestino = dest;
};

void Voo::setEmergencia(bool emg){
    this->emergencia = emg;
};

bool Voo::isEmergencia(){
    return emergencia;
};

bool Voo::isPouso(){
    return pouso;
};

Aviao* Voo::getAviao(){
    return a;
};

int Voo::getInstateContato(){
    return instanteContato;
}

/*CLASSES E MÉTODOS PARA MANIPULAÇÃO DAS LISTAS LIGADAS DE VÔOS*/

class Cel{
    public:
        Voo* v;
        Cel *prox;
};


class Fila{
    private:
        Cel *p;
    public:
        Fila();
        ~Fila();
        Cel getFila();
        void enqByCombustivel(Voo *v);
        void enq(Voo *v);
        void enqDepois(Cel *predecessora, Voo *v);
        Voo* deq();
        bool isEmpty();
        int getTempoEspera(Voo* v, Cel* predecessora);
};

Fila::Fila(): p(new Cel) {
    p->prox = NULL;
};

Fila::~Fila(){
    Cel *aux;
    while(p != NULL){
        aux = p->prox;
        delete p;
        p = aux;
    }
};

Cel Fila::getFila(){
    return *p;
};

bool Fila::isEmpty(){
    return (p->prox == NULL);
};

void Fila::enq(Voo *v){
    Cel *c = new Cel;
    Cel *aux = p->prox;

    if(aux == NULL){
        c->prox = p->prox;
        p->prox = c;
    }else{
        while(aux->prox != NULL) aux = aux->prox;
        c->prox = aux->prox;
        aux->prox = c;
    }

    c->v = v;
};

void Fila::enqDepois(Cel *predecessora, Voo *v){
    Cel *c = new Cel;
    Cel *aux = p->prox;

    c->prox = predecessora->prox;
    predecessora->prox = c;

    c->v = v;
};

void Fila::enqByCombustivel(Voo *v){
    Cel *c = new Cel;
    Cel *a = p->prox;
    if(v->isEmergencia()){
        if(Fila::isEmpty() || (a->v->isEmergencia() && a->v->getAviao()->getCombustivel() >= v->getAviao()->getCombustivel() ) ){
            //Insere na primeira posição da lista ligada
            p->prox = c;
            c->prox = a;
        }else{
            while(a->prox != NULL && a->v->isEmergencia() && a->v->getAviao()->getCombustivel() <= v->getAviao()->getCombustivel())
                a = a->prox;
            c->prox = a->prox;
            a->prox = c;
        }
    }else{
        while (a->v->isEmergencia()) a = a->prox;
        if(Fila::isEmpty() || a->v->getAviao()->getCombustivel() >= v->getAviao()->getCombustivel() ){
            //Insere na primeira posição da lista ligada
            p->prox = c;
            c->prox = a;
        }else{            
            while(a->prox != NULL && a->v->getAviao()->getCombustivel() <= v->getAviao()->getCombustivel())
                a = a->prox;
            c->prox = a->prox;
            a->prox = c;
        }
    }

    c->v = v;
};

Voo* Fila::deq(){
    Voo *v;
    Cel *c;
    if (p->prox == NULL) return NULL;
    v = p->prox->v;

    c = p->prox;
    p->prox = p->prox->prox;

    delete c;
    return v;
};

/*MÉTODOS E CLASSES PARA A MANIPULAÇÃO DAS PISTAS*/
enum Estado{
    LIVRE = 0,
    POUSO = 1,
    DECOLANDO = 1,
    INTERDITADA1,
    INTERDITADA2,
};

class Pista{
    private:
        Estado e;
    public:
        Fila* f;
        Voo* vooOper;
        Pista();
        ~Pista();
        Estado avanceEstado();
        Estado getEstado();
        int getTempoEspera(Voo* v, Cel* predecessora);
        int conteEmergencias(Cel *predecessora, int te);
        void atualizarPista();
};

Pista::Pista():f(new Fila), e(LIVRE){};

Pista::~Pista(){
    f->~Fila();
};

Estado Pista::avanceEstado(){
    e = (Estado) (((int)e+1)%3);
    return e;
};

Estado Pista::getEstado(){
    return e;
};

int Pista::getTempoEspera(Voo* v, Cel* predecessora){
    Cel *a = f->p->prox;
    int tempoEspera = 0;

    predecessora = f->p;
    if(v->isEmergencia()){
        if(Fila::isEmpty() || !a->v->isEmergencia() || a->v->getAviao()->getCombustivel() >= v->getAviao()->getCombustivel() ){
            return 0;
        }else{
            while(a->prox != NULL && a->v->isEmergencia() && a->v->getAviao()->getCombustivel() <= v->getAviao()->getCombustivel()){
                predecessora = a;
                a = a->prox;
                tempoEspera += 3;
            }
        }
    }else{
        while (a != NULL && a->v->isEmergencia()){
            predecessora = a;
            a = a->prox;
            tempoEspera += 3;
        }
        
        if(Fila::isEmpty() || a->v->getInstateContato() >= v->getInstateContato() ){
            return tempoEspera;
        }else{            
            while(a->prox != NULL && a->v->getInstateContato() <= v->getInstateContato()){
                predecessora = a;
                a = a->prox;
                tempoEspera += 3;
            }
        }
    }

    return tempoEspera;
};

/*Calcula e retorna a quantidade de vôos que entrariam em estado
  emergência caso seja feita uma inserção na fila após a célula
  predecessora dada como parâmetro.*/
int Pista::conteEmergencias(Cel* predecessora, int te){
    Cel *aux;
    int contEmerg = 0;

    for(aux = predecessora->prox; aux != NULL ; aux = aux->prox){
        if (aux->v->getAviao()->getCombustivel() <= te + 3) contEmerg++;
        te += 3;
    }

    return contEmerg;
};

void Pista::atualizarPista(){
    Voo* oper;
    Cel *aux;

    if(getEstado() == LIVRE){
        oper = this->f->deq();
        if (oper != NULL)
            avanceEstado();
    }else
        avanceEstado();
    for( aux = this->f->getFila().prox; aux != NULL; aux = aux->prox){
        if (aux->v->isPouso()){
            aux->v->getAviao()->setCombustivel(aux->v->getAviao()->getCombustivel() - 1);
            if(aux->v->getAviao()->getCombustivel() == 0) aux->v->setEmergencia(true);
        }
    }
};

#endif