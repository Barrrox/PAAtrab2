#include <iostream>
#include <fstream>  // Para ler e escrever arquivos (ifstream / ofstream)
#include <vector>   // Para armazenar os números (std::vector)
#include <string>   // Para manipular os nomes dos arquivos
#include <chrono>   // Para calcular tempo de execução das funções
#include "AVL.hpp"  // Arvore AVL
#include "RB.hpp"  // Arvore Red-Black
using namespace std;

typedef long long shenlong;

vector<int> lerEntrada(string caminho){
    vector<int> numeros; // Array com a entrada lida
    ifstream arquivo(caminho); // Abre o arquivo para leitura

    if (!arquivo){
        cout << "Erro ao abrir o arquivo" << caminho << endl;
        return numeros;
    }

    int valor;
    while(arquivo >> valor){ // >> funciona igual cin, pula espaços em branco e retorna valor inteiro lido
        numeros.push_back(valor); // Concatena no vetor
    }

    return numeros;
}


int main() {

    vector<string> entradas = {
        "50.txt",
        "100.txt",
        "200.txt",
        "300.txt",
        "500.txt",
        "750.txt",
        "1000.txt",
        "1500.txt",
        "2000.txt",
        "3000.txt",
        "5000.txt",
        "7500.txt",
        "10000.txt",
        "12500.txt",
        "15000.txt",
        "20000.txt",
        "25000.txt",
        "30000.txt",
        "40000.txt",
        "50000.txt",
        "75000.txt",
        "100000.txt",
        "125000.txt",
        "150000.txt",
        "175000.txt",
        "200000.txt",
        "225000.txt",
        "250000.txt"
    };

    // Inicialização do CSV

    // Abre (ou cria) o arquivo resultados.csv para escrita
    ofstream csv("resultados.csv");

    if (!csv) {
        cout << "Erro ao criar o arquivo CSV!" << endl;
        return 1;
    }

    // Escreve o cabeçalho (1ª linha da tabela)
    csv << "Tamanho,"
        << "Comp_Constr_AVL,Tempo_Constr_AVL_ms,"
        << "Comp_Consul_AVL,Tempo_Consul_AVL_ms,"
        << "Comp_Constr_RB,Tempo_Constr_RB_ms,"
        << "Comp_Consul_RB,Tempo_Consul_RB_ms\n";

    // Loop principal
    // Para cada entrada:
    // 1. Le entrada de construir e consultar
    // 2. Executa Métodos e conta o tempo
    // 3. Salva resultados

    

    shenlong compConstrucaoRB;
    shenlong compConstrucaoAVL;
    shenlong compConsultaRB;
    shenlong compConsultaAVL;

    
    int tamanho;
    for (string entrada : entradas){

        double tempoConstrucaoAVL = 0;
        double tempoConstrucaoRB = 0;
        double tempoConsultaAVL = 0;
        double tempoConsultaRB = 0;

        string caminhoConstr = "entrada/Construir/" + entrada;
        string caminhoConsul = "entrada/Consultar/" + entrada;

        vector<int> entradaConstr = lerEntrada(caminhoConstr);
        vector<int> entradaConsul = lerEntrada(caminhoConsul);

        for(int i = 0; i < 6; i++){


            if (entradaConstr.empty() || entradaConsul.empty()){
                cout << entradaConstr.size() << entradaConsul.size() << endl;
                cout << "Erro ao ler entradas!" << endl;
                return 2;
            }

            // Construção AVL
            auto inicio = chrono::high_resolution_clock::now();
            arvoreAVL* noAVL = ConstruirAVL(entradaConstr, compConstrucaoAVL);
            auto fim = chrono::high_resolution_clock::now();
            if (i != 0)
                tempoConstrucaoAVL += chrono::duration<double, milli>(fim - inicio).count();


            // Consulta AVL
            inicio = chrono::high_resolution_clock::now();
            compConsultaAVL = ConsultarAVL(noAVL, entradaConsul);
            fim = chrono::high_resolution_clock::now();
            if (i != 0)
                tempoConsultaAVL += chrono::duration<double, milli>(fim - inicio).count();
            
            
            
            delete noAVL;

            // Construção Rubro-Negra
            inicio = chrono::high_resolution_clock::now();
            arvoreRB *noRB = ConstruirRB(entradaConstr, compConstrucaoRB);
            fim = chrono::high_resolution_clock::now();
            if (i != 0)
                tempoConstrucaoRB += chrono::duration<double, milli>(fim - inicio).count();

            // Consulta Rubro-Negra
            inicio = chrono::high_resolution_clock::now();
            compConsultaRB = ConsultarRB(noRB, entradaConsul);
            fim = chrono::high_resolution_clock::now();
            if (i != 0)
                tempoConsultaRB += chrono::duration<double, milli>(fim - inicio).count();
        
            tamanho = entradaConstr.size();



            delete noRB;
        }
       
               // Salvar resultados
    

    csv << tamanho << ","
        << compConstrucaoAVL << "," << tempoConstrucaoAVL/5 << ","
        << compConsultaAVL   << "," << tempoConsultaAVL/5   << ","
        << compConstrucaoRB  << "," << tempoConstrucaoRB/5  << ","
        << compConsultaRB    << "," << tempoConsultaRB/5    << endl; // o endl salva no disco 
    }

    csv.close();
    cout << "Execuções concluídas. Resultados salvos em resultados.csv" << endl;

    return 0;
}