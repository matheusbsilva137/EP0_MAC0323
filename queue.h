/*
  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
  Nome: Matheus Barbosa Silva
  NUSP: 11221741
*/
#include<string>
#include<iostream>
#include <iomanip>
#ifndef QUEUE_H
#define QUEUE_H
#define QUANT_AEROP 31
#define QUANT_COMP 5

//Vetor de Companhias, usado para gerar o código do avião e exibir a lista de opções
std::string comp[] = {
    "JJ - LATAM",
    "G3 - GOL",
    "AD - AZUL",
    "AF - AIR FRANCE",
    "AA - AMERICAN AIRLINES"
};

//Vetor de Aeroportos, usado para determinar a origem/destino do vôo e exibir a lista de opções
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

//Funções para exibir as listas associadas aos vetores acima
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
        std::string getId();
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

std::string Aviao::getId(){
    return idAviao;
};

void Aviao::setCombustivel(int tempoComb){
    tempoCombustivel = tempoComb;
};

/*MÉTODOS E CLASSES PARA VÔOS*/
class Voo{
    private:
        Aviao* a;
        std::string aerop;
        int tempoVoo, instanteContato;
        bool emergencia, pouso;
    public:
        Voo(Aviao* av, std::string arp, int tmpV, bool emerg, bool ps, int ic);
        ~Voo();
        void setViagem(std::string arp);
        void setEmergencia(bool emg);
        std::string getAeroporto();
        Aviao* getAviao();
        bool isEmergencia();
        bool isPouso();
        int getInstateContato();
        int getTempoVoo();
};

Voo::Voo(Aviao* av, std::string arp, int tmpV, bool emerg, bool ps, int ic): 
        a(av), aerop(arp), tempoVoo(tmpV), emergencia(emerg), pouso(ps), instanteContato(ic){};

Voo::~Voo(){
    delete a;
};

std::string Voo::getAeroporto(){
    return aerop.substr(0, 3);
};

void Voo::setViagem(std::string arp){
    aerop = arp;
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

int Voo::getTempoVoo(){
    return tempoVoo;
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
        int size;
    public:
        Fila();
        ~Fila();
        Cel* getFila();
        Cel* getLastNode();
        void enq(Voo *v);
        void enqDepois(Cel **predecessora, Voo *v, int* tmpPouso, int* tmpDecol);
        Voo* deq();
        bool isEmpty();
        int getTempoEspera(Voo* v, Cel* predecessora);
        int getSize();
};

Fila::Fila(): p(new Cel), size(0) {
    p->prox = nullptr;
};

Fila::~Fila(){
    Cel *aux;
    while(p != nullptr){
        aux = p->prox;
        delete p->v;
        delete p;
        p = aux;
    }
};

Cel* Fila::getFila(){
    return p;
};

Cel* Fila::getLastNode(){
    Cel *a;
    for (a = p; a->prox != NULL; a = a->prox);
    return a;
};

bool Fila::isEmpty(){
    return (p->prox == NULL);
};

int Fila::getSize(){
    return size;
};

void Fila::enq(Voo *v){
    Cel *c = new Cel;
    Cel *aux = p->prox;

    size++;

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

void Fila::enqDepois(Cel **predecessora, Voo *v, int* tmpPouso, int* tmpDecol){
    Cel *c = new Cel;
    Cel *aux = p->prox, *auxTmp;

    for(auxTmp = (*predecessora)->prox; auxTmp != NULL; auxTmp = auxTmp->prox){
        if (auxTmp->v->isPouso()) *tmpPouso += 3;
        else *tmpDecol += 3;
    }

    size++;

    c->prox = (*predecessora)->prox;
    (*predecessora)->prox = c;

    c->v = v;
};

Voo* Fila::deq(){
    Voo *v;
    Cel *c;
    if (p->prox == NULL) return NULL;
    v = p->prox->v;

    c = p->prox;
    p->prox = p->prox->prox;

    size--;
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
        int num;
    public:
        Fila* f;
        Voo* vooOper;
        Pista(int n);
        ~Pista();
        Estado avanceEstado();
        Estado getEstado();
        int getNumPista();
        int getTempoEspera(Voo* v, Cel** predecessora);
        int conteEmergencias(Cel *predecessora, int te);
        void atualizarPista(int* qcomb, int* qespPousp, int* qespDecol, int* qcombEsp, int* qemergPouso, int* qemergDecol, int* qpouso, int* qdecol);
};

Pista::Pista(int n):f(new Fila), e(LIVRE), num(n){};

Pista::~Pista(){
    delete f;
};

Estado Pista::avanceEstado(){
    if (e == LIVRE) e = POUSO;
    else if (e == POUSO) e = INTERDITADA1;
    else if (e == INTERDITADA1) e = INTERDITADA2;
    else e = LIVRE;
    return e;
};

Estado Pista::getEstado(){
    return e;
};

int Pista::getNumPista(){
    return num;
};

/*
    Obtém a posição ideal para a inserção do vôo na fila, analisando e evitando possíveis casos de emergência ou excesso
    de tempo de espera. A célula que precederá a célula a ser inserida na fila é passada como parâmetro como predecessora e 
    é alterada pela função. Assim, quando possível, esta função retorna a última célula da fila - o que faz com o que o 
    resultado de enfileirar a célula seja equivalente a utilizar a função enq.
*/
int Pista::getTempoEspera(Voo* v, Cel** predecessora){
    Cel *a = f->getFila()->prox;
    int tempoEspera = 0, i;
    *predecessora = f->getFila();

    if(v->isEmergencia()){
        if(f->isEmpty() || !a->v->isEmergencia() || conteEmergencias(f->getFila(), tempoEspera + (4 - (int) this->getEstado())%4) == 0 ){
            *predecessora = f->getFila();
            return (4 - (int) this->getEstado())%4;
        }else{
            if (!v->isPouso()){
                while (a->prox != nullptr && a->v->isPouso()){
                    *predecessora = a;
                    a = a->prox;
                    tempoEspera += 3;
                }

                while(a->prox != nullptr && a->v->isEmergencia() && a->v->getTempoVoo() <= v->getTempoVoo() ){
                    *predecessora = a;
                    a = a->prox;
                    tempoEspera += 3;
                }
            }else{
                while(a->prox != nullptr && a->v->isEmergencia() && a->v->getAviao()->getCombustivel() <= v->getAviao()->getCombustivel() && a->v->isPouso()){
                    *predecessora = a;
                    a = a->prox;
                    tempoEspera += 3;
                }
            }
            
            while ((*predecessora)->prox != nullptr && conteEmergencias(*predecessora, tempoEspera + (4 - (int) this->getEstado())%4) > 0){
                tempoEspera += 3;
                *predecessora = (*predecessora)->prox;
            }
        }
    }else{
        while (a != nullptr && a->v->isEmergencia()){
            *predecessora = a;
            a = a->prox;
            tempoEspera += 3;
        }
        
        if(f->isEmpty() || a->v->getInstateContato() > v->getInstateContato() ){
            *predecessora = f->getFila();
            return tempoEspera + (4 - (int) this->getEstado())%4;
        }else{
            if (a->prox == NULL && a->v->getInstateContato() <= v->getInstateContato()){
                *predecessora = a;
                tempoEspera += 3;
            }
            while(a->prox != NULL && a->v->getInstateContato() <= v->getInstateContato()){
                *predecessora = a;
                a = a->prox;
                tempoEspera += 3;

                if (a->prox == NULL && a->v->getInstateContato() <= v->getInstateContato()){
                    *predecessora = a;
                    tempoEspera += 3;
                }
            }

            while ((*predecessora)->prox != nullptr && conteEmergencias(*predecessora, tempoEspera + (4 - (int) this->getEstado())%4) > 0){
                tempoEspera += 3;
                *predecessora = (*predecessora)->prox;
            }
        }
    }

    return tempoEspera + (4 - (int) this->getEstado())%4;
};

/*
    Calcula e retorna a quantidade de vôos que entrariam em estado
    emergência caso seja feita uma inserção na fila após a célula
    predecessora dada como parâmetro. Esta função é auxiliar à função
    getTempoEspera, que busca o resultado mínimo (0) de conteEmergencias().
*/
int Pista::conteEmergencias(Cel* predecessora, int te){
    Cel *aux;
    int contEmerg = 0;

    if (predecessora == NULL || predecessora->prox == NULL) return 0;
    for(aux = predecessora->prox; aux != NULL ; aux = aux->prox){
        if (aux->v->getAviao()->getCombustivel() <= te + 3) contEmerg++;
        te += 3;
    }

    return contEmerg;
};

/*
    Atualiza a quantidade de combustível dos aviões nas filas e manipula os inteiros responsáveis pelas estatísticas apresentadas ao usuário.
*/
void Pista::atualizarPista(int* qcomb, int* qespPouso, int* qespDecol, int* qcombEsp, int* qemergPouso, int* qemergDecol, int* qpouso, int* qdecol){
    Voo* oper;
    Cel *aux;

    if (getEstado() == INTERDITADA2){
        avanceEstado();
        delete vooOper;
        vooOper = NULL;
    }

    if(getEstado() == LIVRE){
        oper = this->f->deq();
        if (oper != NULL){
            avanceEstado();
            this->vooOper = oper;
            if (oper->isPouso()) {
                std::cout << " - Avião " << oper->getAviao()->getId() << " " << oper->getAeroporto() << " pousa na pista " << this->getNumPista();
                *qcomb += oper->getAviao()->getCombustivel();
                *qespPouso -= 1;
                *qpouso += 1;
                *qcombEsp -= oper->getAviao()->getCombustivel();
                if (oper->getAviao()->getCombustivel() == 0 || this->getNumPista() == 3) *qemergPouso += 1; 
                if (this->getNumPista() == 3) std::cout << " (EMERGÊNCIA)" << std::endl;
            }else{
                std::cout << " - Avião " << oper->getAviao()->getId() << " " << oper->getAeroporto() << " decola na pista " << this->getNumPista();
                *qespDecol -= 1;
                *qdecol += 1;
                if (oper->isEmergencia() == 1) *qemergDecol += 1; 
            }
            if (oper->getAviao()->getCombustivel() == 0) std::cout << " (EMERGÊNCIA)" << std::endl;
            else std::cout << std::endl;
        }
    }else{
        avanceEstado();
    }
    for( aux = this->f->getFila()->prox; aux != NULL; aux = aux->prox)
        if (aux->v->isPouso()) aux->v->getAviao()->setCombustivel(aux->v->getAviao()->getCombustivel() - 1);
};

void exibirPistas(Pista* p1, Pista* p2, Pista *p3){
    Cel *a1, *a2, *a3;
    int i;

    a1 = p1->f->getFila()->prox;
    a2 = p2->f->getFila()->prox;
    a3 = p3->f->getFila()->prox;

    std::cout << "       ";
    for (i = 0; i < 30; i ++){
        if (i % 10 == 0) std::cout << "+----";
        else std::cout << "-";
    }
    std::cout << "+" << std::endl;

    std::cout << "       | ";
    for (i = 0; i < 3; i++){
        std::cout << "  PISTA " << i+1 << "   | ";
    }
    std::cout << std::endl;

    for (i = 0; i < 46; i ++){
        std::cout << "-";
        if ((i - 6) % 13 == 0) std::cout << "+";
    }
    std::cout << std::endl;

    std::cout << " STATUS|";
    
    switch (p1->getEstado()){
        case LIVRE: std::cout << "    LIVRE    |"; break;
        case POUSO:
            if (p1->vooOper->isPouso()) std::cout << "POUSO (" << p1->vooOper->getAviao()->getId() << ")|"; 
            else std::cout << "DECOL (" << p1->vooOper->getAviao()->getId() << ")|";
            break;
        case INTERDITADA1:
        case INTERDITADA2:
            std::cout << " INTERDITADA |"; break;
        default: std::cout << "ERRADO";
    }

    switch (p2->getEstado()){
        case LIVRE: std::cout << "    LIVRE    |"; break;
        case POUSO:
            if (p2->vooOper->isPouso()) std::cout << "POUSO (" << p2->vooOper->getAviao()->getId() << ")|"; 
            else std::cout << "DECOL (" << p2->vooOper->getAviao()->getId() << ")|";
            break;
        case INTERDITADA1:
        case INTERDITADA2:
            std::cout << " INTERDITADA |"; break;
    }

    switch (p3->getEstado()){
        case LIVRE: std::cout << "    LIVRE    |"; break;
        case POUSO:
            if (p3->vooOper->isPouso()) std::cout << "POUSO (" << p3->vooOper->getAviao()->getId() << ")|"; 
            else std::cout << "DECOL (" << p3->vooOper->getAviao()->getId() << ")|";
            break;
        case INTERDITADA1:
        case INTERDITADA2:
            std::cout << " INTERDITADA |"; break;
    }
    std::cout << std::endl;

    for (i = 0; i < 46; i ++){
        std::cout << "-";
        if ((i - 6) % 13 == 0) std::cout << "+";
    }
    std::cout << std::endl;

    i = 1;
    while(a1 != NULL || a2 != NULL || a3 != NULL){
        printf("   %02d. | ", i++);
        if(a1 != NULL){
            std::cout << "  ✈️ " << a1->v->getAviao()->getId() << "   | ";
            a1 = a1->prox;
        }else{
            std::cout << "            | ";
        }

        if(a2 != NULL){
            std::cout << "  ✈️ " << a2->v->getAviao()->getId() << "   | ";
            a2 = a2->prox;
        }else{
            std::cout << "            | ";
        }

        if(a3 != NULL){
            std::cout << "  ✈️ " << a3->v->getAviao()->getId() << "   | ";
            a3 = a3->prox;
        }else{
            std::cout << "            | ";
        }
        std::cout << std::endl;
    }

    for (i = 0; i < 46; i++){
        std::cout << "-";
        if ((i - 6) % 13 == 0) std::cout << "+";
    }
    std::cout << std::endl;
};

#endif