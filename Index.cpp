#include "Index.h"
#include <cstring>
#include<string>
#include<sstream>
#include <fstream>
#include <iostream>
using namespace std;

Index::Index(const string& nomeArquivo) 
    : nomeArquivo(nomeArquivo) {}

Index::Index(int id, streampos endereco,  const string& nomeArquivo)
    : id(id), endereco(endereco), nomeArquivo(nomeArquivo) {}

Index::Index() {}

void Index::escreveIndex() {
    // Abrir o arquivo para adicionar no final (modo texto)
    ofstream arquivoIndex(nomeArquivo, ios:: app);
    if (!arquivoIndex.is_open()) {
        cerr << "Falha ao abrir o arquivo de índice: " << nomeArquivo << endl;
        throw runtime_error("Erro ao abrir o arquivo de índice para escrita.");
    }

    // Criar o registro no formato: "ID|POSIÇÃO\n"
    arquivoIndex << id << "|" << endereco << "\n";
}

// Operador de comparação '>'
bool Index::operator>(const Index& other) const {
    return id > other.id; 
}

// Operador de comparação '<'
bool Index::operator<(const Index& other) const {
    return id < other.id; 
}

// Operador de comparação '=='
bool Index::operator==(const Index& other) const {
    return id == other.id;
}

