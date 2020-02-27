#include<iostream>
#include <string>
#include "queue.h"
using namespace std;

int main(){
    string nome_arq, idAviao;
    FILE* arq;
    bool leituraArq, lerDados = 0, emerg, pouso;
    int tempoAtual = 0, tempoSimulacao, codAviao, tempoComb, codComp, codPart, codDest, tempoVoo, te1, te2, te3, teEmg, emgP1, emgP2;

    cout << "✈️ ✈ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ TORRE DE COMANDO ✈️ ✈ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️" << endl;
    cout << "MODOS DE FUNCIONAMENTO: " << endl << "\t0 - INTERATIVO," << endl << "\t1 - ENTRADA DE DADOS POR ARQUIVO DE TEXTO." << endl;
    cout << "Escolha um modo de funcionamento: ";
    cin >> leituraArq;
    
    /*LEITURA DOS DADOS DO ARQUIVO*/    
    Pista* p1 = new Pista();
    Pista* p2 = new Pista();
    Pista* p3 = new Pista();
    Fila *filaEmerg = new Fila();
    Cel *predP1, *predP2, *predP3, *predEmg;

    if(leituraArq){
        
    }

    for (tempoAtual = 0; tempoAtual <= tempoSimulacao; tempoAtual++){
        if (!leituraArq){
            cout << "Deseja enviar informações de vôos para a torre de comando (0 - NÃO, 1 - SIM)? ";
            cin >> lerDados;
        }

        while (lerDados){
            cout << endl << "✈️ ✈ ✈️ ✈️ ✈️ ✈️ INFORMAÇÕES DO AVIÃO" << endl;
            cout << "--DIGITE UM NÚMERO NO INTERVALO DE CÓDIGOS DA BASE DADO ou '0' PARA LISTÁ-LOS-- " << endl;

            cout << "    Código da Companhia Aérea na Base (2 LETRAS, digite um número de 1 a " << QUANT_COMP << "): ";
            cin >> codComp;
            while (codComp < 1 || codComp > QUANT_COMP){
                listarCompanhias();
                cout << "    Código da Companhia Aérea na Base (2 LETRAS, digite um número de 1 a " << QUANT_COMP << "): ";
                cin >> codComp;
            }

            cout << "    Código de Identificação do Avião (3 DÍGITOS): ";
            cin >> codAviao;
            while(codAviao < 0 || codAviao > 999){
                cout << "    Código de Identificação do Avião Inválido!" << endl;
                cout << "    Código de Identificação do Avião (3 DÍGITOS): ";
                cin >> codAviao;
            }
            //Converte o código de três dígitos para uma string com 3 caracteres
            if(codAviao < 10) idAviao = "00" + to_string(codAviao);
            else if (codAviao < 100) idAviao = "0" + to_string(codAviao);
            else idAviao = to_string(codAviao);

            cout << "    Tempo de Combustível disponível para o Avião: ";
            cin >> tempoComb;

            idAviao = comp[codComp-1].substr(0,2) + idAviao;

            Aviao* av = new Aviao(idAviao, tempoComb);
            
            cout << endl << "✈️ ✈ ✈️ ✈️ ✈️ ✈️ INFORMAÇÕES DO VÔO" << endl;
            cout << "--DIGITE UM NÚMERO NO INTERVALO DE CÓDIGOS DA BASE DADO ou '0' PARA LISTÁ-LOS-- " << endl;

            cout << "    Código do Aeroporto de Partida na Base (3 LETRAS, digite um número de 1 a " << QUANT_AEROP << "): ";
            cin >> codPart;
            while (codPart < 1 || codPart > QUANT_AEROP){
                listarAeroportos();
                cout << "    Código do Aeroporto de Partida na Base (3 LETRAS, digite um número de 1 a " << QUANT_AEROP << "): ";
                cin >> codPart;
            }

            cout << "    Código do Aeroporto de Destino na Base (3 LETRAS, digite um número de 1 a " << QUANT_AEROP << "): ";
            cin >> codDest;
            while (codDest < 1 || codDest > QUANT_AEROP){
                listarAeroportos();
                cout << "    Código do Aeroporto de Destino na Base (3 LETRAS, digite um número de 1 a " << QUANT_AEROP << "): ";
                cin >> codDest;
            }

            cout << "    Tempo de Vôo: ";
            cin >> tempoVoo;
            cout << "    O vôo descrito é de emergência? (0 - NÃO, 1 - SIM): ";
            cin >> emerg;
            cout << "    O vôo descrito deseja pousar ou decolar neste aeroporto? (0 - DECOLAR, 1 - POUSAR): ";
            cin >> pouso;

            Voo* v = new Voo(av, aerop[codPart-1], aerop[codDest-1], tempoVoo, emerg, pouso);
            te1 = p1->getTempoEspera(v, predP1);
            emgP1 = p1->conteEmergencias(predP1, te1);
            te2 = p2->getTempoEspera(v, predP2);
            emgP2 = p2->conteEmergencias(predP2, te2);
            if()
            //Arrumar o gerenciamento de pistas, decolagens e pousos
            
            if(te1 <= v->getAviao()->getCombustivel() && te2 <= v->getAviao()->getCombustivel()){
                if(emgP1 == emgP2 == 0){
                    if(te1 <= te2)
                        p1->f->enqDepois(predP1, v);
                    else
                        p2->f->enqDepois(predP2, v);
                }else{
                    if(emgP1 == 0){
                        p1->f->enqDepois(predP1, v);
                    }else if(emgP2 == 0){
                        p2->f->enqDepois(predP2, v);
                    }else{
                        /*Há combustível para aguardar nas duas filas com a prioridade indicada,
                        mas isso gera casos de emergência para alguns aviões que já aguardavam nas filas*/
                        te3 = p3->getTempoEspera(v, predP3);
                        emgP3 = p3->conteEmergencias(predP3, te3);
                    }
                }
            }else if(te1 <= v->getAviao()->getCombustivel() || te2 <= v->getAviao()->getCombustivel()){

            }else{

            }

            p1->atualizarPista();
            p2->atualizarPista();
            p3->atualizarPista(); 

            cout << "Deseja enviar mais informações de vôos para a torre de comando (0 - NÃO, 1 - SIM)? ";
            cin >> lerDados;
        }
    }

    delete filaEmerg;
    delete p1;
    delete p2;
    delete p3;
}