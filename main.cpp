#include "Buffer.h"
#include "Registro.h"
#include "Index.h"
#include "Arvore.h"
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
    string arquivoIndex = "Index.txt";
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
        //getline(ss, title, ';');
        getline(ss, authors, ';');
        getline(ss, publishYear_str, ';');
        getline(ss, category);

        int ID = stoi(ID_str);
        int publishYear = stoi(publishYear_str);
        
        Registro reg(ID, title, authors, publishYear, category);
        registros.push_back(reg);
    }
    arquivoEntrada.close();
    

    // 2. Salva os registros no formato binário com descritor de tamanho
    Buffer buffer(arquivoBinario, arquivoIndex);
    buffer.escreverDescritorVetor(registros);

    //3. Querys
    try {
        //Encontrando registros por id
        buffer.buscarRegistro(103063);
        buffer.buscarRegistro(35244);
        buffer.buscarRegistro(5109);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    //4. Adicionando novos registros
    vector<Registro> novosRegistros = {
        Registro(25303063, "The Great Gatsby", "F. Scott Fitzgerald", 1925, "Fiction"),
        Registro(2325244, "The Catcher in the Rye", "J.D. Salinger", 1951, "Fiction"),
        Registro(2345109, "To Kill a Mockingbird", "Harper Lee", 1960, "Fiction")
    };

    buffer.adicionarRegistros(novosRegistros);

    try {
        for(auto reg : novosRegistros) {
            buffer.buscarRegistro(reg.ID);
        }
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }


    cout << endl << "Leitura e gravação de registros concluída com sucesso!\n";
    return 0;
}


