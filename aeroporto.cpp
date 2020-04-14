/*
  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
  Nome: Matheus Barbosa Silva
  NUSP: 11221741
*/
#include<iostream>
#include <fstream>
#include <string>
#include "queue.h"
using namespace std;

int main(){
    //Eliminar todas as linhas com a contagem de emergências, inserir o template e leitura por arquivo
    string nome_arq, idAviao;
    ifstream arq;
    bool lerDados = 0, emerg, pouso;
    int tempoAtual = 0, tempoSimulacao, codAviao, tempoComb, codComp, codAer, tempoVoo, te1, te2, te3, teEmg, i;
    int tempoPousos = 0, quantPousos = 0, quantDecol = 0, tempoDecol = 0, quantReg, entrada, semente;
    int quantEmerg = 0, quantCombPouso = 0, quantCombEsp = 0, quantEspPouso = 0, quantEspDecol = 0, quantEmgPouso = 0, quantEmgDecol = 0; 
    float mediaPouso, mediaCombPouso = 0, mediaCombEsp = 0, mediaDecol;

    cout << "✈️ ✈ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ TORRE DE COMANDO ✈️ ✈ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️ ✈️" << endl;
    cout << "MODOS DE FUNCIONAMENTO: " << endl << "\t0 - INTERATIVO," << endl << "\t1 - ENTRADA DE DADOS POR ARQUIVO DE TEXTO, " << endl << "\t2 - ALEATÓRIO." << endl;
    cout << "Escolha um modo de funcionamento: ";
    cin >> entrada;
    
    /*LEITURA DOS DADOS DO ARQUIVO*/    
    Pista* p1 = new Pista(1);
    Pista* p2 = new Pista(2);
    Pista* p3 = new Pista(3);
    Aviao* av;
    Voo* v;
    Cel *predP1, *predP2, *predP3, *predEmg;

    if(entrada == 1){
        cout << "Informe o nome do arquivo de entrada: ";
        cin >> nome_arq;
        arq.open(nome_arq);
        if (!arq) {
            cerr << "Não foi possivel abrir o arquivo de texto informado!";
            tempoSimulacao = -1;
        }
        arq >> tempoSimulacao;
    }else if (entrada == 0){
        cout << "Informe o tempo total de simulação: ";
        cin >> tempoSimulacao;
    }else{
        cout << "Informe uma semente: ";
        srand (time(NULL));
        cin >> semente;
        srand(semente);
        cout << "Informe o tempo total de simulação: ";
        cin >> tempoSimulacao;
    }

    for (tempoAtual = 0; tempoAtual <= tempoSimulacao; tempoAtual++){
        if (entrada == 0){
            cout << "Deseja enviar informações de vôos para a torre de comando (0 - NÃO, 1 - SIM)? ";
            cin >> lerDados;
        }else if (entrada == 1){
            arq >> quantReg;
            lerDados = true;
        }else{
            cout << "Informe a quantidade de registros a serem gerados: ";
            cin >> quantReg;
            lerDados = true;
        }

        while (lerDados){
            if (quantReg == 0){
                lerDados = false;
            }else if (entrada == 1){
                //Entrada de dados pelo arquivo de texto
                arq >> codComp >> codAviao >> tempoComb >> pouso >> codAer >> tempoVoo >> emerg;
                if(codAviao < 10) idAviao = "00" + to_string(codAviao);
                else if (codAviao < 100) idAviao = "0" + to_string(codAviao);
                else idAviao = to_string(codAviao);
                idAviao = comp[codComp-1].substr(0,2) + idAviao;

                av = new Aviao(idAviao, tempoComb);
                v = new Voo(av, aerop[codAer-1], tempoVoo, emerg, pouso, tempoAtual);
                quantReg--;
                cout << endl;
            }else if (entrada == 2){
                codComp = (rand()%QUANT_COMP) + 1;
                codAviao = rand()%1000;
                tempoComb = rand();
                pouso = rand()%2;
                codAer = (rand()%QUANT_AEROP) + 1;
                tempoVoo = rand();
                emerg = rand()%2;

                if(codAviao < 10) idAviao = "00" + to_string(codAviao);
                else if (codAviao < 100) idAviao = "0" + to_string(codAviao);
                else idAviao = to_string(codAviao);
                idAviao = comp[codComp-1].substr(0,2) + idAviao;

                av = new Aviao(idAviao, tempoComb);
                v = new Voo(av, aerop[codAer-1], tempoVoo, emerg, pouso, tempoAtual);
                quantReg--;
                cout << endl;
            }else if (entrada == 0){
                //Entrada de dados interativa (usuário)
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

                av = new Aviao(idAviao, tempoComb);
                
                cout << endl << "✈️ ✈ ✈️ ✈️ ✈️ ✈️ INFORMAÇÕES DO VÔO" << endl;
                cout << "    O vôo descrito deseja pousar ou decolar neste aeroporto? (0 - DECOLAR, 1 - POUSAR): ";
                cin >> pouso;

                cout << "--DIGITE UM NÚMERO NO INTERVALO DE CÓDIGOS DA BASE DADO ou '0' PARA LISTÁ-LOS-- " << endl;
                if (pouso) cout << "    Código do Aeroporto de Partida na Base (3 LETRAS, digite um número de 1 a " << QUANT_AEROP << "): ";
                else cout << "    Código do Aeroporto de Destino na Base (3 LETRAS, digite um número de 1 a " << QUANT_AEROP << "): ";
                cin >> codAer;
                while (codAer < 1 || codAer > QUANT_AEROP){
                    listarAeroportos();
                    if (pouso) cout << "    Código do Aeroporto de Partida na Base (3 LETRAS, digite um número de 1 a " << QUANT_AEROP << "): ";
                    else cout << "    Código do Aeroporto de Destino na Base (3 LETRAS, digite um número de 1 a " << QUANT_AEROP << "): ";
                    cin >> codAer;
                }

                cout << "    Tempo de Vôo: ";
                cin >> tempoVoo;
                cout << "    O vôo descrito é de emergência? (0 - NÃO, 1 - SIM): ";
                cin >> emerg;

                v = new Voo(av, aerop[codAer-1], tempoVoo, emerg, pouso, tempoAtual);
            }

            if (lerDados){
                if (v->getAviao()->getCombustivel() <= 3) v->setEmergencia(true);

                if (v->isPouso() && !v->isEmergencia()){
                    te1 = p1->f->getSize()*3 + (4 - (int) p1->getEstado())%4;
                    te2 = p2->f->getSize()*3 + (4 - (int) p2->getEstado())%4;

                    if (te1 > v->getAviao()->getCombustivel() && te2 > v->getAviao()->getCombustivel()) v->setEmergencia(true);
                }

                if (v->isEmergencia() && v->isPouso()){
                    te1 = p1->getTempoEspera(v, &predP1);
                    te2 = p2->getTempoEspera(v, &predP2);
                }
                
                if(!v->isEmergencia() && !v->isPouso()){
                    te1 = p1->f->getSize()*3 + (4 - (int) p1->getEstado())%4;
                    te2 = p2->f->getSize()*3 + (4 - (int) p2->getEstado())%4;
                    te3 = p3->f->getSize()*3 + (4 - (int) p2->getEstado())%4;

                    if (te1 > v->getTempoVoo() / 10 && te2 > v->getTempoVoo() / 10 && te3 > v->getTempoVoo() / 10) v->setEmergencia(true);
                }

                if(v->isEmergencia() && !v->isPouso()){
                    te1 = p1->getTempoEspera(v, &predP1);
                    te2 = p2->getTempoEspera(v, &predP2);
                    te3 = p3->getTempoEspera(v, &predP3);
                }
                
                if (v->isPouso()){
                    quantEspPouso++;
                    if(te1 <= v->getAviao()->getCombustivel() && te2 <= v->getAviao()->getCombustivel()){
                        quantCombEsp += v->getAviao()->getCombustivel();

                        if(te1 < te2 || (te1 == te2 && p1->f->getSize() <= p2->f->getSize()) ){
                            if (!v->isEmergencia()) predP1 = p1->f->getLastNode();
                            p1->f->enqDepois(&predP1, v, &tempoPousos, &tempoDecol);
                            tempoPousos += te1;
                        }else{
                            if (!v->isEmergencia()) predP2 = p2->f->getLastNode();
                            p2->f->enqDepois(&predP2, v, &tempoPousos, &tempoDecol);
                            tempoPousos += te2;
                        }
                    }else if(te1 <= v->getAviao()->getCombustivel() || te2 <= v->getAviao()->getCombustivel()){
                        quantCombEsp += v->getAviao()->getCombustivel();

                        if (te1 <= v->getAviao()->getCombustivel()){
                            if (!v->isEmergencia()) predP1 = p1->f->getLastNode();
                            p1->f->enqDepois(&predP1, v, &tempoPousos, &tempoDecol);
                            tempoPousos += te1;
                        }else{
                            if (!v->isEmergencia()) predP2 = p2->f->getLastNode();
                            p2->f->enqDepois(&predP2, v, &tempoPousos, &tempoDecol);
                            tempoPousos += te2;
                        }
                    }else{
                        v->setEmergencia(true);
                        te3 = p3->getTempoEspera(v, &predP3);
                        if (te3 <= v->getAviao()->getCombustivel() ) {
                            p3->f->enqDepois(&predP3, v, &tempoPousos, &tempoDecol);
                            tempoPousos += te3;
                            quantCombPouso += v->getAviao()->getCombustivel();
                            quantCombEsp += v->getAviao()->getCombustivel();
                        }else{
                            quantEspPouso--;
                            cout << " - Avião " << v->getAviao()->getId() << " " << v->getAeroporto() << " é desviado para aeroporto vizinho.\n" << endl;
                            delete v;
                        }
                    }
                }else{
                    quantEspDecol++;
                    //Decolagens
                    if (te3 <= te1 && te3 <= te2){
                        if ( !v->isEmergencia() ) predP3 = p3->f->getLastNode();
                        p3->f->enqDepois(&predP3, v, &tempoPousos, &tempoDecol);
                        tempoDecol += te3;
                    }else if (te1 <= te3 && te1 <= te2){
                        if ( !v->isEmergencia() ) predP1 = p1->f->getLastNode();
                        p1->f->enqDepois(&predP1, v, &tempoPousos, &tempoDecol);
                        tempoDecol += te1;
                    }else{
                        if ( !v->isEmergencia() ) predP2 = p2->f->getLastNode();
                        p2->f->enqDepois(&predP2, v, &tempoPousos, &tempoDecol);
                        tempoDecol += te2;
                    }
                }

                exibirPistas(p1, p2, p3);
                if (entrada == 0){
                    cout << "Deseja enviar mais informações de vôos para a torre de comando (0 - NÃO, 1 - SIM)? ";
                    cin >> lerDados;
                }
            }
        }
        p1->atualizarPista(&quantCombPouso, &quantEspPouso, &quantEspDecol, &quantCombEsp, &quantEmgPouso, &quantEmgDecol, &quantPousos, &quantDecol);
        p2->atualizarPista(&quantCombPouso, &quantEspPouso, &quantEspDecol, &quantCombEsp, &quantEmgPouso, &quantEmgDecol, &quantPousos, &quantDecol);
        p3->atualizarPista(&quantCombPouso, &quantEspPouso, &quantEspDecol, &quantCombEsp, &quantEmgPouso, &quantEmgDecol, &quantPousos, &quantDecol);

        if (quantPousos != 0) mediaCombPouso = (float)quantCombPouso/(float)quantPousos;
        else mediaCombPouso = 0;
        
        if(quantPousos+quantEspPouso != 0) mediaPouso = (float)tempoPousos/(float)(quantPousos+quantEspPouso);
        else mediaPouso = 0;

        if (quantEspDecol + quantDecol != 0) mediaDecol = (float) tempoDecol/(float)(quantEspDecol+quantDecol);
        else mediaDecol = 0;

        if (quantEspPouso != 0) mediaCombEsp = (float)quantCombEsp/(float)quantEspPouso;
        else mediaCombEsp = 0;

        cout << endl << "INSTANTE: " << tempoAtual << " / " << tempoSimulacao << "; POUSOS: " << quantPousos << "; DECOLAGENS: " << quantDecol << endl;
        exibirPistas(p1, p2, p3);
        cout << "T.M.E. Pousos: " << mediaPouso << " ut; T.M.E. Decolagens: " << mediaDecol << " ut" << endl;
        cout << "Média de Combustível dos Aviões que Pousaram: " << mediaCombPouso << " tc" << endl;
        cout << "Média de Combustível dos Aviões aguardando para Pousar: " << mediaCombEsp << " tc" << endl;
        cout << quantEmgPouso << " aviões pousaram em condições de emergência." << endl;
        cout << quantEmgDecol << " aviões decolaram em condições de emergência." << endl;
        cout << endl;

        quantCombEsp -= quantEspPouso;
    }

    if (arq.is_open()) arq.close();
    delete p1;
    delete p2;
    delete p3;
}