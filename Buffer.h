#ifndef BUFFER_H
#define BUFFER_H
#include "Registro.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include "arvore.h"
using namespace std;

class Node
{
    public:
		int id;
        streampos endereco;
        
        bool operator>(const Node& other) const {
            return id > other.id; 
        }

        // Operador de comparação '<'
        bool operator<(const Node& other) const {
            return id < other.id; 
        }

        // Operador de comparação '=='
        bool operator==(const Node& other) const {
            return id == other.id;
        }
};

class Buffer {
public:
    string nomeArquivo;
    string nomeArquivoIndex;
    ArvoreBinaria<Node> arvoreIndices; 

    // Buffer(const string& nomeArquivo);
    Buffer(const string& nomeArquivo, const string& nomeArquivoIndex);
    Buffer() : nomeArquivo(""), nomeArquivoIndex("") {} 

    Registro lerDescritor();

    void escreverDescritor(const Registro& reg);
    void escreverDescritorVetor(const vector<Registro>& registros);

    int buscarEnd(int id);
    void buscarRegistro(int id);
    void adicionarRegistros(const vector<Registro>& registros);
};

#endif
