#include "Buffer.h"
#include "Registro.h"
#include "Index.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// função que conta o número de aspas
int count_quotes(const string& str) {
    int count = 0;
    for (char c : str) {
        if (c == '"') {
            count++;
        }
    }
    return count;
}

// função leitura dos campos para garantir que a string title seja lida corretamente, mesmo quando ela contém aspas.
bool read_field(stringstream& ss, string& field) {
    getline(ss, field, ';');
    
    // Verifica se há aspas
    while (count_quotes(field) % 2 != 0) {
        string temp;
        getline(ss, temp, ';');
        field += ";" + temp;
    }
    
    // Retorna verdadeiro se o campo foi lido com sucesso
    return true;
}


int main() {
    string arquivoCSV = "booksDataset.csv";
    string arquivoBinario = "dados_binario.dat";
    string arquivoIndex = "index.txt";
    vector<Registro> registros;

    // 1. Lê os registros do arquivo CSV e os armazena em um vetor
    ifstream arquivoEntrada(arquivoCSV);
    if (!arquivoEntrada) {
        cerr << "Erro ao abrir o arquivo CSV para leitura.\n";
        return 1;
    }

    string linha;
    getline(arquivoEntrada, linha);
    while (getline(arquivoEntrada, linha)) {
        stringstream ss(linha);
        string ID_str, title, authors, publishYear_str, category;

        getline(ss, ID_str, ';');
        if (!read_field(ss, title)) {
            cerr << "Erro ao ler título" << endl;
            continue;
        }
        // getline(ss, title, ';');
        getline(ss, authors, ';');
        getline(ss, publishYear_str, ';');
        getline(ss, category);

        int ID = stoi(ID_str);
        int publishYear = stoi(publishYear_str);
        
        Registro reg(ID, title, authors, publishYear, category);
        registros.push_back(reg);
        //cout << reg.ID << endl;
    }
    arquivoEntrada.close();
    

    // 2. Salva os registros no formato binário com descritor de tamanho
    ofstream arquivoSaidaBinario(arquivoBinario, ios::binary);
    if (!arquivoSaidaBinario) {
        cerr << "Erro ao abrir o arquivo para escrita no formato binário.\n";
        return 1;
    }

    for (const Registro& reg : registros) {
        string registroBinario = reg.packDescritor();
        arquivoSaidaBinario.write(registroBinario.c_str(), registroBinario.size());
    }
    arquivoSaidaBinario.close();

    cout << "Leitura e gravação de registros concluída com sucesso!\n";
    return 0;
}
