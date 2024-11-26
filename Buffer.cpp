#include "Buffer.h"
#include "Index.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

Buffer::Buffer(const string& nomeArquivo) : nomeArquivo(nomeArquivo) {}

void Buffer::escreverDescritor(const Registro& reg) {
    ofstream arquivoSaida(nomeArquivo, ios::app | ios::binary);
    if (!arquivoSaida)
        throw runtime_error("Erro ao abrir o arquivo para escrita.");
    string buffer = reg.packDescritor();
    streampos pos = arquivoSaida.tellp();
    arquivoSaida.write(buffer.data(), buffer.size());
    Index i;
    i.escreveIndex(reg.ID, pos);
    arquivoSaida.close();
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
    return reg;
}
