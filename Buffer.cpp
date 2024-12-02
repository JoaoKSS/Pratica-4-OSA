#include "Buffer.h"
#include "Index.h"
#include "arvore.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

Buffer::Buffer(const string& nomeArquivo, const string& nomeArquivoIndex) 
    : nomeArquivo(nomeArquivo), nomeArquivoIndex(nomeArquivoIndex) {}

void Buffer::escreverDescritor(const vector<Registro>& registros) {
    ofstream arquivoSaida(nomeArquivo, ios::trunc | ios::binary);
    if (!arquivoSaida)
        throw runtime_error("Erro ao abrir o arquivo para escrita.");

    // Vetor índices
    vector<Index> indices;

    for (const Registro& reg : registros) {
        // Empacota o registro
        string buffer = reg.packDescritor();
        // Salva a posição 
        streampos pos = arquivoSaida.tellp();
        // Escreve o registro no arquivo de dados
        arquivoSaida.write(buffer.data(), buffer.size());
        // Cria o objeto Index
        Index index(reg.ID, pos, nomeArquivoIndex);
        Node n = {reg.ID, pos};
        arvoreIndices.Inserir(n);
        // Adiciona o índice no vetor (para posterior escrita no arquivo)
        indices.push_back(index);
    }
    // Mostra a arvore inserida
    // arvoreIndices.Print();
    arquivoSaida.close();
    // Abre o arquivo de índice para escrita
    ofstream arquivoIndex(nomeArquivoIndex, ios::trunc);
    if (!arquivoIndex.is_open())
        throw runtime_error("Erro ao abrir o arquivo de índice.");
    // Escreve todos os índices no arquivo
    for (const Index& index : indices) {
        arquivoIndex << index.id << "|" << index.endereco << "\n";
    }
    arquivoIndex.close();
}

Registro Buffer::lerDescritor() {
    ifstream arquivoEntrada(nomeArquivo, ios::binary);
    if (!arquivoEntrada)
        throw runtime_error("Erro ao abrir o arquivo para leitura.");

    int tamanho;
    arquivoEntrada.read(reinterpret_cast<char*>(&tamanho), sizeof(int));
    if (!arquivoEntrada)
        throw runtime_error("Erro ao ler o descritor de tamanho.");

    string buffer(tamanho, '\0');
    arquivoEntrada.read(&buffer[0], tamanho);
    if (!arquivoEntrada)
        throw runtime_error("Erro ao ler o registro com descritor.");

    Registro reg;
    reg.unpackDescritor(buffer);
    return reg;
}


int Buffer::buscarEndereco(int id) {
    // Busca na árvore 
    int address = arvoreIndices.Busca(id);
    if (address != 0) {
        cout << "Índice encontrado: ID = " << id << ", Endereço = " << address << endl;
        return address;
    } else {
        cout << "Índice com ID " << id << " não encontrado." << endl;
        throw runtime_error("Índice não encontrado.");
    }
}

void Buffer::buscarRegistro(int id){
    int encontra = buscarEndereco(id); // Procura o índice com ID 
    ifstream file(nomeArquivo, ios::binary);
    file.seekg(static_cast<streampos>(encontra));
    string buffer;
    char DelimitadorF;
    // Encontrar o delimitador final '\n'
    while (file.get(DelimitadorF)) {
        buffer += DelimitadorF;
        if (DelimitadorF == '\n') {
            break;
        }
    }
    if (buffer.empty()) {
        cerr << "Erro: nenhum dado lido!" << endl;
        return;
    }
    Registro REG;
    REG.unpackDescritor(buffer);
    // Exibir os dados desserializados
    cout << "===================================================" << endl;
    cout << "ID: " << REG.ID << endl;
    cout << "Title: " << REG.title << endl;
    cout << "Authors: " << REG.authors << endl;
    cout << "Publish Year: " << REG.publishYear << endl;
    cout << "Category: " << REG.category << endl;
    cout << "===================================================" << endl;
    file.close();
}

void Buffer::adicionarRegistros(const vector<Registro>& registros) {
    ofstream arquivoSaida(nomeArquivo, ios::app | ios::binary);
    if (!arquivoSaida)
        throw runtime_error("Erro ao abrir o arquivo para escrita.");

    // Vetor de índices
    vector<Index> indices;

    for (const Registro& reg : registros) {
        // Empacota o registro
        string buffer = reg.packDescritor();
        // Salva a posição 
        streampos pos = arquivoSaida.tellp();
        // Escreve o registro no arquivo de dados
        arquivoSaida.write(buffer.data(), buffer.size());
        // Cria o objeto Index
        Index index(reg.ID, pos, nomeArquivoIndex);
        Node n = {reg.ID, pos};
        arvoreIndices.Inserir(n);
        // Adiciona o índice no vetor (para posterior escrita no arquivo)
        indices.push_back(index);
    }
    arquivoSaida.close();
    // escreve no arquivo de índice para escrita
    ofstream arquivoIndex(nomeArquivoIndex, ios::app);
    if (!arquivoIndex.is_open())
        throw runtime_error("Erro ao abrir o arquivo de índice.");
    // Escreve todos os índices no arquivo
    for (const Index& index : indices) {
        arquivoIndex << index.id << "|" << index.endereco << "\n";
    }
    arquivoIndex.close();
}
