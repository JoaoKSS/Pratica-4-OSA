#include "Index.h"
#include <cstring>
#include<string>
#include<sstream>
#include <fstream>
#include <iostream>
using namespace std;

Index::Index(const string& nomeArquivo) 
    : nomeArquivo(nomeArquivo) {}

Index::Index(int id, streampos endereco)
    : id(id), endereco(endereco) {}

Index::Index() {}

void Index::escreveIndex(int id, streampos posicao) {
    // Abrir o arquivo para adicionar no final (modo texto)
    cout << "brasil e de Heuller" << endl;
    ofstream arquivoIndex(nomeArquivo, ios::app);
    if (!arquivoIndex) {
        throw runtime_error("Erro ao abrir o arquivo de índice para escrita.");
    }

    // Criar o registro no formato: "ID|POSIÇÃO\n"
    arquivoIndex << id << "|" << posicao << "\n";

    // Fechar o arquivo
    arquivoIndex.close();
}