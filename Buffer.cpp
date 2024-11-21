#include "Buffer.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

Buffer::Buffer(const string& nomeArquivo) : nomeArquivo(nomeArquivo) {}

void Buffer::escreverDelimitado(const Registro& reg) {
    ofstream arquivoSaida(nomeArquivo, ios::app);
    if (!arquivoSaida)
        throw runtime_error("Erro ao abrir o arquivo para escrita.");
    arquivoSaida << reg.packDelimited();
    arquivoSaida.close();
}

void Buffer::escreverDescritor(const Registro& reg) {
    ofstream arquivoSaida(nomeArquivo, ios::app | ios::binary);
    if (!arquivoSaida)
        throw runtime_error("Erro ao abrir o arquivo para escrita.");
    string buffer = reg.packDescritor();
    arquivoSaida.write(buffer.data(), buffer.size());
    arquivoSaida.close();
}

Registro Buffer::lerDelimitado() {
    ifstream arquivoEntrada(nomeArquivo);
    if (!arquivoEntrada)
        throw runtime_error("Erro ao abrir o arquivo para leitura.");

    string buffer;
    if (getline(arquivoEntrada, buffer)) {
        Registro reg;
        reg.unpackDelimited(buffer);
        arquivoEntrada.close();
        return reg;
    }
    throw runtime_error("Fim do arquivo ou erro na leitura.");
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
    reg.unpackDelimited(buffer);
    return reg;
}
