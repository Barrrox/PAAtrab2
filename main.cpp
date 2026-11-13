#include <iostream>
#include <fstream>  // Para ler e escrever arquivos (ifstream / ofstream)
#include <vector>   // Para armazenar os números (std::vector)
#include <string>   // Para manipular os nomes dos arquivos
#include <chrono>   // Para calcular tempo de execução das funções
using namespace std;

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

struct noArvore {
    int temp;
};

pair<noArvore, long long> ConstruirAVL(const vector<int> entrada){

    noArvore raiz;
    return make_pair(raiz, 10000);
}

pair<noArvore, long long> ConstruirRN(const vector<int> entrada){

    noArvore raiz;
    return make_pair(raiz, 10000);
}

auto ConsultarAVL(const noArvore parametro1, const vector<int> parametro2){

    return 0;
}

auto ConsultarRN(const noArvore parametro1, const vector<int> parametro2){

    return 0;
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
        << "Comp_Constr_RN,Tempo_Constr_RN_ms,"
        << "Comp_Consul_RN,Tempo_Consul_RN_ms\n";

    // Loop principal
    // Para cada entrada:
    // 1. Le entrada de construir e consultar
    // 2. Executa Métodos e conta o tempo
    // 3. Salva resultados

    double tempoConstrucaoAVL = 0;
    double tempoConstrucaoRN = 0;
    double tempoConsultaAVL = 0;
    double tempoConsultaRN = 0;

    long long compConstrucaoRN;
    long long compConstrucaoAVL;
    long long compConsultaRN;
    long long compConsultaAVL;

    
    int tamanho;
    for (string entrada : entradas){

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
            auto [arvoreAVL, compConstrucaoAVL] = ConstruirAVL(entradaConstr);
            auto fim = chrono::high_resolution_clock::now();
            if (i != 0)
                tempoConstrucaoAVL += chrono::duration<double, milli>(fim - inicio).count();

            // Consulta AVL
            inicio = chrono::high_resolution_clock::now();
            compConsultaAVL = ConsultarAVL(arvoreAVL, entradaConsul);
            fim = chrono::high_resolution_clock::now();
            if (i != 0)
                tempoConsultaAVL += chrono::duration<double, milli>(fim - inicio).count();

            // Construção Rubro-Negra
            inicio = chrono::high_resolution_clock::now();
            auto [arvoreRN, compConstrucaoRN] = ConstruirRN(entradaConstr);
            fim = chrono::high_resolution_clock::now();
            if (i != 0)
                tempoConstrucaoRN += chrono::duration<double, milli>(fim - inicio).count();

            // Consulta Rubro-Negra
            inicio = chrono::high_resolution_clock::now();
            compConsultaRN = ConsultarRN(arvoreRN, entradaConsul);
            fim = chrono::high_resolution_clock::now();
            if (i != 0)
                tempoConsultaRN += chrono::duration<double, milli>(fim - inicio).count();
        
            tamanho = entradaConstr.size();
        }
       
               // Salvar resultados
    

    csv << tamanho << ","
        << compConstrucaoAVL << "," << tempoConstrucaoAVL/5 << ","
        << compConsultaAVL   << "," << tempoConsultaAVL/5   << ","
        << compConstrucaoRN  << "," << tempoConstrucaoRN/5  << ","
        << compConsultaRN    << "," << tempoConsultaRN/5    << endl; // o endl salva no disco 
    }

    csv.close();
    cout << "Execuções concluídas. Resultados salvos em resultados.csv" << endl;

    return 0;
}